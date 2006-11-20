# Microsoft Developer Studio Project File - Name="RavlMPEG2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlMPEG2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlMPEG2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlMPEG2.mak" CFG="RavlMPEG2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlMPEG2 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlMPEG2 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlMPEG2 - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlMPEG2"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlMPEG2 - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlMPEG2"
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

# Name "RavlMPEG2 - Win32 Release"
# Name "RavlMPEG2 - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\Contrib\MPEG\mpeg2dec\ImgIOmpeg2dec.cc
# End Source File

# Begin Source File
SOURCE=..\.\Contrib\MPEG\mpeg2dec\MPEG2Format.cc
# End Source File

# Begin Source File
SOURCE=..\.\Contrib\MPEG\mpeg2dec\MustLinkMPEG2.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\Contrib\MPEG\mpeg2dec\ImgIOmpeg2dec.hh

!IF  "$(CFG)" == "RavlMPEG2 - Win32 Release"

# Begin Custom Build - Install Header ImgIOmpeg2dec.hh

"C:\Build\inc\Ravl\Image\ImgIOmpeg2dec.hh" :  "" ""
	copy ..\.\Contrib\MPEG\mpeg2dec\ImgIOmpeg2dec.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMPEG2 - Win32 Debug"

# Begin Custom Build - Install Header ImgIOmpeg2dec.hh

"C:\Build\inc\Ravl\Image\ImgIOmpeg2dec.hh" :  "" ""
	copy ..\.\Contrib\MPEG\mpeg2dec\ImgIOmpeg2dec.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Contrib\MPEG\mpeg2dec\MPEG2Format.hh

!IF  "$(CFG)" == "RavlMPEG2 - Win32 Release"

# Begin Custom Build - Install Header MPEG2Format.hh

"C:\Build\inc\Ravl\Image\MPEG2Format.hh" :  "" ""
	copy ..\.\Contrib\MPEG\mpeg2dec\MPEG2Format.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMPEG2 - Win32 Debug"

# Begin Custom Build - Install Header MPEG2Format.hh

"C:\Build\inc\Ravl\Image\MPEG2Format.hh" :  "" ""
	copy ..\.\Contrib\MPEG\mpeg2dec\MPEG2Format.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
