#ifndef RAVLGUITEXTBOX_HEADER
#define RAVLGUITEXTBOX_HEADER 1
//////////////////////////////////////////////////
//! lib=GUI
//! author="Charles Galambos"
//! date="23/03/99"
//! docentry="Ravl.GUI.Control"
//! rcsid="$Id$"

#include "Ravl/PThread/Mutex.hh"
#include "Ravl/GUI/Widget.hh"
#include "Ravl/String.hh"
#include "Ravl/DP/Signal1.hh"
#include "Ravl/DP/Signal2.hh"

namespace RavlGUIN {

  //! userlevel=Develop
  //: TextBox body
  
  class TextBoxBodyC 
    : public WidgetBodyC
  {
  public:
    TextBoxBodyC(const StringC &ntext,IntT nMaxLen = -1);
    //: Constructor.
    
    virtual bool Create();
    //: Create the widget.
    
    virtual bool Entry(const StringC &text);
    //: Some new text has been entered.
    
    StringC Text();
    //: Access text
    
    bool Text(const StringC &txt);
    //: Update text.
    // This is thread safe.
    
    Signal1C<StringC> &Activate() { return activate; }
    //: Activate, called when text is changed.
    
  protected:
    bool SetText(const StringC &txt);
    //: Set text to edit.
    // This should only be called within the GUI thread.
    
    void SigChanged();
    //: Got a changed signal.
    
    MutexC access;
    
    StringC text; // Default text.
    IntT maxLen; // Maximum length, -1==Unset.
    
    Signal1C<StringC> activate; // Return has been pressed.
    Signal0C changed;  // Text in box has been changed.
    
  };


  //! userlevel=Normal
  //: TextBox 
  // This displays some text.
  
  class TextBoxC 
    : public WidgetC
  {
  public:
    TextBoxC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    TextBoxC(const StringC &text,IntT nMaxLen = -1)
      : WidgetC(*new TextBoxBodyC(text,nMaxLen))
      {}
    //: Constructor
    
  protected:
    
    TextBoxBodyC &Body() 
      { return dynamic_cast<TextBoxBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const  TextBoxBodyC &Body() const
      { return dynamic_cast<const TextBoxBodyC &>(WidgetC::Body()); }
    //: Access body.  
    
  public:
    StringC Text() 
      { return Body().Text(); }
    //: Access text
    
    bool Text(const StringC &txt)
      { return Body().Text(txt); }
    //: Update text.
    // This is thread safe, with respect to the GUI thread.
    
    bool SetText(StringC &txt)
      { return Body().Text(txt); }
    //: Update text, for signal functions.
    // This is thread safe, with respect to the GUI thread.
    
    Signal1C<StringC> &Activate() 
      { return Body().Activate(); }
    //: Activate, called when text is changed.
    
  };

}

#endif
