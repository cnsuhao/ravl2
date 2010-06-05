// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: FunctionConcatenate.cc 4106 2004-03-18 16:30:45Z kier $"
//! lib=RavlPatternRec
//! author="Charles Galambos"
//! file="Ravl/PatternRec/Modeling/Basic/FunctionConcatenate.cc"

#include "Ravl/PatternRec/FunctionConcatenate.hh"
#include "Ravl/VirtualConstructor.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/config.h"
#include "Ravl/SArray1dIter.hh"

#if RAVL_COMPILER_MIPSPRO 
#include "Ravl/VirtualConstructor.hh"
#pragma instantiate RavlN::FunctionConcatenateBodyC* RavlN::VCLoad(RavlN::BinIStreamC&,RavlN::FunctionConcatenateBodyC*)
#pragma instantiate RavlN::FunctionConcatenateBodyC* RavlN::VCLoad(istream &,RavlN::FunctionConcatenateBodyC*)
#endif 

namespace RavlN {

  //: Default constructor.
  
  FunctionConcatenateBodyC::FunctionConcatenateBodyC()
  {}
  
  //: Default constructor.
  
  FunctionConcatenateBodyC::FunctionConcatenateBodyC(const SArray1dC<FunctionC> & functions)
    : m_functions(functions)
  { 
    
    UIntT inputSize = 0;
    UIntT outputSize = 0;
    
    // work out the input and output size
    for(SArray1dIterC<FunctionC>it(functions);it;it++) {
      inputSize += it.Data().InputSize();
      outputSize += it.Data().OutputSize();
    }
    
    InputSize(inputSize);
    OutputSize(outputSize);
  }

  FunctionConcatenateBodyC::FunctionConcatenateBodyC(const FunctionC & function1, const FunctionC & function2)
    : m_functions(2)
  {
    m_functions[0] = function1;
    m_functions[1] = function2;
    InputSize(m_functions[0].InputSize());
    OutputSize(m_functions[1].OutputSize());
  }

  FunctionConcatenateBodyC::FunctionConcatenateBodyC(const FunctionC & function1, const FunctionC & function2, const FunctionC &function3)
    : m_functions(3)
  {
    m_functions[0] = function1;
    m_functions[1] = function2;
    m_functions[2] = function3;
    InputSize(m_functions[0].InputSize());
    OutputSize(m_functions[2].OutputSize());
  }
  
  
  //: Load from stream.
  
  FunctionConcatenateBodyC::FunctionConcatenateBodyC(istream &strm) 
    : FunctionBodyC(strm)
  { strm >> m_functions; }
  
  //: Load from binary stream.
  
  FunctionConcatenateBodyC::FunctionConcatenateBodyC(BinIStreamC &strm) 
    : FunctionBodyC(strm)
  { strm >> m_functions; }
  
  //: Writes object to stream.
  
  bool FunctionConcatenateBodyC::Save (ostream &out) const {
    if(!FunctionBodyC::Save(out))
      return false;
    out << ' ' << m_functions;
    return true;    
  }
  
  //: Writes object to binary stream.
  
  bool FunctionConcatenateBodyC::Save (BinOStreamC &out) const {
    if(!FunctionBodyC::Save(out))
      return false;
    out << m_functions;
    return true;
  }
  
  //: Apply function to 'data'
  
  VectorC FunctionConcatenateBodyC::Apply(const VectorC &data) const {


    // create space for level 2 vec
    VectorC vec(OutputSize());
    
    UIntT inputIndex = 0;
    UIntT outputIndex = 0;

    for(SArray1dIterC<FunctionC>it(m_functions);it;it++) {

      // do first level projection
      UIntT vecSize = it.Data().InputSize();      

      // FIXME: Can do this lots more efficiently
      // copy across input data
      VectorC inputVec(vecSize);
      for(SArray1dIterC<RealT>vecIt(inputVec);vecIt;vecIt++) {
        *vecIt = data[inputIndex];
        inputIndex++;
      }
      
      VectorC outputVec = it.Data().Apply(inputVec);                                    
      
      // copy to our output vector
      for(SArray1dIterC<RealT>vecIt(outputVec);vecIt;vecIt++) {
        vec[outputIndex] = *vecIt;
        outputIndex++;
      }

    }
        
    return vec;
  }
  
  ///////////////////////////////////////////////////////////
  
  
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(FunctionConcatenateBodyC,FunctionConcatenateC,FunctionC);
  //FileFormatStreamC <FunctionConcatenateC> FileFormatStream_FunctionConcatenateC;
  //FileFormatBinStreamC <FunctionConcatenateC> FileFormatBinStream_FunctionConcatenateC;
  //static TypeNameC typenameFunctionConcatenate(typeid(FunctionConcatenateC),"FunctionConcatenateC");

}
