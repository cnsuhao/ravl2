//////////////////////////////////////////////////
//! docentry="GUI"
//! rcsid="$Id$"

#include "Ravl/GUI/FileSelector.hh"
#include <gtk/gtk.h>

namespace RavlGUIN {

  /* Get the selected filename and print it to the console */
  static void file_ok_sel (GtkWidget *w, FileSelectorBodyC *fs) { 
    if(fs->HideOnSelect())
      fs->GUIHide(); // We're in the GUI thread.
    fs->Selected()(gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs->Widget()))); 
  }
  
  static void cancel (GtkWidget *widget, FileSelectorBodyC *fs) { 
    fs->GUIHide(); // We're in the GUI thread.
  } 
  
  //: Constructor.
  
  FileSelectorBodyC::FileSelectorBodyC(const StringC &nname,const StringC &filename)
    : name(nname),
      defaultFN(filename),
      hideOnSelect(true),
      selected(FilenameC(""))
  {}
  
  
  bool FileSelectorBodyC::Create() {
    widget = gtk_file_selection_new (name);
  
    // Connect default signal, to handle widget destructon correctly
    ConnectSignals(); 
    
    /* Connect the ok_button to file_ok_sel function */
    gtk_signal_connect (GTK_OBJECT (GTK_FILE_SELECTION (widget)->ok_button),
			"clicked", (GtkSignalFunc) file_ok_sel, this );
    
    /* Connect the cancel button to the destroyed function */
    
    gtk_signal_connect (GTK_OBJECT (GTK_FILE_SELECTION (widget)->cancel_button),
			"clicked", (GtkSignalFunc) cancel, this );
    
    /* Lets set the filename, as if this were a save dialog, and we are giving
       a default filename */
    gtk_file_selection_set_filename (GTK_FILE_SELECTION(widget), 
				     defaultFN);
    
    ConnectSignals();
    
    return true;
  }
  
  //: Dissconnect all signals.
  
  void FileSelectorBodyC::Destroy() {
    selected.DisconnectAll();
    WidgetBodyC::Destroy();
  }
}
