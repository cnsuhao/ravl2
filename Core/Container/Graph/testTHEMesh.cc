// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore

#include "Ravl/THEMeshEdge.hh"
#include "Ravl/THEMeshFace.hh"
#include "Ravl/THEMeshFaceIter.hh"
#include "Ravl/THEMesh.hh"
#include "Ravl/THEMeshVertex.hh"
#include "Ravl/THEMeshVertexIter.hh"

using namespace RavlN;

int main(int nargs,char **argv) {
  
  THEMeshC<IntT,RealT,bool> test(true);
  
  THEMeshVertexC<IntT,RealT,bool> vert1 = test.InsertVertex(1);
  THEMeshVertexC<IntT,RealT,bool> vert2 = test.InsertVertex(2);
  
  return 0;
}
