/*
 * CoreHub FSM - Implementação Baseada no Diagrama
 * 
 * Estados conforme diagrama:
 * - INIT_STATE: Início
 * - CONNECT_MQTT_STATE: Conectado ao MQTT?
 * - IDLE_STATE: Ocioso: Aguardando Eventos
 * - RECONNECT_STATE: Tenta Reconectar
 * - ANALYZE_DOOR_STATE: Análise: Luz / Porta
 * - ANALYZE_TEMP_STATE: Análise: Temperatura
 * - AC_ON_STATE: Ligar Ar Condicionado
 * - AC_OFF_STATE: Desligar Ar Condicionado
 * - ALARM_LOGIC_STATE: Lógica do Alarme
 * - WAIT_TIMER_STATE: Aguardando Timer (60s)
 * - BUZZER_ON_STATE: Ligar Buzzer
 * - BUZZER_OFF_STATE: Desligar Buzzer
 */

#include "HT_CoreHubFsm.h"
#include "HT_MQTT_Api.h"
#include "stdio.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"
#include "osasys.h" 

/* Estados da FSM - Exatamente como no diagrama */
typedef enum {
    COREHUB_INIT_STATE = 0,           // Início
    COREHUB_CONNECT_MQTT_STATE,       // Conectado ao MQTT?
    COREHUB_IDLE_STATE,               // Ocioso: Aguardando Eventos
    COREHUB_RECONNECT_STATE,          // Tenta Reconectar
    COREHUB_ANALYZE_DOOR_STATE,       // Análise: Luz / Porta
    COREHUB_ANALYZE_TEMP_STATE,       // Análise: Temperatura
    COREHUB_AC_ON_STATE,              // Ligar Ar Condicionado
    COREHUB_AC_OFF_STATE,             // Desligar Ar Condicionado
    COREHUB_ALARM_LOGIC_STATE,        // Lógica do Alarme
    COREHUB_WAIT_TIMER_STATE,         // Aguardando Timer (60s)
    COREHUB_BUZZER_ON_STATE,          // Ligar Buzzer
    COREHUB_BUZZER_OFF_STATE          // Desligar Buzzer
} CoreHub_FSM_States;

/* Estrutura de dados */
typedef struct {
    float temperature;
    float humidity;
    uint8_t door_state;      // 0=CLOSED, 1=OPEN
    uint8_t light_state;     // 0=OFF, 1=ON
    uint8_t ac_state;        // 0=OFF, 1=ON
    uint8_t buzzer_state;    // 0=OFF, 1=ON
    uint32_t alarm_start_time;
    uint32_t buzzer_start_time;  // Tempo quando buzzer foi ligado
    uint32_t system_uptime;
    uint8_t mqtt_connected;
    uint8_t alarm_active;    // 0=INACTIVE, 1=ACTIVE
} CoreHub_Data_t;

/* Variáveis globais */
static MQTTClient mqttClient;
static Network mqttNetwork;
static uint8_t mqttSendbuf[HT_COREHUB_MQTT_BUFFER_SIZE] = {0};
static uint8_t mqttReadbuf[HT_COREHUB_MQTT_BUFFER_SIZE] = {0};
static CoreHub_Data_t corehub_data = {0};
static CoreHub_FSM_States current_state = COREHUB_INIT_STATE;
static TaskHandle_t xMqttTaskHandle = NULL;
static uint8_t mqtt_connection_active = 0;

/* Configurações MQTT */
static const char clientID[] = {"corehub01"};
static const char username[] = {""};
static const char password[] = {""};
static const char broker_addr[] = {"131.255.82.115"};
static const int32_t broker_port = HT_MQTT_PORT;

/* Tópicos MQTT */
static const char topic_smartdoor_door[] = {"hana/externo/smartdoor/door"};
static const char topic_smartdoor_light[] = {"hana/externo/smartdoor/light"};
static const char topic_smartdoor_buzzer[] = {"hana/externo/smartdoor/buzzer"};
static const char topic_senseclima_temp[] = {"hana/externo/senseclima/01/temperature"};
static const char topic_senseclima_humidity[] = {"hana/externo/senseclima/01/humidity"};
static const char topic_aircontrol_power[] = {"hana/externo/aircontrol/01/power"};
static const char topic_aircontrol_temp[] = {"hana/externo/aircontrol/01/temperature"};

