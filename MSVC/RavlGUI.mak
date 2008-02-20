


#--------------------------
# Compiler and flags etc
#--------------------------
CC = cl.exe

LD = lib.exe

INCLUDES =  /I "include\Win32" /I "include" /I "c:/Program Files/Microsoft Visual Studio 8/VC/ATLMFC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/include" /I "c:/Program Files/Microsoft Visual Studio 8/SDK/v2.0/include" /I "C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\Include" /I "C:\GTKWIN32\lib\gtk-2.0\include" /I "C:\GTKWIN32\lib\glib-2.0\include" /I "C:\GTKWIN32\include\cairo" /I "C:\GTKWIN32\include\gtk-2.0" /I "C:\GTKWIN32\include\glib-2.0" /I "C:\GTKWIN32\include\pango-1.0" /I "C:\GTKWIN32\include\atk-1.0" 

DEFINES = /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2=1" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_SCL_SECURE=0" /D "_UNICODE" /D "UNICODE"


OPTFLAGS = /nologo /c /O2 /Ob1 /EHsc /MD /TP

DEBUGFLAGS = /nologo /c /Ob1 /EHsc /MD /TP

#-----------------------------------------------------------------------------
# OK lets define some of our output directories and define script to make them
#-----------------------------------------------------------------------------
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlGUI
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlGUI
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/Manager.obj $(OPTOBJDIR)/Widget.obj $(OPTOBJDIR)/MouseEvent.obj $(OPTOBJDIR)/Window.obj $(OPTOBJDIR)/Cursor.obj $(OPTOBJDIR)/ToolTips.obj $(OPTOBJDIR)/CWidget.obj $(OPTOBJDIR)/Button.obj $(OPTOBJDIR)/Pixmap.obj $(OPTOBJDIR)/PackInfo.obj $(OPTOBJDIR)/OneChild.obj $(OPTOBJDIR)/LBox.obj $(OPTOBJDIR)/Menu.obj $(OPTOBJDIR)/Label.obj $(OPTOBJDIR)/FileSelector.obj $(OPTOBJDIR)/TextEntry.obj $(OPTOBJDIR)/Slider.obj $(OPTOBJDIR)/ScrolledArea.obj $(OPTOBJDIR)/Fixed.obj $(OPTOBJDIR)/EventBox.obj $(OPTOBJDIR)/Frame.obj $(OPTOBJDIR)/ToggleButton.obj $(OPTOBJDIR)/StatusBar.obj $(OPTOBJDIR)/Combo.obj $(OPTOBJDIR)/List.obj $(OPTOBJDIR)/MenuCheck.obj $(OPTOBJDIR)/RawCanvas.obj $(OPTOBJDIR)/Table.obj $(OPTOBJDIR)/Ruler.obj $(OPTOBJDIR)/SpinButton.obj $(OPTOBJDIR)/Tree.obj $(OPTOBJDIR)/Separator.obj $(OPTOBJDIR)/Bitmap.obj $(OPTOBJDIR)/Notebook.obj $(OPTOBJDIR)/CList.obj $(OPTOBJDIR)/VLabel.obj $(OPTOBJDIR)/RadioButton.obj $(OPTOBJDIR)/ProgressBar.obj $(OPTOBJDIR)/TextBox.obj $(OPTOBJDIR)/DragAndDrop.obj $(OPTOBJDIR)/Paned.obj $(OPTOBJDIR)/MessageBox.obj $(OPTOBJDIR)/WidgetStyle.obj $(OPTOBJDIR)/ReadBack.obj $(OPTOBJDIR)/WaitForExit.obj $(OPTOBJDIR)/TreeModel.obj $(OPTOBJDIR)/TreeStore.obj $(OPTOBJDIR)/TreeView.obj $(OPTOBJDIR)/ListStore.obj $(OPTOBJDIR)/Pixbuf.obj $(OPTOBJDIR)/AspectFrame.obj $(OPTOBJDIR)/ButtonBox.obj $(OPTOBJDIR)/ColourSelector.obj $(OPTOBJDIR)/DebugAssertDialog.obj $(OPTOBJDIR)/IconView.obj
	@echo -- making $(OPTLIBDIR)/RavlGUI.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlGUI.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/Manager.obj $(DEBUGOBJDIR)/Widget.obj $(DEBUGOBJDIR)/MouseEvent.obj $(DEBUGOBJDIR)/Window.obj $(DEBUGOBJDIR)/Cursor.obj $(DEBUGOBJDIR)/ToolTips.obj $(DEBUGOBJDIR)/CWidget.obj $(DEBUGOBJDIR)/Button.obj $(DEBUGOBJDIR)/Pixmap.obj $(DEBUGOBJDIR)/PackInfo.obj $(DEBUGOBJDIR)/OneChild.obj $(DEBUGOBJDIR)/LBox.obj $(DEBUGOBJDIR)/Menu.obj $(DEBUGOBJDIR)/Label.obj $(DEBUGOBJDIR)/FileSelector.obj $(DEBUGOBJDIR)/TextEntry.obj $(DEBUGOBJDIR)/Slider.obj $(DEBUGOBJDIR)/ScrolledArea.obj $(DEBUGOBJDIR)/Fixed.obj $(DEBUGOBJDIR)/EventBox.obj $(DEBUGOBJDIR)/Frame.obj $(DEBUGOBJDIR)/ToggleButton.obj $(DEBUGOBJDIR)/StatusBar.obj $(DEBUGOBJDIR)/Combo.obj $(DEBUGOBJDIR)/List.obj $(DEBUGOBJDIR)/MenuCheck.obj $(DEBUGOBJDIR)/RawCanvas.obj $(DEBUGOBJDIR)/Table.obj $(DEBUGOBJDIR)/Ruler.obj $(DEBUGOBJDIR)/SpinButton.obj $(DEBUGOBJDIR)/Tree.obj $(DEBUGOBJDIR)/Separator.obj $(DEBUGOBJDIR)/Bitmap.obj $(DEBUGOBJDIR)/Notebook.obj $(DEBUGOBJDIR)/CList.obj $(DEBUGOBJDIR)/VLabel.obj $(DEBUGOBJDIR)/RadioButton.obj $(DEBUGOBJDIR)/ProgressBar.obj $(DEBUGOBJDIR)/TextBox.obj $(DEBUGOBJDIR)/DragAndDrop.obj $(DEBUGOBJDIR)/Paned.obj $(DEBUGOBJDIR)/MessageBox.obj $(DEBUGOBJDIR)/WidgetStyle.obj $(DEBUGOBJDIR)/ReadBack.obj $(DEBUGOBJDIR)/WaitForExit.obj $(DEBUGOBJDIR)/TreeModel.obj $(DEBUGOBJDIR)/TreeStore.obj $(DEBUGOBJDIR)/TreeView.obj $(DEBUGOBJDIR)/ListStore.obj $(DEBUGOBJDIR)/Pixbuf.obj $(DEBUGOBJDIR)/AspectFrame.obj $(DEBUGOBJDIR)/ButtonBox.obj $(DEBUGOBJDIR)/ColourSelector.obj $(DEBUGOBJDIR)/DebugAssertDialog.obj $(DEBUGOBJDIR)/IconView.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlGUI.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlGUI.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlGUI
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/Manager.obj: .././GUI/GTK/Manager.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Manager.obj .././GUI/GTK/Manager.cc

