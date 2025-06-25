CFLAGS_INC += -I$(TOP)/SDK/PLAT/driver/hal/common/inc \
              -I$(TOP)/SDK/PLAT/driver/hal/qcx212/inc \

DRIVER_HAL_ADC_ENABLE ?= n
DRIVER_HAL_UART_ENABLE ?= y

ifeq ($(DRIVER_EFUSE_ENABLE)_$(DRIVER_ADC_ENABLE),y_y)  
    DRIVER_HAL_ADC_ENABLE = y
endif

ifeq ($(DRIVER_HAL_ADC_ENABLE), y)
libdriver-y += PLAT/driver/hal/qcx212/src/hal_adc.o
endif

ifeq ($(TOOLCHAIN),GCC)
libdriver-y += PLAT/driver/hal/common/src/gcc/memcpy-armv7m.o
endif

libdriver-y += PLAT/driver/hal/qcx212/src/hal_misc.o 

ifeq ($(DRIVER_HAL_UART_ENABLE), y)
libdriver-y +=  PLAT/driver/hal/qcx212/src/hal_uart.o \
                PLAT/driver/hal/qcx212/src/HT_hal_uart.o
endif

libdriver-y += PLAT/driver/hal/common/src/ring_buffer.o \
               PLAT/driver/hal/common/src/os_exception.o
libdriverprivate-$(BUILD_OS) += PLAT/driver/hal/common/src/exception_dump.o
