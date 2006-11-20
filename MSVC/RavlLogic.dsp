# Microsoft Developer Studio Project File - Name="RavlLogic" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlLogic - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlLogic.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlLogic.mak" CFG="RavlLogic - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlLogic - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlLogic - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlLogic"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlLogic"
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

# Name "RavlLogic - Win32 Release"
# Name "RavlLogic - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\Logic\Base\Literal.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\Var.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\Unify.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\BindSet.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\Tuple.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\LList.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\Condition.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\MinTerm.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\Or.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\And.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\Not.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\LiteralIter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\State.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\LiteralIter1.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\StateOrIter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\StateSet.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\LiteralFilterIter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\StateAndIter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\NamedLiteral.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\NamedVar.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\LiteralIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\MinTermIter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\Value.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\Context.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\LiteralIndexBase.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\LiteralIndexElement.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\LiteralIndexLeaf.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\LiteralIndexNode.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\LiteralIndexIter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\LiteralIndexFilterBase.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\LiteralIndexLeafIter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\LiteralIndexLeafVarIter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\StateIndexed.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\LiteralIndexFilterRaw.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\DecisionTree\DecisionTreeElement.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\DecisionTree\DecisionTreeLeaf.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\DecisionTree\DecisionTreeBase.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\DecisionTree\DecisionTreeBranch.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\DecisionTree\DecisionTreeBranchBinary.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\DecisionTree\DecisionExamples.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\DecisionTree\Discriminator.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\DecisionTree\SampleLiteral.cc
# End Source File

# Begin Source File
SOURCE=..\.\Logic\DecisionTree\SampleState.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\Logic\Base\Literal.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header Literal.hh

"C:\Build\inc\Ravl\Logic\Literal.hh" :  "" ""
	copy ..\.\Logic\Base\Literal.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header Literal.hh

"C:\Build\inc\Ravl\Logic\Literal.hh" :  "" ""
	copy ..\.\Logic\Base\Literal.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\Var.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header Var.hh

"C:\Build\inc\Ravl\Logic\Var.hh" :  "" ""
	copy ..\.\Logic\Base\Var.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header Var.hh

"C:\Build\inc\Ravl\Logic\Var.hh" :  "" ""
	copy ..\.\Logic\Base\Var.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\Unify.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header Unify.hh

"C:\Build\inc\Ravl\Logic\Unify.hh" :  "" ""
	copy ..\.\Logic\Base\Unify.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header Unify.hh

"C:\Build\inc\Ravl\Logic\Unify.hh" :  "" ""
	copy ..\.\Logic\Base\Unify.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\BindSet.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header BindSet.hh

"C:\Build\inc\Ravl\Logic\BindSet.hh" :  "" ""
	copy ..\.\Logic\Base\BindSet.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header BindSet.hh

"C:\Build\inc\Ravl\Logic\BindSet.hh" :  "" ""
	copy ..\.\Logic\Base\BindSet.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\Tuple.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header Tuple.hh

"C:\Build\inc\Ravl\Logic\Tuple.hh" :  "" ""
	copy ..\.\Logic\Base\Tuple.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header Tuple.hh

"C:\Build\inc\Ravl\Logic\Tuple.hh" :  "" ""
	copy ..\.\Logic\Base\Tuple.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\LList.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header LList.hh

"C:\Build\inc\Ravl\Logic\LList.hh" :  "" ""
	copy ..\.\Logic\Base\LList.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header LList.hh

"C:\Build\inc\Ravl\Logic\LList.hh" :  "" ""
	copy ..\.\Logic\Base\LList.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\Condition.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header Condition.hh

"C:\Build\inc\Ravl\Logic\Condition.hh" :  "" ""
	copy ..\.\Logic\Base\Condition.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header Condition.hh

"C:\Build\inc\Ravl\Logic\Condition.hh" :  "" ""
	copy ..\.\Logic\Base\Condition.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\MinTerm.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header MinTerm.hh

"C:\Build\inc\Ravl\Logic\MinTerm.hh" :  "" ""
	copy ..\.\Logic\Base\MinTerm.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header MinTerm.hh

"C:\Build\inc\Ravl\Logic\MinTerm.hh" :  "" ""
	copy ..\.\Logic\Base\MinTerm.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\Or.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header Or.hh

