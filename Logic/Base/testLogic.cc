// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlLogic
//! file="Ravl/Logic/Base/testLogic.cc"

#include "Ravl/Logic/Tuple.hh"
#include "Ravl/Logic/Unify.hh"
#include "Ravl/Logic/Var.hh"
#include "Ravl/Logic/StateSet.hh"
#include "Ravl/Logic/Or.hh"
#include "Ravl/Logic/And.hh"
#include "Ravl/Logic/Not.hh"

using namespace RavlLogicN;

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

int testBasic();
int testBind();
int testStateSet();
int testStateOr();
int testStateAnd();
int testStateNot();

int main() {
  int err;
  if((err = testBind()) != 0) {
    cerr << "testBind failed at : " << err << "\n";
    return 1;
  }
  if((err = testBasic()) != 0) {
    cerr << "testBasic failed at : " << err << "\n";
    return 1;
  }
  if((err = testStateSet()) != 0) {
    cerr << "testStateSet failed at : " << err << "\n";
    return 1;
  }
  if((err = testStateOr()) != 0) {
    cerr << "testStateOr failed at : " << err << "\n";
    return 1;
  }
  if((err = testStateAnd()) != 0) {
    cerr << "testStateAnd failed at : " << err << "\n";
    return 1;
  }
  if((err = testStateNot()) != 0) {
    cerr << "testStateAnd failed at : " << err << "\n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}

//: Test basic literal operations and unification.

int testBasic() {
  
  if(!Literal().IsValid()) return __LINE__;
  if(!Var().IsValid()) return __LINE__;

  LiteralC s1(Literal());
  LiteralC s2(Literal());
  VarC v1(true);
  LiteralC test;
  
  // Check unification of plain literals.
  BindSetC bs1(true);
  if(!Unify(v1,s1,bs1)) return __LINE__;
  if(!bs1.IsBound(v1)) return __LINE__;
  if(!bs1.Resolve(v1,test)) return __LINE__;
  if(test != s1) return __LINE__;
  
  bs1.Empty();
  if(!Unify(s1,v1,bs1)) return __LINE__;
  if(!bs1.IsBound(v1)) return __LINE__;
  if(!bs1.Resolve(v1,test)) return __LINE__;
  if(test != s1) return __LINE__;
  
  // Check the most basic unify operation.
  TupleC e1 = Tuple(s1,s2);
  //e1.Dump(cerr);   cerr <<"\n";
  TupleC e2 = Tuple(s1,s2);
  BindSetC bs(true);
  if(!Unify(e1,e2,bs)) return __LINE__;
  TupleC e3 = Tuple(s1,Var());
  //e3.Dump(cerr); cerr << "\n";
  if(!Unify(e1,e3,bs)) return __LINE__;
  if(bs.Size() != 1) return __LINE__;

  return 0;
}

// Test BindSetC.

int testBind() {
  
  BindSetC test(true);
  if(!test.IsValid()) return __LINE__;
  VarC v1(true);
  VarC v2(true);
  VarC v3(true);
  LiteralC l1(true);
  LiteralC l2(true);
  BindMarkT bm1 = test.Mark();  
  if(!test.Bind(v1,l1)) return __LINE__;
  if(test.Bind(v1,l2)) return __LINE__;
  if(!test.Bind(v2,l2)) return __LINE__;  
  BindMarkT bm2 = test.Mark(); 
  if(!test.Bind(v3,l1)) return __LINE__;
  if(test[v1] != l1) return __LINE__;
  if(test[v2] != l2) return __LINE__;
  if(test[v3] != l1) return __LINE__;
  if(test.Size() != 3) return __LINE__;
  test.Undo(bm2);
  if(test.Size() != 2) return __LINE__;
  if(!test.IsBound(v1)) return __LINE__;
  if(!test.IsBound(v2)) return __LINE__;
  if(test.IsBound(v3)) return __LINE__;
  test.Undo(bm1);
  if(test.Size() != 0) return __LINE__;
  if(test.IsBound(v1)) return __LINE__;
  if(test.IsBound(v2)) return __LINE__;
  if(test.IsBound(v3)) return __LINE__;
  return 0;
}


// Test BindSetC.

int testStateSet() {
  StateSetC state(true);
  if(!state.IsValid()) return __LINE__;
  LiteralC l1(true);
  LiteralC l2(true);
  if(state.Ask(l1)) return __LINE__;
  if(!state.Tell(l1)) return __LINE__;
  if(state.Ask(l2)) return __LINE__;
  if(!state.Tell(l2)) return __LINE__;
  if(!state.Ask(l1)) return __LINE__;
  if(!state.Ask(l2)) return __LINE__;
  // Check filter on unbound var.
  VarC v1(true);
  BindSetC binds(true);
  LiteralIterC it = state.ListFilter(v1,binds);
  int count = 0;
  for(;it;it++) {
    if(!binds.IsBound(v1)) return __LINE__;
    count++;
  }
  if(count != 2) return __LINE__;
  // Check filter on bound var.
  count = 0;
  binds.Bind(v1,l1);
  it = state.ListFilter(v1,binds);
  for(;it;it++) {
    count++;
    if(it.Data() != l1) return __LINE__;
  }
  if(count != 1) return __LINE__;
  // Dump state.
  cout << "Test dump of state: \n";
  cout << state;
  return 0;
}


int testStateOr() {
  //cerr << "testStateOr() \n";
  StateSetC state(true);
  LiteralC l1(true);
  LiteralC l2(true);
  LiteralC l3(true);
  VarC v1(true);
  
  TupleC t1(l1,l2);
  TupleC t2(l2,l3);
  TupleC t3(l2,l1);
  state.Tell(t1);
  state.Tell(t2);
  state.Tell(t3);
  
  ConditionC orTest(Tuple(v1,l3) + Tuple(l1,v1));
  //cerr << "testStateOr() Creating iter.\n";
  BindSetC binds(true);
  int count = 0;
  for(LiteralIterC it(orTest.Solutions(state,binds));it;it++) {
    if(it.Data() == t1) {
      if(!binds.IsBound(v1)) return __LINE__;
    }
    if(it.Data() == t2) {
      if(!binds.IsBound(v1)) return __LINE__;
    }
    if(it.Data() == t3) return __LINE__;
    count++;
  }
  if(count != 2) return __LINE__;
  return 0;
}

int testStateAnd() {
  //cerr << "testStateAnd() \n";
  StateSetC state(true);
  LiteralC l1(true);
  LiteralC l2(true);
  LiteralC l3(true);
  VarC v1(true);
  VarC v2(true);
  
  TupleC t1(l1,l2);
  TupleC t2(l2,l3);
  TupleC t3(l2,l1);
  TupleC t4(l1,l3);
  state.Tell(t1);
  state.Tell(t2);
  state.Tell(t3);
  state.Tell(t4);
  
  ConditionC andTest(Tuple(v1,l3) * Tuple(l1,v2));
  //cerr << "testStateAnd() Creating iter.\n";
  BindSetC binds(true);
  int count = 0;
  for(LiteralIterC it(andTest.Solutions(state,binds));it;it++) {
    ONDEBUG(cerr << "Got solution, Binds :" << binds << "\n");
    if(!binds.IsBound(v1)) return __LINE__;
    if(!binds.IsBound(v2)) return __LINE__;
    count++;
  }
  if(count != 4) return __LINE__;
  return 0;
}

int testStateNot() {
  //cerr << "testStateAnd() \n";
  StateSetC state(true);
  LiteralC l1(true);
  LiteralC l2(true);
  LiteralC l3(true);
  VarC v1(true);
  
  TupleC t1(l1,l2);
  TupleC t2(l2,l3);
  TupleC t3(l2,l1);
  TupleC t4(l1,l3);
  state.Tell(t1);
  state.Tell(t2);
  state.Tell(t3);
  state.Tell(t4);
  
  ConditionC notTest = !(Tuple(l1,l3) + Tuple(l2,v1));
  //cerr << "testStateAnd() Creating iter.\n";
  BindSetC binds(true);
  int count = 0;
  for(LiteralIterC it(notTest.Solutions(state,binds));it;it++) {
    ONDEBUG(cerr << "Got solution, Binds :" << binds << "\n");
    //    if(!binds.IsEmpty()) return __LINE__;
    if(it.Data() != t1) return __LINE__;
    count++;
  }
  if(count != 1) return __LINE__;
  return 0;
}
