# CoreHub - Sistema de Decisão e Automação

## 📋 Visão Geral

O **CoreHub** é um sistema de decisão inteligente que integra dispositivos IoT através de MQTT, implementado com FreeRTOS para gerenciar:

- **SmartDoor**: Controle de porta e alarme
- **SenseClima**: Monitoramento de temperatura e umidade  
- **AirControl**: Controle de ar condicionado

## 🏗️ Arquitetura

### Sistema de Tasks FreeRTOS

```
┌─────────────────────────────────────────────────────────────┐
│                    CoreHub - FreeRTOS Tasks                 │
├─────────────────────────────────────────────────────────────┤
│  🚀 MQTT Task (Prioridade Máxima)                          │
│     • Gerencia conexão MQTT                                 │
│     • Processa mensagens recebidas                         │
│     • Sinaliza outras tasks via semáforo                   │
├─────────────────────────────────────────────────────────────┤
│  🚪 SmartDoor Task (Alta Prioridade)                       │
│     • Sempre ativa quando MQTT conectado                   │
│     • Controla lógica de alarme e buzzer                   │
│     • Prioridade máxima para segurança                     │
├─────────────────────────────────────────────────────────────┤
│  🌡️ SenseClima Task (Média Prioridade)                    │
│     • Conecta a cada 30 segundos                           │
│     • Lê temperatura/umidade por 5 segundos                │
│     • Desconecta após leitura                              │
├─────────────────────────────────────────────────────────────┤
│  ❄️ AirControl Task (Baixa Prioridade)                     │
│     • Conecta apenas quando necessário                     │
│     • Controla AC baseado na temperatura                   │
│     • Desconecta após 10 segundos                          │
└─────────────────────────────────────────────────────────────┘
```

## 🔄 Fluxo de Funcionamento

### 1. Inicialização
```
main.c → HT_CoreHubTask → HT_CoreHubFsm() → Tasks FreeRTOS
```

### 2. Conexão MQTT
- **Task MQTT** conecta ao broker
- Libera semáforo para outras tasks
- Processa mensagens continuamente

### 3. SmartDoor (Sempre Ativo)
- **Prioridade máxima** para segurança
- Monitora porta e luz
- Controla alarme e buzzer
- Ativa controle de AC quando necessário

### 4. SenseClima (Ciclo de 30s)
```
Conectar → Ler dados (5s) → Desconectar → Aguardar (25s) → Repetir
```

### 5. AirControl (Sob Demanda)
```
Verificar necessidade → Conectar → Controlar AC → Desconectar (10s)
```

## 🎯 Lógica de Decisão

### Alarme e Buzzer
```
Luz ON + Porta ABERTA → Timer 60s → Buzzer ON
Porta FECHADA → Buzzer OFF (Prioridade Máxima)
```

### Controle de Temperatura
```
Temp > 28°C → AC ON (22°C)
Temp < 24°C → AC OFF
24°C ≤ Temp ≤ 28°C → AC mantém estado
```

### Conexão Inteligente
- **SmartDoor**: Sempre conectado
- **SenseClima**: Ciclo de 30 segundos
- **AirControl**: Apenas quando necessário

## 📡 Tópicos MQTT

### SmartDoor
- `hana/externo/smartdoor/door` (OPEN/CLOSED)
- `hana/externo/smartdoor/light` (ON/OFF)
- `hana/externo/smartdoor/buzzer` (ON/OFF)

### SenseClima
- `hana/externo/senseclima/01/temperature` (float)
- `hana/externo/senseclima/01/humidity` (float)

### AirControl
- `hana/externo/aircontrol/01/power` (ON/OFF)
- `hana/externo/aircontrol/01/temperature` (int)

## ⚙️ Configurações

### Limites de Temperatura
```c
#define HT_COREHUB_TEMP_LIMIT_UPPER    28.0f  // Ligar AC
#define HT_COREHUB_TEMP_LIMIT_LOWER    24.0f  // Desligar AC
#define HT_COREHUB_AC_TEMP_SETPOINT    22     // Setpoint do AC
```

### Timeouts
```c
#define HT_COREHUB_ALARM_TIMEOUT_MS    60000  // 60s para alarme
#define HT_COREHUB_SENSECLIMA_INTERVAL_MS  30000  // 30s ciclo
#define HT_COREHUB_AIRCONTROL_TIMEOUT_MS  10000   // 10s timeout
```

### Prioridades FreeRTOS
```c
#define HT_COREHUB_MQTT_TASK_PRIORITY      (configMAX_PRIORITIES - 1)
#define HT_COREHUB_SMARTDOOR_TASK_PRIORITY (configMAX_PRIORITIES - 2)
#define HT_COREHUB_SENSECLIMA_TASK_PRIORITY (configMAX_PRIORITIES - 3)
#define HT_COREHUB_AIRCONTROL_TASK_PRIORITY (configMAX_PRIORITIES - 4)
```

## 🔧 Sincronização

### Semáforos
- `xMqttConnectedSemaphore`: Controla execução das tasks
- `xMqttMutex`: Protege acesso ao cliente MQTT

### Estados
- Tasks de decisão só rodam quando MQTT conectado
- Reconexão automática em caso de falha
- Logs detalhados com emojis para clareza

## 📊 Logs e Monitoramento

### Exemplos de Logs
```
CoreHub - 🚀 Task MQTT iniciada (Prioridade Máxima)
CoreHub - 🔌 Conectado ao MQTT Broker!
CoreHub - 🚪 SmartDoor ativo - Processando porta/luz
CoreHub - 🌡️ Conectando ao SenseClima...
CoreHub - ❄️ Necessário controlar AC - Conectando...
CoreHub - 🚨 ALARME ATIVADO! Aguardando 60000 ms...
```

## ✅ Status Atual

O sistema está **adequado ao cenário** com:

- ✅ Arquitetura FreeRTOS implementada
- ✅ Conexão inteligente funcionando
- ✅ Lógica de alarme e buzzer corrigida
- ✅ Controle de temperatura implementado
- ✅ Sincronização entre tasks
- ✅ Logs detalhados
- ✅ Tratamento de erros robusto

## 🚀 Como Usar

1. Compile o projeto
2. Flash no dispositivo HTNB32L
3. Monitore os logs via UART (115200 baud)
4. O sistema inicia automaticamente após conexão NB-IoT

---

**Desenvolvido para o Laboratório 4.0 - Projeto Educacional** 