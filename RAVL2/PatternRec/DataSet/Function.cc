// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/Function.cc"

#include "Ravl/PatternRec/Function.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/PatternRec/Sample.hh"
#include "Ravl/DArray1dIter2.hh"
#include "Ravl/VirtualConstructor.hh"

namespace RavlN {

  //: Load from stream.
  
  FunctionBodyC::FunctionBodyC(istream &strm)
    : RCBodyVC(strm)
  { strm >> inputSize >> outputSize; }
  
  //: Load from binary stream.
  
  FunctionBodyC::FunctionBodyC(BinIStreamC &strm)
    : RCBodyVC(strm)
  { strm >> inputSize >> outputSize; }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool FunctionBodyC::Save (ostream &out) const {
    if(!RCBodyVC::Save(out))
      return false;
    out  << ' ' << inputSize << ' ' << outputSize << ' ';
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool FunctionBodyC::Save (BinOStreamC &out) const {
    if(!RCBodyVC::Save(out))
      return false;
    out << inputSize << outputSize;
    return true;
  }
  
  //: Apply function to 'data'
  
  VectorC FunctionBodyC::Apply(const VectorC &data) const {
    RavlAssertMsg(0,"RavlN::Apply(), Abstract method called. \n");
    return data;
  }
  
  //: Apply function to two data vectors 

  VectorC FunctionBodyC::Apply(const VectorC & data1, const VectorC & data2) const {
    return Apply( data1.Join(data2) ) ; }

  //: Apply transform to whole dataset.
  
  SampleC<VectorC> FunctionBodyC::Apply(const SampleC<VectorC> &data) {
    SampleC<VectorC> ret(data.Size());
    for(DArray1dIterC<VectorC> it(data.DArray());it;it++)
      ret += Apply(*it);
    return ret;
  }
  
  MatrixC FunctionBodyC::Jacobian (const VectorC &X) const {
    RavlAssert(X.Size() == inputSize);
    MatrixC J (outputSize,inputSize);
    VectorC dX (inputSize);
    dX.Fill(0);
    for(UIntT index = 0;index < inputSize;index++) {
      dX[index] = 1e-6;
      VectorC temp = Apply(X+dX) - Apply(X-dX);
      temp /= 2e-6;
      J.SetColumn (index,temp);
      dX[index] = 0;
    }
    return J;
  }
  
  //: Evalate the function and its jacobian at the same time.
  // This method defaults to calling 'Apply' and 'Jacobian' sperately.
  
  VectorMatrixC FunctionBodyC::Evaluate(const VectorC &X) {
    return VectorMatrixC(Apply(X),Jacobian(X));
  }
  
  //: Evaluate the value,jacobian of the function at point X
  // Returns true if all values are provide, false if one or more is approximated.
  
  bool FunctionBodyC::EvaluateValueJacobian(const VectorC &X,VectorC &value,MatrixC &jacobian) const {
    value = Apply(X);
    jacobian = Jacobian (X);
    return false;
  }
  
  //: Evaluate the value of the function at point X
  // Returns true if all values are provide, false if one or more is approximated.
  
  bool FunctionBodyC::EvaluateValue(const VectorC &X,VectorC &value) const {
    value = Apply(X);
    return true;
  }
  
  //: Write a human readable text description of the function.
  void FunctionBodyC::Describe(ostream &out) {
    out << "Describe not implemented\n";
  }
  
  //////////////////////////////////////////////////////////
  
  //: Apply transform to whole dataset.
  
  SampleC<VectorC> FunctionC::Apply(const SampleC<VectorC> &data)
  { return Body().Apply(data); }

  //: Load from stream.
  
  FunctionC::FunctionC(istream &strm) 
    : RCHandleVC<FunctionBodyC>(RAVL_VIRTUALCONSTRUCTOR(strm,FunctionBodyC))
  {}
    
  //: Load from binary stream.
  
  FunctionC::FunctionC(BinIStreamC &strm) 
    : RCHandleVC<FunctionBodyC>(RAVL_VIRTUALCONSTRUCTOR(strm,FunctionBodyC))    
  {}
  
  //: Setup virtual constructor.
  // As this is an abstract class its not really needed, but its usefull to
  // have an example of how it should work here.
  
  //RAVL_INITVIRTUALCONSTRUCTOR(FunctionBodyC);
  
}
