/////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/PThread/EventHandler.hh"
#include "amma/PThread/EventHandlerRef.hh" // Include here so its checked...
#include <iostream.h>

namespace PThread
{

  void SignalEventBodyC::Invoke()
  { cerr << "WARNING: Abstract method called : SignalEventBodyC::Invoke() \n"; }
  
  //: Process event queue.
  // returns the number of events handled.
  
  int SignalEventHandlerC::Process(int maxHandle) {
    int ret = 0;
    if(maxHandle <= 0) { // Unlimited ?
      for(;events.IsElm();ret++) {
	SignalEventC se(events.Get());
	if(!se.IsValid()) {
	  cerr << "ERROR: SignalEventHandlerC::Process(), ask to process an invalid event.\n";
	  continue;
	}
	se.Invoke();
      }
    } else {
      for(;events.IsElm() && (maxHandle-- > 0);ret++) {
	SignalEventC se(events.Get());
	if(!se.IsValid()) {
	  cerr << "ERROR: SignalEventHandlerC::Process(), ask to process an invalid event.\n";
	  continue;
	}
	se.Invoke();
      }
    }
    return ret;
  }

};
