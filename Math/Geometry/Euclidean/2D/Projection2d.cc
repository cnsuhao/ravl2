// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! date="17/10/2002"
//! author="Charles Galambos"

#include "Ravl/Projection2d.hh"
#include "Ravl/BinStream.hh"

namespace RavlN {

  //: Read from a stream.
  
  istream &operator>>(istream &s,Projection2dC &proj) {
    s >> proj.Matrix() >> proj.Iz() >> proj.Oz();
    return s;
  }

  //: Write to a stream.
  
  ostream &operator<<(ostream &s,const Projection2dC &proj) {
    s << proj.Matrix() << ' ' << proj.Iz() << ' ' << proj.Oz();
    return s;
  }
  
  //: Read from a binary stream.
  
  BinIStreamC &operator>>(BinIStreamC &s,Projection2dC &proj) {
    s >> proj.Matrix() >> proj.Iz() >> proj.Oz();
    return s;
  }
  
  //: Write to a binary stream.
  
  BinOStreamC &operator<<(BinOStreamC &s,const Projection2dC &proj) {
    s << proj.Matrix() << proj.Iz() << proj.Oz();
    return s;    
  }
  
  
}
