// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Modeling/Basic/FuncLinear.cc"

#include "Ravl/PatternRec/FuncLinear.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {

  //: Construct from a transform matrix.
  
  FuncLinearBodyC::FuncLinearBodyC() {
    ONDEBUG(cerr << "FuncLinearBodyC::FuncLinearBodyC(), Called. \n");
  }
  
  //: Load from stream.
  
  FuncLinearBodyC::FuncLinearBodyC(istream &strm)
    : FuncLinearCoeffBodyC(strm)
  {
    SetTransform(a); // make sure transform is setup properly.
  }
  
  //: Load from binary stream.
  
  FuncLinearBodyC::FuncLinearBodyC(BinIStreamC &strm)
    : FuncLinearCoeffBodyC(strm)
  { 
    SetTransform(a); // make sure transform is setup properly.
  }
  
  //: Writes object to stream.
  
  bool FuncLinearBodyC::Save (ostream &out) const 
  { return FuncLinearCoeffBodyC::Save(out); }
  
  //: Writes object to binary stream.
  
  bool FuncLinearBodyC::Save (BinOStreamC &out) const
  { return FuncLinearCoeffBodyC::Save(out); }
  
  //: Expand vector to linear coefficients.
  
  VectorC FuncLinearBodyC::MakeInput(const VectorC &X) const {
    VectorC ret(X.Size() + 1);
    ret[0] = 1;
    for(BufferAccessIter2C<RealT,RealT> it(X,ret.From(1));it;it++)
      it.Data2() = it.Data1();
    return ret;
  }
  
  //: Expand vector to linear coefficients.
  
  VectorC FuncLinearBodyC::MakeJacobianInput(const VectorC &X, IntT i) const {
    VectorC ret(1+X.Size());
    ret.Fill(0);
    ret[i] = 1.0;
    return ret;
  }

  //: Calculate the number of coefficents for a given input size.
  
  UIntT FuncLinearBodyC::NumberCoeffs(UIntT inputSize) const {
    return inputSize + 1;
  }
  
  //: Apply function to 'data'
  
  VectorC FuncLinearBodyC::Apply(const VectorC &data) const {
    return proj * data + mean;
  }

  //: Setup the transform.
  
  bool FuncLinearBodyC::SetTransform(const MatrixC &na) {
    if(!FuncLinearCoeffBodyC::SetTransform(na))
      return false;
    
    mean = a.SliceColumn(0);
    IndexRange2dC rng = a.Frame();
    rng.LCol()++;
    proj = SArray2dC<RealT>(a,rng);
    
    return true;
  }

  ////////////////////////////////////////////////////////////////////////
  
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(FuncLinearBodyC,FuncLinearC,FuncLinearCoeffC);
  
}
