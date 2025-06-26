libdriver-y :=
libdriverprivate-y :=


include $(TOP)/SDK/PLAT/driver/board/qcx212_0h00/Makefile.inc
include $(TOP)/SDK/PLAT/driver/chip/qcx212/Makefile.inc
include $(TOP)/SDK/PLAT/driver/hal/Makefile.inc

ifeq ($(TOOLCHAIN),GCC)

DRIVER_OBJS := $(addprefix $(BUILDDIR)/,$(libdriver-y))

-include $(DRIVER_OBJS:.o=.d)

ifneq ($(DRIVER_OBJS),)
lib-y += libdriver.a

lib-y += libdriver_private_ht.a
endif


$(BUILDDIR)/lib/libdriver.a: $(DRIVER_OBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) -cr $@ $^



DRIVER_PRIVATE_OBJS := $(addprefix $(BUILDDIR)/,$(libdriverprivate-y))
-include $(DRIVER_PRIVATE_OBJS:.o=.d)
ifeq ($(BUILD_USE_PREBUILD_LIB),n)
ifneq ($(DRIVER_PRIVATE_OBJS),)
  lib-y += libdriver_private.a
endif
endif
$(BUILDDIR)/lib/libdriver_private.a: $(DRIVER_PRIVATE_OBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) $(ARFLAGS) $@ $^

libdriver_private_ht-y	+=	PLAT/prebuild/PLAT/src/HT_slpman_qcx212.o \
							PLAT/prebuild/PLAT/src/HT_ostask.o

DRIVER_HT_PRIVATE_OBJS := $(addprefix $(BUILDDIR)/,$(libdriver_private_ht-y))
-include $(DRIVER_HT_PRIVATE_OBJS:.o=.d)
lib-y += libdriver_private_ht.a

$(BUILDDIR)/lib/libdriver_private_ht.a: $(DRIVER_HT_PRIVATE_OBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) $(ARFLAGS) $@ $^

endif

ifeq ($(TOOLCHAIN),ARMCC)

DRIVER_OBJS := $(addprefix $(BUILDDIR)/,$(libdriver-y))
-include $(DRIVER_OBJS:.o=.d)

ifneq ($(DRIVER_OBJS),)
lib-y += libdriver.lib
endif

$(BUILDDIR)/lib/libdriver.lib: $(DRIVER_OBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) $(ARFLAGS) $@ $^


DRIVER_PRIVATE_OBJS := $(addprefix $(BUILDDIR)/,$(libdriverprivate-y))
-include $(DRIVER_PRIVATE_OBJS:.o=.d)
ifeq ($(BUILD_USE_PREBUILD_LIB),n)
ifneq ($(DRIVER_PRIVATE_OBJS),)
  lib-y += libdriver_private.lib
endif
endif
$(BUILDDIR)/lib/libdriver_private.lib: $(DRIVER_PRIVATE_OBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) $(ARFLAGS) $@ $^


endif