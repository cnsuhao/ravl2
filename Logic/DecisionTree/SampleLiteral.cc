
#include "Ravl/Logic/SampleLiteral.hh"

namespace RavlLogicN {
  
  //: Make a list of all LiteralC and sub LiteralC's in the sample.
  
  HSetC<LiteralC> SampleLiteralC::Components() const {
    HSetC<LiteralC> ret;
    for(DArray1dIterC<LiteralC> it(*this);it;it++) {
      if(!ret.Insert(*it))
	continue; // Already done.
      it->SubLiterals(ret);
    }
    return ret;
  }

}
