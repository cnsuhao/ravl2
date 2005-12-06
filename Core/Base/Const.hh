// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_CONST_HEADER
#define RAVL_CONST_HEADER 1
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore
//! docentry="Ravl.API.Core.Misc"
//! author="Charles Galambos"
//! file="Ravl/Core/Base/Const.hh"

#include "Ravl/Assert.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Constant flag mix-in class.
  // This class can be used to ensure that an object
  // is not modified if some other class requires that
  // it remains constant. <p>
  // Once an object is made constant it may not be reset.
  // Any object using this class should place 
  // AssertNonConst(), in all methods that modify its
  // contents.
  
  class ConstBodyC {
  public:
    ConstBodyC()
      : isConst(false)
    {}
    //: Default constructor.
    // sets the object to constant.
    
    bool IsConst() const
    { return isConst; }
    //: Return const state.
    
    void MakeConst()
    { isConst = true; }
    //: Make object constant.
    
    void AssertConst() const
    { RavlAssertMsg(isConst,"Constant violation. "); }
    //: Assert that an object must be const.
    
    void AssertNotConst() const
    { RavlAssertMsg(isConst,"Non constant violation. "); }
    //: Assert that an object must not be const.
    
  protected:
    bool isConst;
  };

}

#endif
