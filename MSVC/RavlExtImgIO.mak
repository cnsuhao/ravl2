


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlExtImgIO
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlExtImgIO
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/ImgIOJPeg.obj $(OPTOBJDIR)/JPEGFormat.obj $(OPTOBJDIR)/ImgIOPNG.obj $(OPTOBJDIR)/PNGFormat.obj $(OPTOBJDIR)/ImgIOTiff.obj $(OPTOBJDIR)/TiffFormat.obj $(OPTOBJDIR)/CompressedImageJPEG.obj $(OPTOBJDIR)/ExtImgIO.obj
	@echo -- making $(OPTLIBDIR)/RavlExtImgIO.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlExtImgIO.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/ImgIOJPeg.obj $(DEBUGOBJDIR)/JPEGFormat.obj $(DEBUGOBJDIR)/ImgIOPNG.obj $(DEBUGOBJDIR)/PNGFormat.obj $(DEBUGOBJDIR)/ImgIOTiff.obj $(DEBUGOBJDIR)/TiffFormat.obj $(DEBUGOBJDIR)/CompressedImageJPEG.obj $(DEBUGOBJDIR)/ExtImgIO.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlExtImgIO.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlExtImgIO.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlExtImgIO
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/ImgIOJPeg.obj: .././Image/ExternalImageIO/ImgIOJPeg.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOJPeg.obj .././Image/ExternalImageIO/ImgIOJPeg.cc

$(DEBUGOBJDIR)/ImgIOJPeg.obj: .././Image/ExternalImageIO/ImgIOJPeg.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOJPeg.obj .././Image/ExternalImageIO/ImgIOJPeg.cc

$(OPTOBJDIR)/JPEGFormat.obj: .././Image/ExternalImageIO/JPEGFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/JPEGFormat.obj .././Image/ExternalImageIO/JPEGFormat.cc

$(DEBUGOBJDIR)/JPEGFormat.obj: .././Image/ExternalImageIO/JPEGFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/JPEGFormat.obj .././Image/ExternalImageIO/JPEGFormat.cc

$(OPTOBJDIR)/ImgIOPNG.obj: .././Image/ExternalImageIO/ImgIOPNG.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOPNG.obj .././Image/ExternalImageIO/ImgIOPNG.cc

$(DEBUGOBJDIR)/ImgIOPNG.obj: .././Image/ExternalImageIO/ImgIOPNG.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOPNG.obj .././Image/ExternalImageIO/ImgIOPNG.cc

$(OPTOBJDIR)/PNGFormat.obj: .././Image/ExternalImageIO/PNGFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PNGFormat.obj .././Image/ExternalImageIO/PNGFormat.cc

$(DEBUGOBJDIR)/PNGFormat.obj: .././Image/ExternalImageIO/PNGFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PNGFormat.obj .././Image/ExternalImageIO/PNGFormat.cc

$(OPTOBJDIR)/ImgIOTiff.obj: .././Image/ExternalImageIO/ImgIOTiff.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOTiff.obj .././Image/ExternalImageIO/ImgIOTiff.cc

$(DEBUGOBJDIR)/ImgIOTiff.obj: .././Image/ExternalImageIO/ImgIOTiff.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOTiff.obj .././Image/ExternalImageIO/ImgIOTiff.cc

$(OPTOBJDIR)/TiffFormat.obj: .././Image/ExternalImageIO/TiffFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TiffFormat.obj .././Image/ExternalImageIO/TiffFormat.cc

$(DEBUGOBJDIR)/TiffFormat.obj: .././Image/ExternalImageIO/TiffFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TiffFormat.obj .././Image/ExternalImageIO/TiffFormat.cc

$(OPTOBJDIR)/CompressedImageJPEG.obj: .././Image/ExternalImageIO/CompressedImageJPEG.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/CompressedImageJPEG.obj .././Image/ExternalImageIO/CompressedImageJPEG.cc

$(DEBUGOBJDIR)/CompressedImageJPEG.obj: .././Image/ExternalImageIO/CompressedImageJPEG.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/CompressedImageJPEG.obj .././Image/ExternalImageIO/CompressedImageJPEG.cc

$(OPTOBJDIR)/ExtImgIO.obj: .././Image/ExternalImageIO/ExtImgIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ExtImgIO.obj .././Image/ExternalImageIO/ExtImgIO.cc

$(DEBUGOBJDIR)/ExtImgIO.obj: .././Image/ExternalImageIO/ExtImgIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ExtImgIO.obj .././Image/ExternalImageIO/ExtImgIO.cc


