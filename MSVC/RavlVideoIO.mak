


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlVideoIO
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlVideoIO
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/ImgIOCif.obj $(OPTOBJDIR)/CifFormat.obj $(OPTOBJDIR)/ImgIOyuv.obj $(OPTOBJDIR)/yuvFormat.obj $(OPTOBJDIR)/syuvFormat.obj $(OPTOBJDIR)/ImgIOrgb.obj $(OPTOBJDIR)/rgbFormat.obj $(OPTOBJDIR)/rawFormat.obj $(OPTOBJDIR)/ImgIOjs.obj $(OPTOBJDIR)/jsFormat.obj $(OPTOBJDIR)/MultiVidIO.obj $(OPTOBJDIR)/DVFrame.obj $(OPTOBJDIR)/AviIStream.obj $(OPTOBJDIR)/AviOStream.obj $(OPTOBJDIR)/BGRFrmIOAvi.obj $(OPTOBJDIR)/DVFrmIOAvi.obj $(OPTOBJDIR)/AviFormat.obj $(OPTOBJDIR)/RavlVidIO.obj
	@echo -- making $(OPTLIBDIR)/RavlVideoIO.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlVideoIO.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/ImgIOCif.obj $(DEBUGOBJDIR)/CifFormat.obj $(DEBUGOBJDIR)/ImgIOyuv.obj $(DEBUGOBJDIR)/yuvFormat.obj $(DEBUGOBJDIR)/syuvFormat.obj $(DEBUGOBJDIR)/ImgIOrgb.obj $(DEBUGOBJDIR)/rgbFormat.obj $(DEBUGOBJDIR)/rawFormat.obj $(DEBUGOBJDIR)/ImgIOjs.obj $(DEBUGOBJDIR)/jsFormat.obj $(DEBUGOBJDIR)/MultiVidIO.obj $(DEBUGOBJDIR)/DVFrame.obj $(DEBUGOBJDIR)/AviIStream.obj $(DEBUGOBJDIR)/AviOStream.obj $(DEBUGOBJDIR)/BGRFrmIOAvi.obj $(DEBUGOBJDIR)/DVFrmIOAvi.obj $(DEBUGOBJDIR)/AviFormat.obj $(DEBUGOBJDIR)/RavlVidIO.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlVideoIO.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlVideoIO.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlVideoIO
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/ImgIOCif.obj: .././Image/VideoIO/ImgIOCif.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOCif.obj .././Image/VideoIO/ImgIOCif.cc

$(DEBUGOBJDIR)/ImgIOCif.obj: .././Image/VideoIO/ImgIOCif.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOCif.obj .././Image/VideoIO/ImgIOCif.cc

$(OPTOBJDIR)/CifFormat.obj: .././Image/VideoIO/CifFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/CifFormat.obj .././Image/VideoIO/CifFormat.cc

$(DEBUGOBJDIR)/CifFormat.obj: .././Image/VideoIO/CifFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/CifFormat.obj .././Image/VideoIO/CifFormat.cc

$(OPTOBJDIR)/ImgIOyuv.obj: .././Image/VideoIO/ImgIOyuv.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOyuv.obj .././Image/VideoIO/ImgIOyuv.cc

$(DEBUGOBJDIR)/ImgIOyuv.obj: .././Image/VideoIO/ImgIOyuv.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOyuv.obj .././Image/VideoIO/ImgIOyuv.cc

$(OPTOBJDIR)/yuvFormat.obj: .././Image/VideoIO/yuvFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/yuvFormat.obj .././Image/VideoIO/yuvFormat.cc

$(DEBUGOBJDIR)/yuvFormat.obj: .././Image/VideoIO/yuvFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/yuvFormat.obj .././Image/VideoIO/yuvFormat.cc

$(OPTOBJDIR)/syuvFormat.obj: .././Image/VideoIO/syuvFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/syuvFormat.obj .././Image/VideoIO/syuvFormat.cc

$(DEBUGOBJDIR)/syuvFormat.obj: .././Image/VideoIO/syuvFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/syuvFormat.obj .././Image/VideoIO/syuvFormat.cc

$(OPTOBJDIR)/ImgIOrgb.obj: .././Image/VideoIO/ImgIOrgb.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOrgb.obj .././Image/VideoIO/ImgIOrgb.cc

$(DEBUGOBJDIR)/ImgIOrgb.obj: .././Image/VideoIO/ImgIOrgb.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOrgb.obj .././Image/VideoIO/ImgIOrgb.cc

