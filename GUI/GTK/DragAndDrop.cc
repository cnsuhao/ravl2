
#include "Ravl/GUI/DragAndDrop.hh"
#include <gtk/gtk.h>

namespace RavlGUIN {
  
  //: Finish drag and drop.
  // This must be called on the GUI thread.
  
  bool DNDDataInfoC::Finish(bool success,bool del) {
    RavlAssert(context != 0);
    gtk_drag_finish(context,success,del,time);
    return true;
  }
  
  // Find the GTK source widget.
  
  GtkWidget *DNDDataInfoC::GTKSourceWidget() {
    RavlAssert(context != 0);
    return gtk_drag_get_source_widget (context);
  }

  //: Is recieved data a string ?
  
  bool DNDDataInfoC::IsString() const {
    if(data == 0)
      return false;
    return (data->format == 8); // This is really a guess, but it seems to be faily standard.
  }
  
  //: Get data as string.
  // It is the user's responsibility to ensure this is appropriate.
  
  StringC DNDDataInfoC::String() {
    if(data == 0)
      return StringC();
    if(data->format != 8)
      cerr << "DNDDataInfoC::String(), WARNING: Selection may not be a string. \n";
    return StringC((char *) data->data,data->length);
  }

  //: Put a string.
  
  bool DNDDataInfoC::PutString(int dtype,const StringC &str) {
    gtk_selection_data_set (data,dtype,8, (const guchar *)str.chars(), str.Size());
    return true;
  }
  
}
