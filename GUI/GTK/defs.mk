# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#########################################
# $Id$
#! rcsid="$Id$"

PACKAGE = Ravl/GUI

SUPPORT_ONLY = linux sol2 sgi

HEADERS = Manager.hh Widget.hh GTKTypes.hh SignalInfo.hh \
 MouseEvent.hh Window.hh Cursor.hh ToolTips.hh CWidget.hh \
 Button.hh Pixmap.hh  OneChild.hh PackInfo.hh LBox.hh \
 Menu.hh Label.hh FileSelector.hh TextEntry.hh Slider.hh \
 ScrolledArea.hh Fixed.hh EventBox.hh Frame.hh ToggleButton.hh \
 StatusBar.hh Combo.hh List.hh MenuCheck.hh RawCanvas.hh Table.hh \
 Ruler.hh SpinButton.hh Tree.hh Separator.hh Bitmap.hh \
 Notebook.hh CList.hh VLabel.hh RadioButton.hh ProgressBar.hh 

# TextBox.hh

SOURCES = Manager.cc Widget.cc MouseEvent.cc Window.cc \
 Cursor.cc ToolTips.cc CWidget.cc Button.cc Pixmap.cc \
 PackInfo.cc OneChild.cc LBox.cc Menu.cc Label.cc \
 FileSelector.cc TextEntry.cc Slider.cc ScrolledArea.cc \
 Fixed.cc EventBox.cc Frame.cc ToggleButton.cc StatusBar.cc \
 Combo.cc List.cc MenuCheck.cc RawCanvas.cc Table.cc \
 Ruler.cc SpinButton.cc Tree.cc Separator.cc Bitmap.cc \
 Notebook.cc CList.cc VLabel.cc RadioButton.cc ProgressBar.cc

# TextBox.cc

MAINS = 

LOCAL_FILES = info.xpm

EXAMPLES = exButton.cc exMenu.cc exCList.cc exList.cc \
 exSlider.cc exRadioButton.cc exRuler.cc exWheel.cc \
 exNotebook.cc exCursor.cc exFixed.cc exTree.cc

#  exGUI.cc exCanvas.cc   exGraph1d.cc \

PLIB = RavlGUI

USESLIBS = RavlCore RavlOS GTK RavlThreads

PROGLIBS = 

EHT = Ravl.GUI.Control.eht  Ravl.GUI.Layout.eht  Ravl.GUI.eht  Ravl.GUI.Internal.eht
#libRavlGUI.eht
