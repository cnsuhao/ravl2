// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, Charles Galambos
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlLogicAgent
//! file="Ravl/Logic/Agent/ActiveBlackboard.cc"

#include "Ravl/Logic/ActiveBlackboard.hh"
#include "Ravl/Calls.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlLogicN {
  
  //: Default constructor.
  
  ActiveBlackboardBodyC::ActiveBlackboardBodyC() 
    : index(true),
      triggers(true)
  {}
  
  //: Register a trigger.
  
  UIntT ActiveBlackboardBodyC::AddTrigger(const LiteralC &condition,TriggerC trigger) {
    DListC<TriggerC> &list = triggers.Access(condition);
    list.InsLast(trigger);
    return 0;
  }
  
  //: Process add signal.
  
  bool ActiveBlackboardBodyC::ProcessAdd(const LiteralC &key,RCWrapAbstractC &data) {
    ONDEBUG(cerr << "ActiveBlackboardBodyC::ProcessAdd(), Called. Key=" << key.Name() << "\n");
    RWLockHoldC lock(rwlock,RWLOCK_READONLY);
    LiteralC literal(key);
    for(LiteralIndexFilterC<DListC<TriggerC> > it(triggers,key);it;it++) {
      ONDEBUG(cerr << " Got match " << it.Data() << "\n");
      for(DLIterC<TriggerC> lit(it.MappedData());lit;lit++) {
	CallFunc2C<LiteralC,RCWrapAbstractC> call2(*lit,true);
	if(call2.IsValid()) {
	  call2.Call(literal,data);
	  continue;
	}
	CallFunc1C<LiteralC> call1(*lit,true);
	if(call1.IsValid()) {
	  call1.Call(literal);
	  continue;
	}
	lit->Invoke();
      }
    }
    return true;
  }
  
  
}
