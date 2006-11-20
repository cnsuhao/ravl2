# Microsoft Developer Studio Project File - Name="Optimisation" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Optimisation - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Optimisation.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Optimisation.mak" CFG="Optimisation - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Optimisation - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Optimisation - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Optimisation - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\Optimisation"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Optimisation - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\Optimisation"
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

# Name "Optimisation - Win32 Release"
# Name "Optimisation - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\PatternRec\Optimise\Parameters.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\Cost.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\CostInvert.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\CostFunction.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\CostFunction1d.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\BracketMinimum.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\Optimise.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\OptimiseDescent.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\OptimiseRandomUniform.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\OptimiseSobol.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\OptimiseBrent.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\OptimisePowell.cc
# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\OptimiseGrid.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\PatternRec\Optimise\Parameters.hh

!IF  "$(CFG)" == "Optimisation - Win32 Release"

# Begin Custom Build - Install Header Parameters.hh

"C:\Build\inc\Ravl\PatternRec\Parameters.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\Parameters.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "Optimisation - Win32 Debug"

# Begin Custom Build - Install Header Parameters.hh

"C:\Build\inc\Ravl\PatternRec\Parameters.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\Parameters.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\Cost.hh

!IF  "$(CFG)" == "Optimisation - Win32 Release"

# Begin Custom Build - Install Header Cost.hh

"C:\Build\inc\Ravl\PatternRec\Cost.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\Cost.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "Optimisation - Win32 Debug"

# Begin Custom Build - Install Header Cost.hh

"C:\Build\inc\Ravl\PatternRec\Cost.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\Cost.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\CostInvert.hh

!IF  "$(CFG)" == "Optimisation - Win32 Release"

# Begin Custom Build - Install Header CostInvert.hh

"C:\Build\inc\Ravl\PatternRec\CostInvert.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\CostInvert.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "Optimisation - Win32 Debug"

# Begin Custom Build - Install Header CostInvert.hh

"C:\Build\inc\Ravl\PatternRec\CostInvert.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\CostInvert.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\CostFunction.hh

!IF  "$(CFG)" == "Optimisation - Win32 Release"

# Begin Custom Build - Install Header CostFunction.hh

"C:\Build\inc\Ravl\PatternRec\CostFunction.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\CostFunction.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "Optimisation - Win32 Debug"

# Begin Custom Build - Install Header CostFunction.hh

"C:\Build\inc\Ravl\PatternRec\CostFunction.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\CostFunction.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\CostFunction1d.hh

!IF  "$(CFG)" == "Optimisation - Win32 Release"

# Begin Custom Build - Install Header CostFunction1d.hh

"C:\Build\inc\Ravl\PatternRec\CostFunction1d.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\CostFunction1d.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "Optimisation - Win32 Debug"

# Begin Custom Build - Install Header CostFunction1d.hh

"C:\Build\inc\Ravl\PatternRec\CostFunction1d.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\CostFunction1d.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\BracketMinimum.hh

!IF  "$(CFG)" == "Optimisation - Win32 Release"

# Begin Custom Build - Install Header BracketMinimum.hh

"C:\Build\inc\Ravl\PatternRec\BracketMinimum.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\BracketMinimum.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "Optimisation - Win32 Debug"

# Begin Custom Build - Install Header BracketMinimum.hh

"C:\Build\inc\Ravl\PatternRec\BracketMinimum.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\BracketMinimum.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\Optimise.hh

!IF  "$(CFG)" == "Optimisation - Win32 Release"

# Begin Custom Build - Install Header Optimise.hh

"C:\Build\inc\Ravl\PatternRec\Optimise.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\Optimise.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "Optimisation - Win32 Debug"

# Begin Custom Build - Install Header Optimise.hh

"C:\Build\inc\Ravl\PatternRec\Optimise.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\Optimise.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\OptimiseDescent.hh

!IF  "$(CFG)" == "Optimisation - Win32 Release"

# Begin Custom Build - Install Header OptimiseDescent.hh

"C:\Build\inc\Ravl\PatternRec\OptimiseDescent.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\OptimiseDescent.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "Optimisation - Win32 Debug"

# Begin Custom Build - Install Header OptimiseDescent.hh

"C:\Build\inc\Ravl\PatternRec\OptimiseDescent.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\OptimiseDescent.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\OptimiseRandomUniform.hh

!IF  "$(CFG)" == "Optimisation - Win32 Release"

# Begin Custom Build - Install Header OptimiseRandomUniform.hh

"C:\Build\inc\Ravl\PatternRec\OptimiseRandomUniform.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\OptimiseRandomUniform.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "Optimisation - Win32 Debug"

# Begin Custom Build - Install Header OptimiseRandomUniform.hh

"C:\Build\inc\Ravl\PatternRec\OptimiseRandomUniform.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\OptimiseRandomUniform.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\OptimiseSobol.hh

!IF  "$(CFG)" == "Optimisation - Win32 Release"

# Begin Custom Build - Install Header OptimiseSobol.hh

"C:\Build\inc\Ravl\PatternRec\OptimiseSobol.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\OptimiseSobol.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "Optimisation - Win32 Debug"

# Begin Custom Build - Install Header OptimiseSobol.hh

"C:\Build\inc\Ravl\PatternRec\OptimiseSobol.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\OptimiseSobol.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\OptimiseBrent.hh

!IF  "$(CFG)" == "Optimisation - Win32 Release"

# Begin Custom Build - Install Header OptimiseBrent.hh

"C:\Build\inc\Ravl\PatternRec\OptimiseBrent.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\OptimiseBrent.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "Optimisation - Win32 Debug"

# Begin Custom Build - Install Header OptimiseBrent.hh

"C:\Build\inc\Ravl\PatternRec\OptimiseBrent.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\OptimiseBrent.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\OptimisePowell.hh

!IF  "$(CFG)" == "Optimisation - Win32 Release"

# Begin Custom Build - Install Header OptimisePowell.hh

"C:\Build\inc\Ravl\PatternRec\OptimisePowell.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\OptimisePowell.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "Optimisation - Win32 Debug"

# Begin Custom Build - Install Header OptimisePowell.hh

"C:\Build\inc\Ravl\PatternRec\OptimisePowell.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\OptimisePowell.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\Optimise\OptimiseGrid.hh

!IF  "$(CFG)" == "Optimisation - Win32 Release"

# Begin Custom Build - Install Header OptimiseGrid.hh

"C:\Build\inc\Ravl\PatternRec\OptimiseGrid.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\OptimiseGrid.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ELSEIF  "$(CFG)" == "Optimisation - Win32 Debug"

# Begin Custom Build - Install Header OptimiseGrid.hh

"C:\Build\inc\Ravl\PatternRec\OptimiseGrid.hh" :  "" ""
	copy ..\.\PatternRec\Optimise\OptimiseGrid.hh C:\Build\inc\Ravl\PatternRec

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
