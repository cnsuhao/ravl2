


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlAudioFeatures
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlAudioFeatures
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setupRavlAudioFeatures  $(OPTOBJDIR)/MelSpectrum.obj $(OPTOBJDIR)/MelCepstrum.obj $(OPTOBJDIR)/FeatureMFCC.obj $(OPTOBJDIR)/VectorDelta012.obj
	@echo -- making $(OPTLIBDIR)/RavlAudioFeatures.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlAudioFeatures.lib $(OPTOBJDIR)/*.obj


debug:: setupRavlAudioFeatures  $(DEBUGOBJDIR)/MelSpectrum.obj $(DEBUGOBJDIR)/MelCepstrum.obj $(DEBUGOBJDIR)/FeatureMFCC.obj $(DEBUGOBJDIR)/VectorDelta012.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlAudioFeatures.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlAudioFeatures.lib $(DEBUGOBJDIR)/*.obj

setupRavlAudioFeatures::
        echo --- creating dir for RavlAudioFeatures
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/MelSpectrum.obj: .././Audio/Features/MelSpectrum.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MelSpectrum.obj .././Audio/Features/MelSpectrum.cc

$(DEBUGOBJDIR)/MelSpectrum.obj: .././Audio/Features/MelSpectrum.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MelSpectrum.obj .././Audio/Features/MelSpectrum.cc

$(OPTOBJDIR)/MelCepstrum.obj: .././Audio/Features/MelCepstrum.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MelCepstrum.obj .././Audio/Features/MelCepstrum.cc

$(DEBUGOBJDIR)/MelCepstrum.obj: .././Audio/Features/MelCepstrum.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MelCepstrum.obj .././Audio/Features/MelCepstrum.cc

$(OPTOBJDIR)/FeatureMFCC.obj: .././Audio/Features/FeatureMFCC.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FeatureMFCC.obj .././Audio/Features/FeatureMFCC.cc

$(DEBUGOBJDIR)/FeatureMFCC.obj: .././Audio/Features/FeatureMFCC.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FeatureMFCC.obj .././Audio/Features/FeatureMFCC.cc

$(OPTOBJDIR)/VectorDelta012.obj: .././Audio/Features/VectorDelta012.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/VectorDelta012.obj .././Audio/Features/VectorDelta012.cc

$(DEBUGOBJDIR)/VectorDelta012.obj: .././Audio/Features/VectorDelta012.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/VectorDelta012.obj .././Audio/Features/VectorDelta012.cc


