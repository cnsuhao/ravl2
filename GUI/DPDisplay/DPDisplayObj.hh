#ifndef RAVLGUI_DPDISPLAYOBJ_HEADER
#define RAVLGUI_DPDISPLAYOBJ_HEADER 1
/////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/RefCounter.hh"
#include "Ravl/IndexRange2d.hh"
#include "Ravl/Vector2d.hh"
#include "Ravl/String.hh"

namespace RavlGUIN {
  using namespace RavlN;
  
  class DPDisplayViewBodyC;
  
  //! userlevel=Develop
  //: Display object body
  
  class DPDisplayObjBodyC 
    : public RCBodyVC
  {
  public:
    DPDisplayObjBodyC();
    //: Default constructor.
    
    virtual bool Draw(DPDisplayViewBodyC &canvas);
    //: Draw object to canvas.
    
    virtual IndexRange2dC Frame() const;
    //: Find bounding box for object.
    
    virtual bool Query(const Vector2dC &pnt,StringC &text);
    //: Query a point in the display.
    // Return true if point is within object.
  protected:
  };
  
  //! userlevel=Normal
  //: Display object.
  
  class DPDisplayObjC 
    : public RCHandleC<DPDisplayObjBodyC>
  {
  public:
    DPDisplayObjC()
    {}
    //: Default constructor.
    // Creates invalid handle.
    
  protected:
    DPDisplayObjC(DPDisplayObjBodyC &body)
      : RCHandleC<DPDisplayObjBodyC>(body)
    {}
    //: Body constructor.
    
    DPDisplayObjBodyC &Body()
    { return RCHandleC<DPDisplayObjBodyC>::Body(); }
    //: Access body.

    const DPDisplayObjBodyC &Body() const
    { return RCHandleC<DPDisplayObjBodyC>::Body(); }
    //: Access body.
  public:
    
    bool Draw(DPDisplayViewBodyC &canvas)
    { return Body().Draw(canvas); }
    //: Draw object to canvas.
    
    IndexRange2dC Frame() const
    { return Body().Frame(); }
    //: Find bounding box for object.
    
    bool Query(const Vector2dC &pnt,StringC &text)
    { return Body().Query(pnt,text); }
    //: Query a point in the display.
    // Return true if point is within object.

  };
  
}


#endif
