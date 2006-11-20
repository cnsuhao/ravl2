# Microsoft Developer Studio Project File - Name="Ravl3D" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Ravl3D - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Ravl3D.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ravl3D.mak" CFG="Ravl3D - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Ravl3D - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Ravl3D - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Ravl3D - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\Ravl3D"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Ravl3D - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\Ravl3D"
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

# Name "Ravl3D - Win32 Release"
# Name "Ravl3D - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\3D\Mesh\Vertex.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\Tri.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\TriMesh.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\TriMeshBinIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\TexTriMesh.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\TexTriMeshBinIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\HEMeshVertex.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\HEMeshEdge.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\HEMeshFace.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\HEMesh.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\TriMesh2HEMesh.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\HEMeshFaceIter.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\VertexColourByteRGB.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\Carve3D\VoxelSet.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\Carve3D\PointSet.cc
# End Source File

# Begin Source File
SOURCE=..\.\3D\Carve3D\SurfacePoint3dArray.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\3D\Mesh\Vertex.hh

!IF  "$(CFG)" == "Ravl3D - Win32 Release"

# Begin Custom Build - Install Header Vertex.hh

"C:\Build\inc\Ravl\3D\Vertex.hh" :  "" ""
	copy ..\.\3D\Mesh\Vertex.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3D - Win32 Debug"

# Begin Custom Build - Install Header Vertex.hh

"C:\Build\inc\Ravl\3D\Vertex.hh" :  "" ""
	copy ..\.\3D\Mesh\Vertex.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\Tri.hh

!IF  "$(CFG)" == "Ravl3D - Win32 Release"

# Begin Custom Build - Install Header Tri.hh

"C:\Build\inc\Ravl\3D\Tri.hh" :  "" ""
	copy ..\.\3D\Mesh\Tri.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3D - Win32 Debug"

# Begin Custom Build - Install Header Tri.hh

"C:\Build\inc\Ravl\3D\Tri.hh" :  "" ""
	copy ..\.\3D\Mesh\Tri.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\TriMesh.hh

!IF  "$(CFG)" == "Ravl3D - Win32 Release"

# Begin Custom Build - Install Header TriMesh.hh

"C:\Build\inc\Ravl\3D\TriMesh.hh" :  "" ""
	copy ..\.\3D\Mesh\TriMesh.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3D - Win32 Debug"

# Begin Custom Build - Install Header TriMesh.hh

"C:\Build\inc\Ravl\3D\TriMesh.hh" :  "" ""
	copy ..\.\3D\Mesh\TriMesh.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\TexTriMesh.hh

!IF  "$(CFG)" == "Ravl3D - Win32 Release"

# Begin Custom Build - Install Header TexTriMesh.hh

"C:\Build\inc\Ravl\3D\TexTriMesh.hh" :  "" ""
	copy ..\.\3D\Mesh\TexTriMesh.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3D - Win32 Debug"

# Begin Custom Build - Install Header TexTriMesh.hh

"C:\Build\inc\Ravl\3D\TexTriMesh.hh" :  "" ""
	copy ..\.\3D\Mesh\TexTriMesh.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\HEMeshVertex.hh

!IF  "$(CFG)" == "Ravl3D - Win32 Release"

# Begin Custom Build - Install Header HEMeshVertex.hh

"C:\Build\inc\Ravl\3D\HEMeshVertex.hh" :  "" ""
	copy ..\.\3D\Mesh\HEMeshVertex.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3D - Win32 Debug"

# Begin Custom Build - Install Header HEMeshVertex.hh

"C:\Build\inc\Ravl\3D\HEMeshVertex.hh" :  "" ""
	copy ..\.\3D\Mesh\HEMeshVertex.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\HEMeshEdge.hh

!IF  "$(CFG)" == "Ravl3D - Win32 Release"

# Begin Custom Build - Install Header HEMeshEdge.hh

"C:\Build\inc\Ravl\3D\HEMeshEdge.hh" :  "" ""
	copy ..\.\3D\Mesh\HEMeshEdge.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3D - Win32 Debug"

# Begin Custom Build - Install Header HEMeshEdge.hh

"C:\Build\inc\Ravl\3D\HEMeshEdge.hh" :  "" ""
	copy ..\.\3D\Mesh\HEMeshEdge.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\HEMeshFace.hh

!IF  "$(CFG)" == "Ravl3D - Win32 Release"

# Begin Custom Build - Install Header HEMeshFace.hh

"C:\Build\inc\Ravl\3D\HEMeshFace.hh" :  "" ""
	copy ..\.\3D\Mesh\HEMeshFace.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3D - Win32 Debug"

