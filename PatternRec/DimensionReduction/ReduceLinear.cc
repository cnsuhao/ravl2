// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/ReduceLinear.hh"
#include "Ravl/BinStream.hh"

namespace RavlN {
  
  //: Default constructor.
  
  ReduceLinearBodyC::ReduceLinearBodyC(const VectorC &nmean,const MatrixC &nproj,RealT variationPreserved )
    : ReduceBodyC(variationPreserved),
      mean(nmean),
      proj(nproj)
  {}
  
  //: Load from stream.
  
  ReduceLinearBodyC::ReduceLinearBodyC(istream &strm) 
    : ReduceBodyC(strm)
  {
    strm >> mean >> proj;
  }
  
  //: Load from binary stream.
  
  ReduceLinearBodyC::ReduceLinearBodyC(BinIStreamC &strm)
    : ReduceBodyC(strm)
  {
    strm >> mean >> proj;
  }

  //: Reduce the dimension of 'data'.
  
  VectorC ReduceLinearBodyC::Apply(const VectorC &data) {
    return proj*(data-mean);
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool ReduceLinearBodyC::Save(ostream &out) const {
    if(!ReduceBodyC::Save(out))
      return false;
    out << ' ' << mean << ' ' << proj;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool ReduceLinearBodyC::Save(BinOStreamC &out) const {
    if(!ReduceBodyC::Save(out))
      return false;
    out << mean << proj;
    return true;
  }


}
