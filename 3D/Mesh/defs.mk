# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2002, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/3D/Mesh/defs.mk"

PACKAGE=Ravl/3D

HEADERS= Vertex.hh Tri.hh TriMesh.hh \
 HEMeshVertex.hh HEMeshEdge.hh HEMeshFace.hh HEMesh.hh

SOURCES= Vertex.cc Tri.cc TriMesh.cc TriMeshBinIO.cc \
 HEMeshVertex.cc HEMeshEdge.cc HEMeshFace.cc HEMesh.cc \
 TriMesh2HEMesh.cc

#TESTEXES=testHEMesh.cc

PLIB=Ravl3D

USESLIBS=RavlMath

EHT=Ravl.3D.Mesh.html

