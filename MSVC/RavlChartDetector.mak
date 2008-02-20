


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlChartDetector
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlChartDetector
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/ChartDetector.obj $(OPTOBJDIR)/ChartDetectorRegion.obj $(OPTOBJDIR)/ChartLocalise.obj $(OPTOBJDIR)/CostAffineImageCorrelation.obj
	@echo -- making $(OPTLIBDIR)/RavlChartDetector.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlChartDetector.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/ChartDetector.obj $(DEBUGOBJDIR)/ChartDetectorRegion.obj $(DEBUGOBJDIR)/ChartLocalise.obj $(DEBUGOBJDIR)/CostAffineImageCorrelation.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlChartDetector.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlChartDetector.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlChartDetector
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/ChartDetector.obj: .././Image/Processing/ChartDetector/ChartDetector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ChartDetector.obj .././Image/Processing/ChartDetector/ChartDetector.cc

$(DEBUGOBJDIR)/ChartDetector.obj: .././Image/Processing/ChartDetector/ChartDetector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ChartDetector.obj .././Image/Processing/ChartDetector/ChartDetector.cc

$(OPTOBJDIR)/ChartDetectorRegion.obj: .././Image/Processing/ChartDetector/ChartDetectorRegion.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ChartDetectorRegion.obj .././Image/Processing/ChartDetector/ChartDetectorRegion.cc

$(DEBUGOBJDIR)/ChartDetectorRegion.obj: .././Image/Processing/ChartDetector/ChartDetectorRegion.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ChartDetectorRegion.obj .././Image/Processing/ChartDetector/ChartDetectorRegion.cc

$(OPTOBJDIR)/ChartLocalise.obj: .././Image/Processing/ChartDetector/ChartLocalise.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ChartLocalise.obj .././Image/Processing/ChartDetector/ChartLocalise.cc

$(DEBUGOBJDIR)/ChartLocalise.obj: .././Image/Processing/ChartDetector/ChartLocalise.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ChartLocalise.obj .././Image/Processing/ChartDetector/ChartLocalise.cc

$(OPTOBJDIR)/CostAffineImageCorrelation.obj: .././Image/Processing/ChartDetector/CostAffineImageCorrelation.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/CostAffineImageCorrelation.obj .././Image/Processing/ChartDetector/CostAffineImageCorrelation.cc

$(DEBUGOBJDIR)/CostAffineImageCorrelation.obj: .././Image/Processing/ChartDetector/CostAffineImageCorrelation.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/CostAffineImageCorrelation.obj .././Image/Processing/ChartDetector/CostAffineImageCorrelation.cc


