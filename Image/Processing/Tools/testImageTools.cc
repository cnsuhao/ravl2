// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImageProc

#include "Ravl/Image/Rectangle2dIter.hh"
#include "Ravl/Image/SummedAreaTable.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Image/Image.hh"

using namespace RavlN;
using namespace RavlImageN;

int testRectangle2dIter();
int testSummedAreaTable();

int main() {
  int ln;
  if((ln = testRectangle2dIter()) != 0) {
    cerr << "Error on line numner '" << ln << "'\n";
    return 1;
  }
  if((ln = testSummedAreaTable()) != 0) {
    cerr << "Error on line numner '" << ln << "'\n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}

int testRectangle2dIter() {
  ImageRectangleC rect1(0,6,0,5);
  ImageRectangleC rect2(5,5);
  ImageC<int> data(rect1);
  data.Fill(1);
  cerr << "Area=" << rect2.Area() << "\n";
  int rects = 0;
  for(Rectangle2dIterC it(rect1,rect2);it;it++) {
    if(it.Window().Area() != rect2.Area()) return __LINE__;
    int x = 0;
    for(Array2dIterC<int> itx(data,it.Window());itx;itx++)
      x += *itx;
    //cerr << "x=" << x << "\n";
    if((UIntT) x != it.Window().Area()) return __LINE__;
    rects++;
  }
  if(rects != 6)
    return __LINE__;
  return 0;
}

int testSummedAreaTable() {
  Array2dC<IntT> img(5,5);
  img.Fill(1);
  SummedAreaTableC<UIntT> tab(img);
  //cerr << tab << "\n";
  if(tab.Sum(img.Frame()) != 25) return __LINE__;
  IndexRange2dC srect(img.Frame());
  srect = srect.Erode();
  if(tab.Sum(srect) != 9) return __LINE__;
  
  // Build a more interesting image.
  IntT sum = 1;
  for(Array2dIterC<IntT> it(img);it;it++)
    *it = sum++;
  tab.BuildTable(img);
  //cerr << img << "\n";
  //cerr << tab << "\n";
  IndexRange2dC rec2(0,1,0,1);
  //cerr <<"Sum=" << tab.Sum(rec2) << "\n";
  if(tab.Sum(rec2) != 16) return __LINE__;
  
  IndexRange2dC rec3(0,1,1,2);
  //cerr <<"Sum=" << tab.Sum(rec3) << "\n";
  if(tab.Sum(rec3) != 20) return __LINE__;
  
  IndexRange2dC rec4(1,2,1,2);
  //cerr <<"Sum=" << tab.Sum(rec4) << "\n";
  if(tab.Sum(rec4) != 40) return __LINE__;
  
  
  return 0;
}
