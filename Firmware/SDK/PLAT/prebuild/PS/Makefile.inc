CFLAGS_INC += -I $(LIBDIR)/PS/inc

ifeq ($(BUILD_PS), y)
ifeq ($(TOOLCHAIN),GCC)
PREBUILDLIBS += $(LIBDIR)/PS/lib/gcc/libps.a   \
                $(LIBDIR)/PS/lib/gcc/libpsl1.a \
				$(LIBDIR)/PLAT/lib/gcc/libpsnv.a
ifeq ($(QC_ROHC_ENABLE),y)
PREBUILDLIBS += $(LIBDIR)/PS/lib/gcc/libpsif_rohc.a
else
PREBUILDLIBS += $(LIBDIR)/PS/lib/gcc/libpsif.a
endif
endif
endif

ifeq ($(TOOLCHAIN),ARMCC)
ifeq ($(BINNAME),app-demo-flash)
LDFLAGS += --userlibpath=$(LIBDIR)/PLAT/lib/keil\
		   --userlibpath=$(LIBDIR)/PS/lib/keil	
						 
PREBUILDLIBS += libpsnv.lib\(*.o\) \
				libps.lib\(*.o\) \
				libpsif.lib\(*.o\) \
				libpsl1.lib\(*.o\) \
				libmiddleware_ec_private.lib\(*.o\) 
ifeq ($(QC_ROHC_ENABLE),y)
PREBUILDLIBS += libpsif_rohc.lib\(*.o\)
else
PREBUILDLIBS += libpsif.lib\(*.o\)
endif
endif
else


CFLAGS += -DFEAT_RPM
CFLAGS += -DVZW_ACC_TEST

endif
