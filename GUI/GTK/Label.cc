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
//! file="Ravl/GUI/GTK/Label.cc"

#include "Ravl/GUI/Label.hh"
#include "Ravl/GUI/Manager.hh"
#include <gtk/gtk.h>

namespace RavlGUIN  {
  
  StringC LabelBodyC::Name() const
  { return text; }

  //: Create the widget.
  
  bool LabelBodyC::Create() {
    if(widget != 0)
      return true;
    widget = gtk_label_new (text);
    ConnectSignals();
    return true;
  }
  
  //: Set label.
  
  bool LabelBodyC::GUISetLabel(StringC &txt) {
    text = txt;
    if(widget != 0) // Maybe on shutdown ?
      gtk_label_set (GTK_LABEL(widget),text);
    return true;
  }
  
  //: Update the text in the label.
  
  bool LabelBodyC::Label(const StringC &txt) {
    Manager.Queue(Trigger(LabelC(*this),&LabelC::GUISetLabel,txt));
    return true;
  }
  
}
