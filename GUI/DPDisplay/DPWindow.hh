#ifndef RAVLGUI_DPWINDOW_HEADER
#define RAVLGUI_DPWINDOW_HEADER 1
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/DP/Port.hh"
#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/DPDisplayView.hh"
#include "Ravl/Threads/Mutex.hh"

namespace RavlGUIN {
  class DPWindowC;
  
  void DisableWaitForGUIExit();
  //: Disable waiting for GUI to finish on program exit.
  // Call this method to allow program to exit immediatly even if
  // there are DPWindowC's open.
  
  //! userlevel=Develop
  //: DP Window base.
  
  class DPWindowBodyC 
    : public RCBodyVC
  {
  public:
    DPWindowBodyC(const StringC &nname,const IndexRange2dC &nWinSize = IndexRange2dC(IndexC(100),IndexC(100)));
    //: Default constructor.
    
    const StringC &Name() const
    { return name; }
    //: Access window name.
    
    void Init(const IndexRange2dC &size);
    //: Construct widgets.
    
    bool AddObject(const DPDisplayObjC &obj);
    //: Add object to the display list.
    
    bool ReplaceObject(const DPDisplayObjC &obj);
    //: This clears the display list then adds 'obj'.
    
    bool Clear();
    //: Clear the display list.
    
    bool Refresh();
    //: Refresh the display.
    
  protected:    
    StringC name;
    MutexC setupMutex; // Make sure window is only setup once.
    WindowC win;
    IndexRange2dC winSize;
    DPDisplayViewC view;
    friend class DPWindowC;    
  };
  
  //! userlevel=Normal
  //: DP Window.
  
  class DPWindowC 
    : public RCHandleC<DPWindowBodyC>
  {
  public:
    DPWindowC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DPWindowC(const StringC &nname,const IndexRange2dC &nWinSize = IndexRange2dC(IndexC(100),
										 IndexC(100)))
      : RCHandleC<DPWindowBodyC>(*new DPWindowBodyC(nname,nWinSize))
    {}
    //: Construct a named window.

  protected:
    DPWindowC(DPWindowBodyC &body)
      : RCHandleC<DPWindowBodyC>(body)
    {}
    //: Body constructor.
    
    DPWindowBodyC &Body()
    { return RCHandleC<DPWindowBodyC>::Body(); }
    //: Access body.

    const DPWindowBodyC &Body() const
    { return RCHandleC<DPWindowBodyC>::Body(); }
    //: Access body.

    
  public:
    
    bool AddObject(const DPDisplayObjC &obj) 
    { return Body().AddObject(obj); }
    //: Add object to the display list.
    
    bool ReplaceObject(const DPDisplayObjC &obj)
    { return Body().ReplaceObject(obj); }
    //: This clears the display list then adds 'obj'.
    
    bool Clear()
    { return Body().Clear(); }
    //: Clear the display list.
    
    bool Refresh()
    { return Body().Refresh(); }
    //: Refresh the display.

    friend class DPWindowBodyC;
  };
  
}



#endif
