MW_HOST_DIRS := $(TOP)/SDK/PLAT/middleware/developed
CFLAGS += -DARM_MATH_CM3
CFLAGS_INC += -I $(MW_HOST_DIRS)/debug/inc \
              -I $(MW_HOST_DIRS)/nvram/inc \
              -I $(MW_HOST_DIRS)/cms/psdial/inc \
              -I $(MW_HOST_DIRS)/cms/cms/inc \
              -I $(MW_HOST_DIRS)/cms/psil/inc \
              -I $(MW_HOST_DIRS)/cms/pslpp/inc \
              -I $(MW_HOST_DIRS)/cms/pslpp/nbasn1/inc \
              -I $(MW_HOST_DIRS)/cms/psstk/inc \
              -I $(MW_HOST_DIRS)/cms/sockmgr/inc \
              -I $(MW_HOST_DIRS)/cms/cmsnetlight/inc \
              -I $(MW_HOST_DIRS)/qcapi/appmwapi/inc \
              -I $(MW_HOST_DIRS)/qcapi/psapi/inc \
              -I $(MW_HOST_DIRS)/simbip/inc        \
              -I $(MW_HOST_DIRS)/common/inc        \
              -I $(CROSS_COMPILE)/../../PACK/ARM/CMSIS/5.0.1/CMSIS/include
			  
			  
ifeq ($(COAP_MDM_ENABLE),y)
CFLAGS_INC += -I $(MW_HOST_DIRS)/iot/dtls/inc \
			  -I $(MW_HOST_DIRS)/iot/coap/inc
endif
ifeq ($(LWM2M_MDM_ENABLE),y)
CFLAGS_INC += -I $(MW_HOST_DIRS)/iot/m2m/core/inc \
			  -I $(MW_HOST_DIRS)/iot/common/inc \
			  -I $(MW_HOST_DIRS)/iot/m2m/lwm2m/inc
endif
			  
ifeq ($(BUILD_PS), y) 			  
include $(TOP)/SDK/PLAT/middleware/developed/psnv/Makefile.inc
endif

ifeq ($(BUILD_USE_PREBUILD_LIB), n)
CFLAGS_INC += -I $(TOP)/SDK/PROTOCOL/SRC/tcpip/netmgr/inc \
              -I $(TOP)/SDK/PROTOCOL/SRC/ps/ccm/cmi       \
              -I $(TOP)/SDK/PROTOCOL/SRC/tcpip/lwip/src/include \
              -I $(TOP)/SDK/PROTOCOL/SRC/tcpip/lwip/src/include/lwip

else
CFLAGS_INC += -I $(LIBDIR)/PS/inc \
              -I $(TOP)/SDK/PLAT/middleware/thirdparty/lwip/src/include \
              -I $(TOP)/SDK/PLAT/middleware/thirdparty/lwip/src/include/lwip
endif

ifeq ($(AT_EXAMPLE_ENABLE),y)
CFLAGS += -DFEATURE_EXAMPLE_ENABLE 
endif

ifeq ($(MIDDLEWARE_DEBUG_TRACE_ENABLE),y)
     MW_PRIVATE_SRC_DIRS += $(MW_HOST_DIRS)/debug/src 
endif

ifeq ($(MIDDLEWARE_NVRAM_ENABLE),y)
     MW_PRIVATE_SRC_DIRS += $(MW_HOST_DIRS)/nvram/src 
	 MW_SRC_DIRS         += $(MW_HOST_DIRS)/nvram/data/qcx212
						   
endif
ifeq ($(COAP_MDM_ENABLE),y)
	include $(TOP)/SDK/PLAT/middleware/developed/iot/coap/Makefile.inc
endif

ifeq ($(LWM2M_MDM_ENABLE),y)
    include $(TOP)/SDK/PLAT/middleware/developed/iot/Makefile.inc
endif

