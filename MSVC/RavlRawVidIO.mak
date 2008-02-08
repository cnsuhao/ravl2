


#--------------------------
# Compiler and flags etc
#--------------------------
CC = cl.exe

LD = lib.exe

INCLUDES =  /I "include\Win32" /I "include" /I "c:/Program Files/Microsoft Visual Studio 8/VC/ATLMFC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/include" /I "c:/Program Files/Microsoft Visual Studio 8/SDK/v2.0/include" /I "C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\Include" /I "C:\GTKWIN32\include" 

DEFINES = /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2=1" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_SCL_SECURE=0" /D "_UNICODE" /D "UNICODE"


OPTFLAGS = /nologo /c /O2 /Ob1 /EHsc /MD /TP

DEBUGFLAGS = /nologo /c /Ob1 /EHsc /MD /TP

#-----------------------------------------------------------------------------
# OK lets define some of our output directories and define script to make them
#-----------------------------------------------------------------------------
DEBUGOBJDIR = c:\Build/win32/debug/obj/RavlRawVidIO
DEBUGLIBDIR = c:\Build/win32/debug/lib

OPTOBJDIR = c:\Build/win32/opt/obj/RavlRawVidIO
OPTLIBDIR = c:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/ImgIOdvsyuv.obj $(OPTOBJDIR)/ImgIOdvsrgb.obj $(OPTOBJDIR)/dvsFormat.obj $(OPTOBJDIR)/GrabfileReader.obj $(OPTOBJDIR)/GrabfileReaderV1.obj $(OPTOBJDIR)/GrabfileWriterV1.obj $(OPTOBJDIR)/LegacyGrabfileReader.obj $(OPTOBJDIR)/NewGrabfileReader.obj $(OPTOBJDIR)/NewGrabfileWriter.obj $(OPTOBJDIR)/Utilities.obj $(OPTOBJDIR)/RavlRawVidIO.obj
	@echo -- making $(OPTLIBDIR)/RavlRawVidIO.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlRawVidIO.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/ImgIOdvsyuv.obj $(DEBUGOBJDIR)/ImgIOdvsrgb.obj $(DEBUGOBJDIR)/dvsFormat.obj $(DEBUGOBJDIR)/GrabfileReader.obj $(DEBUGOBJDIR)/GrabfileReaderV1.obj $(DEBUGOBJDIR)/GrabfileWriterV1.obj $(DEBUGOBJDIR)/LegacyGrabfileReader.obj $(DEBUGOBJDIR)/NewGrabfileReader.obj $(DEBUGOBJDIR)/NewGrabfileWriter.obj $(DEBUGOBJDIR)/Utilities.obj $(DEBUGOBJDIR)/RavlRawVidIO.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlRawVidIO.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlRawVidIO.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlRawVidIO
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/ImgIOdvsyuv.obj: .././Contrib/RawVidFileFormat/ImgIOdvsyuv.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOdvsyuv.obj .././Contrib/RawVidFileFormat/ImgIOdvsyuv.cc

$(DEBUGOBJDIR)/ImgIOdvsyuv.obj: .././Contrib/RawVidFileFormat/ImgIOdvsyuv.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOdvsyuv.obj .././Contrib/RawVidFileFormat/ImgIOdvsyuv.cc

$(OPTOBJDIR)/ImgIOdvsrgb.obj: .././Contrib/RawVidFileFormat/ImgIOdvsrgb.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOdvsrgb.obj .././Contrib/RawVidFileFormat/ImgIOdvsrgb.cc

$(DEBUGOBJDIR)/ImgIOdvsrgb.obj: .././Contrib/RawVidFileFormat/ImgIOdvsrgb.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOdvsrgb.obj .././Contrib/RawVidFileFormat/ImgIOdvsrgb.cc

$(OPTOBJDIR)/dvsFormat.obj: .././Contrib/RawVidFileFormat/dvsFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/dvsFormat.obj .././Contrib/RawVidFileFormat/dvsFormat.cc

