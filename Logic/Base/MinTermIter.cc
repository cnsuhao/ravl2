/////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Logic/MinTermIter.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlLogicN {
  
  //: Constructor.
  
  MinTermIterC::MinTermIterC(const MinTermC &mt) {
    if(!mt.IsValid())
      return ;
    pos = const_cast<SArray1dC<LiteralC> &>(mt.Pos());
    neg = const_cast<SArray1dC<LiteralC> &>(mt.Neg());
    ONDEBUG(cerr << "MinTermIterC::MinTermIterC(), Mt=" << mt.Name() << "\n");
    First(); 
  }
  
  //: Assign to a min term.
  
  const MinTermIterC &MinTermIterC::operator=(const MinTermC &mt) {
    ONDEBUG(cerr << "MinTermIterC::operator=(), Mt=" << mt.Name() << "\n");
    pos = const_cast<SArray1dC<LiteralC> &>(mt.Pos());
    neg = const_cast<SArray1dC<LiteralC> &>(mt.Neg());
    First();
    return *this;
  }
  
  //: Goto first element.
  
  bool MinTermIterC::First() {
    it = pos;
    RavlAssert(it);
    it++;
    negated = false;
    if(!it) {
      it = neg;
      RavlAssert(it);
      it++;
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
      RavlAssert(it);
      it++;
      negated = true;
    }
    return it;
  }
  
}
