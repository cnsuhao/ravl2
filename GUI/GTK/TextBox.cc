////////////////////////////////////////////
//! docentry="GUI"
//! rcsid="$Id$"

#include "Ravl/GUI/TextEntry.hh"
#include <gtk/gtk.h>

namespace RavlGUIN {

  
  static void enter_callback(GtkWidget *widget, GUITextBoxBodyC *entry)
  { entry->Entry(gtk_entry_get_text(GTK_ENTRY(entry->Widget()))); }
  
  
  TextBoxBodyC::TextBoxBodyC(const StringC &ntext,IntT nMaxLen)
    : GUIWidgetBodyC(true),
      text(ntext),
      maxLen(nMaxLen),
      activate(text)
  {}
  
  //: Got a changed signal.
  
  void TextBoxBodyC::SigChanged() {
    MutexLockC lock(access);
    //text = StringC(gtk_entry_get_text(GTK_ENTRY(Widget())));
  }
  
  //: Create the widget.
  
  bool TextBoxBodyC::Create() {
    //GtkAdjustment *hadj,*vadj;
    //GtkWidget *textw;
    //widget = gtk_table_new(2,2,0);
    
    widget = gtk_text_new(0,0);
    ConnectSignals();
    return true;
  }

  
  //: Access text
  
  StringC TextBoxBodyC::Text() {
    MutexLockC lock(access);
    StringC ret = text; // Ensure the right order.
    lock.Unlock();
    return ret ;
  }
  
  //: Service request.
  
  bool TextBoxBodyC::Service() {
    if(widget == 0)
      return true;
    // The only thing we know how to do, update the text.
    //gtk_entry_set_text (GTK_ENTRY (widget), text);
    return true;
  }
  
  //: Some new text has been entered.
  
  bool  TextBoxBodyC::Entry(const StringC &txt) {
    MutexLockC lock(access);
    text=txt;
    lock.Unlock();
    //  activate(txt);
    //cerr << "TextBoxBodyC::Entry(), Text:" << text << "\n";
    return true;
  }
  
  //: Update text.
  // This is thread safe.
  
  bool TextBoxBodyC::Text(const StringC &txt) {
    MutexLockC lock(access);
    //text = txt;
    lock.Unlock();
    return true;
  }
  
  //: Set text to display.
  
  bool TextBoxBodyC::SetText(const StringC &txt) {
    //gtk_entry_set_text (GTK_ENTRY (widget), text);
    return true;
  }
  
}
