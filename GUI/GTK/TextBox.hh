#ifndef GUITEXTBOX_HEADER
#define GUITEXTBOX_HEADER 1
//////////////////////////////////////////////////
//! lib=GUI
//! author="Charles Galambos"
//! date="23/03/99"
//! docentry="Ravl.GUI.Control"
//! rcsid="$Id$"

#include "amma/PThread/Mutex.hh"
#include "amma/GUI/Widget.hh"
#include "amma/String.hh"
#include "amma/DP/Signal1.hh"
#include "amma/DP/Signal2.hh"

//! userlevel=Develop
//: TextBox body

class GUITextBoxBodyC 
  : public GUIWidgetBodyC
{
public:
  GUITextBoxBodyC(const StringC &ntext,IntT nMaxLen = -1);
  //: Constructor.
  
  virtual BooleanT Create();
  //: Create the widget.
  
  virtual BooleanT Entry(const StringC &text);
  //: Some new text has been entered.
  
  virtual BooleanT Service();
  //: Service request.
  // Used to send signals from other
  // threads to the program.  
  
  StringC Text();
  //: Access text
  
  BooleanT Text(const StringC &txt);
  //: Update text.
  // This is thread safe.
  
  Signal1C<StringC> &Activate() { return activate; }
  //: Activate, called when text is changed.
  
protected:
  BooleanT SetText(const StringC &txt);
  //: Set text to edit.
  // This should only be called within the GUI thread.
  
  void SigChanged();
  //: Got a changed signal.
  
  PThread::MutexC access;
  
  StringC text; // Default text.
  IntT maxLen; // Maximum length, -1==Unset.
  
  Signal1C<StringC> activate; // Return has been pressed.
  Signal0C changed;  // Text in box has been changed.
  
};


//! userlevel=Normal
//: TextBox 
// This displays some text.

class GUITextBoxC 
  : public GUIWidgetC
{
public:
  GUITextBoxC()
    : DPEntityC(TRUE)
    {}
  //: Default constructor.
  // Creates an invalid handle.
  
  GUITextBoxC(const StringC &text,IntT nMaxLen = -1)
    : DPEntityC(*new GUITextBoxBodyC(text,nMaxLen))
    {}
  //: Constructor
  
protected:

  GUITextBoxBodyC &Body() 
    { return dynamic_cast<GUITextBoxBodyC &>(DPEntityC::Body()); }
  //: Access body.
  
  const  GUITextBoxBodyC &Body() const
    { return dynamic_cast<const GUITextBoxBodyC &>(DPEntityC::Body()); }
  //: Access body.  
  
public:
  StringC Text() 
    { return Body().Text(); }
  //: Access text
  
  BooleanT Text(const StringC &txt)
    { return Body().Text(txt); }
  //: Update text.
  // This is thread safe, with respect to the GUI thread.
  
  void SetText(StringC &txt)
    { Body().Text(txt); }
  //: Update text, for signal functions.
  // This is thread safe, with respect to the GUI thread.
  
  Signal1C<StringC> &Activate() 
    { return Body().Activate(); }
  //: Activate, called when text is changed.
  
};


#endif
