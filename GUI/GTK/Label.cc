////////////////////////////////////////////
//! docentry="GUI"
//! rcsid="$Id$"

#include "Ravl/GUI/Label.hh"
#include "Ravl/GUI/Manager.hh"
#include <gtk/gtk.h>

namespace RavlGUIN  {
  
  StringC LabelBodyC::Name() const
  { return text; }

  //: Create the widget.
  
  bool LabelBodyC::Create() {
    if(widget != 0)
      return true;
    widget = gtk_label_new (text);
    ConnectSignals();
    return true;
  }
  
  //: Set label.
  
  bool LabelBodyC::GUISetLabel(StringC &txt) {
    text = txt;
    if(widget != 0) // Maybe on shutdown ?
      gtk_label_set (GTK_LABEL(widget),text);
    return true;
  }
  
  //: Update the text in the label.
  
  bool LabelBodyC::Label(const StringC &txt) {
    Manager.Queue(Trigger(LabelC(*this),&LabelC::GUISetLabel,txt));
    return true;
  }
  
}
