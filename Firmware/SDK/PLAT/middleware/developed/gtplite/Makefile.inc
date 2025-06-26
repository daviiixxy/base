GTPLITE_DIR  := $(TOP)/SDK/PLAT/middleware/developed/gtplite

CFLAGS_INC  +=  -I $(TOP)/SDK/PLAT/middleware/developed/gtplite/inc \
				-I $(TOP)/SDK/PLAT/middleware/developed/gtplite/V4/include

CFLAGS += -DFEATURE_LOCATION_MCS
CFLAGS += -DGTPLITE_ENABLE

GTPLITE_SRC_DIRS += $(GTPLITE_DIR)/src \
					$(GTPLITE_DIR)/V4/src
GTPLITE_EXCLUDE_FILES := 
GTPLITE_CSRC = $(foreach dir, $(GTPLITE_SRC_DIRS), $(wildcard $(dir)/*.c))
GTPLITE_CFILES = $(filter-out $(GTPLITE_EXCLUDE_FILES), $(GTPLITE_CSRC))
GTPLITE_COBJSTEMP := $(patsubst %.c, %.o, $(GTPLITE_CFILES))
GTPLITE_COBJSTEMP :=$(subst $(GTPLITE_DIR),PLAT/middleware/developed/gtplite,$(GTPLITE_COBJSTEMP))
GTPLITE_COBJS := $(addprefix $(BUILDDIR)/, $(GTPLITE_COBJSTEMP))

-include $(GTPLITE_COBJS:.o=.d)

#$(ECHO) Objects GTPLITE_COBJS

ifeq ($(TOOLCHAIN),GCC)
ifeq ($(BUILD_USE_PREBUILD_LIB),n)
lib-y += libgtplite.a
endif
$(BUILDDIR)/lib/libgtplite.a: $(GTPLITE_COBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) -cr $@ $^

endif

ifeq ($(TOOLCHAIN),ARMCC)
ifeq ($(BUILD_USE_PREBUILD_LIB),n)
lib-y += libgtplite.lib
endif
$(BUILDDIR)/lib/libgtplite.lib: $(GTPLITE_COBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) $(ARFLAGS) $@ $^

endif