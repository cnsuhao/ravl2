#ifndef RAVLGUISIGNALINFO_HEADER
#define RAVLGUISIGNALINFO_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Develop
//! file="Ravl/GUI/GTK/SignalInfo.hh"
//! lib=GUI
//! userlevel=Advanced
//! docentry="Ravl.GUI.Internal"
//! author="Charles Galambos"
//! date="23/09/99"

//**** This header is for internal use ONLY ******

#include "Ravl/GUI/GTKTypes.hh"
#include <gtk/gtk.h>

namespace RavlGUIN {
  //: Signal types.
  
  enum SignalTypeT
  {
    SigTypeUnknown,
    SigTypeGeneric,
    SigTypeEvent,
    SigTypeEventMouseButton,
    SigTypeEventMouseMotion,
    SigTypeString,
    SigTypeCListSel,
    SigTypeCListCol
  };
  
  //: Signal info
  
  struct GTKSignalInfoC {
    GTKSignalInfoC()
      : name(0)
      {}
    //: Constructor to ensure name defaults to 0.
    
    GTKSignalInfoC(const char *nname,GtkSignalFunc nfunc,SignalTypeT nsignalType)
      : name(nname),
	func(nfunc),
	signalType(nsignalType)
      {}
    //: Constructor.
    
    const char *name;
    GtkSignalFunc func;
    SignalTypeT signalType;
  };

}
#endif
