# Microsoft Developer Studio Project File - Name="RavlAudioFeatures" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlAudioFeatures - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlAudioFeatures.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlAudioFeatures.mak" CFG="RavlAudioFeatures - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlAudioFeatures - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlAudioFeatures - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlAudioFeatures - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlAudioFeatures"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlAudioFeatures - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlAudioFeatures"
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

# Name "RavlAudioFeatures - Win32 Release"
# Name "RavlAudioFeatures - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\Audio\Features\MelSpectrum.cc
# End Source File

# Begin Source File
SOURCE=..\.\Audio\Features\MelCepstrum.cc
# End Source File

# Begin Source File
SOURCE=..\.\Audio\Features\FeatureMFCC.cc
# End Source File

# Begin Source File
SOURCE=..\.\Audio\Features\VectorDelta012.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\Audio\Features\MelSpectrum.hh

!IF  "$(CFG)" == "RavlAudioFeatures - Win32 Release"

# Begin Custom Build - Install Header MelSpectrum.hh

"C:\Build\inc\Ravl\Audio\MelSpectrum.hh" :  "" ""
	copy ..\.\Audio\Features\MelSpectrum.hh C:\Build\inc\Ravl\Audio

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlAudioFeatures - Win32 Debug"

# Begin Custom Build - Install Header MelSpectrum.hh

"C:\Build\inc\Ravl\Audio\MelSpectrum.hh" :  "" ""
	copy ..\.\Audio\Features\MelSpectrum.hh C:\Build\inc\Ravl\Audio

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Audio\Features\MelCepstrum.hh

!IF  "$(CFG)" == "RavlAudioFeatures - Win32 Release"

# Begin Custom Build - Install Header MelCepstrum.hh

"C:\Build\inc\Ravl\Audio\MelCepstrum.hh" :  "" ""
	copy ..\.\Audio\Features\MelCepstrum.hh C:\Build\inc\Ravl\Audio

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlAudioFeatures - Win32 Debug"

# Begin Custom Build - Install Header MelCepstrum.hh

"C:\Build\inc\Ravl\Audio\MelCepstrum.hh" :  "" ""
	copy ..\.\Audio\Features\MelCepstrum.hh C:\Build\inc\Ravl\Audio

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Audio\Features\PreEmphasis.hh

!IF  "$(CFG)" == "RavlAudioFeatures - Win32 Release"

# Begin Custom Build - Install Header PreEmphasis.hh

"C:\Build\inc\Ravl\Audio\PreEmphasis.hh" :  "" ""
	copy ..\.\Audio\Features\PreEmphasis.hh C:\Build\inc\Ravl\Audio

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlAudioFeatures - Win32 Debug"

# Begin Custom Build - Install Header PreEmphasis.hh

"C:\Build\inc\Ravl\Audio\PreEmphasis.hh" :  "" ""
	copy ..\.\Audio\Features\PreEmphasis.hh C:\Build\inc\Ravl\Audio

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Audio\Features\FeatureMFCC.hh

!IF  "$(CFG)" == "RavlAudioFeatures - Win32 Release"

# Begin Custom Build - Install Header FeatureMFCC.hh

"C:\Build\inc\Ravl\Audio\FeatureMFCC.hh" :  "" ""
	copy ..\.\Audio\Features\FeatureMFCC.hh C:\Build\inc\Ravl\Audio

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlAudioFeatures - Win32 Debug"

# Begin Custom Build - Install Header FeatureMFCC.hh

"C:\Build\inc\Ravl\Audio\FeatureMFCC.hh" :  "" ""
	copy ..\.\Audio\Features\FeatureMFCC.hh C:\Build\inc\Ravl\Audio

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Audio\Features\VectorDelta012.hh

!IF  "$(CFG)" == "RavlAudioFeatures - Win32 Release"

# Begin Custom Build - Install Header VectorDelta012.hh

"C:\Build\inc\Ravl\Audio\VectorDelta012.hh" :  "" ""
	copy ..\.\Audio\Features\VectorDelta012.hh C:\Build\inc\Ravl\Audio

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlAudioFeatures - Win32 Debug"

# Begin Custom Build - Install Header VectorDelta012.hh

"C:\Build\inc\Ravl\Audio\VectorDelta012.hh" :  "" ""
	copy ..\.\Audio\Features\VectorDelta012.hh C:\Build\inc\Ravl\Audio

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
