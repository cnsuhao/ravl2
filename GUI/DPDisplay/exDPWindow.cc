// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGUIDisplay


#include "Ravl/GUI/DPWindow.hh"
#include "Ravl/GUI/DPDisplayImage.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/IO.hh"

using namespace RavlGUIN;

int main() {
  ImageC<ByteRGBValueC> img(256,256);
  for(int x = 0;x < 256;x++)
    for(int y = 0;y < 256;y++)
      img[x][y] = ByteRGBValueC(x,y,128);
  
  if(!Save("@X:hello",img,"",true)) {
    cerr << "Failed to save image. \n";
    return 1;
  }
  
  ImageC<ByteT> img2(100,200);
  for(int x = 0;x < 100;x++)
    for(int y = 0;y < 200;y++)
      img2[x][y] =  (x+1) % (y+1);
  
  if(!Save("@X:hello2",img2,"",true)) {
    cerr << "Failed to save image 2. \n";
    return 1;
  }
  
  //while(1)
  //  Sleep(1);
  return 0;
}
