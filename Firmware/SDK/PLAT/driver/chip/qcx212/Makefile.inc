
CFLAGS_INC += -I$(TOP)/SDK/PLAT/driver/board/qcx212_0h00/inc       \
               -I$(TOP)/SDK/PLAT/driver/board/qcx212_0h00/chip/qcx212/inc       \
              -I$(TOP)/SDK/PLAT/driver/chip/qcx212/inc          \
              -I$(TOP)/SDK/PLAT/os/freertos/CMSIS/inc            \
              -I$(TOP)/SDK/PLAT/os/freertos/inc                  \
              -I$(TOP)/SDK/PLAT/os/osa/inc                        


ifeq ($(DRIVER_PMU_ENABLE),y)  
    CFLAGS      += -DPM_FEATURE_ENABLE
endif

ifeq ($(DRIVER_UNILOG_ENABLE),y)  
    CFLAGS      += -DUINILOG_FEATURE_ENABLE
endif

libdriver-$(DRIVER_ADC_ENABLE)           += PLAT/driver/chip/qcx212/src/adc_qcx212.o
libdriver-$(DRIVER_GPIO_ENABLE)          += PLAT/driver/chip/qcx212/src/gpio_qcx212.o          \
                                            PLAT/driver/chip/qcx212/src/HT_gpio_qcx212.o \
                                            PLAT/driver/chip/qcx212/src/pad_qcx212.o \
                                            PLAT/driver/chip/qcx212/src/HT_pad_qcx212.o

libdriver-$(DRIVER_TIMER_ENABLE)         += PLAT/driver/chip/qcx212/src/timer_qcx212.o
libdriver-$(DRIVER_WDG_ENABLE)           += PLAT/driver/chip/qcx212/src/wdt_qcx212.o
libdriver-y                              += PLAT/driver/chip/qcx212/src/clock_qcx212.o \
                                            PLAT/driver/chip/qcx212/src/HT_clock_qcx212.o


libdriverprivate-y                       += PLAT/driver/chip/qcx212/src/uart_qcx212.o
libdriverprivate-$(DRIVER_UNILOG_ENABLE) += PLAT/driver/chip/qcx212/src/unilog_qcx212.o
libdriverprivate-$(DRIVER_EFUSE_ENABLE)  += PLAT/driver/chip/qcx212/src/efuse_qcx212.o
libdriverprivate-$(DRIVER_CIPHER_ENABLE) += PLAT/driver/chip/qcx212/src/l2cflh_qcx212.o       \
                                            PLAT/driver/chip/qcx212/src/l2ctls_qcx212.o
libdriverprivate-$(DRIVER_RNG_ENABLE)    += PLAT/driver/chip/qcx212/src/rng_qcx212.o                                           
libdriverprivate-$(DRIVER_CACHE_ENABLE)  += PLAT/driver/chip/qcx212/src/cache_qcx212.o

libdriverprivate-$(DRIVER_FLASHRT_ENABLE)+= PLAT/driver/chip/qcx212/src/flash_qcx212_rt.o     \
                                            PLAT/driver/chip/qcx212/src/batmonos_qcx212.o
libdriverprivate-$(DRIVER_FLASH_ENABLE)  += PLAT/driver/chip/qcx212/src/qspi_qcx212.o           \
                                            PLAT/driver/chip/qcx212/src/flash_qcx212.o          \
                                            PLAT/driver/chip/qcx212/src/batmonraw_qcx212.o


libdriverprivate-$(DRIVER_IC_ENABLE)     += PLAT/driver/chip/qcx212/src/ic_qcx212.o
libdriverprivate-$(DRIVER_GPR_ENABLE)    += PLAT/driver/chip/qcx212/src/gpr_qcx212.o
libdriverprivate-$(DRIVER_DMA_ENABLE)    += PLAT/driver/chip/qcx212/src/dma_qcx212.o
libdriverprivate-$(DRIVER_PMU_ENABLE)       += PLAT/driver/chip/qcx212/src/ecpm_qcx212.o          \
                                            PLAT/driver/chip/qcx212/src/pmu_qcx212.o            \
                                            PLAT/driver/chip/qcx212/src/swcnt_qcx212.o          \
                                            PLAT/driver/chip/qcx212/src/ramboot_qcx212.o        \
                                           PLAT/driver/chip/qcx212/src/timetrans_qcx212.o      \
                                           PLAT/driver/chip/qcx212/src/hibtimer_qcx212.o       \
                                           PLAT/driver/chip/qcx212/src/slpman_qcx212.o



