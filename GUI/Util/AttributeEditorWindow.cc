// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGUIUtil
//! file="Ravl/GUI/Util/AttributeEditorWindow.cc"

#include "Ravl/GUI/AttributeEditorWindow.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/GUI/Button.hh"
#include "Ravl/GUI/Frame.hh"

namespace RavlGUIN {
  
  //: Constructor.
  
  AttributeEditorWindowBodyC::AttributeEditorWindowBodyC(const StringC &name,const AttributeCtrlC &ctrl)
    : WindowBodyC(100,100,name,GTK_WINDOW_TOPLEVEL,4,false),
      editor(ctrl)
  {
    Add(VBox(editor + RavlGUIN::ButtonR("Close",(WidgetBodyC &)*this,&WindowBodyC::GUIHide)));
  }
  
}
