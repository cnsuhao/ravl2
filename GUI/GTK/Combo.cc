// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/Combo.cc"

#include "Ravl/Threads/Signal1.hh"
#include "Ravl/Threads/Signal2.hh"
#include "Ravl/GUI/Combo.hh"
#include "Ravl/GUI/Manager.hh"
#include <gtk/gtk.h>

namespace RavlGUIN {

  //: Constructor.
  
  ComboBodyC::ComboBodyC(const DListC<StringC> &nChoices,bool neditable)
    : choices(nChoices),
      editable(neditable),
      allowsignals(true),
      sigSelected(StringC())
  {
    signals["combo_activate"] = Signal1C<StringC>(StringC("-none-"));
    ConnectRef(signals["combo_activate"],*this,&ComboBodyC::FilterSignal);
  }
  
  //: Get currently selected string.
  
  StringC ComboBodyC::Selected() const { 
    return StringC(gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(widget)->entry)));
  }
  
  //: Add new entry to combo list.
  
  bool ComboBodyC::AddEntry(StringC &opt) {
    Manager.Queue(Trigger(ComboC(*this),&ComboC::GUIAddEntry,opt));
    return true;
  }
  
  //: Add new entry to combo list.
  
  bool ComboBodyC::DelEntry(StringC &opt) {
    Manager.Queue(Trigger(ComboC(*this),&ComboC::GUIDelEntry,opt));
    return true;
  }
  
  //: Add new entry to combo list.
  // Call on the GUI thread only.
  
  bool ComboBodyC::GUIAddEntry(StringC &opt) {
    choices.InsLast(opt);
    if(widget == 0)
      return true;
    GtkWidget *li = gtk_list_item_new_with_label ((gchar *) opt.chars());
    cmap[opt] = li;
    // Disable signals
    allowsignals = false;
    // Add widget
    gtk_widget_show (li);
    gtk_container_add (GTK_CONTAINER (GTK_COMBO(widget)->list), li);
    // Re-enable signals
    allowsignals = true;
    // Done
    return true;
  }
  
  //: Add new entry to combo list.
  // Call on the GUI thread only.
  
  bool ComboBodyC::GUIDelEntry(StringC &opt) {
    RavlAssertMsg(0,"ComboBodyC::GUIDelEntry(), Not implemented. ");
    GtkWidget *li;
    if(!cmap.Lookup(opt,li))
      return true; // item not in list.
    cmap.Del(opt);
    // Disable signals
    allowsignals = false;
    // Remove widget
    gtk_widget_hide((GtkWidget *) li);
    gtk_container_remove (GTK_CONTAINER (GTK_COMBO(widget)->list), li);
    // Re-enable signals
    allowsignals = true;
    // Done
    return true;
  }

  //: Set selection string.
  
  bool ComboBodyC::SetSelection(StringC &opt) {
    Manager.Queue(Trigger(ComboC(*this),&ComboC::GUISetSelection,opt));
    return true;
  }
  
  //: Set selection string.
  
  bool ComboBodyC::GUISetSelection(StringC &opt) {
    if(widget == 0) {
      selection = opt;
      return false;
    }
    gtk_entry_set_text (GTK_ENTRY (GTK_COMBO(widget)->entry), opt.chars());
    return true;
  }
  
  //: Test if an entry exists.
  // Call from the GUI thread only.
  
  bool ComboBodyC::GUIEntryExists(const StringC &entry) {
    return cmap.IsElm(entry);
  }
  
  //: Create the widget.
  
  bool ComboBodyC::Create() {
    widget = gtk_combo_new();
    
    // gtk_list_clear_items (GTK_LIST (combo->list), 0, -1);
    
    for(DLIterC<StringC> it(choices);it.IsElm();it.Next()) {
      GtkWidget *li = gtk_list_item_new_with_label ((gchar *) it.Data().chars());
      gtk_widget_show (li);
      gtk_container_add (GTK_CONTAINER (GTK_COMBO(widget)->list), li);
      cmap[*it] = li;
      if(!editable)
	gtk_entry_set_editable(GTK_ENTRY(GTK_COMBO(widget)->entry),0);
    }
    if(!selection.IsEmpty())
      gtk_entry_set_text (GTK_ENTRY (GTK_COMBO(widget)->entry), selection.chars());
    
    ConnectSignals();
#if 1
    gtk_signal_connect(GTK_OBJECT(GTK_COMBO(widget)->entry), "changed",
		       GTK_SIGNAL_FUNC (WidgetBodyC::gtkString),& signals["combo_activate"]);
#endif
    
    return true;
  }
  
  bool ComboBodyC::FilterSignal(StringC &sel) {
    if (allowsignals) {
      // Send signal
      sigSelected(sel);
    }
    return true;
  }

}
