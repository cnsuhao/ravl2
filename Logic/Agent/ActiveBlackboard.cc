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
#include "Ravl/Logic/State.hh"
#include "Ravl/Logic/LiteralIO.hh"
#include "Ravl/Logic/Unify.hh"
#include "Ravl/Calls.hh"
#include "Ravl/CallMethods.hh"

#define DODEBUG 0
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

  //: Load rules from a file.
  
  bool ActiveBlackboardBodyC::LoadRules(const StringC &filename) {
    StateC state(true);
    ContextC context;
    if(!LoadState(filename,state,context))
      return false;
    LiteralC pre = Var();
    LiteralC post = Var();
    LiteralC lit = Tuple(pre,post);
    BindSetC bnd(true);
    for(LiteralIterC it(state.Filter(lit,bnd));it;it++) {
      TupleC tup = *it;
      cerr << "ActiveBlackboardBodyC::LoadRules(), Loading rule " << tup.Name() << "\n";
      AddRule(tup[0],tup[1]);
    }
    return true;
  }
  
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
    DListC<DListC<TriggerC> > todo;
    for(LiteralIndexFilterC<DListC<TriggerC> > it(triggers,key);it;it++) {
      todo.InsLast(it.MappedData());
    }
    lock.Unlock();
    LiteralC x(key);
    for(DLIterC<DListC<TriggerC> > it(todo);it;it++) {
      ONDEBUG(cerr << " Got match " << key.Name() << "\n");
      for(DLIterC<TriggerC> lit(*it);lit;lit++) {
	CallFunc2C<LiteralC,RCWrapAbstractC> call2(*lit,true);
	if(call2.IsValid()) {
	  call2.Call(x,data);
	  continue;
	}
	CallFunc1C<LiteralC> call1(*lit,true);
	if(call1.IsValid()) {
	  call1.Call(x);
	  continue;
	}
	lit->Invoke();
      }
    }
    return true;
  }
  
  //: Handle assertion of a post condition
  
  bool ActiveBlackboardBodyC::AssertPost(LiteralC event,
					 const LiteralC &preCond,
					 const LiteralC &postCond) {
    ONDEBUG(cerr << "ActiveBlackboardBodyC::AssertPost(), Event=" << event.Name() << " Pre=" << preCond.Name() << " Post=" << postCond.Name() << "\n");
    BindSetC binds(true);
    if(!Unify(preCond,event,binds)) {
      cerr << "ActiveBlackboardBodyC::AssertPost(), ERROR: Unify failed. \n";
      return true;
    }
    LiteralC newLit;
    postCond.Substitute(binds,newLit);
    ONDEBUG(cerr << "ActiveBlackboardBodyC::AssertPost(), Tell=" << newLit.Name() << " binds=" << binds << "\n");
    Tell(newLit);
    return true;
  }
  
  //: Add a rule to the blackboard.
  // When 'pre' condition it met, assert 'post' condition.
  
  UIntT ActiveBlackboardBodyC::AddRule(const LiteralC &pre,const LiteralC &post) {
    LiteralC tmp;
    return AddTrigger(pre,TriggerR(*this,&ActiveBlackboardBodyC::AssertPost,tmp,pre,post));
  }
  
}
