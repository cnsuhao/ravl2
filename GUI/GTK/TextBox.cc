// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////
//! docentry="GUI"
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/TextBox.cc"

#include "Ravl/GUI/TextBox.hh"
#include "Ravl/GUI/Manager.hh"
#include <gtk/gtk.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x) 
#endif

namespace RavlGUIN {
  
  //static void enter_callback(GtkWidget *widget, GUITextBoxBodyC *entry)
  //{ entry->Entry(gtk_entry_get_text(GTK_ENTRY(entry->Widget()))); }
  
  
  TextBoxBodyC::TextBoxBodyC(const StringC &ntext,bool neditable)
    : text(ntext),
      editable(neditable)
  {}
  
  //: Create the widget.
  
  bool TextBoxBodyC::Create() {
    ONDEBUG(cerr << "TextBoxBodyC::Create(), Called. \n");
    if(widget != 0)
      return true; // Done already.
    widget = gtk_text_new(0,0);
    gtk_text_insert(GTK_TEXT(widget),
		    widget->style->font,
		    &widget->style->black, 
		    &widget->style->white,
		    text.chars(),text.length());
    gtk_text_set_editable(GTK_TEXT(widget),editable);
    ConnectSignals();
    return true;
  }

  
  //: Access text
  
  StringC TextBoxBodyC::Text() {
    //MutexLockC lock(access);
    StringC ret = text; // Ensure the right order.
    //lock.Unlock();
    return ret ;
  }

  //: Update text.
  // This is thread safe.
  
  bool TextBoxBodyC::Insert(const StringC &txt) {
    StringC tmp(txt);
    Manager.Queue(Trigger(TextBoxC(*this),&TextBoxC::GUIInsert,tmp));
    return true;
  }
  
  //: Insert text in window.
  
  bool TextBoxBodyC::GUIInsert(StringC &txt) {
    gtk_text_insert(GTK_TEXT(widget),
		    widget->style->font,
		    &widget->style->black, 
		    &widget->style->white,
		    txt.chars(),txt.length());    
    return true;
  }
  
  
}
