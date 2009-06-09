// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Sequence/PrimitiveBinaryPolynomial.cc"

#include "Ravl/PrimitiveBinaryPolynomial.hh"
#include "Ravl/BufferAccessIter2.hh"

namespace RavlN {

  
  //: Evalutate the sequence of 'len' values.

  SArray1dC<UIntT> PrimitiveBinaryPolynomialC::Evaluate(IntT len) {
    SArray1dC<UIntT> seq(len);
    for(BufferAccessIter2C<UIntT,UIntT> it(seq,
                                           m_init,
                                           (SizeT) m_deg);it;it++)
      it.Data1() = it.Data2();
    for(int i = m_deg;i < len ;i++) {
      IntT res = seq[i-m_deg] ^ (seq[i-m_deg] << m_deg);
      int ta = m_args;
      for(int q = m_deg-1;q > 0;q--) {
	if(ta & 1)
	  res ^= seq[i-q] << q;
	ta >>= 1;
      }
      seq[i] = res;
    }
    return seq;
  }

}
