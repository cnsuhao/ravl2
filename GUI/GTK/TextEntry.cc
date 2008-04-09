// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////
//! docentry="Graphics.GTK"
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/TextEntry.cc"

#include "Ravl/GUI/TextEntry.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/ReadBack.hh"
#include <gtk/gtk.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {

  static void enter_callback(GtkWidget *widget, TextEntryBodyC *entry)
  { entry->Entry(gtk_entry_get_text(GTK_ENTRY(entry->Widget()))); }
  
  
  TextEntryBodyC::TextEntryBodyC(const StringC &ntext,IntT nMaxLen,bool nsigAllChanges,bool editable, IntT xdim,IntT ydim)
    : text(ntext),
      maxLen(nMaxLen),
      sigAllChanges(nsigAllChanges),
      bPasswdMode(false),
      activate(text),
      xsize(xdim), 
      ysize(ydim),
      isEditable(editable)
  {}
  
  //: Got a changed signal.
  
  bool TextEntryBodyC::SigChanged() {
    MutexLockC lock(access);
    text = StringC(gtk_entry_get_text(GTK_ENTRY(Widget())));
    if(sigAllChanges)
      activate(text);
    return true;
  }
  
  //: Got a activate signal.
  
  bool TextEntryBodyC::SigActivate()  {  
    ONDEBUG(cerr << "TextEntryBodyC::SigActivate() \n"); 
    MutexLockC lock(access);
    text = StringC(gtk_entry_get_text(GTK_ENTRY(Widget())));
    activate(text);
    return true;
  }
  
  //: Create the widget.
  
  bool TextEntryBodyC::Create() {
    ONDEBUG(cerr << "TextEntryBodyC::Create() MaxLen=" << maxLen << " Text='" << text << "'\n");
    if(maxLen > 0)
      widget = gtk_entry_new_with_max_length(maxLen);
    else
      widget = gtk_entry_new();
    if(!text.IsEmpty())
      gtk_entry_set_text (GTK_ENTRY (widget), text);
    GUISetUSize( xsize, ysize ) ; 
    gtk_editable_set_editable(GTK_EDITABLE(widget), isEditable) ;
    ONDEBUG(cerr << "TextEntryBodyC::Create(), Size=" << GTK_ENTRY (widget)->text_size << " Used=" << GTK_ENTRY (widget)->text_length <<" Max=" << GTK_ENTRY (widget)->text_max_length <<"\n");
    
    gtk_signal_connect(GTK_OBJECT(widget), "activate",
		       GTK_SIGNAL_FUNC(enter_callback),
		       this);
    changed = Signal("changed");
    RavlAssert(changed.IsValid());
    ConnectSignals();
    ConnectRef(changed,*this,&TextEntryBodyC::SigChanged);
    ConnectRef(Signal("activate"),*this,&TextEntryBodyC::SigActivate);

    // Set password mode if necessary
    if (bPasswdMode) GUIHideText(bPasswdMode);
    // Done
    return true;
  }
  


  bool TextEntryBodyC::Create(GtkWidget *newWidget) {
    widget = newWidget;
    gtk_signal_connect(GTK_OBJECT(widget), "activate",
		       GTK_SIGNAL_FUNC(enter_callback),
		       this);
    if(!text.IsEmpty())
      gtk_entry_set_text (GTK_ENTRY (widget), text);
    changed = Signal("changed");
    RavlAssert(changed.IsValid());
    ConnectSignals();
    ConnectRef(changed,*this,&TextEntryBodyC::SigChanged);
    ConnectRef(Signal("activate"),*this,&TextEntryBodyC::SigActivate);

    // Set password mode if necessary
    if (bPasswdMode) GUIHideText(bPasswdMode);
    // Done
    return true;
  }
  
  //: Access text
  
  StringC TextEntryBodyC::Text() const {
    MutexLockC lock(access);
    StringC ret = text; // Ensure the right order.
    lock.Unlock();
    return ret ;
  }
  
  
  //: Set text to edit.
  // This should only be called within the GUI thread.
  
  bool TextEntryBodyC::GUISetText(const StringC &txt) {
    MutexLockC lock(access);
    text=txt;
    lock.Unlock();
    if(widget == 0)
      return true;
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    gtk_entry_set_text (GTK_ENTRY (widget), text);
    return true;
  }
  
  //: Some new text has been entered.
  
  bool TextEntryBodyC::Entry(const StringC &txt) {
    MutexLockC lock(access);
    text=txt;
    lock.Unlock();
    //cerr << "TextEntryBodyC::Entry(), Text:" << text << "\n";
    return true;
  }
  
  //: Update text.
  // This is thread safe.
  
  bool TextEntryBodyC::Text(const StringC &txt) {
    Manager.Queue(Trigger(TextEntryC(*this),&TextEntryC::GUISetText,txt));
    return true;
  }
  
  //: Set text to display.
  
  bool TextEntryBodyC::SetText(const StringC &txt) {
    gtk_entry_set_text (GTK_ENTRY (widget), txt);
    return true;
  }

  bool TextEntryBodyC::GUIHideText(bool hide) {
    bPasswdMode = hide;
    if(widget == 0)
      return true;
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    gtk_entry_set_visibility (GTK_ENTRY (widget), !hide);
    return true;
  }
  
  bool TextEntryBodyC::HideText(bool hide) {
    Manager.Queue(Trigger(TextEntryC(*this),&TextEntryC::GUIHideText,hide));
    return true;
  }



  bool TextEntryBodyC::Editable() const
  {
    ReadBackLockC rbLock;
    MutexLockC lock(access);
    return gtk_editable_get_editable(GTK_EDITABLE(widget)) != 0;
  }
  
  
  
  bool TextEntryBodyC::GUISetEditable(const bool editable) 
  {
    isEditable = editable ; 
    if (widget == 0)
      return true ; 
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    gtk_editable_set_editable(GTK_EDITABLE(widget), editable) ;
    return true ; 
  }



  bool TextEntryBodyC::SetEditable(const bool editable) 
  {
    Manager.Queue(Trigger(TextEntryC(*this), &TextEntryC::GUISetEditable, editable)) ;
    return true ; 
  }



}
