// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: FuncSubset.cc 3073 2003-06-13 07:18:32Z craftit $"
//! lib=RavlPatternRec
//! author="Charles Galambos"
//! file="Ravl/PatternRec/Modeling/DimensionReduction/FuncSubset.cc"

#include "Ravl/PatternRec/FuncSubset.hh"
#include "Ravl/BinStream.hh"

namespace RavlN {
  
  //: Constructor from an array of indexes.
  
  FuncSubsetBodyC::FuncSubsetBodyC(const SArray1dC<IndexC> &ninds,UIntT inSize)
    : inds(ninds)
  {
    OutputSize(inds.Size());
    InputSize(inSize);
  }
  
  //: Reduce the dimension of 'data'.
  
  VectorC FuncSubsetBodyC::Apply(const VectorC &data) {
    VectorC ret(inds.Size());
    for(BufferAccessIter2C<IndexC,RealT> it(inds,ret);it;it++)
      it.Data2() = data[it.Data1()];
    return ret;
  }

}
