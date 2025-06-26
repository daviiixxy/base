# Sources
MBEDTLSDIR = $(PS_SUBDIR)/tcpip/mbedtls/library
MBEDTLS_DEPDENDENCY_INC = -I $(PS_SUBDIR)/tcpip/mbedtls/include \
-I $(PS_SUBDIR)/tcpip/mbedtls/configs \
-I $(PS_SUBDIR)/tcpip/lwip/src/include \
-I $(PS_SUBDIR)/tcpip/lwip/src/include/posix \
-I ./os/freertos/inc \
-I ./os/freertos/CMSIS/inc \
-I ./os/freertos/portable/keil

#include configuration file
MBEDTLS_CFLAGS = $(TCPIP_CFLAGS)

MBEDTLS_CIPHER_FUNCTION_FILES=$(MBEDTLSDIR)/aes.c \
	$(MBEDTLSDIR)/aesni.c \
	$(MBEDTLSDIR)/gcm.c \
	$(MBEDTLSDIR)/arc4.c \
	$(MBEDTLSDIR)/aria.c \		
	$(MBEDTLSDIR)/blowfish.c \
	$(MBEDTLSDIR)/camellia.c \
	$(MBEDTLSDIR)/des.c \
	$(MBEDTLSDIR)/xtea.c \
	$(MBEDTLSDIR)/ccm.c \
	$(MBEDTLSDIR)/cmac.c \
	$(MBEDTLSDIR)/chacha20.c \	
	$(MBEDTLSDIR)/chachapoly.c
	
MBEDTLS_HASH_FUNCTION_FILES=$(MBEDTLSDIR)/md2.c \
	$(MBEDTLSDIR)/md4.c \
	$(MBEDTLSDIR)/md5.c \
	$(MBEDTLSDIR)/sha1.c \
	$(MBEDTLSDIR)/sha256.c \
	$(MBEDTLSDIR)/sha512.c \
	$(MBEDTLSDIR)/ripemd160.c \

MBEDTLS_PUBLICKEY_FUNCTION_FILES=$(MBEDTLSDIR)/rsa.c \
	$(MBEDTLSDIR)/rsa_internal.c \
	$(MBEDTLSDIR)/bignum.c \
	$(MBEDTLSDIR)/dhm.c \
	$(MBEDTLSDIR)/ecdh.c \
	$(MBEDTLSDIR)/ecp.c \
	$(MBEDTLSDIR)/ecdsa.c \
	$(MBEDTLSDIR)/ecjpake.c \
	$(MBEDTLSDIR)/ecp_curves.c \
	$(MBEDTLSDIR)/pem.c \
	$(MBEDTLSDIR)/pkparse.c \
	$(MBEDTLSDIR)/pkcs11.c \
	$(MBEDTLSDIR)/pkcs12.c \
	$(MBEDTLSDIR)/pkcs5.c \
	$(MBEDTLSDIR)/nist_kw.c

MBEDTLS_PSA_FUNCTION_FILES=$(MBEDTLSDIR)/psa_crypto.c \
	$(MBEDTLSDIR)/poly1305.c \
	$(MBEDTLSDIR)/psa_crypto_se.c \
	$(MBEDTLSDIR)/psa_crypto_slot_management.c \
	$(MBEDTLSDIR)/psa_crypto_storage.c \
	$(MBEDTLSDIR)/psa_its_file.c \
	
MBEDTLS_CRYTOGRAPHIC_FUNCTION_FILES=$(MBEDTLSDIR)/x509_crl.c \
	$(MBEDTLSDIR)/x509_crt.c \
	$(MBEDTLSDIR)/x509_csr.c \
	$(MBEDTLSDIR)/x509.c \
	$(MBEDTLSDIR)/x509_create.c \
	$(MBEDTLSDIR)/certs.c 

