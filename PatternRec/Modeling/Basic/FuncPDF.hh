// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FUNCPDF_HEADER
#define RAVL_FUNCPDF_HEADER 1
//! docentry="Ravl.Pattern Recognition.Numerical Modeling"
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/Function.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Abstract Probablity Distribution Function.
  // The integral of these functions must be 1.
  
  class FuncPDFBodyC 
    : public FunctionBodyC
  {
  public:
    FuncPDFBodyC()
    {}
    //: Default constructor.
    
    FuncPDFBodyC(UIntT inSize,UIntT outSize);
    //: Constructor.
    
  };
  
  //! userlevel=Normal
  //: Abstract Probablity Distribution Function.
  // The integral of these functions must be 1.
  
  class FuncPDFC
    : public FunctionC
  {
  public:
    FuncPDFC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    FuncPDFC(FuncPDFBodyC &bod)
      : FunctionC(bod)
    {}
    //: Body constructor.
    
    FuncPDFBodyC& Body()
    { return static_cast<FuncPDFBodyC &>(FunctionC::Body()); }
    //: Access body.

    const FuncPDFBodyC& Body() const
    { return static_cast<const FuncPDFBodyC &>(FunctionC::Body()); }
    //: Access body.
    
  public:
    
  };

}


#endif
