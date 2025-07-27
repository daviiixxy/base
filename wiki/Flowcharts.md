# 🔄 Fluxogramas do CoreHub

> **Sistema de Automação com iMCP HTNB32L**  
> **Diagramas de Fluxo e Estados do Sistema de Automação Inteligente**

---

## 📋 Índice

1. [Máquina de Estados Principal](#máquina-de-estados-principal)
2. [Fluxo de Inicialização](#fluxo-de-inicialização)
3. [Fluxo de Processamento MQTT](#fluxo-de-processamento-mqtt)
4. [Fluxo de Controle de Temperatura](#fluxo-de-controle-de-temperatura)
5. [Fluxo de Alarme](#fluxo-de-alarme)
6. [Fluxo de Reconexão](#fluxo-de-reconexão)
7. [Fluxo de Watchdog](#fluxo-de-watchdog)
8. [Casos de Uso](#casos-de-uso)

---

## 🎯 Máquina de Estados Principal

### 📊 Diagrama de Estados Completo

```mermaid
stateDiagram-v2
    [*] --> INIT : Sistema Iniciado
    
    INIT --> CONNECT_MQTT : Inicialização OK
    
    CONNECT_MQTT --> IDLE : Conexão Estabelecida
    CONNECT_MQTT --> RECONNECT : Falha na Conexão
    
    IDLE --> ANALYZE_DOOR : Evento Porta/Luz
    IDLE --> ANALYZE_TEMP : Evento Temperatura
    IDLE --> CONNECT_MQTT : Perda de Conexão
    
    ANALYZE_DOOR --> AC_ON : Porta Fechada + Luz ON
    ANALYZE_DOOR --> AC_OFF : Luz OFF
    ANALYZE_DOOR --> ALARM_LOGIC : Porta Aberta + Luz ON
    ANALYZE_DOOR --> IDLE : Nenhuma Condição
    
    ANALYZE_TEMP --> AC_ON : Temp > 25°C
    ANALYZE_TEMP --> AC_OFF : Temp < 22°C
    ANALYZE_TEMP --> IDLE : Temp Normal
    
    AC_ON --> IDLE : AC Ligado
    AC_OFF --> IDLE : AC Desligado
    
    ALARM_LOGIC --> WAIT_TIMER : Timer Iniciado
    ALARM_LOGIC --> IDLE : Condições Não Atendidas
    
    WAIT_TIMER --> BUZZER_ON : Timer Expirado (60s)
    WAIT_TIMER --> BUZZER_OFF : Porta Fechada/Luz OFF
    WAIT_TIMER --> WAIT_TIMER : Timer Rodando
    
    BUZZER_ON --> IDLE : Buzzer Ligado
    BUZZER_OFF --> ANALYZE_DOOR : Buzzer Desligado
    
    RECONNECT --> CONNECT_MQTT : Tentativa de Reconexão
```

### 🔄 Transições Detalhadas

| Estado | Condição | Próximo Estado | Ação |
|--------|----------|----------------|------|
| `INIT` | Sistema iniciado | `CONNECT_MQTT` | Inicializar variáveis |
| `CONNECT_MQTT` | Conexão OK | `IDLE` | Configurar MQTT |
| `CONNECT_MQTT` | Falha | `RECONNECT` | Aguardar e tentar |
| `IDLE` | Porta/Luz muda | `ANALYZE_DOOR` | Analisar condições |
| `IDLE` | Temperatura muda | `ANALYZE_TEMP` | Verificar limites |
| `ANALYZE_DOOR` | Porta fechada + Luz ON | `AC_ON` | Ligar ar condicionado |
| `ANALYZE_DOOR` | Luz OFF | `AC_OFF` | Desligar ar condicionado |
| `ANALYZE_DOOR` | Porta aberta + Luz ON | `ALARM_LOGIC` | Ativar lógica de alarme |
| `ANALYZE_TEMP` | Temp > 25°C | `AC_ON` | Ligar ar condicionado |
| `ANALYZE_TEMP` | Temp < 22°C | `AC_OFF` | Desligar ar condicionado |
| `ALARM_LOGIC` | Condições atendidas | `WAIT_TIMER` | Iniciar timer 60s |
| `WAIT_TIMER` | Timer expirado | `BUZZER_ON` | Ligar buzzer |
| `WAIT_TIMER` | Porta fechada/Luz OFF | `BUZZER_OFF` | Desligar buzzer |

---

## 🚀 Fluxo de Inicialização

### 📊 Diagrama de Inicialização

```mermaid
flowchart TD
    A[Power On] --> B[Hardware Init]
    B --> C[FreeRTOS Start]
    C --> D[CoreHub Task Create]
    D --> E[Initialize Ambientes]
    E --> F[Setup MQTT Topics]
    F --> G[Wait for SIM Ready]
    G --> H{SIM Ready?}
    H -->|No| G
    H -->|Yes| I[Configure NB-IoT]
    I --> J[Set Band Mode]
    J --> K[Configure APN]
    K --> L[Wait for Network]
    L --> M{Network Ready?}
    M -->|No| L
    M -->|Yes| N[Connect MQTT]
    N --> O{MQTT Connected?}
    O -->|No| P[Retry Connection]
    P --> N
    O -->|Yes| Q[Subscribe Topics]
    Q --> R[Start FSM]
    R --> S[System Ready]
```

### 🔧 Detalhes da Inicialização

```c
// Sequência de inicialização
void HT_CoreHub_InitSystem(void) {
    // 1. Inicializar hardware
    BSP_CommonInit();
    
    // 2. Inicializar FreeRTOS
    osKernelInitialize();
    
    // 3. Criar task principal
    xTaskCreate(HT_CoreHubTask, "CoreHub", 
               HT_COREHUB_TASK_STACK_SIZE, NULL, 
               HT_COREHUB_TASK_PRIORITY, NULL);
    
    // 4. Inicializar ambientes
    for (int i = 0; i < NUM_AMBIENTES; i++) {
        HT_CoreHub_InitAmbiente(i, ambientes[i]);
    }
    
    // 5. Iniciar kernel
    osKernelStart();
}
```

---

## 📡 Fluxo de Processamento MQTT

### 📊 Diagrama de Processamento MQTT

```mermaid
sequenceDiagram
    participant Device as SmartDoor/SenseClima
    participant MQTT as MQTT Broker
    participant CoreHub as CoreHub FSM
    participant AC as AirControl
    
    Device->>MQTT: Publish sensor data
    MQTT->>CoreHub: Message callback
    
    Note over CoreHub: Validate message
    CoreHub->>CoreHub: Identify environment
    
    alt Valid message
        CoreHub->>CoreHub: Process data
        CoreHub->>CoreHub: Update state machine
        CoreHub->>CoreHub: Execute logic
        
        alt Action required
            CoreHub->>MQTT: Publish command
            MQTT->>AC: Deliver command
            AC->>AC: Execute action
        end
    else Invalid message
        CoreHub->>CoreHub: Log error
        CoreHub->>CoreHub: Discard message
    end
```

### 🔄 Processamento de Mensagens

```c
// Fluxo de processamento MQTT
static void HT_CoreHub_MessageCallback(MessageData *msg) {
    // 1. Validação de entrada
    if (!validateMessage(msg)) {
        return;
    }
    
    // 2. Identificação do ambiente
    int ambiente_idx = CoreHub_IdentificaAmbientePorTopico(topic);
    if (ambiente_idx < 0) {
        return;
    }
    
    // 3. Processamento por tipo
    if (strstr(topic, "smartdoor/door")) {
        processDoorMessage(ambiente_idx, payload);
    } else if (strstr(topic, "smartdoor/light")) {
        processLightMessage(ambiente_idx, payload);
    } else if (strstr(topic, "senseclima/01/temperature")) {
        processTemperatureMessage(ambiente_idx, payload);
    } else if (strstr(topic, "senseclima/01/humidity")) {
        processHumidityMessage(ambiente_idx, payload);
    }
    
    // 4. Atualização da FSM
    updateStateMachine(ambiente_idx);
}
```

---

## 🌡️ Fluxo de Controle de Temperatura

### 📊 Diagrama de Controle de Temperatura

```mermaid
flowchart TD
    A[Temperature Data] --> B{Valid Data?}
    B -->|No| C[Discard Data]
    B -->|Yes| D[Buffer Temperature]
    D --> E{Environment Conditions?}
    E -->|Door Open| F[No AC Control]
    E -->|Light Off| F
    E -->|Alarm Active| F
    E -->|Door Closed + Light On| G{Check Temperature}
    G --> H{Temp > 25°C?}
    H -->|Yes| I[AC ON State]
    H -->|No| J{Temp < 22°C?}
    J -->|Yes| K[AC OFF State]
    J -->|No| L[Maintain Current State]
    I --> M[Publish AC ON]
    K --> N[Publish AC OFF]
    M --> O[Update AC State]
    N --> O
    O --> P[Return to IDLE]
```

### 🌡️ Lógica de Controle

```c
// Controle de temperatura
case COREHUB_IDLE_STATE:
    if (new_temp_data[ambiente_idx]) {
        data->temperature = buffered_temp[ambiente_idx];
        new_temp_data[ambiente_idx] = 0;
        
        // Verificar condições para controle de AC
        if (data->door_state == 0 && data->light_state == 1 && 
            !data->alarm_active && !data->buzzer_state) {
            
            if (data->temperature > HT_COREHUB_TEMP_LIMIT_UPPER) {
                printf("[CoreHub][%s] Temp %.1f°C > %.1f°C - Ligando AC\n", 
                       ambientes[ambiente_idx], data->temperature, 
                       HT_COREHUB_TEMP_LIMIT_UPPER);
                *state = COREHUB_AC_ON_STATE;
            } else if (data->temperature < HT_COREHUB_TEMP_LIMIT_LOWER) {
                printf("[CoreHub][%s] Temp %.1f°C < %.1f°C - Desligando AC\n", 
                       ambientes[ambiente_idx], data->temperature, 
                       HT_COREHUB_TEMP_LIMIT_LOWER);
                *state = COREHUB_AC_OFF_STATE;
            }
        }
    }
    break;
```

---

## 🚨 Fluxo de Alarme

### 📊 Diagrama de Alarme

```mermaid
stateDiagram-v2
    [*] --> MONITORING : Sistema Ativo
    
    MONITORING --> ALARM_TRIGGERED : Porta Aberta + Luz ON
    ALARM_TRIGGERED --> TIMER_START : Iniciar Timer 60s
    
    TIMER_START --> TIMER_RUNNING : Timer Ativo
    TIMER_RUNNING --> TIMER_RUNNING : Aguardando
    
    TIMER_RUNNING --> BUZZER_ACTIVE : Timer Expirado
    TIMER_RUNNING --> ALARM_CLEARED : Porta Fechada OU Luz OFF
    
    BUZZER_ACTIVE --> MONITORING : Buzzer Ligado
    ALARM_CLEARED --> MONITORING : Alarme Desativado
    
    note right of TIMER_RUNNING
        Timer: 60 segundos
        Condições de cancelamento:
        - Porta fechada
        - Luz apagada
    end note
```

### 🔔 Lógica de Alarme

```c
// Estados de alarme
case COREHUB_ALARM_LOGIC_STATE:
    if (data->door_state == 1 && data->light_state == 1 && !data->alarm_active) {
        data->alarm_active = 1;
        data->alarm_start_time = CoreHub_GetTimeSecs();
        printf("[CoreHub][%s] ALARME ATIVADO - Timer iniciado\n", ambientes[ambiente_idx]);
        *state = COREHUB_WAIT_TIMER_STATE;
    } else {
        *state = COREHUB_IDLE_STATE;
    }
    break;

case COREHUB_WAIT_TIMER_STATE:
    if (data->alarm_active) {
        uint32_t elapsed = CoreHub_GetTimeSecs() - data->alarm_start_time;
        uint32_t timeout = HT_COREHUB_ALARM_TIMEOUT_MS / 1000;
        
        if (elapsed >= timeout) {
            *state = COREHUB_BUZZER_ON_STATE;
        } else if (!data->door_state || !data->light_state) {
            *state = COREHUB_BUZZER_OFF_STATE;
        }
    } else {
        *state = COREHUB_IDLE_STATE;
    }
    break;
```

---

## 🔄 Fluxo de Reconexão

### 📊 Diagrama de Reconexão

```mermaid
flowchart TD
    A[Connection Lost] --> B[Detect Loss]
    B --> C[Set Reconnect Flag]
    C --> D[Disconnect MQTT]
    D --> E[Wait 5 Seconds]
    E --> F[Attempt Reconnect]
    F --> G{Reconnect Success?}
    G -->|No| H[Increment Retry Count]
    H --> I{Max Retries?}
    I -->|No| E
    I -->|Yes| J[Reset System]
    G -->|Yes| K[Reinitialize Topics]
    K --> L[Resume Normal Operation]
    J --> A
```

### 🔄 Lógica de Reconexão

```c
// Reconexão MQTT
void HT_CoreHub_Reconnect(void) {
    int retry_count = 0;
    const int max_retries = 10;
    
    while (retry_count < max_retries) {
        printf("[CoreHub] Tentativa de reconexão %d/%d\n", retry_count + 1, max_retries);
        
        // Tentar reconectar
        int result = HT_MQTT_Connect(&mqttClient_global, &mqttNetwork_global,
                                   (char*)broker_addr, broker_port,
                                   HT_MQTT_SEND_TIMEOUT, HT_MQTT_RECEIVE_TIMEOUT,
                                   (char*)clientID, (char*)username, (char*)password,
                                   HT_MQTT_VERSION, HT_MQTT_KEEP_ALIVE_INTERVAL,
                                   mqttSendbuf_global, HT_COREHUB_MQTT_BUFFER_SIZE,
                                   mqttReadbuf_global, HT_COREHUB_MQTT_BUFFER_SIZE);
        
        if (result == 0) {
            printf("[CoreHub] Reconexão bem-sucedida\n");
            
            // Reinscrever nos tópicos
            for (int i = 0; i < NUM_AMBIENTES; i++) {
                HT_MQTT_Subscribe(&mqttClient_global, topic_smartdoor_door[i], QOS0);
                HT_MQTT_Subscribe(&mqttClient_global, topic_smartdoor_light[i], QOS0);
                HT_MQTT_Subscribe(&mqttClient_global, topic_senseclima_temp[i], QOS0);
                HT_MQTT_Subscribe(&mqttClient_global, topic_senseclima_humidity[i], QOS0);
                corehub_data[i].mqtt_connected = 1;
            }
            
            mqtt_connection_active = 1;
            return;
        }
        
        retry_count++;
        vTaskDelay(pdMS_TO_TICKS(5000)); // Aguardar 5 segundos
    }
    
    printf("[CoreHub] Falha na reconexão após %d tentativas\n", max_retries);
    // Reset do sistema se necessário
}
```

---

## 🛡️ Fluxo de Watchdog

### 📊 Diagrama de Watchdog

```mermaid
flowchart TD
    A[Watchdog Timer] --> B{30s Elapsed?}
    B -->|No| A
    B -->|Yes| C[Check FSM Health]
    C --> D{FSM Stuck?}
    D -->|No| E[Log System Health]
    D -->|Yes| F[Mark FSM as Stuck]
    F --> G[Increment Stuck Counter]
    G --> H{Stuck Counter > 500?}
    H -->|No| E
    H -->|Yes| I[Reset FSM]
    I --> J[Clear Stuck Flag]
    J --> K[Reset Execution Counter]
    K --> L[Log Recovery]
    E --> M{5 Minutes Elapsed?}
    M -->|No| A
    M -->|Yes| N[Log System Status]
    N --> A
```

### 🛡️ Sistema de Watchdog

```c
// Watchdog global
static void CoreHub_WatchdogCheck(void) {
    uint32_t current_time = CoreHub_GetTimeSecs();
    
    // Verificar a cada 30 segundos
    if (current_time - last_watchdog_check < 30) {
        return;
    }
    last_watchdog_check = current_time;
    
    // Verificar se alguma FSM está travada
    for (int i = 0; i < NUM_AMBIENTES; i++) {
        if (fsm_execution_count[i] > 500) {
            fsm_stuck_detected[i] = 1;
            printf("[CoreHub] WATCHDOG: FSM %s detectada como travada\n", ambientes[i]);
        }
    }
    
    // Log de saúde do sistema a cada 5 minutos
    static uint32_t health_log_counter = 0;
    health_log_counter++;
    if (health_log_counter >= 10) { // 30s * 10 = 5 minutos
        printf("[CoreHub] SAÚDE: Sistema operando normalmente (%lu s uptime)\n", current_time);
        health_log_counter = 0;
    }
}
```

---

## 🎯 Casos de Uso

### 🏠 Caso de Uso 1: Controle Automático de AC

```mermaid
sequenceDiagram
    participant User as Usuário
    participant Door as SmartDoor
    participant CoreHub as CoreHub
    participant AC as AirControl
    
    User->>Door: Fecha porta
    Door->>CoreHub: Door: CLOSED
    User->>Door: Liga luz
    Door->>CoreHub: Light: ON
    CoreHub->>CoreHub: Analyze door state
    CoreHub->>AC: Power: ON
    CoreHub->>AC: Temperature: 23°C
    AC->>AC: Ligar ar condicionado
```

### 🚨 Caso de Uso 2: Sistema de Alarme

```mermaid
sequenceDiagram
    participant User as Usuário
    participant Door as SmartDoor
    participant CoreHub as CoreHub
    participant Buzzer as Buzzer
    
    User->>Door: Abre porta
    Door->>CoreHub: Door: OPEN
    User->>Door: Liga luz
    Door->>CoreHub: Light: ON
    CoreHub->>CoreHub: Start alarm timer (60s)
    Note over CoreHub: Timer running...
    CoreHub->>Buzzer: Buzzer: ON
    User->>Door: Fecha porta
    Door->>CoreHub: Door: CLOSED
    CoreHub->>Buzzer: Buzzer: OFF
```

### 🌡️ Caso de Uso 3: Controle de Temperatura

```mermaid
sequenceDiagram
    participant Sensor as SenseClima
    participant CoreHub as CoreHub
    participant AC as AirControl
    
    Sensor->>CoreHub: Temperature: 26.5°C
    CoreHub->>CoreHub: Check temperature limits
    CoreHub->>AC: Power: ON
    CoreHub->>AC: Temperature: 23°C
    AC->>AC: Ligar ar condicionado
    
    Note over Sensor,AC: Time passes...
    
    Sensor->>CoreHub: Temperature: 21.8°C
    CoreHub->>CoreHub: Check temperature limits
    CoreHub->>AC: Power: OFF
    AC->>AC: Desligar ar condicionado
```

---

## 📊 Métricas de Fluxo

### ⏱️ Tempos de Resposta

| Operação | Tempo Típico | Tempo Máximo |
|----------|--------------|--------------|
| **Processamento MQTT** | < 10ms | < 50ms |
| **Transição de Estado** | < 5ms | < 20ms |
| **Publicação MQTT** | < 100ms | < 500ms |
| **Reconexão** | < 5s | < 30s |
| **Recuperação Watchdog** | < 1s | < 5s |

### 📈 Estatísticas de Fluxo

| Métrica | Valor | Descrição |
|---------|-------|-----------|
| **Estados por Segundo** | 1 | Execução FSM |
| **Mensagens MQTT/s** | 10-50 | Depende da atividade |
| **Transições/s** | 0.1-1 | Baseado em eventos |
| **Recuperações/s** | < 0.01 | Raro |

---

<div align="center">

**🔄 Fluxogramas CoreHub** - Sistema de Automação Inteligente  
**Visualizando o fluxo de automação com iMCP HTNB32L**

</div> 