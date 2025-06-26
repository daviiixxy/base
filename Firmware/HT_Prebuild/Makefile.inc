ht_prebuild_libraries :=

ht_prebuild_libraries += $(HT_LIBDIR)/libdriver_private_ht.a \
						$(HT_LIBDIR)/libdriver.a \
						$(HT_LIBDIR)/liblfs.a
                        

ifeq ($(HT_LIBRARY_MQTT_ENABLE),y)

ht_prebuild_libraries += $(HT_LIBDIR)/libfreertos.a \
                        $(HT_LIBDIR)/libiperf.a \
                        $(HT_LIBDIR)/liblwip.a \
                        $(HT_LIBDIR)/libmbedtls.a \
                        $(HT_LIBDIR)/libmiddleware_ec.a \
                        $(HT_LIBDIR)/libping.a \
                        $(HT_LIBDIR)/libsntp.a

endif

ifeq ($(HT_LIBRARY_HTTPS_ENABLE),y)

ht_prebuild_libraries += $(HT_LIBDIR)/libfreertos.a \
                        $(HT_LIBDIR)/libhttpclient.a \
                        $(HT_LIBDIR)/libiperf.a \
                        $(HT_LIBDIR)/liblwip.a \
                        $(HT_LIBDIR)/libmbedtls.a \
                        $(HT_LIBDIR)/libmiddleware_ec.a \
                        $(HT_LIBDIR)/libping.a \
                        $(HT_LIBDIR)/libsntp.a

endif

ifeq ($(HT_LIBRARY_CJSON_ENABLE),y)
CFLAGS_INC += -I $(TOP)/HT_Prebuild/CJSON/Inc
ht_prebuild_libraries += $(HT_LIBDIR)/libHTcjson.a
endif

ifeq ($(HT_LIBRARY_SLPMAN_ENABLE),y)

ht_prebuild_libraries += $(HT_LIBDIR)/libfreertos.a \
                        $(HT_LIBDIR)/libiperf.a \
                        $(HT_LIBDIR)/liblwip.a \
                        $(HT_LIBDIR)/libmiddleware_ec.a \
                        $(HT_LIBDIR)/libping.a \
                        $(HT_LIBDIR)/libsntp.a 

endif

ifeq ($(HT_LIBRARY_SLEEP_ENABLE),y)

ht_prebuild_libraries += $(HT_LIBDIR)/libfreertos.a \
                        $(HT_LIBDIR)/libiperf.a \
                        $(HT_LIBDIR)/liblwip.a \
                        $(HT_LIBDIR)/libmiddleware_ec.a \
                        $(HT_LIBDIR)/libping.a \
                        $(HT_LIBDIR)/libsntp.a \
                        $(HT_LIBDIR)/libHTsleep.a

endif
