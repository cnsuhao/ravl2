// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: FunctionCascade.cc 4106 2004-03-18 16:30:45Z kier $"
//! lib=RavlPatternRec
//! author="Charles Galambos"
//! file="Ravl/PatternRec/Modeling/Basic/FunctionCascade.cc"

#include "Ravl/PatternRec/FunctionCascade.hh"
#include "Ravl/VirtualConstructor.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/config.h"
#include "Ravl/SArray1dIter.hh"

#if RAVL_COMPILER_MIPSPRO 
#include "Ravl/VirtualConstructor.hh"
#pragma instantiate RavlN::FunctionCascadeBodyC* RavlN::VCLoad(RavlN::BinIStreamC&,RavlN::FunctionCascadeBodyC*)
#pragma instantiate RavlN::FunctionCascadeBodyC* RavlN::VCLoad(istream &,RavlN::FunctionCascadeBodyC*)
#endif 

namespace RavlN {

  //: Default constructor.
  
  FunctionCascadeBodyC::FunctionCascadeBodyC()
  {}
  
  //: Default constructor.
  
  FunctionCascadeBodyC::FunctionCascadeBodyC(const SArray1dC<FunctionC> & functions)
    : m_functions(functions)
  { 
    RavlAssert(functions.Size() > 0);
    
    UIntT numberOfFunctions = functions.Size();

    // FIXME Should check all input/output sizes marry
    
    InputSize(functions[0].InputSize());
    OutputSize(functions[numberOfFunctions-1].OutputSize());
  }

  FunctionCascadeBodyC::FunctionCascadeBodyC(const FunctionC & function1, const FunctionC & function2)
    : m_functions(2)
  {    
    m_functions[0] = function1;
    m_functions[1] = function2;
    InputSize(m_functions[0].InputSize());
    OutputSize(m_functions[1].OutputSize());
  }

  FunctionCascadeBodyC::FunctionCascadeBodyC(const FunctionC & function1, const FunctionC & function2, const FunctionC &function3)
    : m_functions(3)
  {
    m_functions[0] = function1;
    m_functions[1] = function2;
    m_functions[2] = function3;
    InputSize(m_functions[0].InputSize());
    OutputSize(m_functions[2].OutputSize());
  }

  
  //: Load from stream.
  
  FunctionCascadeBodyC::FunctionCascadeBodyC(istream &strm) 
    : FunctionBodyC(strm)
  { strm >> m_functions; }
  
  //: Load from binary stream.
  
  FunctionCascadeBodyC::FunctionCascadeBodyC(BinIStreamC &strm) 
    : FunctionBodyC(strm)
  { strm >> m_functions; }
  
  //: Writes object to stream.
  
  bool FunctionCascadeBodyC::Save (ostream &out) const {
    if(!FunctionBodyC::Save(out))
      return false;
    out << ' ' << m_functions;
    return true;    
  }
  
  //: Writes object to binary stream.
  
  bool FunctionCascadeBodyC::Save (BinOStreamC &out) const {
    if(!FunctionBodyC::Save(out))
      return false;
    out << m_functions;
    return true;
  }
  
  //: Apply function to 'data'
  
  VectorC FunctionCascadeBodyC::Apply(const VectorC &data) const {
    VectorC outputVec = data.Copy();
    for(SArray1dIterC<FunctionC>it(m_functions);it;it++) {      
      outputVec= it.Data().Apply(outputVec);
    }            
    return outputVec;
  }
  
  ///////////////////////////////////////////////////////////
  
  
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(FunctionCascadeBodyC,FunctionCascadeC,FunctionC);
  //FileFormatStreamC <FunctionCascadeC> FileFormatStream_FunctionCascadeC;
  //FileFormatBinStreamC <FunctionCascadeC> FileFormatBinStream_FunctionCascadeC;
  //static TypeNameC typenameFunctionCascade(typeid(FunctionCascadeC),"FunctionCascadeC");

}
