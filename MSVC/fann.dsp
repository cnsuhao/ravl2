# Microsoft Developer Studio Project File - Name="fann" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=fann - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "fann.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "fann.mak" CFG="fann - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "fann - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fann - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "fann - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\fann"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "fann - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\fann"
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

# Name "fann - Win32 Release"
# Name "fann - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\PatternRec\fann\floatfann.c
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\PatternRec\fann\fann.h

!IF  "$(CFG)" == "fann - Win32 Release"

# Begin Custom Build - Install Header fann.h

"C:\Build\inc\\fann.h" :  "" ""
	copy ..\.\PatternRec\fann\fann.h C:\Build\inc\

# End Custom Build

!ELSEIF  "$(CFG)" == "fann - Win32 Debug"

# Begin Custom Build - Install Header fann.h

"C:\Build\inc\\fann.h" :  "" ""
	copy ..\.\PatternRec\fann\fann.h C:\Build\inc\

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\fann\compat_time.h

!IF  "$(CFG)" == "fann - Win32 Release"

# Begin Custom Build - Install Header compat_time.h

"C:\Build\inc\\compat_time.h" :  "" ""
	copy ..\.\PatternRec\fann\compat_time.h C:\Build\inc\

# End Custom Build

!ELSEIF  "$(CFG)" == "fann - Win32 Debug"

# Begin Custom Build - Install Header compat_time.h

"C:\Build\inc\\compat_time.h" :  "" ""
	copy ..\.\PatternRec\fann\compat_time.h C:\Build\inc\

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\fann\fann_activation.h

!IF  "$(CFG)" == "fann - Win32 Release"

# Begin Custom Build - Install Header fann_activation.h

"C:\Build\inc\\fann_activation.h" :  "" ""
	copy ..\.\PatternRec\fann\fann_activation.h C:\Build\inc\

# End Custom Build

!ELSEIF  "$(CFG)" == "fann - Win32 Debug"

# Begin Custom Build - Install Header fann_activation.h

"C:\Build\inc\\fann_activation.h" :  "" ""
	copy ..\.\PatternRec\fann\fann_activation.h C:\Build\inc\

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\fann\fann_error.h

!IF  "$(CFG)" == "fann - Win32 Release"

# Begin Custom Build - Install Header fann_error.h

"C:\Build\inc\\fann_error.h" :  "" ""
	copy ..\.\PatternRec\fann\fann_error.h C:\Build\inc\

# End Custom Build

!ELSEIF  "$(CFG)" == "fann - Win32 Debug"

# Begin Custom Build - Install Header fann_error.h

"C:\Build\inc\\fann_error.h" :  "" ""
	copy ..\.\PatternRec\fann\fann_error.h C:\Build\inc\

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\fann\fann_io.h

!IF  "$(CFG)" == "fann - Win32 Release"

# Begin Custom Build - Install Header fann_io.h

"C:\Build\inc\\fann_io.h" :  "" ""
	copy ..\.\PatternRec\fann\fann_io.h C:\Build\inc\

# End Custom Build

!ELSEIF  "$(CFG)" == "fann - Win32 Debug"

# Begin Custom Build - Install Header fann_io.h

"C:\Build\inc\\fann_io.h" :  "" ""
	copy ..\.\PatternRec\fann\fann_io.h C:\Build\inc\

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\fann\floatfann.h

!IF  "$(CFG)" == "fann - Win32 Release"

# Begin Custom Build - Install Header floatfann.h

"C:\Build\inc\\floatfann.h" :  "" ""
	copy ..\.\PatternRec\fann\floatfann.h C:\Build\inc\

# End Custom Build

!ELSEIF  "$(CFG)" == "fann - Win32 Debug"

# Begin Custom Build - Install Header floatfann.h

"C:\Build\inc\\floatfann.h" :  "" ""
	copy ..\.\PatternRec\fann\floatfann.h C:\Build\inc\

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\fann\fann_cascade.h

!IF  "$(CFG)" == "fann - Win32 Release"

# Begin Custom Build - Install Header fann_cascade.h

