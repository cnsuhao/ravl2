// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLBYTEIAVALUE_HEADER
#define RAVLBYTEIAVALUE_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/ByteIAValue.hh"
//! lib=RavlImage
//! userlevel=Default
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Images.Pixel Types"

#include "Ravl/Image/IAValue.hh"

namespace RavlN {
  
  //: Byte Intensity and Alpha value class.
  
  class ByteIAValueC
    : public IAValueC<ByteT>
  {
  public:
    ByteIAValueC()
      {}
    //: Default constructor.
    // creates an undefined IA pixel.

    ByteIAValueC(const IAValueC<ByteT> &oth)
      : IAValueC<ByteT>(oth)
      {}
    //: Default constructor.
    // creates an undefined IA pixel.
    
  };
  
}

#endif
