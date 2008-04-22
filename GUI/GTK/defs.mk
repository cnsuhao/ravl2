# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/GUI/GTK/defs.mk"

#ifeq ($(ARC),sol2)
ifneq ($(filter $(ARC), sol2_7 sol2_9),)
# The solaris x11 header files a broken, so we need
# to turn off ansi flag and make the compiler more forgiving.
ANSIFLAG=-fpermissive
else
endif

PACKAGE = Ravl/GUI

LOCALHEADERS=WidgetDNDInfo.hh

HEADERS = Manager.hh Widget.hh GTKTypes.hh SignalInfo.hh \
 MouseEvent.hh Window.hh Cursor.hh ToolTips.hh CWidget.hh \
 Button.hh Pixmap.hh  OneChild.hh PackInfo.hh LBox.hh \
 Menu.hh Label.hh FileSelector.hh TextEntry.hh Slider.hh \
 ScrolledArea.hh Fixed.hh EventBox.hh Frame.hh ToggleButton.hh \
 StatusBar.hh Combo.hh List.hh MenuCheck.hh RawCanvas.hh Table.hh \
 Ruler.hh SpinButton.hh Tree.hh Separator.hh Bitmap.hh \
 Notebook.hh CList.hh VLabel.hh RadioButton.hh ProgressBar.hh \
 TextBox.hh TextView.hh DragAndDrop.hh Paned.hh MessageBox.hh WidgetStyle.hh \
 ReadBack.hh  WaitForExit.hh TreeModel.hh TreeStore.hh  TreeView.hh \
 ListStore.hh Pixbuf.hh AspectFrame.hh ButtonBox.hh  ColourSelector.hh \
 DebugAssertDialog.hh IconView.hh ComboBox.hh ComboBoxText.hh \
 ComboBoxEntry.hh ComboBoxEntryText.hh

SOURCES = Manager.cc Widget.cc MouseEvent.cc Window.cc \
 Cursor.cc ToolTips.cc CWidget.cc Button.cc Pixmap.cc \
 PackInfo.cc OneChild.cc LBox.cc Menu.cc Label.cc \
 FileSelector.cc TextEntry.cc Slider.cc ScrolledArea.cc \
 Fixed.cc EventBox.cc Frame.cc ToggleButton.cc StatusBar.cc \
 Combo.cc List.cc MenuCheck.cc RawCanvas.cc Table.cc \
 Ruler.cc SpinButton.cc Tree.cc Separator.cc Bitmap.cc \
 Notebook.cc CList.cc VLabel.cc RadioButton.cc ProgressBar.cc \
 TextBox.cc TextView.cc DragAndDrop.cc Paned.cc MessageBox.cc WidgetStyle.cc \
 ReadBack.cc WaitForExit.cc TreeModel.cc TreeStore.cc TreeView.cc \
 ListStore.cc Pixbuf.cc AspectFrame.cc ButtonBox.cc ColourSelector.cc \
 DebugAssertDialog.cc IconView.cc ComboBox.cc ComboBoxText.cc \
 ComboBoxEntry.cc ComboBoxEntryText.cc

MAINS = rdialog.cc

LOCAL_FILES = info.xpm

EXAMPLES = exButton.cc exMenu.cc exCList.cc exList.cc \
 exSlider.cc exRadioButton.cc exRuler.cc exWheel.cc \
 exNotebook.cc exCursor.cc exFixed.cc exTree.cc exTextBox.cc exTextView.cc \
 exMessageBox.cc exStyle.cc exLBox.cc exFrame.cc exScrolledArea.cc \
 exLabel.cc exTreeStore.cc exFileSelector.cc exCombo.cc exGUIThread.cc \
 exKeyboard.cc exPixmap.cc

#  exGUI.cc exCanvas.cc   exGraph1d.cc \

PLIB = RavlGUI

USESLIBS = RavlCore RavlOS GTK RavlThreads system

PROGLIBS = RavlImageIO RavlExtImgIO 

EHT = Ravl.API.GUI.Control.eht  Ravl.API.GUI.Layout.eht  Ravl.API.GUI.eht  Ravl.API.GUI.Internal.eht
#libRavlGUI.eht

HTML = tutorial.html

