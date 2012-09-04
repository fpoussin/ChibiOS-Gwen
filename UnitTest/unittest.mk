# don't re-define GWENLIB if it has been set elsewhere, e.g in Makefile
ifeq ($(GWENLIB),)
	GWENLIB =	$(CHIBIOS)/ext/gwen
endif

GWENSRC += $(GWENLIB)/UnitTest/Button.cpp \
		$(GWENLIB)/UnitTest/Checkbox.cpp \
		$(GWENLIB)/UnitTest/CollapsibleList.cpp \
		$(GWENLIB)/UnitTest/ColorPicker.cpp \
		$(GWENLIB)/UnitTest/ComboBox.cpp \
		$(GWENLIB)/UnitTest/CrossSplitter.cpp \
		$(GWENLIB)/UnitTest/GroupBox.cpp \
		$(GWENLIB)/UnitTest/ImagePanel.cpp \
		$(GWENLIB)/UnitTest/Label.cpp \
		$(GWENLIB)/UnitTest/LabelMultiline.cpp \
		$(GWENLIB)/UnitTest/ListBox.cpp \
		$(GWENLIB)/UnitTest/MenuStrip.cpp \
		$(GWENLIB)/UnitTest/Numeric.cpp \
		$(GWENLIB)/UnitTest/PageControl.cpp \
		$(GWENLIB)/UnitTest/ProgressBar.cpp \
		$(GWENLIB)/UnitTest/Properties.cpp \
		$(GWENLIB)/UnitTest/RadioButton.cpp \
		$(GWENLIB)/UnitTest/ScrollControl.cpp \
		$(GWENLIB)/UnitTest/Slider.cpp \
		$(GWENLIB)/UnitTest/StatusBar.cpp \
		$(GWENLIB)/UnitTest/TabControl.cpp \
		$(GWENLIB)/UnitTest/TextBox.cpp \
		$(GWENLIB)/UnitTest/TreeControl.cpp \
		$(GWENLIB)/UnitTest/UnitTest.cpp \
		$(GWENLIB)/UnitTest/Window.cpp \
