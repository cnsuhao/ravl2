// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlLogic
//! file="Ravl/Logic/DecisionTree/testDecisionTree.cc"


#include "Ravl/Logic/DecisionTreeBase.hh"
#include "Ravl/Logic/NamedLiteral.hh"

using namespace RavlLogicN;

int testBasic();

int main() {
  int ln;
  if((ln = testBasic()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
  
  cerr << "Test passed ok. \n";
  return 0;
}

DataSet2C<SampleStateC,SampleLiteralC > BuildDataset() {
  DataSet2C<SampleStateC,SampleLiteralC > ret(true);
  LiteralC d1 = Literal("D1");
  LiteralC d2 = Literal("D2");
  LiteralC d3 = Literal("D3");

  LiteralC l1 = Literal("L1");
  LiteralC l2 = Literal("L2");
  LiteralC l3 = Literal("L3");
  LiteralC l4 = Literal("L4");
  
  StateC s1(true);
  s1.Tell(l1);
  StateC s2(true);
  s2.Tell(l1);
  s2.Tell(l2);
  StateC s3(true);
  s3.Tell(l3);

  StateC s4(true);
  s4.Tell(l4);
  
  ret.Append(s1,d1);
  ret.Append(s2,d2);
  ret.Append(s3,d3);
  ret.Append(s4,d2);
  
  return ret;
}

int testBasic() {
  DecisionTreeBaseC dl(true);  
  DataSet2C<SampleStateC,SampleLiteralC > data = BuildDataset();
  dl.Train(data);
  cerr << "Tree=\n";
  dl.Dump(cout);
  StateC s = dl.BuildRuleSet();
  cerr << "Ruleset=\n";
  s.Dump(cout);
  return 0;
}


