// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
// $Id$
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Base/Index2d.cc"

#include "Ravl/Index2d.hh"
//#include "Ravl/StdMath.hh" // for Sqrt.
#include "Ravl/Assert.hh"
#include "Ravl/IndexRange2d.hh"
#include <iostream.h>
#include <math.h>

namespace RavlN {
  Index2dC relNeighPixel[9]= {Index2dC( 0,  1),
			      Index2dC( 1,  1),
			      Index2dC( 1,  0),
			      Index2dC( 1, -1),
			      Index2dC( 0, -1),
			      Index2dC(-1, -1),
			      Index2dC(-1,  0),
			      Index2dC(-1,  1), 
			      Index2dC( 0,  0)
  };
  
  IndexC Neighbours[3][3] = {{ IndexC(5), IndexC(6), IndexC(7)},
			     { IndexC(4), IndexC(8), IndexC(0)},
			     { IndexC(3), IndexC(2), IndexC(1)}};

  
  bool
  Index2dC::IsInside(const IndexRange2dC & range) const {
    return range.RowRange().Contains(Row()) && range.ColRange().Contains(Col());
  }
  
  
#if 0
  Index2dC &
  Index2dC::Step(const DirectionRLUDC & dir) {
    switch (dir.Code())
      {
      case TO_DOWN : Row()++; break;
      case TO_RIGHT: Col()++; break;
      case TO_UP   : Row()--; break;
      case TO_LEFT : Col()--; break;
      case TO_NODIR: break;
      };
    return *this;
  }
#endif
  
  IndexC
  Index2dC::NeighbourOrder() const {
    RavlAssertMsg(IsRelNeighbour8(),"pxl is not a neighbouring pixel");
    return Neighbours[Row().V()+1][Col().V()+1];
  }
  
  IndexC 
  Index2dC::NeighbourOrder(const Index2dC & pxl) const {
    return Index2dC(pxl - (*this)).NeighbourOrder();
  }  
    
}
