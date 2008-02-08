


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
DEBUGOBJDIR = c:\Build/win32/debug/obj/RavlMathIO
DEBUGLIBDIR = c:\Build/win32/debug/lib

OPTOBJDIR = c:\Build/win32/opt/obj/RavlMathIO
OPTLIBDIR = c:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/FixedVectorIO.obj $(OPTOBJDIR)/FixedPointIO.obj $(OPTOBJDIR)/FixedMatrixIO.obj $(OPTOBJDIR)/BoundryIO.obj $(OPTOBJDIR)/MatrixIO.obj $(OPTOBJDIR)/TMatrixIO.obj $(OPTOBJDIR)/Geom2dIO.obj $(OPTOBJDIR)/MathIO.obj
	@echo -- making $(OPTLIBDIR)/RavlMathIO.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlMathIO.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/FixedVectorIO.obj $(DEBUGOBJDIR)/FixedPointIO.obj $(DEBUGOBJDIR)/FixedMatrixIO.obj $(DEBUGOBJDIR)/BoundryIO.obj $(DEBUGOBJDIR)/MatrixIO.obj $(DEBUGOBJDIR)/TMatrixIO.obj $(DEBUGOBJDIR)/Geom2dIO.obj $(DEBUGOBJDIR)/MathIO.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlMathIO.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlMathIO.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlMathIO
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/FixedVectorIO.obj: .././Math/IO/FixedVectorIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FixedVectorIO.obj .././Math/IO/FixedVectorIO.cc

$(DEBUGOBJDIR)/FixedVectorIO.obj: .././Math/IO/FixedVectorIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FixedVectorIO.obj .././Math/IO/FixedVectorIO.cc

$(OPTOBJDIR)/FixedPointIO.obj: .././Math/IO/FixedPointIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FixedPointIO.obj .././Math/IO/FixedPointIO.cc

$(DEBUGOBJDIR)/FixedPointIO.obj: .././Math/IO/FixedPointIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FixedPointIO.obj .././Math/IO/FixedPointIO.cc

$(OPTOBJDIR)/FixedMatrixIO.obj: .././Math/IO/FixedMatrixIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FixedMatrixIO.obj .././Math/IO/FixedMatrixIO.cc

$(DEBUGOBJDIR)/FixedMatrixIO.obj: .././Math/IO/FixedMatrixIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FixedMatrixIO.obj .././Math/IO/FixedMatrixIO.cc

$(OPTOBJDIR)/BoundryIO.obj: .././Math/IO/BoundryIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/BoundryIO.obj .././Math/IO/BoundryIO.cc

$(DEBUGOBJDIR)/BoundryIO.obj: .././Math/IO/BoundryIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/BoundryIO.obj .././Math/IO/BoundryIO.cc

$(OPTOBJDIR)/MatrixIO.obj: .././Math/IO/MatrixIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MatrixIO.obj .././Math/IO/MatrixIO.cc

$(DEBUGOBJDIR)/MatrixIO.obj: .././Math/IO/MatrixIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MatrixIO.obj .././Math/IO/MatrixIO.cc

$(OPTOBJDIR)/TMatrixIO.obj: .././Math/IO/TMatrixIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TMatrixIO.obj .././Math/IO/TMatrixIO.cc

$(DEBUGOBJDIR)/TMatrixIO.obj: .././Math/IO/TMatrixIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TMatrixIO.obj .././Math/IO/TMatrixIO.cc

$(OPTOBJDIR)/Geom2dIO.obj: .././Math/IO/Geom2dIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Geom2dIO.obj .././Math/IO/Geom2dIO.cc

$(DEBUGOBJDIR)/Geom2dIO.obj: .././Math/IO/Geom2dIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Geom2dIO.obj .././Math/IO/Geom2dIO.cc

$(OPTOBJDIR)/MathIO.obj: .././Math/IO/MathIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MathIO.obj .././Math/IO/MathIO.cc

$(DEBUGOBJDIR)/MathIO.obj: .././Math/IO/MathIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MathIO.obj .././Math/IO/MathIO.cc


