#include "amma/Array1d.hh"
#include "amma/EntryPnt.hh"
#include <iostream.h>
#include <assert.h>
#include <stdlib.h>

int Main(int argc, char* argv[])
{
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << "rowmin rowmax colmin colmax"
	 << endl;
    // argv[1] [2] [3] [4]
    exit(-1);
  } assert((argv[1]<=argv[2]));
  IndexRangeC rect (atoi(argv[1]), atoi(argv[2]));
  Array1dC<IntT> arr(rect);
  cerr << "array has IndexRectangle = " << arr.Rectangle() 
       << endl;
  arr.ShiftIndexes(-1);
  cerr << "after array.ShiftIndexes(-1); " << endl;
  cerr << "array has IndexRectangle = " << arr.Range()<<endl;
  
  return 0;
}

AMMA_ENTRY_POINT(Main);
