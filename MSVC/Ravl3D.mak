


#--------------------------
# Compiler and flags etc
#--------------------------
CC = cl.exe

LD = lib.exe

INCLUDES =  /I "include\Win32" /I "include" /I "c:/Program Files/Microsoft Visual Studio 8/VC/ATLMFC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/include" /I "c:/Program Files/Microsoft Visual Studio 8/SDK/v2.0/include" 

DEFINES = /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2=1" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_SCL_SECURE=0" /D "_UNICODE" /D "UNICODE"


OPTFLAGS = /nologo /c /O2 /Ob1 /EHsc /MD /TP

DEBUGFLAGS = /nologo /c /Ob1 /EHsc /MD /TP

#-----------------------------------------------------------------------------
# OK lets define some of our output directories and define script to make them
#-----------------------------------------------------------------------------
DEBUGOBJDIR = C:\Build/win32/debug/obj/Ravl3D
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/Ravl3D
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/Vertex.obj $(OPTOBJDIR)/Tri.obj $(OPTOBJDIR)/TriMesh.obj $(OPTOBJDIR)/TriMeshBinIO.obj $(OPTOBJDIR)/TexTriMesh.obj $(OPTOBJDIR)/TexTriMeshBinIO.obj $(OPTOBJDIR)/HEMeshVertex.obj $(OPTOBJDIR)/HEMeshEdge.obj $(OPTOBJDIR)/HEMeshFace.obj $(OPTOBJDIR)/HEMesh.obj $(OPTOBJDIR)/TriMesh2HEMesh.obj $(OPTOBJDIR)/HEMeshFaceIter.obj $(OPTOBJDIR)/VertexColourByteRGB.obj $(OPTOBJDIR)/MeshShapes.obj $(OPTOBJDIR)/VoxelSet.obj $(OPTOBJDIR)/PointSet.obj $(OPTOBJDIR)/SurfacePoint3dArray.obj
	@echo -- making $(OPTLIBDIR)/Ravl3D.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/Ravl3D.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/Vertex.obj $(DEBUGOBJDIR)/Tri.obj $(DEBUGOBJDIR)/TriMesh.obj $(DEBUGOBJDIR)/TriMeshBinIO.obj $(DEBUGOBJDIR)/TexTriMesh.obj $(DEBUGOBJDIR)/TexTriMeshBinIO.obj $(DEBUGOBJDIR)/HEMeshVertex.obj $(DEBUGOBJDIR)/HEMeshEdge.obj $(DEBUGOBJDIR)/HEMeshFace.obj $(DEBUGOBJDIR)/HEMesh.obj $(DEBUGOBJDIR)/TriMesh2HEMesh.obj $(DEBUGOBJDIR)/HEMeshFaceIter.obj $(DEBUGOBJDIR)/VertexColourByteRGB.obj $(DEBUGOBJDIR)/MeshShapes.obj $(DEBUGOBJDIR)/VoxelSet.obj $(DEBUGOBJDIR)/PointSet.obj $(DEBUGOBJDIR)/SurfacePoint3dArray.obj 
	@echo -- making $(DEBUGLIBDIR)/Ravl3D.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/Ravl3D.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for Ravl3D
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/Vertex.obj: .././3D/Mesh/Vertex.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Vertex.obj .././3D/Mesh/Vertex.cc

$(DEBUGOBJDIR)/Vertex.obj: .././3D/Mesh/Vertex.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Vertex.obj .././3D/Mesh/Vertex.cc

$(OPTOBJDIR)/Tri.obj: .././3D/Mesh/Tri.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Tri.obj .././3D/Mesh/Tri.cc

$(DEBUGOBJDIR)/Tri.obj: .././3D/Mesh/Tri.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Tri.obj .././3D/Mesh/Tri.cc

$(OPTOBJDIR)/TriMesh.obj: .././3D/Mesh/TriMesh.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TriMesh.obj .././3D/Mesh/TriMesh.cc

$(DEBUGOBJDIR)/TriMesh.obj: .././3D/Mesh/TriMesh.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TriMesh.obj .././3D/Mesh/TriMesh.cc

$(OPTOBJDIR)/TriMeshBinIO.obj: .././3D/Mesh/TriMeshBinIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TriMeshBinIO.obj .././3D/Mesh/TriMeshBinIO.cc

$(DEBUGOBJDIR)/TriMeshBinIO.obj: .././3D/Mesh/TriMeshBinIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TriMeshBinIO.obj .././3D/Mesh/TriMeshBinIO.cc

$(OPTOBJDIR)/TexTriMesh.obj: .././3D/Mesh/TexTriMesh.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TexTriMesh.obj .././3D/Mesh/TexTriMesh.cc

$(DEBUGOBJDIR)/TexTriMesh.obj: .././3D/Mesh/TexTriMesh.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TexTriMesh.obj .././3D/Mesh/TexTriMesh.cc

