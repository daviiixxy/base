ifeq ($(BUILD_USE_PREBUILD_LIB), n)
IPERFDIR        := $(TOP)/SDK/PROTOCOL/SRC/tcpip/iperf/iperf-1.7.0
else
IPERFDIR        := $(TOP)/SDK/PLAT/middleware/thirdparty/iperf
endif

CFLAGS_INC += -I $(IPERFDIR)

IPERF_SRC_DIRS += $(IPERFDIR)


IPERF_EXCLUDE_FILES :=                                   

IPERF_CSRC = $(foreach dir, $(IPERF_SRC_DIRS), $(wildcard $(dir)/*.c))
IPERF_CFILES = $(filter-out $(IPERF_EXCLUDE_FILES), $(IPERF_CSRC))
IPERF_COBJSTEMP := $(patsubst %.c, %.o, $(IPERF_CFILES))
ifeq ($(BUILD_USE_PREBUILD_LIB), n)
IPERF_COBJSTEMP :=$(subst $(IPERFDIR),PROTOCOL/SRC/tcpip/iperf/iperf-1.7.0,$(IPERF_COBJSTEMP))
else
IPERF_COBJSTEMP :=$(subst $(IPERFDIR),PLAT/middleware/thirdparty/iperf,$(IPERF_COBJSTEMP))
endif
IPERF_COBJS := $(addprefix $(BUILDDIR)/, $(IPERF_COBJSTEMP))


-include $(IPERF_COBJS:.o=.d)


ifeq ($(TOOLCHAIN),GCC)


lib-y += libiperf.a

$(BUILDDIR)/lib/libiperf.a: $(IPERF_COBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) -cr $@ $^

endif

ifeq ($(TOOLCHAIN),ARMCC)

lib-y += libiperf.lib

$(BUILDDIR)/lib/libiperf.lib: $(IPERF_COBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) $(ARFLAGS) $@ $^

endif
