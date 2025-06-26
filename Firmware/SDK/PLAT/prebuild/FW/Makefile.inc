CFLAGS_INC += -I $(LIBDIR)/FW/inc
ifeq ($(BUILD_FW), y)
ifeq ($(TOOLCHAIN),GCC)
PREBUILDLIBS += $(LIBDIR)/FW/lib/gcc/libfw.a
endif

endif
