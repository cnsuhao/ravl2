#ifndef RAVL_INDEXRANGE2DITER_HEADER
#define RAVL_INDEXRANGE2DITER_HEADER 1
//! rcsid="$Id$"
//! author="Charles Galambos"
//! docentry="Ravl.Core.Indexing"

#include "Ravl/IndexRange2d.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: Iterate through a 2d range.
  // Note: This is NOT as fast as the usual nested
  // for loop. It does allow cleaner, and more readable
  // code.
  
  class IndexRange2dIterC {
  public:
    IndexRange2dIterC()
    {}
    //: Default constructor.

    IndexRange2dIterC(const IndexRange2dC &rng)
      : range(rng)
    { First(); }
    //:  Construct from an index range.
    
    bool First() {
      at = range.Origin();
      return true;
    }
    //: Goto first index.
    
    const Index2dC &Data() const
    { return at; }
    //: Access current position.
    
    const Index2dC &operator*() const
    { return at; }
    //: Access current position.

    const Index2dC *operator->() const
    { return &at; }
    //: Access current position.
    
    bool Next() {
      if(++at.Col() <= range.RCol())
	return true;
      at.Col() = range.LCol();
      at.Row()++;
      return false;
    }
    //: Goto next index.
    // Returns true if on the same line.
    
    void operator++(int)
    { Next(); }
    //: Goto next index.
    
    bool IsElm() const
    { return at.Row() <= range.BRow(); }
    //: At a valid index in rectangle ?
    
    operator bool() const
    { return IsElm(); }
    //: At a valid index in rectangle ?
    
    const IndexRange2dC &Frame() const
    { return range; }
    //: Access the frame we're iterating.
    
    IndexRange2dC &Frame()
    { return range; }
    //: Access the frame we're iterating.
    
  protected:
    Index2dC at;
    IndexRange2dC range;
  };
}


#endif
