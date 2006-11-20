# Microsoft Developer Studio Project File - Name="RavlImgIOJasper" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlImgIOJasper - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlImgIOJasper.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlImgIOJasper.mak" CFG="RavlImgIOJasper - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlImgIOJasper - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlImgIOJasper - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlImgIOJasper - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlImgIOJasper"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\RavlExtLib\include" /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlImgIOJasper - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlImgIOJasper"
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

# Name "RavlImgIOJasper - Win32 Release"
# Name "RavlImgIOJasper - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\Contrib\Jasper\ImgIOJasper.cc
# End Source File

# Begin Source File
SOURCE=..\.\Contrib\Jasper\JasperFormat.cc
# End Source File

# Begin Source File
SOURCE=..\.\Contrib\Jasper\CompressedImageJ2k.cc
# End Source File

# Begin Source File
SOURCE=..\.\Contrib\Jasper\JasperImgIO.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\Contrib\Jasper\ImgIOJasper.hh

!IF  "$(CFG)" == "RavlImgIOJasper - Win32 Release"

# Begin Custom Build - Install Header ImgIOJasper.hh

"C:\Build\inc\Ravl\Image\ImgIOJasper.hh" :  "" ""
	copy ..\.\Contrib\Jasper\ImgIOJasper.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImgIOJasper - Win32 Debug"

# Begin Custom Build - Install Header ImgIOJasper.hh

"C:\Build\inc\Ravl\Image\ImgIOJasper.hh" :  "" ""
	copy ..\.\Contrib\Jasper\ImgIOJasper.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Contrib\Jasper\JasperFormat.hh

!IF  "$(CFG)" == "RavlImgIOJasper - Win32 Release"

# Begin Custom Build - Install Header JasperFormat.hh

"C:\Build\inc\Ravl\Image\JasperFormat.hh" :  "" ""
	copy ..\.\Contrib\Jasper\JasperFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImgIOJasper - Win32 Debug"

# Begin Custom Build - Install Header JasperFormat.hh

"C:\Build\inc\Ravl\Image\JasperFormat.hh" :  "" ""
	copy ..\.\Contrib\Jasper\JasperFormat.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Contrib\Jasper\CompressedImageJ2k.hh

!IF  "$(CFG)" == "RavlImgIOJasper - Win32 Release"

# Begin Custom Build - Install Header CompressedImageJ2k.hh

"C:\Build\inc\Ravl\Image\CompressedImageJ2k.hh" :  "" ""
	copy ..\.\Contrib\Jasper\CompressedImageJ2k.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImgIOJasper - Win32 Debug"

# Begin Custom Build - Install Header CompressedImageJ2k.hh

"C:\Build\inc\Ravl\Image\CompressedImageJ2k.hh" :  "" ""
	copy ..\.\Contrib\Jasper\CompressedImageJ2k.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
