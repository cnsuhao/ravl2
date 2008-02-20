


#--------------------------
# Compiler and flags etc
#--------------------------
CC = cl.exe

LD = lib.exe

INCLUDES =  /I "include\Win32" /I "include" /I "c:/Program Files/Microsoft Visual Studio 8/VC/ATLMFC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/include" /I "c:/Program Files/Microsoft Visual Studio 8/SDK/v2.0/include" 

DEFINES = /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2=1" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_SCL_SECURE=0" /D "_UNICODE" /D "UNICODE"


OPTFLAGS = /nologo /c /O2 /Ob1 /EHsc /MD /TP

DEBUGFLAGS = /nologo /c /Ob1 /EHsc /MD /TP

#-----------------------------------------------------------------------------
# OK lets define some of our output directories and define script to make them
#-----------------------------------------------------------------------------
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlAV
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlAV
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/AVFrame.obj $(OPTOBJDIR)/AVMixer.obj
	@echo -- making $(OPTLIBDIR)/RavlAV.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlAV.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/AVFrame.obj $(DEBUGOBJDIR)/AVMixer.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlAV.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlAV.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlAV
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/AVFrame.obj: .././Image/AV/AVFrame.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AVFrame.obj .././Image/AV/AVFrame.cc

$(DEBUGOBJDIR)/AVFrame.obj: .././Image/AV/AVFrame.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AVFrame.obj .././Image/AV/AVFrame.cc

$(OPTOBJDIR)/AVMixer.obj: .././Image/AV/AVMixer.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AVMixer.obj .././Image/AV/AVMixer.cc

$(DEBUGOBJDIR)/AVMixer.obj: .././Image/AV/AVMixer.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AVMixer.obj .././Image/AV/AVMixer.cc


