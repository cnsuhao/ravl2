// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUIDisplay

#include "Ravl/GUI/DPWindowOPort.hh"

namespace RavlGUIN {
  
  //: Constructor.
  
  DPWindowOPortBodyC::DPWindowOPortBodyC(DPWindowC &nwin,bool accum) 
    : accumulate(accum),
      win(nwin)
  {}
  
  //: Process in coming display objects.
  
  bool DPWindowOPortBodyC::Put(const DPDisplayObjC &newObj) {
    if(accumulate)
      win.AddObject(newObj);
    else
      win.ReplaceObject(newObj);
    return true;
  }
  
}
