


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
DEBUGOBJDIR = c:\Build/win32/debug/obj/Optimisation
DEBUGLIBDIR = c:\Build/win32/debug/lib

OPTOBJDIR = c:\Build/win32/opt/obj/Optimisation
OPTLIBDIR = c:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/Parameters.obj $(OPTOBJDIR)/Cost.obj $(OPTOBJDIR)/CostInvert.obj $(OPTOBJDIR)/CostFunction.obj $(OPTOBJDIR)/CostFunction1d.obj $(OPTOBJDIR)/BracketMinimum.obj $(OPTOBJDIR)/Optimise.obj $(OPTOBJDIR)/OptimiseDescent.obj $(OPTOBJDIR)/OptimiseConjugateGradient.obj $(OPTOBJDIR)/OptimiseRandomUniform.obj $(OPTOBJDIR)/OptimiseSobol.obj $(OPTOBJDIR)/OptimiseBrent.obj $(OPTOBJDIR)/OptimisePowell.obj $(OPTOBJDIR)/OptimiseGrid.obj $(OPTOBJDIR)/OptimiseLevenbergMarquardt.obj
	@echo -- making $(OPTLIBDIR)/Optimisation.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/Optimisation.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/Parameters.obj $(DEBUGOBJDIR)/Cost.obj $(DEBUGOBJDIR)/CostInvert.obj $(DEBUGOBJDIR)/CostFunction.obj $(DEBUGOBJDIR)/CostFunction1d.obj $(DEBUGOBJDIR)/BracketMinimum.obj $(DEBUGOBJDIR)/Optimise.obj $(DEBUGOBJDIR)/OptimiseDescent.obj $(DEBUGOBJDIR)/OptimiseConjugateGradient.obj $(DEBUGOBJDIR)/OptimiseRandomUniform.obj $(DEBUGOBJDIR)/OptimiseSobol.obj $(DEBUGOBJDIR)/OptimiseBrent.obj $(DEBUGOBJDIR)/OptimisePowell.obj $(DEBUGOBJDIR)/OptimiseGrid.obj $(DEBUGOBJDIR)/OptimiseLevenbergMarquardt.obj 
	@echo -- making $(DEBUGLIBDIR)/Optimisation.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/Optimisation.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for Optimisation
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/Parameters.obj: .././PatternRec/Optimise/Parameters.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Parameters.obj .././PatternRec/Optimise/Parameters.cc

$(DEBUGOBJDIR)/Parameters.obj: .././PatternRec/Optimise/Parameters.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Parameters.obj .././PatternRec/Optimise/Parameters.cc

$(OPTOBJDIR)/Cost.obj: .././PatternRec/Optimise/Cost.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Cost.obj .././PatternRec/Optimise/Cost.cc

$(DEBUGOBJDIR)/Cost.obj: .././PatternRec/Optimise/Cost.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Cost.obj .././PatternRec/Optimise/Cost.cc

$(OPTOBJDIR)/CostInvert.obj: .././PatternRec/Optimise/CostInvert.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/CostInvert.obj .././PatternRec/Optimise/CostInvert.cc

$(DEBUGOBJDIR)/CostInvert.obj: .././PatternRec/Optimise/CostInvert.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/CostInvert.obj .././PatternRec/Optimise/CostInvert.cc

$(OPTOBJDIR)/CostFunction.obj: .././PatternRec/Optimise/CostFunction.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/CostFunction.obj .././PatternRec/Optimise/CostFunction.cc

$(DEBUGOBJDIR)/CostFunction.obj: .././PatternRec/Optimise/CostFunction.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/CostFunction.obj .././PatternRec/Optimise/CostFunction.cc

$(OPTOBJDIR)/CostFunction1d.obj: .././PatternRec/Optimise/CostFunction1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/CostFunction1d.obj .././PatternRec/Optimise/CostFunction1d.cc

$(DEBUGOBJDIR)/CostFunction1d.obj: .././PatternRec/Optimise/CostFunction1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/CostFunction1d.obj .././PatternRec/Optimise/CostFunction1d.cc

$(OPTOBJDIR)/BracketMinimum.obj: .././PatternRec/Optimise/BracketMinimum.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/BracketMinimum.obj .././PatternRec/Optimise/BracketMinimum.cc