/* Função para obter tempo em segundos */
static uint32_t CoreHub_GetTimeSecs(void) {
    static uint32_t start_time = 0;
    uint32_t current_time = OsaSystemTimeReadSecs();
    
    if (start_time == 0) {
        start_time = current_time;
    }
    
    return current_time - start_time;
}

/* Função para converter string para float */
static float string_to_float(const char* str) {
    float result = 0.0f;
    sscanf(str, "%f", &result);
    return result;
}

/* Callback para mensagens MQTT */
static void HT_CoreHub_MessageCallback(MessageData *msg) {
    if (msg == NULL || msg->message == NULL || msg->topicName == NULL) {
        return;
    }
    if (msg->message->payload == NULL || msg->message->payloadlen == 0) {
        return;
    }

    char topic[128] = {0};
    char payload[64] = {0};
    size_t topic_len = msg->topicName->lenstring.len;
    size_t payload_len = msg->message->payloadlen;

    if (topic_len < sizeof(topic)) {
        memcpy(topic, msg->topicName->lenstring.data, topic_len);
        topic[topic_len] = '\0';
    }
    if (payload_len < sizeof(payload)) {
        memcpy(payload, msg->message->payload, payload_len);
        payload[payload_len] = '\0';
    }

    printf("CoreHub - MQTT: %s = %s\n", topic, payload);

    // Processa mensagens conforme diagrama
    if (strstr(topic, "smartdoor/door")) {
        if (strcmp(payload, "OPEN") == 0) {
            corehub_data.door_state = 1;
            printf("CoreHub - Porta ABERTA\n");
        } else if (strcmp(payload, "CLOSED") == 0) {
            corehub_data.door_state = 0;
            printf("CoreHub - Porta FECHADA\n");
            // Se porta fechou e alarme está ativo, desliga buzzer IMEDIATAMENTE
            if (corehub_data.alarm_active || corehub_data.buzzer_state) {
                printf("CoreHub - ALARME: Porta fechou, desligando buzzer/alarme imediatamente!\n");
                current_state = COREHUB_BUZZER_OFF_STATE;
                return;
            }
        }
        // Transição: Msg: SmartDoor --> Análise: Luz / Porta
        current_state = COREHUB_ANALYZE_DOOR_STATE;
    }
    else if (strstr(topic, "smartdoor/light")) {
        corehub_data.light_state = (strcmp(payload, "ON") == 0) ? 1 : 0;
        printf("CoreHub - Luz: %s\n", corehub_data.light_state ? "LIGADA" : "DESLIGADA");
        
        // Se luz apagou e alarme está ativo, desliga buzzer IMEDIATAMENTE
        if (corehub_data.light_state == 0 && (corehub_data.alarm_active || corehub_data.buzzer_state)) {
            printf("CoreHub - ALARME: Luz apagou, desligando buzzer/alarme imediatamente!\n");
            current_state = COREHUB_BUZZER_OFF_STATE;
            return;
        }
        
        // Transição: Msg: SmartDoor --> Análise: Luz / Porta
        current_state = COREHUB_ANALYZE_DOOR_STATE;
    }
    else if (strstr(topic, "senseclima/01/temperature")) {
        float temp = string_to_float(payload);
        if (temp > 0.0f) {
            corehub_data.temperature = temp;
            printf("CoreHub - Temperatura: %.1f°C\n", corehub_data.temperature);
            // Transição: Msg: SenseClima --> Análise: Temperatura
            current_state = COREHUB_ANALYZE_TEMP_STATE;
        }
    }
    else if (strstr(topic, "senseclima/01/humidity")) {
        float hum = string_to_float(payload);
        if (hum > 0.0f) {
            corehub_data.humidity = hum;
            printf("CoreHub - Umidade: %.1f%%\n", corehub_data.humidity);
        }
    }
    else if (strstr(topic, "aircontrol/01/power")) {
        corehub_data.ac_state = (strcmp(payload, "ON") == 0) ? 1 : 0;
        printf("CoreHub - AC: %s\n", corehub_data.ac_state ? "LIGADO" : "DESLIGADO");
    }
}

