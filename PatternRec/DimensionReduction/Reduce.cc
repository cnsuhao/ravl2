// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DimensionReduction/Reduce.cc"

#include "Ravl/PatternRec/Reduce.hh"
#include "Ravl/BinStream.hh"

namespace RavlN {
  
  //: Load from stream.

  ReduceBodyC::ReduceBodyC(istream &strm)
    : FunctionBodyC(strm)
  {
    strm >> varPreserved;
  }
  
  //: Load from binary stream.
  
  ReduceBodyC::ReduceBodyC(BinIStreamC &strm)
    : FunctionBodyC(strm)
  {
    strm >> varPreserved;
  }

  //: Writes object to stream, can be loaded using constructor
  
  bool ReduceBodyC::Save (ostream &out) const {
    if(!ReduceBodyC::Save(out))
      return false;
    out << ' ' << varPreserved;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool ReduceBodyC::Save (BinOStreamC &out) const {
    if(!ReduceBodyC::Save(out))
      return false;
    out << varPreserved;
    return true;
  }

  //: Reduce the dimension of 'data'.
  
  VectorC ReduceBodyC::Apply(const VectorC &data) {
    // Don't do anything...
    return data;
  }
  

}