$(DEBUGOBJDIR)/dvsFormat.obj: .././Contrib/RawVidFileFormat/dvsFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/dvsFormat.obj .././Contrib/RawVidFileFormat/dvsFormat.cc

$(OPTOBJDIR)/GrabfileReader.obj: .././Contrib/RawVidFileFormat/GrabfileReader.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/GrabfileReader.obj .././Contrib/RawVidFileFormat/GrabfileReader.cc

$(DEBUGOBJDIR)/GrabfileReader.obj: .././Contrib/RawVidFileFormat/GrabfileReader.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/GrabfileReader.obj .././Contrib/RawVidFileFormat/GrabfileReader.cc

$(OPTOBJDIR)/GrabfileReaderV1.obj: .././Contrib/RawVidFileFormat/GrabfileReaderV1.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/GrabfileReaderV1.obj .././Contrib/RawVidFileFormat/GrabfileReaderV1.cc

$(DEBUGOBJDIR)/GrabfileReaderV1.obj: .././Contrib/RawVidFileFormat/GrabfileReaderV1.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/GrabfileReaderV1.obj .././Contrib/RawVidFileFormat/GrabfileReaderV1.cc

$(OPTOBJDIR)/GrabfileWriterV1.obj: .././Contrib/RawVidFileFormat/GrabfileWriterV1.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/GrabfileWriterV1.obj .././Contrib/RawVidFileFormat/GrabfileWriterV1.cc

$(DEBUGOBJDIR)/GrabfileWriterV1.obj: .././Contrib/RawVidFileFormat/GrabfileWriterV1.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/GrabfileWriterV1.obj .././Contrib/RawVidFileFormat/GrabfileWriterV1.cc

$(OPTOBJDIR)/LegacyGrabfileReader.obj: .././Contrib/RawVidFileFormat/LegacyGrabfileReader.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LegacyGrabfileReader.obj .././Contrib/RawVidFileFormat/LegacyGrabfileReader.cc

$(DEBUGOBJDIR)/LegacyGrabfileReader.obj: .././Contrib/RawVidFileFormat/LegacyGrabfileReader.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LegacyGrabfileReader.obj .././Contrib/RawVidFileFormat/LegacyGrabfileReader.cc

$(OPTOBJDIR)/NewGrabfileReader.obj: .././Contrib/RawVidFileFormat/NewGrabfileReader.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NewGrabfileReader.obj .././Contrib/RawVidFileFormat/NewGrabfileReader.cc

$(DEBUGOBJDIR)/NewGrabfileReader.obj: .././Contrib/RawVidFileFormat/NewGrabfileReader.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NewGrabfileReader.obj .././Contrib/RawVidFileFormat/NewGrabfileReader.cc

$(OPTOBJDIR)/NewGrabfileWriter.obj: .././Contrib/RawVidFileFormat/NewGrabfileWriter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NewGrabfileWriter.obj .././Contrib/RawVidFileFormat/NewGrabfileWriter.cc

$(DEBUGOBJDIR)/NewGrabfileWriter.obj: .././Contrib/RawVidFileFormat/NewGrabfileWriter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NewGrabfileWriter.obj .././Contrib/RawVidFileFormat/NewGrabfileWriter.cc

$(OPTOBJDIR)/Utilities.obj: .././Contrib/RawVidFileFormat/Utilities.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Utilities.obj .././Contrib/RawVidFileFormat/Utilities.cc

$(DEBUGOBJDIR)/Utilities.obj: .././Contrib/RawVidFileFormat/Utilities.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Utilities.obj .././Contrib/RawVidFileFormat/Utilities.cc

$(OPTOBJDIR)/RavlRawVidIO.obj: .././Contrib/RawVidFileFormat/RavlRawVidIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RavlRawVidIO.obj .././Contrib/RawVidFileFormat/RavlRawVidIO.cc

$(DEBUGOBJDIR)/RavlRawVidIO.obj: .././Contrib/RawVidFileFormat/RavlRawVidIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RavlRawVidIO.obj .././Contrib/RawVidFileFormat/RavlRawVidIO.cc


