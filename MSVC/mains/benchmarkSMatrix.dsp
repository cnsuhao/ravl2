# Microsoft Developer Studio Project File - Name="VGrab" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=VGrab - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VGrab.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VGrab.mak" CFG="VGrab - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VGrab - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "VGrab - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VGrab - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\bin"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\VGrab"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\GTKWIN32\include\gtk-2.0\" /I "C:\GTKWIN32\include\glib-2.0\" /I "C:\GTKWIN32\include\pango-1.0\" /I "C:\GTKWIN32\include\atk-1.0\" /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "VISUAL_CPP" /D "_CONSOLE" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386   /LIBPATH:"C:\GTKWIN32\lib\"  /LIBPATH:"C:\Build\win32\debug\lib"  RavlDPDisplay.lib RavlGUI.lib RavlThreads.lib system.lib  atk-1.0.lib glib-2.0.lib gthread-2.0.lib gobject-2.0.lib gmodule-2.0.lib gtk-win32-2.0.lib gdk-win32-2.0.lib gdk-pixbuf-2.0.lib pango-basic.lib pango-1.0.lib pangoft2.lib RavlVideoIO.lib RavlOSIO.lib RavlImageIO.lib RavlImage.lib RavlMath.lib ccmath.lib RavlIO.lib RavlOS.lib RavlCore.lib

!ELSEIF  "$(CFG)" == "VGrab - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\bin"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\VGrab"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /MDd /Od  /I "C:\GTKWIN32\include\gtk-2.0\" /I "C:\GTKWIN32\include\glib-2.0\" /I "C:\GTKWIN32\include\pango-1.0\" /I "C:\GTKWIN32\include\atk-1.0\" /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "_DEBUG" /D "VISUAL_CPP" /D "_CONSOLE" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /GZ /TP /c
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept  /LIBPATH:"C:\GTKWIN32\lib\"  /LIBPATH:"C:\Build\win32\debug\lib"  RavlDPDisplay.lib RavlGUI.lib RavlThreads.lib system.lib  atk-1.0.lib glib-2.0.lib gthread-2.0.lib gobject-2.0.lib gmodule-2.0.lib gtk-win32-2.0.lib gdk-win32-2.0.lib gdk-pixbuf-2.0.lib pango-basic.lib pango-1.0.lib pangoft2.lib RavlVideoIO.lib RavlOSIO.lib RavlImageIO.lib RavlImage.lib RavlMath.lib ccmath.lib RavlIO.lib RavlOS.lib RavlCore.lib
!ENDIF 

# Begin Target

# Name "VGrab - Win32 Release"
# Name "VGrab - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\..\.\Applications\VGrab\VGrab.cc
# End Source File


# End Group

# End Target
# End Project
