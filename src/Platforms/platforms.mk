# don't re-define GWENLIB if it has been set elsewhere, e.g in Makefile
ifeq ($(GWENLIB),)
	GWENLIB =	$(CHIBIOS)/ext/gwen
endif

GWENSRC += $(GWENLIB)/src/Platforms/ChibiOS.cpp \
		$(GWENLIB)/src/Platforms/Null.cpp
