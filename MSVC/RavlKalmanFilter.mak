


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlKalmanFilter
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlKalmanFilter
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/KalmanFilter.obj $(OPTOBJDIR)/LinearKalmanFilter.obj $(OPTOBJDIR)/ExtendedKalmanFilter.obj $(OPTOBJDIR)/KalmanTwoWheelDifferentialMotionModel.obj $(OPTOBJDIR)/KalmanNullMeasurementModel.obj
	@echo -- making $(OPTLIBDIR)/RavlKalmanFilter.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlKalmanFilter.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/KalmanFilter.obj $(DEBUGOBJDIR)/LinearKalmanFilter.obj $(DEBUGOBJDIR)/ExtendedKalmanFilter.obj $(DEBUGOBJDIR)/KalmanTwoWheelDifferentialMotionModel.obj $(DEBUGOBJDIR)/KalmanNullMeasurementModel.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlKalmanFilter.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlKalmanFilter.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlKalmanFilter
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/KalmanFilter.obj: .././PatternRec/KalmanFilter/KalmanFilter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/KalmanFilter.obj .././PatternRec/KalmanFilter/KalmanFilter.cc

$(DEBUGOBJDIR)/KalmanFilter.obj: .././PatternRec/KalmanFilter/KalmanFilter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/KalmanFilter.obj .././PatternRec/KalmanFilter/KalmanFilter.cc

$(OPTOBJDIR)/LinearKalmanFilter.obj: .././PatternRec/KalmanFilter/LinearKalmanFilter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LinearKalmanFilter.obj .././PatternRec/KalmanFilter/LinearKalmanFilter.cc

$(DEBUGOBJDIR)/LinearKalmanFilter.obj: .././PatternRec/KalmanFilter/LinearKalmanFilter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LinearKalmanFilter.obj .././PatternRec/KalmanFilter/LinearKalmanFilter.cc

$(OPTOBJDIR)/ExtendedKalmanFilter.obj: .././PatternRec/KalmanFilter/ExtendedKalmanFilter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ExtendedKalmanFilter.obj .././PatternRec/KalmanFilter/ExtendedKalmanFilter.cc

$(DEBUGOBJDIR)/ExtendedKalmanFilter.obj: .././PatternRec/KalmanFilter/ExtendedKalmanFilter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ExtendedKalmanFilter.obj .././PatternRec/KalmanFilter/ExtendedKalmanFilter.cc

$(OPTOBJDIR)/KalmanTwoWheelDifferentialMotionModel.obj: .././PatternRec/KalmanFilter/KalmanTwoWheelDifferentialMotionModel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/KalmanTwoWheelDifferentialMotionModel.obj .././PatternRec/KalmanFilter/KalmanTwoWheelDifferentialMotionModel.cc

$(DEBUGOBJDIR)/KalmanTwoWheelDifferentialMotionModel.obj: .././PatternRec/KalmanFilter/KalmanTwoWheelDifferentialMotionModel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/KalmanTwoWheelDifferentialMotionModel.obj .././PatternRec/KalmanFilter/KalmanTwoWheelDifferentialMotionModel.cc

$(OPTOBJDIR)/KalmanNullMeasurementModel.obj: .././PatternRec/KalmanFilter/KalmanNullMeasurementModel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/KalmanNullMeasurementModel.obj .././PatternRec/KalmanFilter/KalmanNullMeasurementModel.cc

$(DEBUGOBJDIR)/KalmanNullMeasurementModel.obj: .././PatternRec/KalmanFilter/KalmanNullMeasurementModel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/KalmanNullMeasurementModel.obj .././PatternRec/KalmanFilter/KalmanNullMeasurementModel.cc


