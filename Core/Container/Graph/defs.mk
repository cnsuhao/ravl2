# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 5567 2006-06-09 12:51:47Z craftit $"
#! file="Ravl/Core/Container/Graph/defs.mk"

PACKAGE=Ravl

HEADERS=GraphBase.hh Graph.hh GraphNode.hh GraphEdge.hh GraphAdj.hh \
 GraphBaseLinearIter.hh GraphLinearIter.hh GraphBestRoute.hh GraphConnIt.hh \
 GraphBConIt.hh \
 HEMeshBaseVertex.hh HEMeshBaseEdge.hh  HEMeshBaseFace.hh HEMeshBase.hh HEMeshBaseFaceIter.hh \
 HEMeshBaseVertexIter.hh \
 THEMeshVertex.hh THEMeshEdge.hh  THEMeshFace.hh THEMesh.hh THEMeshFaceIter.hh \
 THEMeshVertexIter.hh

SOURCES=GraphBase.cc Graph.cc GraphBaseLinearIter.cc  GraphBConIt.cc \
 HEMeshBaseVertex.cc HEMeshBaseEdge.cc HEMeshBaseFace.cc HEMeshBase.cc HEMeshBaseFaceIter.cc

PLIB=RavlCore

LIBDEPS=RavlGraph.def

TESTEXES= testGraph.cc testTHEMesh.cc

EXAMPLES=exGraph.cc

USESLIBS=RavlCore

EHT=Ravl.API.Core.Graphs.eht
