////////////////////////////////////////////
//! docentry="GUI"
//! rcsid="$Id$"

#include "amma/GUI/TextEntry.hh"
#include <gtk/gtk.h>

using namespace PThread;
using namespace StdDP;

static void enter_callback(GtkWidget *widget, GUITextBoxBodyC *entry)
{ entry->Entry(gtk_entry_get_text(GTK_ENTRY(entry->Widget()))); }


GUITextBoxBodyC::GUITextBoxBodyC(const StringC &ntext,IntT nMaxLen)
  : GUIWidgetBodyC(TRUE),
    text(ntext),
    maxLen(nMaxLen),
    activate(text)
{}

//: Got a changed signal.

void GUITextBoxBodyC::SigChanged() {
  MutexLockC lock(access);
  //text = StringC(gtk_entry_get_text(GTK_ENTRY(Widget())));
}

//: Create the widget.

BooleanT GUITextBoxBodyC::Create()
{
  //GtkAdjustment *hadj,*vadj;
  //GtkWidget *textw;
  //widget = gtk_table_new(2,2,0);
  
  widget = gtk_text_new(0,0);
  
  ConnectSignals();
  return TRUE;
}

//: Access text

StringC GUITextBoxBodyC::Text() {
  MutexLockC lock(access);
  StringC ret = text; // Ensure the right order.
  lock.Unlock();
  return ret ;
}

//: Service request.

BooleanT GUITextBoxBodyC::Service()
{
  if(widget == 0)
    return TRUE;
  // The only thing we know how to do, update the text.
  //gtk_entry_set_text (GTK_ENTRY (widget), text);
  return TRUE;
}

//: Some new text has been entered.

BooleanT  GUITextBoxBodyC::Entry(const StringC &txt)
{
  MutexLockC lock(access);
  text=txt;
  lock.Unlock();
  //  activate(txt);
  //cerr << "GUITextBoxBodyC::Entry(), Text:" << text << "\n";
  return TRUE;
}

//: Update text.
// This is thread safe.

BooleanT GUITextBoxBodyC::Text(const StringC &txt)
{
  MutexLockC lock(access);
  //text = txt;
  lock.Unlock();
  return TRUE;
}

//: Set text to display.

BooleanT GUITextBoxBodyC::SetText(const StringC &txt)
{
  //gtk_entry_set_text (GTK_ENTRY (widget), text);
  return TRUE;
}
