QCCOAP_DIR  := $(TOP)/SDK/PLAT/middleware/developed/iot/coap

CFLAGS_INC  +=  -I $(TOP)/SDK/PLAT/middleware/developed/iot/coap/inc
CFLAGS += -DLWM2M_CLIENT_MODE -DLWM2M_LITTLE_ENDIAN -DCOAP_STACK_SIZE=16384 -DCOAP_PRIORITY=50 -DDTLS_SUPPORT -DBLOCK1_SUPPORT -DENABLE_COMMON_ERR_LOG -DENABLE_COMMON_INFO_LOG

QCCOAP_SRC_DIRS += $(QCCOAP_DIR)/src
QCCOAP_EXCLUDE_FILES :=
QCCOAP_CSRC = $(foreach dir, $(QCCOAP_SRC_DIRS), $(wildcard $(dir)/*.c))
QCCOAP_CFILES = $(filter-out $(QCCOAP_EXCLUDE_FILES), $(QCCOAP_CSRC))
QCCOAP_COBJSTEMP := $(patsubst %.c, %.o, $(QCCOAP_CFILES))
QCCOAP_COBJSTEMP :=$(subst $(QCCOAP_DIR),PLAT/middleware/developed/iot/coap,$(QCCOAP_COBJSTEMP))
QCCOAP_COBJS := $(addprefix $(BUILDDIR)/, $(QCCOAP_COBJSTEMP))

-include $(QCCOAP_COBJS:.o=.d)

#$(ECHO) Objects QCCOAP_COBJS

ifeq ($(TOOLCHAIN),GCC)

lib-y += libqccoap.a

$(BUILDDIR)/lib/libqccoap.a: $(QCCOAP_COBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) -cr $@ $^

endif

ifeq ($(TOOLCHAIN),ARMCC)

lib-y += libqccoap.lib

$(BUILDDIR)/lib/libqccoap.lib: $(QCCOAP_COBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) $(ARFLAGS) $@ $^

endif

