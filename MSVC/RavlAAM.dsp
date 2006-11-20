# Microsoft Developer Studio Project File - Name="RavlAAM" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlAAM - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlAAM.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlAAM.mak" CFG="RavlAAM - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlAAM - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlAAM - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlAAM - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlAAM"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlAAM - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlAAM"
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

# Name "RavlAAM - Win32 Release"
# Name "RavlAAM - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMAppearance.cc
# End Source File

# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMShapeModel.cc
# End Source File

# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMAffineShapeModel.cc
# End Source File

# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMScaleRotationShapeModel.cc
# End Source File

# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMAppearanceModel.cc
# End Source File

# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMAppearanceUtil.cc
# End Source File

# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMActiveAppearanceModel.cc
# End Source File

# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMSampleStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMMultiResActiveAppearanceModel.cc
# End Source File

# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMFaceLocalisation.cc
# End Source File

# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMActiveAppearanceModelsIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMActiveAppearanceModelMustLink.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMAppearance.hh

!IF  "$(CFG)" == "RavlAAM - Win32 Release"

# Begin Custom Build - Install Header AAMAppearance.hh

"C:\Build\inc\Ravl\Image\AAMAppearance.hh" :  "" ""
	copy ..\.\CompVision\ActiveAppearanceModels\AAMAppearance.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlAAM - Win32 Debug"

# Begin Custom Build - Install Header AAMAppearance.hh

"C:\Build\inc\Ravl\Image\AAMAppearance.hh" :  "" ""
	copy ..\.\CompVision\ActiveAppearanceModels\AAMAppearance.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMShapeModel.hh

!IF  "$(CFG)" == "RavlAAM - Win32 Release"

# Begin Custom Build - Install Header AAMShapeModel.hh

"C:\Build\inc\Ravl\Image\AAMShapeModel.hh" :  "" ""
	copy ..\.\CompVision\ActiveAppearanceModels\AAMShapeModel.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlAAM - Win32 Debug"

# Begin Custom Build - Install Header AAMShapeModel.hh

"C:\Build\inc\Ravl\Image\AAMShapeModel.hh" :  "" ""
	copy ..\.\CompVision\ActiveAppearanceModels\AAMShapeModel.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMAffineShapeModel.hh

!IF  "$(CFG)" == "RavlAAM - Win32 Release"

# Begin Custom Build - Install Header AAMAffineShapeModel.hh

"C:\Build\inc\Ravl\Image\AAMAffineShapeModel.hh" :  "" ""
	copy ..\.\CompVision\ActiveAppearanceModels\AAMAffineShapeModel.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlAAM - Win32 Debug"

# Begin Custom Build - Install Header AAMAffineShapeModel.hh

"C:\Build\inc\Ravl\Image\AAMAffineShapeModel.hh" :  "" ""
	copy ..\.\CompVision\ActiveAppearanceModels\AAMAffineShapeModel.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMScaleRotationShapeModel.hh

!IF  "$(CFG)" == "RavlAAM - Win32 Release"

# Begin Custom Build - Install Header AAMScaleRotationShapeModel.hh

"C:\Build\inc\Ravl\Image\AAMScaleRotationShapeModel.hh" :  "" ""
	copy ..\.\CompVision\ActiveAppearanceModels\AAMScaleRotationShapeModel.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlAAM - Win32 Debug"

# Begin Custom Build - Install Header AAMScaleRotationShapeModel.hh

"C:\Build\inc\Ravl\Image\AAMScaleRotationShapeModel.hh" :  "" ""
	copy ..\.\CompVision\ActiveAppearanceModels\AAMScaleRotationShapeModel.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMAppearanceModel.hh

!IF  "$(CFG)" == "RavlAAM - Win32 Release"

# Begin Custom Build - Install Header AAMAppearanceModel.hh

"C:\Build\inc\Ravl\Image\AAMAppearanceModel.hh" :  "" ""
	copy ..\.\CompVision\ActiveAppearanceModels\AAMAppearanceModel.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlAAM - Win32 Debug"

