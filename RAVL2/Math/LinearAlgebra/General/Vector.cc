// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/LinearAlgebra/General/Vector.cc"

#include "Ravl/StdMath.hh"

#include "Ravl/Vector.hh"
#include "Ravl/CCMath.hh"

namespace RavlN {
  
  //: Test if vector only contains real values.
  // This will return false if either nan's (Not an number) 
  // or infinite values are found.
  
  bool VectorC::IsReal() const {
    for(BufferAccessIterC<RealT> it(*this);it;it++)
      if(IsInf(*it) || IsNan(*it))
	return false;
    return true;
  }

  //: Dump to cout in a human readable format.
  
  void VectorC::Dump() const {
    cout << Size();
    for(BufferAccessIterC<RealT> it(*this);it;it++)
      cout << ' ' << *it ;
  }
  
  //: Multiply vec by scale and add it to this one.

  const TVectorC<RealT> &VectorC::MulAdd(const TVectorC<float> &vec,float a) {
    for(BufferAccessIter2C<RealT,float> it(*this,vec);it;it++)
      it.Data1() += it.Data2() * a;
    return *this;
  }



#ifdef __sgi__
  // Help the compiler a bit...
  template ostream &operator<<(ostream&,const TVectorC<double>&);
  template istream &operator>>(istream&,SArray1dC<double>&);
#endif
  
}
