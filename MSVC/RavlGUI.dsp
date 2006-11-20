# Microsoft Developer Studio Project File - Name="RavlGUI" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlGUI - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlGUI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlGUI.mak" CFG="RavlGUI - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlGUI - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlGUI - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlGUI"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\GTKWIN32\include\gtk-2.0\" /I "C:\GTKWIN32\include\glib-2.0\" /I "C:\GTKWIN32\include\pango-1.0\" /I "C:\GTKWIN32\include\atk-1.0\" /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlGUI"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /MDd  /I "C:\GTKWIN32\include\gtk-2.0\" /I "C:\GTKWIN32\include\glib-2.0\" /I "C:\GTKWIN32\include\pango-1.0\" /I "C:\GTKWIN32\include\atk-1.0\" /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "_DEBUG" /D "VISUAL_CPP" /D "_LIB" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /GZ /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "RavlGUI - Win32 Release"
# Name "RavlGUI - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\GUI\GTK\Manager.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Widget.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\MouseEvent.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Window.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Cursor.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\ToolTips.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\CWidget.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Button.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Pixmap.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\PackInfo.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\OneChild.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\LBox.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Menu.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Label.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\FileSelector.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\TextEntry.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Slider.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\ScrolledArea.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Fixed.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\EventBox.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Frame.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\ToggleButton.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\StatusBar.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Combo.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\List.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\MenuCheck.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\RawCanvas.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Table.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Ruler.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\SpinButton.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Tree.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Separator.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Bitmap.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Notebook.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\CList.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\VLabel.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\RadioButton.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\ProgressBar.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\TextBox.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\DragAndDrop.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Paned.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\MessageBox.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\WidgetStyle.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\ReadBack.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\WaitForExit.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\TreeModel.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\TreeStore.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\TreeView.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\ListStore.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Pixbuf.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\AspectFrame.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\ButtonBox.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\ColourSelector.cc
# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\DebugAssertDialog.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\GUI\GTK\Manager.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header Manager.hh

"C:\Build\inc\Ravl\GUI\Manager.hh" :  "" ""
	copy ..\.\GUI\GTK\Manager.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header Manager.hh

"C:\Build\inc\Ravl\GUI\Manager.hh" :  "" ""
	copy ..\.\GUI\GTK\Manager.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Widget.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header Widget.hh

"C:\Build\inc\Ravl\GUI\Widget.hh" :  "" ""
	copy ..\.\GUI\GTK\Widget.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header Widget.hh

"C:\Build\inc\Ravl\GUI\Widget.hh" :  "" ""
	copy ..\.\GUI\GTK\Widget.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\GTKTypes.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header GTKTypes.hh

"C:\Build\inc\Ravl\GUI\GTKTypes.hh" :  "" ""
	copy ..\.\GUI\GTK\GTKTypes.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header GTKTypes.hh

"C:\Build\inc\Ravl\GUI\GTKTypes.hh" :  "" ""
	copy ..\.\GUI\GTK\GTKTypes.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\SignalInfo.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header SignalInfo.hh

"C:\Build\inc\Ravl\GUI\SignalInfo.hh" :  "" ""
	copy ..\.\GUI\GTK\SignalInfo.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header SignalInfo.hh

"C:\Build\inc\Ravl\GUI\SignalInfo.hh" :  "" ""
	copy ..\.\GUI\GTK\SignalInfo.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\MouseEvent.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header MouseEvent.hh

"C:\Build\inc\Ravl\GUI\MouseEvent.hh" :  "" ""
	copy ..\.\GUI\GTK\MouseEvent.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header MouseEvent.hh

"C:\Build\inc\Ravl\GUI\MouseEvent.hh" :  "" ""
	copy ..\.\GUI\GTK\MouseEvent.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Window.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header Window.hh

"C:\Build\inc\Ravl\GUI\Window.hh" :  "" ""
	copy ..\.\GUI\GTK\Window.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header Window.hh

"C:\Build\inc\Ravl\GUI\Window.hh" :  "" ""
	copy ..\.\GUI\GTK\Window.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Cursor.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header Cursor.hh

"C:\Build\inc\Ravl\GUI\Cursor.hh" :  "" ""
	copy ..\.\GUI\GTK\Cursor.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header Cursor.hh

"C:\Build\inc\Ravl\GUI\Cursor.hh" :  "" ""
	copy ..\.\GUI\GTK\Cursor.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\ToolTips.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header ToolTips.hh