$(DEBUGOBJDIR)/Manager.obj: .././GUI/GTK/Manager.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Manager.obj .././GUI/GTK/Manager.cc

$(OPTOBJDIR)/Widget.obj: .././GUI/GTK/Widget.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Widget.obj .././GUI/GTK/Widget.cc

$(DEBUGOBJDIR)/Widget.obj: .././GUI/GTK/Widget.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Widget.obj .././GUI/GTK/Widget.cc

$(OPTOBJDIR)/MouseEvent.obj: .././GUI/GTK/MouseEvent.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MouseEvent.obj .././GUI/GTK/MouseEvent.cc

$(DEBUGOBJDIR)/MouseEvent.obj: .././GUI/GTK/MouseEvent.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MouseEvent.obj .././GUI/GTK/MouseEvent.cc

$(OPTOBJDIR)/Window.obj: .././GUI/GTK/Window.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Window.obj .././GUI/GTK/Window.cc

$(DEBUGOBJDIR)/Window.obj: .././GUI/GTK/Window.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Window.obj .././GUI/GTK/Window.cc

$(OPTOBJDIR)/Cursor.obj: .././GUI/GTK/Cursor.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Cursor.obj .././GUI/GTK/Cursor.cc

$(DEBUGOBJDIR)/Cursor.obj: .././GUI/GTK/Cursor.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Cursor.obj .././GUI/GTK/Cursor.cc

