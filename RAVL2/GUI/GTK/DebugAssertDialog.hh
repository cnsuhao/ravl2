#ifndef RAVLGUI_DEBUGASSERT_DIALOG_HEADER
#define RAVLGUI_DEBUGASSERT_DIALOG_HEADER 1

//ONLY USE THIS CLASS WHEN IN DEBUG MODE
//Used to warn the programmer when something's happening that shouldn't be 
//however the programmer can choose to ignore the warning.

#include "Ravl/GUI/Window.hh"
#include "Ravl/String.hh"
#include "Ravl/GUI/Button.hh"
#include "Ravl/GUI/Widget.hh"

namespace RavlGUIN 
{  
  using namespace RavlN;
  class DebugAssertDialogC;
 
  class DebugAssertDialogBodyC : public WindowBodyC
  {
  public:
    DebugAssertDialogBodyC(StringC message, const char *title = 0, const WindowC* parent = NULL); 

    virtual ~DebugAssertDialogBodyC() { }
    //: Have virtual methods - need virtual destructor

    virtual bool Create();	//: Create the widget.

  protected:
    bool OnContinue();
    bool OnBombOut();
    bool OnQuit(GdkEvent*& event, WidgetC& myWidge, bool& bRef);
    bool OnDestroy();
    bool OnDisableDialog(bool &bStatus);
 
    StringC m_strMessage;
    ButtonC m_continueButton;
    WindowC *m_rootWindow;
  
  //  friend class MessageBoxC;
  };
  
  
  
  class DebugAssertDialogC : public WindowC
  {
  public:
    DebugAssertDialogC() {}	// Creates an invalid handle.
    
    DebugAssertDialogC(StringC message, const char *title = 0,const WindowC* parent = NULL)
      : WindowC( *new DebugAssertDialogBodyC(message, title, parent)) {}
    // If parent is not NULL, the dialog will be kept above it by the window manager
    
  protected:
    DebugAssertDialogC(DebugAssertDialogBodyC &bod)
      : WindowC(bod) {}
    
    DebugAssertDialogBodyC &Body() 
    { return static_cast<DebugAssertDialogBodyC  &>(WidgetC::Body()); }
    //: Access body.
    
    const DebugAssertDialogBodyC  &Body() const
    { return static_cast<const DebugAssertDialogBodyC  &>(WidgetC::Body()); }
    //: Access body.
    
  public:

    static bool m_sbShowDialog;
    void Destroy() 
    {
      WidgetC::Destroy(); 
      Invalidate();
    }
    
    friend class DebugAssertDialogBodyC;
  };

  //Wrapper class for the debug dialog, this makes sure it's only ever called in debug mode
  class DebugDialogWrapperC
  //class DebugDialogWrapperBodyC
  {
    public:
    DebugDialogWrapperC() {};    
    DebugDialogWrapperC(StringC message, const char *title = 0, const WindowC* parent = NULL); 
  };
  
}

#endif
