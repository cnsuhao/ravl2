#ifndef RAVL_BVERTEX_HH
#define RAVL_BVERTEX_HH
/////////////////////////////////////////////////////////////////////////
//! file="Ravl/Geometry/Boundary/BVertex.hh"
//! lib=Mbnd
//! userlevel=Normal
//! author="Radek Marik"
//! date="26.06.1994"
//! docentry="Image.Image Processing.Edges"
//! rcsid="$Id$"

#include "Ravl/Index2d.hh"
#include "Ravl/Point2d.hh"

namespace RavlN {

  class Point2dC;

  //: Boundary vertex
  // The relationship between pixel coordinates and boundary
  // vertex is that the boundary vertex [i,j] is the up-left corner
  // of the pixel (i,j). The figure contains the orientation of edges too.
  //
  //<pre>
  //        [i,j] <------------ [i,j+1]
  //        |                    /^\       
  //        |      (i,j)          |       
  //        V                     |       
  //       [i+1,j] ---------> [i+1, j+1]
  //</pre>
  
  class BVertexC
    : public Index2dC
  {
  public:
    BVertexC()
    {}
    //: Default constructor.
    // The value of the vertex is undefined.
    
    BVertexC(IndexC row, IndexC col)
      : Index2dC(row,col)
    {}
    //: Create the boundary vertex from two coordinates.

    BVertexC(const Index2dC & px)
      : Index2dC(px)
    {}
    //: Create the upper-left vertex of the pixel 'px'.
    
    BVertexC(const Point2dC & point)
      : Index2dC(point)
    {}
    //: Transform the point coordinates into the vertex.
    
    inline const BVertexC & BVertex() const
    { return(*this); }
    //: Access to the constant object

    inline BVertexC & BVertex()
    { return(*this); }
    //: Access to the object

  };

}
#endif
