// $Id$

#include "Ravl/Array1d.hh"
#include "Ravl/Array2d.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/EntryPnt.hh"
#include <iostream.h>

using namespace RavlN;

int Main(int argc, char* argv[])
{
  Array2dC<IntT> arr(-5,6,-7,8);
  cout << "array has arr.Range1() = " << arr.Range1() << "  arr.Range2() = " << arr.Range1() << "\n";
  
  // Index each dimension separately.
  
  arr[-2][3] = 1;

  // Access using a 2d index.
  
  Index2dC at(2,5);
  arr[at] = 4;
  
  // Go through array with an iterator.
  
  for(Array2dIterC<IntT> it(arr);it;it++) 
    if(*it != 0)
      cout << "Element " << it.Index() << " is non zero, " << *it << "\n";
  

  // Slice out a row.
  
  Array1dC<IntT> slice = arr.SliceRow(-2);
  if(slice[3] != 1)
    cout << "Ooops something went wrong! \n";
  
  return 0;
}

RAVL_ENTRY_POINT(Main);
