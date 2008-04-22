// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_COMBOBOXTEXT_HEADER
#define RAVLGUI_COMBOBOXTEXT_HEADER
//! docentry="Ravl.API.Graphics.GTK.Control"
//! author="Charles Galambos"
//! date="21/04/2008"

#include "Ravl/GUI/ComboBox.hh"
#include "Ravl/DList.hh"
#include "Ravl/Threads/Mutex.hh"

namespace RavlGUIN {
  
  //! userlevel=Develop
  //: Combo box body.
  
  class ComboBoxTextBodyC
    : public ComboBoxBodyC
  {
  public:
    ComboBoxTextBodyC();
    //: Constructor
    
    ComboBoxTextBodyC(const DListC<StringC> &options,bool editable = true);
    //: Constructor
    
    Signal1C<StringC> &SigTextSelected()
    { return m_sigSelected; }
    //: Short cut clicked signal.
    
    StringC GUITextSelected();
    //: Access current selected text.
    
    StringC TextSelected();
    //: Access current selection.
    
  protected:
    
    bool CommonCreate(GtkWidget *widget);
    //: Create with a widget possibly supplied from elsewhere.
    
    bool CBChanged();
    //: Process changed call back signals.
    
    DListC<StringC> m_options; //: List of preset options.
    bool m_editable;
    
    Signal1C<StringC> m_sigSelected; //: Sig selected for compatibility with old ComboC code.
    
    StringC m_selected;
  };
  

  //! userlevel=Normal
  //: Combo box body.
  
  class ComboBoxTextC
    : public ComboBoxC
  {
  public:
    ComboBoxTextC()
    {}
    //: Default constructor
    // Creates an invalid handle.
    
    ComboBoxTextC(const DListC<StringC> &options,bool editable = true)
      : ComboBoxC(new ComboBoxTextBodyC(options,editable))
    {}
    //: Constructor
    
  protected:
    ComboBoxTextC(const ComboBoxTextBodyC *body)
      : ComboBoxC(body)
    {}
    //: Body constructor
    
    ComboBoxTextBodyC &Body()
    { return dynamic_cast<ComboBoxTextBodyC &>(WidgetC::Body()); }
    //: Body access.
    
    const ComboBoxTextBodyC &Body() const
    { return dynamic_cast<const ComboBoxTextBodyC &>(WidgetC::Body()); }
    //: Body access.
    
  public:
    StringC GUITextSelected()
    { return Body().GUITextSelected(); }
    //: Access current selected text.
    
    StringC TextSelected()
    { return Body().TextSelected(); }
    //: Access current selection.
    
    Signal1C<StringC> &SigTextSelected()
    { return Body().SigTextSelected(); }
    //: Short cut clicked signal.

  };

}

#endif
