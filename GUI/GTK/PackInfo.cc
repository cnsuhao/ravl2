// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI

#include "Ravl/GUI/PackInfo.hh"

namespace RavlGUIN {

  //: Create the widget.
  
  bool PackInfoBodyC::Create() {
    if(!child.IsValid())
      return false;
    if(!child.Create())
      return false;
    widget = child.Widget();
    return true;
  }
  
  //: Undo all refrences.
  
  void PackInfoBodyC::Destroy() {
    if(child.IsValid())
      child.Destroy();
    widget = 0; // It'll be the childs widget....
    WidgetBodyC::Destroy();
  }
  
  //: Construct packing info from other widget.
  
  PackInfoC::PackInfoC(WidgetC &other)
    : OneChildC(other)
  {
    if(!dynamic_cast<const PackInfoBodyC *>(&Body()) == 0)
      Invalidate();
  }
  
}