$(OPTOBJDIR)/ToolTips.obj: .././GUI/GTK/ToolTips.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ToolTips.obj .././GUI/GTK/ToolTips.cc

$(DEBUGOBJDIR)/ToolTips.obj: .././GUI/GTK/ToolTips.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ToolTips.obj .././GUI/GTK/ToolTips.cc

$(OPTOBJDIR)/CWidget.obj: .././GUI/GTK/CWidget.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/CWidget.obj .././GUI/GTK/CWidget.cc

$(DEBUGOBJDIR)/CWidget.obj: .././GUI/GTK/CWidget.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/CWidget.obj .././GUI/GTK/CWidget.cc

$(OPTOBJDIR)/Button.obj: .././GUI/GTK/Button.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Button.obj .././GUI/GTK/Button.cc

$(DEBUGOBJDIR)/Button.obj: .././GUI/GTK/Button.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Button.obj .././GUI/GTK/Button.cc

$(OPTOBJDIR)/Pixmap.obj: .././GUI/GTK/Pixmap.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Pixmap.obj .././GUI/GTK/Pixmap.cc

$(DEBUGOBJDIR)/Pixmap.obj: .././GUI/GTK/Pixmap.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Pixmap.obj .././GUI/GTK/Pixmap.cc

$(OPTOBJDIR)/PackInfo.obj: .././GUI/GTK/PackInfo.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PackInfo.obj .././GUI/GTK/PackInfo.cc

$(DEBUGOBJDIR)/PackInfo.obj: .././GUI/GTK/PackInfo.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PackInfo.obj .././GUI/GTK/PackInfo.cc

$(OPTOBJDIR)/OneChild.obj: .././GUI/GTK/OneChild.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/OneChild.obj .././GUI/GTK/OneChild.cc

$(DEBUGOBJDIR)/OneChild.obj: .././GUI/GTK/OneChild.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/OneChild.obj .././GUI/GTK/OneChild.cc

$(OPTOBJDIR)/LBox.obj: .././GUI/GTK/LBox.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LBox.obj .././GUI/GTK/LBox.cc

$(DEBUGOBJDIR)/LBox.obj: .././GUI/GTK/LBox.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LBox.obj .././GUI/GTK/LBox.cc

$(OPTOBJDIR)/Menu.obj: .././GUI/GTK/Menu.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Menu.obj .././GUI/GTK/Menu.cc

$(DEBUGOBJDIR)/Menu.obj: .././GUI/GTK/Menu.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Menu.obj .././GUI/GTK/Menu.cc

$(OPTOBJDIR)/Label.obj: .././GUI/GTK/Label.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Label.obj .././GUI/GTK/Label.cc

$(DEBUGOBJDIR)/Label.obj: .././GUI/GTK/Label.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Label.obj .././GUI/GTK/Label.cc

$(OPTOBJDIR)/FileSelector.obj: .././GUI/GTK/FileSelector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FileSelector.obj .././GUI/GTK/FileSelector.cc

$(DEBUGOBJDIR)/FileSelector.obj: .././GUI/GTK/FileSelector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FileSelector.obj .././GUI/GTK/FileSelector.cc

$(OPTOBJDIR)/TextEntry.obj: .././GUI/GTK/TextEntry.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TextEntry.obj .././GUI/GTK/TextEntry.cc

$(DEBUGOBJDIR)/TextEntry.obj: .././GUI/GTK/TextEntry.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TextEntry.obj .././GUI/GTK/TextEntry.cc

$(OPTOBJDIR)/Slider.obj: .././GUI/GTK/Slider.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Slider.obj .././GUI/GTK/Slider.cc

$(DEBUGOBJDIR)/Slider.obj: .././GUI/GTK/Slider.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Slider.obj .././GUI/GTK/Slider.cc

