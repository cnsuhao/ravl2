// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_MINTERMLISTINDEX_HEADER
#define RAVL_MINTERMLISTINDEX_HEADER 1
////////////////////////////////////////////////////
//! userlevel=Normal
//! rcsid="$Id$"
//! file="Ravl/Logic/Index/BNPListIndex.hh"
//! lib=RavlLogic
//! author="Charles Galambos"
//! date="14/05/1998"
//! docentry="Logic.Index"

#include "Ravl/Logic/BMinTermIndex.hh"
#include "Ravl/Logic/MinTermIter.hh"
#include "Ravl/Logic/Not.hh"
#include "Ravl/Logic/Or.hh"
#include "Ravl/BList.hh"

namespace RavlLogicN {
  
  //! userlevel=Normal
  //: This is a specialisation of VLNPIndex. 
  // Used in the Non-linear planner, but put
  // here in case it's usefull elsewhere.
  
  template <class DataT>
  class BMinTermListIndexC 
    : public BMinTermIndexC<BListC<DataT> > 
  {
  public:
    BMinTermListIndexC() 
    {}
    //: Default constructor.
    // Creates an empty index.
    
    BMinTermListIndexC(const BMinTermIndexC<BListC<DataT> > &oth)
      : BMinTermIndexC<BListC<DataT> >(oth)
    {}
    //: Base class constructor.
    
#if 0
    inline VLBNPIndexC<BListC<DataT> > DeepCopy() const
    { return VLBNPIndexC<BListC<DataT> >::DeepCopy(); }
    //: Make a deep copy of this class.
#endif  
    
    bool Insert(const LiteralC &symb,const DataT &dat);
    //: Insert data into all appropriate lists.
    
    bool Insert(const MinTermC &symb,const DataT &dat);
    //: Insert data into all appropriate lists.
  
  };

  ///////////////////////////////////////////////////
  
  template <class DataT>
  bool BMinTermListIndexC<DataT>::Insert(const LiteralC &as,const DataT &dat) {
    AndC at(as);
    if(at.IsValid()) {
      Access(false,at).InsFirst(dat);
      for(SArray1dIterC<LiteralC> it(at.Terms());it;it++)
	Insert(as,dat);
      return true;
    }
    NotC nt(as);
    if(nt.IsValid()) {
      OrC ot(as);
      if(ot.IsValid()) {
	for(SArray1dIterC<LiteralC> it(ot.Terms());it;it++)
	  Access(true,*it).InsFirst(dat);
	return true;
      }
      Access(true,as).InsFirst(dat);
      return true;
    }
    Access(false,as).InsFirst(dat);
    return true;
  }
  
  template <class DataT>
  bool BMinTermListIndexC<DataT>::Insert(const MinTermC &mt,const DataT &dat) {
    for(MinTermIterC iter(mt);iter;iter++)
      Access(iter.IsNegated(),iter.Data()).InsFirst(dat);
    return true;
  }

}

#endif
