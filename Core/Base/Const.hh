#ifndef RAVLCONST_HEADER
#define RAVLCONST_HEADER 1
/////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Assert.hh"

namespace RavlN {
  
  //! userlevel=Advanced
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