"C:\Build\inc\Ravl\Logic\Or.hh" :  "" ""
	copy ..\.\Logic\Base\Or.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header Or.hh

"C:\Build\inc\Ravl\Logic\Or.hh" :  "" ""
	copy ..\.\Logic\Base\Or.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\And.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header And.hh

"C:\Build\inc\Ravl\Logic\And.hh" :  "" ""
	copy ..\.\Logic\Base\And.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header And.hh

"C:\Build\inc\Ravl\Logic\And.hh" :  "" ""
	copy ..\.\Logic\Base\And.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\Not.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header Not.hh

"C:\Build\inc\Ravl\Logic\Not.hh" :  "" ""
	copy ..\.\Logic\Base\Not.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header Not.hh

"C:\Build\inc\Ravl\Logic\Not.hh" :  "" ""
	copy ..\.\Logic\Base\Not.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\LiteralIter.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header LiteralIter.hh

"C:\Build\inc\Ravl\Logic\LiteralIter.hh" :  "" ""
	copy ..\.\Logic\Base\LiteralIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header LiteralIter.hh

"C:\Build\inc\Ravl\Logic\LiteralIter.hh" :  "" ""
	copy ..\.\Logic\Base\LiteralIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\LiteralIterWrap.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header LiteralIterWrap.hh

"C:\Build\inc\Ravl\Logic\LiteralIterWrap.hh" :  "" ""
	copy ..\.\Logic\Base\LiteralIterWrap.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header LiteralIterWrap.hh

"C:\Build\inc\Ravl\Logic\LiteralIterWrap.hh" :  "" ""
	copy ..\.\Logic\Base\LiteralIterWrap.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\LiteralMapIter.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header LiteralMapIter.hh

"C:\Build\inc\Ravl\Logic\LiteralMapIter.hh" :  "" ""
	copy ..\.\Logic\Base\LiteralMapIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header LiteralMapIter.hh

"C:\Build\inc\Ravl\Logic\LiteralMapIter.hh" :  "" ""
	copy ..\.\Logic\Base\LiteralMapIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\LiteralMapListIter.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header LiteralMapListIter.hh

"C:\Build\inc\Ravl\Logic\LiteralMapListIter.hh" :  "" ""
	copy ..\.\Logic\Base\LiteralMapListIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header LiteralMapListIter.hh

"C:\Build\inc\Ravl\Logic\LiteralMapListIter.hh" :  "" ""
	copy ..\.\Logic\Base\LiteralMapListIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\State.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header State.hh

"C:\Build\inc\Ravl\Logic\State.hh" :  "" ""
	copy ..\.\Logic\Base\State.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header State.hh

"C:\Build\inc\Ravl\Logic\State.hh" :  "" ""
	copy ..\.\Logic\Base\State.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\LiteralIter1.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header LiteralIter1.hh

"C:\Build\inc\Ravl\Logic\LiteralIter1.hh" :  "" ""
	copy ..\.\Logic\Base\LiteralIter1.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header LiteralIter1.hh

"C:\Build\inc\Ravl\Logic\LiteralIter1.hh" :  "" ""
	copy ..\.\Logic\Base\LiteralIter1.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\StateOrIter.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header StateOrIter.hh

"C:\Build\inc\Ravl\Logic\StateOrIter.hh" :  "" ""
	copy ..\.\Logic\Base\StateOrIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header StateOrIter.hh

"C:\Build\inc\Ravl\Logic\StateOrIter.hh" :  "" ""
	copy ..\.\Logic\Base\StateOrIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\StateSet.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header StateSet.hh

"C:\Build\inc\Ravl\Logic\StateSet.hh" :  "" ""
	copy ..\.\Logic\Base\StateSet.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header StateSet.hh

"C:\Build\inc\Ravl\Logic\StateSet.hh" :  "" ""
	copy ..\.\Logic\Base\StateSet.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\LiteralFilterIter.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header LiteralFilterIter.hh

"C:\Build\inc\Ravl\Logic\LiteralFilterIter.hh" :  "" ""
	copy ..\.\Logic\Base\LiteralFilterIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header LiteralFilterIter.hh

"C:\Build\inc\Ravl\Logic\LiteralFilterIter.hh" :  "" ""
	copy ..\.\Logic\Base\LiteralFilterIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\StateAndIter.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header StateAndIter.hh

