// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BOUNDARY_HEADER
#define RAVL_BOUNDARY_HEADER 1
/////////////////////////////////////////////////////////////////////////
//! file="Ravl/Math/Geometry/Euclidean/Boundary/Boundary.hh"
//! lib=RavlMath
//! userlevel=Normal
//! author="Radek Marik"
//! date="26/10/1992"
//! docentry="Ravl.Images.Boundaries;Ravl.Math.Geometry.2D.Boundary"
//! rcsid="$Id$"

#include "Ravl/Types.hh" 
#include "Ravl/Edge.hh"
#include "Ravl/DList.hh"
#include "Ravl/IndexRange2d.hh"

namespace RavlN {
  template<class KeyT, class DataT> class RCHashC;
  template<class DataT> class PairC;
  template<class DataT> class Array2dC;
  
  //! userlevel=Normal
  //: Crack code boundary
  // The class BoundaryC represents the 4-connected oriented boundary of a image
  // region.
  
  class BoundaryC
    : public DListC<EdgeC>
  {
  public:
    //:------------------------------------------------
    //: Constructors, copies, assignment, and destructor.
    
    BoundaryC(bool orient = true);
    //: Empty boundary with orientation 'orient'.
    // If orient is true, the object is on the left of the boundary.
    
    BoundaryC(const Array2dC<IntT> &emask,IntT inLabel);
    //: Create a boundary from the edges between 'inLabel' pixels an other values
    
    BoundaryC(const Array2dC<UIntT> &emask,IntT inLabel);
    //: Create a boundary from the edges between 'inLabel' pixels an other values
    
    BoundaryC(const DListC<EdgeC> & edgeList, bool orient);
    //: Create the boundary from the list of edges with a appropriate orientation. 
    // The 'edgeList' will be a part of boundary.  If orient is true, the object
    // is on the left of the boundary.
    
    BoundaryC(const DListC<DLIterC<EdgeC> > & edgeList, bool orient = true);
    //: Creates the boundary from the list of pointers to the elementary edges.
    // If orient is true, the object is on the left of the boundary.
    
    BoundaryC(const IndexRange2dC & rect,bool asHole = true);
    //: The boundary of the rectangle.
    // The boundary goes clockwise around the rectangle. If asHole is true, 
    // then the rectangle is 'outside' the region. otherwise its inside. 
    
    IntT Area() const;
    //: Get the area of the region which is determined by the 'boundary'.
    // Note: The area of the region can be negative, If it is a 'hole' in
    // a plane. This can be inverted with the BReverse() method.
    
    DListC<BoundaryC> Order(const EdgeC & firstEdge, bool orient = true);
    //: Order boundary from edge.
    // Note: There is a bug in this code which can cause an infinite loop
    // for some edge patterns. In particular where the two edges go through
    // the same vertex. <br>
    // Order the edgels of this boundary such that it can be traced 
    // continuously along the direction of the first edge. The orientation 
    // of the boundary is set according to 'orient'. If the boundary is open,
    // 'firstEdge' and 'orient' are ignored.
    
    DListC<BoundaryC> OrderEdges() const;
    //: Generate an order list of boundaries.
    
    bool Orient() const
    { return orientation; }
    //: Return the orientation of the boundary.
    // true means that an object is on the left side of edges
    // and false that is on the right.
    
    void Invert()
    { orientation = !orientation; }
    //: Invert the boundary.
    
    BoundaryC & BReverse();
    //: Reverse the order of the edges.
    
    BoundaryC Copy() const;
    //: Create a physical copy of the boundary.
    
    DListC<DLIterC<EdgeC> > ConvexHull() const;
    //: Compute the convex hull.
    // The convex hull is created from the original Jordan boundary using
    // Melkman's method.
    // Ref.: A V Melkman. On-line construction of the convex hull of a 
    //                    simple polyline. Information Processing Letters,
    //                    25(1):11-12, 1987.
    // Ref.: M Sonka, V Hlavac: Image Processing.    
    
    IndexRange2dC BoundingBox() const;
    //: Get the bounding box of the boundary in "boundary's" coordinates.
    
  private:
    bool orientation;  
    // Orientation of the boundary. true means that
    // an object is on the left side of edges.
    
    RCHashC<BVertexC, PairC<BVertexC> > CreateHashtable() const;
    // Returns the hash table for the boundary; all end points which are only
    // connected to one other point will have at least one invalid
    // neighbour (-1, -1).

    BoundaryC OrderContinuous(const RCHashC<BVertexC, PairC<BVertexC> > & hashtable, const EdgeC & firstEdge, bool orient) const;
    // Returns a continuous boundary; if the boundary is open, 'orient' will be 
    // ignored and 'firstEdge' must be one of the end points of the boundary.
    
    DListC<BVertexC> FindEndpoints(const RCHashC<BVertexC, PairC<BVertexC> > & hashtable) const;
    // Returns the endpoints of the boundary, i.e. if the boundary is closed,
    // the list will be empty.
  };
  
  inline ostream & operator<<(ostream & s, const BoundaryC & b)
  { s << (DListC<EdgeC> &) b; return s; }
  //: Write the boundary to output stream 's'.
  
  inline istream & operator<<(istream & s,BoundaryC & b)
  { s >> (DListC<EdgeC> &) b; return s;  }
  //: Read the boundary from input stream 's'.
  
  inline BinOStreamC & operator<<(BinOStreamC & s, const BoundaryC & b)
  { s << (DListC<EdgeC> &) b; return s;  }
  //: Write the boundary to output stream 's'.
  
  inline BinIStreamC & operator<<(BinIStreamC & s,BoundaryC & b)
  { s >> (DListC<EdgeC> &) b; return s;  }
  //: Read the boundary from input stream 's'.
  
  BoundaryC Line2Boundary(const BVertexC & startVertex, const BVertexC & endVertex);
  //: Creates a boundary which connects both boundary vertexes.
  
}
#endif


