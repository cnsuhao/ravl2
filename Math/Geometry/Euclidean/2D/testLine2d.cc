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

using namespace RavlN;

int main() {
  
  Index2dC start(0,0);
  Index2dC end(10,5);
  int c = 0;
  cerr << "From " << start << " to " << end << "\n";
  for(Line2dIterC it(start,end);it && c < 20;it++,c++) {
    cerr << "Line " << it.Data() << "\n";
  }
  if(c > 19) {
    cerr << "Test failed. \n";
    return 1;
  }
  
  for(RealT x = 0;x < RavlConstN::pi * 2; x += 0.1) {
    end = Index2dC(Round(Sin(x) * 10.0),Round(Cos(x) * 10.0));
    c = 0;
    cerr << "From " << start << " to " << end << "\n";
    for(Line2dIterC it(start,end);it && c < 20;it++,c++) {
      cerr << "Line " << it.Data() << "\n";
    }
    if(c > 19) {
      cerr << "Test failed. \n";
      return 1;
    }
  }
  return 0;
}
