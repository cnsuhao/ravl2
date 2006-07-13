// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlDPDisplay
//! file="Ravl/GUI/DPDisplay/exDPWindow.cc"
//! author="Charles Galambos"
//! docentry="Ravl.API.GUI.Data Display"
//! userlevel=Normal

#include "Ravl/GUI/DPWindow.hh"
#include "Ravl/GUI/DPDisplayImage.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/IO.hh"

using namespace RavlGUIN;

int main() {
  Index2dC origin(5,10);
  IndexRange2dC rng(origin,origin + Index2dC(256,256));
  ImageC<ByteRGBValueC> img(rng);
  for(int x = 0;x < 256;x++)
    for(int y = 0;y < 256;y++)
      img[origin[0] + x][origin[1] + y] = ByteRGBValueC(x,y,128);
  
  if(!Save("@X:hello",img,"",true)) {
    cerr << "Failed to save image. \n";
    return 1;
  }
  
  IndexRangeC rr(-100,100);
  IndexRangeC cr(-100,200);
  ImageC<ByteT> img2(rr,cr);
  for(int x = rr.Min().V();x < rr.Max();x++)
    for(int y = cr.Min().V();y < cr.Max();y++) {
      if(y != 0)
	img2[x][y] =  (x) % (y);
      else
	img2[x][y] = x;
    }
  
  if(!Save("@X:hello2",img2,"",true)) {
    cerr << "Failed to save image 2. \n";
    return 1;
  }
#if 0
  while(1)
    RavlN::Sleep(1);
#endif
  return 0;
}
