// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_TEXTENTRY_HEADER
#define RAVLGUI_TEXTENTRY_HEADER 1
//////////////////////////////////////////////////
//! file="Ravl/GUI/GTK/TextEntry.hh"
//! lib=RavlGUI
//! author="Charles Galambos"
//! date="23/03/1999"
//! docentry="Ravl.GUI.Control"
//! rcsid="$Id$"

#include "Ravl/GUI/Widget.hh"
#include "Ravl/Threads/Mutex.hh"
#include "Ravl/String.hh"
#include "Ravl/Threads/Signal1.hh"
#include "Ravl/Threads/Signal2.hh"

namespace RavlGUIN {

  class TextEntryC;
  
  //! userlevel=Develop
  //: TextEntry body
  
  class TextEntryBodyC 
    : public WidgetBodyC
  {
  public:
    TextEntryBodyC(const StringC &ntext,IntT MaxLen = -1,bool sigAllChanges = false);
    //: Constructor.
    // The inital content of the entry is set to ntext.
    // If MaxLen is set to a negative number, the length is unlimited.
    
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
    
    bool HideText(const bool& hide);
    //: Hides text entered into this field
    // If the argument is true, text in this field will be displayed as *s

  protected:
    bool SetText(const StringC &txt);
    //: Set text to edit.
    // This should only be called within the GUI thread.
    
    bool GUISetText(StringC &txt);
    //: Set text to edit.
    // This should only be called within the GUI thread.
    
    bool GUIHideText(bool& hide);
    //: Hides text entered into this field
    // GUI Thread only

    bool SigChanged();
    //: Got a changed signal.
    
    bool SigActivate();
    //: Got a activate signal.
    
    MutexC access;
    
    StringC text; // Default text.
    IntT maxLen; // Maximum length, -1==Unset.
    bool sigAllChanges; // Signal all changes to text.
    bool bPasswdMode; // Use password mode

    Signal1C<StringC> activate; // Return has been pressed.
    Signal0C changed;  // Text in box has been changed.
    
    friend class TextEntryC;
  };
  

  //! userlevel=Normal
  //: Display one line of text
  
  class TextEntryC 
    : public WidgetC
  {
  public:
    TextEntryC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    TextEntryC(const StringC &text,IntT nMaxLen = -1,bool sigAllChanges = false)
      : WidgetC(*new TextEntryBodyC(text,nMaxLen,sigAllChanges))
      {}
    //: Constructor
    // The inital content of the entry is set to ntext.
    // If MaxLen is set to a negative number, the length is unlimited.
    
  protected:
    TextEntryC(TextEntryBodyC &bod)
      : WidgetC(bod)
      {}
    //: Body constructor.
    
    TextEntryBodyC &Body() 
      { return static_cast<TextEntryBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const  TextEntryBodyC &Body() const
      { return static_cast<const TextEntryBodyC &>(WidgetC::Body()); }
    //: Access body.  
    
    bool GUISetText(StringC &txt)
      { return Body().GUISetText(txt); }
    //: Set text to edit.
    // This should only be called within the GUI thread.
    
    bool GUIHideText(bool& hide)
    { return Body().GUIHideText(hide); }
    //: Hides text entered into this field
    // GUI thread only

  public:
    bool HideText(const bool& hide) 
    { return Body().HideText(hide); }
    //: Hides text entered into this field
    // If the argument is true, text in this field will be displayed as *s

    StringC Text() 
      { return Body().Text(); }
    //: Access text
    
    bool Text(const StringC &txt)
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
    
    friend class TextEntryBodyC;
  };
  
  inline 
  TextEntryC TextEntry(const StringC &def,int maxLen = -1)
  { return TextEntryC(def,maxLen); }
  //: Create a text entry.
  
  template<class DataT>
  TextEntryC TextEntry(const StringC &def,const DataT &dat,bool (DataT::*func)(StringC &ref),int maxLen = -1,bool sigAllChanges = false)
  { 
    TextEntryC ret(def,maxLen,sigAllChanges);
    Connect(ret.Activate(),dat,func);
    return ret;    
  } 

  template<class DataT>
  TextEntryC TextEntryR(const StringC &def,DataT &dat,bool (DataT::*func)(StringC &ref),int maxLen = -1,bool sigAllChanges = false)
  { 
    TextEntryC ret(def,maxLen,sigAllChanges);
    ConnectRef(ret.Activate(),dat,func);
    return ret;    
  } 
  
  template<class DataT>
  TextEntryC TextEntry(const StringC &def,bool (*func)(StringC &ref,DataT &dat),const DataT &dat,int maxLen = -1,bool sigAllChanges = false)
  {
    TextEntryC ret(def,maxLen,sigAllChanges);
    Connect(ret.Activate(),func,StringC(""),dat);
    return ret;    
  } 
}


#endif
