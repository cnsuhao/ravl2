// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FUNCTION_HEADER
#define RAVL_FUNCTION_HEADER 1
///////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Charles Galambos, based on code by Robert Crida"
//! docentry="Ravl.Pattern Recognition.Functions"
//! file="Ravl/PatternRec/DataSet/Function.hh"

#include "Ravl/Vector.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/RCHandleV.hh"
#include "Ravl/VectorMatrix.hh"

namespace RavlN {
  template<class DataT> class SampleC;
  
  //! userlevel=Develop
  //: Map an input vector to an output vector.
  
  class FunctionBodyC
    : public RCBodyVC
  {
  public:
    FunctionBodyC()
      : inputSize(0),
	outputSize(0)
    {}
    //: Default constructor.
    
    FunctionBodyC(UIntT inSize,UIntT outSize)
      : inputSize(inSize),
	outputSize(outSize)
    {}
    //: Create function with given number of inputs and outputs.
    
    FunctionBodyC(istream &strm);
    //: Load from stream.
    
    FunctionBodyC(BinIStreamC &strm);
    //: Load from binary stream.

    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual VectorC Apply(const VectorC &data) const;
    //: Apply function to 'data'
    
    virtual VectorC Apply(const VectorC & data1, const VectorC & data2) const ; 
    //: Apply function to two data vectors 
    // The default behaviour is to concatenate the two vectors  
    // and then call the single vector version of Apply() 

    virtual SampleC<VectorC> Apply(const SampleC<VectorC> &data);
    //: Apply transform to whole dataset.
    
    virtual MatrixC Jacobian (const VectorC &X) const;
    //: Calculate Jacobian matrix at X
    // Performs numerical estimation of the Jacobian using differences. This
    // function has and should be overloaded for all cases where the Jacobian
    // can be calculated analytically.
    
    virtual VectorMatrixC Evaluate(const VectorC &X);
    //: Evalate the function and its jacobian at the same time.
    // This method defaults to calling 'Apply' and 'Jacobian' sperately.
    
    inline UIntT InputSize() const
    { return inputSize; }
    //: Size of input vectors
    
    inline UIntT OutputSize() const
    { return outputSize; }
    //: Size of output vectors
    
    virtual UIntT InputSize(UIntT inSize)
    { return inputSize = inSize; }
    //: Set the input size.
    // This is for use of designer classes, changing the input size of
    // an existing function has undefined effects.
    
    virtual UIntT OutputSize(UIntT outSize)
    { return outputSize = outSize; }
    //: Set the output size.
    // This is for use of designer classes, changing the output size of
    // an existing function has undefined effects.
  protected:
    
    UIntT inputSize;  // (X in amma speak.)
    UIntT outputSize; // (Y in amma speak.)
  };
  
  //! userlevel=Normal
  //: Map an input vector to an output vector.
  
  class FunctionC
    : public RCHandleVC<FunctionBodyC>
  {
  public:
    FunctionC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    FunctionC(istream &strm);
    //: Load from stream.

    FunctionC(BinIStreamC &strm);
    //: Load from binary stream.
    
  protected:
    FunctionC(FunctionBodyC &bod)
      : RCHandleVC<FunctionBodyC>(bod)
    {}
    //: Body constructor.
    
    FunctionC(FunctionBodyC *bod)
      : RCHandleVC<FunctionBodyC>(bod)
    {}
    //: Body ptr constructor.
    
    FunctionBodyC &Body()
    { return RCHandleC<FunctionBodyC>::Body(); }
    //: Access body.
    
    const FunctionBodyC &Body() const
    { return RCHandleC<FunctionBodyC>::Body(); }
    //: Access body.
    
  public:
    VectorC Apply(const VectorC &data) const
    { return Body().Apply(data); }
    //: Apply function to 'data'
    
    inline VectorC Apply(const VectorC & data1, const VectorC & data2) const
      { return Body().Apply(data1, data2) ; }
    //: Apply function to two data vectors 
    // The default behaviour is to concatenate the two vectors  
    // and then call the single vector version of Apply() 
    
    SampleC<VectorC> Apply(const SampleC<VectorC> &data);
    //: Apply transform to whole dataset.
    
    VectorC operator() (const VectorC &X) const 
    { return Body().Apply(X); }
    //: Evaluate Y=f(X)
    
    MatrixC Jacobian(const VectorC &X) const
    { return Body().Jacobian(X); }    
    //: Calculate Jacobian matrix at X
    // Performs numerical estimation of the Jacobian using differences. This
    // function has and should be overloaded for all cases where the Jacobian
    // can be calculated analytically.
    
    inline VectorMatrixC Evaluate(const VectorC &X)
    { return Body().Evaluate(X); }
    //: Evalate the function and its jacobian at the same time.
    // This method defaults to calling 'Apply' and 'Jacobian' sperately.
    
    inline UIntT InputSize() const
    { return Body().InputSize(); }
    //: Size of input vector
    
    inline UIntT OutputSize() const
    { return Body().OutputSize(); }
    //: Size of output vector

    UIntT InputSize(UIntT inSize)
    { return Body().InputSize(inSize); }
    //: Set the input size.
    // This is for use of designer classes, changing the input size of
    // an existing function has undefined effects.
    
    UIntT OutputSize(UIntT outSize)
    { return Body().OutputSize(outSize); }
    //: Set the output size.
    // This is for use of designer classes, changing the output size of
    // an existing function has undefined effects.
    
  };

  
  inline istream &operator>>(istream &strm,FunctionC &obj) {
    obj = FunctionC(strm);
    return strm;
  }
  //: Load from a stream.
  // Uses virtual constructor.
  
  inline ostream &operator<<(ostream &out,const FunctionC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.
  
  inline BinIStreamC &operator>>(BinIStreamC &strm,FunctionC &obj) {
    obj = FunctionC(strm);
    return strm;
  }
  //: Load from a binary stream.
  // Uses virtual constructor.
  
  inline BinOStreamC &operator<<(BinOStreamC &out,const FunctionC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.
}

#endif