$(OPTOBJDIR)/ScrolledArea.obj: .././GUI/GTK/ScrolledArea.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ScrolledArea.obj .././GUI/GTK/ScrolledArea.cc

$(DEBUGOBJDIR)/ScrolledArea.obj: .././GUI/GTK/ScrolledArea.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ScrolledArea.obj .././GUI/GTK/ScrolledArea.cc

$(OPTOBJDIR)/Fixed.obj: .././GUI/GTK/Fixed.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Fixed.obj .././GUI/GTK/Fixed.cc

$(DEBUGOBJDIR)/Fixed.obj: .././GUI/GTK/Fixed.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Fixed.obj .././GUI/GTK/Fixed.cc

$(OPTOBJDIR)/EventBox.obj: .././GUI/GTK/EventBox.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/EventBox.obj .././GUI/GTK/EventBox.cc

$(DEBUGOBJDIR)/EventBox.obj: .././GUI/GTK/EventBox.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/EventBox.obj .././GUI/GTK/EventBox.cc

$(OPTOBJDIR)/Frame.obj: .././GUI/GTK/Frame.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Frame.obj .././GUI/GTK/Frame.cc

$(DEBUGOBJDIR)/Frame.obj: .././GUI/GTK/Frame.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Frame.obj .././GUI/GTK/Frame.cc

$(OPTOBJDIR)/ToggleButton.obj: .././GUI/GTK/ToggleButton.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ToggleButton.obj .././GUI/GTK/ToggleButton.cc

$(DEBUGOBJDIR)/ToggleButton.obj: .././GUI/GTK/ToggleButton.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ToggleButton.obj .././GUI/GTK/ToggleButton.cc

$(OPTOBJDIR)/StatusBar.obj: .././GUI/GTK/StatusBar.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/StatusBar.obj .././GUI/GTK/StatusBar.cc

$(DEBUGOBJDIR)/StatusBar.obj: .././GUI/GTK/StatusBar.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/StatusBar.obj .././GUI/GTK/StatusBar.cc

$(OPTOBJDIR)/Combo.obj: .././GUI/GTK/Combo.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Combo.obj .././GUI/GTK/Combo.cc

$(DEBUGOBJDIR)/Combo.obj: .././GUI/GTK/Combo.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Combo.obj .././GUI/GTK/Combo.cc

$(OPTOBJDIR)/List.obj: .././GUI/GTK/List.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/List.obj .././GUI/GTK/List.cc

$(DEBUGOBJDIR)/List.obj: .././GUI/GTK/List.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/List.obj .././GUI/GTK/List.cc

$(OPTOBJDIR)/MenuCheck.obj: .././GUI/GTK/MenuCheck.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MenuCheck.obj .././GUI/GTK/MenuCheck.cc

$(DEBUGOBJDIR)/MenuCheck.obj: .././GUI/GTK/MenuCheck.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MenuCheck.obj .././GUI/GTK/MenuCheck.cc

$(OPTOBJDIR)/RawCanvas.obj: .././GUI/GTK/RawCanvas.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RawCanvas.obj .././GUI/GTK/RawCanvas.cc

$(DEBUGOBJDIR)/RawCanvas.obj: .././GUI/GTK/RawCanvas.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RawCanvas.obj .././GUI/GTK/RawCanvas.cc

$(OPTOBJDIR)/Table.obj: .././GUI/GTK/Table.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Table.obj .././GUI/GTK/Table.cc

$(DEBUGOBJDIR)/Table.obj: .././GUI/GTK/Table.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Table.obj .././GUI/GTK/Table.cc

$(OPTOBJDIR)/Ruler.obj: .././GUI/GTK/Ruler.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Ruler.obj .././GUI/GTK/Ruler.cc

$(DEBUGOBJDIR)/Ruler.obj: .././GUI/GTK/Ruler.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Ruler.obj .././GUI/GTK/Ruler.cc

$(OPTOBJDIR)/SpinButton.obj: .././GUI/GTK/SpinButton.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SpinButton.obj .././GUI/GTK/SpinButton.cc

$(DEBUGOBJDIR)/SpinButton.obj: .././GUI/GTK/SpinButton.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SpinButton.obj .././GUI/GTK/SpinButton.cc

