// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/Ellipse2d.hh"
#include "Ravl/BinStream.hh"

namespace RavlN {
  
  //: Write ellipse to text stream.
  
  ostream &operator<<(ostream &s,const Ellipse2dC &obj) {
    s << obj.Projection();
    return s;
  }
  
  //: Read ellipse from text stream.
  
  istream &operator>>(istream &s,Ellipse2dC &obj) {
    Affine2dC aff;
    s >> aff;
    obj = Ellipse2dC(aff);
    return s;
  }
  
  //: Write ellipse to binary stream.
  
  BinOStreamC &operator<<(BinOStreamC &s,const Ellipse2dC &obj) {
    s << obj.Projection();
    return s;
  }
  
  //: Read ellipse from binary stream.
  
  BinIStreamC &operator>>(BinIStreamC &s,Ellipse2dC &obj) {
    Affine2dC aff;
    s >> aff;
    obj = Ellipse2dC(aff);
    return s;
  }

}
