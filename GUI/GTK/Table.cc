//////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/Table.hh"
#include <gtk/gtk.h>

namespace RavlGUIN {

  //: Add object to table.
  
  bool TableBodyC::AddObject(const WidgetC &widge,
			     UIntT left_attach,UIntT right_attach,
			     UIntT top_attach,UIntT bottom_attach,
			     GtkAttachOptions nxoptions,GtkAttachOptions nyoptions,
			     UIntT nxpadding,UIntT nypadding)
  {
    children.InsLast(WidgeInfoC(widge,left_attach,right_attach,top_attach,bottom_attach,
				nxoptions,nyoptions,
				nxpadding,nypadding));
    return true;
  }

  //: Create widget.
  
  bool TableBodyC::Create() {
    widget = gtk_table_new(sx,sy,homogeneous);
    for(DLIterC<WidgeInfoC> it(children);it.IsElm();it.Next()) {
      if(it.Data().widge.Widget() == 0) {
	if(!it.Data().widge.Create()) {
	  cerr << "TableBodyC::Create(), Widget create failed. \n";
	  return false;
	}
      }
      //cerr << "TableBodyC::Create(), Making entry " << it.Data().widge.WidgetName()<< "\n";
      gtk_table_attach(GTK_TABLE(widget),
		       it.Data().widge.Widget(),
		       it.Data().left_attach,it.Data().right_attach,
		       it.Data().top_attach,it.Data().bottom_attach,
		       it.Data().xoptions,it.Data().yoptions,
		       it.Data().xpadding,it.Data().ypadding);
      gtk_widget_show (it.Data().widge.Widget());
    }
    ConnectSignals();
    return true;
  }
  
  //: Undo all refrences.
  
  void TableBodyC::Destroy() {
    for(DLIterC<WidgeInfoC> it(children);it.IsElm();it.Next()) 
      it.Data().widge.Destroy();
    WidgetBodyC::Destroy();
  }
  
}
