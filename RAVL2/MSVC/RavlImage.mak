


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlImage
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlImage
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setupRavlImage  $(OPTOBJDIR)/ImageRectangle.obj $(OPTOBJDIR)/Image.obj $(OPTOBJDIR)/ByteRGBValue.obj $(OPTOBJDIR)/ByteYUVValue.obj $(OPTOBJDIR)/RealRGBValue.obj $(OPTOBJDIR)/RealYUVValue.obj $(OPTOBJDIR)/RGBcYUV.obj $(OPTOBJDIR)/Font.obj $(OPTOBJDIR)/ImageConv.obj $(OPTOBJDIR)/ImageConv2.obj $(OPTOBJDIR)/ImageConv3.obj $(OPTOBJDIR)/ImageConv4.obj $(OPTOBJDIR)/ByteRGBAValue.obj $(OPTOBJDIR)/ByteVYUValue.obj $(OPTOBJDIR)/ByteYUV422Value.obj $(OPTOBJDIR)/ByteYUVAValue.obj $(OPTOBJDIR)/RealDVSRGBValue.obj $(OPTOBJDIR)/RealDVSYUVValue.obj $(OPTOBJDIR)/dvsRGBcdvsYUV422.obj $(OPTOBJDIR)/ImageConvSSE.obj $(OPTOBJDIR)/InitImageConvSSE.obj
	@echo -- making $(OPTLIBDIR)/RavlImage.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlImage.lib $(OPTOBJDIR)/*.obj


debug:: setupRavlImage  $(DEBUGOBJDIR)/ImageRectangle.obj $(DEBUGOBJDIR)/Image.obj $(DEBUGOBJDIR)/ByteRGBValue.obj $(DEBUGOBJDIR)/ByteYUVValue.obj $(DEBUGOBJDIR)/RealRGBValue.obj $(DEBUGOBJDIR)/RealYUVValue.obj $(DEBUGOBJDIR)/RGBcYUV.obj $(DEBUGOBJDIR)/Font.obj $(DEBUGOBJDIR)/ImageConv.obj $(DEBUGOBJDIR)/ImageConv2.obj $(DEBUGOBJDIR)/ImageConv3.obj $(DEBUGOBJDIR)/ImageConv4.obj $(DEBUGOBJDIR)/ByteRGBAValue.obj $(DEBUGOBJDIR)/ByteVYUValue.obj $(DEBUGOBJDIR)/ByteYUV422Value.obj $(DEBUGOBJDIR)/ByteYUVAValue.obj $(DEBUGOBJDIR)/RealDVSRGBValue.obj $(DEBUGOBJDIR)/RealDVSYUVValue.obj $(DEBUGOBJDIR)/dvsRGBcdvsYUV422.obj $(DEBUGOBJDIR)/ImageConvSSE.obj $(DEBUGOBJDIR)/InitImageConvSSE.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlImage.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlImage.lib $(DEBUGOBJDIR)/*.obj

setupRavlImage::
        echo --- creating dir for RavlImage
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/ImageRectangle.obj: .././Image/Base/ImageRectangle.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImageRectangle.obj .././Image/Base/ImageRectangle.cc

$(DEBUGOBJDIR)/ImageRectangle.obj: .././Image/Base/ImageRectangle.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImageRectangle.obj .././Image/Base/ImageRectangle.cc

$(OPTOBJDIR)/Image.obj: .././Image/Base/Image.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Image.obj .././Image/Base/Image.cc

$(DEBUGOBJDIR)/Image.obj: .././Image/Base/Image.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Image.obj .././Image/Base/Image.cc

$(OPTOBJDIR)/ByteRGBValue.obj: .././Image/Base/ByteRGBValue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ByteRGBValue.obj .././Image/Base/ByteRGBValue.cc

$(DEBUGOBJDIR)/ByteRGBValue.obj: .././Image/Base/ByteRGBValue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ByteRGBValue.obj .././Image/Base/ByteRGBValue.cc

$(OPTOBJDIR)/ByteYUVValue.obj: .././Image/Base/ByteYUVValue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ByteYUVValue.obj .././Image/Base/ByteYUVValue.cc

$(DEBUGOBJDIR)/ByteYUVValue.obj: .././Image/Base/ByteYUVValue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ByteYUVValue.obj .././Image/Base/ByteYUVValue.cc

$(OPTOBJDIR)/RealRGBValue.obj: .././Image/Base/RealRGBValue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RealRGBValue.obj .././Image/Base/RealRGBValue.cc

$(DEBUGOBJDIR)/RealRGBValue.obj: .././Image/Base/RealRGBValue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RealRGBValue.obj .././Image/Base/RealRGBValue.cc

$(OPTOBJDIR)/RealYUVValue.obj: .././Image/Base/RealYUVValue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RealYUVValue.obj .././Image/Base/RealYUVValue.cc

$(DEBUGOBJDIR)/RealYUVValue.obj: .././Image/Base/RealYUVValue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RealYUVValue.obj .././Image/Base/RealYUVValue.cc

$(OPTOBJDIR)/RGBcYUV.obj: .././Image/Base/RGBcYUV.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RGBcYUV.obj .././Image/Base/RGBcYUV.cc

$(DEBUGOBJDIR)/RGBcYUV.obj: .././Image/Base/RGBcYUV.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RGBcYUV.obj .././Image/Base/RGBcYUV.cc

$(OPTOBJDIR)/Font.obj: .././Image/Base/Font.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Font.obj .././Image/Base/Font.cc

$(DEBUGOBJDIR)/Font.obj: .././Image/Base/Font.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Font.obj .././Image/Base/Font.cc

$(OPTOBJDIR)/ImageConv.obj: .././Image/Base/ImageConv.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImageConv.obj .././Image/Base/ImageConv.cc

$(DEBUGOBJDIR)/ImageConv.obj: .././Image/Base/ImageConv.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImageConv.obj .././Image/Base/ImageConv.cc

$(OPTOBJDIR)/ImageConv2.obj: .././Image/Base/ImageConv2.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImageConv2.obj .././Image/Base/ImageConv2.cc

$(DEBUGOBJDIR)/ImageConv2.obj: .././Image/Base/ImageConv2.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImageConv2.obj .././Image/Base/ImageConv2.cc

$(OPTOBJDIR)/ImageConv3.obj: .././Image/Base/ImageConv3.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImageConv3.obj .././Image/Base/ImageConv3.cc

$(DEBUGOBJDIR)/ImageConv3.obj: .././Image/Base/ImageConv3.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImageConv3.obj .././Image/Base/ImageConv3.cc

$(OPTOBJDIR)/ImageConv4.obj: .././Image/Base/ImageConv4.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImageConv4.obj .././Image/Base/ImageConv4.cc

$(DEBUGOBJDIR)/ImageConv4.obj: .././Image/Base/ImageConv4.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImageConv4.obj .././Image/Base/ImageConv4.cc

$(OPTOBJDIR)/ByteRGBAValue.obj: .././Image/Base/ByteRGBAValue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ByteRGBAValue.obj .././Image/Base/ByteRGBAValue.cc

$(DEBUGOBJDIR)/ByteRGBAValue.obj: .././Image/Base/ByteRGBAValue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ByteRGBAValue.obj .././Image/Base/ByteRGBAValue.cc

$(OPTOBJDIR)/ByteVYUValue.obj: .././Image/Base/ByteVYUValue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ByteVYUValue.obj .././Image/Base/ByteVYUValue.cc

$(DEBUGOBJDIR)/ByteVYUValue.obj: .././Image/Base/ByteVYUValue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ByteVYUValue.obj .././Image/Base/ByteVYUValue.cc

$(OPTOBJDIR)/ByteYUV422Value.obj: .././Image/Base/ByteYUV422Value.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ByteYUV422Value.obj .././Image/Base/ByteYUV422Value.cc

$(DEBUGOBJDIR)/ByteYUV422Value.obj: .././Image/Base/ByteYUV422Value.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ByteYUV422Value.obj .././Image/Base/ByteYUV422Value.cc

$(OPTOBJDIR)/ByteYUVAValue.obj: .././Image/Base/ByteYUVAValue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ByteYUVAValue.obj .././Image/Base/ByteYUVAValue.cc

$(DEBUGOBJDIR)/ByteYUVAValue.obj: .././Image/Base/ByteYUVAValue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ByteYUVAValue.obj .././Image/Base/ByteYUVAValue.cc

$(OPTOBJDIR)/RealDVSRGBValue.obj: .././Image/Base/RealDVSRGBValue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RealDVSRGBValue.obj .././Image/Base/RealDVSRGBValue.cc

$(DEBUGOBJDIR)/RealDVSRGBValue.obj: .././Image/Base/RealDVSRGBValue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RealDVSRGBValue.obj .././Image/Base/RealDVSRGBValue.cc

$(OPTOBJDIR)/RealDVSYUVValue.obj: .././Image/Base/RealDVSYUVValue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RealDVSYUVValue.obj .././Image/Base/RealDVSYUVValue.cc

$(DEBUGOBJDIR)/RealDVSYUVValue.obj: .././Image/Base/RealDVSYUVValue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RealDVSYUVValue.obj .././Image/Base/RealDVSYUVValue.cc

$(OPTOBJDIR)/dvsRGBcdvsYUV422.obj: .././Image/Base/dvsRGBcdvsYUV422.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/dvsRGBcdvsYUV422.obj .././Image/Base/dvsRGBcdvsYUV422.cc

$(DEBUGOBJDIR)/dvsRGBcdvsYUV422.obj: .././Image/Base/dvsRGBcdvsYUV422.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/dvsRGBcdvsYUV422.obj .././Image/Base/dvsRGBcdvsYUV422.cc

$(OPTOBJDIR)/ImageConvSSE.obj: .././Image/BaseSSE/ImageConvSSE.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImageConvSSE.obj .././Image/BaseSSE/ImageConvSSE.cc

$(DEBUGOBJDIR)/ImageConvSSE.obj: .././Image/BaseSSE/ImageConvSSE.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImageConvSSE.obj .././Image/BaseSSE/ImageConvSSE.cc

$(OPTOBJDIR)/InitImageConvSSE.obj: .././Image/BaseSSE/InitImageConvSSE.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/InitImageConvSSE.obj .././Image/BaseSSE/InitImageConvSSE.cc

$(DEBUGOBJDIR)/InitImageConvSSE.obj: .././Image/BaseSSE/InitImageConvSSE.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/InitImageConvSSE.obj .././Image/BaseSSE/InitImageConvSSE.cc


