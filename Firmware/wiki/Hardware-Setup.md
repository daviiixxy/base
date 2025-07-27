# 🔧 Hardware Setup e Simuladores

> **Sistema de Automação com iMCP HTNB32L**  
> **Configuração Física e Simuladores de Teste**

---

## 📋 Índice

1. [Circuito do CoreHub](#circuito-do-corehub)
2. [Componentes do Sistema](#componentes-do-sistema)
3. [Configuração Física](#configuração-física)
4. [Simuladores de Teste](#simuladores-de-teste)
5. [Logs de Operação](#logs-de-operação)
6. [Troubleshooting](#troubleshooting)

---

## 🔌 Circuito do CoreHub

### 📊 Visão Geral do Setup

O CoreHub utiliza um **KIT-HANA 07** como base de desenvolvimento, contendo:

```
┌─────────────────────────────────────────────────────────────┐
│                    KIT-HANA 07                              │
├─────────────────────────────────────────────────────────────┤
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐          │
│  │  Breadboard │  │   iMCP      │  │   USB-Serial│          │
│  │  (Prototip.)│  │   HTNB32L   │  │   Converter │          │
│  └─────────────┘  └─────────────┘  └─────────────┘          │
├─────────────────────────────────────────────────────────────┤
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐          │
│  │   Power     │  │   Antenna   │  │   SIM Card  │          │
│  │   Module    │  │   (NB-IoT)  │  │   (TIM)     │          │
│  └─────────────┘  └─────────────┘  └─────────────┘          │
└─────────────────────────────────────────────────────────────┘
```

### 🔧 Componentes Principais

#### **1. Base KIT-HANA 07**
- **Material**: Base preta texturizada (possivelmente 3D-printed)
- **Função**: Suporte integrado para todos os componentes
- **Identificação**: Label "KIT-HANA 07" no canto inferior esquerdo

#### **2. iMCP HTNB32L (Placa Principal)**
- **Localização**: Canto inferior direito da base
- **Chip Principal**: iMCP HTNB32L (chip metálico quadrado central)
- **Identificação**: Labels "HT MICRON" e "ASTRACORE"
- **SIM Card**: Sticker "TIM" indicando chip NB-IoT ativo
- **Antena**: Conector SMA dourado com cabo coaxial preto

#### **3. Breadboard (Prototipagem)**
- **Localização**: Seção superior da base
- **Componentes**:
  - **Botão BOOT**: Push-button cinza para modo de boot/programação
  - **Botão RESET**: Push-button cinza para reset do sistema
  - Componente preto multi-pino (resistor network/IC)
  - Fios jumper coloridos (vermelho, amarelo, marrom, laranja, preto)

#### **4. USB-to-Serial Converter**
- **Localização**: Canto inferior esquerdo
- **Cor**: PCB vermelho
- **Status**: LED vermelho aceso (indicando alimentação)
- **Função**: Comunicação serial para debug/programação

#### **5. Power Module**
- **Localização**: Canto superior esquerdo
- **Conexões**: 
  - Cabo de alimentação com conector barrel jack
  - Conexão para breadboard
- **Função**: Gerenciamento de energia

---

## 🔧 Componentes do Sistema

### 📡 Conectividade NB-IoT

#### **SIM Card TIM**
```bash
# Configuração da rede
Operadora: TIM
Tecnologia: NB-IoT
Banda: 28 (700MHz)
APN: iot.datatem.com.br
```

#### **Antena Celular**
- **Tipo**: Antena externa com conector SMA
- **Frequência**: Compatível com banda 28
- **Conexão**: Cabo coaxial preto
- **Posicionamento**: Extensão para fora do frame

### 🔌 Conexões Elétricas

#### **Esquemático do Circuito**

```
┌─────────────────────────────────────────────────────────────┐
│                    ESQUEMÁTICO COREHUB                      │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  +3.3V ────[10kΩ]─── GPIO1 ────[BOOT]─── GND                │
│                    │         │                              │
│                    │    [Capacitor]                         │
│                    │         │                              │
│  +3.3V ────[10kΩ]─── RST ────[RESET]─── GND                 │
│                    │         │                              │
│                    │    [Capacitor]                         │
│                    │         │                              │
│  HTNB32L-XXX       │         │                              │
│  ┌─────────────┐   │         │                              │
│  │ GPIO12 (TX) ├───┼─────────┼─── RX ── FTDI USB-Serial     │
│  │ GPIO13 (RX) ├───┼─────────┼─── TX ── FTDI USB-Serial     │
│  │ GPIO1       ├───┘         │                              │
│  │ RST         ├─────────────┘                              │
│  │ GND         ├───────────── GND ── FTDI USB-Serial        │
│  │ +3.3V       ├───────────── +3.3V                         │
│  └─────────────┘                                            │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

#### **Conexões Específicas (Baseado no Esquemático)**

| Componente | Pino HTNB32L | Pino Destino | Função | Observações |
|------------|--------------|--------------|--------|-------------|
| **Alimentação** | +3.3V | Power Module | Alimentação | Tensão de operação |
| **Terra** | GND | FTDI GND | Terra comum | Referência elétrica |
| **UART TX** | GPIO12 (TX) | FTDI RX | Transmissão | Comunicação serial |
| **UART RX** | GPIO13 (RX) | FTDI TX | Recepção | Comunicação serial |
| **Botão BOOT** | GPIO1 | GND (via botão) | Modo bootloader | Pull-up 10kΩ + capacitor |
| **Botão RESET** | RST | GND (via botão) | Reset hardware | Pull-up 10kΩ + capacitor |

#### **Conexões Diretas (iMCP)**
| Cor | Função | Observações |
|-----|--------|-------------|
| **Azul** | GPIO/Comunicação | Conectado diretamente ao iMCP |
| **Laranja** | GPIO/Comunicação | Conectado diretamente ao iMCP |

---

## ⚙️ Configuração Física

### 🔧 Setup Inicial

#### **1. Montagem da Base**
```bash
# Sequência de montagem
1. Posicionar base KIT-HANA 07
2. Instalar iMCP HTNB32L no slot dedicado
3. Conectar breadboard na seção superior
4. Instalar USB-to-Serial converter
5. Conectar power module
```

#### **2. Conexões de Energia**
```bash
# Alimentação do sistema
- Power Module → iMCP HTNB32L (+3.3V)
- Power Module → Breadboard (via cabo dedicado)
- USB-Serial → Alimentação via USB
- Terra comum → GND compartilhado
```

#### **3. Conexões de Comunicação Serial**
```bash
# UART (Comunicação serial)
- HTNB32L GPIO12 (TX) → FTDI RX
- HTNB32L GPIO13 (RX) → FTDI TX
- Configuração: 115200 baud, 8N1
- Terra comum entre HTNB32L e FTDI
```

#### **4. Conexões de Controle (Botões)**
```bash
# Circuito do Botão BOOT (GPIO1)
- +3.3V → Resistor 10kΩ → GPIO1
- GPIO1 → Botão BOOT → GND
- Capacitor de debouncing em paralelo

# Circuito do Botão RESET (RST)
- +3.3V → Resistor 10kΩ → RST
- RST → Botão RESET → GND
- Capacitor de debouncing em paralelo
```

#### **5. Especificações Técnicas**
```bash
# Configurações elétricas
- Tensão de operação: +3.3V
- Resistores pull-up: 10kΩ (BOOT e RESET)
- Capacitores: Debouncing para ambos os botões
- UART: GPIO12 (TX), GPIO13 (RX)
- Baud rate: 115200
- Configuração: 8N1 (8 bits, sem paridade, 1 stop bit)
```

### 📡 Configuração NB-IoT

#### **SIM Card**
```bash
# Inserção do chip
1. Localizar slot SIM no iMCP HTNB32L
2. Inserir chip TIM NB-IoT
3. Verificar fixação adequada
4. Confirmar presença do sticker TIM
```

#### **Antena**
```bash
# Instalação da antena
1. Conectar cabo coaxial ao conector SMA
2. Posicionar antena para melhor recepção
3. Verificar fixação do conector
4. Testar conectividade
```

---

## 🎮 Simuladores de Teste

### 📁 Estrutura do Projeto

```
Firmware/
├── Applications/
│   └── Core_Hub/                 # Aplicação principal do CoreHub
│       ├── Inc/                  # Headers
│       ├── Src/                  # Código fonte
│       └── Makefile              # Compilação
├── Publishers/
│   ├── SmartDoor/
│   │   ├── smartdoor_simulator.py    # Simulador de porta/luz
│   │   ├── requirements.txt          # Dependências Python
│   │   └── README.md                 # Documentação
│   ├── SenseClima/
│   │   ├── senseclima_simulator.py   # Simulador de sensores
│   │   ├── requirements.txt          # Dependências Python
│   │   └── README.md                 # Documentação
│   ├── AirControl/
│   │   ├── aircontrol_simulator.py   # Simulador de ar condicionado
│   │   ├── requirements.txt          # Dependências Python
│   │   └── README.md                 # Documentação
│   └── CoreHub/
│       └── .gitkeep                  # Pasta reservada
└── SDK/                          # SDK do iMCP HTNB32L
```

### 🤖 SmartDoor Simulator

#### **Características**
```python
# Configurações do simulador
BROKER_IP = "131.255.82.115"
BROKER_PORT = 1883
CLIENT_ID_PREFIX = "smartdoor_sim_real"

# Intervalos realistas
DOOR_INTERVAL_MIN = 120   # 2 minutos
DOOR_INTERVAL_MAX = 600   # 10 minutos
LIGHT_INTERVAL_MIN = 1800 # 30 minutos
LIGHT_INTERVAL_MAX = 5400 # 90 minutos
```

#### **Funcionalidades**
- **Simulação de Porta**: Estados OPEN/CLOSED com intervalos realistas
- **Simulação de Luz**: Estados ON/OFF com intervalos longos
- **Recepção de Comandos**: Responde a comandos de buzzer
- **Tópicos MQTT**:
  - `hana/{ambiente}/smartdoor/door`
  - `hana/{ambiente}/smartdoor/light`
  - `hana/{ambiente}/smartdoor/buzzer`

#### **Uso**
```bash
# Executar simulador
cd Publishers/SmartDoor
python smartdoor_simulator.py --ambiente externo

# Múltiplos ambientes
python smartdoor_simulator.py --ambiente mesanino
python smartdoor_simulator.py --ambiente prototipagem
```

### 🌡️ SenseClima Simulator

#### **Características**
```python
# Configurações avançadas
SIMULATION_SPEED_FACTOR = 3600  # 1 segundo real = 1 hora simulada
DEFAULT_INTERVAL = 10           # Publicação a cada 10 segundos

# Curva diária de temperatura
temp_points = [(0, 14), (8, 18), (12, 30), (18, 22), (24, 14)]
```

#### **Funcionalidades**
- **Simulação Dinâmica**: Temperatura e umidade baseadas na hora do dia
- **Curva Realista**: Variação diária de temperatura (14°C - 30°C)
- **Múltiplas Placas**: Suporte a múltiplos sensores por ambiente
- **Configuração Remota**: Intervalo configurável via MQTT
- **Tópicos MQTT**:
  - `hana/{ambiente}/senseclima/{id}/temperature`
  - `hana/{ambiente}/senseclima/{id}/humidity`
  - `hana/{ambiente}/senseclima/{id}/interval`

#### **Uso**
```bash
# Executar simulador
cd Publishers/SenseClima
python senseclima_simulator.py --ambiente externo --boards 01,02

# Configurar intervalo
mosquitto_pub -h 131.255.82.115 -t "hana/externo/senseclima/01/interval" -m "5"
```

### ❄️ AirControl Simulator

#### **Características**
```python
# Configurações do simulador
BROKER_IP = "131.255.82.115"
BROKER_PORT = 1883
CLIENT_ID_PREFIX = "aircontrol_sim"

# Estados dos equipamentos
ac_units_state = {
    '01': {'power': 'OFF', 'temp': 24},
    '02': {'power': 'OFF', 'temp': 24}
}
```

#### **Funcionalidades**
- **Controle de Power**: ON/OFF via MQTT
- **Controle de Temperatura**: Setpoint configurável
- **Múltiplos Equipamentos**: Suporte a vários ACs
- **Feedback de Estado**: Confirmação de comandos
- **Tópicos MQTT**:
  - `hana/{ambiente}/aircontrol/{id}/power`
  - `hana/{ambiente}/aircontrol/{id}/temperature`

#### **Uso**
```bash
# Executar simulador
cd Publishers/AirControl
python aircontrol_simulator.py --ambiente externo --equipamentos 01,02

# Comandos de teste
mosquitto_pub -h 131.255.82.115 -t "hana/externo/aircontrol/01/power" -m "ON"
mosquitto_pub -h 131.255.82.115 -t "hana/externo/aircontrol/01/temperature" -m "23"
```

---

## 📊 Logs de Operação

### 🔍 Análise dos Logs

#### **1. Inicialização do Sistema**
```
=== Sistema Pronto para Operação ===
HT MQTT Connect: Conectando ao broker MQTT...
HT MQTT Connect: Successfully connected to MQTT broker 131.255.82.115:1883
[CoreHub] Conectado ao MQTT Broker
```

#### **2. Inscrições MQTT**
```
[CoreHub] Inscrito em tópicos de 3 ambientes
- hana/externo/smartdoor/door
- hana/externo/smartdoor/light
- hana/externo/senseclima/01/temperature
- hana/externo/senseclima/01/humidity
- hana/mesanino/smartdoor/door
- hana/mesanino/smartdoor/light
- hana/mesanino/senseclima/01/temperature
- hana/mesanino/senseclima/01/humidity
- hana/prototipagem/smartdoor/door
- hana/prototipagem/smartdoor/light
- hana/prototipagem/senseclima/01/temperature
- hana/prototipagem/senseclima/01/humidity
```

#### **3. Saúde do Sistema**
```
[CoreHub] SAÚDE: Sistema operando normalmente (302 s uptime)
[CoreHub] SAÚDE: Sistema operando normalmente (604 s uptime)
[CoreHub] SAÚDE: Sistema operando normalmente (904 s uptime)
```

#### **4. Operação de Dispositivos**
```
[CoreHub] [mesanino] AC LIGADO (Porta fechada + Luz ligada)
```

### 📈 Interpretação dos Logs

#### **✅ Indicadores de Sucesso**
- **Conexão MQTT**: Estabelecida com sucesso
- **Inscrições**: Todos os tópicos inscritos
- **Uptime**: Sistema estável (302s, 604s, 904s)
- **Lógica**: AC ligado baseado em condições (porta fechada + luz ligada)

#### **🔍 Análise de Performance**
- **Tempo de Inicialização**: Rápido
- **Conectividade**: Estável
- **Processamento**: Funcionando corretamente
- **Lógica de Negócio**: Operacional

---

## 🚨 Troubleshooting

### ❌ Problemas Comuns

#### **🔴 Sem Conectividade NB-IoT**
```bash
# Verificar hardware
1. SIM Card TIM inserido corretamente
2. Antena conectada ao conector SMA
3. Sinal RSSI adequado
4. Cobertura NB-IoT disponível

# Comandos de teste
AT+CGATT?    # Verificar attach à rede
AT+CEREG?    # Verificar registro
AT+CSQ       # Verificar qualidade do sinal
```

#### **🔴 Falha na Comunicação Serial**
```bash
# Verificar conexões
1. USB-to-Serial converter conectado
2. LED vermelho aceso (indicando alimentação)
3. Driver USB instalado
4. Baud rate configurado (115200)

# Teste de comunicação
screen /dev/ttyUSB0 115200
# ou
minicom -D /dev/ttyUSB0 -b 115200
```

#### **🔴 Problemas com Botões BOOT/RESET**
```bash
# Verificar circuitos
1. Resistor 10kΩ pull-up em GPIO1 (BOOT)
2. Resistor 10kΩ pull-up em RST (RESET)
3. Capacitores de debouncing conectados
4. Conexões GND corretas

# Sequência de bootloader
1. Pressionar e segurar BOOT (GPIO1 → GND)
2. Pressionar RESET (RST → GND, mantendo BOOT)
3. Soltar RESET
4. Soltar BOOT
5. Sistema entra em modo de programação

# Verificação elétrica
- GPIO1: Deve estar em +3.3V (pull-up) quando não pressionado
- RST: Deve estar em +3.3V (pull-up) quando não pressionado
- Ambos devem ir para 0V quando pressionados
```

#### **🔴 Simuladores Não Conectam**
```bash
# Verificar rede
ping 131.255.82.115
telnet 131.255.82.115 1883

# Verificar dependências
pip install -r requirements.txt

# Verificar configuração
python -c "import paho.mqtt.client; print('MQTT OK')"
```

### 🔧 Soluções

#### **📡 Problemas de Rede**
```bash
# Reset do módulo NB-IoT
AT+CFUN=1,1    # Reset completo
AT+CGATT=1     # Reattach à rede
AT+CGPADDR     # Verificar IP
```

#### **🔌 Problemas de Hardware**
```bash
# Verificar alimentação
1. Medir tensão no power module
2. Verificar conexões dos fios jumper
3. Confirmar LED de status aceso
4. Testar USB-to-Serial converter
```

#### **🐛 Problemas de Software**
```bash
# Reset do sistema
1. Reiniciar iMCP HTNB32L
2. Verificar logs de inicialização
3. Confirmar configuração MQTT
4. Testar conectividade básica
```

---

## 📚 Referências

### 🔗 Links Úteis

- [iMCP HTNB32L Datasheet](https://github.com/htmicron/HTNB32L-XXX-SDK/tree/main)
- [MQTT Protocol](https://mqtt.org/specification)
- [NB-IoT Specification](https://www.3gpp.org/technologies/nb-iot)
- [TIM IoT](https://www.tim.com.br/empresas/iot)

### 📖 Documentação dos Simuladores

- [SmartDoor Simulator](Publishers/SmartDoor/README.md)
- [SenseClima Simulator](Publishers/SenseClima/README.md)
- [AirControl Simulator](Publishers/AirControl/README.md)

---

<div align="center">

**🔧 Hardware Setup CoreHub** - Sistema de Automação Inteligente  
**Configuração Física e Simuladores com iMCP HTNB32L**

</div> 