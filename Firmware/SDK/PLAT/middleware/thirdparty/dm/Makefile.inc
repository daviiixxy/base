DM_DIR        := $(TOP)/SDK/PLAT/middleware/thirdparty/dm

CFLAGS_INC     +=  -I $(TOP)/SDK/PLAT/middleware/thirdparty/dm \
                   -I $(TOP)/SDK/PLAT/middleware/thirdparty/dm/include
              

DM_SRC_DIRS += $(DM_DIR)\common \
               $(DM_DIR)

ifeq ($(THIRDPARTY_CMCC_DM_ENABLE),y)
DM_CSRC += $(DM_DIR)/cmcc_dm.c
CFLAGS += -DFEATURE_CMCC_DM_ENABLE 
endif

ifeq ($(THIRDPARTY_CTCC_DM_ENABLE),y)
DM_CSRC += $(DM_DIR)/ctcc_dm.c
CFLAGS += -DFEATURE_CTCC_DM_ENABLE 
endif

ifeq ($(THIRDPARTY_CUCC_DM_ENABLE),y)
DM_CSRC += $(DM_DIR)/common/base64.c \
          $(DM_DIR)/cucc_dm.c
CFLAGS += -DFEATURE_CUCC_DM_ENABLE 
endif

DM_CSRC += $(DM_DIR)/dm_task.c

DM_EXCLUDE_FILES :=
DM_CFILES = $(filter-out $(DM_EXCLUDE_FILES), $(DM_CSRC))
DM_COBJSTEMP := $(patsubst %.c, %.o, $(DM_CFILES))
DM_COBJSTEMP :=$(subst $(DM_DIR),PLAT/middleware/thirdparty/dm,$(DM_COBJSTEMP))
DM_COBJS := $(addprefix $(BUILDDIR)/, $(DM_COBJSTEMP))


-include $(DM_COBJS:.o=.d)


ifeq ($(TOOLCHAIN),GCC)

CFLAGS_INC += -I $(TOP)/SDK/PLAT/os/freertos/portable/gcc
CFLAGS_INC += -I $(GCCLIB_PATH)/arm-none-eabi/include

lib-y += libdm.a

$(BUILDDIR)/lib/libdm.a: $(DM_COBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) -cr $@ $^

endif
