// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGUI2D
//! author="Charles Galambos"
//! docentry="Ravl.GUI.Control"

#include "Ravl/GUI/RawZoomCanvas.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/Window.hh"
#include "Ravl/Polygon2d.hh"
#include "Ravl/GUI/Slider.hh"
#include "Ravl/GUI/LBox.hh"

using namespace RavlGUIN;

ImageC<ByteRGBValueC> img;
Polygon2dC poly;
RawZoomCanvasC canvas;

bool Refresh() {
  canvas.GUIDrawImage(img);
  if(!poly.IsEmpty()) {
    Point2dC last = poly.Last();
    for(DLIterC<Point2dC> it(poly);it;it++) {
      canvas.GUIDrawLine(canvas.GUIDrawGCWhite(),last,*it);
      last = *it;
    }
  }
  return true;
}

bool UpdateScale(RealT &scale) {
  canvas.GUISetScale(Vector2dC(scale,scale));
  Refresh();
  return true;
}

bool UpdateROffset(RealT &roff) {
  Vector2dC tmp = canvas.Offset();
  tmp[0] = roff;
  canvas.GUISetOffset(tmp);
  Refresh();
  return true;
}

bool UpdateCOffset(RealT &coff) {
  Vector2dC tmp = canvas.Offset();
  tmp[1] = coff;
  canvas.GUISetOffset(tmp);
  Refresh();
  return true;
}

int main(int nargs,char **argv) {
  
  WindowC win(400,400,"Polygon canvas");
  
  canvas = RawZoomCanvasC(100,100);
  
  // Create an image.
  
  img = ImageC<ByteRGBValueC> (256,256);
  for(int i = 0;i <256;i++)
    for(int j = 0;j < 256;j++)
      img[i][j] = ByteRGBValueC(i,j,0);
  
  //canvas.SetBackground(img);
  
  // Create a poly.
  
  poly.InsLast(Point2dC(10,10));
  poly.InsLast(Point2dC(100,10));
  poly.InsLast(Point2dC(100,100));
  poly.InsLast(Point2dC(10,100));
  
  Connect(canvas.Signal("expose_event"),&Refresh);
  
  SliderC scale = SliderH(1,1,10,1,&UpdateScale);
  SliderC roffset = SliderH(1,0,100,1,&UpdateROffset);
  SliderC coffset = SliderH(1,0,100,1,&UpdateCOffset);
  
  win.Add(VBox(canvas + scale + roffset + coffset));
  win.Show();
  Manager.Start();

  return 0;
}
