# Microsoft Developer Studio Project File - Name="Ravl3DIO" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Ravl3DIO - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Ravl3DIO.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ravl3DIO.mak" CFG="Ravl3DIO - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Ravl3DIO - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Ravl3DIO - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Ravl3DIO - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\Ravl3DIO"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Ravl3DIO - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\Ravl3DIO"
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

# Name "Ravl3DIO - Win32 Release"
# Name "Ravl3DIO - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\3D\MeshIO\VRMLFileIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\FormatVRMLFile.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\CTriFileIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\FormatCTriFile.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\TriFileIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\FormatTriFile.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\MeshIOObj.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\FormatMeshObj.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\TriMeshIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\TexTriMeshIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\POVRayFileIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\FormatPOVRayFile.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\MeshConv.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\RavlMeshIO.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\3D\MeshIO\RavlMeshIO.hh

!IF  "$(CFG)" == "Ravl3DIO - Win32 Release"

# Begin Custom Build - Install Header RavlMeshIO.hh

"C:\Build\inc\Ravl\3D\RavlMeshIO.hh" :  "" ""
	copy ..\.\3D\MeshIO\RavlMeshIO.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3DIO - Win32 Debug"

# Begin Custom Build - Install Header RavlMeshIO.hh

"C:\Build\inc\Ravl\3D\RavlMeshIO.hh" :  "" ""
	copy ..\.\3D\MeshIO\RavlMeshIO.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\VRMLFileIO.hh

!IF  "$(CFG)" == "Ravl3DIO - Win32 Release"

# Begin Custom Build - Install Header VRMLFileIO.hh

"C:\Build\inc\Ravl\3D\VRMLFileIO.hh" :  "" ""
	copy ..\.\3D\MeshIO\VRMLFileIO.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3DIO - Win32 Debug"

# Begin Custom Build - Install Header VRMLFileIO.hh

"C:\Build\inc\Ravl\3D\VRMLFileIO.hh" :  "" ""
	copy ..\.\3D\MeshIO\VRMLFileIO.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\FormatVRMLFile.hh

!IF  "$(CFG)" == "Ravl3DIO - Win32 Release"

# Begin Custom Build - Install Header FormatVRMLFile.hh

"C:\Build\inc\Ravl\3D\FormatVRMLFile.hh" :  "" ""
	copy ..\.\3D\MeshIO\FormatVRMLFile.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3DIO - Win32 Debug"

# Begin Custom Build - Install Header FormatVRMLFile.hh

"C:\Build\inc\Ravl\3D\FormatVRMLFile.hh" :  "" ""
	copy ..\.\3D\MeshIO\FormatVRMLFile.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\CTriFileIO.hh

!IF  "$(CFG)" == "Ravl3DIO - Win32 Release"

# Begin Custom Build - Install Header CTriFileIO.hh

"C:\Build\inc\Ravl\3D\CTriFileIO.hh" :  "" ""
	copy ..\.\3D\MeshIO\CTriFileIO.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3DIO - Win32 Debug"

# Begin Custom Build - Install Header CTriFileIO.hh

"C:\Build\inc\Ravl\3D\CTriFileIO.hh" :  "" ""
	copy ..\.\3D\MeshIO\CTriFileIO.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\FormatCTriFile.hh

!IF  "$(CFG)" == "Ravl3DIO - Win32 Release"

# Begin Custom Build - Install Header FormatCTriFile.hh

"C:\Build\inc\Ravl\3D\FormatCTriFile.hh" :  "" ""
	copy ..\.\3D\MeshIO\FormatCTriFile.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3DIO - Win32 Debug"

# Begin Custom Build - Install Header FormatCTriFile.hh

"C:\Build\inc\Ravl\3D\FormatCTriFile.hh" :  "" ""
	copy ..\.\3D\MeshIO\FormatCTriFile.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\TriFileIO.hh

!IF  "$(CFG)" == "Ravl3DIO - Win32 Release"

# Begin Custom Build - Install Header TriFileIO.hh

"C:\Build\inc\Ravl\3D\TriFileIO.hh" :  "" ""
	copy ..\.\3D\MeshIO\TriFileIO.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3DIO - Win32 Debug"

# Begin Custom Build - Install Header TriFileIO.hh

"C:\Build\inc\Ravl\3D\TriFileIO.hh" :  "" ""
	copy ..\.\3D\MeshIO\TriFileIO.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\FormatTriFile.hh

!IF  "$(CFG)" == "Ravl3DIO - Win32 Release"

# Begin Custom Build - Install Header FormatTriFile.hh

"C:\Build\inc\Ravl\3D\FormatTriFile.hh" :  "" ""
	copy ..\.\3D\MeshIO\FormatTriFile.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3DIO - Win32 Debug"

# Begin Custom Build - Install Header FormatTriFile.hh

"C:\Build\inc\Ravl\3D\FormatTriFile.hh" :  "" ""
	copy ..\.\3D\MeshIO\FormatTriFile.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\MeshIOObj.hh

!IF  "$(CFG)" == "Ravl3DIO - Win32 Release"

# Begin Custom Build - Install Header MeshIOObj.hh

"C:\Build\inc\Ravl\3D\MeshIOObj.hh" :  "" ""
	copy ..\.\3D\MeshIO\MeshIOObj.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3DIO - Win32 Debug"

# Begin Custom Build - Install Header MeshIOObj.hh

"C:\Build\inc\Ravl\3D\MeshIOObj.hh" :  "" ""
	copy ..\.\3D\MeshIO\MeshIOObj.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\FormatMeshObj.hh

!IF  "$(CFG)" == "Ravl3DIO - Win32 Release"

# Begin Custom Build - Install Header FormatMeshObj.hh

"C:\Build\inc\Ravl\3D\FormatMeshObj.hh" :  "" ""
	copy ..\.\3D\MeshIO\FormatMeshObj.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3DIO - Win32 Debug"

# Begin Custom Build - Install Header FormatMeshObj.hh

"C:\Build\inc\Ravl\3D\FormatMeshObj.hh" :  "" ""
	copy ..\.\3D\MeshIO\FormatMeshObj.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\POVRayFileIO.hh

!IF  "$(CFG)" == "Ravl3DIO - Win32 Release"

# Begin Custom Build - Install Header POVRayFileIO.hh

"C:\Build\inc\Ravl\3D\POVRayFileIO.hh" :  "" ""
	copy ..\.\3D\MeshIO\POVRayFileIO.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3DIO - Win32 Debug"

# Begin Custom Build - Install Header POVRayFileIO.hh

"C:\Build\inc\Ravl\3D\POVRayFileIO.hh" :  "" ""
	copy ..\.\3D\MeshIO\POVRayFileIO.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\MeshIO\FormatPOVRayFile.hh

!IF  "$(CFG)" == "Ravl3DIO - Win32 Release"

# Begin Custom Build - Install Header FormatPOVRayFile.hh

"C:\Build\inc\Ravl\3D\FormatPOVRayFile.hh" :  "" ""
	copy ..\.\3D\MeshIO\FormatPOVRayFile.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3DIO - Win32 Debug"

# Begin Custom Build - Install Header FormatPOVRayFile.hh

"C:\Build\inc\Ravl\3D\FormatPOVRayFile.hh" :  "" ""
	copy ..\.\3D\MeshIO\FormatPOVRayFile.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
