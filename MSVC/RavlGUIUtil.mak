


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlGUIUtil
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlGUIUtil
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setupRavlGUIUtil  $(OPTOBJDIR)/AttributeEditor.obj $(OPTOBJDIR)/AttributeEditorWindow.obj $(OPTOBJDIR)/ThumbNailTimeLine.obj $(OPTOBJDIR)/EventTimeLine.obj
	@echo -- making $(OPTLIBDIR)/RavlGUIUtil.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlGUIUtil.lib $(OPTOBJDIR)/*.obj


debug:: setupRavlGUIUtil  $(DEBUGOBJDIR)/AttributeEditor.obj $(DEBUGOBJDIR)/AttributeEditorWindow.obj $(DEBUGOBJDIR)/ThumbNailTimeLine.obj $(DEBUGOBJDIR)/EventTimeLine.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlGUIUtil.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlGUIUtil.lib $(DEBUGOBJDIR)/*.obj

setupRavlGUIUtil::
        echo --- creating dir for RavlGUIUtil
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/AttributeEditor.obj: .././GUI/Util/AttributeEditor.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AttributeEditor.obj .././GUI/Util/AttributeEditor.cc

$(DEBUGOBJDIR)/AttributeEditor.obj: .././GUI/Util/AttributeEditor.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AttributeEditor.obj .././GUI/Util/AttributeEditor.cc

$(OPTOBJDIR)/AttributeEditorWindow.obj: .././GUI/Util/AttributeEditorWindow.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AttributeEditorWindow.obj .././GUI/Util/AttributeEditorWindow.cc

$(DEBUGOBJDIR)/AttributeEditorWindow.obj: .././GUI/Util/AttributeEditorWindow.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AttributeEditorWindow.obj .././GUI/Util/AttributeEditorWindow.cc

$(OPTOBJDIR)/ThumbNailTimeLine.obj: .././GUI/Util/ThumbNailTimeLine.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ThumbNailTimeLine.obj .././GUI/Util/ThumbNailTimeLine.cc

$(DEBUGOBJDIR)/ThumbNailTimeLine.obj: .././GUI/Util/ThumbNailTimeLine.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ThumbNailTimeLine.obj .././GUI/Util/ThumbNailTimeLine.cc

$(OPTOBJDIR)/EventTimeLine.obj: .././GUI/Util/EventTimeLine.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/EventTimeLine.obj .././GUI/Util/EventTimeLine.cc

$(DEBUGOBJDIR)/EventTimeLine.obj: .././GUI/Util/EventTimeLine.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/EventTimeLine.obj .././GUI/Util/EventTimeLine.cc