$(OPTOBJDIR)/Tree.obj: .././GUI/GTK/Tree.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Tree.obj .././GUI/GTK/Tree.cc

$(DEBUGOBJDIR)/Tree.obj: .././GUI/GTK/Tree.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Tree.obj .././GUI/GTK/Tree.cc

$(OPTOBJDIR)/Separator.obj: .././GUI/GTK/Separator.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Separator.obj .././GUI/GTK/Separator.cc

$(DEBUGOBJDIR)/Separator.obj: .././GUI/GTK/Separator.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Separator.obj .././GUI/GTK/Separator.cc

$(OPTOBJDIR)/Bitmap.obj: .././GUI/GTK/Bitmap.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Bitmap.obj .././GUI/GTK/Bitmap.cc

$(DEBUGOBJDIR)/Bitmap.obj: .././GUI/GTK/Bitmap.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Bitmap.obj .././GUI/GTK/Bitmap.cc

$(OPTOBJDIR)/Notebook.obj: .././GUI/GTK/Notebook.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Notebook.obj .././GUI/GTK/Notebook.cc

$(DEBUGOBJDIR)/Notebook.obj: .././GUI/GTK/Notebook.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Notebook.obj .././GUI/GTK/Notebook.cc

$(OPTOBJDIR)/CList.obj: .././GUI/GTK/CList.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/CList.obj .././GUI/GTK/CList.cc

$(DEBUGOBJDIR)/CList.obj: .././GUI/GTK/CList.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/CList.obj .././GUI/GTK/CList.cc

$(OPTOBJDIR)/VLabel.obj: .././GUI/GTK/VLabel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/VLabel.obj .././GUI/GTK/VLabel.cc

$(DEBUGOBJDIR)/VLabel.obj: .././GUI/GTK/VLabel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/VLabel.obj .././GUI/GTK/VLabel.cc

$(OPTOBJDIR)/RadioButton.obj: .././GUI/GTK/RadioButton.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RadioButton.obj .././GUI/GTK/RadioButton.cc

$(DEBUGOBJDIR)/RadioButton.obj: .././GUI/GTK/RadioButton.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RadioButton.obj .././GUI/GTK/RadioButton.cc

$(OPTOBJDIR)/ProgressBar.obj: .././GUI/GTK/ProgressBar.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ProgressBar.obj .././GUI/GTK/ProgressBar.cc

$(DEBUGOBJDIR)/ProgressBar.obj: .././GUI/GTK/ProgressBar.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ProgressBar.obj .././GUI/GTK/ProgressBar.cc

$(OPTOBJDIR)/TextBox.obj: .././GUI/GTK/TextBox.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TextBox.obj .././GUI/GTK/TextBox.cc

$(DEBUGOBJDIR)/TextBox.obj: .././GUI/GTK/TextBox.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TextBox.obj .././GUI/GTK/TextBox.cc

$(OPTOBJDIR)/DragAndDrop.obj: .././GUI/GTK/DragAndDrop.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DragAndDrop.obj .././GUI/GTK/DragAndDrop.cc

$(DEBUGOBJDIR)/DragAndDrop.obj: .././GUI/GTK/DragAndDrop.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DragAndDrop.obj .././GUI/GTK/DragAndDrop.cc

$(OPTOBJDIR)/Paned.obj: .././GUI/GTK/Paned.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Paned.obj .././GUI/GTK/Paned.cc

$(DEBUGOBJDIR)/Paned.obj: .././GUI/GTK/Paned.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Paned.obj .././GUI/GTK/Paned.cc

$(OPTOBJDIR)/MessageBox.obj: .././GUI/GTK/MessageBox.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MessageBox.obj .././GUI/GTK/MessageBox.cc

$(DEBUGOBJDIR)/MessageBox.obj: .././GUI/GTK/MessageBox.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MessageBox.obj .././GUI/GTK/MessageBox.cc

$(OPTOBJDIR)/WidgetStyle.obj: .././GUI/GTK/WidgetStyle.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/WidgetStyle.obj .././GUI/GTK/WidgetStyle.cc

$(DEBUGOBJDIR)/WidgetStyle.obj: .././GUI/GTK/WidgetStyle.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/WidgetStyle.obj .././GUI/GTK/WidgetStyle.cc

