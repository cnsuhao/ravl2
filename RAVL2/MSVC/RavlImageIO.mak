


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlImageIO
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlImageIO
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setupRavlImageIO  $(OPTOBJDIR)/ImgIOPNM.obj $(OPTOBJDIR)/PNMFormat.obj $(OPTOBJDIR)/ImgIOInt.obj $(OPTOBJDIR)/ImgIOByte.obj $(OPTOBJDIR)/ImgIOUInt16.obj $(OPTOBJDIR)/ImgIOByteRGB.obj $(OPTOBJDIR)/ImgIOByteYUV.obj $(OPTOBJDIR)/ImgIOReal.obj $(OPTOBJDIR)/ImgIORealRGB.obj $(OPTOBJDIR)/ImgIOByteRGBA.obj $(OPTOBJDIR)/ImgIORealYUV.obj $(OPTOBJDIR)/ImgIOUInt16RGB.obj $(OPTOBJDIR)/ImgIOByteYUVA.obj $(OPTOBJDIR)/ImgCnvRGB.obj $(OPTOBJDIR)/ImgCnvYUV.obj $(OPTOBJDIR)/ImgIOFloat.obj $(OPTOBJDIR)/ImgTypeCnv.obj $(OPTOBJDIR)/ImgTypeCnv2.obj $(OPTOBJDIR)/ImgTypeCnv3.obj $(OPTOBJDIR)/ImgTypeCnv4.obj $(OPTOBJDIR)/ImgIOByteYUV422.obj $(OPTOBJDIR)/ImgIOByteVYU.obj $(OPTOBJDIR)/ImgTypeCnv5.obj $(OPTOBJDIR)/RavlImgIO.obj
	@echo -- making $(OPTLIBDIR)/RavlImageIO.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlImageIO.lib $(OPTOBJDIR)/*.obj


debug:: setupRavlImageIO  $(DEBUGOBJDIR)/ImgIOPNM.obj $(DEBUGOBJDIR)/PNMFormat.obj $(DEBUGOBJDIR)/ImgIOInt.obj $(DEBUGOBJDIR)/ImgIOByte.obj $(DEBUGOBJDIR)/ImgIOUInt16.obj $(DEBUGOBJDIR)/ImgIOByteRGB.obj $(DEBUGOBJDIR)/ImgIOByteYUV.obj $(DEBUGOBJDIR)/ImgIOReal.obj $(DEBUGOBJDIR)/ImgIORealRGB.obj $(DEBUGOBJDIR)/ImgIOByteRGBA.obj $(DEBUGOBJDIR)/ImgIORealYUV.obj $(DEBUGOBJDIR)/ImgIOUInt16RGB.obj $(DEBUGOBJDIR)/ImgIOByteYUVA.obj $(DEBUGOBJDIR)/ImgCnvRGB.obj $(DEBUGOBJDIR)/ImgCnvYUV.obj $(DEBUGOBJDIR)/ImgIOFloat.obj $(DEBUGOBJDIR)/ImgTypeCnv.obj $(DEBUGOBJDIR)/ImgTypeCnv2.obj $(DEBUGOBJDIR)/ImgTypeCnv3.obj $(DEBUGOBJDIR)/ImgTypeCnv4.obj $(DEBUGOBJDIR)/ImgIOByteYUV422.obj $(DEBUGOBJDIR)/ImgIOByteVYU.obj $(DEBUGOBJDIR)/ImgTypeCnv5.obj $(DEBUGOBJDIR)/RavlImgIO.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlImageIO.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlImageIO.lib $(DEBUGOBJDIR)/*.obj

setupRavlImageIO::
        echo --- creating dir for RavlImageIO
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/ImgIOPNM.obj: .././Image/ImageIO/ImgIOPNM.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOPNM.obj .././Image/ImageIO/ImgIOPNM.cc

$(DEBUGOBJDIR)/ImgIOPNM.obj: .././Image/ImageIO/ImgIOPNM.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOPNM.obj .././Image/ImageIO/ImgIOPNM.cc

$(OPTOBJDIR)/PNMFormat.obj: .././Image/ImageIO/PNMFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PNMFormat.obj .././Image/ImageIO/PNMFormat.cc

$(DEBUGOBJDIR)/PNMFormat.obj: .././Image/ImageIO/PNMFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PNMFormat.obj .././Image/ImageIO/PNMFormat.cc

$(OPTOBJDIR)/ImgIOInt.obj: .././Image/ImageIO/ImgIOInt.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOInt.obj .././Image/ImageIO/ImgIOInt.cc

$(DEBUGOBJDIR)/ImgIOInt.obj: .././Image/ImageIO/ImgIOInt.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOInt.obj .././Image/ImageIO/ImgIOInt.cc

$(OPTOBJDIR)/ImgIOByte.obj: .././Image/ImageIO/ImgIOByte.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOByte.obj .././Image/ImageIO/ImgIOByte.cc

$(DEBUGOBJDIR)/ImgIOByte.obj: .././Image/ImageIO/ImgIOByte.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOByte.obj .././Image/ImageIO/ImgIOByte.cc

$(OPTOBJDIR)/ImgIOUInt16.obj: .././Image/ImageIO/ImgIOUInt16.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOUInt16.obj .././Image/ImageIO/ImgIOUInt16.cc

$(DEBUGOBJDIR)/ImgIOUInt16.obj: .././Image/ImageIO/ImgIOUInt16.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOUInt16.obj .././Image/ImageIO/ImgIOUInt16.cc

$(OPTOBJDIR)/ImgIOByteRGB.obj: .././Image/ImageIO/ImgIOByteRGB.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOByteRGB.obj .././Image/ImageIO/ImgIOByteRGB.cc

$(DEBUGOBJDIR)/ImgIOByteRGB.obj: .././Image/ImageIO/ImgIOByteRGB.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOByteRGB.obj .././Image/ImageIO/ImgIOByteRGB.cc

$(OPTOBJDIR)/ImgIOByteYUV.obj: .././Image/ImageIO/ImgIOByteYUV.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOByteYUV.obj .././Image/ImageIO/ImgIOByteYUV.cc

$(DEBUGOBJDIR)/ImgIOByteYUV.obj: .././Image/ImageIO/ImgIOByteYUV.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOByteYUV.obj .././Image/ImageIO/ImgIOByteYUV.cc

$(OPTOBJDIR)/ImgIOReal.obj: .././Image/ImageIO/ImgIOReal.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOReal.obj .././Image/ImageIO/ImgIOReal.cc

$(DEBUGOBJDIR)/ImgIOReal.obj: .././Image/ImageIO/ImgIOReal.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOReal.obj .././Image/ImageIO/ImgIOReal.cc

$(OPTOBJDIR)/ImgIORealRGB.obj: .././Image/ImageIO/ImgIORealRGB.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIORealRGB.obj .././Image/ImageIO/ImgIORealRGB.cc

$(DEBUGOBJDIR)/ImgIORealRGB.obj: .././Image/ImageIO/ImgIORealRGB.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIORealRGB.obj .././Image/ImageIO/ImgIORealRGB.cc

$(OPTOBJDIR)/ImgIOByteRGBA.obj: .././Image/ImageIO/ImgIOByteRGBA.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOByteRGBA.obj .././Image/ImageIO/ImgIOByteRGBA.cc

$(DEBUGOBJDIR)/ImgIOByteRGBA.obj: .././Image/ImageIO/ImgIOByteRGBA.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOByteRGBA.obj .././Image/ImageIO/ImgIOByteRGBA.cc

$(OPTOBJDIR)/ImgIORealYUV.obj: .././Image/ImageIO/ImgIORealYUV.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIORealYUV.obj .././Image/ImageIO/ImgIORealYUV.cc

$(DEBUGOBJDIR)/ImgIORealYUV.obj: .././Image/ImageIO/ImgIORealYUV.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIORealYUV.obj .././Image/ImageIO/ImgIORealYUV.cc

$(OPTOBJDIR)/ImgIOUInt16RGB.obj: .././Image/ImageIO/ImgIOUInt16RGB.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOUInt16RGB.obj .././Image/ImageIO/ImgIOUInt16RGB.cc

$(DEBUGOBJDIR)/ImgIOUInt16RGB.obj: .././Image/ImageIO/ImgIOUInt16RGB.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOUInt16RGB.obj .././Image/ImageIO/ImgIOUInt16RGB.cc

$(OPTOBJDIR)/ImgIOByteYUVA.obj: .././Image/ImageIO/ImgIOByteYUVA.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOByteYUVA.obj .././Image/ImageIO/ImgIOByteYUVA.cc

$(DEBUGOBJDIR)/ImgIOByteYUVA.obj: .././Image/ImageIO/ImgIOByteYUVA.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOByteYUVA.obj .././Image/ImageIO/ImgIOByteYUVA.cc

$(OPTOBJDIR)/ImgCnvRGB.obj: .././Image/ImageIO/ImgCnvRGB.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgCnvRGB.obj .././Image/ImageIO/ImgCnvRGB.cc

$(DEBUGOBJDIR)/ImgCnvRGB.obj: .././Image/ImageIO/ImgCnvRGB.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgCnvRGB.obj .././Image/ImageIO/ImgCnvRGB.cc

$(OPTOBJDIR)/ImgCnvYUV.obj: .././Image/ImageIO/ImgCnvYUV.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgCnvYUV.obj .././Image/ImageIO/ImgCnvYUV.cc

$(DEBUGOBJDIR)/ImgCnvYUV.obj: .././Image/ImageIO/ImgCnvYUV.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgCnvYUV.obj .././Image/ImageIO/ImgCnvYUV.cc

$(OPTOBJDIR)/ImgIOFloat.obj: .././Image/ImageIO/ImgIOFloat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOFloat.obj .././Image/ImageIO/ImgIOFloat.cc

$(DEBUGOBJDIR)/ImgIOFloat.obj: .././Image/ImageIO/ImgIOFloat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOFloat.obj .././Image/ImageIO/ImgIOFloat.cc

$(OPTOBJDIR)/ImgTypeCnv.obj: .././Image/ImageIO/ImgTypeCnv.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgTypeCnv.obj .././Image/ImageIO/ImgTypeCnv.cc

$(DEBUGOBJDIR)/ImgTypeCnv.obj: .././Image/ImageIO/ImgTypeCnv.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgTypeCnv.obj .././Image/ImageIO/ImgTypeCnv.cc

$(OPTOBJDIR)/ImgTypeCnv2.obj: .././Image/ImageIO/ImgTypeCnv2.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgTypeCnv2.obj .././Image/ImageIO/ImgTypeCnv2.cc

$(DEBUGOBJDIR)/ImgTypeCnv2.obj: .././Image/ImageIO/ImgTypeCnv2.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgTypeCnv2.obj .././Image/ImageIO/ImgTypeCnv2.cc

$(OPTOBJDIR)/ImgTypeCnv3.obj: .././Image/ImageIO/ImgTypeCnv3.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgTypeCnv3.obj .././Image/ImageIO/ImgTypeCnv3.cc

$(DEBUGOBJDIR)/ImgTypeCnv3.obj: .././Image/ImageIO/ImgTypeCnv3.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgTypeCnv3.obj .././Image/ImageIO/ImgTypeCnv3.cc

$(OPTOBJDIR)/ImgTypeCnv4.obj: .././Image/ImageIO/ImgTypeCnv4.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgTypeCnv4.obj .././Image/ImageIO/ImgTypeCnv4.cc

$(DEBUGOBJDIR)/ImgTypeCnv4.obj: .././Image/ImageIO/ImgTypeCnv4.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgTypeCnv4.obj .././Image/ImageIO/ImgTypeCnv4.cc

$(OPTOBJDIR)/ImgIOByteYUV422.obj: .././Image/ImageIO/ImgIOByteYUV422.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOByteYUV422.obj .././Image/ImageIO/ImgIOByteYUV422.cc

$(DEBUGOBJDIR)/ImgIOByteYUV422.obj: .././Image/ImageIO/ImgIOByteYUV422.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOByteYUV422.obj .././Image/ImageIO/ImgIOByteYUV422.cc

$(OPTOBJDIR)/ImgIOByteVYU.obj: .././Image/ImageIO/ImgIOByteVYU.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgIOByteVYU.obj .././Image/ImageIO/ImgIOByteVYU.cc

$(DEBUGOBJDIR)/ImgIOByteVYU.obj: .././Image/ImageIO/ImgIOByteVYU.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgIOByteVYU.obj .././Image/ImageIO/ImgIOByteVYU.cc

$(OPTOBJDIR)/ImgTypeCnv5.obj: .././Image/ImageIO/ImgTypeCnv5.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImgTypeCnv5.obj .././Image/ImageIO/ImgTypeCnv5.cc

$(DEBUGOBJDIR)/ImgTypeCnv5.obj: .././Image/ImageIO/ImgTypeCnv5.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImgTypeCnv5.obj .././Image/ImageIO/ImgTypeCnv5.cc

$(OPTOBJDIR)/RavlImgIO.obj: .././Image/ImageIO/RavlImgIO.cc  
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RavlImgIO.obj .././Image/ImageIO/RavlImgIO.cc 

$(DEBUGOBJDIR)/RavlImgIO.obj: .././Image/ImageIO/RavlImgIO.cc  
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RavlImgIO.obj .././Image/ImageIO/RavlImgIO.cc 


