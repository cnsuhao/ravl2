// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI

#include "Ravl/Threads/Signal1.hh"
#include "Ravl/Threads/Signal2.hh"
#include "Ravl/GUI/List.hh"
#include "Ravl/CDLIter.hh"
#include "Ravl/GUI/Label.hh"
#include "Ravl/GUI/Manager.hh"
#include <gtk/gtk.h>

namespace RavlGUIN {

  static char *ListItemKey = "ListDataKey";
  
#if 0
  static int list_activate(GtkWidget *widget,Signal0C *data) {
    cerr << "Got list_activate. \n";
    Signal1C<StringC> sig(*data);
    sig(StringC(gtk_entry_get_text(GTK_ENTRY(widget))));
    return 1;
  }
#endif
  
  //: Constructor.
  
  ListBodyC::ListBodyC(const DListC<StringC> &nChoices,GtkSelectionMode nSelMode)
    : selMode(nSelMode)
  {
    //signals["list_activate"] = Signal1C<StringC>("-none-");
    for(ConstDLIterC<StringC> it(nChoices);it.IsElm();it.Next()) 
      Add(it.Data());
  }
  
  //: Constructor from a list of strings.
  
  ListBodyC::ListBodyC(const DListC<WidgetC> &lst,GtkSelectionMode nSelMode)
    : children(lst),
      selMode(nSelMode)    
  {}
  
  ListBodyC::ListBodyC(GtkSelectionMode nSelMode)
    : selMode(nSelMode)
  {
    //signals["list_activate"] = Signal1C<StringC>("-none-");  
  }

  //: Get currently selected string.
  
  DListC<StringC> ListBodyC::Selected() const {
    DListC<StringC> ret; 
    GList   *dlist=GTK_LIST(widget)->selection;
    
    /* Get the list item from the doubly linked list
     * and then query the data associated with list_item_data_key.
     * We then just print it */
    while (dlist) {
      GtkObject       *list_item;
      gchar           *item_data_string;
      
      list_item=GTK_OBJECT(dlist->data);
      item_data_string=(gchar *)gtk_object_get_data(list_item,
						    ListItemKey);    
      ret.InsLast(StringC(item_data_string));
      dlist=dlist->next;
    }
    return ret;
  }
  
  //: Add new widget to list.
  
  void ListBodyC::Add(WidgetC &widge) {
    Manager.Queue(Trigger(ListC(*this),&ListC::GUIAdd,widge));
  }
  
  //: Del string from list.
  
  void ListBodyC::Del(const StringC &text) {
    Manager.Queue(Trigger(ListC(*this),&ListC::GUIDelS,const_cast<StringC &>(text)));
  }
  
  //: Del widget from list.
  
  void ListBodyC::Del(WidgetC &widge) {
    Manager.Queue(Trigger(ListC(*this),&ListC::GUIDel,widge));
  }
  
  
  //: Add new string to window.
  
  void ListBodyC::Add(const StringC &text)  { 
    LabelC lab(text);
    Add(lab);
  }
  
  //: Add new widget to list.
  
  bool ListBodyC::GUIAdd(WidgetC &widge) {
    if(Widget() == 0) { // List created yet ?
      children.InsLast(widge);
      return true;
    }
    widge.GUIShow();
    gtk_widget_show(widge.Widget());
    GtkWidget *li = gtk_list_item_new();
    gtk_container_add(GTK_CONTAINER(li), widge.Widget());
    gtk_object_set_data(GTK_OBJECT(li),
			ListItemKey,
			(void *) widge.Name().chars());
    
#if 1
    gtk_container_add (GTK_CONTAINER (widget), li);
#else
    GList *dlist = 0;
    dlist = g_list_prepend(dlist,li);
    gtk_list_append_items(GTK_LIST(widget), dlist);
    // Free list ???
#endif
    gtk_widget_show (li);
    cerr << "Added " << widge.Name() << "\n";
    return true;
  }
  
  
  //: Del string from list.
  
  bool ListBodyC::GUIDelS(StringC &text) {
    cerr << "ListBodyC::GUIDel(const StringC &), Not implemented \n";
    return true;
  }
  
  //: Del widget from list.
  
  bool ListBodyC::GUIDel(WidgetC &widge) {
    cerr << "ListBodyC::GUIDel(WidgetC&), Not implemented. \n";
    return true;
  }
  
  //: Create the widget.
  
  bool ListBodyC::Create() {
    if(widget != 0)
      return true; // Done already!
    
    widget = gtk_list_new();
    gtk_list_set_selection_mode(GTK_LIST(widget),selMode);  
    for(DLIterC<WidgetC> it(children);it.IsElm();it.Next())
      GUIAdd(it.Data());
    //gtk_signal_connect(GTK_OBJECT(GTK_COMBO(widget)->entry), "changed",
    //GTK_SIGNAL_FUNC (combo_activate),& signals["combo_activate"]);
    ConnectSignals();
    return true;
  }
  
  //: Undo all refrences.
  
  void ListBodyC::Destroy()  {
    for(DLIterC<WidgetC> it(children);it.IsElm();it.Next())
      it.Data().Destroy();
    WidgetBodyC::Destroy();
  }

}

