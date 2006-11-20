# Microsoft Developer Studio Project File - Name="RavlOS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlOS - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlOS.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlOS.mak" CFG="RavlOS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlOS - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlOS - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlOS"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlOS"
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

# Name "RavlOS - Win32 Release"
# Name "RavlOS - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\OS\Time\Date.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Time\DateIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Time\DeadLineTimer.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\FileSystem\FilePermission.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\FileSystem\Filename.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\FileSystem\Directory.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\FileSystem\FileSearch.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\FileSystem\UserInfo.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\FileSystem\FileOwner.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\FileSystem\FileStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Misc\SerialIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Misc\SysLog.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Exec\OSProcess.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Exec\ChildOSProcess.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Exec\ChildOSProcessWait.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Exec\ChildOSProcessStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Exec\MailUser.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Exec\FileUser.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Text\TextFileLine.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Text\TextBuffer.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Text\TextFile.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Text\TextCursor.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Text\TemplateFile.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Text\TextFragment.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Text\ConfigFile.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Text\TemplateComplex.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\OS\Time\Date.hh

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# Begin Custom Build - Install Header Date.hh

"C:\Build\inc\Ravl\OS\Date.hh" :  "" ""
	copy ..\.\OS\Time\Date.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# Begin Custom Build - Install Header Date.hh

"C:\Build\inc\Ravl\OS\Date.hh" :  "" ""
	copy ..\.\OS\Time\Date.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Time\DeadLineTimer.hh

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# Begin Custom Build - Install Header DeadLineTimer.hh

"C:\Build\inc\Ravl\OS\DeadLineTimer.hh" :  "" ""
	copy ..\.\OS\Time\DeadLineTimer.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# Begin Custom Build - Install Header DeadLineTimer.hh

"C:\Build\inc\Ravl\OS\DeadLineTimer.hh" :  "" ""
	copy ..\.\OS\Time\DeadLineTimer.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\FileSystem\FilePermission.hh

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# Begin Custom Build - Install Header FilePermission.hh

"C:\Build\inc\Ravl\OS\FilePermission.hh" :  "" ""
	copy ..\.\OS\FileSystem\FilePermission.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# Begin Custom Build - Install Header FilePermission.hh

"C:\Build\inc\Ravl\OS\FilePermission.hh" :  "" ""
	copy ..\.\OS\FileSystem\FilePermission.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\FileSystem\Filename.hh

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# Begin Custom Build - Install Header Filename.hh

"C:\Build\inc\Ravl\OS\Filename.hh" :  "" ""
	copy ..\.\OS\FileSystem\Filename.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# Begin Custom Build - Install Header Filename.hh

"C:\Build\inc\Ravl\OS\Filename.hh" :  "" ""
	copy ..\.\OS\FileSystem\Filename.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\FileSystem\Directory.hh

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# Begin Custom Build - Install Header Directory.hh

"C:\Build\inc\Ravl\OS\Directory.hh" :  "" ""
	copy ..\.\OS\FileSystem\Directory.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# Begin Custom Build - Install Header Directory.hh

"C:\Build\inc\Ravl\OS\Directory.hh" :  "" ""
	copy ..\.\OS\FileSystem\Directory.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\FileSystem\UserInfo.hh

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# Begin Custom Build - Install Header UserInfo.hh

"C:\Build\inc\Ravl\OS\UserInfo.hh" :  "" ""
	copy ..\.\OS\FileSystem\UserInfo.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# Begin Custom Build - Install Header UserInfo.hh

"C:\Build\inc\Ravl\OS\UserInfo.hh" :  "" ""
	copy ..\.\OS\FileSystem\UserInfo.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\FileSystem\FileStream.hh

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# Begin Custom Build - Install Header FileStream.hh

"C:\Build\inc\Ravl\OS\FileStream.hh" :  "" ""
	copy ..\.\OS\FileSystem\FileStream.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# Begin Custom Build - Install Header FileStream.hh

"C:\Build\inc\Ravl\OS\FileStream.hh" :  "" ""
	copy ..\.\OS\FileSystem\FileStream.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Misc\SerialIO.hh

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# Begin Custom Build - Install Header SerialIO.hh

"C:\Build\inc\Ravl\OS\SerialIO.hh" :  "" ""
	copy ..\.\OS\Misc\SerialIO.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# Begin Custom Build - Install Header SerialIO.hh

"C:\Build\inc\Ravl\OS\SerialIO.hh" :  "" ""
	copy ..\.\OS\Misc\SerialIO.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Misc\DMABuffer.hh

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# Begin Custom Build - Install Header DMABuffer.hh

"C:\Build\inc\Ravl\OS\DMABuffer.hh" :  "" ""
	copy ..\.\OS\Misc\DMABuffer.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# Begin Custom Build - Install Header DMABuffer.hh

"C:\Build\inc\Ravl\OS\DMABuffer.hh" :  "" ""
	copy ..\.\OS\Misc\DMABuffer.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Misc\SysLog.hh

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# Begin Custom Build - Install Header SysLog.hh

"C:\Build\inc\Ravl\OS\SysLog.hh" :  "" ""
	copy ..\.\OS\Misc\SysLog.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# Begin Custom Build - Install Header SysLog.hh

