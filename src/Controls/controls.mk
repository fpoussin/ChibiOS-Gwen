# don't re-define GWENLIB if it has been set elsewhere, e.g in Makefile
ifeq ($(GWENLIB),)
	GWENLIB =	$(CHIBIOS)/ext/gwen
endif

GWENSRC += $(GWENLIB)/src/Controls/Base.cpp \
		$(GWENLIB)/src/Controls/Button.cpp \
		$(GWENLIB)/src/Controls/Canvas.cpp \
		$(GWENLIB)/src/Controls/CheckBox.cpp \
		$(GWENLIB)/src/Controls/CollapsibleCategory.cpp \
		$(GWENLIB)/src/Controls/ColorControls.cpp \
		$(GWENLIB)/src/Controls/ColorPicker.cpp \
		$(GWENLIB)/src/Controls/ComboBox.cpp \
		$(GWENLIB)/src/Controls/CrossSplitter.cpp \
		$(GWENLIB)/src/Controls/DockBase.cpp \
		$(GWENLIB)/src/Controls/DockedTabControl.cpp \
		$(GWENLIB)/src/Controls/Dragger.cpp \
		$(GWENLIB)/src/Controls/GroupBox.cpp \
		$(GWENLIB)/src/Controls/HorizontalScrollBar.cpp \
		$(GWENLIB)/src/Controls/HorizontalSlider.cpp \
		$(GWENLIB)/src/Controls/HSVColorPicker.cpp \
		$(GWENLIB)/src/Controls/ImagePanel.cpp \
		$(GWENLIB)/src/Controls/LabelClickable.cpp \
		$(GWENLIB)/src/Controls/Label.cpp \
		$(GWENLIB)/src/Controls/ListBox.cpp \
		$(GWENLIB)/src/Controls/Menu.cpp \
		$(GWENLIB)/src/Controls/MenuItem.cpp \
		$(GWENLIB)/src/Controls/MenuStrip.cpp \
		$(GWENLIB)/src/Controls/NumericUpDown.cpp \
		$(GWENLIB)/src/Controls/PageControl.cpp \
		$(GWENLIB)/src/Controls/ProgressBar.cpp \
		$(GWENLIB)/src/Controls/Properties.cpp \
		$(GWENLIB)/src/Controls/PropertyTree.cpp \
		$(GWENLIB)/src/Controls/RadioButtonController.cpp \
		$(GWENLIB)/src/Controls/RadioButton.cpp \
		$(GWENLIB)/src/Controls/Rectangle.cpp \
		$(GWENLIB)/src/Controls/ResizableControl.cpp \
		$(GWENLIB)/src/Controls/Resizer.cpp \
		$(GWENLIB)/src/Controls/RichLabel.cpp \
		$(GWENLIB)/src/Controls/ScrollBarBar.cpp \
		$(GWENLIB)/src/Controls/ScrollBarButton.cpp \
		$(GWENLIB)/src/Controls/ScrollBar.cpp \
		$(GWENLIB)/src/Controls/ScrollControl.cpp \
		$(GWENLIB)/src/Controls/Slider.cpp \
		$(GWENLIB)/src/Controls/SplitterBar.cpp \
		$(GWENLIB)/src/Controls/TabButton.cpp \
		$(GWENLIB)/src/Controls/TabControl.cpp \
		$(GWENLIB)/src/Controls/TabStrip.cpp \
		$(GWENLIB)/src/Controls/TextBox.cpp \
		$(GWENLIB)/src/Controls/TextBoxNumeric.cpp \
		$(GWENLIB)/src/Controls/Text.cpp \
		$(GWENLIB)/src/Controls/TreeControl.cpp \
		$(GWENLIB)/src/Controls/TreeNode.cpp \
		$(GWENLIB)/src/Controls/VerticalScrollBar.cpp \
		$(GWENLIB)/src/Controls/VerticalSlider.cpp \
		$(GWENLIB)/src/Controls/WindowCanvas.cpp \
		$(GWENLIB)/src/Controls/WindowControl.cpp
