// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BOUNDARY_HEADER
#define RAVL_BOUNDARY_HEADER 1
/////////////////////////////////////////////////////////////////////////
//! file="Ravl/Geometry/Boundary/Boundary.hh"
//! lib=RavlMath
//! userlevel=Normal
//! author="Radek Marik"
//! date="26/10/1992"
//! docentry="Image.Image Processing.Edges"
//! rcsid="$Id$"

#include "Ravl/Types.hh" 
#include "Ravl/Edge.hh"
#include "Ravl/DList.hh"
#include "Ravl/IndexRange2d.hh"

namespace RavlN {
  template<class KeyT, class DataT> class RCHashC;
  template<class DataT> class PairC;
  
  //! userlevel=Normal
  //: Crack code boundary
  // The class BoundaryC represents the 4-connected oriented boundary of a image
  // region.
  
  class BoundaryC
    : public DListC<EdgeC>
  {
  public:
    //:------------------------------------------------
    //: Constructors, copies, assigment, and destructor.
    
    BoundaryC(bool orient = true);
    //: Empty boundary with orientation 'orient'.
    
    BoundaryC(const DListC<EdgeC> & edgeList, bool orient);
    //: Create the boundary from the list of edges with a appropriate orientation. 
    // The 'edgelist' will be a part of boundary.

#if 0
    BoundaryC(const DListC<EdgePtrC> & edgeList, bool orient = true);
    //: Creates the boundary from the list of pointers to the elementary edges.
    // The orientation of the boundary is set according to 'orient'.
#endif
    
    BoundaryC(const IndexRange2dC & rect);
    //: The boundary of the rectangle as a hole
    
    SizeT Area() const;
    //: Get the area of the region which is determined by the 'boundary'.
    
    DListC<BoundaryC> Order(const EdgeC & firstEdge, bool orient = true);
    // Order the edgels of this boundary such that it can be traced 
    // continuously along the direction of the first edge. The orientation 
    // of the boundary is set according to 'orient'. If the boundary is open,
    // 'firstEdge' and 'orient' are ignored.
    
    bool Orient() const
    { return orientation; }
    //: Return the orientation of the boundary.
    
    BoundaryC & BReverse();
    //: Reverse the order of the edges.
    
    BoundaryC Copy() const;
    //: Create a physical copy of the boundary.
    
#if 0
    EdgeCPtrListC ConvexHull() const;
    //: Compute the convex hull.
    // The convex hull is created from the original Jordan boundary using
    // Melkman's method.
    // Ref.: A V Melkman. On-line construction of the convex hull of a 
    //                    simple polyline. Information Processing Letters,
    //                    25(1):11-12, 1987.
    // Ref.: M Sonka, V Hlavac: Image Processing.
    
    EdgeCPtrListC ConvexHullMM() const;
    // The convex hull is created from the original Jordan boundary using
    // Marik&Matas's method. 
#endif
    
    IndexRange2dC BoundingBox() const;
    //: Get the bounding box of the boundary in "boundary's" coordinates.
    
    void WriteCompressed(ostream &s) const;
    //: Save as ASCII characters in compressed format.
    
    void ReadCompressed(istream & s);
    // Read a boundary stored in compressed format. The current object
    // is deleted.
    
  private:
    bool orientation;  
    // Orientation of the boundary. true means that
    // an object is on the left side of edges.
    
    RCHashC<BVertexC, PairC<BVertexC> > CreateHashtable() const;
    // Returns the hashtable for the boundary; all end points which are only
    // connected to one other point will have at least one invalid
    // neighbour (-1, -1).

    BoundaryC OrderContinuous(const RCHashC<BVertexC, PairC<BVertexC> > & hashtable, const EdgeC & firstEdge, bool orient) const;
    // Returns a continous boundary; if the boundary is open, 'orient' will be 
    // ignored and 'firstEdge' must be one of the end points of the boundary.
    
    DListC<BVertexC> FindEndpoints(const RCHashC<BVertexC, PairC<BVertexC> > & hashtable) const;
    // Returns the endpoints of the boundary, i.e. if the boundary is closed,
    // the list will be empty.
  };
  
  ostream & operator<<(ostream & s, const BoundaryC & b);
  // Prints the whole boundary into the output stream 's'.

#if 0
  BoundaryC Line2Boundary(const BVertexC & startVertex, const BVertexC & endVertex);
  // Creates a boundary which connects both boundary vertexes.

  void SaveAsGF(ostream & s, const DListC<BoundaryC> & boundaries, LongIntT minArea);
  // Save all boundaries which inside area is bigger than 'minArea'
  // into the stream 's'.

  void SaveCompressed(ostream & s, const DListC<BoundaryC> & boundaries, 
		 LongIntT minArea);
  // Save all boundaries which inside area is bigger than 'minArea'
  // into the stream 's'.

#define FOREACH_C_EDGE(boundary, e) \
  for(EdgeCPtrC e(boundary); e.IsElm(); e.Next())

#define FOREACH_EDGE(boundary, e) \
  for(EdgePtrC e(boundary); e.IsElm(); e.Next())
#endif
}
#endif


