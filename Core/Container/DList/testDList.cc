//! rcsid="$Id$"

#include "Ravl/InDList.hh"
#include "Ravl/InDLIter.hh"
#include <iostream.h>

using namespace RavlN;

class StuffC
  : public DLinkC
{
public:
  StuffC()
    {}
  //: Default constructor.

  StuffC(int nv)
    : v(nv)
    {}
  //: Constructor.
  
  int v;
};
  
int testIntrDList();

int main(int nargs,char *argv[])
{
  int lineno;
  if((lineno = testIntrDList()) != 0) {
    cerr << "IntrDListC test failed on line "<< lineno << "\n";
    return 1;
  }
  cerr << "Test passed ok. \n";	      
  return 0;
}

int testIntrDList() {
  IntrDListC<StuffC> lst;
  if(!lst.IsEmpty()) return __LINE__;
  int i;
  for(i = 0;i < 10;i++)
    lst.InsLast(*new StuffC(i));
  i = 0;
  if(lst.IsEmpty()) return __LINE__;
  for(IntrDLIterC<StuffC> it(lst);it;it++,i++) {
    if(it->v != i)
      return __LINE__;
  }
    
  IntrDListC<StuffC> lstCopy(lst);
  if(lstCopy.IsEmpty()) return __LINE__;
  lst.Empty();
  if(!lst.IsEmpty()) return __LINE__;
  if(lstCopy.IsEmpty()) return __LINE__;
  i = 0;
  for(IntrDLIterC<StuffC> it(lstCopy);it;it++,i++) {
    if(it->v != i)
      return __LINE__;
  }
  IntrDListC<StuffC> lstCopy2;
  lstCopy2 = lstCopy;
  if(!lst.IsEmpty()) return __LINE__;
  if(lstCopy.IsEmpty()) return __LINE__;
  if(lstCopy2.IsEmpty()) return __LINE__;
  i = 0;
  for(IntrDLIterC<StuffC> it(lstCopy2);it;it++,i++) {
    if(it->v != i)
      return __LINE__;
  }
  
  return 0;
}