"C:\Build\inc\Ravl\GUI\ToolTips.hh" :  "" ""
	copy ..\.\GUI\GTK\ToolTips.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header ToolTips.hh

"C:\Build\inc\Ravl\GUI\ToolTips.hh" :  "" ""
	copy ..\.\GUI\GTK\ToolTips.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\CWidget.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header CWidget.hh

"C:\Build\inc\Ravl\GUI\CWidget.hh" :  "" ""
	copy ..\.\GUI\GTK\CWidget.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header CWidget.hh

"C:\Build\inc\Ravl\GUI\CWidget.hh" :  "" ""
	copy ..\.\GUI\GTK\CWidget.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Button.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header Button.hh

"C:\Build\inc\Ravl\GUI\Button.hh" :  "" ""
	copy ..\.\GUI\GTK\Button.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header Button.hh

"C:\Build\inc\Ravl\GUI\Button.hh" :  "" ""
	copy ..\.\GUI\GTK\Button.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Pixmap.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header Pixmap.hh

"C:\Build\inc\Ravl\GUI\Pixmap.hh" :  "" ""
	copy ..\.\GUI\GTK\Pixmap.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header Pixmap.hh

"C:\Build\inc\Ravl\GUI\Pixmap.hh" :  "" ""
	copy ..\.\GUI\GTK\Pixmap.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\OneChild.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header OneChild.hh

"C:\Build\inc\Ravl\GUI\OneChild.hh" :  "" ""
	copy ..\.\GUI\GTK\OneChild.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header OneChild.hh

"C:\Build\inc\Ravl\GUI\OneChild.hh" :  "" ""
	copy ..\.\GUI\GTK\OneChild.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\PackInfo.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header PackInfo.hh

"C:\Build\inc\Ravl\GUI\PackInfo.hh" :  "" ""
	copy ..\.\GUI\GTK\PackInfo.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header PackInfo.hh

"C:\Build\inc\Ravl\GUI\PackInfo.hh" :  "" ""
	copy ..\.\GUI\GTK\PackInfo.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\LBox.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header LBox.hh

"C:\Build\inc\Ravl\GUI\LBox.hh" :  "" ""
	copy ..\.\GUI\GTK\LBox.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header LBox.hh

"C:\Build\inc\Ravl\GUI\LBox.hh" :  "" ""
	copy ..\.\GUI\GTK\LBox.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Menu.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header Menu.hh

"C:\Build\inc\Ravl\GUI\Menu.hh" :  "" ""
	copy ..\.\GUI\GTK\Menu.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header Menu.hh

"C:\Build\inc\Ravl\GUI\Menu.hh" :  "" ""
	copy ..\.\GUI\GTK\Menu.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Label.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header Label.hh

"C:\Build\inc\Ravl\GUI\Label.hh" :  "" ""
	copy ..\.\GUI\GTK\Label.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header Label.hh

"C:\Build\inc\Ravl\GUI\Label.hh" :  "" ""
	copy ..\.\GUI\GTK\Label.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\FileSelector.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header FileSelector.hh

"C:\Build\inc\Ravl\GUI\FileSelector.hh" :  "" ""
	copy ..\.\GUI\GTK\FileSelector.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header FileSelector.hh

"C:\Build\inc\Ravl\GUI\FileSelector.hh" :  "" ""
	copy ..\.\GUI\GTK\FileSelector.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\TextEntry.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header TextEntry.hh

"C:\Build\inc\Ravl\GUI\TextEntry.hh" :  "" ""
	copy ..\.\GUI\GTK\TextEntry.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header TextEntry.hh

"C:\Build\inc\Ravl\GUI\TextEntry.hh" :  "" ""
	copy ..\.\GUI\GTK\TextEntry.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Slider.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header Slider.hh

"C:\Build\inc\Ravl\GUI\Slider.hh" :  "" ""
	copy ..\.\GUI\GTK\Slider.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header Slider.hh

"C:\Build\inc\Ravl\GUI\Slider.hh" :  "" ""
	copy ..\.\GUI\GTK\Slider.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\ScrolledArea.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header ScrolledArea.hh

"C:\Build\inc\Ravl\GUI\ScrolledArea.hh" :  "" ""
	copy ..\.\GUI\GTK\ScrolledArea.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header ScrolledArea.hh

