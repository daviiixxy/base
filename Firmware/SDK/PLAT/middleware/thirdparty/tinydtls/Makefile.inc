TINYDTLS_DIR   := $(TOP)/SDK/PLAT/middleware/thirdparty/tinydtls
CFLAGS_INC     += -I $(TINYDTLS_DIR) \
		              -I $(TINYDTLS_DIR)/include \
		              -I $(TINYDTLS_DIR)/aes \
		              -I $(TINYDTLS_DIR)/ecc\
		              -I $(TINYDTLS_DIR)/platform-specific \
		              -I $(TINYDTLS_DIR)/sha2


TINYDTLS_CFLAGS ?= -DDTLSv12 -DWITH_SHA256 -DNO_DECLTYPE -DWITH_TINYDTLS
CFLAGS += $(TINYDTLS_CFLAGS)

TINYDTLS_SRC_DIRS += $(TINYDTLS_DIR) \
                  $(TINYDTLS_DIR)/aes \
                  $(TINYDTLS_DIR)/ecc\
                  $(TINYDTLS_DIR)/platform-specific\
                  $(TINYDTLS_DIR)/sha2
TINYDTLS_EXCLUDE_FILES :=

TINYDTLS_CSRC = $(foreach dir, $(TINYDTLS_SRC_DIRS), $(wildcard $(dir)/*.c))
TINYDTLS_CFILES = $(filter-out $(TINYDTLS_EXCLUDE_FILES), $(TINYDTLS_CSRC))
TINYDTLS_COBJSTEMP := $(patsubst %.c, %.o, $(TINYDTLS_CFILES))
TINYDTLS_COBJSTEMP :=$(subst $(TINYDTLS_DIR),PLAT/middleware/thirdparty/tinydtls,$(TINYDTLS_COBJSTEMP))
TINYDTLS_COBJS := $(addprefix $(BUILDDIR)/, $(TINYDTLS_COBJSTEMP))


-include $(TINYDTLS_COBJS:.o=.d)


ifeq ($(TOOLCHAIN),GCC)

CFLAGS_INC += -I $(TOP)/SDK/PLAT/os/freertos/portable/gcc

lib-y += libtinydtls.a

$(BUILDDIR)/lib/libtinydtls.a: $(TINYDTLS_COBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) -cr $@ $^

endif