// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_DPDISPLAYOBJ_HEADER
#define RAVLGUI_DPDISPLAYOBJ_HEADER 1
/////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlDPDisplay
//! file="Ravl/GUI/DPDisplay/DPDisplayObj.hh"
//! author="Charles Galambos"
//! docentry="Ravl.GUI.Data Display"

#include "Ravl/RCHandleV.hh"
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
