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
int testTwistEdge();
int testSplitFace();
int testInsertVertexInEdge();
int testInsertVertexInEdgeTri();

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
  if((ln = testTwistEdge()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
 if((ln = testSplitFace()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testInsertVertexInEdge()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  } 
  if((ln = testInsertVertexInEdgeTri()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  } 
  cerr << "Test passed. \n";
  return 0;
}

int testInsertVertexOnFace() {
  cerr << "testInsertVertexOnFace(). \n";
  HEMeshBaseC mesh(true);
  SArray1dC<HEMeshBaseVertexC> tempFace(3);
  tempFace[0] = mesh.InsertVertex();
  tempFace[1] = mesh.InsertVertex();
  tempFace[2] = mesh.InsertVertex();
  
  HashC<Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC> , HEMeshBaseEdgeC> edgeTab;
  HEMeshBaseFaceC face = mesh.InsertFace(tempFace,edgeTab); // Insert initial face.
  if(!mesh.CheckMesh(true)) return __LINE__;
  if(!face.IsValid()) return __LINE__;
  
  HEMeshBaseVertexC vert = mesh.InsertVertex();
  if(!vert.IsValid()) return __LINE__;
  if(!mesh.InsertVertexInFace(vert,face)) return __LINE__;
  if(!mesh.CheckMesh(true)) return __LINE__;
  return 0;
}

int testTwistEdge() {
  cerr << "testTwistEdge(). \n";
  HEMeshBaseC mesh(true);
  SArray1dC<HEMeshBaseVertexC> tempFace1(3);
  tempFace1[0] = mesh.InsertVertex();
  tempFace1[1] = mesh.InsertVertex();
  tempFace1[2] = mesh.InsertVertex();
  
  HashC<Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC> , HEMeshBaseEdgeC> edgeTab;
  
  mesh.InsertFace(tempFace1,edgeTab); // Insert initial face.
  
  SArray1dC<HEMeshBaseVertexC> tempFace2(3);
  tempFace2[0] = mesh.InsertVertex();
  tempFace2[1] = tempFace1[2];
  tempFace2[2] = tempFace1[1];
  
  mesh.InsertFace(tempFace2,edgeTab); // Insert initial face.
  
  if(!mesh.CheckMesh(true)) return __LINE__;
  
  HEMeshBaseEdgeC edge = edgeTab[Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC>(tempFace1[1],tempFace1[2])];
  if(!edge.IsValid()) return __LINE__;
  
  HEMeshBaseEdgeC efrom = edgeTab[Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC>(tempFace1[2],tempFace1[0])];
  if(!efrom.IsValid()) return __LINE__;
  
  HEMeshBaseEdgeC eto = edgeTab[Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC>(tempFace2[2],tempFace2[0])];
  if(!eto.IsValid()) return __LINE__;
  
  mesh.TwistEdge(edge,efrom,eto);
  
  if(!mesh.CheckMesh(true)) return __LINE__;
  
  return 0;
}

int testSplitFace() {
  cout << "testSplitFace(), Called. \n";
  HEMeshBaseC mesh(true);
  SArray1dC<HEMeshBaseVertexC> tempFace(4);
  tempFace[0] = mesh.InsertVertex();
  tempFace[1] = mesh.InsertVertex();
  tempFace[2] = mesh.InsertVertex();
  tempFace[3] = mesh.InsertVertex();
  
  HashC<Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC> , HEMeshBaseEdgeC> edgeTab;
  HEMeshBaseFaceC face = mesh.InsertFace(tempFace,edgeTab); // Insert initial face.
  
  if(!mesh.CheckMesh(true)) return __LINE__;
  
  HEMeshBaseEdgeC e1 = face.FindEdge(tempFace[0]);
  HEMeshBaseEdgeC e2 = face.FindEdge(tempFace[2]);
  
  HEMeshBaseEdgeC ne = mesh.SplitFace(e1,e2);
  if(!ne.IsValid()) return __LINE__;
  if(!mesh.CheckMesh(true)) return __LINE__;
  if(!mesh.OpenEdge(ne)) return __LINE__;
  if(!mesh.CheckMesh(true)) return __LINE__;
  return 0;
}

int testInsertVertexInEdge() {
  cout << "testInsertVertexInEdge(), Called. \n";
  
  HEMeshBaseC mesh(true);
  SArray1dC<HEMeshBaseVertexC> tempFace(3);
  tempFace[0] = mesh.InsertVertex();
  tempFace[1] = mesh.InsertVertex();
  tempFace[2] = mesh.InsertVertex();
  
  HashC<Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC> , HEMeshBaseEdgeC> edgeTab;
  HEMeshBaseFaceC face = mesh.InsertFace(tempFace,edgeTab); // Insert initial face.
  if(!mesh.CheckMesh(true)) return __LINE__;

  HEMeshBaseEdgeC e1 = face.FindEdge(tempFace[1]);
  HEMeshBaseVertexC newVert = mesh.InsertVertex();
  mesh.InsertVertexInEdge(newVert,e1);
  
  if(!mesh.CheckMesh(true)) return __LINE__;
  
  return 0;
}

int testInsertVertexInEdgeTri() {
  cout << "testInsertVertexInEdgeTri(), Called. \n";
  
  HEMeshBaseC mesh(true);
  SArray1dC<HEMeshBaseVertexC> tempFace(3);
  tempFace[0] = mesh.InsertVertex();
  tempFace[1] = mesh.InsertVertex();
  tempFace[2] = mesh.InsertVertex();
  
  HashC<Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC> , HEMeshBaseEdgeC> edgeTab;
  HEMeshBaseFaceC face = mesh.InsertFace(tempFace,edgeTab); // Insert initial face.
  if(!mesh.CheckMesh(true)) return __LINE__;

  HEMeshBaseEdgeC e1 = face.FindEdge(tempFace[1]);
  HEMeshBaseVertexC newVert = mesh.InsertVertex();
  mesh.InsertVertexInEdgeTri(newVert,e1);
  
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
