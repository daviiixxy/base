
ifeq ($(HT_LIBRARY_MQTT_ENABLE),y)

MQTT_DIR      := $(TOP)/SDK/Thirdparty/MQTT

CFLAGS_INC    += -I $(TOP)/SDK/PLAT/os/freertos/inc \
                  -I $(TOP)/SDK/PLAT/os/freertos/CMSIS/inc \
                  -I $(TOP)/SDK/PLAT/middleware/thirdparty/cjson \
                  -I $(MQTT_DIR)/MQTTPacket/Inc \
                  -I $(MQTT_DIR)/FreeRTOS/Inc \
                  -I $(MQTT_DIR)/MQTTClient/Inc \
                  -I $(TOP)/SDK/PLAT/os/freertos/portable/gcc

CFLAGS += -DFEATURE_MQTT_ENABLE

ht_thirdparty_api-y += SDK/Thirdparty/MQTT/MQTTPacket/Src/MQTTConnectClient.o \
						SDK/Thirdparty/MQTT/MQTTPacket/Src/MQTTDeserializePublish.o \
						SDK/Thirdparty/MQTT/MQTTPacket/Src/MQTTPacket.o \
						SDK/Thirdparty/MQTT/MQTTPacket/Src/MQTTSubscribeClient.o \
						SDK/Thirdparty/MQTT/MQTTPacket/Src/MQTTUnsubscribeClient.o \
						SDK/Thirdparty/MQTT/MQTTPacket/Src/MQTTConnectServer.o \
						SDK/Thirdparty/MQTT/MQTTPacket/Src/MQTTFormat.o \
						SDK/Thirdparty/MQTT/MQTTPacket/Src/MQTTSerializePublish.o \
						SDK/Thirdparty/MQTT/MQTTPacket/Src/MQTTSubscribeServer.o \
						SDK/Thirdparty/MQTT/MQTTPacket/Src/MQTTUnsubscribeServer.o \
						SDK/Thirdparty/MQTT/FreeRTOS/Src/MQTTFreeRTOS.o \
						SDK/Thirdparty/MQTT/MQTTClient/Src/HT_MQTT_Tls.o \
						SDK/Thirdparty/MQTT/MQTTClient/Src/MQTTClient.o

endif