


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
DEBUGOBJDIR = c:\Build/win32/debug/obj/RavlPatternRecIO
DEBUGLIBDIR = c:\Build/win32/debug/lib

OPTOBJDIR = c:\Build/win32/opt/obj/RavlPatternRecIO
OPTLIBDIR = c:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/SampleIO.obj $(OPTOBJDIR)/DataSetIO.obj $(OPTOBJDIR)/ClassifierIO.obj $(OPTOBJDIR)/Classifier2IO.obj $(OPTOBJDIR)/FunctionIO.obj $(OPTOBJDIR)/GaussianMixtureIO.obj $(OPTOBJDIR)/DistanceIO.obj $(OPTOBJDIR)/RavlPatternRecIO.obj
	@echo -- making $(OPTLIBDIR)/RavlPatternRecIO.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlPatternRecIO.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/SampleIO.obj $(DEBUGOBJDIR)/DataSetIO.obj $(DEBUGOBJDIR)/ClassifierIO.obj $(DEBUGOBJDIR)/Classifier2IO.obj $(DEBUGOBJDIR)/FunctionIO.obj $(DEBUGOBJDIR)/GaussianMixtureIO.obj $(DEBUGOBJDIR)/DistanceIO.obj $(DEBUGOBJDIR)/RavlPatternRecIO.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlPatternRecIO.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlPatternRecIO.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlPatternRecIO
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/SampleIO.obj: .././PatternRec/IO/SampleIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SampleIO.obj .././PatternRec/IO/SampleIO.cc

$(DEBUGOBJDIR)/SampleIO.obj: .././PatternRec/IO/SampleIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SampleIO.obj .././PatternRec/IO/SampleIO.cc

$(OPTOBJDIR)/DataSetIO.obj: .././PatternRec/IO/DataSetIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DataSetIO.obj .././PatternRec/IO/DataSetIO.cc

$(DEBUGOBJDIR)/DataSetIO.obj: .././PatternRec/IO/DataSetIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DataSetIO.obj .././PatternRec/IO/DataSetIO.cc

$(OPTOBJDIR)/ClassifierIO.obj: .././PatternRec/IO/ClassifierIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ClassifierIO.obj .././PatternRec/IO/ClassifierIO.cc

$(DEBUGOBJDIR)/ClassifierIO.obj: .././PatternRec/IO/ClassifierIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ClassifierIO.obj .././PatternRec/IO/ClassifierIO.cc

$(OPTOBJDIR)/Classifier2IO.obj: .././PatternRec/IO/Classifier2IO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Classifier2IO.obj .././PatternRec/IO/Classifier2IO.cc

$(DEBUGOBJDIR)/Classifier2IO.obj: .././PatternRec/IO/Classifier2IO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Classifier2IO.obj .././PatternRec/IO/Classifier2IO.cc

$(OPTOBJDIR)/FunctionIO.obj: .././PatternRec/IO/FunctionIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FunctionIO.obj .././PatternRec/IO/FunctionIO.cc

$(DEBUGOBJDIR)/FunctionIO.obj: .././PatternRec/IO/FunctionIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FunctionIO.obj .././PatternRec/IO/FunctionIO.cc

$(OPTOBJDIR)/GaussianMixtureIO.obj: .././PatternRec/IO/GaussianMixtureIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/GaussianMixtureIO.obj .././PatternRec/IO/GaussianMixtureIO.cc

$(DEBUGOBJDIR)/GaussianMixtureIO.obj: .././PatternRec/IO/GaussianMixtureIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/GaussianMixtureIO.obj .././PatternRec/IO/GaussianMixtureIO.cc

$(OPTOBJDIR)/DistanceIO.obj: .././PatternRec/IO/DistanceIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DistanceIO.obj .././PatternRec/IO/DistanceIO.cc

$(DEBUGOBJDIR)/DistanceIO.obj: .././PatternRec/IO/DistanceIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DistanceIO.obj .././PatternRec/IO/DistanceIO.cc

$(OPTOBJDIR)/RavlPatternRecIO.obj: .././PatternRec/IO/RavlPatternRecIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RavlPatternRecIO.obj .././PatternRec/IO/RavlPatternRecIO.cc

$(DEBUGOBJDIR)/RavlPatternRecIO.obj: .././PatternRec/IO/RavlPatternRecIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RavlPatternRecIO.obj .././PatternRec/IO/RavlPatternRecIO.cc


