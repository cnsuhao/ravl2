// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImageProc

#include "Ravl/Image/Edgel.hh"
#include <iostream.h>

namespace RavlImageN {
  
  ostream &operator<<(ostream &s,const EdgelC &edgel) {
    s << edgel.At() << ' ' << edgel.Direction() << ' ' << edgel.Magnitude();
    return s;
  }
  //: Write to a stream.
  
  istream &operator>>(istream &s,EdgelC &edgel) {
    s >> edgel.At() >> edgel.Direction() >> edgel.Magnitude();
    return s;
  }
  //: Read from a stream.

}
