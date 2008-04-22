#ifndef RAVLGUI_COMBOBOXENTRY_HEADER
#define RAVLGUI_COMBOBOXENTRY_HEADER 1

#include "Ravl/GUI/ComboBox.hh"
#include "Ravl/GUI/TextEntry.hh"

namespace RavlGUIN {
  
  //! userlevel=Normal
  //: Combo box with text entry.
  
  class ComboBoxEntryBodyC
    : public ComboBoxBodyC
  {
  public:
    ComboBoxEntryBodyC();
    //: Constructor
    
    ComboBoxEntryBodyC(TreeModelC &treeModel,UIntT textColumn);
    //: Constructor
    
    TextEntryC &TextEntry()
    { return m_textEntry; }
    //: Access text entry.
    
  protected:
    virtual bool CommonCreate(GtkWidget *widget);
    //: Create with a widget possibly supplied from elsewhere.
    
    TextEntryC m_textEntry; // Text entry.
    UIntT m_textColumn; // Text column in the tree store.
  };
  
  //! userlevel=Normal
  //: Combo box with text entry.
  
  class ComboBoxEntryC
    : public ComboBoxC
  {
  public:
    ComboBoxEntryC()
    {}
    //: Default constructor
    
    ComboBoxEntryC(TreeModelC &treeModel,UIntT textColumn)
      : ComboBoxC(new ComboBoxEntryBodyC(treeModel,textColumn))
    {}
    //: Constructor
    
  protected:
    ComboBoxEntryC(const ComboBoxEntryBodyC *body)
      : ComboBoxC(body)
    {}
    //: Body Constructor
    
    ComboBoxEntryBodyC &Body()
    { return dynamic_cast<ComboBoxEntryBodyC &>(WidgetC::Body()); }
    //: Body access.
    
    const ComboBoxEntryBodyC &Body() const
    { return dynamic_cast<const ComboBoxEntryBodyC &>(WidgetC::Body()); }
    //: Body access.
 
  public:
    TextEntryC &TextEntry()
    { return Body().TextEntry(); }
    //: Access text entry.
    
  };

  
}

#endif
