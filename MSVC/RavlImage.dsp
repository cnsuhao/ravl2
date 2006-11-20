# Microsoft Developer Studio Project File - Name="RavlImage" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlImage - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlImage.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlImage.mak" CFG="RavlImage - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlImage - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlImage - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlImage"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlImage"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /MDd  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "_DEBUG" /D "VISUAL_CPP" /D "_LIB" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /GZ /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "RavlImage - Win32 Release"
# Name "RavlImage - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\Image\Base\ImageRectangle.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\Image.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ByteRGBValue.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ByteYUVValue.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\RealRGBValue.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\RealYUVValue.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\RGBcYUV.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\Font.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ImageConv.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ImageConv2.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ImageConv3.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ImageConv4.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ByteRGBAValue.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ByteVYUValue.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ByteYUV422Value.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ByteYUVAValue.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\Image\Base\ImageRectangle.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header ImageRectangle.hh

"C:\Build\inc\Ravl\Image\ImageRectangle.hh" :  "" ""
	copy ..\.\Image\Base\ImageRectangle.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header ImageRectangle.hh

"C:\Build\inc\Ravl\Image\ImageRectangle.hh" :  "" ""
	copy ..\.\Image\Base\ImageRectangle.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\Image.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header Image.hh

"C:\Build\inc\Ravl\Image\Image.hh" :  "" ""
	copy ..\.\Image\Base\Image.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header Image.hh

"C:\Build\inc\Ravl\Image\Image.hh" :  "" ""
	copy ..\.\Image\Base\Image.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\RGBValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header RGBValue.hh

"C:\Build\inc\Ravl\Image\RGBValue.hh" :  "" ""
	copy ..\.\Image\Base\RGBValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header RGBValue.hh

"C:\Build\inc\Ravl\Image\RGBValue.hh" :  "" ""
	copy ..\.\Image\Base\RGBValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\RGBAValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header RGBAValue.hh

"C:\Build\inc\Ravl\Image\RGBAValue.hh" :  "" ""
	copy ..\.\Image\Base\RGBAValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header RGBAValue.hh

"C:\Build\inc\Ravl\Image\RGBAValue.hh" :  "" ""
	copy ..\.\Image\Base\RGBAValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\YUVValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header YUVValue.hh

"C:\Build\inc\Ravl\Image\YUVValue.hh" :  "" ""
	copy ..\.\Image\Base\YUVValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header YUVValue.hh

"C:\Build\inc\Ravl\Image\YUVValue.hh" :  "" ""
	copy ..\.\Image\Base\YUVValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ByteRGBValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header ByteRGBValue.hh

"C:\Build\inc\Ravl\Image\ByteRGBValue.hh" :  "" ""
	copy ..\.\Image\Base\ByteRGBValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header ByteRGBValue.hh

"C:\Build\inc\Ravl\Image\ByteRGBValue.hh" :  "" ""
	copy ..\.\Image\Base\ByteRGBValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ByteYUVValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header ByteYUVValue.hh

"C:\Build\inc\Ravl\Image\ByteYUVValue.hh" :  "" ""
	copy ..\.\Image\Base\ByteYUVValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header ByteYUVValue.hh

"C:\Build\inc\Ravl\Image\ByteYUVValue.hh" :  "" ""
	copy ..\.\Image\Base\ByteYUVValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ByteRGBAValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header ByteRGBAValue.hh

"C:\Build\inc\Ravl\Image\ByteRGBAValue.hh" :  "" ""
	copy ..\.\Image\Base\ByteRGBAValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header ByteRGBAValue.hh

"C:\Build\inc\Ravl\Image\ByteRGBAValue.hh" :  "" ""
	copy ..\.\Image\Base\ByteRGBAValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\IAValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header IAValue.hh

"C:\Build\inc\Ravl\Image\IAValue.hh" :  "" ""
	copy ..\.\Image\Base\IAValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header IAValue.hh

"C:\Build\inc\Ravl\Image\IAValue.hh" :  "" ""
	copy ..\.\Image\Base\IAValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ByteIAValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header ByteIAValue.hh

