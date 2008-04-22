// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include "Ravl/GUI/ComboBoxText.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/ReadBack.hh"
#include <gtk/gtk.h>

namespace RavlGUIN {

  //: Constructor
  
  ComboBoxTextBodyC::ComboBoxTextBodyC()
    : m_sigSelected(StringC(""))
  {}
  
  //: Constructor
  
  ComboBoxTextBodyC::ComboBoxTextBodyC(const DListC<StringC> &options,bool editable)
    : m_options(options),
      m_editable(editable),
      m_sigSelected(StringC(""))
  {}
  
  //: Create with a widget possibly supplied from elsewhere.
  
  bool ComboBoxTextBodyC::CommonCreate(GtkWidget *nwidget) {
    if(nwidget != 0)
      nwidget = gtk_combo_box_new_text();
    
    if(!ComboBoxBodyC::CommonCreate(nwidget))
      return false;
    m_treeModel = TreeModelC(gtk_combo_box_get_model (GTK_COMBO_BOX(widget)));

    RavlAssert(widget != 0);
    for(DLIterC<StringC> it(m_options);it;it++)
      gtk_combo_box_append_text(GTK_COMBO_BOX(widget),it->chars());
    
    ConnectRef(Signal("changed"),*this,&ComboBoxTextBodyC::CBChanged);
    return true;
  }

  //: Access current selected text.
  
  StringC ComboBoxTextBodyC::GUITextSelected() {
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");    
    return StringC(gtk_combo_box_get_active_text(GTK_COMBO_BOX(widget)));
  }
  
  //: Access current selection.
  
  StringC ComboBoxTextBodyC::TextSelected() {
    ReadBackLockC lock;    
    return m_selected;
  }
  
  //: Process changed call back signals.
  
  bool ComboBoxTextBodyC::CBChanged() {
    //std::cerr << "Selection changed. \n";
    StringC selStr = GUITextSelected();
    m_selected = selStr;
    m_sigSelected(selStr);
    return true;
  }


}
