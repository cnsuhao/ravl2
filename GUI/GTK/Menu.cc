// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/Menu.cc"

#include "Ravl/GUI/Menu.hh"
#include <gtk/gtk.h>

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN
{
  void MenuItemC_response ( GtkWidget *,MenuItemBodyC *data) { 
    if(data->SigSelected().IsValid())
      data->SigSelected()();
  }
  
  //: Constructor.
  
  MenuItemBodyC::MenuItemBodyC(const StringC &lab)
    : name(lab),
      selected(true)
  {}
  
  //: Create the widget.
  
  bool MenuItemBodyC::Create() {
    ONDEBUG(cerr << "MenuItemBodyC::Create(), Called. \n");
    /* Create a new menu-item with a name... */
    if(!name.IsEmpty()) {
      widget = gtk_menu_item_new_with_label(name);
      
      /* Do something interesting when the menuitem is selected */
      gtk_signal_connect(GTK_OBJECT(widget), "activate",
			 GTK_SIGNAL_FUNC(RavlGUIN::MenuItemC_response), this);
    } else { // Separator....
      widget = gtk_menu_item_new();
    }
    ONDEBUG(cerr << "MenuItemBodyC::Create(), Done. \n");
    return true;
  }
  
  //: Create with a widget supplied from elsewhere.
  
  bool MenuItemBodyC::Create(GtkWidget *newWidget) {
    widget = newWidget;
    gtk_signal_connect(GTK_OBJECT(widget), "activate",
     GTK_SIGNAL_FUNC(RavlGUIN::MenuItemC_response), this);
    ONDEBUG(cerr << "MenuItemBodyC::Create(), Done. \n");
    return true;
  }
  
  //: Undo all references.
  
  void MenuItemBodyC::Destroy() {
    ONDEBUG(cerr << "MenuItemBodyC::Destroy(), Called. \n");  
    selected.Invalidate();
    WidgetBodyC::Destroy();
  }
  
  //////////////////////////////////////////////////
  
  //: Create the widget.
  
  bool MenuBodyC::Create() {
    ONDEBUG(cerr << "MenuBodyC::Create(), Called. \n");
    widget = gtk_menu_new();
    for(DLIterC<WidgetC> it(children);it.IsElm();it.Next()) {
      if(!it.Data().Create()) 
	cerr << "MenubarBodyC::Create(), Widget create failed ! \n";
      gtk_widget_show (it.Data().Widget());
#if 1
      MenuC sm(it.Data());
      if(sm.IsValid()) {
	ONDEBUG(cerr << "Creating a sub menu. \n");
	GtkWidget *submenu = gtk_menu_item_new_with_label(sm.MenuName());
	gtk_widget_show(submenu);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(submenu),it.Data().Widget()); 
	gtk_menu_append(GTK_MENU(widget),submenu);
      } else // Assume its a menu item.
#endif
	gtk_menu_append(GTK_MENU (widget), it.Data().Widget());
    }
    ONDEBUG(cerr << "MenuBodyC::Create(), Done. \n");  
    ConnectSignals();
    return true;
  }
  
  //: Add an item to the end of the menu
  bool MenuBodyC::GUIAdd(WidgetC &widge) {
    // Call base class add
    ContainerWidgetBodyC::GUIAdd(widge);
    if (widget == 0) {
      // Append to menu
      gtk_menu_append(GTK_MENU(widget),widge.Widget());
    }
    return true;
  }


  //: Make menu popup in 'parent' at 'where'.
  
  void MenuBodyC::Popup(GdkEvent *event) {
    if(widget == 0) 
      Create();
    if(widget == 0) {
      cerr << "ERROR: Failed to create menu. \n";
      return ;
    }
    if(event != 0) {
      if (event->type == GDK_BUTTON_PRESS) {
	GdkEventButton *bevent = (GdkEventButton *) event; 
	gtk_menu_popup (GTK_MENU(Widget()), NULL, NULL, NULL, NULL,
			bevent->button, bevent->time);
	return ;
      } 
      if (event->type == GDK_MOTION_NOTIFY) {
	GdkEventMotion *bevent = (GdkEventMotion *) event; 
	gtk_menu_popup (GTK_MENU(Widget()), NULL, NULL, NULL, NULL,
			0, bevent->time);
	return ;
      } 
#if 0
      gtk_menu_popup (GTK_MENU(Widget()), NULL, NULL, NULL, NULL,
		      0, event->time);
      return ;
#endif
    }
    gtk_menu_popup (GTK_MENU(Widget()), NULL, NULL, NULL, NULL,
		    0, GDK_CURRENT_TIME);
    return ;
  }
  
  //: Create a handle from a base class.
  // This will create an invalid reference if
  // the given object is not derived from MenuC
  
  MenuC::MenuC(WidgetC &widge)
    : ContainerWidgetC(widge)
  {
    if(IsValid()) {
      if(dynamic_cast<const MenuBodyC *>(&(WidgetC::Body())) == 0)
	Invalidate();
    }
  }


  //////////////////////////////////////////////////
  
  //: Create the widget.
  
  bool MenuBarBodyC::Create() {
    ONDEBUG(cerr << "MenuBarBodyC::Create(), Called. \n");
    widget = gtk_menu_bar_new();
    
    for(DLIterC<WidgetC> it(children);it.IsElm();it.Next()) {
      if(!it.Data().Create()) 
	cerr << "MenubarBodyC::Create(), Widget create failed ! \n";
      gtk_widget_show (it.Data().Widget());
      MenuC subMenu(it.Data());
      if(subMenu.IsValid()) {
	GtkWidget *root_menu = gtk_menu_item_new_with_label(subMenu.MenuName());
	gtk_widget_show(root_menu);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu),it.Data().Widget()); 
	gtk_menu_bar_append(GTK_MENU_BAR (widget), root_menu);
      } else
	gtk_menu_bar_append(GTK_MENU_BAR (widget), it.Data().Widget());
    }
    ONDEBUG(cerr << "MenuBarBodyC::Create(), Done. \n");  
    return true;
  }
  
  // This will always be invoked by the GUI thread.
  static bool MenuShowWidget(MenuItemC &,WidgetC &ref) { 
    ref.GUIShow(); 
    return true;
  }
  
  //: Function which invokes to show method of a widget.
  MenuItemC MenuItemShow(const StringC &label,const WidgetC &widge) { 
    return MenuItem(label,MenuShowWidget,widge); 
  }
  
  MenuItemC MenuItem(const StringC &label,bool (*func)()) {
    MenuItemC ret(label);
    Connect(ret.SigSelected(),func);
    return ret;
  }
  //: Simply call a function.
  
}
