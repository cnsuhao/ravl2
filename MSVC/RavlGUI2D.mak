


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
DEBUGOBJDIR = c:\Build/win32/debug/obj/RavlGUI2D
DEBUGLIBDIR = c:\Build/win32/debug/lib

OPTOBJDIR = c:\Build/win32/opt/obj/RavlGUI2D
OPTLIBDIR = c:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/Canvas.obj $(OPTOBJDIR)/RawCanvas2d.obj $(OPTOBJDIR)/RawZoomCanvas.obj $(OPTOBJDIR)/FrameMarkup.obj $(OPTOBJDIR)/GUIMarkupLayerEditor.obj $(OPTOBJDIR)/MarkupImageRGB.obj $(OPTOBJDIR)/MarkupLine2d.obj $(OPTOBJDIR)/MarkupPolygon2d.obj $(OPTOBJDIR)/MarkupImageByte.obj $(OPTOBJDIR)/MarkupInfo.obj $(OPTOBJDIR)/MarkupNote.obj $(OPTOBJDIR)/GUIMarkupCanvas.obj $(OPTOBJDIR)/MarkupImageRGBA.obj $(OPTOBJDIR)/MarkupLayerInfo.obj $(OPTOBJDIR)/MarkupPoint2d.obj
	@echo -- making $(OPTLIBDIR)/RavlGUI2D.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlGUI2D.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/Canvas.obj $(DEBUGOBJDIR)/RawCanvas2d.obj $(DEBUGOBJDIR)/RawZoomCanvas.obj $(DEBUGOBJDIR)/FrameMarkup.obj $(DEBUGOBJDIR)/GUIMarkupLayerEditor.obj $(DEBUGOBJDIR)/MarkupImageRGB.obj $(DEBUGOBJDIR)/MarkupLine2d.obj $(DEBUGOBJDIR)/MarkupPolygon2d.obj $(DEBUGOBJDIR)/MarkupImageByte.obj $(DEBUGOBJDIR)/MarkupInfo.obj $(DEBUGOBJDIR)/MarkupNote.obj $(DEBUGOBJDIR)/GUIMarkupCanvas.obj $(DEBUGOBJDIR)/MarkupImageRGBA.obj $(DEBUGOBJDIR)/MarkupLayerInfo.obj $(DEBUGOBJDIR)/MarkupPoint2d.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlGUI2D.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlGUI2D.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlGUI2D
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/Canvas.obj: .././GUI/2D/Canvas.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Canvas.obj .././GUI/2D/Canvas.cc

$(DEBUGOBJDIR)/Canvas.obj: .././GUI/2D/Canvas.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Canvas.obj .././GUI/2D/Canvas.cc

$(OPTOBJDIR)/RawCanvas2d.obj: .././GUI/2D/RawCanvas2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RawCanvas2d.obj .././GUI/2D/RawCanvas2d.cc

$(DEBUGOBJDIR)/RawCanvas2d.obj: .././GUI/2D/RawCanvas2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RawCanvas2d.obj .././GUI/2D/RawCanvas2d.cc

$(OPTOBJDIR)/RawZoomCanvas.obj: .././GUI/2D/RawZoomCanvas.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RawZoomCanvas.obj .././GUI/2D/RawZoomCanvas.cc

$(DEBUGOBJDIR)/RawZoomCanvas.obj: .././GUI/2D/RawZoomCanvas.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RawZoomCanvas.obj .././GUI/2D/RawZoomCanvas.cc

$(OPTOBJDIR)/FrameMarkup.obj: .././GUI/2D/FrameMarkup.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FrameMarkup.obj .././GUI/2D/FrameMarkup.cc

$(DEBUGOBJDIR)/FrameMarkup.obj: .././GUI/2D/FrameMarkup.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FrameMarkup.obj .././GUI/2D/FrameMarkup.cc

$(OPTOBJDIR)/GUIMarkupLayerEditor.obj: .././GUI/2D/GUIMarkupLayerEditor.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/GUIMarkupLayerEditor.obj .././GUI/2D/GUIMarkupLayerEditor.cc

