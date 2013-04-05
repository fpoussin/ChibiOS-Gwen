
GWENLIB = .

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
		
include $(GWENLIB)/src/Controls/controls.mk
include $(GWENLIB)/src/Controls/Dialog/dialog.mk

BUILD_DIR = build
OBJDIR_M3 = $(BUILD_DIR)/obj_m3
OBJDIR_M4 = $(BUILD_DIR)/obj_m4
OBJDIR_M3_DBG = $(BUILD_DIR)_dgb/obj_m3
OBJDIR_M4_DBG = $(BUILD_DIR)_dgb/obj_m4
LIBDIR = ./

rm=rm -f
MKDIR_P = mkdir -p

CROSS_COMPILE = arm-none-eabi-
CC=$(CROSS_COMPILE)gcc
CXX=$(CROSS_COMPILE)g++
AR = $(CROSS_COMPILE)ar

OBJECTS_M3  := $(GWENSRC:%.cpp=$(OBJDIR_M3)/%.o)
OBJECTS_M4  := $(GWENSRC:%.cpp=$(OBJDIR_M4)/%.o)
OBJECTS_M3_DBG  := $(GWENSRC:%.cpp=$(OBJDIR_M3_DBG)/%.o)
OBJECTS_M4_DBG  := $(GWENSRC:%.cpp=$(OBJDIR_M4_DBG)/%.o)
INCLUDES = -I$(GWENINC)

CPPFLAGS_M3=-Wall $(INCLUDES) -Os -nostdlib -mthumb -DTHUMB -nostartfiles -fomit-frame-pointer -falign-functions=16 -ffunction-sections -fdata-sections -fno-common
CPPFLAGS_M4=-Wall $(INCLUDES) -Os -nostdlib -mthumb -DTHUMB -nostartfiles -fomit-frame-pointer -falign-functions=16 -ffunction-sections -fdata-sections -fno-common

USE_FPU = yes

ifeq ($(USE_FPU),yes)
  CPPFLAGS_M4 += -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -fsingle-precision-constant
endif

default: all
all: gwen gwen-dbg
gwen: libgwen-cm3.a libgwen-cm4.a
gwen-dbg: libgwen-cm3d.a libgwen-cm4d.a

libgwen-cm3.a: $(OBJECTS_M3)
	@mkdir -p $(LIBDIR)
	$(AR) rcs $(LIBDIR)/$@ $(OBJECTS_M3)
	
libgwen-cm3d.a: $(OBJECTS_M3_DBG)
	@mkdir -p $(LIBDIR)
	$(AR) rcs $(LIBDIR)/$@ $(OBJECTS_M3_DBG)

libgwen-cm4.a: $(OBJECTS_M4)
	@mkdir -p $(LIBDIR)
	$(AR) rcs $(LIBDIR)/$@ $(OBJECTS_M4)
	
libgwen-cm4d.a: $(OBJECTS_M4_DBG)
	@mkdir -p $(LIBDIR)
	$(AR) rcs $(LIBDIR)/$@ $(OBJECTS_M4_DBG)
	
$(OBJECTS_M3): $(OBJDIR_M3)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) -mcpu=cortex-m3 $(CXXFLAGS) $(CPPFLAGS_M3) -c $< -o $@
	
$(OBJECTS_M3_DBG): $(OBJDIR_M3_DBG)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) -ggdb -mcpu=cortex-m3 $(CXXFLAGS) $(CPPFLAGS_M3)  -c $< -o $@
	
$(OBJECTS_M4): $(OBJDIR_M4)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) -mcpu=cortex-m4 $(CXXFLAGS) $(CPPFLAGS_M4) -c $< -o $@
	
$(OBJECTS_M4_DBG): $(OBJDIR_M4_DBG)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) -ggdb -mcpu=cortex-m4 $(CXXFLAGS) $(CPPFLAGS_M4) -c $< -o $@
	
clean:
	@$(rm) $(OBJECTS_M3) $(OBJECTS_M4) $(OBJECTS_M3_DBG) $(OBJECTS_M4_DBG) $(LIBDIR)/lib*.a
	
	@echo "Cleanup complete!"

    