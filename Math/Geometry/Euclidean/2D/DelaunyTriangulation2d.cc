// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! author="Charles Galambos"
//! lib=RavlMath

#include "Ravl/DelaunyTriangulation2d.hh"
#include "Ravl/THEMeshFaceIter.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/Circle2d.hh"
#include "Ravl/HSet.hh"

namespace RavlN {

  static bool testLegal(const Point2dC &pi,const Point2dC &pj,const Point2dC &pk,const Point2dC &pr) {
    Circle2dC cir;
    if(!cir.Fit(pi,pj,pk))
      return false;
    return cir.IsInside(pr);
  }
  
  static void LegaliseEdge(HEMesh2dC &mesh,THEMeshEdgeC<Point2dC> &edge,const HSetC<THEMeshVertexC<Point2dC> > &special) {
    RavlAssert(edge.HasPair());
    
    THEMeshVertexC<Point2dC> pi = edge.Prev().Vertex();
    bool spi = special[pi];
    THEMeshVertexC<Point2dC> pj = edge.Vertex();
    bool spj = special[pj];
    if(spi && spj) return ;
    
    THEMeshVertexC<Point2dC> pr = edge.Next().Vertex(); // Find point being inserted.
    bool spr = special[pr];
    THEMeshVertexC<Point2dC> pk = edge.Pair().Next().Vertex();
    bool spk = special[pk];
    
    int count = (int) spr + (int) spk + (int) spi + (int) spj;
    switch(count)
      {
      case 0:
	if(testLegal(pi.Data(),pj.Data(),pk.Data(),pr.Data()))
	  return ; // Edge is legal, we're done.
	break;
      case 1:
	if(!spi && !spj) return ;
	break;
      case 2:
	{
	  THEMeshVertexC<Point2dC> a,b;
	  if(spi) a = pi;
	  else a = pj;
	  if(spr) b = pr;
	  else  b = pk;
	  if(a > b) return ;
	}
      }
    
    THEMeshEdgeC<Point2dC> edge1 = edge.Pair().Next();
    THEMeshEdgeC<Point2dC> edge2 = edge.Pair().Prev();
    
    // Twist edge in the face.
    mesh.TwistEdge(edge,edge.Next(),edge.Pair().Next());
    
    // Check resulting triangles are ok.
    LegaliseEdge(mesh,edge1,special);
    LegaliseEdge(mesh,edge2,special);
  }
  
  
  //: Create a delauny triangulation of the given set of points.
  
  HEMesh2dC DelaunyTriangulation(const SArray1dC<Point2dC> &points) {
    HEMesh2dC ret(true);
    
    // Create initial face.
    
    SArray1dC<HEMeshBaseVertexC> tempFace(3);
    HSetC<THEMeshVertexC<Point2dC> > init;
    tempFace[0] = ret.InsertVertex(Point2dC(0,1000));
    tempFace[1] = ret.InsertVertex(Point2dC(1000,0));
    tempFace[2] = ret.InsertVertex(Point2dC(-1000,-1000));
    int i;
    for(i = 0;i < 3;i++)
      init += tempFace[i];
    
    HashC<Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC> , HEMeshBaseEdgeC> edgeTab;
    ret.InsertFace(tempFace,edgeTab); // Insert initial face.
    
    SArray1dC<HEMeshBaseVertexC> vertices(points.Size());
    // Start inserting points,
    
    for(SArray1dIter2C<Point2dC,HEMeshBaseVertexC> it(points,vertices);it;it++) {
      // Insert new vertex.
      it.Data2() = ret.InsertVertex(it.Data1());
      THEMeshFaceC<Point2dC> face = ret.FindFace(it.Data1());
      RavlAssert(face.IsValid()); // There always should be a face we're splitting up.
      RavlAssert(face.Sides() == 3);
      THEMeshFaceEdgeIterC<Point2dC> eit(face);
      THEMeshEdgeC<Point2dC> e1 = *eit; eit++;
      THEMeshEdgeC<Point2dC> e2 = *eit; eit++;
      THEMeshEdgeC<Point2dC> e3 = *eit; eit++;
      
      ret.InsertVertexInFace(it.Data2(),face);
      
      LegaliseEdge(ret,e1,init);
      LegaliseEdge(ret,e2,init);
      LegaliseEdge(ret,e3,init);
    }
    
    for(i = 0;i < 3;i++)
      ret.DeleteVertex(tempFace[i]);
    return ret;
  }

  //: Test if mesh is a delauny triangulation. 
  
  bool IsDelaunyTriangulation(const HEMesh2dC &mesh) {
    for(THEMeshFaceIterC<Point2dC> fit(mesh.Faces());fit;fit++) {
      for(THEMeshFaceEdgeIterC<Point2dC> eit(*fit);eit;eit++) {
	if(!eit.Data().HasPair()) // On the edge of the mesh ?
	  continue;
	THEMeshEdgeC<Point2dC> edge = eit.Data();
	if(edge.Vertex() > edge.Next().Vertex()) { // Only have to check one edge from each pair.
	  THEMeshVertexC<Point2dC> pi = edge.Prev().Vertex();
	  THEMeshVertexC<Point2dC> pj = edge.Vertex();
	  THEMeshVertexC<Point2dC> pr = edge.Next().Vertex(); // Find point being inserted.
	  THEMeshVertexC<Point2dC> pk = edge.Pair().Next().Vertex();
	  if(!testLegal(pi.Data(),pj.Data(),pk.Data(),pr.Data()))
	    return false;
	}
      }
    }
    return true;
  }

  
}