"C:\Build\inc\Ravl\Image\ByteIAValue.hh" :  "" ""
	copy ..\.\Image\Base\ByteIAValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header ByteIAValue.hh

"C:\Build\inc\Ravl\Image\ByteIAValue.hh" :  "" ""
	copy ..\.\Image\Base\ByteIAValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\RealRGBValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header RealRGBValue.hh

"C:\Build\inc\Ravl\Image\RealRGBValue.hh" :  "" ""
	copy ..\.\Image\Base\RealRGBValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header RealRGBValue.hh

"C:\Build\inc\Ravl\Image\RealRGBValue.hh" :  "" ""
	copy ..\.\Image\Base\RealRGBValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\RealYUVValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header RealYUVValue.hh

"C:\Build\inc\Ravl\Image\RealYUVValue.hh" :  "" ""
	copy ..\.\Image\Base\RealYUVValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header RealYUVValue.hh

"C:\Build\inc\Ravl\Image\RealYUVValue.hh" :  "" ""
	copy ..\.\Image\Base\RealYUVValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\UInt16RGBValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header UInt16RGBValue.hh

"C:\Build\inc\Ravl\Image\UInt16RGBValue.hh" :  "" ""
	copy ..\.\Image\Base\UInt16RGBValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header UInt16RGBValue.hh

"C:\Build\inc\Ravl\Image\UInt16RGBValue.hh" :  "" ""
	copy ..\.\Image\Base\UInt16RGBValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\RGBcYUV.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header RGBcYUV.hh

"C:\Build\inc\Ravl\Image\RGBcYUV.hh" :  "" ""
	copy ..\.\Image\Base\RGBcYUV.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header RGBcYUV.hh

"C:\Build\inc\Ravl\Image\RGBcYUV.hh" :  "" ""
	copy ..\.\Image\Base\RGBcYUV.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\YUVAValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header YUVAValue.hh

"C:\Build\inc\Ravl\Image\YUVAValue.hh" :  "" ""
	copy ..\.\Image\Base\YUVAValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header YUVAValue.hh

"C:\Build\inc\Ravl\Image\YUVAValue.hh" :  "" ""
	copy ..\.\Image\Base\YUVAValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ByteYUVAValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header ByteYUVAValue.hh

"C:\Build\inc\Ravl\Image\ByteYUVAValue.hh" :  "" ""
	copy ..\.\Image\Base\ByteYUVAValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header ByteYUVAValue.hh

"C:\Build\inc\Ravl\Image\ByteYUVAValue.hh" :  "" ""
	copy ..\.\Image\Base\ByteYUVAValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ByteBGRAValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header ByteBGRAValue.hh

"C:\Build\inc\Ravl\Image\ByteBGRAValue.hh" :  "" ""
	copy ..\.\Image\Base\ByteBGRAValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header ByteBGRAValue.hh

"C:\Build\inc\Ravl\Image\ByteBGRAValue.hh" :  "" ""
	copy ..\.\Image\Base\ByteBGRAValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\BGRAValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header BGRAValue.hh

"C:\Build\inc\Ravl\Image\BGRAValue.hh" :  "" ""
	copy ..\.\Image\Base\BGRAValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header BGRAValue.hh

"C:\Build\inc\Ravl\Image\BGRAValue.hh" :  "" ""
	copy ..\.\Image\Base\BGRAValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\BGRValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header BGRValue.hh

"C:\Build\inc\Ravl\Image\BGRValue.hh" :  "" ""
	copy ..\.\Image\Base\BGRValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header BGRValue.hh

"C:\Build\inc\Ravl\Image\BGRValue.hh" :  "" ""
	copy ..\.\Image\Base\BGRValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ByteBGRValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header ByteBGRValue.hh

"C:\Build\inc\Ravl\Image\ByteBGRValue.hh" :  "" ""
	copy ..\.\Image\Base\ByteBGRValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header ByteBGRValue.hh

"C:\Build\inc\Ravl\Image\ByteBGRValue.hh" :  "" ""
	copy ..\.\Image\Base\ByteBGRValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\YUV422Value.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header YUV422Value.hh

