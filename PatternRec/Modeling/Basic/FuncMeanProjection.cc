// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Charles Galambos"

#include "Ravl/PatternRec/FuncMeanProjection.hh"
#include "Ravl/BinStream.hh"

namespace RavlN {
  
  //: Default constructor.
  
  FuncMeanProjectionBodyC::FuncMeanProjectionBodyC(const VectorC &nMean,const MatrixC &nProj)
    : mean(nMean),
      proj(nProj)
  { 
    RavlAssert(mean.Size() == proj.Cols());
    InputSize(mean.Size());
    OutputSize(proj.Rows());
  }
  
  //: Load from stream.
  
  FuncMeanProjectionBodyC::FuncMeanProjectionBodyC(istream &strm) 
    : FunctionBodyC(strm)
  { strm >> mean >> proj; }
  
  //: Load from binary stream.
  
  FuncMeanProjectionBodyC::FuncMeanProjectionBodyC(BinIStreamC &strm) 
    : FunctionBodyC(strm)
  { strm >> mean >> proj; }
  
  //: Writes object to stream.
  
  bool FuncMeanProjectionBodyC::Save (ostream &out) const {
    if(!FunctionBodyC::Save(out))
      return false;
    out << ' ' << mean << ' ' << proj;
    return true;    
  }
  
  //: Writes object to binary stream.
  
  bool FuncMeanProjectionBodyC::Save (BinOStreamC &out) const {
    if(!FunctionBodyC::Save(out))
      return false;
    out << mean << proj;
    return true;
  }
  
  //: Apply function to 'data'
  
  VectorC FuncMeanProjectionBodyC::Apply(const VectorC &data) const {
    return proj * (data - mean);
  }
  
  ///////////////////////////////////////////////////////////
  
  //: Load from stream.
  
  FuncMeanProjectionC::FuncMeanProjectionC(istream &strm) 
    : FunctionC(RAVL_VIRTUALCONSTRUCTOR(strm,FuncMeanProjectionBodyC))
  {}
  
  //: Load from binary stream.
  
  FuncMeanProjectionC::FuncMeanProjectionC(BinIStreamC &strm) 
    : FunctionC(RAVL_VIRTUALCONSTRUCTOR(strm,FuncMeanProjectionBodyC))
  {}

}
