// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/LinearAlgebra/General/Matrix.cc"

#include "Ravl/StdMath.hh"
#include "Ravl/Matrix.hh"

// General matrix functions.

namespace RavlN {

  //: Test if matrix only contains real values.
  // This will return false if either nan's (Not an number) 
  // or infinite values are found.
  
  bool MatrixC::IsReal() const {
    for(BufferAccess2dIterC<RealT> it(*this,Size2());it;it++)
      if(IsInf(*it) || IsNan(*it))
	return false;
    return true;
  }
  
#ifdef __sgi__
  // Help the compiler a bit...
  template istream &operator>> (istream&,SizeBufferAccess2dC<double>&);
  template ostream &operator<< (ostream&,const SizeBufferAccess2dC<double>&);

  template ostream &operator<<(ostream&,const SArray2dC<double>&);
  template istream &operator>>(istream&,SArray2dC<double>&);
#endif

}