$(OPTOBJDIR)/TexTriMeshBinIO.obj: .././3D/Mesh/TexTriMeshBinIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TexTriMeshBinIO.obj .././3D/Mesh/TexTriMeshBinIO.cc

$(DEBUGOBJDIR)/TexTriMeshBinIO.obj: .././3D/Mesh/TexTriMeshBinIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TexTriMeshBinIO.obj .././3D/Mesh/TexTriMeshBinIO.cc

$(OPTOBJDIR)/HEMeshVertex.obj: .././3D/Mesh/HEMeshVertex.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/HEMeshVertex.obj .././3D/Mesh/HEMeshVertex.cc

$(DEBUGOBJDIR)/HEMeshVertex.obj: .././3D/Mesh/HEMeshVertex.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/HEMeshVertex.obj .././3D/Mesh/HEMeshVertex.cc

$(OPTOBJDIR)/HEMeshEdge.obj: .././3D/Mesh/HEMeshEdge.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/HEMeshEdge.obj .././3D/Mesh/HEMeshEdge.cc

$(DEBUGOBJDIR)/HEMeshEdge.obj: .././3D/Mesh/HEMeshEdge.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/HEMeshEdge.obj .././3D/Mesh/HEMeshEdge.cc

$(OPTOBJDIR)/HEMeshFace.obj: .././3D/Mesh/HEMeshFace.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/HEMeshFace.obj .././3D/Mesh/HEMeshFace.cc

$(DEBUGOBJDIR)/HEMeshFace.obj: .././3D/Mesh/HEMeshFace.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/HEMeshFace.obj .././3D/Mesh/HEMeshFace.cc

$(OPTOBJDIR)/HEMesh.obj: .././3D/Mesh/HEMesh.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/HEMesh.obj .././3D/Mesh/HEMesh.cc

$(DEBUGOBJDIR)/HEMesh.obj: .././3D/Mesh/HEMesh.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/HEMesh.obj .././3D/Mesh/HEMesh.cc

$(OPTOBJDIR)/TriMesh2HEMesh.obj: .././3D/Mesh/TriMesh2HEMesh.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TriMesh2HEMesh.obj .././3D/Mesh/TriMesh2HEMesh.cc

$(DEBUGOBJDIR)/TriMesh2HEMesh.obj: .././3D/Mesh/TriMesh2HEMesh.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TriMesh2HEMesh.obj .././3D/Mesh/TriMesh2HEMesh.cc

$(OPTOBJDIR)/HEMeshFaceIter.obj: .././3D/Mesh/HEMeshFaceIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/HEMeshFaceIter.obj .././3D/Mesh/HEMeshFaceIter.cc

$(DEBUGOBJDIR)/HEMeshFaceIter.obj: .././3D/Mesh/HEMeshFaceIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/HEMeshFaceIter.obj .././3D/Mesh/HEMeshFaceIter.cc

$(OPTOBJDIR)/VertexColourByteRGB.obj: .././3D/Mesh/VertexColourByteRGB.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/VertexColourByteRGB.obj .././3D/Mesh/VertexColourByteRGB.cc

$(DEBUGOBJDIR)/VertexColourByteRGB.obj: .././3D/Mesh/VertexColourByteRGB.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/VertexColourByteRGB.obj .././3D/Mesh/VertexColourByteRGB.cc

$(OPTOBJDIR)/MeshShapes.obj: .././3D/Mesh/MeshShapes.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MeshShapes.obj .././3D/Mesh/MeshShapes.cc

$(DEBUGOBJDIR)/MeshShapes.obj: .././3D/Mesh/MeshShapes.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MeshShapes.obj .././3D/Mesh/MeshShapes.cc

$(OPTOBJDIR)/VoxelSet.obj: .././3D/Carve3D/VoxelSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/VoxelSet.obj .././3D/Carve3D/VoxelSet.cc

$(DEBUGOBJDIR)/VoxelSet.obj: .././3D/Carve3D/VoxelSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/VoxelSet.obj .././3D/Carve3D/VoxelSet.cc

$(OPTOBJDIR)/PointSet.obj: .././3D/Carve3D/PointSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PointSet.obj .././3D/Carve3D/PointSet.cc

$(DEBUGOBJDIR)/PointSet.obj: .././3D/Carve3D/PointSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PointSet.obj .././3D/Carve3D/PointSet.cc

$(OPTOBJDIR)/SurfacePoint3dArray.obj: .././3D/Carve3D/SurfacePoint3dArray.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SurfacePoint3dArray.obj .././3D/Carve3D/SurfacePoint3dArray.cc

$(DEBUGOBJDIR)/SurfacePoint3dArray.obj: .././3D/Carve3D/SurfacePoint3dArray.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SurfacePoint3dArray.obj .././3D/Carve3D/SurfacePoint3dArray.cc


