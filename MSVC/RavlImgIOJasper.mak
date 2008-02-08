


#--------------------------
# Compiler and flags etc
#--------------------------
CC = cl.exe

LD = lib.exe

INCLUDES =  /I "include\Win32" /I "include" /I "c:/Program Files/Microsoft Visual Studio 8/VC/ATLMFC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/include" /I "c:/Program Files/Microsoft Visual Studio 8/SDK/v2.0/include" /I "C:\GTKWIN32\include" 

DEFINES = /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2=1" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_SCL_SECURE=0" /D "_UNICODE" /D "UNICODE"


OPTFLAGS = /nologo /c /O2 /Ob1 /EHsc /MD /TP

DEBUGFLAGS = /nologo /c /Ob1 /EHsc /MD /TP

#-----------------------------------------------------------------------------
# OK lets define some of our output directories and define script to make them
#-----------------------------------------------------------------------------
DEBUGOBJDIR = c:\Build/win32/debug/obj/RavlImgIOJasper
DEBUGLIBDIR = c:\Build/win32/debug/lib

OPTOBJDIR = c:\Build/win32/opt/obj/RavlImgIOJasper
OPTLIBDIR = c:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/ImgIOJasper.obj $(OPTOBJDIR)/JasperFormat.obj $(OPTOBJDIR)/CompressedImageJ2k.obj $(OPTOBJDIR)/JasperImgIO.obj
	@echo -- making $(OPTLIBDIR)/RavlImgIOJasper.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlImgIOJasper.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/ImgIOJasper.obj $(DEBUGOBJDIR)/JasperFormat.obj $(DEBUGOBJDIR)/CompressedImageJ2k.obj $(DEBUGOBJDIR)/JasperImgIO.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlImgIOJasper.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlImgIOJasper.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlImgIOJasper
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/ImgIOJasper.obj: .././Contrib/Jasper/ImgIOJasper.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOJasper.obj .././Contrib/Jasper/ImgIOJasper.cc

$(DEBUGOBJDIR)/ImgIOJasper.obj: .././Contrib/Jasper/ImgIOJasper.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOJasper.obj .././Contrib/Jasper/ImgIOJasper.cc

$(OPTOBJDIR)/JasperFormat.obj: .././Contrib/Jasper/JasperFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/JasperFormat.obj .././Contrib/Jasper/JasperFormat.cc

$(DEBUGOBJDIR)/JasperFormat.obj: .././Contrib/Jasper/JasperFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/JasperFormat.obj .././Contrib/Jasper/JasperFormat.cc

$(OPTOBJDIR)/CompressedImageJ2k.obj: .././Contrib/Jasper/CompressedImageJ2k.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/CompressedImageJ2k.obj .././Contrib/Jasper/CompressedImageJ2k.cc

$(DEBUGOBJDIR)/CompressedImageJ2k.obj: .././Contrib/Jasper/CompressedImageJ2k.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/CompressedImageJ2k.obj .././Contrib/Jasper/CompressedImageJ2k.cc

$(OPTOBJDIR)/JasperImgIO.obj: .././Contrib/Jasper/JasperImgIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/JasperImgIO.obj .././Contrib/Jasper/JasperImgIO.cc

$(DEBUGOBJDIR)/JasperImgIO.obj: .././Contrib/Jasper/JasperImgIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/JasperImgIO.obj .././Contrib/Jasper/JasperImgIO.cc


