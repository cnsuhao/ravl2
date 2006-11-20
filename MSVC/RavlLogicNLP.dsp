# Microsoft Developer Studio Project File - Name="RavlLogicNLP" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlLogicNLP - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlLogicNLP.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlLogicNLP.mak" CFG="RavlLogicNLP - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlLogicNLP - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlLogicNLP - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlLogicNLP - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlLogicNLP"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlLogicNLP - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlLogicNLP"
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

# Name "RavlLogicNLP - Win32 Release"
# Name "RavlLogicNLP - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\Logic\NonLinearPlanner\NLPCausalLink.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\NonLinearPlanner\NLPStep.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\NonLinearPlanner\NLPAgendaItem.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\NonLinearPlanner\NLPAction.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\NonLinearPlanner\NLPAgenda.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\NonLinearPlanner\NonLinearPlan.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\NonLinearPlanner\NLPlanner.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\Logic\NonLinearPlanner\NLPCausalLink.hh

!IF  "$(CFG)" == "RavlLogicNLP - Win32 Release"

# Begin Custom Build - Install Header NLPCausalLink.hh

"C:\Build\inc\Ravl\Logic\NLPCausalLink.hh" :  "" ""
	copy ..\.\Logic\NonLinearPlanner\NLPCausalLink.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogicNLP - Win32 Debug"

# Begin Custom Build - Install Header NLPCausalLink.hh

"C:\Build\inc\Ravl\Logic\NLPCausalLink.hh" :  "" ""
	copy ..\.\Logic\NonLinearPlanner\NLPCausalLink.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\NonLinearPlanner\NLPStep.hh

!IF  "$(CFG)" == "RavlLogicNLP - Win32 Release"

# Begin Custom Build - Install Header NLPStep.hh

"C:\Build\inc\Ravl\Logic\NLPStep.hh" :  "" ""
	copy ..\.\Logic\NonLinearPlanner\NLPStep.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogicNLP - Win32 Debug"

# Begin Custom Build - Install Header NLPStep.hh

"C:\Build\inc\Ravl\Logic\NLPStep.hh" :  "" ""
	copy ..\.\Logic\NonLinearPlanner\NLPStep.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\NonLinearPlanner\NLPAgendaItem.hh

!IF  "$(CFG)" == "RavlLogicNLP - Win32 Release"

# Begin Custom Build - Install Header NLPAgendaItem.hh

"C:\Build\inc\Ravl\Logic\NLPAgendaItem.hh" :  "" ""
	copy ..\.\Logic\NonLinearPlanner\NLPAgendaItem.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogicNLP - Win32 Debug"

# Begin Custom Build - Install Header NLPAgendaItem.hh

"C:\Build\inc\Ravl\Logic\NLPAgendaItem.hh" :  "" ""
	copy ..\.\Logic\NonLinearPlanner\NLPAgendaItem.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\NonLinearPlanner\NLPAction.hh

!IF  "$(CFG)" == "RavlLogicNLP - Win32 Release"

# Begin Custom Build - Install Header NLPAction.hh

"C:\Build\inc\Ravl\Logic\NLPAction.hh" :  "" ""
	copy ..\.\Logic\NonLinearPlanner\NLPAction.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogicNLP - Win32 Debug"

# Begin Custom Build - Install Header NLPAction.hh

"C:\Build\inc\Ravl\Logic\NLPAction.hh" :  "" ""
	copy ..\.\Logic\NonLinearPlanner\NLPAction.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\NonLinearPlanner\NLPAgenda.hh

!IF  "$(CFG)" == "RavlLogicNLP - Win32 Release"

# Begin Custom Build - Install Header NLPAgenda.hh

"C:\Build\inc\Ravl\Logic\NLPAgenda.hh" :  "" ""
	copy ..\.\Logic\NonLinearPlanner\NLPAgenda.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogicNLP - Win32 Debug"

# Begin Custom Build - Install Header NLPAgenda.hh

"C:\Build\inc\Ravl\Logic\NLPAgenda.hh" :  "" ""
	copy ..\.\Logic\NonLinearPlanner\NLPAgenda.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\NonLinearPlanner\NonLinearPlan.hh

!IF  "$(CFG)" == "RavlLogicNLP - Win32 Release"

# Begin Custom Build - Install Header NonLinearPlan.hh

"C:\Build\inc\Ravl\Logic\NonLinearPlan.hh" :  "" ""
	copy ..\.\Logic\NonLinearPlanner\NonLinearPlan.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogicNLP - Win32 Debug"

# Begin Custom Build - Install Header NonLinearPlan.hh

"C:\Build\inc\Ravl\Logic\NonLinearPlan.hh" :  "" ""
	copy ..\.\Logic\NonLinearPlanner\NonLinearPlan.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\NonLinearPlanner\NLPTypes.hh

!IF  "$(CFG)" == "RavlLogicNLP - Win32 Release"

# Begin Custom Build - Install Header NLPTypes.hh

"C:\Build\inc\Ravl\Logic\NLPTypes.hh" :  "" ""
	copy ..\.\Logic\NonLinearPlanner\NLPTypes.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogicNLP - Win32 Debug"

# Begin Custom Build - Install Header NLPTypes.hh

"C:\Build\inc\Ravl\Logic\NLPTypes.hh" :  "" ""
	copy ..\.\Logic\NonLinearPlanner\NLPTypes.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\NonLinearPlanner\NLPlanner.hh

!IF  "$(CFG)" == "RavlLogicNLP - Win32 Release"

# Begin Custom Build - Install Header NLPlanner.hh

"C:\Build\inc\Ravl\Logic\NLPlanner.hh" :  "" ""
	copy ..\.\Logic\NonLinearPlanner\NLPlanner.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogicNLP - Win32 Debug"

# Begin Custom Build - Install Header NLPlanner.hh

"C:\Build\inc\Ravl\Logic\NLPlanner.hh" :  "" ""
	copy ..\.\Logic\NonLinearPlanner\NLPlanner.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
