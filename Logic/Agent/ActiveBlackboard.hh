// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, Charles Galambos
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ACTIVEBLACKBOARD_HEADER
#define RAVL_ACTIVEBLACKBOARD_HEADER 1
//! author="Charles Galambos"
//! userlevel=Normal
//! rcsid="$Id$"
//! lib=RavlLogicAgent
//! file="Ravl/Logic/Agent/ActiveBlackboard.hh"

#include "Ravl/Logic/Literal.hh"
#include "Ravl/Logic/LiteralIndex.hh"
#include "Ravl/Logic/LiteralIndexFilter.hh"
#include "Ravl/RCWrap.hh"
#include "Ravl/Threads/RWLock.hh"
#include "Ravl/DList.hh"

namespace RavlLogicN {
  
  //! userlevel=Develop
  //: Active blackboard
  
  class ActiveBlackboardBodyC
    : public RCBodyVC
  {
  public:
    ActiveBlackboardBodyC();
    //: Default constructor.
    
    UIntT AddTrigger(const LiteralC &condition,TriggerC trigger);
    //: Register a trigger.
    
    template<class DataT>
    bool Tell(const LiteralC &key,const DataT &data) {
      RWLockHoldC lock(rwlock,RWLOCK_WRITE);
      RCWrapC<DataT> wrap(data);
      index[key] = wrap;
      lock.Unlock();
      ProcessAdd(key,wrap);
      return true;
    }
    //: Tell blackboard something.

    bool Ask(const LiteralC &key,RCWrapAbstractC &data) {
      RWLockHoldC lock(rwlock,RWLOCK_READONLY);
      return index.Lookup(key,data);
    }
    //: Ask about a first match.
    
    template<class DataT>
    bool Ask(const LiteralC &key,DataT &data) {
      RWLockHoldC lock(rwlock,RWLOCK_READONLY);
      RCWrapAbstractC wrap;
      if(!index.Lookup(key,wrap))
	return false;
      lock.Unlock();
      RCWrapC<DataT> rcw(wrap,true);
      if(!rcw.IsValid())
	return false;
      data = rcw.Data();
      return true;
    }
    //: Ask about a first match.
    
    template<class DataT>
    UIntT AskAll(const LiteralC &key,DListC<Tuple2C<LiteralC,DataT> > &list) {
      RWLockHoldC lock(rwlock,RWLOCK_READ);
      for(LiteralIndexFilterC<RCWrapAbstractC> it(index,key);it;it++) {
	RCWrapC<DataT> rcw(wrap,true);
	if(!rcw.IsValid())
	  return false;
	list.InsLast(Tuple2C<LiteralC,DataT>(it.Key(),rcw.Data()));
      }
      return true;
    }
    //: Ask about a all matchs.
    
  protected:
    bool ProcessAdd(const LiteralC &lit,RCWrapAbstractC &data);
    //: Process add signal.
    
    RWLockC rwlock;
    
    LiteralIndexC<RCWrapAbstractC> index;
    LiteralIndexC<DListC<TriggerC> > triggers;
  };
  
  //! userlevel=Normal
  //: Active blackboard
  
  class ActiveBlackboardC
    : public RCHandleVC<ActiveBlackboardBodyC>
  {
  public:
    ActiveBlackboardC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    ActiveBlackboardC(bool)
      : RCHandleVC<ActiveBlackboardBodyC>(*new ActiveBlackboardBodyC())
    {}
    //: Constructor.
    
  protected:
    
  public:
    
    UIntT AddTrigger(const LiteralC &condition,TriggerC trigger)
    { return Body().AddTrigger(condition,trigger); }
    //: Register a trigger.
    
    template<class DataT>
    bool Tell(const LiteralC &key,const DataT &data) 
    { return Body().Tell(key,data); }
    //: Tell blackboard something.
    
    bool Ask(const LiteralC &key,RCWrapAbstractC &data) 
    { return Body().Ask(key,data); }
    //: Ask about a first match.
    
    template<class DataT>
    bool Ask(const LiteralC &key,DataT &data) 
    { return Body().Ask(key,data); }
    //: Ask about a first match.
    
    template<class DataT>
    UIntT AskAll(const LiteralC &key,DListC<Tuple2C<LiteralC,DataT> > &list) 
    { return Body().AskAll(key,list);  }
    //: Ask about a all matchs.
    
  };
  
  
}


#endif 