"C:\Build\inc\Ravl\Logic\StateAndIter.hh" :  "" ""
	copy ..\.\Logic\Base\StateAndIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header StateAndIter.hh

"C:\Build\inc\Ravl\Logic\StateAndIter.hh" :  "" ""
	copy ..\.\Logic\Base\StateAndIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\NamedLiteral.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header NamedLiteral.hh

"C:\Build\inc\Ravl\Logic\NamedLiteral.hh" :  "" ""
	copy ..\.\Logic\Base\NamedLiteral.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header NamedLiteral.hh

"C:\Build\inc\Ravl\Logic\NamedLiteral.hh" :  "" ""
	copy ..\.\Logic\Base\NamedLiteral.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\NamedVar.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header NamedVar.hh

"C:\Build\inc\Ravl\Logic\NamedVar.hh" :  "" ""
	copy ..\.\Logic\Base\NamedVar.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header NamedVar.hh

"C:\Build\inc\Ravl\Logic\NamedVar.hh" :  "" ""
	copy ..\.\Logic\Base\NamedVar.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\LiteralIO.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header LiteralIO.hh

"C:\Build\inc\Ravl\Logic\LiteralIO.hh" :  "" ""
	copy ..\.\Logic\Base\LiteralIO.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header LiteralIO.hh

"C:\Build\inc\Ravl\Logic\LiteralIO.hh" :  "" ""
	copy ..\.\Logic\Base\LiteralIO.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\MinTermIter.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header MinTermIter.hh

"C:\Build\inc\Ravl\Logic\MinTermIter.hh" :  "" ""
	copy ..\.\Logic\Base\MinTermIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header MinTermIter.hh

"C:\Build\inc\Ravl\Logic\MinTermIter.hh" :  "" ""
	copy ..\.\Logic\Base\MinTermIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\Value.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header Value.hh

"C:\Build\inc\Ravl\Logic\Value.hh" :  "" ""
	copy ..\.\Logic\Base\Value.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header Value.hh

"C:\Build\inc\Ravl\Logic\Value.hh" :  "" ""
	copy ..\.\Logic\Base\Value.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Base\Context.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header Context.hh

"C:\Build\inc\Ravl\Logic\Context.hh" :  "" ""
	copy ..\.\Logic\Base\Context.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header Context.hh

"C:\Build\inc\Ravl\Logic\Context.hh" :  "" ""
	copy ..\.\Logic\Base\Context.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\LiteralIndexBase.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header LiteralIndexBase.hh

"C:\Build\inc\Ravl\Logic\LiteralIndexBase.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndexBase.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header LiteralIndexBase.hh

"C:\Build\inc\Ravl\Logic\LiteralIndexBase.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndexBase.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\LiteralIndexElement.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header LiteralIndexElement.hh

"C:\Build\inc\Ravl\Logic\LiteralIndexElement.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndexElement.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header LiteralIndexElement.hh

"C:\Build\inc\Ravl\Logic\LiteralIndexElement.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndexElement.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\LiteralIndexLeaf.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header LiteralIndexLeaf.hh

"C:\Build\inc\Ravl\Logic\LiteralIndexLeaf.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndexLeaf.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header LiteralIndexLeaf.hh

"C:\Build\inc\Ravl\Logic\LiteralIndexLeaf.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndexLeaf.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\LiteralIndexNode.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header LiteralIndexNode.hh

"C:\Build\inc\Ravl\Logic\LiteralIndexNode.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndexNode.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header LiteralIndexNode.hh

"C:\Build\inc\Ravl\Logic\LiteralIndexNode.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndexNode.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\LiteralIndex.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header LiteralIndex.hh

"C:\Build\inc\Ravl\Logic\LiteralIndex.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndex.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header LiteralIndex.hh

"C:\Build\inc\Ravl\Logic\LiteralIndex.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndex.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\LiteralIndexIter.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header LiteralIndexIter.hh

"C:\Build\inc\Ravl\Logic\LiteralIndexIter.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndexIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header LiteralIndexIter.hh

"C:\Build\inc\Ravl\Logic\LiteralIndexIter.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndexIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\LiteralIndexFilterBase.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header LiteralIndexFilterBase.hh

