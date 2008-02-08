


#--------------------------
# Compiler and flags etc
#--------------------------
CC = cl.exe

LD = lib.exe

INCLUDES =  /I "include\Win32" /I "include" /I "c:/Program Files/Microsoft Visual Studio 8/VC/ATLMFC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/include" /I "c:/Program Files/Microsoft Visual Studio 8/SDK/v2.0/include" /I "C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\Include" /I "C:\GTKWIN32\lib\gtk-2.0\include" /I "C:\GTKWIN32\lib\glib-2.0\include" /I "C:\GTKWIN32\include\cairo" /I "C:\GTKWIN32\include\gtk-2.0" /I "C:\GTKWIN32\include\glib-2.0" /I "C:\GTKWIN32\include\pango-1.0" /I "C:\GTKWIN32\include\atk-1.0" /I "C:\GTKWIN32\include\libglade-2.0" 

DEFINES = /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2=1" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_SCL_SECURE=0" /D "_UNICODE" /D "UNICODE"


OPTFLAGS = /nologo /c /O2 /Ob1 /EHsc /MD /TP

DEBUGFLAGS = /nologo /c /Ob1 /EHsc /MD /TP

#-----------------------------------------------------------------------------
# OK lets define some of our output directories and define script to make them
#-----------------------------------------------------------------------------
DEBUGOBJDIR = c:\Build/win32/debug/obj/RavlLibGlade
DEBUGLIBDIR = c:\Build/win32/debug/lib

OPTOBJDIR = c:\Build/win32/opt/obj/RavlLibGlade
OPTLIBDIR = c:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/GladeWidget.obj $(OPTOBJDIR)/GladeXML.obj $(OPTOBJDIR)/GladeWindow.obj
	@echo -- making $(OPTLIBDIR)/RavlLibGlade.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlLibGlade.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/GladeWidget.obj $(DEBUGOBJDIR)/GladeXML.obj $(DEBUGOBJDIR)/GladeWindow.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlLibGlade.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlLibGlade.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlLibGlade
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/GladeWidget.obj: .././GUI/LibGlade/GladeWidget.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/GladeWidget.obj .././GUI/LibGlade/GladeWidget.cc

$(DEBUGOBJDIR)/GladeWidget.obj: .././GUI/LibGlade/GladeWidget.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/GladeWidget.obj .././GUI/LibGlade/GladeWidget.cc

$(OPTOBJDIR)/GladeXML.obj: .././GUI/LibGlade/GladeXML.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/GladeXML.obj .././GUI/LibGlade/GladeXML.cc

$(DEBUGOBJDIR)/GladeXML.obj: .././GUI/LibGlade/GladeXML.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/GladeXML.obj .././GUI/LibGlade/GladeXML.cc

$(OPTOBJDIR)/GladeWindow.obj: .././GUI/LibGlade/GladeWindow.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/GladeWindow.obj .././GUI/LibGlade/GladeWindow.cc

$(DEBUGOBJDIR)/GladeWindow.obj: .././GUI/LibGlade/GladeWindow.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/GladeWindow.obj .././GUI/LibGlade/GladeWindow.cc