ifeq ($(GTPLITE_ENABLE),y)
	include $(TOP)/SDK/PLAT/middleware/developed/gtplite/Makefile.inc
endif

ifeq ($(MIDDLEWARE_CMS_ENABLE),y)
     MW_SRC_DIRS         += $(MW_HOST_DIRS)/cms/psdial/src \
                            $(MW_HOST_DIRS)/qcapi/psapi/src \
                            $(MW_HOST_DIRS)/qcapi/appmwapi/src \
                            $(MW_HOST_DIRS)/cms/cms/src  \
                            $(MW_HOST_DIRS)/common/src   \
                            $(MW_HOST_DIRS)/cms/cmsnetlight/src \
							$(MW_HOST_DIRS)/cms/sockmgr/src

     MW_PRIVATE_SRC_DIRS += $(MW_HOST_DIRS)/cms/psil/src \
                            $(MW_HOST_DIRS)/cms/pslpp/src \
                            $(MW_HOST_DIRS)/cms/pslpp/nbasn1/src \
                            $(MW_HOST_DIRS)/cms/psstk/src \
                            
     #MW_PRIVATE_EXCLUDE_FILES += $(MW_HOST_DIRS)/cms/pslpp/nbasn1/src/perdecenc.c
endif
ifeq ($(MIDDLEWARE_SIMBIP_ENABLE),y)
     MW_PRIVATE_SRC_DIRS += $(MW_HOST_DIRS)/simbip/src
endif

ifeq ($(MIDDLEWARE_FEATURE_PRODMODE_ENABLE),y)
CFLAGS += -DFEATURE_PRODMODE_ENABLE
endif

ifeq ($(BUILD_AT),y)
CFLAGS_INC += -I $(MW_HOST_DIRS)/at/atdecoder/inc \
              -I $(MW_HOST_DIRS)/at/atps/inc \
              -I $(MW_HOST_DIRS)/at/atps/inc/cnfind \
              -I $(MW_HOST_DIRS)/at/atcust/inc \
              -I $(MW_HOST_DIRS)/at/atcust/inc/cnfind \
              -I $(MW_HOST_DIRS)/at/atentity/inc \
              -I $(MW_HOST_DIRS)/at/atreply/inc 

CFLAGS += -DFEATURE_AT_ENABLE

ifeq ($(BUILD_AT_REF),y)
CFLAGS_INC += -I $(MW_HOST_DIRS)/at/atref/inc \
              -I $(MW_HOST_DIRS)/at/atref/inc/cnfind 
	

MW_SRC_DIRS += $(MW_HOST_DIRS)/at/atref/src	\
               $(MW_HOST_DIRS)/at/atref/src/cnfind 
			   
CFLAGS += -DFEATURE_REF_AT_ENABLE
endif
              
MW_SRC_DIRS += $(MW_HOST_DIRS)/at/atcust/src/cnfind \
               $(MW_HOST_DIRS)/at/atcust/src \
               $(MW_HOST_DIRS)/at/atentity/src	\
               $(MW_HOST_DIRS)/at/atps/src	\
               $(MW_HOST_DIRS)/at/atps/src/cnfind \
               $(MW_HOST_DIRS)/at/atreply/src     \
			   $(MW_HOST_DIRS)/at/atdecoder/src

#MW_PRIVATE_SRC_DIRS += $(MW_HOST_DIRS)/at/atdecoder/src

#########################################################
ifeq ($(BUILD_AT_DEBUG), y)
BUILD_EXCLUDE_ATDEBUG :=
CFLAGS += -DFEATURE_ATDEBUG_ENABLE
else
BUILD_EXCLUDE_ATDEBUG := $(MW_HOST_DIRS)/at/atps/src/atqc_debug.c \
                         $(MW_HOST_DIRS)/at/atps/src/atqc_tcpip.c
endif

