// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_EDGE_HH
#define RAVL_EDGE_HH
////////////////////////////////////////////////////////////////////////
//! file="Ravl/Geometry/Boundary/Edge.hh"
//! lib=RavlMath
//! userlevel=Normal
//! author="Radek Marik"
//! date="26.10.1995"
//! docentry="Image.Image Processing.Edges"
//! rcsid="$Id$"

#include "Ravl/BVertex.hh"
#include "Ravl/CrackCode.hh"


namespace RavlN {

  //: Elementary boundary edge
  // The class EdgeC represent an elementary edge of discrete image.
  // Elementary edge is located between two pixels. Edge is represented
  // by its origin and its direction. This definition implies only 4
  // possible directions represented by Freeman code. Four elementary
  // edges around a pixel are oriented counter-clockwise according to
  // the center of the pixel. For example, the top edge has the direction
  // to the left and its origin is upper-right corner of the pixel.
  
  class EdgeC
    : public BVertexC, 
      public CrackCodeC
  {
  public:
    //:------------------------------------------------
    //: Constructors, copies, assigment, and destructor.

    EdgeC();
    //: Creates an edge
    // The value is undefined.
    
    EdgeC(const BVertexC & px,const CrackCodeC & cc)
      : BVertexC(px),
	CrackCodeC(cc) 
    {}
    // Create the edge with origin in the boundary vertex 'px' and with
    // direction 'cc'.
    
    EdgeC(const BVertexC & begin, const BVertexC & end);
    // Create the edge with origin in the boundary vertex 'begin' pointing 
    // towards the boudary vertex 'end'. The direction is automatically 
    // generated.
    
    EdgeC(const Index2dC &pxl, const CrackCodeC & cc);
    // Creates the edge which starts at one corner of the pixel 'pxl'
    // and has the direction 'cc'. The corner of the pixel is chosen
    // in such way that the elementary edge is an elementary edge of the pixel.

    //:------------------
    //: Logical operators.
    
    bool operator==(const EdgeC & edg) const
    { return (CrackCodeC::operator==(edg)) && (Index2dC::operator==(edg)); }
    //: Returns true if both edge are equivalent.

    bool operator!=(const EdgeC & edg) const
    { return (CrackCodeC::operator!=(edg)) || (Index2dC::operator!=(edg)); }
    //: Returns true if edges are different.
    
    //:-----------------------------------------
    //: Access to elements of an elementary edge.
    
    Index2dC RPixel() const;
    //: Returns the pixel on the right side of the edge.

    Index2dC LPixel() const;
    //: Returns the pixel on the left side of the edge.
    
    const BVertexC & Begin() const
    { return *this; }
    //: Returns the boundary vertex from which the elementary edge starts from.
    
    BVertexC End() const
    { return CrackStep(*this,crackCode); }
    //: Returns the boundary vertex to which the elementary edge points to.
    
    const EdgeC & Reverse() { 
      BVertex() = CrackStep((Index2dC &) BVertex(),Code()); 
      TurnBack();
      return *this;
    }
    //: Reverse the direction of this edge.
  };
  
  ostream & operator<<(ostream & s, const EdgeC & e);
  //: Writes the elementary edge 'e' into the output stream 's'.
  
}
#endif