"C:\Build\inc\Ravl\GUI\ScrolledArea.hh" :  "" ""
	copy ..\.\GUI\GTK\ScrolledArea.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Fixed.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header Fixed.hh

"C:\Build\inc\Ravl\GUI\Fixed.hh" :  "" ""
	copy ..\.\GUI\GTK\Fixed.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header Fixed.hh

"C:\Build\inc\Ravl\GUI\Fixed.hh" :  "" ""
	copy ..\.\GUI\GTK\Fixed.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\EventBox.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header EventBox.hh

"C:\Build\inc\Ravl\GUI\EventBox.hh" :  "" ""
	copy ..\.\GUI\GTK\EventBox.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header EventBox.hh

"C:\Build\inc\Ravl\GUI\EventBox.hh" :  "" ""
	copy ..\.\GUI\GTK\EventBox.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Frame.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header Frame.hh

"C:\Build\inc\Ravl\GUI\Frame.hh" :  "" ""
	copy ..\.\GUI\GTK\Frame.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header Frame.hh

"C:\Build\inc\Ravl\GUI\Frame.hh" :  "" ""
	copy ..\.\GUI\GTK\Frame.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\ToggleButton.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header ToggleButton.hh

"C:\Build\inc\Ravl\GUI\ToggleButton.hh" :  "" ""
	copy ..\.\GUI\GTK\ToggleButton.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header ToggleButton.hh

"C:\Build\inc\Ravl\GUI\ToggleButton.hh" :  "" ""
	copy ..\.\GUI\GTK\ToggleButton.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\StatusBar.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header StatusBar.hh

"C:\Build\inc\Ravl\GUI\StatusBar.hh" :  "" ""
	copy ..\.\GUI\GTK\StatusBar.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header StatusBar.hh

"C:\Build\inc\Ravl\GUI\StatusBar.hh" :  "" ""
	copy ..\.\GUI\GTK\StatusBar.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Combo.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header Combo.hh

"C:\Build\inc\Ravl\GUI\Combo.hh" :  "" ""
	copy ..\.\GUI\GTK\Combo.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header Combo.hh

"C:\Build\inc\Ravl\GUI\Combo.hh" :  "" ""
	copy ..\.\GUI\GTK\Combo.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\List.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header List.hh

"C:\Build\inc\Ravl\GUI\List.hh" :  "" ""
	copy ..\.\GUI\GTK\List.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header List.hh

"C:\Build\inc\Ravl\GUI\List.hh" :  "" ""
	copy ..\.\GUI\GTK\List.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\MenuCheck.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header MenuCheck.hh

"C:\Build\inc\Ravl\GUI\MenuCheck.hh" :  "" ""
	copy ..\.\GUI\GTK\MenuCheck.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header MenuCheck.hh

"C:\Build\inc\Ravl\GUI\MenuCheck.hh" :  "" ""
	copy ..\.\GUI\GTK\MenuCheck.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\RawCanvas.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header RawCanvas.hh

"C:\Build\inc\Ravl\GUI\RawCanvas.hh" :  "" ""
	copy ..\.\GUI\GTK\RawCanvas.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header RawCanvas.hh

"C:\Build\inc\Ravl\GUI\RawCanvas.hh" :  "" ""
	copy ..\.\GUI\GTK\RawCanvas.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Table.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header Table.hh

"C:\Build\inc\Ravl\GUI\Table.hh" :  "" ""
	copy ..\.\GUI\GTK\Table.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header Table.hh

"C:\Build\inc\Ravl\GUI\Table.hh" :  "" ""
	copy ..\.\GUI\GTK\Table.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Ruler.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header Ruler.hh

"C:\Build\inc\Ravl\GUI\Ruler.hh" :  "" ""
	copy ..\.\GUI\GTK\Ruler.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header Ruler.hh

"C:\Build\inc\Ravl\GUI\Ruler.hh" :  "" ""
	copy ..\.\GUI\GTK\Ruler.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\SpinButton.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header SpinButton.hh

"C:\Build\inc\Ravl\GUI\SpinButton.hh" :  "" ""
	copy ..\.\GUI\GTK\SpinButton.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header SpinButton.hh

"C:\Build\inc\Ravl\GUI\SpinButton.hh" :  "" ""
	copy ..\.\GUI\GTK\SpinButton.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Tree.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header Tree.hh

"C:\Build\inc\Ravl\GUI\Tree.hh" :  "" ""
	copy ..\.\GUI\GTK\Tree.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header Tree.hh