BUILD_EXCLUDE_ATSTUB  := $(MW_HOST_DIRS)/cms/cms/src/cms_at_stub.c
#########################################################
ifeq ($(THIRDPARTY_CISONENET_ENABLE), y)
THIRD_PARTY_EXCLUDE_CISONENET :=
else
THIRD_PARTY_EXCLUDE_CISONENET := $(MW_HOST_DIRS)/at/atentity/src/at_onenet_task.c \
                                 $(MW_HOST_DIRS)/at/atcust/src/cnfind/atqc_onenet_cnf_ind.c \
                                 $(MW_HOST_DIRS)/at/atcust/src/atqc_onenet.c
endif

#########################################################
ifeq ($(THIRDPARTY_WAKAAMA_ENABLE), y)
THIRD_PARTY_EXCLUDE_WAKAAMA :=
else
THIRD_PARTY_EXCLUDE_WAKAAMA := $(MW_HOST_DIRS)/at/atentity/src/at_lwm2m_task.c\
                               $(MW_HOST_DIRS)/at/atcust/src/cnfind/atqc_lwm2m_cnf_ind.c \
                               $(MW_HOST_DIRS)/at/atcust/src/atqc_lwm2m.c
endif

#########################################################

ifeq ($(THIRDPARTY_CTWING1_5_ENABLE), y)
THIRD_PARTY_EXCLUDE_CTWING1_5 :=
else
THIRD_PARTY_EXCLUDE_CTWING1_5 := $(MW_HOST_DIRS)/at/atentity/src/at_ctlwm2m_task.c\
                               $(MW_HOST_DIRS)/qcapi/appmwapi/src/qc_ctlwm2m_api.c \
                               $(MW_HOST_DIRS)/at/atcust/src/cnfind/atqc_ctlwm2m_cnf_ind.c \
                               $(MW_HOST_DIRS)/at/atcust/src/atqc_ctlwm2m1_5.c \
                               $(MW_HOST_DIRS)/at/atref/src/atqc_ref_ctlwm2m.c 
endif

#########################################################
ifeq ($(THIRDPARTY_MQTT_ENABLE), y)
THIRD_PARTY_EXCLUDE_MQTT :=
else
THIRD_PARTY_EXCLUDE_MQTT := $(MW_HOST_DIRS)/qcapi/appmwapi/src/qc_mqtt_api.c \
                            $(MW_HOST_DIRS)/at/atcust/src/cnfind/atqc_mqtt_cnf_ind.c \
                            $(MW_HOST_DIRS)/at/atcust/src/atqc_mqtt.c \
                            $(MW_HOST_DIRS)/at/atentity/src/at_mqtt_task.c
endif

#########################################################
ifeq ($(THIRDPARTY_LIBCOAP_NO_DTLS_ENABLE), y)
THIRD_PARTY_EXCLUDE_LIBCOAP :=
else
    ifeq ($(THIRDPARTY_LIBCOAP_DTLS_ENABLE), y)
    THIRD_PARTY_EXCLUDE_LIBCOAP :=
    else
    THIRD_PARTY_EXCLUDE_LIBCOAP := $(MW_HOST_DIRS)/qcapi/appmwapi/src/qc_coap_api.c \
                                    $(MW_HOST_DIRS)/at/atcust/src/cnfind/atqc_coap_cnf_ind.c \
                                    $(MW_HOST_DIRS)/at/atcust/src/atqc_coap.c \
                                    $(MW_HOST_DIRS)/at/atentity/src/at_coap_task.c
    endif							   
endif

#########################################################
ifeq ($(THIRDPARTY_HTTPC_ENABLE), y)
THIRD_PARTY_EXCLUDE_HTTPC :=
else
THIRD_PARTY_EXCLUDE_HTTPC := $(MW_HOST_DIRS)/at/atentity/src/at_http_task.c \
                             $(MW_HOST_DIRS)/at/atcust/src/cnfind/atqc_http_cnf_ind.c \
                             $(MW_HOST_DIRS)/at/atcust/src/atqc_http.c
endif

