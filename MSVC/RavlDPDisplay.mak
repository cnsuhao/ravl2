


#--------------------------
# Compiler and flags etc
#--------------------------
CC = cl.exe

LD = lib.exe

INCLUDES =  /I "include\Win32" /I "include" /I "c:/Program Files/Microsoft Visual Studio 8/VC/ATLMFC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/include" /I "c:/Program Files/Microsoft Visual Studio 8/SDK/v2.0/include" /I "C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\Include" /I "C:\GTKWIN32\lib\gtk-2.0\include" /I "C:\GTKWIN32\lib\glib-2.0\include" /I "C:\GTKWIN32\include\cairo" /I "C:\GTKWIN32\include\gtk-2.0" /I "C:\GTKWIN32\include\glib-2.0" /I "C:\GTKWIN32\include\pango-1.0" /I "C:\GTKWIN32\include\atk-1.0" /I "C:\GTKWIN32\include\gtkglext-1.0" 

DEFINES = /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2=1" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_SCL_SECURE=0" /D "_UNICODE" /D "UNICODE"


OPTFLAGS = /nologo /c /O2 /Ob1 /EHsc /MD /TP

DEBUGFLAGS = /nologo /c /Ob1 /EHsc /MD /TP

#-----------------------------------------------------------------------------
# OK lets define some of our output directories and define script to make them
#-----------------------------------------------------------------------------
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlDPDisplay
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlDPDisplay
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/DPWindow.obj $(OPTOBJDIR)/DPDisplayObj.obj $(OPTOBJDIR)/DPDisplayImage.obj $(OPTOBJDIR)/DPWindowOPort.obj $(OPTOBJDIR)/DPWindowFormat.obj $(OPTOBJDIR)/DPDisplayView.obj $(OPTOBJDIR)/DPDisplayPoints.obj $(OPTOBJDIR)/DPDisplayPolygon.obj $(OPTOBJDIR)/RavlGUIDisplay.obj
	@echo -- making $(OPTLIBDIR)/RavlDPDisplay.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlDPDisplay.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/DPWindow.obj $(DEBUGOBJDIR)/DPDisplayObj.obj $(DEBUGOBJDIR)/DPDisplayImage.obj $(DEBUGOBJDIR)/DPWindowOPort.obj $(DEBUGOBJDIR)/DPWindowFormat.obj $(DEBUGOBJDIR)/DPDisplayView.obj $(DEBUGOBJDIR)/DPDisplayPoints.obj $(DEBUGOBJDIR)/DPDisplayPolygon.obj $(DEBUGOBJDIR)/RavlGUIDisplay.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlDPDisplay.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlDPDisplay.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlDPDisplay
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/DPWindow.obj: .././GUI/DPDisplay/DPWindow.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DPWindow.obj .././GUI/DPDisplay/DPWindow.cc

$(DEBUGOBJDIR)/DPWindow.obj: .././GUI/DPDisplay/DPWindow.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DPWindow.obj .././GUI/DPDisplay/DPWindow.cc

$(OPTOBJDIR)/DPDisplayObj.obj: .././GUI/DPDisplay/DPDisplayObj.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DPDisplayObj.obj .././GUI/DPDisplay/DPDisplayObj.cc

$(DEBUGOBJDIR)/DPDisplayObj.obj: .././GUI/DPDisplay/DPDisplayObj.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DPDisplayObj.obj .././GUI/DPDisplay/DPDisplayObj.cc

$(OPTOBJDIR)/DPDisplayImage.obj: .././GUI/DPDisplay/DPDisplayImage.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DPDisplayImage.obj .././GUI/DPDisplay/DPDisplayImage.cc

$(DEBUGOBJDIR)/DPDisplayImage.obj: .././GUI/DPDisplay/DPDisplayImage.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DPDisplayImage.obj .././GUI/DPDisplay/DPDisplayImage.cc

$(OPTOBJDIR)/DPWindowOPort.obj: .././GUI/DPDisplay/DPWindowOPort.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DPWindowOPort.obj .././GUI/DPDisplay/DPWindowOPort.cc

$(DEBUGOBJDIR)/DPWindowOPort.obj: .././GUI/DPDisplay/DPWindowOPort.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DPWindowOPort.obj .././GUI/DPDisplay/DPWindowOPort.cc

$(OPTOBJDIR)/DPWindowFormat.obj: .././GUI/DPDisplay/DPWindowFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DPWindowFormat.obj .././GUI/DPDisplay/DPWindowFormat.cc

$(DEBUGOBJDIR)/DPWindowFormat.obj: .././GUI/DPDisplay/DPWindowFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DPWindowFormat.obj .././GUI/DPDisplay/DPWindowFormat.cc

$(OPTOBJDIR)/DPDisplayView.obj: .././GUI/DPDisplay/DPDisplayView.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DPDisplayView.obj .././GUI/DPDisplay/DPDisplayView.cc

$(DEBUGOBJDIR)/DPDisplayView.obj: .././GUI/DPDisplay/DPDisplayView.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DPDisplayView.obj .././GUI/DPDisplay/DPDisplayView.cc

$(OPTOBJDIR)/DPDisplayPoints.obj: .././GUI/DPDisplay/DPDisplayPoints.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DPDisplayPoints.obj .././GUI/DPDisplay/DPDisplayPoints.cc

$(DEBUGOBJDIR)/DPDisplayPoints.obj: .././GUI/DPDisplay/DPDisplayPoints.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DPDisplayPoints.obj .././GUI/DPDisplay/DPDisplayPoints.cc

$(OPTOBJDIR)/DPDisplayPolygon.obj: .././GUI/DPDisplay/DPDisplayPolygon.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DPDisplayPolygon.obj .././GUI/DPDisplay/DPDisplayPolygon.cc

$(DEBUGOBJDIR)/DPDisplayPolygon.obj: .././GUI/DPDisplay/DPDisplayPolygon.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DPDisplayPolygon.obj .././GUI/DPDisplay/DPDisplayPolygon.cc

$(OPTOBJDIR)/RavlGUIDisplay.obj: .././GUI/DPDisplay/RavlGUIDisplay.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RavlGUIDisplay.obj .././GUI/DPDisplay/RavlGUIDisplay.cc

$(DEBUGOBJDIR)/RavlGUIDisplay.obj: .././GUI/DPDisplay/RavlGUIDisplay.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RavlGUIDisplay.obj .././GUI/DPDisplay/RavlGUIDisplay.cc