"C:\Build\inc\\fann_cascade.h" :  "" ""
	copy ..\.\PatternRec\fann\fann_cascade.h C:\Build\inc\

# End Custom Build

!ELSEIF  "$(CFG)" == "fann - Win32 Debug"

# Begin Custom Build - Install Header fann_cascade.h

"C:\Build\inc\\fann_cascade.h" :  "" ""
	copy ..\.\PatternRec\fann\fann_cascade.h C:\Build\inc\

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\fann\fann_train.h

!IF  "$(CFG)" == "fann - Win32 Release"

# Begin Custom Build - Install Header fann_train.h

"C:\Build\inc\\fann_train.h" :  "" ""
	copy ..\.\PatternRec\fann\fann_train.h C:\Build\inc\

# End Custom Build

!ELSEIF  "$(CFG)" == "fann - Win32 Debug"

# Begin Custom Build - Install Header fann_train.h

"C:\Build\inc\\fann_train.h" :  "" ""
	copy ..\.\PatternRec\fann\fann_train.h C:\Build\inc\

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\fann\doublefann.h

!IF  "$(CFG)" == "fann - Win32 Release"

# Begin Custom Build - Install Header doublefann.h

"C:\Build\inc\\doublefann.h" :  "" ""
	copy ..\.\PatternRec\fann\doublefann.h C:\Build\inc\

# End Custom Build

!ELSEIF  "$(CFG)" == "fann - Win32 Debug"

# Begin Custom Build - Install Header doublefann.h

"C:\Build\inc\\doublefann.h" :  "" ""
	copy ..\.\PatternRec\fann\doublefann.h C:\Build\inc\

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\fann\fann_data.h

!IF  "$(CFG)" == "fann - Win32 Release"

# Begin Custom Build - Install Header fann_data.h

"C:\Build\inc\\fann_data.h" :  "" ""
	copy ..\.\PatternRec\fann\fann_data.h C:\Build\inc\

# End Custom Build

!ELSEIF  "$(CFG)" == "fann - Win32 Debug"

# Begin Custom Build - Install Header fann_data.h

"C:\Build\inc\\fann_data.h" :  "" ""
	copy ..\.\PatternRec\fann\fann_data.h C:\Build\inc\

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\fann\fann_internal.h

!IF  "$(CFG)" == "fann - Win32 Release"

# Begin Custom Build - Install Header fann_internal.h

"C:\Build\inc\\fann_internal.h" :  "" ""
	copy ..\.\PatternRec\fann\fann_internal.h C:\Build\inc\

# End Custom Build

!ELSEIF  "$(CFG)" == "fann - Win32 Debug"

# Begin Custom Build - Install Header fann_internal.h

"C:\Build\inc\\fann_internal.h" :  "" ""
	copy ..\.\PatternRec\fann\fann_internal.h C:\Build\inc\

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\fann\fixedfann.h

!IF  "$(CFG)" == "fann - Win32 Release"

# Begin Custom Build - Install Header fixedfann.h

"C:\Build\inc\\fixedfann.h" :  "" ""
	copy ..\.\PatternRec\fann\fixedfann.h C:\Build\inc\

# End Custom Build

!ELSEIF  "$(CFG)" == "fann - Win32 Debug"

# Begin Custom Build - Install Header fixedfann.h

"C:\Build\inc\\fixedfann.h" :  "" ""
	copy ..\.\PatternRec\fann\fixedfann.h C:\Build\inc\

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\PatternRec\fann\fann_common.h

!IF  "$(CFG)" == "fann - Win32 Release"

# Begin Custom Build - Install Header fann_common.h

"C:\Build\inc\\fann_common.h" :  "" ""
	copy ..\.\PatternRec\fann\fann_common.h C:\Build\inc\

# End Custom Build

!ELSEIF  "$(CFG)" == "fann - Win32 Debug"

# Begin Custom Build - Install Header fann_common.h

"C:\Build\inc\\fann_common.h" :  "" ""
	copy ..\.\PatternRec\fann\fann_common.h C:\Build\inc\

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
