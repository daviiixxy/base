CFLAGS_INC += -I $(LIBDIR)/PLAT/inc

ifeq ($(TOOLCHAIN),ARMCC)
ifeq ($(BINNAME),bootloader)
LDFLAGS += --userlibpath=$(LIBDIR)/PLAT/lib/keil
PREBUILDLIBS += libdriver_private.lib
		   
else

CFLAGS += -DHAVE_MBEDTLS	\
		  -DWITH_POSIX    \
		  -DFEATURE_MQTT_ENABLE  \
		  -DFEATURE_HTTPC_ENABLE \
		  -DFEATURE_AT_ENABLE \
		  -DFEATURE_ATDEBUG_ENABLE \
		  -DFEATURE_ATADC_ENABLE 


TINYDTLS_CFLAGS ?= -DDTLSv12 -DWITH_SHA256 -DNO_DECLTYPE -DWITH_TINYDTLS
CFLAGS += $(TINYDTLS_CFLAGS)

CFLAGS += $(MBEDTLS_CFLAGS)
CFLAGS += -DFEATURE_MBEDTLS_ENABLE

LWIPCONFIG_CFLAGS ?= -DLWIP_CONFIG_FILE=\"lwip_config_qcx2120h00.h\"
CFLAGS += $(LWIPCONFIG_CFLAGS)

ifeq ($(DRIVER_PMU_ENABLE),y)  
    CFLAGS      += -DPM_FEATURE_ENABLE
endif

ifeq ($(DRIVER_UNILOG_ENABLE),y)  
    CFLAGS      += -DUINILOG_FEATURE_ENABLE
endif

PREBUILDLIBS += $(LIBDIR)/PLAT/lib/keil/libdriver_private.lib \
				$(LIBDIR)/PLAT/lib/keil/libmiddleware_ec_private.lib \
				$(LIBDIR)/PLAT/lib/keil/libpsnv.lib 
				
ifeq ($(MIDDLEWARE_CCIO_ENABLE),y)
PREBUILDLIBS += $(LIBDIR)/PLAT/lib/keil/libccio.lib
endif

ifeq ($(GTPLITE_ENABLE),y)
PREBUILDLIBS += $(LIBDIR)/PLAT/lib/keil/libgtplite.lib
endif

ifeq ($(QC_ROHC_ENABLE),y)
PREBUILDLIBS += $(LIBDIR)/PLAT/lib/keil/libosa_rohc.lib \
				$(LIBDIR)/PLAT/lib/keil/librohc.lib 
else
PREBUILDLIBS += $(LIBDIR)/PLAT/lib/keil/libosa.lib
endif                
endif
endif
		  
ifeq ($(QC_ROHC_ENABLE),y)
	CFLAGS +=  -DROHC_ENABLE_DEFINE=1
endif

ifeq ($(TOOLCHAIN),GCC)
PREBUILDLIBS += $(LIBDIR)/PLAT/lib/gcc/libdriver_private.a \
                $(LIBDIR)/PLAT/lib/gcc/libmiddleware_ec_private.a 

ifeq ($(MIDDLEWARE_CCIO_ENABLE),y)
PREBUILDLIBS += $(LIBDIR)/PLAT/lib/gcc/libccio.a 
endif				
	
ifeq ($(GTPLITE_ENABLE),y)
PREBUILDLIBS += $(LIBDIR)/PLAT/lib/gcc/libgtplite.a 
endif
		
ifeq ($(QC_ROHC_ENABLE),y)
PREBUILDLIBS += $(LIBDIR)/PLAT/lib/gcc/libosa_rohc.a \
				$(LIBDIR)/PLAT/lib/gcc/librohc.a 
else
PREBUILDLIBS += $(LIBDIR)/PLAT/lib/gcc/libosa.a
endif

endif