# Begin Custom Build - Install Header AAMAppearanceModel.hh

"C:\Build\inc\Ravl\Image\AAMAppearanceModel.hh" :  "" ""
	copy ..\.\CompVision\ActiveAppearanceModels\AAMAppearanceModel.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMAppearanceUtil.hh

!IF  "$(CFG)" == "RavlAAM - Win32 Release"

# Begin Custom Build - Install Header AAMAppearanceUtil.hh

"C:\Build\inc\Ravl\Image\AAMAppearanceUtil.hh" :  "" ""
	copy ..\.\CompVision\ActiveAppearanceModels\AAMAppearanceUtil.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlAAM - Win32 Debug"

# Begin Custom Build - Install Header AAMAppearanceUtil.hh

"C:\Build\inc\Ravl\Image\AAMAppearanceUtil.hh" :  "" ""
	copy ..\.\CompVision\ActiveAppearanceModels\AAMAppearanceUtil.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMActiveAppearanceModel.hh

!IF  "$(CFG)" == "RavlAAM - Win32 Release"

# Begin Custom Build - Install Header AAMActiveAppearanceModel.hh

"C:\Build\inc\Ravl\Image\AAMActiveAppearanceModel.hh" :  "" ""
	copy ..\.\CompVision\ActiveAppearanceModels\AAMActiveAppearanceModel.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlAAM - Win32 Debug"

# Begin Custom Build - Install Header AAMActiveAppearanceModel.hh

"C:\Build\inc\Ravl\Image\AAMActiveAppearanceModel.hh" :  "" ""
	copy ..\.\CompVision\ActiveAppearanceModels\AAMActiveAppearanceModel.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMSampleStream.hh

!IF  "$(CFG)" == "RavlAAM - Win32 Release"

# Begin Custom Build - Install Header AAMSampleStream.hh

"C:\Build\inc\Ravl\Image\AAMSampleStream.hh" :  "" ""
	copy ..\.\CompVision\ActiveAppearanceModels\AAMSampleStream.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlAAM - Win32 Debug"

# Begin Custom Build - Install Header AAMSampleStream.hh

"C:\Build\inc\Ravl\Image\AAMSampleStream.hh" :  "" ""
	copy ..\.\CompVision\ActiveAppearanceModels\AAMSampleStream.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMMultiResActiveAppearanceModel.hh

!IF  "$(CFG)" == "RavlAAM - Win32 Release"

# Begin Custom Build - Install Header AAMMultiResActiveAppearanceModel.hh

"C:\Build\inc\Ravl\Image\AAMMultiResActiveAppearanceModel.hh" :  "" ""
	copy ..\.\CompVision\ActiveAppearanceModels\AAMMultiResActiveAppearanceModel.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlAAM - Win32 Debug"

# Begin Custom Build - Install Header AAMMultiResActiveAppearanceModel.hh

"C:\Build\inc\Ravl\Image\AAMMultiResActiveAppearanceModel.hh" :  "" ""
	copy ..\.\CompVision\ActiveAppearanceModels\AAMMultiResActiveAppearanceModel.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\CompVision\ActiveAppearanceModels\AAMFaceLocalisation.hh

!IF  "$(CFG)" == "RavlAAM - Win32 Release"

# Begin Custom Build - Install Header AAMFaceLocalisation.hh

"C:\Build\inc\Ravl\Image\AAMFaceLocalisation.hh" :  "" ""
	copy ..\.\CompVision\ActiveAppearanceModels\AAMFaceLocalisation.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlAAM - Win32 Debug"

# Begin Custom Build - Install Header AAMFaceLocalisation.hh

"C:\Build\inc\Ravl\Image\AAMFaceLocalisation.hh" :  "" ""
	copy ..\.\CompVision\ActiveAppearanceModels\AAMFaceLocalisation.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
