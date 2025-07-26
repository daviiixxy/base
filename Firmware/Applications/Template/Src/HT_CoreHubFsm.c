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
#include "cJSON.h"

// === SUPORTE A MÚLTIPLOS AMBIENTES (MESANINO, PROTOTIPAGEM, EXTERNO) ===
typedef enum {
    AMBIENTE_MESANINO = 0,
    AMBIENTE_PROTOTIPAGEM,
    AMBIENTE_EXTERNO,
    NUM_AMBIENTES
} CoreHub_AmbienteId;

static const char* ambiente_nome[NUM_AMBIENTES] = { "mesanino", "prototipagem", "externo" };

// Struct de ambiente (ainda sem lógica FSM/callback)
typedef struct {
    MQTTClient mqttClient;
    Network mqttNetwork;
    uint8_t mqttSendbuf[HT_COREHUB_MQTT_BUFFER_SIZE];
    uint8_t mqttReadbuf[HT_COREHUB_MQTT_BUFFER_SIZE];
    CoreHub_Data_t corehub_data;
    CoreHub_FSM_States current_state;
    // Buffers para retain/flags
    volatile int new_temp_data;
    volatile int new_hum_data;
    float buffered_temp;
    float buffered_hum;
    char nome[16];
} CoreHub_Ambiente_t;

static CoreHub_Ambiente_t ambientes[NUM_AMBIENTES];

// Função para montar tópicos dinâmicos
static void monta_topico(char* buffer, size_t buflen, const char* ambiente, const char* recurso) {
    snprintf(buffer, buflen, "hana/%s/%s", ambiente, recurso);
}

