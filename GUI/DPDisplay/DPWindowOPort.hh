#ifndef RAVLGUI_DPWINDOWOPORT_HEADER
#define RAVLGUI_DPWINDOWOPORT_HEADER 1
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/DPWindow.hh"

namespace RavlGUIN {

  //! userlevel=Develop
  //: Window OPort body.
  
  class DPWindowOPortBodyC
    : public DPOPortBodyC<DPDisplayObjC>
  {
  public:
    DPWindowOPortBodyC(DPWindowC &win,bool accum = false);
    //: Constructor.
    
    virtual bool Put(const DPDisplayObjC &newObj);
    //: Process in coming display objects.
    
  protected:
    bool accumulate;
    DPWindowC win;
  };

  //! userlevel=Normal
  //: Window OPort.
  
  class DPWindowOPortC
    : public DPOPortC<DPDisplayObjC>
  {
  public:
    DPWindowOPortC(DPWindowC &win,bool accum = false)
      : DPEntityC(*new DPWindowOPortBodyC(win,accum))
    {}
    //: Constructor.
    
    DPWindowOPortC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    // creates an invalid handle.
  };
  
  
}

#endif
