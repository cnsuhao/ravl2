// $Id$

#include "Ravl/Array2d.hh"
#include "Ravl/EntryPnt.hh"
#include <iostream.h>
#include <assert.h>
#include <stdlib.h>

using namespace RavlN;

int Main(int argc, char* argv[])
{
  if (argc != 5) {
    cerr << "Usage: " << argv[0] << "rowmin rowmax colmin colmax"
	 << endl;
    // argv[1] [2] [3] [4]
    exit(-1);
  } assert((argv[1]<=argv[2]) && (argv[3]<=argv[4]));
  IndexRectangleC rect (atoi(argv[1]), atoi(argv[2]),
			atoi(argv[3]),atoi(argv[4]));
  Array2dC<IntT> arr(rect);
  cerr << "array has IndexRectangle = " << arr.Rectangle() 
       << endl;
  arr.ShiftIndexes1(-1);
  arr.ShiftIndexes2(-2);
  cerr << "after array.ShiftIndexes1(-1);
array.ShiftIndexes2(-2)" << endl;
  cerr << "array has IndexRectangle = " << arr.Rectangle()<<endl;
  cerr << " and has Range1() = " << arr.Range1() <<endl;
  cerr << " and has Range2() = " << arr.Range2() <<endl;
  
  return 0;
}

AMMA_ENTRY_POINT(Main);
