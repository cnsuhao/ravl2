// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_EDGEL_HEADER
#define RAVLIMAGE_EDGEL_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Images.Edges"
//! author="Charles Galambos"
//! date="23/09/1999"
//! lib=RavlImageProc
//! file="Ravl/Image/Processing/Edges/Edgel.hh"

#include "Ravl/Index2d.hh"

namespace RavlImageN {
  using namespace RavlN;
  
  //! userlevel=Normal
  //: Edge Location, Direction and Magniture information.
  
  class EdgelC 
  {
  public:
    EdgelC(Index2dC loc,RealT dir,RealT mag)
      : at(loc),
	direction(dir),
	magnitude(mag)
    {}
    //: Constructor.
    
    EdgelC()
    {}
    //: Default constructor.
    // The contents of the edgel are left undefined.
    
    Index2dC &At()
    { return at; }
    //: Location of edge.
    
    RealT &Direction()
    { return direction; }
    //: Direction direction in radians
    
    RealT &Magnitude()
    { return magnitude; }
    //: Magnitude
    
    const Index2dC &At() const
    { return at; }
    //: Location of edge.
    
    RealT Direction() const
    { return direction; }
    //: Direction in Radians
    
    RealT Magnitude() const
    { return magnitude; }
    //: Magnitude
    
  protected:
    Index2dC at;
    RealT direction;
    RealT magnitude;
  };

  //! userlevel=Normal
  
  ostream &operator<<(ostream &s,const EdgelC &edgel);
  //: Write to a stream.
  
  istream &operator>>(istream &s,EdgelC &edgel);
  //: Read from a stream.
  
    
}
#endif
