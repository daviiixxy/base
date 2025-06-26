ifeq ($(BUILD_USE_PREBUILD_LIB), n)
PSNV_DIR        := $(TOP)/SDK/PROTOCOL/SRC/ps/nv/src
CFLAGS_INC += -I $(TOP)/SDK/PROTOCOL/SRC/ps/nv/inc
else
PSNV_DIR        := $(TOP)/SDK/PLAT/middleware/Qualcomm/psnv/src
CFLAGS_INC += -I $(TOP)/SDK/PLAT/middleware/Qualcomm/psnv/inc
endif
              
CFLAGS += -I $(PSNV_DIR)

PSNV_SRC_DIRS += $(PSNV_DIR)
PSNV_EXCLUDE_FILES :=
PSNV_CSRC = $(foreach dir, $(PSNV_SRC_DIRS), $(wildcard $(dir)/*.c))
PSNV_CFILES = $(filter-out $(PSNV_EXCLUDE_FILES), $(PSNV_CSRC))
PSNV_COBJSTEMP := $(patsubst %.c, %.o, $(PSNV_CFILES))
ifeq ($(BUILD_USE_PREBUILD_LIB), n)
PSNV_COBJSTEMP :=$(subst $(PSNV_DIR),PROTOCOL/SRC/ps/nv/src,$(PSNV_COBJSTEMP))
else
PSNV_COBJSTEMP :=$(subst $(PSNV_DIR),PLAT/middleware/Qualcomm/psnv/src,$(PSNV_COBJSTEMP))
endif
PSNV_COBJS := $(addprefix $(BUILDDIR)/, $(PSNV_COBJSTEMP))


-include $(PSNV_COBJS:.o=.d)


ifeq ($(TOOLCHAIN),GCC)

CFLAGS_INC += -I $(TOP)/SDK/PLAT/os/freertos/portable/gcc

lib-y += libpsnv.a

$(BUILDDIR)/lib/libpsnv.a: $(PSNV_COBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) -cr $@ $^

endif
