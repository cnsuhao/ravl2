/////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Logic/MinTermIter.hh"

namespace RavlLogicN {
  
  //: Constructor.
  
  MinTermIterC::MinTermIterC(const MinTermC &mt)
    : pos(const_cast<SArray1dC<LiteralC> &>(mt.Pos())),
      neg(const_cast<SArray1dC<LiteralC> &>(mt.Neg()))
  { First(); }
  
  //: Assign to a min term.
  
  const MinTermIterC &MinTermIterC::operator=(const MinTermC &mt) {
    pos = const_cast<SArray1dC<LiteralC> &>(mt.Pos());
    neg = const_cast<SArray1dC<LiteralC> &>(mt.Neg());
    First();
    return *this;
  }
  
  //: Goto first element.
  
  bool MinTermIterC::First() {
    it = pos;
    negated = false;
    if(!it) {
      it = neg;
      negated = true;
    }
    return it;
  }

  //: Goto next element.
  
  bool MinTermIterC::Next() {
    it++;
    if(!it) {
      if(negated)
	return false;
      it = neg;
      negated = true;
    }
    return it;
  }
  
}
