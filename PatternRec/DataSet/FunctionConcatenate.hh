// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FUNCTIONCONCATENATE_HEADER
#define RAVL_FUNCTIONCONCATENATE_HEADER 1
//! rcsid="$Id: FunctionConcatenate.hh 6820 2008-05-30 14:30:11Z ees1wc $"
//! lib=RavlPatternRec
//! author="Kieron"
//! docentry="Ravl.API.Pattern Recognition.Numerical Modeling"
//! file="Ravl/PatternRec/Modeling/Basic/FunctionConcatenate.hh"

#include "Ravl/PatternRec/Function.hh"
#include "Ravl/SArray1d.hh"

namespace RavlN {

  //! userlevel=Develop
  //: Function which con-catenates a set of functions together!
  
  class FunctionConcatenateBodyC
    : public FunctionBodyC
  {
  public:
    FunctionConcatenateBodyC();
    //: Default constructor.
    
    FunctionConcatenateBodyC(const SArray1dC<FunctionC> & functions);
    //: Default constructor.
    
    FunctionConcatenateBodyC(const FunctionC & function1, const FunctionC & function2);

    FunctionConcatenateBodyC(const FunctionC & function1, const FunctionC & function2, const FunctionC & function3);
    
    FunctionConcatenateBodyC(istream &strm);
    //: Load from stream.
    
    FunctionConcatenateBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream.
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to binary stream.
    
    virtual VectorC Apply(const VectorC &data) const;
    //: Apply function to 'data'
    
    const SArray1dC<FunctionC> & Functions() const
    { return m_functions; }
    //: Access to the functions
    
    
  protected:
    // The concatenated functions
    SArray1dC<FunctionC> m_functions;
  };
  
  //! userlevel=Normal
  //: Function which concatenates a set of functions together!
  
  class FunctionConcatenateC
    : public FunctionC 
  {
  public:
    FunctionConcatenateC()
    {}
    //: Default constructor.
    

    FunctionConcatenateC(const SArray1dC<FunctionC> & functions)
      : FunctionC(*new FunctionConcatenateBodyC(functions))
    {}
    //: Construct from a set of functions

    FunctionConcatenateC(const FunctionC & function1, const FunctionC & function2)
      : FunctionC(*new FunctionConcatenateBodyC(function1, function2))
    {}
    //: Construct from a set of functions

    FunctionConcatenateC(const FunctionC & function1, const FunctionC & function2, const FunctionC & function3)
      : FunctionC(*new FunctionConcatenateBodyC(function1, function2, function3))
    {}
    //: Construct from a set of functions

    
    
    FunctionConcatenateC(istream &is);
    //: Stream constructor.
    
    FunctionConcatenateC(BinIStreamC &is);
    //: Stream constructor.
    
    FunctionConcatenateC(const FunctionC &func)
      : FunctionC(dynamic_cast<const FunctionConcatenateBodyC *>(BodyPtr(func)))
    {}
    //: Attempt to create handle from base class.
    // If object is not a FunctionConcatenateC, an invalid handle will be created.
    
  protected:
    FunctionConcatenateC(FunctionConcatenateBodyC &bod)
      : FunctionC(bod)
    {}
    //: Body constructor.
    
    FunctionConcatenateC(const FunctionConcatenateBodyC *bod)
      : FunctionC(bod)
    {}
    //: Body constructor.
    
    FunctionConcatenateBodyC &Body()
    { return static_cast<FunctionConcatenateBodyC &>(FunctionC::Body()); }
    //: Access body.

    const FunctionConcatenateBodyC &Body() const 
    { return static_cast<const FunctionConcatenateBodyC &>(FunctionC::Body()); }
    //: Access body.
    
  public:
    const SArray1dC<FunctionC> & Functions() const
    { return Body().Functions(); }
    //: Access functions.
    
    
  };
  
  
  inline istream &operator>>(istream &strm,FunctionConcatenateC &obj) {
    obj = FunctionConcatenateC(strm);
    return strm;
  }
  //: Load from a stream.
  // Uses virtual constructor.
  
  inline ostream &operator<<(ostream &out,const FunctionConcatenateC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.
  
  inline BinIStreamC &operator>>(BinIStreamC &strm,FunctionConcatenateC &obj) {
    obj = FunctionConcatenateC(strm);
    return strm;
  }
  //: Load from a binary stream.
  // Uses virtual constructor.
  
  inline BinOStreamC &operator<<(BinOStreamC &out,const FunctionConcatenateC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.

}



#endif
