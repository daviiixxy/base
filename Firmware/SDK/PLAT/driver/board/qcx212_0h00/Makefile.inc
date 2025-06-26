CFLAGS_INC += -I$(TOP)/SDK/PLAT/driver/board/qcx212_0h00/inc

libdriver-y                                   += PLAT/driver/board/qcx212_0h00/src/bsp.o \
                                                PLAT/driver/board/qcx212_0h00/src/HT_bsp.o

libdriver-$(THIRDPARTY_LITTEFS_ENABLE)        +=    PLAT/driver/board/qcx212_0h00/src/plat_config.o \
                                                    PLAT/driver/board/qcx212_0h00/src/HT_plat_config.o
libdriverprivate-$(DRIVER_ECMAIN_ENABLE)   += PLAT/driver/board/qcx212_0h00/src/qc_main.o