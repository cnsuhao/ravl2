// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLSQUAREITER_HEADER
#define RAVLSQUAREITER_HEADER 1
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Tools/Misc/SquareIter.hh"
//! lib=RavlMath
//! userlevel=Normal
//! author="Charles Galambos"
//! docentry="Ravl.Math.Sequences"
//! example=testSquareIterFill.cc
//! date="29/08/2000"

#include "Ravl/Types.hh"
#include "Ravl/Index2d.hh"
#include "Ravl/IndexRange2d.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Clockwise iterate through a square.
  // starting at the centre working outward.
  
  class SquareIterC {
  public:  
    inline SquareIterC(UIntT thesize,Index2dC thecentre = Index2dC(0,0))
      : centre(thecentre), 
      maxSize(thesize) 
      { First(); }
    //: Constructor.
    
    inline void First() { 
      state = 1;
      at = centre; 
      size = 1;
    }
    //: Goto first point on square.
    
    inline bool IsElm() const
      { return state != 0; }
    //: At valid position ?
    
    inline const Index2dC &Data() const
      { return at; }
    //: Get point.
    
    bool Next();
    //: Goto next point.
    
  private:
    IntT state;     // State we're in.
    IntT end;       // End of current side.
    Index2dC at;    // Current pixel.
    Index2dC centre; // Centre of square.
    UIntT size;    // Current size.
    UIntT maxSize; // Maximum size.
  };
  
}
#endif