"C:\Build\inc\Ravl\Logic\LiteralIndexFilterBase.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndexFilterBase.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header LiteralIndexFilterBase.hh

"C:\Build\inc\Ravl\Logic\LiteralIndexFilterBase.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndexFilterBase.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\LiteralIndexFilter.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header LiteralIndexFilter.hh

"C:\Build\inc\Ravl\Logic\LiteralIndexFilter.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndexFilter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header LiteralIndexFilter.hh

"C:\Build\inc\Ravl\Logic\LiteralIndexFilter.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndexFilter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\LiteralIndexLeafIter.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header LiteralIndexLeafIter.hh

"C:\Build\inc\Ravl\Logic\LiteralIndexLeafIter.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndexLeafIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header LiteralIndexLeafIter.hh

"C:\Build\inc\Ravl\Logic\LiteralIndexLeafIter.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndexLeafIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\BLiteralIndex.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header BLiteralIndex.hh

"C:\Build\inc\Ravl\Logic\BLiteralIndex.hh" :  "" ""
	copy ..\.\Logic\Index\BLiteralIndex.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header BLiteralIndex.hh

"C:\Build\inc\Ravl\Logic\BLiteralIndex.hh" :  "" ""
	copy ..\.\Logic\Index\BLiteralIndex.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\BMinTermIndex.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header BMinTermIndex.hh

"C:\Build\inc\Ravl\Logic\BMinTermIndex.hh" :  "" ""
	copy ..\.\Logic\Index\BMinTermIndex.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header BMinTermIndex.hh

"C:\Build\inc\Ravl\Logic\BMinTermIndex.hh" :  "" ""
	copy ..\.\Logic\Index\BMinTermIndex.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\BMinTermIndexIter.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header BMinTermIndexIter.hh

"C:\Build\inc\Ravl\Logic\BMinTermIndexIter.hh" :  "" ""
	copy ..\.\Logic\Index\BMinTermIndexIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header BMinTermIndexIter.hh

"C:\Build\inc\Ravl\Logic\BMinTermIndexIter.hh" :  "" ""
	copy ..\.\Logic\Index\BMinTermIndexIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\BMinTermListIndex.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header BMinTermListIndex.hh

"C:\Build\inc\Ravl\Logic\BMinTermListIndex.hh" :  "" ""
	copy ..\.\Logic\Index\BMinTermListIndex.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header BMinTermListIndex.hh

"C:\Build\inc\Ravl\Logic\BMinTermListIndex.hh" :  "" ""
	copy ..\.\Logic\Index\BMinTermListIndex.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\LiteralIndexLeafVarIter.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header LiteralIndexLeafVarIter.hh

"C:\Build\inc\Ravl\Logic\LiteralIndexLeafVarIter.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndexLeafVarIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header LiteralIndexLeafVarIter.hh

"C:\Build\inc\Ravl\Logic\LiteralIndexLeafVarIter.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndexLeafVarIter.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\StateIndexed.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header StateIndexed.hh

"C:\Build\inc\Ravl\Logic\StateIndexed.hh" :  "" ""
	copy ..\.\Logic\Index\StateIndexed.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header StateIndexed.hh

"C:\Build\inc\Ravl\Logic\StateIndexed.hh" :  "" ""
	copy ..\.\Logic\Index\StateIndexed.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\Index\LiteralIndexFilterRaw.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header LiteralIndexFilterRaw.hh

"C:\Build\inc\Ravl\Logic\LiteralIndexFilterRaw.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndexFilterRaw.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header LiteralIndexFilterRaw.hh

"C:\Build\inc\Ravl\Logic\LiteralIndexFilterRaw.hh" :  "" ""
	copy ..\.\Logic\Index\LiteralIndexFilterRaw.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\DecisionTree\DecisionTreeElement.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header DecisionTreeElement.hh

"C:\Build\inc\Ravl\Logic\DecisionTreeElement.hh" :  "" ""
	copy ..\.\Logic\DecisionTree\DecisionTreeElement.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header DecisionTreeElement.hh

"C:\Build\inc\Ravl\Logic\DecisionTreeElement.hh" :  "" ""
	copy ..\.\Logic\DecisionTree\DecisionTreeElement.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\DecisionTree\DecisionTreeLeaf.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header DecisionTreeLeaf.hh

