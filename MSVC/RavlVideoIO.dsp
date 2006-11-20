# Microsoft Developer Studio Project File - Name="RavlVideoIO" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlVideoIO - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlVideoIO.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlVideoIO.mak" CFG="RavlVideoIO - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlVideoIO - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlVideoIO - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlVideoIO - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlVideoIO"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlVideoIO - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlVideoIO"
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

# Name "RavlVideoIO - Win32 Release"
# Name "RavlVideoIO - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\Image\VideoIO\ImgIOCif.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\CifFormat.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\ImgIOyuv.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\yuvFormat.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\syuvFormat.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\ImgIOrgb.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\rgbFormat.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\rawFormat.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\ImgIOjs.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\jsFormat.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\MultiVidIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\DVFrame.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\AviIStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\AviOStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\BGRFrmIOAvi.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\DVFrmIOAvi.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\AviFormat.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\RavlVidIO.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\Image\VideoIO\ImgIOCif.hh

!IF  "$(CFG)" == "RavlVideoIO - Win32 Release"

# Begin Custom Build - Install Header ImgIOCif.hh

"C:\Build\inc\Ravl\Image\ImgIOCif.hh" :  "" ""
	copy ..\.\Image\VideoIO\ImgIOCif.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlVideoIO - Win32 Debug"

# Begin Custom Build - Install Header ImgIOCif.hh

"C:\Build\inc\Ravl\Image\ImgIOCif.hh" :  "" ""
	copy ..\.\Image\VideoIO\ImgIOCif.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\CifFormat.hh

!IF  "$(CFG)" == "RavlVideoIO - Win32 Release"

# Begin Custom Build - Install Header CifFormat.hh

"C:\Build\inc\Ravl\Image\CifFormat.hh" :  "" ""
	copy ..\.\Image\VideoIO\CifFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlVideoIO - Win32 Debug"

# Begin Custom Build - Install Header CifFormat.hh

"C:\Build\inc\Ravl\Image\CifFormat.hh" :  "" ""
	copy ..\.\Image\VideoIO\CifFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\ImgIOyuv.hh

!IF  "$(CFG)" == "RavlVideoIO - Win32 Release"

# Begin Custom Build - Install Header ImgIOyuv.hh

"C:\Build\inc\Ravl\Image\ImgIOyuv.hh" :  "" ""
	copy ..\.\Image\VideoIO\ImgIOyuv.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlVideoIO - Win32 Debug"

# Begin Custom Build - Install Header ImgIOyuv.hh

"C:\Build\inc\Ravl\Image\ImgIOyuv.hh" :  "" ""
	copy ..\.\Image\VideoIO\ImgIOyuv.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\yuvFormat.hh

!IF  "$(CFG)" == "RavlVideoIO - Win32 Release"

# Begin Custom Build - Install Header yuvFormat.hh

"C:\Build\inc\Ravl\Image\yuvFormat.hh" :  "" ""
	copy ..\.\Image\VideoIO\yuvFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlVideoIO - Win32 Debug"

# Begin Custom Build - Install Header yuvFormat.hh

"C:\Build\inc\Ravl\Image\yuvFormat.hh" :  "" ""
	copy ..\.\Image\VideoIO\yuvFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\syuvFormat.hh

!IF  "$(CFG)" == "RavlVideoIO - Win32 Release"

# Begin Custom Build - Install Header syuvFormat.hh

"C:\Build\inc\Ravl\Image\syuvFormat.hh" :  "" ""
	copy ..\.\Image\VideoIO\syuvFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlVideoIO - Win32 Debug"

# Begin Custom Build - Install Header syuvFormat.hh

"C:\Build\inc\Ravl\Image\syuvFormat.hh" :  "" ""
	copy ..\.\Image\VideoIO\syuvFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\ImgIOrgb.hh

!IF  "$(CFG)" == "RavlVideoIO - Win32 Release"

# Begin Custom Build - Install Header ImgIOrgb.hh

"C:\Build\inc\Ravl\Image\ImgIOrgb.hh" :  "" ""
	copy ..\.\Image\VideoIO\ImgIOrgb.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlVideoIO - Win32 Debug"

# Begin Custom Build - Install Header ImgIOrgb.hh

"C:\Build\inc\Ravl\Image\ImgIOrgb.hh" :  "" ""
	copy ..\.\Image\VideoIO\ImgIOrgb.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\rgbFormat.hh

!IF  "$(CFG)" == "RavlVideoIO - Win32 Release"

# Begin Custom Build - Install Header rgbFormat.hh

"C:\Build\inc\Ravl\Image\rgbFormat.hh" :  "" ""
	copy ..\.\Image\VideoIO\rgbFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlVideoIO - Win32 Debug"

# Begin Custom Build - Install Header rgbFormat.hh

"C:\Build\inc\Ravl\Image\rgbFormat.hh" :  "" ""
	copy ..\.\Image\VideoIO\rgbFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\rawFormat.hh

!IF  "$(CFG)" == "RavlVideoIO - Win32 Release"

# Begin Custom Build - Install Header rawFormat.hh

"C:\Build\inc\Ravl\Image\rawFormat.hh" :  "" ""
	copy ..\.\Image\VideoIO\rawFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlVideoIO - Win32 Debug"

# Begin Custom Build - Install Header rawFormat.hh