#########################################################
ifeq ($(THIRDPARTY_LIBSNTP_ENABLE), y)
THIRD_PARTY_EXCLUDE_LIBSNTP :=
else
THIRD_PARTY_EXCLUDE_LIBSNTP := 	$(MW_HOST_DIRS)/qcapi/appmwapi/src/reqsntpapi.c \
                             		$(MW_HOST_DIRS)/at/atps/src/atqc_sntp.c
endif

#########################################################
ifeq ($(AT_ADC_ENABLE), y)
CFLAGS += -DFEATURE_ATADC_ENABLE
THIRD_PARTY_EXCLUDE_EXAMPLE :=
else
THIRD_PARTY_EXCLUDE_EXAMPLE := 	$(MW_HOST_DIRS)/at/atcust/src/cnfind/atqc_adc_cnf_ind.c \
                                $(MW_HOST_DIRS)/at/atcust/src/atqc_adc.c \
                                $(MW_HOST_DIRS)/at/atentity/src/at_adc_task.c
endif

#########################################################
ifeq ($(AT_EXAMPLE_ENABLE), y)
THIRD_PARTY_EXCLUDE_EXAMPLE :=
else
THIRD_PARTY_EXCLUDE_EXAMPLE := 	$(MW_HOST_DIRS)/at/atcust/src/cnfind/atqc_example_cnf_ind.c \
                                $(MW_HOST_DIRS)/at/atcust/src/atqc_example.c \
                                $(MW_HOST_DIRS)/at/atentity/src/at_example_task.c
endif

else
##############################For non-AT############################################
#################################CIS_ONENET#########################################
ifeq ($(THIRDPARTY_CISONENET_ENABLE), y)
THIRD_PARTY_EXCLUDE_CISONENET :=
else
THIRD_PARTY_EXCLUDE_CISONENET := $(MW_HOST_DIRS)/at/atentity/src/at_onenet_task.c \
                                 $(MW_HOST_DIRS)/at/atcust/src/cnfind/atqc_onenet_cnf_ind.c \
                                 $(MW_HOST_DIRS)/at/atcust/src/atqc_onenet.c
endif
#################################wakaama############################################
ifeq ($(THIRDPARTY_WAKAAMA_ENABLE), y)
THIRD_PARTY_EXCLUDE_WAKAAMA :=
else
THIRD_PARTY_EXCLUDE_WAKAAMA := $(MW_HOST_DIRS)/at/atentity/src/at_lwm2m_task.c \
                               $(MW_HOST_DIRS)/at/atcust/src/cnfind/atqc_lwm2m_cnf_ind.c \
                               $(MW_HOST_DIRS)/at/atcust/src/atqc_lwm2m.c
endif
#################################ctlwm2m############################################
ifeq ($(THIRDPARTY_CTWING1_5_ENABLE), y)
THIRD_PARTY_EXCLUDE_CTWING1_5 :=
else
THIRD_PARTY_EXCLUDE_CTWING1_5 := $(MW_HOST_DIRS)/at/atentity/src/at_ctlwm2m_task.c\
                                 $(MW_HOST_DIRS)/qcapi/appmwapi/src/qc_ctlwm2m_api.c \
                                 $(MW_HOST_DIRS)/at/atcust/src/cnfind/atqc_ctlwm2m_cnf_ind.c \
                                 $(MW_HOST_DIRS)/at/atcust/src/atqc_ctlwm2m1_5.c
endif
ifeq ($(THIRDPARTY_HTTPC_ENABLE), y)
THIRD_PARTY_EXCLUDE_HTTPC :=
else
THIRD_PARTY_EXCLUDE_HTTPC     := $(MW_HOST_DIRS)/at/atentity/src/at_http_task.c \
                                 $(MW_HOST_DIRS)/at/atcust/src/cnfind/atqc_http_cnf_ind.c \
                                 $(MW_HOST_DIRS)/at/atcust/src/atqc_http.c
