//////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Collection.hh"
#include "Ravl/SArr1Iter.hh"

using namespace RavlN;

int testBasic();

int main()
{
  int err;
  if((err = testBasic()) != 0) {
    cerr << "Test failed line :" << err <<"\n";
  }
  
  cerr << "Collection test passed. \n";
  return 0;
}

int testBasic() {
  
  CollectionC<IntT> c(100);
  
  if(!c.IsEmpty()) return __LINE__;
  int x = 0;
  c.Insert(x);
  if(c.IsEmpty()) return __LINE__;
  for(int i= 1;i < 100;i++)
    c.Insert(i);
  if(c.Size() != 100) return __LINE__;
  // Check pick.
  int v = c.Pick();
  if(v < 0 || v > 99) return __LINE__;
  // Check array function works, and the
  // value 'v' has been removed from the set.
  if(c.Size() != 99) return __LINE__;
  SArray1dC<IntT> vs(c.Array());
  for(SArray1dIterC<IntT> it(vs);it;it++)
    if(*it == v) return __LINE__;
  
  return 0;
}
