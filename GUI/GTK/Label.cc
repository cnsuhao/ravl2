// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/Label.cc"

#include "Ravl/GUI/Label.hh"
#include "Ravl/GUI/Manager.hh"
#include <gtk/gtk.h>

namespace RavlGUIN  {

  //: Constructor.
  
  LabelBodyC::LabelBodyC(const StringC &ntext)
    : text(ntext.Copy()),
      lineWrap(false),
      justification(0)
  {}
  
  StringC LabelBodyC::Name() const
  { return text; }
  
  //: Create the widget.
  
  bool LabelBodyC::Create() {
    if(widget != 0)
      return true;
    widget = gtk_label_new (text);
    if(lineWrap)
      gtk_label_set_line_wrap (GTK_LABEL(widget),lineWrap);
    if(justification != 0)
      gtk_label_set_justify (GTK_LABEL(widget),(GtkJustification) justification);
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
  
  bool LabelBodyC::GUIJustify(GtkJustification& justify) {
    justification = (IntT) justify;
    if(widget != 0) // Maybe on shutdown ?
      gtk_label_set_justify (GTK_LABEL(widget),justify);
    return true;
  }

  bool LabelBodyC::Justify(GtkJustification& justify) {
    Manager.Queue(Trigger(LabelC(*this),&LabelC::GUIJustify,justify));
    return true;
  }
  
  bool LabelBodyC::GUIWrap(bool& wrap) {
    lineWrap = wrap;
    if(widget != 0) // Maybe on shutdown ?
      gtk_label_set_line_wrap (GTK_LABEL(widget),wrap);
    return true;    
  }

  bool LabelBodyC::Wrap(bool& wrap) {
    Manager.Queue(Trigger(LabelC(*this),&LabelC::GUIWrap,wrap));
    return true;
  }


}
