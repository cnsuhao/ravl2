// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/Line2dIter.hh"
#include "Ravl/StdMath.hh"
#include "Ravl/Stream.hh"
#include "Ravl/Moments2d2.hh"

using namespace RavlN;

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

int testMoments();
int testLines();

int main() {
  int ln;
  if((ln = testLines()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
  return 0;
}

int testLines() {  
  Index2dC start(0,0);
  Index2dC end(10,5);
  int c = 0;
  ONDEBUG(cerr << "From " << start << " to " << end << "\n");
  for(Line2dIterC it(start,end);it && c < 20;it++,c++) {
    ONDEBUG(cerr << "Line " << it.Data() << "\n");
  }
  if(c > 19) return __LINE__;  
  for(RealT x = 0;x < RavlConstN::pi * 2; x += 0.1) {
    end = Index2dC(Round(Sin(x) * 10.0),Round(Cos(x) * 10.0));
    c = 0;
    ONDEBUG(cerr << "From " << start << " to " << end << "\n");
    for(Line2dIterC it(start,end);it && c < 20;it++,c++) {
      ONDEBUG(cerr << "Line " << it.Data() << "\n");
    }
    if(c > 19) return __LINE__;
  }
  return 0;
}

