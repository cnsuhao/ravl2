// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/BLiteralIndex.hh"
#include "Ravl/Logic/BMinTermIndex.hh"
#include "Ravl/Logic/BMinTermIndexIter.hh"
#include "Ravl/Logic/BMinTermListIndex.hh"
#include "Ravl/Logic/Literal.hh"

using namespace RavlLogicN;

template class BMinTermListIndexC<LiteralC>;

int testBIndex();
int testBMinTermIndex();

int main() {
  int ln;
  if((ln = testBIndex()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testBMinTermIndex()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  return 0;
}


int testBIndex() {
  BLiteralIndexC<LiteralC> ind;
  // Test basic functionality.
  ind["Hello1"] = LiteralC("Hello1");
  ind["Hello2"] = LiteralC("Hello2");
  ind["Hello3"] = LiteralC("Hello3");
  if(ind["Hello1"] != LiteralC("Hello1"))
    return __LINE__;
  if(ind["Hello2"] != LiteralC("Hello2"))
    return __LINE__;
  if(ind["Hello3"] != LiteralC("Hello3"))
    return __LINE__;
  return 0;
}

int testBMinTermIndex() {
  BMinTermIndexC<LiteralC> ind(true);
  // Test basic functionality.
  ind.Add(true,"Hello1","Hello1");
  ind.Add(true,"Hello2","Hello2");
  ind.Add(true,"Hello3","Hello3");
  ind.Add(false,"Hello1","Hello4");
  ind.Add(false,"Hello2","Hello5");
  ind.Add(false,"Hello3","Hello6");
  if(ind.Access(true,"Hello1") != LiteralC("Hello1"))
    return __LINE__;
  if(ind.Access(true,"Hello2") != LiteralC("Hello2"))
    return __LINE__;
  if(ind.Access(true,"Hello3") != LiteralC("Hello3"))
    return __LINE__;
  if(ind.Access(false,"Hello1") != LiteralC("Hello4"))
    return __LINE__;
  if(ind.Access(false,"Hello2") != LiteralC("Hello5"))
    return __LINE__;
  if(ind.Access(false,"Hello3") != LiteralC("Hello6"))
    return __LINE__;
  // Quick check on the iterator.
  BMinTermIndexIterC<LiteralC> it(ind,LiteralC("Hello1"));
  if(!it.IsElm()) return __LINE__;
  if(it.Data() != LiteralC("Hello4")) return __LINE__;
  if(it.Next()) return __LINE__;
  if(it.IsElm()) return __LINE__;
  return 0;
}
