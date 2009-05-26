


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlAudioIO
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlAudioIO
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setupRavlAudioIO  $(OPTOBJDIR)/AudioSample.obj $(OPTOBJDIR)/SphereIO.obj $(OPTOBJDIR)/SphereFormat.obj $(OPTOBJDIR)/TranscriptionFiles.obj $(OPTOBJDIR)/TranscriptionStream.obj $(OPTOBJDIR)/RavlAudioSample.obj
	@echo -- making $(OPTLIBDIR)/RavlAudioIO.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlAudioIO.lib $(OPTOBJDIR)/*.obj


debug:: setupRavlAudioIO  $(DEBUGOBJDIR)/AudioSample.obj $(DEBUGOBJDIR)/SphereIO.obj $(DEBUGOBJDIR)/SphereFormat.obj $(DEBUGOBJDIR)/TranscriptionFiles.obj $(DEBUGOBJDIR)/TranscriptionStream.obj $(DEBUGOBJDIR)/RavlAudioSample.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlAudioIO.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlAudioIO.lib $(DEBUGOBJDIR)/*.obj

setupRavlAudioIO::
        echo --- creating dir for RavlAudioIO
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/AudioSample.obj: .././Audio/IO/AudioSample.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AudioSample.obj .././Audio/IO/AudioSample.cc

$(DEBUGOBJDIR)/AudioSample.obj: .././Audio/IO/AudioSample.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AudioSample.obj .././Audio/IO/AudioSample.cc

$(OPTOBJDIR)/SphereIO.obj: .././Audio/IO/SphereIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SphereIO.obj .././Audio/IO/SphereIO.cc

$(DEBUGOBJDIR)/SphereIO.obj: .././Audio/IO/SphereIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SphereIO.obj .././Audio/IO/SphereIO.cc

$(OPTOBJDIR)/SphereFormat.obj: .././Audio/IO/SphereFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SphereFormat.obj .././Audio/IO/SphereFormat.cc

$(DEBUGOBJDIR)/SphereFormat.obj: .././Audio/IO/SphereFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SphereFormat.obj .././Audio/IO/SphereFormat.cc

$(OPTOBJDIR)/TranscriptionFiles.obj: .././Audio/IO/TranscriptionFiles.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TranscriptionFiles.obj .././Audio/IO/TranscriptionFiles.cc

$(DEBUGOBJDIR)/TranscriptionFiles.obj: .././Audio/IO/TranscriptionFiles.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TranscriptionFiles.obj .././Audio/IO/TranscriptionFiles.cc

$(OPTOBJDIR)/TranscriptionStream.obj: .././Audio/IO/TranscriptionStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TranscriptionStream.obj .././Audio/IO/TranscriptionStream.cc

$(DEBUGOBJDIR)/TranscriptionStream.obj: .././Audio/IO/TranscriptionStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TranscriptionStream.obj .././Audio/IO/TranscriptionStream.cc

$(OPTOBJDIR)/RavlAudioSample.obj: .././Audio/IO/RavlAudioSample.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RavlAudioSample.obj .././Audio/IO/RavlAudioSample.cc

$(DEBUGOBJDIR)/RavlAudioSample.obj: .././Audio/IO/RavlAudioSample.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RavlAudioSample.obj .././Audio/IO/RavlAudioSample.cc


