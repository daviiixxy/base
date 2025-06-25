ifeq ($(BUILD_USE_PREBUILD_LIB), n)
PINGDIR        := $(TOP)/SDK/PROTOCOL/SRC/tcpip/ping/src
else
PINGDIR        := $(TOP)/SDK/PLAT/middleware/thirdparty/ping/src
endif

CFLAGS_INC += -I $(PINGDIR)

PING_SRC_DIRS += $(PINGDIR)


PING_EXCLUDE_FILES :=                                   

PING_CSRC = $(foreach dir, $(PING_SRC_DIRS), $(wildcard $(dir)/*.c))
PING_CFILES = $(filter-out $(PING_EXCLUDE_FILES), $(PING_CSRC))
PING_COBJSTEMP := $(patsubst %.c, %.o, $(PING_CFILES))
ifeq ($(BUILD_USE_PREBUILD_LIB), n)
PING_COBJSTEMP :=$(subst $(PINGDIR),PROTOCOL/SRC/tcpip/ping/src,$(PING_COBJSTEMP))
else
PING_COBJSTEMP :=$(subst $(PINGDIR),PLAT/middleware/thirdparty/ping/src,$(PING_COBJSTEMP))
endif
PING_COBJS := $(addprefix $(BUILDDIR)/, $(PING_COBJSTEMP))


-include $(PING_COBJS:.o=.d)


ifeq ($(TOOLCHAIN),GCC)


lib-y += libping.a

$(BUILDDIR)/lib/libping.a: $(PING_COBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) -cr $@ $^

endif

ifeq ($(TOOLCHAIN),ARMCC)

lib-y += libping.lib

$(BUILDDIR)/lib/libping.lib: $(PING_COBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) $(ARFLAGS) $@ $^

endif