MBEDTLS_TLS_FUNCTION_FILES=$(MBEDTLSDIR)/ssl_tls.c \
	$(MBEDTLSDIR)/ssl_cli.c \
	$(MBEDTLSDIR)/ssl_srv.c \
	$(MBEDTLSDIR)/ssl_cache.c \
	$(MBEDTLSDIR)/ssl_ciphersuites.c \
	$(MBEDTLSDIR)/ssl_cookie.c \
	$(MBEDTLSDIR)/ssl_ticket.c \
	$(MBEDTLSDIR)/ssl_msg.c

MBEDTLS_RNG_FUNCTION_FILES=$(MBEDTLSDIR)/entropy.c \
	$(MBEDTLSDIR)/entropy_poll.c \
	$(MBEDTLSDIR)/ctr_drbg.c \
	$(MBEDTLSDIR)/hmac_drbg.c \
	$(MBEDTLSDIR)/havege.c \
	$(MBEDTLSDIR)/hkdf.c
	
MBEDTLS_MISC_FUNCTION_FILES=$(MBEDTLSDIR)/asn1parse.c \
	$(MBEDTLSDIR)/base64.c \
	$(MBEDTLSDIR)/debug.c \
	$(MBEDTLSDIR)/error.c \
	$(MBEDTLSDIR)/oid.c \
	$(MBEDTLSDIR)/padlock.c \
	$(MBEDTLSDIR)/version_features.c \
	$(MBEDTLSDIR)/version.c

MBEDTLS_ABSTRACTION_FUNCTION_FILES=$(MBEDTLSDIR)/cipher.c \
	$(MBEDTLSDIR)/cipher_wrap.c \
	$(MBEDTLSDIR)/md.c \
	$(MBEDTLSDIR)/pk.c \
	$(MBEDTLSDIR)/pk_wrap.c
	
MBEDTLS_PLATFORM_FUNCTION_FILES=$(MBEDTLSDIR)/platform.c \
	$(MBEDTLSDIR)/timing.c  \
	$(MBEDTLSDIR)/threading.c \
	$(MBEDTLSDIR)/net_sockets.c \
	$(MBEDTLSDIR)/memory_buffer_alloc.c \
	$(MBEDTLSDIR)/platform.c \
	$(MBEDTLSDIR)/platform_util.c
	
MBEDTLS_CA_FUNCTION_FILES=$(MBEDTLSDIR)/asn1write.c \
	$(MBEDTLSDIR)/pkwrite.c \
	$(MBEDTLSDIR)/x509write_crt.c \
	$(MBEDTLSDIR)/x509write_csr.c
			
MBEDTLS_C_OBJS := $(MBEDTLS_CIPHER_FUNCTION_FILES:%.c=%.o) \
	$(MBEDTLS_HASH_FUNCTION_FILES:%.c=%.o) \
	$(MBEDTLS_PUBLICKEY_FUNCTION_FILES:%.c=%.o) \
	$(MBEDTLS_CRYTOGRAPHIC_FUNCTION_FILES:%.c=%.o) \
	$(MBEDTLS_TLS_FUNCTION_FILES:%.c=%.o) \
	$(MBEDTLS_RNG_FUNCTION_FILES:%.c=%.o) \
	$(MBEDTLS_MISC_FUNCTION_FILES:%.c=%.o) \
	$(MBEDTLS_ABSTRACTION_FUNCTION_FILES:%.c=%.o) \
	$(MBEDTLS_PLATFORM_FUNCTION_FILES:%.c=%.o) \
	$(MBEDTLS_CA_FUNCTION_FILES:%.c=%.o)
	
MBEDTLS_SHARE_OBJ := $(notdir $(MBEDTLS_C_OBJS))
MBEDTLS_C_SHARE_OBJ := $(addprefix $(MD_OUTDIR)\tcp\tls\obj\,$(MBEDTLS_SHARE_OBJ)) 

#MBEDTLS_LIN_INC_MBEDTLS