/* Função para imprimir status */
static void HT_CoreHub_PrintStatus(void) {
    printf("=== CoreHub Status ===\n");
    printf("Estado: %d\n", current_state);
    printf("Uptime: %lu s\n", corehub_data.system_uptime);
    printf("MQTT: %s\n", corehub_data.mqtt_connected ? "Conectado" : "Desconectado");
    printf("Porta: %s\n", corehub_data.door_state ? "ABERTA" : "FECHADA");
    printf("Luz: %s\n", corehub_data.light_state ? "LIGADA" : "DESLIGADA");
    printf("Buzzer: %s\n", corehub_data.buzzer_state ? "LIGADO" : "DESLIGADO");
    printf("AC: %s\n", corehub_data.ac_state ? "LIGADO" : "DESLIGADO");
    printf("Alarme: %s\n", corehub_data.alarm_active ? "ATIVO" : "INATIVO");
    
    if (corehub_data.temperature > 0.0f) {
        printf("Temperatura: %.1f°C\n", corehub_data.temperature);
    } else {
        printf("Temperatura: Não recebida\n");
    }
    
    if (corehub_data.humidity > 0.0f) {
        printf("Umidade: %.1f%%\n", corehub_data.humidity);
    } else {
        printf("Umidade: Não recebida\n");
    }
    
    if (corehub_data.alarm_active) {
        uint32_t elapsed = CoreHub_GetTimeSecs() - corehub_data.alarm_start_time;
        printf("Timer Alarme: %lu s / %d s\n", elapsed, HT_COREHUB_ALARM_TIMEOUT_MS/1000);
    }
    
    if (corehub_data.buzzer_state) {
        uint32_t buzzer_elapsed = CoreHub_GetTimeSecs() - corehub_data.buzzer_start_time;
        printf("Timer Buzzer: %lu s / 30 s\n", buzzer_elapsed);
    }
    printf("======================\n");
}

