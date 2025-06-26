ifeq ($(BUILD_USE_PREBUILD_LIB), n)
SNTP_DIR        := $(TOP)/SDK/PROTOCOL/SRC/tcpip/sntp
else
SNTP_DIR        := $(TOP)/SDK/PLAT/middleware/thirdparty/sntp
endif
              
CFLAGS += -I $(SNTP_DIR)

SNTP_SRC_DIRS += $(SNTP_DIR)
SNTP_EXCLUDE_FILES :=
SNTP_CSRC = $(foreach dir, $(SNTP_SRC_DIRS), $(wildcard $(dir)/*.c))
SNTP_CFILES = $(filter-out $(SNTP_EXCLUDE_FILES), $(SNTP_CSRC))
SNTP_COBJSTEMP := $(patsubst %.c, %.o, $(SNTP_CFILES))
ifeq ($(BUILD_USE_PREBUILD_LIB), n)
SNTP_COBJSTEMP :=$(subst $(SNTP_DIR),PROTOCOL/SRC/tcpip/sntp,$(SNTP_COBJSTEMP))
else
SNTP_COBJSTEMP :=$(subst $(SNTP_DIR),PLAT/middleware/thirdparty/sntp,$(SNTP_COBJSTEMP))
endif
SNTP_COBJS := $(addprefix $(BUILDDIR)/, $(SNTP_COBJSTEMP))


-include $(SNTP_COBJS:.o=.d)


ifeq ($(TOOLCHAIN),GCC)

CFLAGS_INC += -I $(TOP)/SDK/PLAT/os/freertos/portable/gcc

lib-y += libsntp.a

$(BUILDDIR)/lib/libsntp.a: $(SNTP_COBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) -cr $@ $^

endif
