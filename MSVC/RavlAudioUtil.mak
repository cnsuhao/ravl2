


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlAudioUtil
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlAudioUtil
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/AudioIO.obj $(OPTOBJDIR)/WindowSignal.obj $(OPTOBJDIR)/Segment.obj $(OPTOBJDIR)/Transcription.obj $(OPTOBJDIR)/AudioFrame.obj
	@echo -- making $(OPTLIBDIR)/RavlAudioUtil.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlAudioUtil.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/AudioIO.obj $(DEBUGOBJDIR)/WindowSignal.obj $(DEBUGOBJDIR)/Segment.obj $(DEBUGOBJDIR)/Transcription.obj $(DEBUGOBJDIR)/AudioFrame.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlAudioUtil.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlAudioUtil.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlAudioUtil
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/AudioIO.obj: .././Audio/Util/AudioIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AudioIO.obj .././Audio/Util/AudioIO.cc

$(DEBUGOBJDIR)/AudioIO.obj: .././Audio/Util/AudioIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AudioIO.obj .././Audio/Util/AudioIO.cc

$(OPTOBJDIR)/WindowSignal.obj: .././Audio/Util/WindowSignal.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/WindowSignal.obj .././Audio/Util/WindowSignal.cc

$(DEBUGOBJDIR)/WindowSignal.obj: .././Audio/Util/WindowSignal.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/WindowSignal.obj .././Audio/Util/WindowSignal.cc

$(OPTOBJDIR)/Segment.obj: .././Audio/Util/Segment.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Segment.obj .././Audio/Util/Segment.cc

$(DEBUGOBJDIR)/Segment.obj: .././Audio/Util/Segment.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Segment.obj .././Audio/Util/Segment.cc

$(OPTOBJDIR)/Transcription.obj: .././Audio/Util/Transcription.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Transcription.obj .././Audio/Util/Transcription.cc

$(DEBUGOBJDIR)/Transcription.obj: .././Audio/Util/Transcription.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Transcription.obj .././Audio/Util/Transcription.cc

$(OPTOBJDIR)/AudioFrame.obj: .././Audio/Util/AudioFrame.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AudioFrame.obj .././Audio/Util/AudioFrame.cc

$(DEBUGOBJDIR)/AudioFrame.obj: .././Audio/Util/AudioFrame.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AudioFrame.obj .././Audio/Util/AudioFrame.cc


