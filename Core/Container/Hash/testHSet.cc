//! rcsid="$Id$"

#include "Ravl/HSet.hh"
#include "Ravl/String.hh"

using namespace RavlN;

int BasicTest();

int main(int nargs,char *argv[])
{
  int errline;
  if((errline = BasicTest()) != 0) {
    cerr << "HSetC test failed on line " << errline << "\n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}

int BasicTest() {
  HSetC<StringC> set1;
  set1 += "one";
  set1 += "two";
  set1 += "three";
  if(set1.Size() != 3) return __LINE__;
  if(set1.IsEmpty()) return __LINE__;
  HSetC<StringC> set2;
  if(!set2.IsEmpty()) return __LINE__;
  set2 += "four";  
  if(set2.IsEmpty()) return __LINE__;
  if(set1.IsMember("four")) return __LINE__;
  if(!set1.IsMember("two")) return __LINE__;
  HSetC<StringC> set3 = set1.Union(set2);
  if(set3.Size() != 4) return __LINE__;
  if(set3 == set1) return __LINE__;
  if(!(set3 != set1)) return __LINE__;
  HSetC<StringC> set4 = set1.Copy();
  set4 += "five";
  if(!set4.IsSubset(set1)) return __LINE__;
  if(set1.IsSubset(set4)) return __LINE__;
  if(set1.Size() != 3) return __LINE__; // Copy worked ok ?
  if(set4.Size() != 4) return __LINE__; // Copy worked ok ?
  if(set4.Intersect(set3) != set1) return __LINE__;
  HSetC<StringC> set5 = set3.Disjunction(set4);
  if(set5.Size() != 2) return __LINE__;
  if(!set5.IsMember("five")) return __LINE__;
  if(!set5.IsMember("four")) return __LINE__;
  set1 -= "one";
  if(set1.Size() != 2) return __LINE__; // Copy worked ok ?
  set1.Empty();
  if(set1.Size() != 0) return __LINE__;
  return 0;
}