$(DEBUGOBJDIR)/BracketMinimum.obj: .././PatternRec/Optimise/BracketMinimum.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/BracketMinimum.obj .././PatternRec/Optimise/BracketMinimum.cc

$(OPTOBJDIR)/Optimise.obj: .././PatternRec/Optimise/Optimise.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Optimise.obj .././PatternRec/Optimise/Optimise.cc

$(DEBUGOBJDIR)/Optimise.obj: .././PatternRec/Optimise/Optimise.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Optimise.obj .././PatternRec/Optimise/Optimise.cc

$(OPTOBJDIR)/OptimiseDescent.obj: .././PatternRec/Optimise/OptimiseDescent.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/OptimiseDescent.obj .././PatternRec/Optimise/OptimiseDescent.cc

$(DEBUGOBJDIR)/OptimiseDescent.obj: .././PatternRec/Optimise/OptimiseDescent.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/OptimiseDescent.obj .././PatternRec/Optimise/OptimiseDescent.cc

$(OPTOBJDIR)/OptimiseConjugateGradient.obj: .././PatternRec/Optimise/OptimiseConjugateGradient.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/OptimiseConjugateGradient.obj .././PatternRec/Optimise/OptimiseConjugateGradient.cc

$(DEBUGOBJDIR)/OptimiseConjugateGradient.obj: .././PatternRec/Optimise/OptimiseConjugateGradient.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/OptimiseConjugateGradient.obj .././PatternRec/Optimise/OptimiseConjugateGradient.cc

$(OPTOBJDIR)/OptimiseRandomUniform.obj: .././PatternRec/Optimise/OptimiseRandomUniform.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/OptimiseRandomUniform.obj .././PatternRec/Optimise/OptimiseRandomUniform.cc

$(DEBUGOBJDIR)/OptimiseRandomUniform.obj: .././PatternRec/Optimise/OptimiseRandomUniform.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/OptimiseRandomUniform.obj .././PatternRec/Optimise/OptimiseRandomUniform.cc

$(OPTOBJDIR)/OptimiseSobol.obj: .././PatternRec/Optimise/OptimiseSobol.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/OptimiseSobol.obj .././PatternRec/Optimise/OptimiseSobol.cc

$(DEBUGOBJDIR)/OptimiseSobol.obj: .././PatternRec/Optimise/OptimiseSobol.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/OptimiseSobol.obj .././PatternRec/Optimise/OptimiseSobol.cc

$(OPTOBJDIR)/OptimiseBrent.obj: .././PatternRec/Optimise/OptimiseBrent.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/OptimiseBrent.obj .././PatternRec/Optimise/OptimiseBrent.cc

$(DEBUGOBJDIR)/OptimiseBrent.obj: .././PatternRec/Optimise/OptimiseBrent.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/OptimiseBrent.obj .././PatternRec/Optimise/OptimiseBrent.cc

$(OPTOBJDIR)/OptimisePowell.obj: .././PatternRec/Optimise/OptimisePowell.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/OptimisePowell.obj .././PatternRec/Optimise/OptimisePowell.cc

$(DEBUGOBJDIR)/OptimisePowell.obj: .././PatternRec/Optimise/OptimisePowell.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/OptimisePowell.obj .././PatternRec/Optimise/OptimisePowell.cc

$(OPTOBJDIR)/OptimiseGrid.obj: .././PatternRec/Optimise/OptimiseGrid.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/OptimiseGrid.obj .././PatternRec/Optimise/OptimiseGrid.cc

$(DEBUGOBJDIR)/OptimiseGrid.obj: .././PatternRec/Optimise/OptimiseGrid.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/OptimiseGrid.obj .././PatternRec/Optimise/OptimiseGrid.cc

$(OPTOBJDIR)/OptimiseLevenbergMarquardt.obj: .././PatternRec/Optimise/OptimiseLevenbergMarquardt.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/OptimiseLevenbergMarquardt.obj .././PatternRec/Optimise/OptimiseLevenbergMarquardt.cc

$(DEBUGOBJDIR)/OptimiseLevenbergMarquardt.obj: .././PatternRec/Optimise/OptimiseLevenbergMarquardt.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/OptimiseLevenbergMarquardt.obj .././PatternRec/Optimise/OptimiseLevenbergMarquardt.cc