$(OPTOBJDIR)/rgbFormat.obj: .././Image/VideoIO/rgbFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/rgbFormat.obj .././Image/VideoIO/rgbFormat.cc

$(DEBUGOBJDIR)/rgbFormat.obj: .././Image/VideoIO/rgbFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/rgbFormat.obj .././Image/VideoIO/rgbFormat.cc

$(OPTOBJDIR)/rawFormat.obj: .././Image/VideoIO/rawFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/rawFormat.obj .././Image/VideoIO/rawFormat.cc

$(DEBUGOBJDIR)/rawFormat.obj: .././Image/VideoIO/rawFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/rawFormat.obj .././Image/VideoIO/rawFormat.cc

$(OPTOBJDIR)/ImgIOjs.obj: .././Image/VideoIO/ImgIOjs.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOjs.obj .././Image/VideoIO/ImgIOjs.cc

$(DEBUGOBJDIR)/ImgIOjs.obj: .././Image/VideoIO/ImgIOjs.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOjs.obj .././Image/VideoIO/ImgIOjs.cc

$(OPTOBJDIR)/jsFormat.obj: .././Image/VideoIO/jsFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/jsFormat.obj .././Image/VideoIO/jsFormat.cc

$(DEBUGOBJDIR)/jsFormat.obj: .././Image/VideoIO/jsFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/jsFormat.obj .././Image/VideoIO/jsFormat.cc

$(OPTOBJDIR)/MultiVidIO.obj: .././Image/VideoIO/MultiVidIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MultiVidIO.obj .././Image/VideoIO/MultiVidIO.cc

$(DEBUGOBJDIR)/MultiVidIO.obj: .././Image/VideoIO/MultiVidIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MultiVidIO.obj .././Image/VideoIO/MultiVidIO.cc

$(OPTOBJDIR)/DVFrame.obj: .././Image/VideoIO/DVFrame.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DVFrame.obj .././Image/VideoIO/DVFrame.cc

$(DEBUGOBJDIR)/DVFrame.obj: .././Image/VideoIO/DVFrame.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DVFrame.obj .././Image/VideoIO/DVFrame.cc

$(OPTOBJDIR)/AviIStream.obj: .././Image/VideoIO/AviIStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AviIStream.obj .././Image/VideoIO/AviIStream.cc

$(DEBUGOBJDIR)/AviIStream.obj: .././Image/VideoIO/AviIStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AviIStream.obj .././Image/VideoIO/AviIStream.cc

$(OPTOBJDIR)/AviOStream.obj: .././Image/VideoIO/AviOStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AviOStream.obj .././Image/VideoIO/AviOStream.cc

$(DEBUGOBJDIR)/AviOStream.obj: .././Image/VideoIO/AviOStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AviOStream.obj .././Image/VideoIO/AviOStream.cc

$(OPTOBJDIR)/BGRFrmIOAvi.obj: .././Image/VideoIO/BGRFrmIOAvi.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/BGRFrmIOAvi.obj .././Image/VideoIO/BGRFrmIOAvi.cc

$(DEBUGOBJDIR)/BGRFrmIOAvi.obj: .././Image/VideoIO/BGRFrmIOAvi.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/BGRFrmIOAvi.obj .././Image/VideoIO/BGRFrmIOAvi.cc

$(OPTOBJDIR)/DVFrmIOAvi.obj: .././Image/VideoIO/DVFrmIOAvi.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DVFrmIOAvi.obj .././Image/VideoIO/DVFrmIOAvi.cc

$(DEBUGOBJDIR)/DVFrmIOAvi.obj: .././Image/VideoIO/DVFrmIOAvi.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DVFrmIOAvi.obj .././Image/VideoIO/DVFrmIOAvi.cc

$(OPTOBJDIR)/AviFormat.obj: .././Image/VideoIO/AviFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AviFormat.obj .././Image/VideoIO/AviFormat.cc

$(DEBUGOBJDIR)/AviFormat.obj: .././Image/VideoIO/AviFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AviFormat.obj .././Image/VideoIO/AviFormat.cc

$(OPTOBJDIR)/RavlVidIO.obj: .././Image/VideoIO/RavlVidIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RavlVidIO.obj .././Image/VideoIO/RavlVidIO.cc

$(DEBUGOBJDIR)/RavlVidIO.obj: .././Image/VideoIO/RavlVidIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RavlVidIO.obj .././Image/VideoIO/RavlVidIO.cc


