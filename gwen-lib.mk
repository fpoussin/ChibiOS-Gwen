# don't re-define GWENLIB if it has been set elsewhere, e.g in Makefile
ifeq ($(GWENLIB),)
	GWENLIB =	$(CHIBIOS)/ext/gwen
endif

GWENINC +=   $(GWENLIB)/include

include $(GWENLIB)/src/Platforms/platforms.mk
include $(GWENLIB)/Renderers/renderers.mk

#You will have to set these in your Chibios project makefile

ULIBDIR = $(GWENLIB)
ULIBS = -lgwen-cm4 #or -lgwen-cm4d if you need to use gdb