#MBEDTLS_LIB_INC_INSTALL := $(patsubst %.h,%.o,$(MBEDTLS_LIB_INC))

#first patch mbedtls
#$(info ---- run patch MBEDTLS -----)
#$(CP) 

$(shell mkdir $(MD_OUTDIR)\tcp\tls\obj)
MBEDTLS_C_OBJS=$(patsubst %.c,%.o,$(MBEDTLS_CIPHER_FUNCTION_FILES)) \
	$(patsubst %.c,%.o,$(MBEDTLS_HASH_FUNCTION_FILES)) \
	$(patsubst %.c,%.o,$(MBEDTLS_PUBLICKEY_FUNCTION_FILES)) \
	$(patsubst %.c,%.o,$(MBEDTLS_CRYTOGRAPHIC_FUNCTION_FILES)) \
	$(patsubst %.c,%.o,$(MBEDTLS_TLS_FUNCTION_FILES)) \
	$(patsubst %.c,%.o,$(MBEDTLS_RNG_FUNCTION_FILES)) \
	$(patsubst %.c,%.o,$(MBEDTLS_MISC_FUNCTION_FILES)) \
	$(patsubst %.c,%.o,$(MBEDTLS_ABSTRACTION_FUNCTION_FILES)) \
	$(patsubst %.c,%.o,$(MBEDTLS_PLATFORM_FUNCTION_FILES)) \
	$(patsubst %.c,%.o,$(MBEDTLS_CA_FUNCTION_FILES))
$(info ---- load mbedtls makefile ----)

$(MBEDTLS_C_OBJS):$(MBEDTLS_CIPHER_FUNCTION_FILES) $(MBEDTLS_HASH_FUNCTION_FILES) $(MBEDTLS_PUBLICKEY_FUNCTION_FILES) $(MBEDTLS_CRYTOGRAPHIC_FUNCTION_FILES) $(MBEDTLS_TLS_FUNCTION_FILES) $(MBEDTLS_RNG_FUNCTION_FILES) $(MBEDTLS_MISC_FUNCTION_FILES) $(MBEDTLS_ABSTRACTION_FUNCTION_FILES) $(MBEDTLS_PLATFORM_FUNCTION_FILES) $(MBEDTLS_CA_FUNCTION_FILES) 
	$(CC) $(MBEDTLS_CFLAGS) $(MBEDTLS_DEPDENDENCY_INC) -o $(MD_OUTDIR)\tcp\tls\obj\$(@F) $*.c

#MBEDTLS_DEPENDENT_LIBS = $(LIBS_PATH)\$(OS).lib $(LIBS_PATH)\$(TCPIP).lib
	
#MBEDTLS_LIB_INC_INSTALL: $(MBEDTLS_LIB_INC)
#	$(info *  $*.h *)
#	$(info **  $(dir $<) **)
#	$(info ***  $(*F)   ***)
#	$(info ****  $@  ****)
#$(CP) $*.h $(LIBS_INCS)\$(*F).h

	
.PHONY:mbedtls
mbedtls:$(MBEDTLS_C_OBJS)
	$(info *****************************)
	$(info ***** MBEDTLS Build OK *****)
	$(info *****************************)
	$(shell mkdir $(LIBS_OUTPUT))
	$(AR) -r $(LIBS_OUTPUT)\mbedtls.lib $(MBEDTLS_C_SHARE_OBJ)
#	$(foreach f,$(MBEDTLS_LIB_INC),$(shell $(CP) $(f) $(LIBS_INCS)))

.PHONY:clean-mbedtls
clean-mbedtls:
	$(RM) $(MD_OUTDIR)\tcp\tls\obj\*
	$(RM) $(LIBS_OUTPUT)\mbedtls.lib
#	$(foreach f,$(MBEDTLS_LIB_INC),$(shell $(RM) $(LIBS_INCS)\$(notdir $(f)))) 
