//! rcsid="$Id$"

#include "Ravl/Array1d.hh"
#include "Ravl/Array1dIter.hh"
#include "Ravl/EntryPnt.hh"
#include <iostream.h>

using namespace RavlN;

int Main(int argc, char* argv[])
{
  
  Array1dC<IntT> arr(-10,10);
  
  cout << "arr.Range() = " << arr.Range() << "\n";
  cout << "arr.Size()  = " << arr.Size() << "\n";
  
  arr.Fill(0); // Fill array with 0's
  
  arr[-2] = 1;
  arr[3] = 2;
  
  for(Array1dIterC<IntT> it(arr);it;it++)
    if(*it != 0)
      cout << "Array element arr[" << it.Index() << "] is non zero, " << *it << "\n";
  
  return 0;
}

RAVL_ENTRY_POINT(Main);