"C:\Build\inc\Ravl\GUI\Tree.hh" :  "" ""
	copy ..\.\GUI\GTK\Tree.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Separator.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header Separator.hh

"C:\Build\inc\Ravl\GUI\Separator.hh" :  "" ""
	copy ..\.\GUI\GTK\Separator.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header Separator.hh

"C:\Build\inc\Ravl\GUI\Separator.hh" :  "" ""
	copy ..\.\GUI\GTK\Separator.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Bitmap.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header Bitmap.hh

"C:\Build\inc\Ravl\GUI\Bitmap.hh" :  "" ""
	copy ..\.\GUI\GTK\Bitmap.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header Bitmap.hh

"C:\Build\inc\Ravl\GUI\Bitmap.hh" :  "" ""
	copy ..\.\GUI\GTK\Bitmap.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Notebook.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header Notebook.hh

"C:\Build\inc\Ravl\GUI\Notebook.hh" :  "" ""
	copy ..\.\GUI\GTK\Notebook.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header Notebook.hh

"C:\Build\inc\Ravl\GUI\Notebook.hh" :  "" ""
	copy ..\.\GUI\GTK\Notebook.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\CList.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header CList.hh

"C:\Build\inc\Ravl\GUI\CList.hh" :  "" ""
	copy ..\.\GUI\GTK\CList.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header CList.hh

"C:\Build\inc\Ravl\GUI\CList.hh" :  "" ""
	copy ..\.\GUI\GTK\CList.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\VLabel.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header VLabel.hh

"C:\Build\inc\Ravl\GUI\VLabel.hh" :  "" ""
	copy ..\.\GUI\GTK\VLabel.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header VLabel.hh

"C:\Build\inc\Ravl\GUI\VLabel.hh" :  "" ""
	copy ..\.\GUI\GTK\VLabel.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\RadioButton.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header RadioButton.hh

"C:\Build\inc\Ravl\GUI\RadioButton.hh" :  "" ""
	copy ..\.\GUI\GTK\RadioButton.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header RadioButton.hh

"C:\Build\inc\Ravl\GUI\RadioButton.hh" :  "" ""
	copy ..\.\GUI\GTK\RadioButton.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\ProgressBar.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header ProgressBar.hh

"C:\Build\inc\Ravl\GUI\ProgressBar.hh" :  "" ""
	copy ..\.\GUI\GTK\ProgressBar.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header ProgressBar.hh

"C:\Build\inc\Ravl\GUI\ProgressBar.hh" :  "" ""
	copy ..\.\GUI\GTK\ProgressBar.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\TextBox.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header TextBox.hh

"C:\Build\inc\Ravl\GUI\TextBox.hh" :  "" ""
	copy ..\.\GUI\GTK\TextBox.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header TextBox.hh

"C:\Build\inc\Ravl\GUI\TextBox.hh" :  "" ""
	copy ..\.\GUI\GTK\TextBox.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\DragAndDrop.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header DragAndDrop.hh

"C:\Build\inc\Ravl\GUI\DragAndDrop.hh" :  "" ""
	copy ..\.\GUI\GTK\DragAndDrop.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header DragAndDrop.hh

"C:\Build\inc\Ravl\GUI\DragAndDrop.hh" :  "" ""
	copy ..\.\GUI\GTK\DragAndDrop.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Paned.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header Paned.hh

"C:\Build\inc\Ravl\GUI\Paned.hh" :  "" ""
	copy ..\.\GUI\GTK\Paned.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header Paned.hh

"C:\Build\inc\Ravl\GUI\Paned.hh" :  "" ""
	copy ..\.\GUI\GTK\Paned.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\MessageBox.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header MessageBox.hh

"C:\Build\inc\Ravl\GUI\MessageBox.hh" :  "" ""
	copy ..\.\GUI\GTK\MessageBox.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header MessageBox.hh

"C:\Build\inc\Ravl\GUI\MessageBox.hh" :  "" ""
	copy ..\.\GUI\GTK\MessageBox.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\WidgetStyle.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header WidgetStyle.hh

"C:\Build\inc\Ravl\GUI\WidgetStyle.hh" :  "" ""
	copy ..\.\GUI\GTK\WidgetStyle.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header WidgetStyle.hh

"C:\Build\inc\Ravl\GUI\WidgetStyle.hh" :  "" ""
	copy ..\.\GUI\GTK\WidgetStyle.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\ReadBack.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header ReadBack.hh

