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

int testTHEMeshBasic();
int testHEMeshBase();
int testInsertVertexOnFace();

int main(int nargs,char **argv) {
  int ln;
  if((ln = testHEMeshBase()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testTHEMeshBasic()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testInsertVertexOnFace()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}

int testInsertVertexOnFace() {
  HEMeshBaseC mesh(true);
  SArray1dC<HEMeshBaseVertexC> tempFace(3);
  tempFace[0] = mesh.InsertVertex();
  tempFace[1] = mesh.InsertVertex();
  tempFace[2] = mesh.InsertVertex();
  cerr << "Creating face. \n";
  
  HashC<Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC> , HEMeshBaseEdgeC> edgeTab;
  HEMeshBaseFaceC face = mesh.InsertFace(tempFace,edgeTab); // Insert initial face.
  if(!mesh.CheckMesh(true)) return __LINE__;
  if(!face.IsValid()) return __LINE__;
  
  cerr << "Inserting vertex. \n";
  HEMeshBaseVertexC vert = mesh.InsertVertex();
  if(!vert.IsValid()) return __LINE__;
  if(!mesh.InsertVertexInFace(vert,face)) return __LINE__;
  if(!mesh.CheckMesh(true)) return __LINE__;
  return 0;
}

int testHEMeshBase() {
  cout << "testHEMeshBase(), Called. \n";
  HEMeshBaseC mesh(true);
  
  return 0;
}

int testTHEMeshBasic() {
  cout << "testTHEMeshBasic(), Called. \n";
  THEMeshC<IntT,RealT,bool> test(true);
  
  SArray1dC<HEMeshBaseVertexC> arr(3);
  HashC<Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC> , HEMeshBaseEdgeC> edgeTab;
  THEMeshVertexC<IntT,RealT,bool> mv = test.InsertVertex(1);
  arr[0] = mv;
  arr[1] = test.InsertVertex(2);
  arr[2] = test.InsertVertex(3);
  test.InsertFace(true,arr,edgeTab);
  return 0;
}