endif
THIRD_PARTY_EXCLUDE_LIBCOAP   := $(MW_HOST_DIRS)/qcapi/appmwapi/src/qc_coap_api.c
THIRD_PARTY_EXCLUDE_MQTT      := $(MW_HOST_DIRS)/qcapi/appmwapi/src/qc_mqtt_api.c

endif




MW_EXCLUDE_FILES := $(THIRD_PARTY_EXCLUDE_CISONENET) \
                    $(THIRD_PARTY_EXCLUDE_MQTT)      \
                    $(THIRD_PARTY_EXCLUDE_LIBCOAP)   \
                    $(THIRD_PARTY_EXCLUDE_HTTPC)     \
                    $(THIRD_PARTY_EXCLUDE_CTWING1_5) \
                    $(THIRD_PARTY_EXCLUDE_LIBSNTP)   \
                    $(THIRD_PARTY_EXCLUDE_EXAMPLE)   \
                    $(BUILD_EXCLUDE_ATDEBUG)         \
					$(BUILD_EXCLUDE_ATSTUB)



MW_CSRC = $(foreach dir, $(MW_SRC_DIRS), $(wildcard $(dir)/*.c))
MW_CFILES = $(filter-out $(MW_EXCLUDE_FILES), $(MW_CSRC))
MW_COBJSTEMP := $(patsubst %.c, %.o, $(MW_CFILES))
MW_COBJS :=$(subst $(MW_HOST_DIRS),PLAT/middleware/developed,$(MW_COBJSTEMP))
MW_COBJS := $(addprefix $(BUILDDIR)/, $(MW_COBJS))


MW_PRIVATE_CSRC = $(foreach dir, $(MW_PRIVATE_SRC_DIRS), $(wildcard $(dir)/*.c))
MW_PRIVATE_CFILES = $(filter-out $(MW_EXCLUDE_FILES), $(MW_PRIVATE_CSRC))
MW_PRIVATE_COBJSTEMP := $(patsubst %.c, %.o, $(MW_PRIVATE_CFILES))
MW_PRIVATE_COBJS :=$(subst $(MW_HOST_DIRS),PLAT/middleware/developed,$(MW_PRIVATE_COBJSTEMP))
MW_PRIVATE_COBJS := $(addprefix $(BUILDDIR)/, $(MW_PRIVATE_COBJS))

-include $(MW_COBJS:.o=.d)
-include $(MW_PRIVATE_COBJS:.o=.d)


ifeq ($(TOOLCHAIN),GCC)

CFLAGS_INC += -I $(TOP)/SDK/PLAT/os/freertos/portable/gcc
ifneq ($(MW_COBJS),)
	lib-y += libmiddleware_ec.a
endif
ifneq ($(MW_PRIVATE_COBJS),)
ifeq ($(BUILD_USE_PREBUILD_LIB),n)
	lib-y += libmiddleware_ec_private.a
endif
endif

$(BUILDDIR)/lib/libmiddleware_ec.a: $(MW_COBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) $(ARFLAGS) $@ $^

$(BUILDDIR)/lib/libmiddleware_ec_private.a: $(MW_PRIVATE_COBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) $(ARFLAGS) $@ $^

endif

ifeq ($(TOOLCHAIN),ARMCC)

## if no objs is needed to compile, just not intitate the compile process
ifneq ($(MW_COBJS),)
	lib-y += libmiddleware_ec.lib
endif

ifneq ($(MW_PRIVATE_COBJS),)
ifeq ($(BUILD_USE_PREBUILD_LIB),n)
	lib-y += libmiddleware_ec_private.lib
endif
endif

$(BUILDDIR)/lib/libmiddleware_ec.lib: $(MW_COBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) $(ARFLAGS) $@ $^

$(BUILDDIR)/lib/libmiddleware_ec_private.lib: $(MW_PRIVATE_COBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) $(ARFLAGS) $@ $^

endif

