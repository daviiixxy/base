

CFLAGS_INC += -I $(TOP)/SDK/HT_API/Common/Inc \
                -I $(TOP)/SDK/HT_API/Driver_UART/Inc \
                -I $(TOP)/SDK/HT_API/Driver_SPI/Inc \
                -I $(TOP)/SDK/HT_API/Driver_I2C/Inc \
                -I$(TOP)/SDK/HT_API/Startup/Inc \
                -I$(TOP)/SDK/HT_API/Sleep_API/Inc

PRECINIT_FILE_PATH ?= SDK/HT_API/Startup/Src
SYSTEM_FILE_PATH   ?= SDK/HT_API/Startup/Src
STARTUP_FILE_PATH  ?= SDK/HT_API/Startup/Src
LINK_FILE_PATH     ?= SDK/HT_API/Startup/Src
SYSCALLS_FILE_PATH ?= SDK/HT_API/Startup/Src

ifeq ($(DRIVER_USART_ENABLE), y)
ht_app_api-y   += SDK/HT_API/Driver_UART/Src/htnb32lxxx_hal_usart.o
ifeq ($(UART_UNILOG_ENABLE), y)
ht_app_api-y   += SDK/HT_API/Driver_UART/Src/HT_usart_unilog.o
endif

endif

ifeq ($(DRIVER_SPI_ENABLE), y)
ht_app_api-y   += SDK/HT_API/Driver_SPI/Src/htnb32lxxx_hal_spi.o
endif

ifeq ($(DRIVER_I2C_ENABLE), y)
ht_app_api-y   += SDK/HT_API/Driver_I2C/Src/htnb32lxxx_hal_i2c.o
endif

ht_startup_lib-y += $(PRECINIT_FILE_PATH)/prec_init.o   \
                $(SYSCALLS_FILE_PATH)/syscalls.o    \
                $(SYSTEM_FILE_PATH)/system_qcx212.o \
                $(STARTUP_FILE_PATH)/startup_qcx212_gcc.o \
                $(STARTUP_FILE_PATH)/vector_qcx212.o

ifeq ($(HT_DEFAULT_LINKER_FILE), n)
linker-script-y := $(LINK_FILE_PATH)/qcx212_0h00_flash.ld
else
linker-script-y := ../../$(LINK_FILE_PATH)/qcx212_0h00_flash.ld
endif

