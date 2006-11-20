# Microsoft Developer Studio Project File - Name="RavlDPMT" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlDPMT - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlDPMT.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlDPMT.mak" CFG="RavlDPMT - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlDPMT - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlDPMT - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlDPMT - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlDPMT"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlDPMT - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlDPMT"
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

# Name "RavlDPMT - Win32 Release"
# Name "RavlDPMT - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\OS\DataProc\MTIOConnect.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\DataProc\PlayControl.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\DataProc\Governor.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\DataProc\Blackboard.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\OS\DataProc\MTIOConnect.hh

!IF  "$(CFG)" == "RavlDPMT - Win32 Release"

# Begin Custom Build - Install Header MTIOConnect.hh

"C:\Build\inc\Ravl\DP\MTIOConnect.hh" :  "" ""
	copy ..\.\OS\DataProc\MTIOConnect.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlDPMT - Win32 Debug"

# Begin Custom Build - Install Header MTIOConnect.hh

"C:\Build\inc\Ravl\DP\MTIOConnect.hh" :  "" ""
	copy ..\.\OS\DataProc\MTIOConnect.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\DataProc\PlayControl.hh

!IF  "$(CFG)" == "RavlDPMT - Win32 Release"

# Begin Custom Build - Install Header PlayControl.hh

"C:\Build\inc\Ravl\DP\PlayControl.hh" :  "" ""
	copy ..\.\OS\DataProc\PlayControl.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlDPMT - Win32 Debug"

# Begin Custom Build - Install Header PlayControl.hh

"C:\Build\inc\Ravl\DP\PlayControl.hh" :  "" ""
	copy ..\.\OS\DataProc\PlayControl.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\DataProc\ThreadPipe.hh

!IF  "$(CFG)" == "RavlDPMT - Win32 Release"

# Begin Custom Build - Install Header ThreadPipe.hh

"C:\Build\inc\Ravl\DP\ThreadPipe.hh" :  "" ""
	copy ..\.\OS\DataProc\ThreadPipe.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlDPMT - Win32 Debug"

# Begin Custom Build - Install Header ThreadPipe.hh

"C:\Build\inc\Ravl\DP\ThreadPipe.hh" :  "" ""
	copy ..\.\OS\DataProc\ThreadPipe.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\DataProc\Buffer.hh

!IF  "$(CFG)" == "RavlDPMT - Win32 Release"

# Begin Custom Build - Install Header Buffer.hh

"C:\Build\inc\Ravl\DP\Buffer.hh" :  "" ""
	copy ..\.\OS\DataProc\Buffer.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlDPMT - Win32 Debug"

# Begin Custom Build - Install Header Buffer.hh

"C:\Build\inc\Ravl\DP\Buffer.hh" :  "" ""
	copy ..\.\OS\DataProc\Buffer.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\DataProc\FixedBuffer.hh

!IF  "$(CFG)" == "RavlDPMT - Win32 Release"

# Begin Custom Build - Install Header FixedBuffer.hh

"C:\Build\inc\Ravl\DP\FixedBuffer.hh" :  "" ""
	copy ..\.\OS\DataProc\FixedBuffer.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlDPMT - Win32 Debug"

# Begin Custom Build - Install Header FixedBuffer.hh

"C:\Build\inc\Ravl\DP\FixedBuffer.hh" :  "" ""
	copy ..\.\OS\DataProc\FixedBuffer.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\DataProc\Governor.hh

!IF  "$(CFG)" == "RavlDPMT - Win32 Release"

# Begin Custom Build - Install Header Governor.hh

"C:\Build\inc\Ravl\DP\Governor.hh" :  "" ""
	copy ..\.\OS\DataProc\Governor.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlDPMT - Win32 Debug"

# Begin Custom Build - Install Header Governor.hh

"C:\Build\inc\Ravl\DP\Governor.hh" :  "" ""
	copy ..\.\OS\DataProc\Governor.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\DataProc\Hold.hh

!IF  "$(CFG)" == "RavlDPMT - Win32 Release"

# Begin Custom Build - Install Header Hold.hh

"C:\Build\inc\Ravl\DP\Hold.hh" :  "" ""
	copy ..\.\OS\DataProc\Hold.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlDPMT - Win32 Debug"

# Begin Custom Build - Install Header Hold.hh

"C:\Build\inc\Ravl\DP\Hold.hh" :  "" ""
	copy ..\.\OS\DataProc\Hold.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\DataProc\SerialisePort.hh

!IF  "$(CFG)" == "RavlDPMT - Win32 Release"

# Begin Custom Build - Install Header SerialisePort.hh

"C:\Build\inc\Ravl\DP\SerialisePort.hh" :  "" ""
	copy ..\.\OS\DataProc\SerialisePort.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlDPMT - Win32 Debug"

# Begin Custom Build - Install Header SerialisePort.hh

"C:\Build\inc\Ravl\DP\SerialisePort.hh" :  "" ""
	copy ..\.\OS\DataProc\SerialisePort.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\DataProc\Blackboard.hh

!IF  "$(CFG)" == "RavlDPMT - Win32 Release"

# Begin Custom Build - Install Header Blackboard.hh

"C:\Build\inc\Ravl\DP\Blackboard.hh" :  "" ""
	copy ..\.\OS\DataProc\Blackboard.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlDPMT - Win32 Debug"

# Begin Custom Build - Install Header Blackboard.hh

"C:\Build\inc\Ravl\DP\Blackboard.hh" :  "" ""
	copy ..\.\OS\DataProc\Blackboard.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\DataProc\SPortShare.hh

!IF  "$(CFG)" == "RavlDPMT - Win32 Release"

# Begin Custom Build - Install Header SPortShare.hh

"C:\Build\inc\Ravl\DP\SPortShare.hh" :  "" ""
	copy ..\.\OS\DataProc\SPortShare.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlDPMT - Win32 Debug"

# Begin Custom Build - Install Header SPortShare.hh

"C:\Build\inc\Ravl\DP\SPortShare.hh" :  "" ""
	copy ..\.\OS\DataProc\SPortShare.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\DataProc\SplitI.hh

!IF  "$(CFG)" == "RavlDPMT - Win32 Release"

# Begin Custom Build - Install Header SplitI.hh

"C:\Build\inc\Ravl\DP\SplitI.hh" :  "" ""
	copy ..\.\OS\DataProc\SplitI.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlDPMT - Win32 Debug"

# Begin Custom Build - Install Header SplitI.hh

"C:\Build\inc\Ravl\DP\SplitI.hh" :  "" ""
	copy ..\.\OS\DataProc\SplitI.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