"C:\Build\inc\Ravl\Logic\DecisionTreeLeaf.hh" :  "" ""
	copy ..\.\Logic\DecisionTree\DecisionTreeLeaf.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header DecisionTreeLeaf.hh

"C:\Build\inc\Ravl\Logic\DecisionTreeLeaf.hh" :  "" ""
	copy ..\.\Logic\DecisionTree\DecisionTreeLeaf.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\DecisionTree\DecisionTreeBase.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header DecisionTreeBase.hh

"C:\Build\inc\Ravl\Logic\DecisionTreeBase.hh" :  "" ""
	copy ..\.\Logic\DecisionTree\DecisionTreeBase.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header DecisionTreeBase.hh

"C:\Build\inc\Ravl\Logic\DecisionTreeBase.hh" :  "" ""
	copy ..\.\Logic\DecisionTree\DecisionTreeBase.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\DecisionTree\DecisionTree.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header DecisionTree.hh

"C:\Build\inc\Ravl\Logic\DecisionTree.hh" :  "" ""
	copy ..\.\Logic\DecisionTree\DecisionTree.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header DecisionTree.hh

"C:\Build\inc\Ravl\Logic\DecisionTree.hh" :  "" ""
	copy ..\.\Logic\DecisionTree\DecisionTree.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\DecisionTree\DecisionTreeBranch.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header DecisionTreeBranch.hh

"C:\Build\inc\Ravl\Logic\DecisionTreeBranch.hh" :  "" ""
	copy ..\.\Logic\DecisionTree\DecisionTreeBranch.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header DecisionTreeBranch.hh

"C:\Build\inc\Ravl\Logic\DecisionTreeBranch.hh" :  "" ""
	copy ..\.\Logic\DecisionTree\DecisionTreeBranch.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\DecisionTree\DecisionTreeBranchBinary.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header DecisionTreeBranchBinary.hh

"C:\Build\inc\Ravl\Logic\DecisionTreeBranchBinary.hh" :  "" ""
	copy ..\.\Logic\DecisionTree\DecisionTreeBranchBinary.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header DecisionTreeBranchBinary.hh

"C:\Build\inc\Ravl\Logic\DecisionTreeBranchBinary.hh" :  "" ""
	copy ..\.\Logic\DecisionTree\DecisionTreeBranchBinary.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\DecisionTree\DecisionExamples.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header DecisionExamples.hh

"C:\Build\inc\Ravl\Logic\DecisionExamples.hh" :  "" ""
	copy ..\.\Logic\DecisionTree\DecisionExamples.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header DecisionExamples.hh

"C:\Build\inc\Ravl\Logic\DecisionExamples.hh" :  "" ""
	copy ..\.\Logic\DecisionTree\DecisionExamples.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\DecisionTree\Discriminator.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header Discriminator.hh

"C:\Build\inc\Ravl\Logic\Discriminator.hh" :  "" ""
	copy ..\.\Logic\DecisionTree\Discriminator.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header Discriminator.hh

"C:\Build\inc\Ravl\Logic\Discriminator.hh" :  "" ""
	copy ..\.\Logic\DecisionTree\Discriminator.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\DecisionTree\SampleLiteral.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header SampleLiteral.hh

"C:\Build\inc\Ravl\Logic\SampleLiteral.hh" :  "" ""
	copy ..\.\Logic\DecisionTree\SampleLiteral.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header SampleLiteral.hh

"C:\Build\inc\Ravl\Logic\SampleLiteral.hh" :  "" ""
	copy ..\.\Logic\DecisionTree\SampleLiteral.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Logic\DecisionTree\SampleState.hh

!IF  "$(CFG)" == "RavlLogic - Win32 Release"

# Begin Custom Build - Install Header SampleState.hh

"C:\Build\inc\Ravl\Logic\SampleState.hh" :  "" ""
	copy ..\.\Logic\DecisionTree\SampleState.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlLogic - Win32 Debug"

# Begin Custom Build - Install Header SampleState.hh

"C:\Build\inc\Ravl\Logic\SampleState.hh" :  "" ""
	copy ..\.\Logic\DecisionTree\SampleState.hh C:\Build\inc\Ravl\Logic

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