/* Máquina de Estados - Exatamente como no diagrama */
static void HT_CoreHub_StateMachine(void) {
    switch (current_state) {
        case COREHUB_INIT_STATE:
            printf("CoreHub - FSM: INIT_STATE (Início)\n");
            // Transição: Início --> Conectado ao MQTT?
            current_state = COREHUB_CONNECT_MQTT_STATE;
            break;

        case COREHUB_CONNECT_MQTT_STATE:
            printf("CoreHub - FSM: CONNECT_MQTT_STATE (Conectado ao MQTT?)\n");
            if (corehub_data.mqtt_connected) {
                // Transição: Sim --> Ocioso: Aguardando Eventos
                current_state = COREHUB_IDLE_STATE;
                printf("CoreHub - FSM: Sim --> IDLE_STATE\n");
            } else {
                // Transição: Não --> Tenta Reconectar
                current_state = COREHUB_RECONNECT_STATE;
                printf("CoreHub - FSM: Não --> RECONNECT_STATE\n");
            }
            break;

        case COREHUB_IDLE_STATE:
            // Ocioso: Aguardando Eventos
            // Não faz nada, apenas aguarda mensagens MQTT
            break;

        case COREHUB_RECONNECT_STATE:
            printf("CoreHub - FSM: RECONNECT_STATE (Tenta Reconectar)\n");
            // Tenta reconectar e volta para verificar conexão
            current_state = COREHUB_CONNECT_MQTT_STATE;
            break;

        case COREHUB_ANALYZE_DOOR_STATE:
            printf("CoreHub - FSM: ANALYZE_DOOR_STATE (Análise: Luz / Porta)\n");
            printf("CoreHub - FSM: Luz=%d, Porta=%d\n", corehub_data.light_state, corehub_data.door_state);
            
            if (corehub_data.light_state == 1 && corehub_data.door_state == 0) {
                // Transição: Luz ON & Porta FECHADA --> Ligar Ar Condicionado
                printf("CoreHub - FSM: Luz ON & Porta FECHADA --> AC_ON_STATE\n");
                current_state = COREHUB_AC_ON_STATE;
            } else if (corehub_data.light_state == 0) {
                // Transição: Luz OFF --> Desligar Ar Condicionado
                printf("CoreHub - FSM: Luz OFF --> AC_OFF_STATE\n");
                current_state = COREHUB_AC_OFF_STATE;
            } else if (corehub_data.light_state == 1 && corehub_data.door_state == 1) {
                // Transição: Luz ON & Porta ABERTA --> Lógica do Alarme
                printf("CoreHub - FSM: Luz ON & Porta ABERTA --> ALARM_LOGIC_STATE\n");
                current_state = COREHUB_ALARM_LOGIC_STATE;
            } else {
                // Nenhuma condição atendida --> Volta para Ocioso
                printf("CoreHub - FSM: Nenhuma condição --> IDLE_STATE\n");
                current_state = COREHUB_IDLE_STATE;
            }
            break;

        case COREHUB_ANALYZE_TEMP_STATE:
            printf("CoreHub - FSM: ANALYZE_TEMP_STATE (Análise: Temperatura)\n");
            printf("CoreHub - FSM: Temperatura=%.1f°C\n", corehub_data.temperature);
            
            if (corehub_data.temperature > HT_COREHUB_TEMP_LIMIT_UPPER) {
                // Transição: Temp. > LIM_SUPERIOR --> Ligar Ar Condicionado
                printf("CoreHub - FSM: Temp > %.1f°C --> AC_ON_STATE\n", HT_COREHUB_TEMP_LIMIT_UPPER);
                current_state = COREHUB_AC_ON_STATE;
            } else if (corehub_data.temperature < HT_COREHUB_TEMP_LIMIT_LOWER) {
                // Transição: Temp. < LIM_INFERIOR --> Desligar Ar Condicionado
                printf("CoreHub - FSM: Temp < %.1f°C --> AC_OFF_STATE\n", HT_COREHUB_TEMP_LIMIT_LOWER);
                current_state = COREHUB_AC_OFF_STATE;
            } else {
                // Temperatura normal --> Volta para Ocioso
                printf("CoreHub - FSM: Temperatura normal --> IDLE_STATE\n");
                current_state = COREHUB_IDLE_STATE;
            }
            break;

        case COREHUB_AC_ON_STATE:
            printf("CoreHub - FSM: AC_ON_STATE (Ligar Ar Condicionado)\n");
            if (!corehub_data.ac_state) {
                HT_MQTT_Publish(&mqttClient, (char*)topic_aircontrol_power, (uint8_t*)"ON", 2, QOS0, 1, 0, 0);
                char temp_str[8];
                sprintf(temp_str, "%d", HT_COREHUB_AC_TEMP_SETPOINT);
                HT_MQTT_Publish(&mqttClient, (char*)topic_aircontrol_temp, (uint8_t*)temp_str, strlen(temp_str), QOS0, 1, 0, 0);
                corehub_data.ac_state = 1;
                printf("CoreHub - Publicado: %s = ON\n", topic_aircontrol_power);
                printf("CoreHub - Publicado: %s = %s\n", topic_aircontrol_temp, temp_str);
            }
            // Transição: Ligar Ar Condicionado --> Ocioso
            current_state = COREHUB_IDLE_STATE;
            break;

        case COREHUB_AC_OFF_STATE:
            printf("CoreHub - FSM: AC_OFF_STATE (Desligar Ar Condicionado)\n");
            if (corehub_data.ac_state) {
                HT_MQTT_Publish(&mqttClient, (char*)topic_aircontrol_power, (uint8_t*)"OFF", 3, QOS0, 1, 0, 0);
                corehub_data.ac_state = 0;
                printf("CoreHub - Publicado: %s = OFF\n", topic_aircontrol_power);
            }
            // Transição: Desligar Ar Condicionado --> Ocioso
            current_state = COREHUB_IDLE_STATE;
            break;

        case COREHUB_ALARM_LOGIC_STATE:
            printf("CoreHub - FSM: ALARM_LOGIC_STATE (Lógica do Alarme)\n");
            if (corehub_data.door_state == 1 && corehub_data.light_state == 1 && !corehub_data.alarm_active) {
                corehub_data.alarm_active = 1;
                corehub_data.alarm_start_time = CoreHub_GetTimeSecs();
                printf("CoreHub - Alarme ativado! Timer iniciado.\n");
                // Transição: Inicia Timer (60s) --> Aguardando Timer
                current_state = COREHUB_WAIT_TIMER_STATE;
            } else {
                printf("CoreHub - Condições do alarme não atendidas --> IDLE_STATE\n");
                current_state = COREHUB_IDLE_STATE;
            }
            break;

        case COREHUB_WAIT_TIMER_STATE:
            printf("CoreHub - FSM: WAIT_TIMER_STATE (Aguardando Timer)\n");
            if (corehub_data.alarm_active) {
                uint32_t elapsed = CoreHub_GetTimeSecs() - corehub_data.alarm_start_time;
                uint32_t timeout = HT_COREHUB_ALARM_TIMEOUT_MS / 1000;
                
                if (elapsed >= timeout) {
                    // Transição: Timer Esgotado --> Ligar Buzzer
                    printf("CoreHub - FSM: Timer esgotado (%lu s) --> BUZZER_ON_STATE\n", elapsed);
                    current_state = COREHUB_BUZZER_ON_STATE;
                    // Executa imediatamente o próximo estado
                    break;
                } else if (!corehub_data.door_state || !corehub_data.light_state) {
                    // Transição: Porta Fechou ou Luz Apagou --> Desligar Buzzer
                    printf("CoreHub - FSM: Porta fechou ou luz apagou --> BUZZER_OFF_STATE\n");
                    current_state = COREHUB_BUZZER_OFF_STATE;
                    // Executa imediatamente o próximo estado
                    break;
                } else {
                    // Timer ainda rodando - log a cada 5 segundos para não poluir
                    static uint32_t last_log_time = 0;
                    uint32_t now = CoreHub_GetTimeSecs();
                    if (now - last_log_time >= 5) {
                        printf("CoreHub - FSM: Timer rodando: %lu s / %lu s\n", elapsed, timeout);
                        last_log_time = now;
                    }
                    // Não faz delay aqui, deixa o loop principal controlar
                }
            } else {
                printf("CoreHub - FSM: Alarme não ativo --> IDLE_STATE\n");
                current_state = COREHUB_IDLE_STATE;
            }
            break;

        case COREHUB_BUZZER_ON_STATE:
            printf("CoreHub - FSM: BUZZER_ON_STATE (Ligar Buzzer)\n");
            if (!corehub_data.buzzer_state) {
                HT_MQTT_Publish(&mqttClient, (char*)topic_smartdoor_buzzer, (uint8_t*)"ON", 2, QOS0, 1, 0, 0);
                corehub_data.buzzer_state = 1;
                corehub_data.buzzer_start_time = CoreHub_GetTimeSecs(); // Registra quando ligou
                printf("CoreHub - Publicado: %s = ON\n", topic_smartdoor_buzzer);
                printf("CoreHub - Buzzer ligado às %lu s\n", corehub_data.buzzer_start_time);
            }
            // Transição: Ligar Buzzer --> Ocioso
            current_state = COREHUB_IDLE_STATE;
            break;

        case COREHUB_BUZZER_OFF_STATE:
            printf("CoreHub - FSM: BUZZER_OFF_STATE (Desligar Buzzer)\n");
            if (corehub_data.buzzer_state) {
                HT_MQTT_Publish(&mqttClient, (char*)topic_smartdoor_buzzer, (uint8_t*)"OFF", 3, QOS0, 1, 0, 0);
                corehub_data.buzzer_state = 0;
                printf("CoreHub - Publicado: %s = OFF\n", topic_smartdoor_buzzer);
            }
            
            // Desativa completamente o alarme
            if (corehub_data.alarm_active) {
                corehub_data.alarm_active = 0;
                printf("CoreHub - Alarme completamente desativado\n");
            }
            
            // Transição: Desligar Buzzer --> Ocioso
            current_state = COREHUB_ANALYZE_DOOR_STATE;
            break;

        default:
            printf("CoreHub - FSM: Estado desconhecido (%d), voltando para IDLE\n", current_state);
            current_state = COREHUB_IDLE_STATE;
            break;
    }
}

