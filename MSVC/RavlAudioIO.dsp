# Microsoft Developer Studio Project File - Name="RavlAudioIO" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlAudioIO - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlAudioIO.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlAudioIO.mak" CFG="RavlAudioIO - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlAudioIO - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlAudioIO - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlAudioIO - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlAudioIO"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlAudioIO - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlAudioIO"
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

# Name "RavlAudioIO - Win32 Release"
# Name "RavlAudioIO - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\Audio\IO\AudioSample.cc
# End Source File

# Begin Source File
SOURCE=..\.\Audio\IO\SphereIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\Audio\IO\SphereFormat.cc
# End Source File

# Begin Source File
SOURCE=..\.\Audio\IO\TranscriptionFiles.cc
# End Source File

# Begin Source File
SOURCE=..\.\Audio\IO\TranscriptionStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\Audio\IO\RavlAudioSample.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\Audio\IO\SphereIO.hh

!IF  "$(CFG)" == "RavlAudioIO - Win32 Release"

# Begin Custom Build - Install Header SphereIO.hh

"C:\Build\inc\Ravl\Audio\SphereIO.hh" :  "" ""
	copy ..\.\Audio\IO\SphereIO.hh C:\Build\inc\Ravl\Audio

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlAudioIO - Win32 Debug"

# Begin Custom Build - Install Header SphereIO.hh

"C:\Build\inc\Ravl\Audio\SphereIO.hh" :  "" ""
	copy ..\.\Audio\IO\SphereIO.hh C:\Build\inc\Ravl\Audio

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Audio\IO\SphereFormat.hh

!IF  "$(CFG)" == "RavlAudioIO - Win32 Release"

# Begin Custom Build - Install Header SphereFormat.hh

"C:\Build\inc\Ravl\Audio\SphereFormat.hh" :  "" ""
	copy ..\.\Audio\IO\SphereFormat.hh C:\Build\inc\Ravl\Audio

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlAudioIO - Win32 Debug"

# Begin Custom Build - Install Header SphereFormat.hh

"C:\Build\inc\Ravl\Audio\SphereFormat.hh" :  "" ""
	copy ..\.\Audio\IO\SphereFormat.hh C:\Build\inc\Ravl\Audio

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Audio\IO\TranscriptionFiles.hh

!IF  "$(CFG)" == "RavlAudioIO - Win32 Release"

# Begin Custom Build - Install Header TranscriptionFiles.hh

"C:\Build\inc\Ravl\Audio\TranscriptionFiles.hh" :  "" ""
	copy ..\.\Audio\IO\TranscriptionFiles.hh C:\Build\inc\Ravl\Audio

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlAudioIO - Win32 Debug"

# Begin Custom Build - Install Header TranscriptionFiles.hh

"C:\Build\inc\Ravl\Audio\TranscriptionFiles.hh" :  "" ""
	copy ..\.\Audio\IO\TranscriptionFiles.hh C:\Build\inc\Ravl\Audio

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Audio\IO\TranscriptionStream.hh

!IF  "$(CFG)" == "RavlAudioIO - Win32 Release"

# Begin Custom Build - Install Header TranscriptionStream.hh

"C:\Build\inc\Ravl\Audio\TranscriptionStream.hh" :  "" ""
	copy ..\.\Audio\IO\TranscriptionStream.hh C:\Build\inc\Ravl\Audio

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlAudioIO - Win32 Debug"

# Begin Custom Build - Install Header TranscriptionStream.hh

"C:\Build\inc\Ravl\Audio\TranscriptionStream.hh" :  "" ""
	copy ..\.\Audio\IO\TranscriptionStream.hh C:\Build\inc\Ravl\Audio

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
