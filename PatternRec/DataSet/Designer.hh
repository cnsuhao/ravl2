#ifndef RAVL_DESIGNER_HEADER
#define RAVL_DESIGNER_HEADER 1
//! rcsid="$Id$"
//! author="Charles Galambos"
//! docentry="Ravl.Pattern Recognition.Functions"

#include "Ravl/RCHandleV.hh"
#include "Ravl/Vector.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Designer base class.
  // Abstract Function designer. This is provided to allow the tweeking 
  // of design paramiters to be automated
  
  class DesignerBodyC
    : public RCBodyVC
  {
  public:
    DesignerBodyC()
    {}
    //: Default constructor.

    virtual VectorC Paramiters();
    //: Get the current paramiters.

    virtual VectorC Paramiters(const VectorC &params);
    //: Set the current paramiters.
    // Returns the current paramiters, which may not be exactly those
    // set in 'params', but will be the closest legal values.
  };

  //! userlevel=Normal
  //: Designer base class.
  // Abstract Function designer. This is provided to allow the tweeking 
  // of design paramiters to be automated
  
  class DesignerC
    : public RCHandleVC<DesignerBodyC>
  {
  public:
    DesignerC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    DesignerC(DesignerBodyC &bod)
      : RCHandleVC<DesignerBodyC>(bod)
    {}
    //: Body constructor.
    
    DesignerBodyC &Body()
    { return RCHandleVC<DesignerBodyC>::Body(); }
    //: Access body.
    
    const DesignerBodyC &Body() const
    { return RCHandleVC<DesignerBodyC>::Body(); }
    //: Access body.
    
  public:
    VectorC Paramiters()
    { return Body().Paramiters(); }
    //: Get the current paramiters.
    // Returns the current paramiters, which may not be exactly those
    // set in 'params', but will be the closest legal values.
    
    VectorC Paramiters(const VectorC &params)
    { return Body().Paramiters(params); }
    //: Set the current paramiters.
    // Returns the current paramiters, which may not be exactly those
    // set in 'params', but will be the closest legal values.
    
  };

  
}


#endif