"C:\Build\inc\Ravl\Image\YUV422Value.hh" :  "" ""
	copy ..\.\Image\Base\YUV422Value.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header YUV422Value.hh

"C:\Build\inc\Ravl\Image\YUV422Value.hh" :  "" ""
	copy ..\.\Image\Base\YUV422Value.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ByteYUV422Value.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header ByteYUV422Value.hh

"C:\Build\inc\Ravl\Image\ByteYUV422Value.hh" :  "" ""
	copy ..\.\Image\Base\ByteYUV422Value.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header ByteYUV422Value.hh

"C:\Build\inc\Ravl\Image\ByteYUV422Value.hh" :  "" ""
	copy ..\.\Image\Base\ByteYUV422Value.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ByteRGBMedian.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header ByteRGBMedian.hh

"C:\Build\inc\Ravl\Image\ByteRGBMedian.hh" :  "" ""
	copy ..\.\Image\Base\ByteRGBMedian.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header ByteRGBMedian.hh

"C:\Build\inc\Ravl\Image\ByteRGBMedian.hh" :  "" ""
	copy ..\.\Image\Base\ByteRGBMedian.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\RealRGBAverage.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header RealRGBAverage.hh

"C:\Build\inc\Ravl\Image\RealRGBAverage.hh" :  "" ""
	copy ..\.\Image\Base\RealRGBAverage.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header RealRGBAverage.hh

"C:\Build\inc\Ravl\Image\RealRGBAverage.hh" :  "" ""
	copy ..\.\Image\Base\RealRGBAverage.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ScaleValues.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header ScaleValues.hh

"C:\Build\inc\Ravl\Image\ScaleValues.hh" :  "" ""
	copy ..\.\Image\Base\ScaleValues.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header ScaleValues.hh

"C:\Build\inc\Ravl\Image\ScaleValues.hh" :  "" ""
	copy ..\.\Image\Base\ScaleValues.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\Reflect.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header Reflect.hh

"C:\Build\inc\Ravl\Image\Reflect.hh" :  "" ""
	copy ..\.\Image\Base\Reflect.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header Reflect.hh

"C:\Build\inc\Ravl\Image\Reflect.hh" :  "" ""
	copy ..\.\Image\Base\Reflect.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\Deinterlace.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header Deinterlace.hh

"C:\Build\inc\Ravl\Image\Deinterlace.hh" :  "" ""
	copy ..\.\Image\Base\Deinterlace.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header Deinterlace.hh

"C:\Build\inc\Ravl\Image\Deinterlace.hh" :  "" ""
	copy ..\.\Image\Base\Deinterlace.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\VYUValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header VYUValue.hh

"C:\Build\inc\Ravl\Image\VYUValue.hh" :  "" ""
	copy ..\.\Image\Base\VYUValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header VYUValue.hh

"C:\Build\inc\Ravl\Image\VYUValue.hh" :  "" ""
	copy ..\.\Image\Base\VYUValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ByteVYUValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header ByteVYUValue.hh

"C:\Build\inc\Ravl\Image\ByteVYUValue.hh" :  "" ""
	copy ..\.\Image\Base\ByteVYUValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header ByteVYUValue.hh

"C:\Build\inc\Ravl\Image\ByteVYUValue.hh" :  "" ""
	copy ..\.\Image\Base\ByteVYUValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\DrawFrame.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header DrawFrame.hh

"C:\Build\inc\Ravl\Image\DrawFrame.hh" :  "" ""
	copy ..\.\Image\Base\DrawFrame.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header DrawFrame.hh

"C:\Build\inc\Ravl\Image\DrawFrame.hh" :  "" ""
	copy ..\.\Image\Base\DrawFrame.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\DrawCross.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header DrawCross.hh

"C:\Build\inc\Ravl\Image\DrawCross.hh" :  "" ""
	copy ..\.\Image\Base\DrawCross.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header DrawCross.hh

"C:\Build\inc\Ravl\Image\DrawCross.hh" :  "" ""
	copy ..\.\Image\Base\DrawCross.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\DrawMask.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header DrawMask.hh

