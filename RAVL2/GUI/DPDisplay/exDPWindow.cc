// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: exDPWindow.cc 7175 2009-04-28 16:06:32Z ees1wc $"
//! lib=RavlDPDisplay
//! file="Ravl/GUI/DPDisplay/exDPWindow.cc"
//! author="Charles Galambos"
//! docentry="Ravl.API.Graphics.Data Display"
//! userlevel=Normal

#include "Ravl/GUI/DPWindow.hh"
#include "Ravl/GUI/DPDisplayImage.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/IO.hh"
#include "Ravl/PolyLine2d.hh"
#include "Ravl/LinePP2d.hh"

using namespace RavlGUIN;


PolyLine2dC Arrow(const Point2dC& tail, const Point2dC& head) { 
  PolyLine2dC arrow;
  arrow.InsLast(head);
  arrow.InsLast(tail);
  return arrow;
}


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
  
  // Add a point to the image.
  Point2dC aPnt(128,64);
  if(!Save("@XA:hello",aPnt)) {
    cerr << "Failed to save point. \n";
    return 1;
  }
  
  // Add a closed polygon to the image
  Polygon2dC aPoly(RealRange2dC(Point2dC(30,25),10));
  if(!Save("@XA:hello",aPoly)) {
    cerr << "Failed to save polygon. \n";
    return 1;
  }
  
  // Add a polyline to the image
  PolyLine2dC aPolyLine(Polygon2dC(RealRange2dC(Point2dC(60,25),10)));
  if(!Save("@XA:hello",aPolyLine)) {
    cerr << "Failed to save polygon. \n";
    return 1;
  }
  
  // Add some "arrows" to the image
  for (IndexC r=150; r<=250; r+= 10) for (IndexC c=20; c<=120; c+= 10) {
    PolyLine2dC arrow = Arrow(Point2dC(r,c), Point2dC(r+8,c+6));
    if(!Save("@XA:hello",arrow)) {
      cerr << "Failed to save arrow. \n";
      return 1;
    }
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
  
  if(!Save("@X:hello2",img,"",true)) {
    cerr << "Failed to save image 2. \n";
    return 1;
  }
  
  // Display a new image, and reset the origin and scale
  if(!Save("@XR:hello2",img2,"",true)) {
    cerr << "Failed to save image 2. \n";
    return 1;
  }
  
  return 0;
}
