# don't re-define GWENLIB if it has been set elsewhere, e.g in Makefile
ifeq ($(GWENLIB),)
	GWENLIB =	$(CHIBIOS)/ext/gwen
endif

GWENINC +=   $(GWENLIB)/include

GWENSRC += $(GWENLIB)/src/Anim.cpp \
		$(GWENLIB)/src/BaseRender.cpp \
		$(GWENLIB)/src/DragAndDrop.cpp \
		$(GWENLIB)/src/events.cpp \
		$(GWENLIB)/src/Gwen.cpp \
		$(GWENLIB)/src/Hook.cpp \
		$(GWENLIB)/src/inputhandler.cpp \
		$(GWENLIB)/src/Skin.cpp \
		$(GWENLIB)/src/ToolTip.cpp \
		$(GWENLIB)/src/Utility.cpp
		
		
include $(GWENLIB)/src/Platforms/platforms.mk
include $(GWENLIB)/src/Controls/controls.mk
include $(GWENLIB)/src/Controls/Dialog/dialog.mk
include $(GWENLIB)/Renderers/renderers.mk
#include $(GWENLIB)/UnitTest/unittest.mk
