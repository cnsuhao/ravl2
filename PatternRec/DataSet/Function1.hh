// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FUNCTION1_HEADER
#define RAVL_FUNCTION1_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/Function.hh"

namespace RavlN {

  //! userlevel=Develop
  //: Map a vector to a single real value.
  
  class Function1BodyC 
    : public FunctionBodyC
  {
  public:
    Function1BodyC()
    { outputSize = 1; }
    //: Default constructor.
    
    virtual VectorC Apply(const VectorC &data) const;
    //: Apply function to 'data'
    
    virtual RealT Apply1(const VectorC &data) const;
    //: Apply function to 'data'
    
  };

  //! userlevel=Normal
  //: Map a vector to a single real value.

  class Function1C 
    : public FunctionC
  {
  public:
    Function1C()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    Function1C(Function1BodyC &bod)
      : FunctionC(bod)
    {}
    //: Body constructor.
    
    Function1BodyC &Body()
    { return static_cast<Function1BodyC &>(FunctionC::Body()); }
    //: Access body.

    const Function1BodyC &Body() const
    { return static_cast<const Function1BodyC &>(FunctionC::Body()); }
    //: Access body.
    
  public:
    
    RealT Apply1(const VectorC &data) const
    { return Body().Apply1(data); }
    //: Apply function to 'data'
    
  };
  
  
}


#endif