# Begin Custom Build - Install Header HEMeshFace.hh

"C:\Build\inc\Ravl\3D\HEMeshFace.hh" :  "" ""
	copy ..\.\3D\Mesh\HEMeshFace.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\HEMesh.hh

!IF  "$(CFG)" == "Ravl3D - Win32 Release"

# Begin Custom Build - Install Header HEMesh.hh

"C:\Build\inc\Ravl\3D\HEMesh.hh" :  "" ""
	copy ..\.\3D\Mesh\HEMesh.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3D - Win32 Debug"

# Begin Custom Build - Install Header HEMesh.hh

"C:\Build\inc\Ravl\3D\HEMesh.hh" :  "" ""
	copy ..\.\3D\Mesh\HEMesh.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\HEMeshVertexIter.hh

!IF  "$(CFG)" == "Ravl3D - Win32 Release"

# Begin Custom Build - Install Header HEMeshVertexIter.hh

"C:\Build\inc\Ravl\3D\HEMeshVertexIter.hh" :  "" ""
	copy ..\.\3D\Mesh\HEMeshVertexIter.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3D - Win32 Debug"

# Begin Custom Build - Install Header HEMeshVertexIter.hh

"C:\Build\inc\Ravl\3D\HEMeshVertexIter.hh" :  "" ""
	copy ..\.\3D\Mesh\HEMeshVertexIter.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\HEMeshFaceIter.hh

!IF  "$(CFG)" == "Ravl3D - Win32 Release"

# Begin Custom Build - Install Header HEMeshFaceIter.hh

"C:\Build\inc\Ravl\3D\HEMeshFaceIter.hh" :  "" ""
	copy ..\.\3D\Mesh\HEMeshFaceIter.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3D - Win32 Debug"

# Begin Custom Build - Install Header HEMeshFaceIter.hh

"C:\Build\inc\Ravl\3D\HEMeshFaceIter.hh" :  "" ""
	copy ..\.\3D\Mesh\HEMeshFaceIter.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\Mesh\VertexColourByteRGB.hh

!IF  "$(CFG)" == "Ravl3D - Win32 Release"

# Begin Custom Build - Install Header VertexColourByteRGB.hh

"C:\Build\inc\Ravl\3D\VertexColourByteRGB.hh" :  "" ""
	copy ..\.\3D\Mesh\VertexColourByteRGB.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3D - Win32 Debug"

# Begin Custom Build - Install Header VertexColourByteRGB.hh

"C:\Build\inc\Ravl\3D\VertexColourByteRGB.hh" :  "" ""
	copy ..\.\3D\Mesh\VertexColourByteRGB.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\Carve3D\VoxelSet.hh

!IF  "$(CFG)" == "Ravl3D - Win32 Release"

# Begin Custom Build - Install Header VoxelSet.hh

"C:\Build\inc\Ravl\3D\VoxelSet.hh" :  "" ""
	copy ..\.\3D\Carve3D\VoxelSet.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3D - Win32 Debug"

# Begin Custom Build - Install Header VoxelSet.hh

"C:\Build\inc\Ravl\3D\VoxelSet.hh" :  "" ""
	copy ..\.\3D\Carve3D\VoxelSet.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\Carve3D\PointSet.hh

!IF  "$(CFG)" == "Ravl3D - Win32 Release"

# Begin Custom Build - Install Header PointSet.hh

"C:\Build\inc\Ravl\3D\PointSet.hh" :  "" ""
	copy ..\.\3D\Carve3D\PointSet.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3D - Win32 Debug"

# Begin Custom Build - Install Header PointSet.hh

"C:\Build\inc\Ravl\3D\PointSet.hh" :  "" ""
	copy ..\.\3D\Carve3D\PointSet.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\3D\Carve3D\SurfacePoint3dArray.hh

!IF  "$(CFG)" == "Ravl3D - Win32 Release"

# Begin Custom Build - Install Header SurfacePoint3dArray.hh

"C:\Build\inc\Ravl\3D\SurfacePoint3dArray.hh" :  "" ""
	copy ..\.\3D\Carve3D\SurfacePoint3dArray.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ELSEIF  "$(CFG)" == "Ravl3D - Win32 Debug"

# Begin Custom Build - Install Header SurfacePoint3dArray.hh

"C:\Build\inc\Ravl\3D\SurfacePoint3dArray.hh" :  "" ""
	copy ..\.\3D\Carve3D\SurfacePoint3dArray.hh C:\Build\inc\Ravl\3D

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
