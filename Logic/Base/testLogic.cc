// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/Tuple.hh"
#include "Ravl/Logic/Unify.hh"
#include "Ravl/Logic/Var.hh"

using namespace RavlLogicN;

int testBasic();
int testBind();

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
  cerr << "Test passed. \n";
  return 0;
}

//: Test basic literal operations and unification.

int testBasic() {

  if(!Literal().IsValid()) return __LINE__;
  if(!Var().IsValid()) return __LINE__;
  
  LiteralC s1(Literal()),s2(Literal());
  VarC v1(true);
  TupleC e1 = Tuple(s1,s2);
  e1.Dump(cerr);
  cerr <<"\n";
  TupleC e2 = Tuple(s1,s2);
  BindSetC bs;
  if(!Unify(e1,e2,bs)) return __LINE__;
  TupleC e3 = Tuple(s1,Var());
  e3.Dump(cerr);
  cerr << "\n";
  if(!Unify(e1,e3,bs)) return __LINE__;
  if(bs.Size() != 1) return __LINE__;
  return 0;
}

// Test BindSetC.

int testBind() {
  
  BindSetC test;
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
