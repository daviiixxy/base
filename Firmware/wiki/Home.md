# 🏠 CoreHub - Sistema de Automação Inteligente

> **Sistema de Automação com iMCP HTNB32L**  
> **Central de Decisão e Controle IoT via NB-IoT**

[![iMCP](https://img.shields.io/badge/iMCP-HTNB32L-blue.svg)](https://www.ht.com/imcp)
[![NB-IoT](https://img.shields.io/badge/NB--IoT-Conectividade%20Celular-green.svg)](https://www.3gpp.org/technologies/nb-iot)
[![MQTT](https://img.shields.io/badge/MQTT-Protocolo%20IoT-orange.svg)](https://mqtt.org/)
[![FreeRTOS](https://img.shields.io/badge/FreeRTOS-Sistema%20Tempo%20Real-red.svg)](https://www.freertos.org/)

---

## 🎯 Visão Geral

O **CoreHub** é um sistema central de automação inteligente baseado no **iMCP HTNB32L**, utilizando **NB-IoT** para comunicação celular de baixo consumo. O projeto demonstra a aplicação prática de conceitos de **IoT**, **sistemas embarcados** e **comunicação MQTT**, gerenciando múltiplos ambientes simultaneamente através de uma **Máquina de Estados Finita (FSM)** robusta.

### 🌟 Características Principais

- **🤖 Automação Inteligente**: Controle automático de ar condicionado, alarmes e iluminação
- **📡 Comunicação NB-IoT**: Conectividade celular otimizada para IoT
- **🏢 Multi-Ambiente**: Suporte simultâneo a múltiplos ambientes
- **🛡️ Sistema Robusto**: Watchdog e proteções contra travamentos
- **⚡ Performance Otimizada**: Execução eficiente em sistemas embarcados
- **📊 Monitoramento**: Logs essenciais e status de saúde

---

## 🏗️ Arquitetura do Sistema

```
┌─────────────────────────────────────────────────────────────┐
│                    CoreHub - Sistema IoT                    │
├─────────────────────────────────────────────────────────────┤
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐          │
│  │   Externo   │  │  Mesanino   │  │Prototipagem │          │
│  │  Ambiente   │  │  Ambiente   │  │  Ambiente   │          │
│  └─────────────┘  └─────────────┘  └─────────────┘          │
├─────────────────────────────────────────────────────────────┤
│                    FSM - Máquina de Estados                 │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐          │
│  │   Estado    │  │   Estado    │  │   Estado    │          │
│  │   IDLE      │  │   ALARM     │  │   AC_CTRL   │          │
│  └─────────────┘  └─────────────┘  └─────────────┘          │
├─────────────────────────────────────────────────────────────┤
│                    MQTT - Comunicação                       │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐          │
│  │ SmartDoor   │  │ SenseClima  │  │ AirControl  │          │
│  │ (Porta/Luz) │  │ (Temp/Umid) │  │ (Ar Cond.)  │          │
│  └─────────────┘  └─────────────┘  └─────────────┘          │
├─────────────────────────────────────────────────────────────┤
│                    NB-IoT - Rede Celular                    │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐          │
│  │   Banda 28  │  │ APN IoT     │  │ PSM Mode    │          │
│  │   LTE Cat   │  │ Datatem     │  │ Power Save  │          │
│  └─────────────┘  └─────────────┘  └─────────────┘          │
└─────────────────────────────────────────────────────────────┘
```

---

## 🚀 Início Rápido

### 📋 Pré-requisitos

- **iMCP**: HTNB32L com módulo NB-IoT integrado (plataforma de estudo)
- **SIM Card**: Chip NB-IoT ativo
- **Rede**: Cobertura celular na banda 28
- **MQTT Broker**: Servidor MQTT configurado

### ⚙️ Configuração

```bash
# Clone o repositório
git clone https://github.com/seu-usuario/corehub.git
cd corehub/firmware

# Compile o projeto
make -j4 gccall TARGET=qcx212_0h00 V=0 PROJECT=Core_Hub

# Flash no dispositivo
# (Instruções específicas do hardware)
```

### 🔧 Configuração MQTT

```c
// Configurações no CoreHub_Config.h
#define HT_COREHUB_MQTT_BROKER "131.255.82.115"
#define HT_COREHUB_MQTT_PORT 1883
#define HT_COREHUB_MQTT_CLIENT_ID "corehub01"
```

---

## 📚 Documentação

### 📖 Guias Principais

- **[🏗️ Arquitetura](Architecture.md)** - Visão geral da arquitetura do sistema
- **[🔄 Fluxogramas](Flowcharts.md)** - Diagramas de fluxo e estados
- **[⚙️ Configuração](Configuration.md)** - Guia de configuração detalhado
- **[🔧 API](API.md)** - Documentação da API e funções
- **[🐛 Troubleshooting](Troubleshooting.md)** - Solução de problemas

### 📋 Especificações

- **[📊 Especificações Técnicas](Specifications.md)** - Requisitos e especificações
- **[📈 Performance](Performance.md)** - Métricas e otimizações
- **[🔒 Segurança](Security.md)** - Considerações de segurança

### 💻 Desenvolvimento

- **[👨‍💻 Guia do Desenvolvedor](Developer-Guide.md)** - Como contribuir
- **[🧪 Testes](Testing.md)** - Estratégias de teste
- **[📝 Logs](Logging.md)** - Sistema de logs e debug

---

## 🎯 Casos de Uso

### 🏠 Automação Residencial
- **Controle de Temperatura**: AC automático baseado em sensores
- **Segurança**: Alarme inteligente com timer
- **Eficiência Energética**: Desligamento automático quando ambiente vazio

### 🏢 Automação Comercial
- **Multi-Ambiente**: Controle simultâneo de múltiplas salas
- **Monitoramento**: Status em tempo real via MQTT
- **Escalabilidade**: Fácil adição de novos ambientes

### 🏭 IoT Industrial
- **Conectividade Robusta**: NB-IoT para ambientes industriais
- **Sistema Confiável**: Watchdog e recuperação automática
- **Baixo Consumo**: Otimizado para operação contínua

---

## 🔧 Tecnologias Utilizadas

| Tecnologia | Versão | Propósito |
|------------|--------|-----------|
| **FreeRTOS** | 10.x | Sistema operacional em tempo real |
| **MQTT** | 3.1.1 | Protocolo de comunicação IoT |
| **NB-IoT** | LTE Cat-NB1 | Conectividade celular |
| **C** | C99 | Linguagem de programação |
| **GCC** | 9.x | Compilador |

---

## 📊 Status do Projeto

- ✅ **CoreHub FSM**: Implementado e testado
- ✅ **MQTT Integration**: Funcionando
- ✅ **NB-IoT Connectivity**: Operacional
- ✅ **Multi-Ambiente**: Suporte completo
- ✅ **Watchdog System**: Proteções ativas

- 🔄 **Documentation**: Em constante melhoria
- 🔄 **Testing**: Testes automatizados em desenvolvimento

---

## 🤝 Contribuição

Contribuições são bem-vindas! Por favor, leia nosso [Guia de Contribuição](Contributing.md) antes de submeter pull requests.

### 📝 Como Contribuir

1. **Fork** o projeto
2. **Crie** uma branch para sua feature (`git checkout -b feature/AmazingFeature`)
3. **Commit** suas mudanças (`git commit -m 'Add some AmazingFeature'`)
4. **Push** para a branch (`git push origin feature/AmazingFeature`)
5. **Abra** um Pull Request

---

## 📄 Licença

Este projeto está licenciado sob a Licença MIT - veja o arquivo [LICENSE](LICENSE) para detalhes.

---

## 📞 Suporte

- **📧 Email**: suporte@corehub.com
- **💬 Issues**: [GitHub Issues](https://github.com/seu-usuario/corehub/issues)
- **📖 Wiki**: Esta documentação
- **🔧 Discord**: [Servidor da Comunidade](https://discord.gg/corehub)

---

## 🙏 Agradecimentos

- **HTNB32L Team** - Hardware e SDK
- **FreeRTOS Community** - Sistema operacional
- **MQTT Community** - Protocolo de comunicação

- **Contribuidores** - Todos que ajudaram no projeto

---

<div align="center">

**CoreHub** - Sistema de Automação Inteligente  
**Plataforma iMCP HTNB32L com NB-IoT**

[![GitHub stars](https://img.shields.io/github/stars/seu-usuario/corehub?style=social)](https://github.com/seu-usuario/corehub)
[![GitHub forks](https://img.shields.io/github/forks/seu-usuario/corehub?style=social)](https://github.com/seu-usuario/corehub)
[![GitHub issues](https://img.shields.io/github/issues/seu-usuario/corehub)](https://github.com/seu-usuario/corehub/issues)

</div> 