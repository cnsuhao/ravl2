// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/FuncPDFNormal.hh"

namespace RavlN {

  //: Create from an array of distributions.
  
  FuncPDFNormalBodyC::FuncPDFNormalBodyC(const SArray1dC<NormalC> &ndists)
    : FuncPDFBodyC(0,ndists.Size()),
      dists(ndists)
  {
    if(!ndists.IsEmpty())
      InputSize(ndists[0].Size());
  }
  
  //: Apply function to 'data'

  VectorC FuncPDFNormalBodyC::Apply(const VectorC &data) const {
    VectorC ret(dists.Size());
    for(SArray1dIter2C<RealT,NormalC> it(ret,dists);it;it++)
      it.Data1() = it.Data2().Evaluate(data);
    return ret;
  }
  
}