"C:\Build\inc\Ravl\Image\DrawMask.hh" :  "" ""
	copy ..\.\Image\Base\DrawMask.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header DrawMask.hh

"C:\Build\inc\Ravl\Image\DrawMask.hh" :  "" ""
	copy ..\.\Image\Base\DrawMask.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\Font.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header Font.hh

"C:\Build\inc\Ravl\Image\Font.hh" :  "" ""
	copy ..\.\Image\Base\Font.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header Font.hh

"C:\Build\inc\Ravl\Image\Font.hh" :  "" ""
	copy ..\.\Image\Base\Font.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\PSFFont.h

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header PSFFont.h

"C:\Build\inc\Ravl\Image\PSFFont.h" :  "" ""
	copy ..\.\Image\Base\PSFFont.h C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header PSFFont.h

"C:\Build\inc\Ravl\Image\PSFFont.h" :  "" ""
	copy ..\.\Image\Base\PSFFont.h C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\DrawLine.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header DrawLine.hh

"C:\Build\inc\Ravl\Image\DrawLine.hh" :  "" ""
	copy ..\.\Image\Base\DrawLine.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header DrawLine.hh

"C:\Build\inc\Ravl\Image\DrawLine.hh" :  "" ""
	copy ..\.\Image\Base\DrawLine.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\DrawCircle.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header DrawCircle.hh

"C:\Build\inc\Ravl\Image\DrawCircle.hh" :  "" ""
	copy ..\.\Image\Base\DrawCircle.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header DrawCircle.hh

"C:\Build\inc\Ravl\Image\DrawCircle.hh" :  "" ""
	copy ..\.\Image\Base\DrawCircle.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\DrawPolygon.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header DrawPolygon.hh

"C:\Build\inc\Ravl\Image\DrawPolygon.hh" :  "" ""
	copy ..\.\Image\Base\DrawPolygon.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header DrawPolygon.hh

"C:\Build\inc\Ravl\Image\DrawPolygon.hh" :  "" ""
	copy ..\.\Image\Base\DrawPolygon.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\RealHSVValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header RealHSVValue.hh

"C:\Build\inc\Ravl\Image\RealHSVValue.hh" :  "" ""
	copy ..\.\Image\Base\RealHSVValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header RealHSVValue.hh

"C:\Build\inc\Ravl\Image\RealHSVValue.hh" :  "" ""
	copy ..\.\Image\Base\RealHSVValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\FixedPointHSVValue.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header FixedPointHSVValue.hh

"C:\Build\inc\Ravl\Image\FixedPointHSVValue.hh" :  "" ""
	copy ..\.\Image\Base\FixedPointHSVValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header FixedPointHSVValue.hh

"C:\Build\inc\Ravl\Image\FixedPointHSVValue.hh" :  "" ""
	copy ..\.\Image\Base\FixedPointHSVValue.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\BilinearInterpolation.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header BilinearInterpolation.hh

"C:\Build\inc\Ravl\Image\BilinearInterpolation.hh" :  "" ""
	copy ..\.\Image\Base\BilinearInterpolation.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header BilinearInterpolation.hh

"C:\Build\inc\Ravl\Image\BilinearInterpolation.hh" :  "" ""
	copy ..\.\Image\Base\BilinearInterpolation.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\ImageConv.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header ImageConv.hh

"C:\Build\inc\Ravl\Image\ImageConv.hh" :  "" ""
	copy ..\.\Image\Base\ImageConv.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header ImageConv.hh

"C:\Build\inc\Ravl\Image\ImageConv.hh" :  "" ""
	copy ..\.\Image\Base\ImageConv.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Base\DrawEllipse.hh

!IF  "$(CFG)" == "RavlImage - Win32 Release"

# Begin Custom Build - Install Header DrawEllipse.hh

"C:\Build\inc\Ravl\Image\DrawEllipse.hh" :  "" ""
	copy ..\.\Image\Base\DrawEllipse.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImage - Win32 Debug"

# Begin Custom Build - Install Header DrawEllipse.hh

"C:\Build\inc\Ravl\Image\DrawEllipse.hh" :  "" ""
	copy ..\.\Image\Base\DrawEllipse.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
