
FREERTOS_DIR := $(TOP)/SDK/PLAT/os/freertos


CFLAGS_INC += -I$(TOP)/SDK/PLAT/os/freertos/inc          \
	            -I$(TOP)/SDK/PLAT/os/freertos/CMSIS/inc


FREERTOS_SRC_DIRS += $(FREERTOS_DIR)/src            \
                     $(FREERTOS_DIR)/CMSIS/src

ifeq ($(TOOLCHAIN),GCC)
FREERTOS_SRC_DIRS += $(FREERTOS_DIR)/portable/gcc
CFLAGS += -DconfigUSE_NEWLIB_REENTRANT=1
LDFLAGS += -Wl,--wrap=_malloc_r -Wl,--wrap=_free_r -Wl,--wrap=_realloc_r
endif

ifeq ($(QCHEAP_DEBUG_ENABLE),y)
CFLAGS += -DQC_HEAPDBG_ENABLE
endif

ifeq ($(RTOS_HEAP_5_ENABLE),y)
FREERTOS_EXCLUDE_FILES += $(FREERTOS_DIR)/src/heap_4.c
CFLAGS += -DHEAP_5_ENABLE
else
FREERTOS_EXCLUDE_FILES += $(FREERTOS_DIR)/src/heap_5.c
CFLAGS += -DHEAP_4_ENABLE
endif


FREERTOS_CSRC = $(foreach dir, $(FREERTOS_SRC_DIRS), $(wildcard $(dir)/*.c))
FREERTOS_CFILES = $(filter-out $(FREERTOS_EXCLUDE_FILES), $(FREERTOS_CSRC))
FREERTOS_COBJSTEMP := $(patsubst %.c, %.o, $(FREERTOS_CFILES))
FREERTOS_COBJSTEMP :=$(subst $(FREERTOS_DIR),PLAT/os/freertos,$(FREERTOS_COBJSTEMP))
FREERTOS_COBJS := $(addprefix $(BUILDDIR)/, $(FREERTOS_COBJSTEMP))


-include $(FREERTOS_COBJS:.o=.d)

ifeq ($(TOOLCHAIN),GCC)

CFLAGS_INC += -I $(TOP)/SDK/PLAT/os/freertos/portable/gcc


lib-y += libfreertos.a

$(BUILDDIR)/lib/libfreertos.a: $(FREERTOS_COBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) -cr $@ $^

endif
