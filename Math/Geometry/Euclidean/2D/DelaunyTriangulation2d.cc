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
#include "Ravl/LinePP2d.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {

  static bool testLegal(const Point2dC &pi,const Point2dC &pj,const Point2dC &pk,const Point2dC &pr) {
    Circle2dC cir;
    ONDEBUG(cerr << "testLegal(), Fit. i=" << pi << " j=" << pj << " k=" << pk << " r=" << pr);
    if(!cir.Fit(pi,pj,pk)) {
      ONDEBUG(cerr << " Fit failed. \n");
      return true;
    }
    ONDEBUG(cerr << " IsInside=" << cir.IsInside(pr) << " \n");
    return cir.IsInside(pr);
  }
  
  static void LegaliseEdge(HEMesh2dC &mesh,THEMeshEdgeC<Point2dC> edge,const HSetC<THEMeshVertexC<Point2dC> > &special) {
    ONDEBUG(cerr << "LegaliseEdge(), Called. Edge=" << edge.Hash() << " \n");
    
    if(!edge.HasPair())
      return ; // Must be legal, nothing to change it with!
    
    THEMeshVertexC<Point2dC> pi = edge.Prev().Vertex();
    RavlAssert(pi.IsValid());
    bool spi = special[pi];
    
    THEMeshVertexC<Point2dC> pj = edge.Vertex();
    RavlAssert(pj.IsValid());
    bool spj = special[pj];
    
    if(spi && spj) return ;
    
    THEMeshVertexC<Point2dC> pr = edge.Next().Vertex(); // Find point being inserted.
    RavlAssert(pr.IsValid());
    bool spr = special[pr];
    
    THEMeshVertexC<Point2dC> pk = edge.Pair().Next().Vertex();
    RavlAssert(pk.IsValid());
    bool spk = special[pk];
    
    int count = (int) spr + (int) spk + (int) spi + (int) spj;
    ONDEBUG(cerr << "LegaliseEdge(), Count=" << count << " \n");
    
    switch(count)
      {
      case 0:
	if(testLegal(pi.Data(),pj.Data(),pk.Data(),pr.Data()))
	  return ; // Edge is legal, we're done.
	break;
      case 1:
	if(!spi && !spj) return ;
	break;
      case 2: {
	THEMeshVertexC<Point2dC> a,b;
	if(spi) a = pi;
	else a = pj;
	if(spr) b = pr;
	else  b = pk;
	cerr << "a=" << a.Hash() << " b=" << b.Hash() << "\n";
	RavlAssert(!(a == b));
	if(a > b) return ;
      } break;
      default: // Should never happen.
	RavlAssert(0);
      }
    
    // Twist edge in the face.
    mesh.TwistEdge(edge,edge.Next(),edge.Pair().Next());
    RavlAssert(mesh.CheckMesh(true));
    
    // Check resulting triangles are ok.
    LegaliseEdge(mesh,edge.Next(),special);
    LegaliseEdge(mesh,edge.Pair().Prev(),special);
  }
  
  //: Find face containing point 'pnt'.
  // Returns an invalid handle if none found.
  
  static THEMeshFaceC<Point2dC> FindFace(HEMesh2dC &mesh,HEMeshBaseEdgeC &me,const Point2dC &pnt) {
    ONDEBUG(cerr << "FindFace(), Point= " << pnt << "\n");
    for(THEMeshFaceIterC<Point2dC> it(mesh.Faces());it;it++) {
      RavlAssert((*it).IsValid());
      THEMeshFaceEdgeIterC<Point2dC> eit(*it);
      if(!eit) continue; // Faces has no edges!
      Point2dC last = eit->Vertex().Data();
      Point2dC first = last;
      bool found = true;
      for(eit++;eit;eit++) {
	Point2dC pnt = eit->Vertex().Data();
	if(LinePP2dC(last,pnt).IsPointToLeft(pnt)) {
	  found = false;
	  break;
	}
	last = pnt;
      }
      if(found && !LinePP2dC(last,first).IsPointToLeft(pnt)) {
	// Check for point on edge ?
	
	return *it; // Found it !
      }
      // Keep trying....
    }
    return THEMeshFaceC<Point2dC>();
  }

  
  //: Create a delauny triangulation of the given set of points.
  
  HEMesh2dC DelaunyTriangulation(const SArray1dC<Point2dC> &points) {
    HEMesh2dC ret(true);
    ONDEBUG(cerr << "DelaunyTriangulation(), Called. \n");
    
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
    THEMeshFaceC<Point2dC> firstFace =ret.InsertFace(tempFace,edgeTab); // Insert initial face.
    
    SArray1dC<HEMeshBaseVertexC> vertices(points.Size());
    // Start inserting points,
    
    for(SArray1dIter2C<Point2dC,HEMeshBaseVertexC> it(points,vertices);it;it++) {
      // Insert new vertex.
      THEMeshVertexC<Point2dC> vertex = ret.InsertVertex(it.Data1());
      it.Data2() = vertex;
      HEMeshBaseEdgeC me;
      THEMeshFaceC<Point2dC> face = FindFace(ret,me,it.Data1());
      if(!face.IsValid())
	face = firstFace;
      if(!me.IsValid()) { // Insert vertex in face.
	RavlAssert(face.Sides() == 3);
	THEMeshFaceEdgeIterC<Point2dC> eit(face);
	THEMeshEdgeC<Point2dC> e1 = *eit; eit++;
	THEMeshEdgeC<Point2dC> e2 = *eit; eit++;
	THEMeshEdgeC<Point2dC> e3 = *eit; eit++;
	
	ret.InsertVertexInFace(vertex,face);
	RavlAssert(ret.CheckMesh(true));
	RavlAssert(e1.Next().Vertex() == it.Data2());
	RavlAssert(e2.Next().Vertex() == it.Data2());
	RavlAssert(e3.Next().Vertex() == it.Data2());
	LegaliseEdge(ret,e1,init);
	LegaliseEdge(ret,e2,init);
	LegaliseEdge(ret,e3,init);
      } else { // Insert vertex on edge.
	ret.InsertVertexInEdgeTri(vertex,me);
	THEMeshVertexEdgeIterC<Point2dC> it(vertex);
	RavlAssert(it);
	THEMeshEdgeC<Point2dC> e1 = (*it).Prev(); it++;
	RavlAssert(it);
	THEMeshEdgeC<Point2dC> e2 = (*it).Prev(); it++;
	RavlAssert(it);
	THEMeshEdgeC<Point2dC> e3 = (*it).Prev(); it++;
	RavlAssert(it);
	THEMeshEdgeC<Point2dC> e4 = (*it).Prev(); 
	
	LegaliseEdge(ret,e1,init);
	LegaliseEdge(ret,e2,init);
	LegaliseEdge(ret,e3,init);
	LegaliseEdge(ret,e4,init);
      }
    }
#if 0
    for(i = 0;i < 3;i++)
      ret.DeleteVertex(tempFace[i]);
#endif
    return ret;
  }

  //: Test if mesh is a delauny triangulation. 
  
  bool IsDelaunyTriangulation(const HEMesh2dC &mesh) {
    ONDEBUG(cerr << "IsDelaunyTriangulation(), Called. \n");
    for(THEMeshFaceIterC<Point2dC> fit(mesh.Faces());fit;fit++) {
      for(THEMeshFaceEdgeIterC<Point2dC> eit(*fit);eit;eit++) {
	if(!eit.Data().HasPair()) // On the edge of the mesh ?
	  continue;
	THEMeshEdgeC<Point2dC> edge = eit.Data();
	if(edge.Vertex() > edge.Next().Vertex()) { // Only have to check one edge from each pair.
	  THEMeshVertexC<Point2dC> pi = edge.Prev().Vertex();
	  RavlAssert(pi.IsValid());
	  THEMeshVertexC<Point2dC> pj = edge.Vertex();
	  RavlAssert(pj.IsValid());
	  THEMeshVertexC<Point2dC> pr = edge.Next().Vertex(); // Find point being inserted.
	  RavlAssert(pr.IsValid());
	  THEMeshVertexC<Point2dC> pk = edge.Pair().Next().Vertex();
	  RavlAssert(pk.IsValid());
	  if(!testLegal(pi.Data(),pj.Data(),pk.Data(),pr.Data()))
	    return false;
	}
      }
    }
    return true;
  }

  
}