/* Inicialização dos dados */
static void CoreHub_InitData(void) {
    memset(&corehub_data, 0, sizeof(corehub_data));
    corehub_data.buzzer_start_time = 0;
    corehub_data.alarm_start_time = 0;
    corehub_data.system_uptime = 0;
    current_state = COREHUB_INIT_STATE;
}

/* Inicialização */
void HT_CoreHub_InitTasks(void) {
    printf("CoreHub - Inicializando Tasks FreeRTOS...\n");
    CoreHub_InitData();
}

/* Task MQTT com FSM integrada */
void HT_CoreHub_MqttTask(void *pvParameters) {
    printf("CoreHub - Task MQTT iniciada\n");

    while (1) {
        printf("CoreHub - Tentando conectar ao MQTT Broker...\n");
        
        int result = HT_MQTT_Connect(&mqttClient, &mqttNetwork,
                                    (char*)broker_addr, broker_port,
                                    HT_MQTT_SEND_TIMEOUT, HT_MQTT_RECEIVE_TIMEOUT, (char*)clientID,
                                    (char*)username, (char*)password, HT_MQTT_VERSION, HT_MQTT_KEEP_ALIVE_INTERVAL,
                                    mqttSendbuf, HT_COREHUB_MQTT_BUFFER_SIZE,
                                    mqttReadbuf, HT_COREHUB_MQTT_BUFFER_SIZE);
        
        if (result == 0) {
            printf("CoreHub - Conectado ao MQTT Broker!\n");
            HT_MQTT_SetMessageCallback(HT_CoreHub_MessageCallback);
            
            // Inscreve nos tópicos
            HT_MQTT_Subscribe(&mqttClient, (char*)topic_smartdoor_door, QOS0);
            HT_MQTT_Subscribe(&mqttClient, (char*)topic_smartdoor_light, QOS0);
            HT_MQTT_Subscribe(&mqttClient, (char*)topic_senseclima_temp, QOS0);
            HT_MQTT_Subscribe(&mqttClient, (char*)topic_senseclima_humidity, QOS0);

            corehub_data.mqtt_connected = 1;
            mqtt_connection_active = 1;
            
            printf("CoreHub - Aguardando 2s para receber dados retain...\n");
            vTaskDelay(pdMS_TO_TICKS(1000));
            
            printf("CoreHub - FSM iniciando processamento...\n");
            
            // Loop principal
            uint32_t last_status_time = 0;
            
            while (mqtt_connection_active) {
                corehub_data.system_uptime = CoreHub_GetTimeSecs();
                
                // Yield MQTT
                HT_MQTT_Yield(&mqttClient, 30); // Reduzido de 100ms para 50ms
                
                // Executa FSM
                HT_CoreHub_StateMachine();
                
                // Status periódico
                //uint32_t now = CoreHub_GetTimeSecs();
                //if (now - last_status_time > (HT_COREHUB_STATUS_INTERVAL_MS/1000)) {
                    //HT_CoreHub_PrintStatus();
                    //last_status_time = now;
                //}
                
                if (!corehub_data.mqtt_connected) {
                    printf("CoreHub - Conexão MQTT perdida\n");
                    break;
                }
                
                vTaskDelay(pdMS_TO_TICKS(30)); // Reduzido de 100ms para 50ms
            }
            
            printf("CoreHub - Desconectando do MQTT Broker...\n");
            HT_MQTT_Disconnect(&mqttClient);
            corehub_data.mqtt_connected = 0;
            mqtt_connection_active = 0;
        } else {
            printf("CoreHub - Falha na conexão MQTT (erro: %d)\n", result);
        }
        
        printf("CoreHub - Aguardando 5s antes de tentar reconectar...\n");
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

/* Criação das Tasks */
void HT_CoreHub_StartTasks(void) {
    printf("CoreHub - Criando Tasks FreeRTOS...\n");
    
    BaseType_t result = xTaskCreate(HT_CoreHub_MqttTask, "MQTT_FSM_Task", HT_COREHUB_MQTT_TASK_STACK_SIZE, NULL, 
                                   HT_COREHUB_MQTT_TASK_PRIORITY, &xMqttTaskHandle);
    if (result != pdPASS) { 
        printf("CoreHub - ERRO: Falha ao criar Task MQTT+FSM\n"); 
        return; 
    }
    
    printf("CoreHub - Task MQTT+FSM criada com sucesso!\n");
}