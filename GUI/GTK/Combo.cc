//////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Threads/Signal1.hh"
#include "Ravl/Threads/Signal2.hh"
#include "Ravl/GUI/Combo.hh"
#include <gtk/gtk.h>

namespace RavlGUIN {

  //: Constructor.
  
  ComboBodyC::ComboBodyC(const DListC<StringC> &nChoices,bool neditable)
    : choices(nChoices),
      editable(neditable)
  {
    signals["combo_activate"] = Signal1C<StringC>(StringC("-none-"));
  }
  
  //: Get currently selected string.
  
  StringC ComboBodyC::Selected() const { 
    return StringC(gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(widget)->entry)));
  }
  
  
  
  //: Create the widget.
  
  bool ComboBodyC::Create() {
    widget = gtk_combo_new();
    
    // gtk_list_clear_items (GTK_LIST (combo->list), 0, -1);
    
    for(DLIterC<StringC> it(choices);it.IsElm();it.Next()) {
      GtkWidget *li = gtk_list_item_new_with_label ((gchar *) it.Data().chars());
      gtk_widget_show (li);
      gtk_container_add (GTK_CONTAINER (GTK_COMBO(widget)->list), li);
      if(!editable)
	gtk_entry_set_editable(GTK_ENTRY(GTK_COMBO(widget)->entry),0);
    }
    ConnectSignals();
#if 1
    gtk_signal_connect(GTK_OBJECT(GTK_COMBO(widget)->entry), "changed",
		       GTK_SIGNAL_FUNC (WidgetBodyC::gtkString),& signals["combo_activate"]);
#endif
    
    return true;
  }
  
}
