# Microsoft Developer Studio Project File - Name="RavlOSIO" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlOSIO - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlOSIO.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlOSIO.mak" CFG="RavlOSIO - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlOSIO - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlOSIO - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlOSIO - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlOSIO"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlOSIO - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlOSIO"
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

# Name "RavlOSIO - Win32 Release"
# Name "RavlOSIO - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\OS\IO\FileSequence.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\IO\SequenceIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\IO\FileListIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\IO\CompositeStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\IO\FileFormatComposite.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\IO\PlayList.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\IO\SubSequenceSpec.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\IO\EditSpec.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\IO\FileFormatDynamic.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\IO\DynamicLink.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\IO\RavlOSIOMustLink.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\OS\IO\FileSequence.hh

!IF  "$(CFG)" == "RavlOSIO - Win32 Release"

# Begin Custom Build - Install Header FileSequence.hh

"C:\Build\inc\Ravl\DP\FileSequence.hh" :  "" ""
	copy ..\.\OS\IO\FileSequence.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOSIO - Win32 Debug"

# Begin Custom Build - Install Header FileSequence.hh

"C:\Build\inc\Ravl\DP\FileSequence.hh" :  "" ""
	copy ..\.\OS\IO\FileSequence.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\IO\SequenceIO.hh

!IF  "$(CFG)" == "RavlOSIO - Win32 Release"

# Begin Custom Build - Install Header SequenceIO.hh

"C:\Build\inc\Ravl\DP\SequenceIO.hh" :  "" ""
	copy ..\.\OS\IO\SequenceIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOSIO - Win32 Debug"

# Begin Custom Build - Install Header SequenceIO.hh

"C:\Build\inc\Ravl\DP\SequenceIO.hh" :  "" ""
	copy ..\.\OS\IO\SequenceIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\IO\FileListIO.hh

!IF  "$(CFG)" == "RavlOSIO - Win32 Release"

# Begin Custom Build - Install Header FileListIO.hh

"C:\Build\inc\Ravl\DP\FileListIO.hh" :  "" ""
	copy ..\.\OS\IO\FileListIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOSIO - Win32 Debug"

# Begin Custom Build - Install Header FileListIO.hh

"C:\Build\inc\Ravl\DP\FileListIO.hh" :  "" ""
	copy ..\.\OS\IO\FileListIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\IO\CompositeStream.hh

!IF  "$(CFG)" == "RavlOSIO - Win32 Release"

# Begin Custom Build - Install Header CompositeStream.hh

"C:\Build\inc\Ravl\DP\CompositeStream.hh" :  "" ""
	copy ..\.\OS\IO\CompositeStream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOSIO - Win32 Debug"

# Begin Custom Build - Install Header CompositeStream.hh

"C:\Build\inc\Ravl\DP\CompositeStream.hh" :  "" ""
	copy ..\.\OS\IO\CompositeStream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\IO\FileFormatComposite.hh

!IF  "$(CFG)" == "RavlOSIO - Win32 Release"

# Begin Custom Build - Install Header FileFormatComposite.hh

"C:\Build\inc\Ravl\DP\FileFormatComposite.hh" :  "" ""
	copy ..\.\OS\IO\FileFormatComposite.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOSIO - Win32 Debug"

# Begin Custom Build - Install Header FileFormatComposite.hh

"C:\Build\inc\Ravl\DP\FileFormatComposite.hh" :  "" ""
	copy ..\.\OS\IO\FileFormatComposite.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\IO\PlayList.hh

!IF  "$(CFG)" == "RavlOSIO - Win32 Release"

# Begin Custom Build - Install Header PlayList.hh

"C:\Build\inc\Ravl\DP\PlayList.hh" :  "" ""
	copy ..\.\OS\IO\PlayList.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOSIO - Win32 Debug"

# Begin Custom Build - Install Header PlayList.hh

"C:\Build\inc\Ravl\DP\PlayList.hh" :  "" ""
	copy ..\.\OS\IO\PlayList.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\IO\SubSequenceSpec.hh

!IF  "$(CFG)" == "RavlOSIO - Win32 Release"

# Begin Custom Build - Install Header SubSequenceSpec.hh

"C:\Build\inc\Ravl\DP\SubSequenceSpec.hh" :  "" ""
	copy ..\.\OS\IO\SubSequenceSpec.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOSIO - Win32 Debug"

# Begin Custom Build - Install Header SubSequenceSpec.hh

"C:\Build\inc\Ravl\DP\SubSequenceSpec.hh" :  "" ""
	copy ..\.\OS\IO\SubSequenceSpec.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\IO\EditSpec.hh

!IF  "$(CFG)" == "RavlOSIO - Win32 Release"

# Begin Custom Build - Install Header EditSpec.hh

"C:\Build\inc\Ravl\DP\EditSpec.hh" :  "" ""
	copy ..\.\OS\IO\EditSpec.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOSIO - Win32 Debug"

# Begin Custom Build - Install Header EditSpec.hh

"C:\Build\inc\Ravl\DP\EditSpec.hh" :  "" ""
	copy ..\.\OS\IO\EditSpec.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\IO\FileFormatDynamic.hh

!IF  "$(CFG)" == "RavlOSIO - Win32 Release"

# Begin Custom Build - Install Header FileFormatDynamic.hh

"C:\Build\inc\Ravl\DP\FileFormatDynamic.hh" :  "" ""
	copy ..\.\OS\IO\FileFormatDynamic.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOSIO - Win32 Debug"

# Begin Custom Build - Install Header FileFormatDynamic.hh

"C:\Build\inc\Ravl\DP\FileFormatDynamic.hh" :  "" ""
	copy ..\.\OS\IO\FileFormatDynamic.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\IO\DynamicLink.hh

!IF  "$(CFG)" == "RavlOSIO - Win32 Release"

# Begin Custom Build - Install Header DynamicLink.hh

"C:\Build\inc\Ravl\DP\DynamicLink.hh" :  "" ""
	copy ..\.\OS\IO\DynamicLink.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOSIO - Win32 Debug"

# Begin Custom Build - Install Header DynamicLink.hh

"C:\Build\inc\Ravl\DP\DynamicLink.hh" :  "" ""
	copy ..\.\OS\IO\DynamicLink.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\IO\DynamicIO.hh

!IF  "$(CFG)" == "RavlOSIO - Win32 Release"

# Begin Custom Build - Install Header DynamicIO.hh

"C:\Build\inc\Ravl\DP\DynamicIO.hh" :  "" ""
	copy ..\.\OS\IO\DynamicIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOSIO - Win32 Debug"

# Begin Custom Build - Install Header DynamicIO.hh

"C:\Build\inc\Ravl\DP\DynamicIO.hh" :  "" ""
	copy ..\.\OS\IO\DynamicIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
