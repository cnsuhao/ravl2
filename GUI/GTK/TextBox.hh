#ifndef RAVLGUITEXTBOX_HEADER
#define RAVLGUITEXTBOX_HEADER 1
//////////////////////////////////////////////////
//! lib=GUI
//! author="Charles Galambos"
//! date="23/03/99"
//! docentry="Ravl.GUI.Control"
//! rcsid="$Id$"

#include "Ravl/GUI/Widget.hh"
#include "Ravl/String.hh"
#include "Ravl/Threads/Signal1.hh"
#include "Ravl/Threads/Signal2.hh"

namespace RavlGUIN {

  class TextBoxC;
  
  //! userlevel=Develop
  //: TextBox body
  
  class TextBoxBodyC 
    : public WidgetBodyC
  {
  public:
    TextBoxBodyC(const StringC &ntext,bool editable = true);
    //: Constructor.
    
    virtual bool Create();
    //: Create the widget.
    
    StringC Text();
    //: Access text
    
    bool Insert(const StringC &txt);
    //: Update text.
    // This is thread safe.
    
  protected:
    bool GUIInsert(StringC &txt);
    //: Insert text in window.
    
    StringC text; // text.
    bool editable; // Is text editable ?
    
    friend class TextBoxC;
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
    
    TextBoxC(const StringC &text,bool editable = true)
      : WidgetC(*new TextBoxBodyC(text,editable))
    {}
    //: Constructor
    
  protected:
    TextBoxC(TextBoxBodyC &body)
      : WidgetC(body)
    {}
    //: Body constructor.
    
    TextBoxBodyC &Body() 
    { return dynamic_cast<TextBoxBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const  TextBoxBodyC &Body() const
    { return dynamic_cast<const TextBoxBodyC &>(WidgetC::Body()); }
    //: Access body.  

    bool GUIInsert(StringC &txt)
    { return Body().GUIInsert(txt); }
    //: Insert text in window.
    
  public:
    StringC Text() 
    { return Body().Text(); }
    //: Access text
    
    bool Insert(const StringC &txt)
    { return Body().Insert(txt); }
    //: Insert text at cursor
    // This is thread safe.

    friend class TextBoxBodyC;
  };

}

#endif
