
ht_app_api-y :=
ht_startup_lib-y :=
ht_thirdparty_api-y :=

include $(TOP)/SDK/HT_API/Makefile.inc
include $(TOP)/SDK/Thirdparty/Makefile.inc

HT_DRIVER_OBJ := $(addprefix $(BUILDDIR)/,$(ht_app_api-y))

-include $(HT_DRIVER_OBJ:.o=.d)

ifneq ($(HT_DRIVER_OBJ),)
ht_app_api-y += libHTDriver.a
endif

$(BUILDDIR)/libHTDriver.a: $(HT_DRIVER_OBJ)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) -cr $@ $^


###############################################################

HT_STARTUP_OBJS := $(addprefix $(BUILDDIR)/,$(ht_startup_lib-y))
-include $(HT_STARTUP_OBJS:.o=.d)

ht_startup_lib-y += libHTStartup.a

$(BUILDDIR)/libHTStartup.a: $(HT_STARTUP_OBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) -cr $@ $^

###############################################################

HT_THIRDPARTY_OBJ := $(addprefix $(BUILDDIR)/,$(ht_thirdparty_api-y))
-include $(HT_THIRDPARTY_OBJ:.o=.d)

ifneq ($(HT_THIRDPARTY_OBJ),)
ht_thirdparty_api-y += libHTThirdparty.a
endif

$(BUILDDIR)/libHTThirdparty.a: $(HT_THIRDPARTY_OBJ)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) -cr $@ $^