$(DEBUGOBJDIR)/GUIMarkupLayerEditor.obj: .././GUI/2D/GUIMarkupLayerEditor.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/GUIMarkupLayerEditor.obj .././GUI/2D/GUIMarkupLayerEditor.cc

$(OPTOBJDIR)/MarkupImageRGB.obj: .././GUI/2D/MarkupImageRGB.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MarkupImageRGB.obj .././GUI/2D/MarkupImageRGB.cc

$(DEBUGOBJDIR)/MarkupImageRGB.obj: .././GUI/2D/MarkupImageRGB.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MarkupImageRGB.obj .././GUI/2D/MarkupImageRGB.cc

$(OPTOBJDIR)/MarkupLine2d.obj: .././GUI/2D/MarkupLine2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MarkupLine2d.obj .././GUI/2D/MarkupLine2d.cc

$(DEBUGOBJDIR)/MarkupLine2d.obj: .././GUI/2D/MarkupLine2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MarkupLine2d.obj .././GUI/2D/MarkupLine2d.cc

$(OPTOBJDIR)/MarkupPolygon2d.obj: .././GUI/2D/MarkupPolygon2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MarkupPolygon2d.obj .././GUI/2D/MarkupPolygon2d.cc

$(DEBUGOBJDIR)/MarkupPolygon2d.obj: .././GUI/2D/MarkupPolygon2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MarkupPolygon2d.obj .././GUI/2D/MarkupPolygon2d.cc

$(OPTOBJDIR)/MarkupImageByte.obj: .././GUI/2D/MarkupImageByte.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MarkupImageByte.obj .././GUI/2D/MarkupImageByte.cc

$(DEBUGOBJDIR)/MarkupImageByte.obj: .././GUI/2D/MarkupImageByte.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MarkupImageByte.obj .././GUI/2D/MarkupImageByte.cc

$(OPTOBJDIR)/MarkupInfo.obj: .././GUI/2D/MarkupInfo.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MarkupInfo.obj .././GUI/2D/MarkupInfo.cc

$(DEBUGOBJDIR)/MarkupInfo.obj: .././GUI/2D/MarkupInfo.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MarkupInfo.obj .././GUI/2D/MarkupInfo.cc

$(OPTOBJDIR)/MarkupNote.obj: .././GUI/2D/MarkupNote.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MarkupNote.obj .././GUI/2D/MarkupNote.cc

$(DEBUGOBJDIR)/MarkupNote.obj: .././GUI/2D/MarkupNote.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MarkupNote.obj .././GUI/2D/MarkupNote.cc

$(OPTOBJDIR)/GUIMarkupCanvas.obj: .././GUI/2D/GUIMarkupCanvas.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/GUIMarkupCanvas.obj .././GUI/2D/GUIMarkupCanvas.cc

$(DEBUGOBJDIR)/GUIMarkupCanvas.obj: .././GUI/2D/GUIMarkupCanvas.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/GUIMarkupCanvas.obj .././GUI/2D/GUIMarkupCanvas.cc

$(OPTOBJDIR)/MarkupImageRGBA.obj: .././GUI/2D/MarkupImageRGBA.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MarkupImageRGBA.obj .././GUI/2D/MarkupImageRGBA.cc

$(DEBUGOBJDIR)/MarkupImageRGBA.obj: .././GUI/2D/MarkupImageRGBA.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MarkupImageRGBA.obj .././GUI/2D/MarkupImageRGBA.cc

$(OPTOBJDIR)/MarkupLayerInfo.obj: .././GUI/2D/MarkupLayerInfo.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MarkupLayerInfo.obj .././GUI/2D/MarkupLayerInfo.cc

$(DEBUGOBJDIR)/MarkupLayerInfo.obj: .././GUI/2D/MarkupLayerInfo.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MarkupLayerInfo.obj .././GUI/2D/MarkupLayerInfo.cc

$(OPTOBJDIR)/MarkupPoint2d.obj: .././GUI/2D/MarkupPoint2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MarkupPoint2d.obj .././GUI/2D/MarkupPoint2d.cc

$(DEBUGOBJDIR)/MarkupPoint2d.obj: .././GUI/2D/MarkupPoint2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MarkupPoint2d.obj .././GUI/2D/MarkupPoint2d.cc