"C:\Build\inc\Ravl\OS\SysLog.hh" :  "" ""
	copy ..\.\OS\Misc\SysLog.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Exec\OSProcess.hh

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# Begin Custom Build - Install Header OSProcess.hh

"C:\Build\inc\Ravl\OS\OSProcess.hh" :  "" ""
	copy ..\.\OS\Exec\OSProcess.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# Begin Custom Build - Install Header OSProcess.hh

"C:\Build\inc\Ravl\OS\OSProcess.hh" :  "" ""
	copy ..\.\OS\Exec\OSProcess.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Exec\ChildOSProcess.hh

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# Begin Custom Build - Install Header ChildOSProcess.hh

"C:\Build\inc\Ravl\OS\ChildOSProcess.hh" :  "" ""
	copy ..\.\OS\Exec\ChildOSProcess.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# Begin Custom Build - Install Header ChildOSProcess.hh

"C:\Build\inc\Ravl\OS\ChildOSProcess.hh" :  "" ""
	copy ..\.\OS\Exec\ChildOSProcess.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Text\TextFileLine.hh

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# Begin Custom Build - Install Header TextFileLine.hh

"C:\Build\inc\Ravl\Text\TextFileLine.hh" :  "" ""
	copy ..\.\OS\Text\TextFileLine.hh C:\Build\inc\Ravl\Text

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# Begin Custom Build - Install Header TextFileLine.hh

"C:\Build\inc\Ravl\Text\TextFileLine.hh" :  "" ""
	copy ..\.\OS\Text\TextFileLine.hh C:\Build\inc\Ravl\Text

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Text\TextBuffer.hh

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# Begin Custom Build - Install Header TextBuffer.hh

"C:\Build\inc\Ravl\Text\TextBuffer.hh" :  "" ""
	copy ..\.\OS\Text\TextBuffer.hh C:\Build\inc\Ravl\Text

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# Begin Custom Build - Install Header TextBuffer.hh

"C:\Build\inc\Ravl\Text\TextBuffer.hh" :  "" ""
	copy ..\.\OS\Text\TextBuffer.hh C:\Build\inc\Ravl\Text

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Text\TextFile.hh

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# Begin Custom Build - Install Header TextFile.hh

"C:\Build\inc\Ravl\Text\TextFile.hh" :  "" ""
	copy ..\.\OS\Text\TextFile.hh C:\Build\inc\Ravl\Text

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# Begin Custom Build - Install Header TextFile.hh

"C:\Build\inc\Ravl\Text\TextFile.hh" :  "" ""
	copy ..\.\OS\Text\TextFile.hh C:\Build\inc\Ravl\Text

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Text\TextCursor.hh

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# Begin Custom Build - Install Header TextCursor.hh

"C:\Build\inc\Ravl\Text\TextCursor.hh" :  "" ""
	copy ..\.\OS\Text\TextCursor.hh C:\Build\inc\Ravl\Text

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# Begin Custom Build - Install Header TextCursor.hh

"C:\Build\inc\Ravl\Text\TextCursor.hh" :  "" ""
	copy ..\.\OS\Text\TextCursor.hh C:\Build\inc\Ravl\Text

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Text\TemplateFile.hh

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# Begin Custom Build - Install Header TemplateFile.hh

"C:\Build\inc\Ravl\Text\TemplateFile.hh" :  "" ""
	copy ..\.\OS\Text\TemplateFile.hh C:\Build\inc\Ravl\Text

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# Begin Custom Build - Install Header TemplateFile.hh

"C:\Build\inc\Ravl\Text\TemplateFile.hh" :  "" ""
	copy ..\.\OS\Text\TemplateFile.hh C:\Build\inc\Ravl\Text

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Text\TextFragment.hh

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# Begin Custom Build - Install Header TextFragment.hh

"C:\Build\inc\Ravl\Text\TextFragment.hh" :  "" ""
	copy ..\.\OS\Text\TextFragment.hh C:\Build\inc\Ravl\Text

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# Begin Custom Build - Install Header TextFragment.hh

"C:\Build\inc\Ravl\Text\TextFragment.hh" :  "" ""
	copy ..\.\OS\Text\TextFragment.hh C:\Build\inc\Ravl\Text

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Text\ConfigFile.hh

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# Begin Custom Build - Install Header ConfigFile.hh

"C:\Build\inc\Ravl\Text\ConfigFile.hh" :  "" ""
	copy ..\.\OS\Text\ConfigFile.hh C:\Build\inc\Ravl\Text

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# Begin Custom Build - Install Header ConfigFile.hh

"C:\Build\inc\Ravl\Text\ConfigFile.hh" :  "" ""
	copy ..\.\OS\Text\ConfigFile.hh C:\Build\inc\Ravl\Text

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Text\TemplateComplex.hh

!IF  "$(CFG)" == "RavlOS - Win32 Release"

# Begin Custom Build - Install Header TemplateComplex.hh

"C:\Build\inc\Ravl\Text\TemplateComplex.hh" :  "" ""
	copy ..\.\OS\Text\TemplateComplex.hh C:\Build\inc\Ravl\Text

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlOS - Win32 Debug"

# Begin Custom Build - Install Header TemplateComplex.hh

"C:\Build\inc\Ravl\Text\TemplateComplex.hh" :  "" ""
	copy ..\.\OS\Text\TemplateComplex.hh C:\Build\inc\Ravl\Text

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
