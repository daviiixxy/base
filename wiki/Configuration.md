# ⚙️ Configuração do CoreHub

> **Sistema de Automação com iMCP HTNB32L**  
> **Guia Completo de Configuração e Setup do Sistema**

---

## 📋 Índice

1. [Pré-requisitos](#pré-requisitos)
2. [Configuração de Hardware](#configuração-de-hardware)
3. [Configuração de Rede](#configuração-de-rede)
4. [Configuração MQTT](#configuração-mqtt)
5. [Configuração de Ambientes](#configuração-de-ambientes)
6. [Configuração de Parâmetros](#configuração-de-parâmetros)
7. [Configuração de Logs](#configuração-de-logs)
8. [Verificação de Configuração](#verificação-de-configuração)

---

## 📋 Pré-requisitos

### 🔧 Hardware Necessário

- **iMCP**: HTNB32L com módulo NB-IoT integrado
- **SIM Card**: Chip NB-IoT ativo (recomendado: Datatem IoT)
- **Antena**: Antena celular compatível com banda 28
- **Fonte**: Alimentação 3.3V/5V estável
- **Interface**: UART para debug e configuração

### 📡 Conectividade

- **Rede**: Cobertura NB-IoT na banda 28
- **APN**: `iot.datatem.com.br` (ou conforme operadora)
- **Sinal**: RSSI mínimo -85 dBm
- **Latência**: < 100ms para operação ideal

### 🖥️ Software

- **Compilador**: GCC ARM 9.x ou superior
- **SDK**: HTNB32L SDK com suporte NB-IoT
- **FreeRTOS**: Versão 10.x
- **MQTT**: Biblioteca MQTT compatível

---

## 🔧 Configuração de Hardware

### 📍 Pinout do iMCP HTNB32L

```c
// Configuração de pinos principais
#define UART_TX_PIN      GPIO_PIN_9   // UART1 TX
#define UART_RX_PIN      GPIO_PIN_10  // UART1 RX
#define LED_STATUS_PIN   GPIO_PIN_13  // LED de status
#define RESET_PIN        GPIO_PIN_14  // Reset do módulo NB-IoT
#define POWER_PIN        GPIO_PIN_15  // Controle de power
```

### ⚡ Configuração de Power

```c
// Configurações de alimentação
#define VCC_3V3          3.3f         // Tensão de operação
#define CURRENT_MAX      500          // Corrente máxima (mA)
#define POWER_MODE       PSM_ENABLED  // Power Saving Mode
```

### 🔌 Conexões Físicas

| Componente | Pino iMCP HTNB32L | Função | Observações |
|------------|------------------|--------|-------------|
| **SIM Card** | SIM_SLOT | Interface SIM | Inserir chip NB-IoT |
| **Antena** | RF_ANT | Antena celular | Banda 28 (700MHz) |
| **UART Debug** | UART1_TX/RX | Comunicação serial | 115200 baud |
| **LED Status** | GPIO_13 | Indicador visual | Status do sistema |
| **Reset** | GPIO_14 | Reset manual | Reset do módulo |

---

## 📡 Configuração de Rede

### 🌐 Configuração NB-IoT

```c
// Configurações de rede NB-IoT
static void HT_SetConnectioParameters(void) {
    uint8_t cid = 0;
    PsAPNSetting apnSetting;
    int32_t ret;
    
    // Configuração de banda
    uint8_t networkMode = 0;  // NB-IoT mode
    uint8_t bandNum = 1;      // Band number
    uint8_t band = 28;        // Band frequency (700MHz)
    
    ret = appSetBandModeSync(networkMode, bandNum, &band);
    if(ret == CMS_RET_SUCC) {
        printf("SetBand Result: %d\n", ret);
    }
    
    // Configuração APN
    apnSetting.cid = 0;
    apnSetting.apnLength = strlen("iot.datatem.com.br");
    strcpy((char *)apnSetting.apnStr, "iot.datatem.com.br");
    apnSetting.pdnType = CMI_PS_PDN_TYPE_IP_V4V6;
    ret = appSetAPNSettingSync(&apnSetting, &cid);
}
```

### 🔋 Configuração Power Saving

```c
// Configurações PSM (Power Saving Mode)
uint8_t psmMode = 1;           // PSM habilitado
uint16_t tauTime = 4000;       // TAU: 4 segundos
uint16_t activeTime = 30;      // Active Time: 30 segundos

appGetPSMSettingSync(&psmMode, &tauTime, &activeTime);
printf("PSM: mode=%d, TAU=%d, ActiveTime=%d\n", psmMode, tauTime, activeTime);
```

### 📊 Monitoramento de Rede

```c
// Callback para eventos de rede
static INT32 registerPSUrcCallback(urcID_t eventID, void *param, uint32_t paramLen) {
    switch(eventID) {
        case NB_URC_ID_SIM_READY:
            printf("SIM Ready - IMSI: %s\n", gImsi);
            simReady = 1;
            break;
            
        case NB_URC_ID_MM_SIGQ:
            uint8_t rssi = *(UINT8 *)param;
            printf("RSSI signal: %d dBm\n", rssi);
            break;
            
        case NB_URC_ID_PS_NETINFO:
            NmAtiNetifInfo *netif = (NmAtiNetifInfo *)param;
            if (netif->netStatus == NM_NETIF_ACTIVATED) {
                printf("Network activated - IP ready\n");
                sendQueueMsg(QMSG_ID_NW_IPV4_READY, 0);
            }
            break;
    }
    return 0;
}
```

---

## 📡 Configuração MQTT

### 🔧 Configurações do Broker

```c
// Configurações MQTT no CoreHub_Config.h
#define HT_COREHUB_MQTT_BROKER     "131.255.82.115"
#define HT_COREHUB_MQTT_PORT       1883
#define HT_COREHUB_MQTT_CLIENT_ID  "corehub01"
#define HT_COREHUB_MQTT_USERNAME   ""
#define HT_COREHUB_MQTT_PASSWORD   ""
#define HT_COREHUB_MQTT_VERSION    MQTT_VERSION_3_1_1
#define HT_COREHUB_MQTT_KEEP_ALIVE 60
```

### 📨 Configuração de Tópicos

```c
// Estrutura de tópicos por ambiente
static void CoreHub_MontaTopicos(int ambiente_idx, const char* ambiente) {
    snprintf(topic_smartdoor_door[ambiente_idx], 64, "hana/%s/smartdoor/door", ambiente);
    snprintf(topic_smartdoor_light[ambiente_idx], 64, "hana/%s/smartdoor/light", ambiente);
    snprintf(topic_smartdoor_buzzer[ambiente_idx], 64, "hana/%s/smartdoor/buzzer", ambiente);
    snprintf(topic_senseclima_temp[ambiente_idx], 64, "hana/%s/senseclima/01/temperature", ambiente);
    snprintf(topic_senseclima_humidity[ambiente_idx], 64, "hana/%s/senseclima/01/humidity", ambiente);
    snprintf(topic_aircontrol_power[ambiente_idx], 64, "hana/%s/aircontrol/01/power", ambiente);
    snprintf(topic_aircontrol_temp[ambiente_idx], 64, "hana/%s/aircontrol/01/temperature", ambiente);
}
```

### 🔄 Configuração de Retry

```c
// Configurações de retry MQTT
#define MQTT_MAX_RETRIES          3
#define MQTT_RETRY_DELAY_MS       200
#define MQTT_MAX_RETRY_DELAY_MS   500
#define MQTT_SEND_TIMEOUT_MS      5000
#define MQTT_RECEIVE_TIMEOUT_MS   5000
```

---

## 🏢 Configuração de Ambientes

### 📝 Definição de Ambientes

```c
// Array de ambientes suportados
const char* ambientes[NUM_AMBIENTES] = {
    "externo",      // Ambiente externo
    "mesanino",     // Ambiente mesanino
    "prototipagem"  // Ambiente de prototipagem
};

// Inicialização de ambientes
void HT_CoreHub_InitAmbiente(int ambiente_idx, const char* nome) {
    memset(&corehub_data[ambiente_idx], 0, sizeof(CoreHub_Data_t));
    current_state[ambiente_idx] = COREHUB_INIT_STATE;
    CoreHub_MontaTopicos(ambiente_idx, nome);
}
```

### 🔧 Configuração por Ambiente

```c
// Configurações específicas por ambiente
typedef struct {
    float temp_limit_upper;     // Limite superior de temperatura
    float temp_limit_lower;     // Limite inferior de temperatura
    int ac_temp_setpoint;       // Setpoint do ar condicionado
    uint32_t alarm_timeout_ms;  // Timeout do alarme
    uint8_t enabled;            // Ambiente habilitado
} Ambiente_Config_t;

// Configurações padrão
Ambiente_Config_t ambiente_config[NUM_AMBIENTES] = {
    {25.0f, 22.0f, 23, 60000, 1},  // externo
    {24.0f, 21.0f, 22, 60000, 1},  // mesanino
    {26.0f, 23.0f, 24, 60000, 1}   // prototipagem
};
```

---

## ⚙️ Configuração de Parâmetros

### 🌡️ Parâmetros de Temperatura

```c
// Configurações de temperatura
#define HT_COREHUB_TEMP_LIMIT_UPPER    25.0f   // Limite superior (°C)
#define HT_COREHUB_TEMP_LIMIT_LOWER    22.0f   // Limite inferior (°C)
#define HT_COREHUB_AC_TEMP_SETPOINT    23      // Setpoint do AC (°C)
#define HT_COREHUB_TEMP_HYSTERESIS     0.5f    // Histerese (°C)
```

### ⏰ Parâmetros de Timer

```c
// Configurações de timer
#define HT_COREHUB_ALARM_TIMEOUT_MS    60000   // Timeout do alarme (60s)
#define HT_COREHUB_BUZZER_MAX_TIME_MS  30000   // Tempo máximo do buzzer (30s)
#define HT_COREHUB_FSM_EXEC_INTERVAL_MS 1000   // Intervalo execução FSM (1s)
#define HT_COREHUB_WATCHDOG_INTERVAL_MS 30000  // Intervalo watchdog (30s)
```

### 🔄 Parâmetros de Performance

```c
// Configurações de performance
#define HT_COREHUB_MQTT_BUFFER_SIZE    1024    // Tamanho buffer MQTT
#define HT_COREHUB_MAX_TOPIC_LENGTH    64      // Tamanho máximo tópico
#define HT_COREHUB_MAX_PAYLOAD_LENGTH  128     // Tamanho máximo payload
#define HT_COREHUB_MAX_RETRIES         3       // Máximo de tentativas
```

---

## 📝 Configuração de Logs

### 🔧 Níveis de Log

```c
// Definição de níveis de log
typedef enum {
    LOG_LEVEL_ERROR = 0,    // Apenas erros críticos
    LOG_LEVEL_WARN = 1,     // Avisos e erros
    LOG_LEVEL_INFO = 2,     // Informações gerais
    LOG_LEVEL_DEBUG = 3,    // Debug detalhado
    LOG_LEVEL_TRACE = 4     // Trace completo
} LogLevel_t;

// Configuração do nível de log
#define COREHUB_LOG_LEVEL LOG_LEVEL_INFO
```

### 📊 Formato de Logs

```c
// Macros para logs
#define LOG_ERROR(fmt, ...) \
    if (COREHUB_LOG_LEVEL >= LOG_LEVEL_ERROR) \
        printf("[ERROR][%s] " fmt "\n", ambientes[ambiente_idx], ##__VA_ARGS__)

#define LOG_INFO(fmt, ...) \
    if (COREHUB_LOG_LEVEL >= LOG_LEVEL_INFO) \
        printf("[INFO][%s] " fmt "\n", ambientes[ambiente_idx], ##__VA_ARGS__)

#define LOG_DEBUG(fmt, ...) \
    if (COREHUB_LOG_LEVEL >= LOG_LEVEL_DEBUG) \
        printf("[DEBUG][%s] " fmt "\n", ambientes[ambiente_idx], ##__VA_ARGS__)
```

### 📈 Logs de Performance

```c
// Configuração de logs de performance
#define PERFORMANCE_LOG_INTERVAL_MS    300000  // 5 minutos
#define HEALTH_LOG_INTERVAL_MS         300000  // 5 minutos
#define WATCHDOG_LOG_INTERVAL_MS       30000   // 30 segundos

// Exemplo de log de saúde
printf("[CoreHub] SAÚDE: Sistema operando normalmente (%lu s uptime)\n", 
       CoreHub_GetTimeSecs());
```

---

## ✅ Verificação de Configuração

### 🔍 Checklist de Configuração

#### ✅ Hardware
- [ ] iMCP HTNB32L conectado corretamente
- [ ] SIM Card NB-IoT inserido
- [ ] Antena conectada
- [ ] Alimentação estável
- [ ] UART configurado (115200 baud)

#### ✅ Rede
- [ ] SIM Card ativo
- [ ] Cobertura NB-IoT disponível
- [ ] APN configurado corretamente
- [ ] Sinal RSSI > -85 dBm
- [ ] IP obtido com sucesso

#### ✅ MQTT
- [ ] Broker MQTT acessível
- [ ] Credenciais configuradas
- [ ] Tópicos criados
- [ ] Conexão estabelecida
- [ ] Mensagens sendo trocadas

#### ✅ Sistema
- [ ] FreeRTOS iniciado
- [ ] Tasks criadas
- [ ] FSM funcionando
- [ ] Watchdog ativo
- [ ] Logs aparecendo

### 🧪 Testes de Configuração

#### 📡 Teste de Conectividade

```bash
# Verificar conectividade NB-IoT
AT+CGATT?          # Verificar attach à rede
AT+CEREG?          # Verificar registro
AT+CSQ             # Verificar qualidade do sinal
AT+CGPADDR         # Verificar IP obtido
```

#### 📨 Teste MQTT

```bash
# Testar conexão MQTT
mosquitto_pub -h 131.255.82.115 -t "hana/externo/test" -m "teste"
mosquitto_sub -h 131.255.82.115 -t "hana/externo/test"
```

#### 🔧 Teste do Sistema

```c
// Teste de funcionalidade básica
void test_basic_functionality(void) {
    // Teste de temperatura
    printf("Testando controle de temperatura...\n");
    
    // Simular temperatura alta
    buffered_temp[0] = 26.0f;
    new_temp_data[0] = 1;
    
    // Executar FSM
    HT_CoreHub_StateMachine(0);
    
    // Verificar se AC foi ligado
    if (corehub_data[0].ac_state == 1) {
        printf("✅ Teste de temperatura: OK\n");
    } else {
        printf("❌ Teste de temperatura: FALHOU\n");
    }
}
```

---

## 🚨 Troubleshooting

### ❌ Problemas Comuns

#### 🔴 Sem Conectividade NB-IoT
```bash
# Verificar SIM Card
AT+CPIN?           # Verificar PIN
AT+CREG?           # Verificar registro
AT+CSQ             # Verificar sinal

# Soluções:
# 1. Verificar se SIM está ativo
# 2. Verificar cobertura da rede
# 3. Verificar configuração APN
# 4. Verificar antena
```

#### 🔴 Falha na Conexão MQTT
```bash
# Verificar conectividade
ping 131.255.82.115
telnet 131.255.82.115 1883

# Soluções:
# 1. Verificar IP obtido
# 2. Verificar firewall
# 3. Verificar credenciais MQTT
# 4. Verificar tópicos
```

#### 🔴 FSM Travada
```c
// Verificar logs de watchdog
[CoreHub] WATCHDOG: FSM externo detectada como travada

// Soluções:
// 1. Verificar lógica de estados
// 2. Verificar proteções de performance
// 3. Verificar uso de memória
// 4. Reset manual se necessário
```

---

## 📚 Referências

### 📖 Documentação Técnica

- [iMCP HTNB32L Datasheet](https://www.ht.com/datasheet/htnb32l)
- [NB-IoT Specification](https://www.3gpp.org/technologies/nb-iot)
- [MQTT Protocol](https://mqtt.org/specification)
- [FreeRTOS Documentation](https://www.freertos.org/Documentation)

### 🔗 Links Úteis

- [CoreHub GitHub](https://github.com/seu-usuario/corehub)
- [Issues](https://github.com/seu-usuario/corehub/issues)
- [Wiki](https://github.com/seu-usuario/corehub/wiki)
- [Discord](https://discord.gg/corehub)

---

<div align="center">

**⚙️ Configuração CoreHub** - Sistema de Automação Inteligente  
**Configure seu sistema com iMCP HTNB32L**

</div> 