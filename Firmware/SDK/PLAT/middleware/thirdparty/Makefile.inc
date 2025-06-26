ifeq ($(THIRDPARTY_RTT_ENABLE),y)
include $(TOP)/SDK/PLAT/middleware/thirdparty/RTT/Makefile.inc
endif

ifeq ($(THIRDPARTY_CISONENET_ENABLE),y)
include $(TOP)/SDK/PLAT/middleware/thirdparty/cis_onenet/Makefile.inc
endif

ifeq ($(THIRDPARTY_WAKAAMA_ENABLE),y)
include $(TOP)/SDK/PLAT/middleware/thirdparty/wakaama/Makefile.inc
endif

ifeq ($(THIRDPARTY_CTWING1_5_ENABLE),y)
include $(TOP)/SDK/PLAT/middleware/thirdparty/ctlwm2m/V1.5/Makefile.inc
endif

ifeq ($(THIRDPARTY_HTTPC_ENABLE),y)
include $(TOP)/SDK/PLAT/middleware/thirdparty/httpclient/Makefile.inc
endif

ifeq ($(THIRDPARTY_LWIP_ENABLE),y)
include $(TOP)/SDK/PLAT/middleware/thirdparty/lwip/Makefile.inc
endif

ifeq ($(THIRDPARTY_MBEDTLS_ENABLE),y)
include $(TOP)/SDK/PLAT/middleware/thirdparty/mbedtls/Makefile.inc
endif

ifeq ($(THIRDPARTY_TINYDTLS_ENABLE),y)
include $(TOP)/SDK/PLAT/middleware/thirdparty/tinydtls/Makefile.inc
endif

ifeq ($(THIRDPARTY_IPERF_ENABLE),y)
include $(TOP)/SDK/PLAT/middleware/thirdparty/iperf/Makefile.inc
endif

ifeq ($(THIRDPARTY_PING_ENABLE),y)
include $(TOP)/SDK/PLAT/middleware/thirdparty/ping/Makefile.inc
endif

ifeq ($(THIRDPARTY_LITTEFS_ENABLE),y)
include $(TOP)/SDK/PLAT/middleware/thirdparty/littlefs/Makefile.inc
endif

ifeq ($(THIRDPARTY_LIBCOAP_NO_DTLS_ENABLE),y)
include $(TOP)/SDK/PLAT/middleware/thirdparty/libcoap/MakefileNoDtls.inc
endif

ifeq ($(THIRDPARTY_LIBCOAP_DTLS_ENABLE),y)
include $(TOP)/SDK/PLAT/middleware/thirdparty/libcoap/MakefileDtls.inc
endif

ifeq ($(THIRDPARTY_ERCOAP_ENABLE),y)
include $(TOP)/SDK/PLAT/middleware/thirdparty/er-coap-13/Makefile.inc
endif

ifeq ($(THIRDPARTY_LIBSNTP_ENABLE),y)
include $(TOP)/SDK/PLAT/middleware/thirdparty/sntp/Makefile.inc
endif

ifeq ($(THIRDPARTY_ABUP_FOTA_ENABLE),y)
include $(TOP)/SDK/PLAT/middleware/thirdparty/abup/Makefile.inc
endif

ifeq ($(findstring y, $(THIRDPARTY_CMCC_DM_ENABLE)$(THIRDPARTY_CTCC_DM_ENABLE)$(THIRDPARTY_CUCC_DM_ENABLE)), y)
include $(TOP)/SDK/PLAT/middleware/thirdparty/dm/Makefile.inc
endif