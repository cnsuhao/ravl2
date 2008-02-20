


#--------------------------
# Compiler and flags etc
#--------------------------
CC = cl.exe

LD = lib.exe

INCLUDES =  /I "include\Win32" /I "include" /I "c:/Program Files/Microsoft Visual Studio 8/VC/ATLMFC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/include" /I "c:/Program Files/Microsoft Visual Studio 8/SDK/v2.0/include" /I "C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\Include" 

DEFINES = /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2=1" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_SCL_SECURE=0" /D "_UNICODE" /D "UNICODE"


OPTFLAGS = /nologo /c /O2 /Ob1 /EHsc /MD /TP

DEBUGFLAGS = /nologo /c /Ob1 /EHsc /MD /TP

#-----------------------------------------------------------------------------
# OK lets define some of our output directories and define script to make them
#-----------------------------------------------------------------------------
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlMPEG2
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlMPEG2
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/ImgIOmpeg2dec.obj $(OPTOBJDIR)/MPEG2Format.obj $(OPTOBJDIR)/MustLinkMPEG2.obj
	@echo -- making $(OPTLIBDIR)/RavlMPEG2.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlMPEG2.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/ImgIOmpeg2dec.obj $(DEBUGOBJDIR)/MPEG2Format.obj $(DEBUGOBJDIR)/MustLinkMPEG2.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlMPEG2.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlMPEG2.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlMPEG2
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/ImgIOmpeg2dec.obj: .././Contrib/MPEG/mpeg2dec/ImgIOmpeg2dec.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOmpeg2dec.obj .././Contrib/MPEG/mpeg2dec/ImgIOmpeg2dec.cc

$(DEBUGOBJDIR)/ImgIOmpeg2dec.obj: .././Contrib/MPEG/mpeg2dec/ImgIOmpeg2dec.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOmpeg2dec.obj .././Contrib/MPEG/mpeg2dec/ImgIOmpeg2dec.cc

$(OPTOBJDIR)/MPEG2Format.obj: .././Contrib/MPEG/mpeg2dec/MPEG2Format.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MPEG2Format.obj .././Contrib/MPEG/mpeg2dec/MPEG2Format.cc

$(DEBUGOBJDIR)/MPEG2Format.obj: .././Contrib/MPEG/mpeg2dec/MPEG2Format.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MPEG2Format.obj .././Contrib/MPEG/mpeg2dec/MPEG2Format.cc

$(OPTOBJDIR)/MustLinkMPEG2.obj: .././Contrib/MPEG/mpeg2dec/MustLinkMPEG2.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MustLinkMPEG2.obj .././Contrib/MPEG/mpeg2dec/MustLinkMPEG2.cc

$(DEBUGOBJDIR)/MustLinkMPEG2.obj: .././Contrib/MPEG/mpeg2dec/MustLinkMPEG2.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MustLinkMPEG2.obj .././Contrib/MPEG/mpeg2dec/MustLinkMPEG2.cc


