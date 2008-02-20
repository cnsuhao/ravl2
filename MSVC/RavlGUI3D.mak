


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlGUI3D
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlGUI3D
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/gdkgl.obj $(OPTOBJDIR)/gtkglarea.obj $(OPTOBJDIR)/DObject3D.obj $(OPTOBJDIR)/DLight3D.obj $(OPTOBJDIR)/Util.obj $(OPTOBJDIR)/Canvas3D.obj $(OPTOBJDIR)/DViewPoint3D.obj $(OPTOBJDIR)/DCube3D.obj $(OPTOBJDIR)/DTriMesh3D.obj $(OPTOBJDIR)/DPointSet3d.obj $(OPTOBJDIR)/DPinholeCamera03D.obj $(OPTOBJDIR)/DTexTriMesh3D.obj $(OPTOBJDIR)/View3D.obj $(OPTOBJDIR)/DSurfacePointVertexArray.obj $(OPTOBJDIR)/DSurfacePointVertexByteRGBArray.obj
	@echo -- making $(OPTLIBDIR)/RavlGUI3D.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlGUI3D.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/gdkgl.obj $(DEBUGOBJDIR)/gtkglarea.obj $(DEBUGOBJDIR)/DObject3D.obj $(DEBUGOBJDIR)/DLight3D.obj $(DEBUGOBJDIR)/Util.obj $(DEBUGOBJDIR)/Canvas3D.obj $(DEBUGOBJDIR)/DViewPoint3D.obj $(DEBUGOBJDIR)/DCube3D.obj $(DEBUGOBJDIR)/DTriMesh3D.obj $(DEBUGOBJDIR)/DPointSet3d.obj $(DEBUGOBJDIR)/DPinholeCamera03D.obj $(DEBUGOBJDIR)/DTexTriMesh3D.obj $(DEBUGOBJDIR)/View3D.obj $(DEBUGOBJDIR)/DSurfacePointVertexArray.obj $(DEBUGOBJDIR)/DSurfacePointVertexByteRGBArray.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlGUI3D.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlGUI3D.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlGUI3D
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/gdkgl.obj: .././GUI/3D/gdkgl.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/gdkgl.obj .././GUI/3D/gdkgl.c

$(DEBUGOBJDIR)/gdkgl.obj: .././GUI/3D/gdkgl.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/gdkgl.obj .././GUI/3D/gdkgl.c

$(OPTOBJDIR)/gtkglarea.obj: .././GUI/3D/gtkglarea.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/gtkglarea.obj .././GUI/3D/gtkglarea.c

$(DEBUGOBJDIR)/gtkglarea.obj: .././GUI/3D/gtkglarea.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/gtkglarea.obj .././GUI/3D/gtkglarea.c

$(OPTOBJDIR)/DObject3D.obj: .././GUI/3D/DObject3D.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DObject3D.obj .././GUI/3D/DObject3D.cc

$(DEBUGOBJDIR)/DObject3D.obj: .././GUI/3D/DObject3D.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DObject3D.obj .././GUI/3D/DObject3D.cc

$(OPTOBJDIR)/DLight3D.obj: .././GUI/3D/DLight3D.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DLight3D.obj .././GUI/3D/DLight3D.cc

$(DEBUGOBJDIR)/DLight3D.obj: .././GUI/3D/DLight3D.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DLight3D.obj .././GUI/3D/DLight3D.cc

$(OPTOBJDIR)/Util.obj: .././GUI/3D/Util.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Util.obj .././GUI/3D/Util.cc

$(DEBUGOBJDIR)/Util.obj: .././GUI/3D/Util.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Util.obj .././GUI/3D/Util.cc

$(OPTOBJDIR)/Canvas3D.obj: .././GUI/3D/Canvas3D.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Canvas3D.obj .././GUI/3D/Canvas3D.cc

$(DEBUGOBJDIR)/Canvas3D.obj: .././GUI/3D/Canvas3D.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Canvas3D.obj .././GUI/3D/Canvas3D.cc

$(OPTOBJDIR)/DViewPoint3D.obj: .././GUI/3D/DViewPoint3D.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DViewPoint3D.obj .././GUI/3D/DViewPoint3D.cc

$(DEBUGOBJDIR)/DViewPoint3D.obj: .././GUI/3D/DViewPoint3D.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DViewPoint3D.obj .././GUI/3D/DViewPoint3D.cc

$(OPTOBJDIR)/DCube3D.obj: .././GUI/3D/DCube3D.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DCube3D.obj .././GUI/3D/DCube3D.cc

$(DEBUGOBJDIR)/DCube3D.obj: .././GUI/3D/DCube3D.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DCube3D.obj .././GUI/3D/DCube3D.cc

$(OPTOBJDIR)/DTriMesh3D.obj: .././GUI/3D/DTriMesh3D.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DTriMesh3D.obj .././GUI/3D/DTriMesh3D.cc

$(DEBUGOBJDIR)/DTriMesh3D.obj: .././GUI/3D/DTriMesh3D.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DTriMesh3D.obj .././GUI/3D/DTriMesh3D.cc

$(OPTOBJDIR)/DPointSet3d.obj: .././GUI/3D/DPointSet3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DPointSet3d.obj .././GUI/3D/DPointSet3d.cc

$(DEBUGOBJDIR)/DPointSet3d.obj: .././GUI/3D/DPointSet3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DPointSet3d.obj .././GUI/3D/DPointSet3d.cc

$(OPTOBJDIR)/DPinholeCamera03D.obj: .././GUI/3D/DPinholeCamera03D.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DPinholeCamera03D.obj .././GUI/3D/DPinholeCamera03D.cc

$(DEBUGOBJDIR)/DPinholeCamera03D.obj: .././GUI/3D/DPinholeCamera03D.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DPinholeCamera03D.obj .././GUI/3D/DPinholeCamera03D.cc

$(OPTOBJDIR)/DTexTriMesh3D.obj: .././GUI/3D/DTexTriMesh3D.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DTexTriMesh3D.obj .././GUI/3D/DTexTriMesh3D.cc

$(DEBUGOBJDIR)/DTexTriMesh3D.obj: .././GUI/3D/DTexTriMesh3D.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DTexTriMesh3D.obj .././GUI/3D/DTexTriMesh3D.cc

$(OPTOBJDIR)/View3D.obj: .././GUI/3D/View3D.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/View3D.obj .././GUI/3D/View3D.cc

$(DEBUGOBJDIR)/View3D.obj: .././GUI/3D/View3D.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/View3D.obj .././GUI/3D/View3D.cc

$(OPTOBJDIR)/DSurfacePointVertexArray.obj: .././GUI/3D/DSurfacePointVertexArray.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DSurfacePointVertexArray.obj .././GUI/3D/DSurfacePointVertexArray.cc

$(DEBUGOBJDIR)/DSurfacePointVertexArray.obj: .././GUI/3D/DSurfacePointVertexArray.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DSurfacePointVertexArray.obj .././GUI/3D/DSurfacePointVertexArray.cc

$(OPTOBJDIR)/DSurfacePointVertexByteRGBArray.obj: .././GUI/3D/DSurfacePointVertexByteRGBArray.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DSurfacePointVertexByteRGBArray.obj .././GUI/3D/DSurfacePointVertexByteRGBArray.cc

$(DEBUGOBJDIR)/DSurfacePointVertexByteRGBArray.obj: .././GUI/3D/DSurfacePointVertexByteRGBArray.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DSurfacePointVertexByteRGBArray.obj .././GUI/3D/DSurfacePointVertexByteRGBArray.cc