// Esqueleto da task de ambiente (ainda sem lógica FSM/callback)
void CoreHub_AmbienteTask(void *pvParameters) {
    CoreHub_Ambiente_t *amb = (CoreHub_Ambiente_t *)pvParameters;
    char topic_door[64], topic_light[64], topic_buzzer[64], topic_temp[64], topic_hum[64], topic_ac_power[64], topic_ac_temp[64];
    monta_topico(topic_door, sizeof(topic_door), amb->nome, "smartdoor/door");
    monta_topico(topic_light, sizeof(topic_light), amb->nome, "smartdoor/light");
    monta_topico(topic_buzzer, sizeof(topic_buzzer), amb->nome, "smartdoor/buzzer");
    monta_topico(topic_temp, sizeof(topic_temp), amb->nome, "senseclima/01/temperature");
    monta_topico(topic_hum, sizeof(topic_hum), amb->nome, "senseclima/01/humidity");
    monta_topico(topic_ac_power, sizeof(topic_ac_power), amb->nome, "aircontrol/01/power");
    monta_topico(topic_ac_temp, sizeof(topic_ac_temp), amb->nome, "aircontrol/01/temperature");
    // ... inicialização MQTT, subscribe, FSM, etc (ainda não implementado)
    while (1) {
        // Aqui futuramente rodará a FSM/callback para este ambiente
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

// Inicialização das tasks para cada ambiente
void CoreHub_InitAmbientes(void) {
    for (int i = 0; i < NUM_AMBIENTES; ++i) {
        memset(&ambientes[i], 0, sizeof(CoreHub_Ambiente_t));
        strcpy(ambientes[i].nome, ambiente_nome[i]);
        ambientes[i].current_state = COREHUB_INIT_STATE;
        // ... inicialização MQTT, buffers, etc (ainda não implementado)
        xTaskCreate(CoreHub_AmbienteTask, ambientes[i].nome, 2048, &ambientes[i], 2, NULL);
    }
}
// === FIM SUPORTE A MÚLTIPLOS AMBIENTES ===
// Chame CoreHub_InitAmbientes() na inicialização principal do sistema para ativar as tasks dos ambientes.

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

static volatile int new_temp_data = 0;
static volatile int new_hum_data = 0;
static float buffered_temp = 0.0f;
static float buffered_hum = 0.0f;

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

/* Conversão manual de string para float para ambientes embarcados */
static float simple_str_to_float(const char* str) {
    float result = 0.0f, factor = 1.0f;
    int sign = 1, point_seen = 0;
    if (!str) return 0.0f;
    if (*str == '-') { sign = -1; str++; }
    for (; *str; str++) {
        // Debug: print cada caractere
        printf("CoreHub - DEBUG: analisando char: '%c'\n", *str);
        if (*str == '.') {
            point_seen = 1;
            continue;
        }
        if (*str < '0' || *str > '9') break;
        if (point_seen) {
            factor /= 10.0f;
            result += (*str - '0') * factor;
        } else {
            result = result * 10.0f + (*str - '0');
        }
    }
    float final = sign * result;
    // Convert to integer for display (multiply by 10 to show 1 decimal place)
    int display_value = (int)(final * 10);
    printf("CoreHub - DEBUG: resultado conversão manual = %d.%d\n", display_value/10, display_value%10);
    return final;
}

static float string_to_float(const char* str) {
    float result = simple_str_to_float(str);
    // Convert to integer for display
    int display_value = (int)(result * 10);
    printf("CoreHub - DEBUG: string_to_float('%s') = %d.%d\n", str ? str : "NULL", display_value/10, display_value%10);
    return result;
}

// Adicione no topo do arquivo, após includes:
static int CoreHub_MQTTPublishWithRetry(MQTTClient *mqtt_client, char *topic, uint8_t *payload, uint32_t len, enum QoS qos, uint8_t retained, uint16_t id, uint8_t dup, int max_retries) {
    int rc = -1;
    for (int attempt = 1; attempt <= max_retries; ++attempt) {
        rc = HT_MQTT_Publish(mqtt_client, topic, payload, len, qos, retained, id, dup);
        if (rc == 0) {
            if (attempt > 1) printf("[INFO] Publish no tópico %s OK na tentativa %d\n", topic, attempt);
            return 0;
        }
        printf("[ERRO] Falha ao publicar no tópico %s (tentativa %d)\n", topic, attempt);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
    printf("[ERRO] Todas as tentativas de publish falharam para o tópico %s\n", topic);
    return rc;
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
        float temperature = string_to_float(payload);
        buffered_temp = temperature;
        new_temp_data = 1;
        printf("CoreHub - DEBUG: Bufferizou temperatura = %f\n", buffered_temp);
    }
    else if (strstr(topic, "senseclima/01/humidity")) {
        float humidity = string_to_float(payload);
        buffered_hum = humidity;
        new_hum_data = 1;
        printf("CoreHub - DEBUG: Bufferizou umidade = %f\n", buffered_hum);
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
        int temp_display = (int)(corehub_data.temperature * 10);
        printf("Temperatura: %d.%d°C\n", temp_display/10, temp_display%10);
    } else {
        printf("Temperatura: Não recebida\n");
    }
    
    if (corehub_data.humidity > 0.0f) {
        int hum_display = (int)(corehub_data.humidity * 10);
        printf("Umidade: %d.%d%%\n", hum_display/10, hum_display%10);
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
            if (new_temp_data) {
                corehub_data.temperature = buffered_temp;
                new_temp_data = 0;
                int temp_display = (int)(corehub_data.temperature * 10);
                printf("CoreHub - DEBUG: Valor da temperatura na struct = %d.%d\n", temp_display/10, temp_display%10);
                printf("CoreHub - FSM: Temperatura=%d.%d°C\n", temp_display/10, temp_display%10);
                // Verifica se pode controlar o AC: porta fechada E luz ligada E alarme/buzzer inativo
                if (corehub_data.door_state == 0 && corehub_data.light_state == 1 && !corehub_data.alarm_active && !corehub_data.buzzer_state) {
                    printf("CoreHub - FSM: Condições OK (Porta FECHADA, Luz LIGADA, Alarme INATIVO, Buzzer DESLIGADO) - Analisando temperatura\n");
                    if (corehub_data.temperature > HT_COREHUB_TEMP_LIMIT_UPPER) {
                        printf("CoreHub - FSM: Temp > %.1f°C --> AC_ON_STATE\n", HT_COREHUB_TEMP_LIMIT_UPPER);
                        current_state = COREHUB_AC_ON_STATE;
                    } else if (corehub_data.temperature < HT_COREHUB_TEMP_LIMIT_LOWER) {
                        printf("CoreHub - FSM: Temp < %.1f°C --> AC_OFF_STATE\n", HT_COREHUB_TEMP_LIMIT_LOWER);
                        current_state = COREHUB_AC_OFF_STATE;
                    } else {
                        printf("CoreHub - FSM: Temperatura normal --> IDLE_STATE\n");
                        // Permanece em IDLE_STATE
                    }
                } else {
                    printf("CoreHub - FSM: Condições não atendidas (Porta: %s, Luz: %s, Alarme: %s, Buzzer: %s) --> Ignorando SenseClima\n", 
                        corehub_data.door_state ? "ABERTA" : "FECHADA",
                        corehub_data.light_state ? "LIGADA" : "DESLIGADA",
                        corehub_data.alarm_active ? "ATIVO" : "INATIVO",
                        corehub_data.buzzer_state ? "LIGADO" : "DESLIGADO");
                }
            }
            if (new_hum_data) {
                corehub_data.humidity = buffered_hum;
                new_hum_data = 0;
                int hum_display = (int)(corehub_data.humidity * 10);
                printf("CoreHub - DEBUG: Umidade salva na struct = %d.%d\n", hum_display/10, hum_display%10);
                printf("CoreHub - Umidade: %d.%d%%\n", hum_display/10, hum_display%10);
            }
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

        case COREHUB_AC_ON_STATE:
            printf("CoreHub - FSM: AC_ON_STATE (Ligar Ar Condicionado)\n");
            if (!corehub_data.ac_state) {
                // Verifica se veio do ANALYZE_DOOR_STATE (liga power) ou ANALYZE_TEMP_STATE (só temperatura)
                if (corehub_data.door_state == 0 && corehub_data.light_state == 1) {
                    // Veio do ANALYZE_DOOR_STATE - liga o AC
                    int rc = CoreHub_MQTTPublishWithRetry(&mqttClient, (char*)topic_aircontrol_power, (uint8_t*)"ON", 2, QOS0, 1, 0, 0, 3);
                    if (rc == 0) printf("CoreHub - Publicado: %s = ON (ANALYZE_DOOR_STATE)\n", topic_aircontrol_power);
                } else {
                    // Veio do ANALYZE_TEMP_STATE - só ajusta temperatura
                    printf("CoreHub - Apenas ajustando temperatura (ANALYZE_TEMP_STATE)\n");
                }
                
                // Sempre ajusta o setpoint de temperatura
                char temp_str[8];
                sprintf(temp_str, "%d", HT_COREHUB_AC_TEMP_SETPOINT);
                int rc = CoreHub_MQTTPublishWithRetry(&mqttClient, (char*)topic_aircontrol_temp, (uint8_t*)temp_str, strlen(temp_str), QOS0, 1, 0, 0, 3);
                if (rc == 0) printf("CoreHub - Publicado: %s = %s\n", topic_aircontrol_temp, temp_str);
                corehub_data.ac_state = 1;
            }
            // Transição: Ligar Ar Condicionado --> Ocioso
            current_state = COREHUB_IDLE_STATE;
            break;

        case COREHUB_AC_OFF_STATE:
            printf("CoreHub - FSM: AC_OFF_STATE (Desligar Ar Condicionado)\n");
            if (corehub_data.ac_state) {
                // Verifica se veio do ANALYZE_DOOR_STATE (desliga power) ou ANALYZE_TEMP_STATE (só temperatura)
                if (corehub_data.light_state == 0) {
                    // Veio do ANALYZE_DOOR_STATE - desliga o AC
                    int rc = CoreHub_MQTTPublishWithRetry(&mqttClient, (char*)topic_aircontrol_power, (uint8_t*)"OFF", 3, QOS0, 1, 0, 0, 3);
                    if (rc == 0) printf("CoreHub - Publicado: %s = OFF (ANALYZE_DOOR_STATE)\n", topic_aircontrol_power);
                } else {
                    // Veio do ANALYZE_TEMP_STATE - só faz log
                    printf("CoreHub - AC setado como DESLIGADO (apenas local, ANALYZE_TEMP_STATE)\n");
                }
                corehub_data.ac_state = 0;
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
                int rc = CoreHub_MQTTPublishWithRetry(&mqttClient, (char*)topic_smartdoor_buzzer, (uint8_t*)"ON", 2, QOS0, 1, 0, 0, 3);
                if (rc == 0) printf("CoreHub - Publicado: %s = ON\n", topic_smartdoor_buzzer);
                corehub_data.buzzer_state = 1;
                corehub_data.buzzer_start_time = CoreHub_GetTimeSecs(); // Registra quando ligou
                printf("CoreHub - Buzzer ligado às %lu s\n", corehub_data.buzzer_start_time);
            }
            // Transição: Ligar Buzzer --> Ocioso
            current_state = COREHUB_IDLE_STATE;
            break;

        case COREHUB_BUZZER_OFF_STATE:
            printf("CoreHub - FSM: BUZZER_OFF_STATE (Desligar Buzzer)\n");
            if (corehub_data.buzzer_state) {
                int rc = CoreHub_MQTTPublishWithRetry(&mqttClient, (char*)topic_smartdoor_buzzer, (uint8_t*)"OFF", 3, QOS0, 1, 0, 0, 3);
                if (rc == 0) printf("CoreHub - Publicado: %s = OFF\n", topic_smartdoor_buzzer);
                corehub_data.buzzer_state = 0;
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