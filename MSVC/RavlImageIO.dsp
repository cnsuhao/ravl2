# Microsoft Developer Studio Project File - Name="RavlImageIO" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlImageIO - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlImageIO.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlImageIO.mak" CFG="RavlImageIO - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlImageIO - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlImageIO - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlImageIO - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlImageIO"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlImageIO - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlImageIO"
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

# Name "RavlImageIO - Win32 Release"
# Name "RavlImageIO - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgIOPNM.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\PNMFormat.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgIOInt.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgIOByte.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgIOUInt16.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgIOByteRGB.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgIOByteYUV.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgIOReal.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgIORealRGB.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgIOByteRGBA.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgIORealYUV.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgIOUInt16RGB.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgIOByteYUVA.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgCnvRGB.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgCnvYUV.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgIOFloat.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgTypeCnv.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgTypeCnv2.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgTypeCnv3.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgTypeCnv4.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgIOByteYUV422.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgIOByteVYU.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgTypeCnv5.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\RavlImgIO.cc 
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgIOPNMB.hh

!IF  "$(CFG)" == "RavlImageIO - Win32 Release"

# Begin Custom Build - Install Header ImgIOPNMB.hh

"C:\Build\inc\Ravl\Image\ImgIOPNMB.hh" :  "" ""
	copy ..\.\Image\ImageIO\ImgIOPNMB.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageIO - Win32 Debug"

# Begin Custom Build - Install Header ImgIOPNMB.hh

"C:\Build\inc\Ravl\Image\ImgIOPNMB.hh" :  "" ""
	copy ..\.\Image\ImageIO\ImgIOPNMB.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgIOPNM.hh

!IF  "$(CFG)" == "RavlImageIO - Win32 Release"

# Begin Custom Build - Install Header ImgIOPNM.hh

"C:\Build\inc\Ravl\Image\ImgIOPNM.hh" :  "" ""
	copy ..\.\Image\ImageIO\ImgIOPNM.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageIO - Win32 Debug"

# Begin Custom Build - Install Header ImgIOPNM.hh

"C:\Build\inc\Ravl\Image\ImgIOPNM.hh" :  "" ""
	copy ..\.\Image\ImageIO\ImgIOPNM.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\PNMFormat.hh

!IF  "$(CFG)" == "RavlImageIO - Win32 Release"

# Begin Custom Build - Install Header PNMFormat.hh

"C:\Build\inc\Ravl\Image\PNMFormat.hh" :  "" ""
	copy ..\.\Image\ImageIO\PNMFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageIO - Win32 Debug"

# Begin Custom Build - Install Header PNMFormat.hh

"C:\Build\inc\Ravl\Image\PNMFormat.hh" :  "" ""
	copy ..\.\Image\ImageIO\PNMFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\ImageIO\ImgIO.hh

!IF  "$(CFG)" == "RavlImageIO - Win32 Release"

# Begin Custom Build - Install Header ImgIO.hh

"C:\Build\inc\Ravl\Image\ImgIO.hh" :  "" ""
	copy ..\.\Image\ImageIO\ImgIO.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageIO - Win32 Debug"

# Begin Custom Build - Install Header ImgIO.hh

"C:\Build\inc\Ravl\Image\ImgIO.hh" :  "" ""
	copy ..\.\Image\ImageIO\ImgIO.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