"C:\Build\inc\Ravl\Image\rawFormat.hh" :  "" ""
	copy ..\.\Image\VideoIO\rawFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\ImgIOjs.hh

!IF  "$(CFG)" == "RavlVideoIO - Win32 Release"

# Begin Custom Build - Install Header ImgIOjs.hh

"C:\Build\inc\Ravl\Image\ImgIOjs.hh" :  "" ""
	copy ..\.\Image\VideoIO\ImgIOjs.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlVideoIO - Win32 Debug"

# Begin Custom Build - Install Header ImgIOjs.hh

"C:\Build\inc\Ravl\Image\ImgIOjs.hh" :  "" ""
	copy ..\.\Image\VideoIO\ImgIOjs.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\jsFormat.hh

!IF  "$(CFG)" == "RavlVideoIO - Win32 Release"

# Begin Custom Build - Install Header jsFormat.hh

"C:\Build\inc\Ravl\Image\jsFormat.hh" :  "" ""
	copy ..\.\Image\VideoIO\jsFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlVideoIO - Win32 Debug"

# Begin Custom Build - Install Header jsFormat.hh

"C:\Build\inc\Ravl\Image\jsFormat.hh" :  "" ""
	copy ..\.\Image\VideoIO\jsFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\VidIO.hh

!IF  "$(CFG)" == "RavlVideoIO - Win32 Release"

# Begin Custom Build - Install Header VidIO.hh

"C:\Build\inc\Ravl\Image\VidIO.hh" :  "" ""
	copy ..\.\Image\VideoIO\VidIO.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlVideoIO - Win32 Debug"

# Begin Custom Build - Install Header VidIO.hh

"C:\Build\inc\Ravl\Image\VidIO.hh" :  "" ""
	copy ..\.\Image\VideoIO\VidIO.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\MultiVidIO.hh

!IF  "$(CFG)" == "RavlVideoIO - Win32 Release"

# Begin Custom Build - Install Header MultiVidIO.hh

"C:\Build\inc\Ravl\Image\MultiVidIO.hh" :  "" ""
	copy ..\.\Image\VideoIO\MultiVidIO.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlVideoIO - Win32 Debug"

# Begin Custom Build - Install Header MultiVidIO.hh

"C:\Build\inc\Ravl\Image\MultiVidIO.hh" :  "" ""
	copy ..\.\Image\VideoIO\MultiVidIO.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\DVFrame.hh

!IF  "$(CFG)" == "RavlVideoIO - Win32 Release"

# Begin Custom Build - Install Header DVFrame.hh

"C:\Build\inc\Ravl\Image\DVFrame.hh" :  "" ""
	copy ..\.\Image\VideoIO\DVFrame.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlVideoIO - Win32 Debug"

# Begin Custom Build - Install Header DVFrame.hh

"C:\Build\inc\Ravl\Image\DVFrame.hh" :  "" ""
	copy ..\.\Image\VideoIO\DVFrame.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\AviStream.hh

!IF  "$(CFG)" == "RavlVideoIO - Win32 Release"

# Begin Custom Build - Install Header AviStream.hh

"C:\Build\inc\Ravl\Image\AviStream.hh" :  "" ""
	copy ..\.\Image\VideoIO\AviStream.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlVideoIO - Win32 Debug"

# Begin Custom Build - Install Header AviStream.hh

"C:\Build\inc\Ravl\Image\AviStream.hh" :  "" ""
	copy ..\.\Image\VideoIO\AviStream.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\BGRFrmIOAvi.hh

!IF  "$(CFG)" == "RavlVideoIO - Win32 Release"

# Begin Custom Build - Install Header BGRFrmIOAvi.hh

"C:\Build\inc\Ravl\Image\BGRFrmIOAvi.hh" :  "" ""
	copy ..\.\Image\VideoIO\BGRFrmIOAvi.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlVideoIO - Win32 Debug"

# Begin Custom Build - Install Header BGRFrmIOAvi.hh

"C:\Build\inc\Ravl\Image\BGRFrmIOAvi.hh" :  "" ""
	copy ..\.\Image\VideoIO\BGRFrmIOAvi.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\DVFrmIOAvi.hh

!IF  "$(CFG)" == "RavlVideoIO - Win32 Release"

# Begin Custom Build - Install Header DVFrmIOAvi.hh

"C:\Build\inc\Ravl\Image\DVFrmIOAvi.hh" :  "" ""
	copy ..\.\Image\VideoIO\DVFrmIOAvi.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlVideoIO - Win32 Debug"

# Begin Custom Build - Install Header DVFrmIOAvi.hh

"C:\Build\inc\Ravl\Image\DVFrmIOAvi.hh" :  "" ""
	copy ..\.\Image\VideoIO\DVFrmIOAvi.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\VideoIO\AviFormat.hh

!IF  "$(CFG)" == "RavlVideoIO - Win32 Release"

# Begin Custom Build - Install Header AviFormat.hh

"C:\Build\inc\Ravl\Image\AviFormat.hh" :  "" ""
	copy ..\.\Image\VideoIO\AviFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlVideoIO - Win32 Debug"

# Begin Custom Build - Install Header AviFormat.hh

"C:\Build\inc\Ravl\Image\AviFormat.hh" :  "" ""
	copy ..\.\Image\VideoIO\AviFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