"C:\Build\inc\Ravl\GUI\ReadBack.hh" :  "" ""
	copy ..\.\GUI\GTK\ReadBack.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header ReadBack.hh

"C:\Build\inc\Ravl\GUI\ReadBack.hh" :  "" ""
	copy ..\.\GUI\GTK\ReadBack.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\WaitForExit.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header WaitForExit.hh

"C:\Build\inc\Ravl\GUI\WaitForExit.hh" :  "" ""
	copy ..\.\GUI\GTK\WaitForExit.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header WaitForExit.hh

"C:\Build\inc\Ravl\GUI\WaitForExit.hh" :  "" ""
	copy ..\.\GUI\GTK\WaitForExit.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\TreeModel.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header TreeModel.hh

"C:\Build\inc\Ravl\GUI\TreeModel.hh" :  "" ""
	copy ..\.\GUI\GTK\TreeModel.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header TreeModel.hh

"C:\Build\inc\Ravl\GUI\TreeModel.hh" :  "" ""
	copy ..\.\GUI\GTK\TreeModel.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\TreeStore.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header TreeStore.hh

"C:\Build\inc\Ravl\GUI\TreeStore.hh" :  "" ""
	copy ..\.\GUI\GTK\TreeStore.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header TreeStore.hh

"C:\Build\inc\Ravl\GUI\TreeStore.hh" :  "" ""
	copy ..\.\GUI\GTK\TreeStore.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\TreeView.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header TreeView.hh

"C:\Build\inc\Ravl\GUI\TreeView.hh" :  "" ""
	copy ..\.\GUI\GTK\TreeView.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header TreeView.hh

"C:\Build\inc\Ravl\GUI\TreeView.hh" :  "" ""
	copy ..\.\GUI\GTK\TreeView.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\ListStore.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header ListStore.hh

"C:\Build\inc\Ravl\GUI\ListStore.hh" :  "" ""
	copy ..\.\GUI\GTK\ListStore.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header ListStore.hh

"C:\Build\inc\Ravl\GUI\ListStore.hh" :  "" ""
	copy ..\.\GUI\GTK\ListStore.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\Pixbuf.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header Pixbuf.hh

"C:\Build\inc\Ravl\GUI\Pixbuf.hh" :  "" ""
	copy ..\.\GUI\GTK\Pixbuf.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header Pixbuf.hh

"C:\Build\inc\Ravl\GUI\Pixbuf.hh" :  "" ""
	copy ..\.\GUI\GTK\Pixbuf.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\AspectFrame.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header AspectFrame.hh

"C:\Build\inc\Ravl\GUI\AspectFrame.hh" :  "" ""
	copy ..\.\GUI\GTK\AspectFrame.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header AspectFrame.hh

"C:\Build\inc\Ravl\GUI\AspectFrame.hh" :  "" ""
	copy ..\.\GUI\GTK\AspectFrame.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\ButtonBox.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header ButtonBox.hh

"C:\Build\inc\Ravl\GUI\ButtonBox.hh" :  "" ""
	copy ..\.\GUI\GTK\ButtonBox.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header ButtonBox.hh

"C:\Build\inc\Ravl\GUI\ButtonBox.hh" :  "" ""
	copy ..\.\GUI\GTK\ButtonBox.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\ColourSelector.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header ColourSelector.hh

"C:\Build\inc\Ravl\GUI\ColourSelector.hh" :  "" ""
	copy ..\.\GUI\GTK\ColourSelector.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header ColourSelector.hh

"C:\Build\inc\Ravl\GUI\ColourSelector.hh" :  "" ""
	copy ..\.\GUI\GTK\ColourSelector.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\GUI\GTK\DebugAssertDialog.hh

!IF  "$(CFG)" == "RavlGUI - Win32 Release"

# Begin Custom Build - Install Header DebugAssertDialog.hh

"C:\Build\inc\Ravl\GUI\DebugAssertDialog.hh" :  "" ""
	copy ..\.\GUI\GTK\DebugAssertDialog.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlGUI - Win32 Debug"

# Begin Custom Build - Install Header DebugAssertDialog.hh

"C:\Build\inc\Ravl\GUI\DebugAssertDialog.hh" :  "" ""
	copy ..\.\GUI\GTK\DebugAssertDialog.hh C:\Build\inc\Ravl\GUI

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
