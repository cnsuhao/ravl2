/////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"

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
