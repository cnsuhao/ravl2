# Microsoft Developer Studio Project File - Name="RavlExtImgIO" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlExtImgIO - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlExtImgIO.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlExtImgIO.mak" CFG="RavlExtImgIO - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlExtImgIO - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlExtImgIO - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlExtImgIO - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlExtImgIO"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\RavlExtLib\include" /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlExtImgIO - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlExtImgIO"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /MDd  /I "C:\RavlExtLib\include" /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "_DEBUG" /D "VISUAL_CPP" /D "_LIB" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /GZ /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "RavlExtImgIO - Win32 Release"
# Name "RavlExtImgIO - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\Image\ExternalImageIO\ImgIOJPeg.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ExternalImageIO\JPEGFormat.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ExternalImageIO\ImgIOPNG.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ExternalImageIO\PNGFormat.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ExternalImageIO\ImgIOTiff.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ExternalImageIO\TiffFormat.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ExternalImageIO\CompressedImageJPEG.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\ExternalImageIO\ExtImgIO.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\Image\ExternalImageIO\ImgIOJPeg.hh

!IF  "$(CFG)" == "RavlExtImgIO - Win32 Release"

# Begin Custom Build - Install Header ImgIOJPeg.hh

"C:\Build\inc\Ravl\Image\ImgIOJPeg.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\ImgIOJPeg.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlExtImgIO - Win32 Debug"

# Begin Custom Build - Install Header ImgIOJPeg.hh

"C:\Build\inc\Ravl\Image\ImgIOJPeg.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\ImgIOJPeg.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\ExternalImageIO\ImgIOJPegB.hh

!IF  "$(CFG)" == "RavlExtImgIO - Win32 Release"

# Begin Custom Build - Install Header ImgIOJPegB.hh

"C:\Build\inc\Ravl\Image\ImgIOJPegB.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\ImgIOJPegB.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlExtImgIO - Win32 Debug"

# Begin Custom Build - Install Header ImgIOJPegB.hh

"C:\Build\inc\Ravl\Image\ImgIOJPegB.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\ImgIOJPegB.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\ExternalImageIO\JPEGFormat.hh

!IF  "$(CFG)" == "RavlExtImgIO - Win32 Release"

# Begin Custom Build - Install Header JPEGFormat.hh

"C:\Build\inc\Ravl\Image\JPEGFormat.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\JPEGFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlExtImgIO - Win32 Debug"

# Begin Custom Build - Install Header JPEGFormat.hh

"C:\Build\inc\Ravl\Image\JPEGFormat.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\JPEGFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\ExternalImageIO\ImgIOPNG.hh

!IF  "$(CFG)" == "RavlExtImgIO - Win32 Release"

# Begin Custom Build - Install Header ImgIOPNG.hh

"C:\Build\inc\Ravl\Image\ImgIOPNG.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\ImgIOPNG.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlExtImgIO - Win32 Debug"

# Begin Custom Build - Install Header ImgIOPNG.hh

"C:\Build\inc\Ravl\Image\ImgIOPNG.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\ImgIOPNG.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\ExternalImageIO\ImgIOPNGB.hh

!IF  "$(CFG)" == "RavlExtImgIO - Win32 Release"

# Begin Custom Build - Install Header ImgIOPNGB.hh

"C:\Build\inc\Ravl\Image\ImgIOPNGB.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\ImgIOPNGB.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlExtImgIO - Win32 Debug"

# Begin Custom Build - Install Header ImgIOPNGB.hh

"C:\Build\inc\Ravl\Image\ImgIOPNGB.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\ImgIOPNGB.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\ExternalImageIO\PNGFormat.hh

!IF  "$(CFG)" == "RavlExtImgIO - Win32 Release"

# Begin Custom Build - Install Header PNGFormat.hh

"C:\Build\inc\Ravl\Image\PNGFormat.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\PNGFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlExtImgIO - Win32 Debug"

# Begin Custom Build - Install Header PNGFormat.hh

"C:\Build\inc\Ravl\Image\PNGFormat.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\PNGFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\ExternalImageIO\ImgIOTiff.hh

!IF  "$(CFG)" == "RavlExtImgIO - Win32 Release"

# Begin Custom Build - Install Header ImgIOTiff.hh

"C:\Build\inc\Ravl\Image\ImgIOTiff.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\ImgIOTiff.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlExtImgIO - Win32 Debug"

# Begin Custom Build - Install Header ImgIOTiff.hh

"C:\Build\inc\Ravl\Image\ImgIOTiff.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\ImgIOTiff.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\ExternalImageIO\ImgIOTiffB.hh

!IF  "$(CFG)" == "RavlExtImgIO - Win32 Release"

# Begin Custom Build - Install Header ImgIOTiffB.hh

"C:\Build\inc\Ravl\Image\ImgIOTiffB.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\ImgIOTiffB.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlExtImgIO - Win32 Debug"

# Begin Custom Build - Install Header ImgIOTiffB.hh

"C:\Build\inc\Ravl\Image\ImgIOTiffB.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\ImgIOTiffB.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\ExternalImageIO\TiffFormat.hh

!IF  "$(CFG)" == "RavlExtImgIO - Win32 Release"

# Begin Custom Build - Install Header TiffFormat.hh

"C:\Build\inc\Ravl\Image\TiffFormat.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\TiffFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlExtImgIO - Win32 Debug"

# Begin Custom Build - Install Header TiffFormat.hh

"C:\Build\inc\Ravl\Image\TiffFormat.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\TiffFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\ExternalImageIO\ExtImgIO.hh

!IF  "$(CFG)" == "RavlExtImgIO - Win32 Release"

# Begin Custom Build - Install Header ExtImgIO.hh

"C:\Build\inc\Ravl\Image\ExtImgIO.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\ExtImgIO.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlExtImgIO - Win32 Debug"

# Begin Custom Build - Install Header ExtImgIO.hh

"C:\Build\inc\Ravl\Image\ExtImgIO.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\ExtImgIO.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\ExternalImageIO\CompressedImageJPEG.hh

!IF  "$(CFG)" == "RavlExtImgIO - Win32 Release"

# Begin Custom Build - Install Header CompressedImageJPEG.hh

"C:\Build\inc\Ravl\Image\CompressedImageJPEG.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\CompressedImageJPEG.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlExtImgIO - Win32 Debug"

# Begin Custom Build - Install Header CompressedImageJPEG.hh

"C:\Build\inc\Ravl\Image\CompressedImageJPEG.hh" :  "" ""
	copy ..\.\Image\ExternalImageIO\CompressedImageJPEG.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
