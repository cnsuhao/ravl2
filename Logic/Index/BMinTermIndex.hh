// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGIC_BMINTERMINDEX_HEADER
#define RAVLLOGIC_BMINTERMINDEX_HEADER 1
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Logic/Index/BNPIndex.hh"
//! lib=RavlLogic
//! author="Charles Galambos"
//! date="14/05/1998"
//! docentry="Logic.Index"

#include "Ravl/Logic/BLiteralIndex.hh"
#include "Ravl/Logic/MinTerm.hh"
#include "Ravl/Logic/MinTermIter.hh"

namespace RavlLogicN {
  
  template<class DataT> class BMinTermIndexIterC;
  
  //! userlevel=Normal
  //: Branching MinTerm Index.
  // This allows values to be mapped to both expressions and
  // their negations.  
  
  template<class DataT>
  class BMinTermIndexC {
  public:
    inline BMinTermIndexC()
      : pos(true),
	neg(true)
    { neg.UseIndex(pos.IdIndex()); } // Share index.
    //: Default constructor.
    
    inline BMinTermIndexC(const LiteralIndexC<IntC> &ids)
      : pos(ids), neg(ids)
    {}
    //: Construct using a given id Index.
    // Otherwise creates a new index.
    
#if 0
    inline BMinTermIndexC<DataT> DeepCopy() const
    { return BMinTermIndexC<DataT>(pos.DeepCopy(),neg.DeepCopy()); }
    //: Make a deep copy of this class.
#endif
    
    inline bool Add(bool negate,const LiteralC &lit,const DataT &data) {
      if(!negate)
	return pos.Add(lit,data);
      return neg.Add(lit,data);
    }
    //: Add data indexed on a single literal.
    // Returns true if 'lit' is a new key.
    
    inline bool Add(const MinTermC &mt,const DataT &data);
    //: Add data indexed on a minterm.
    // Returns true if 'mt' is a new key.
    
    DataT &Access(bool negate,const LiteralC &lit) 
    { return negate ? neg[lit] : pos[lit]; }
    //: Access data.
    // Lookup associated with 'lit'. If 'lit' does not
    // exist within the index it is added. The returned value
    // is created with the default constructor.
    
    inline bool IsEmpty() const
    { return pos.IsEmpty() && neg.IsEmpty(); }
    //: Is table empty ?
    
    const LiteralIndexC<IntC> &IdIndex() const { return pos.IdIndex(); }
    //: Get ID index.
    
  protected:
    inline BMinTermIndexC(const BLiteralIndexC<DataT> &npos,const BLiteralIndexC<DataT> &nneg)
      : pos(npos), neg(nneg)
    {}
    //: Make a new NPIndex from two other indexs.
    
  private:
    BLiteralIndexC<DataT> pos; // Index for positive terms.
    BLiteralIndexC<DataT> neg; // Index for negative terms.
    
    friend class BMinTermIndexIterC<DataT>;
  };

  ////////////////////////////////////////////////////////
  
  template<class DataT>
  bool BMinTermIndexC<DataT>::Add(const MinTermC &mt,const DataT &data) {
    bool ret = true;
    for(MinTermIterC it(mt);it;it++) 
      ret &= Add(it.IsNegated(),*it,data);
    return ret;
  }
  
}

#endif
