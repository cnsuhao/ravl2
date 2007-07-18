
#include "Ravl/GUI/IconView.hh"
#include "Ravl/GUI/Manager.hh"
#include  <gtk/gtk.h>

namespace RavlGUIN {
  
  //: Constructor.
  
  IconViewBodyC::IconViewBodyC(const TreeModelC &treeModel,UIntT textColumn,UIntT pixbufColumn,UIntT itemWidth)
    : m_treeModel(treeModel),
      m_textColumn(textColumn),
      m_pixbufColumn(pixbufColumn),
      m_iconWidth(itemWidth)
  {}
  
  
  //: Create widget.
  
  bool IconViewBodyC::Create() {
#ifdef GTK_TYPE_ICON_VIEW
    widget = gtk_icon_view_new_with_model (m_treeModel.TreeModel());
    
    gtk_icon_view_set_text_column (GTK_ICON_VIEW(widget),m_textColumn);
    gtk_icon_view_set_pixbuf_column (GTK_ICON_VIEW(widget),m_pixbufColumn);
    
    if(m_iconWidth > 0)
      gtk_icon_view_set_item_width    (GTK_ICON_VIEW(widget),m_iconWidth);
    
    // Finalise widget
    
    ConnectSignals();
#else
    RavlAssertMsg(0,"Not supported. ");
#endif
    
    return true;
  }
  
  //: Create with a widget supplied from elsewhere.
  
  bool IconViewBodyC::Create(GtkWidget *_widget) {
    
    widget = _widget;
    
#ifdef GTK_TYPE_ICON_VIEW
    gtk_icon_view_set_model (GTK_ICON_VIEW(widget),m_treeModel.TreeModel());
    gtk_icon_view_set_text_column (GTK_ICON_VIEW(widget),m_textColumn);
    gtk_icon_view_set_pixbuf_column (GTK_ICON_VIEW(widget),m_pixbufColumn);
    
    if(m_iconWidth > 0)
      gtk_icon_view_set_item_width    (GTK_ICON_VIEW(widget),m_iconWidth);
#else
    RavlAssertMsg(0,"Not supported. ");
#endif
    
    // Finalise widget
    
    ConnectSignals();
    
    return true;
  }

  
  static void  listSelected(GtkIconView *icon_view,
                            GtkTreePath *path,
                            Tuple2C<DListC<TreeModelIterC>,GtkTreeModel * > *results) 
  {
    results->Data1().InsLast(TreeModelIterC(results->Data2(),path));
  }
  
  //: Get list of selected rows.
  
  DListC<TreeModelIterC> IconViewBodyC::GUISelected() {
    DListC<TreeModelIterC> ret;
    
    if(widget == 0)
      return ret; // Not created yet!.
    
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    
    Tuple2C<DListC<TreeModelIterC>,GtkTreeModel * > selectData(ret,m_treeModel.TreeModel());
    
#ifdef GTK_TYPE_ICON_VIEW
    gtk_icon_view_selected_foreach (GTK_ICON_VIEW(widget),
                                    (GtkIconViewForeachFunc) &listSelected,
                                    (gpointer) &selectData);
#else
    RavlAssertMsg(0,"Not supported. ");
#endif
    
    // Done
    return ret;
  }
  
  
}