$(OPTOBJDIR)/ReadBack.obj: .././GUI/GTK/ReadBack.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ReadBack.obj .././GUI/GTK/ReadBack.cc

$(DEBUGOBJDIR)/ReadBack.obj: .././GUI/GTK/ReadBack.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ReadBack.obj .././GUI/GTK/ReadBack.cc

$(OPTOBJDIR)/WaitForExit.obj: .././GUI/GTK/WaitForExit.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/WaitForExit.obj .././GUI/GTK/WaitForExit.cc

$(DEBUGOBJDIR)/WaitForExit.obj: .././GUI/GTK/WaitForExit.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/WaitForExit.obj .././GUI/GTK/WaitForExit.cc

$(OPTOBJDIR)/TreeModel.obj: .././GUI/GTK/TreeModel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TreeModel.obj .././GUI/GTK/TreeModel.cc

$(DEBUGOBJDIR)/TreeModel.obj: .././GUI/GTK/TreeModel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TreeModel.obj .././GUI/GTK/TreeModel.cc

$(OPTOBJDIR)/TreeStore.obj: .././GUI/GTK/TreeStore.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TreeStore.obj .././GUI/GTK/TreeStore.cc

$(DEBUGOBJDIR)/TreeStore.obj: .././GUI/GTK/TreeStore.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TreeStore.obj .././GUI/GTK/TreeStore.cc

$(OPTOBJDIR)/TreeView.obj: .././GUI/GTK/TreeView.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TreeView.obj .././GUI/GTK/TreeView.cc

$(DEBUGOBJDIR)/TreeView.obj: .././GUI/GTK/TreeView.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TreeView.obj .././GUI/GTK/TreeView.cc

$(OPTOBJDIR)/ListStore.obj: .././GUI/GTK/ListStore.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ListStore.obj .././GUI/GTK/ListStore.cc

$(DEBUGOBJDIR)/ListStore.obj: .././GUI/GTK/ListStore.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ListStore.obj .././GUI/GTK/ListStore.cc

$(OPTOBJDIR)/Pixbuf.obj: .././GUI/GTK/Pixbuf.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Pixbuf.obj .././GUI/GTK/Pixbuf.cc

$(DEBUGOBJDIR)/Pixbuf.obj: .././GUI/GTK/Pixbuf.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Pixbuf.obj .././GUI/GTK/Pixbuf.cc

$(OPTOBJDIR)/AspectFrame.obj: .././GUI/GTK/AspectFrame.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AspectFrame.obj .././GUI/GTK/AspectFrame.cc

$(DEBUGOBJDIR)/AspectFrame.obj: .././GUI/GTK/AspectFrame.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AspectFrame.obj .././GUI/GTK/AspectFrame.cc

$(OPTOBJDIR)/ButtonBox.obj: .././GUI/GTK/ButtonBox.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ButtonBox.obj .././GUI/GTK/ButtonBox.cc

$(DEBUGOBJDIR)/ButtonBox.obj: .././GUI/GTK/ButtonBox.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ButtonBox.obj .././GUI/GTK/ButtonBox.cc

$(OPTOBJDIR)/ColourSelector.obj: .././GUI/GTK/ColourSelector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ColourSelector.obj .././GUI/GTK/ColourSelector.cc

$(DEBUGOBJDIR)/ColourSelector.obj: .././GUI/GTK/ColourSelector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ColourSelector.obj .././GUI/GTK/ColourSelector.cc

$(OPTOBJDIR)/DebugAssertDialog.obj: .././GUI/GTK/DebugAssertDialog.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DebugAssertDialog.obj .././GUI/GTK/DebugAssertDialog.cc

$(DEBUGOBJDIR)/DebugAssertDialog.obj: .././GUI/GTK/DebugAssertDialog.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DebugAssertDialog.obj .././GUI/GTK/DebugAssertDialog.cc

$(OPTOBJDIR)/IconView.obj: .././GUI/GTK/IconView.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/IconView.obj .././GUI/GTK/IconView.cc

$(DEBUGOBJDIR)/IconView.obj: .././GUI/GTK/IconView.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/IconView.obj .././GUI/GTK/IconView.cc


