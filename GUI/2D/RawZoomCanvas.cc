// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGUI2D

#include "Magellan/GUI/RawZoomCanvas.hh"
#include "Ravl/Image/WarpScale.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Threads/Signal1.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {

  //: Constructor.
  
  RawZoomCanvasBodyC::RawZoomCanvasBodyC(IntT rows,IntT cols)
    :  RawCanvasBodyC(cols,rows),
       offset(0,0),
       scale(1,1)
  {}
  
  bool RawZoomCanvasBodyC::Create() {
    ConnectRef(Signal("configure_event"),*this,&RawZoomCanvasBodyC::EventConfigure);
    return RawCanvasBodyC::Create();
  }
  
  //: Handle configure event.
  
  bool RawZoomCanvasBodyC::EventConfigure(GdkEvent* &event) {
    
    RawCanvasBodyC::TranslateConfigureEvent(event,widgetSize);
    cerr << "RawZoomCanvasBodyC::EventConfigure(), Called. Size=" << widgetSize << "\n";
    return true;
  }
  
  //: Access current offset.
  
  void RawZoomCanvasBodyC::GUISetOffset(const Vector2dC &off) {
    offset = off;
  }
  
  //: Access current scale.
  
  void RawZoomCanvasBodyC::GUISetScale(const Vector2dC &nscale) {
    scale = nscale;
  }
  
  //: Draw a line.
  
  void RawZoomCanvasBodyC::GUIDrawLine(GdkGC *gc,Point2dC p1,Point2dC p2) 
  { RawCanvasBodyC::GUIDrawLine(gc,World2GUIi(p1),World2GUIi(p2)); }
  
  //: Draw a rectangle.
  
  void RawZoomCanvasBodyC::GUIDrawRectangle(GdkGC *gc,const RealRange2dC &rect,bool fill) 
  { RawCanvasBodyC::GUIDrawRectangle(gc,World2GUIi(rect.Origin()),World2GUIi(rect.End()),fill); }
  
  //: Draw a rectangle.
  
  void RawZoomCanvasBodyC::GUIDrawRectangle(GdkGC *gc,Point2dC topLeft,Point2dC bottomRight,bool fill) 
  { RawCanvasBodyC::GUIDrawRectangle(gc,World2GUIi(topLeft),World2GUIi(bottomRight),fill); }
  
  //: Draw text.
  // 'at' is the bottom left of the text to be drawn.
  
  void RawZoomCanvasBodyC::GUIDrawText(GdkGC *gc,GdkFont *font,Point2dC at,const StringC &txt)  { 
    // Scale font ?
    RawCanvasBodyC::GUIDrawText(gc,font,World2GUIi(at),txt); 
  }
  
  //: Find the size of 'text' rendered in 'font'.
  
  void RawZoomCanvasBodyC::GUITextSize(GdkFont *font,const StringC &txt,Point2dC &size) {
    // Scale font ?
    size = RawCanvasBodyC::GUITextSize(font,txt); 
  }
  
  //: Draw a circle.
  
  void RawZoomCanvasBodyC::GUIDrawCircle(GdkGC *gc,Point2dC cent,RealT size,bool fill) 
  { 
    // Should draw an elipse ?
    RawCanvasBodyC::GUIDrawCircle(gc,World2GUIi(cent),Round((scale[0] + scale[1]) * size/2),fill); 
  }
  
  //: Draw an image into the canvas with its origin offset by 'offset'.
  // Note: You have to include the RavlGUI2d library to use this function.
  
  void RawZoomCanvasBodyC::GUIDrawImage(const ImageC<ByteRGBValueC> &image,const Point2dC &offset,bool ignoreImageOrigin) {
    cerr << "RawZoomCanvasBodyC::GUIDrawImage(), Called. \n";
    IndexRange2dC drawRect = World2GUIi(image.Frame());
    cerr << "DrawRect=" << drawRect << "\n";
    drawRect.ClipBy(widgetSize);
    if(drawRect.Area() <= 0)
      return ;
    cerr << "FinalDrawRect=" << drawRect << "\n";
    ImageC<ByteRGBValueC> drawImg(drawRect);
    for(Array2dIterC<ByteRGBValueC> it(drawImg);it;it++) {
      Index2dC at = Index2dC(GUI2World(it.Index()));
      if(!image.Frame().Contains(at))
	continue;
      *it = image[at];
    }
    RawCanvasBodyC::GUIDrawImage(drawImg,Index2dC(0,0),false);
  }
  
  //: Draw an image into the canvas with its origin offset by 'offset'.
  // Note: You have to include the RavlGUI2d library to use this function.
  
  void RawZoomCanvasBodyC::GUIDrawImage(const ImageC<ByteT> &image,const Point2dC &offset,bool ignoreImageOrigin) {
    cerr << "RawZoomCanvasBodyC::GUIDrawImage(), Called. \n";
    IndexRange2dC drawRect = World2GUIi(image.Frame());
    cerr << "DrawRect=" << drawRect << "\n";
    drawRect.ClipBy(widgetSize);
    if(drawRect.Area() <= 0)
      return ;
    ImageC<ByteT> drawImg(drawRect);
    for(Array2dIterC<ByteT> it(drawImg);it;it++) {
      Index2dC at = Index2dC(GUI2World(it.Index()));
      if(!image.Frame().Contains(at))
	continue;
      *it = image[at];
    }
    RawCanvasBodyC::GUIDrawImage(drawImg,Index2dC(0,0),false);    
  }
  
  //: Translate an expose event.
  // 'rect' is the area to be updated.
  // 'toFollow' is a count of how many expose events queued to follow this one.
  
  bool RawZoomCanvasBodyC::TranslateExposeEvent(const GdkEvent* event,RealRange2dC &rect,IntT &toFollow) {
    IndexRange2dC rng;
    RawCanvasBodyC::TranslateExposeEvent(event,rng,toFollow);
    rect = GUI2World(rng);
    return true;
  }
  
  //: Translate a configure event.
  // 'rect' is the new size for the widget.
  
  bool RawZoomCanvasBodyC::TranslateConfigureEvent(const GdkEvent* event,RealRange2dC &widgeSize) {
    IndexRange2dC rng;
    RawCanvasBodyC::TranslateConfigureEvent(event,rng);
    widgeSize = RealRange2dC(Point2dC(0,0),Point2dC(rng.End()) * scale);
    return true;    
  }
  
  
  //: Draw a line.  
  
  void RawZoomCanvasBodyC::GUIDrawLine(GdkGC *gc,Index2dC p1,Index2dC p2) {
    GUIDrawLine(gc,Point2dC(p1),Point2dC(p2));
  }
  
  //: Draw a rectangle.
  
  void RawZoomCanvasBodyC::GUIDrawRectangle(GdkGC *gc,const IndexRange2dC &rect,bool fill) {
    GUIDrawRectangle(gc,Point2dC(rect.Origin()),Point2dC(rect.End()),fill);
  }
  
  //: Draw a rectangle.
  
  void RawZoomCanvasBodyC::GUIDrawRectangle(GdkGC *gc,Index2dC topLeft,Index2dC bottomRight,bool fill) {
    GUIDrawRectangle(gc,Point2dC(topLeft),Point2dC(bottomRight),fill);
  }
  
  //: Draw text.
  // 'at' is the bottom left of the text to be drawn.
  
  void RawZoomCanvasBodyC::GUIDrawText(GdkGC *gc,GdkFont *font,Index2dC at,const StringC &txt) {
    GUIDrawText(gc,font,Point2dC(at),txt);
  }
  
  //: Find the size of 'text' rendered in 'font'.
  
  Index2dC RawZoomCanvasBodyC::GUITextSize(GdkFont *font,const StringC &txt) {
    Point2dC size;
    GUITextSize(font,txt,size);
    return Index2dC(size);
  }
  
  //: Draw a circle.
  
  void RawZoomCanvasBodyC::GUIDrawCircle(GdkGC *gc,Index2dC cent,UIntT size,bool fill) {
    GUIDrawCircle(gc,Point2dC(cent),(RealT) size,fill);
  }
  
  //: Draw an image into the canvas with its origin offset by 'offset'.
  // Note: You have to include the RavlGUI2d library to use this function.
  
  void RawZoomCanvasBodyC::GUIDrawImage(const ImageC<ByteRGBValueC> &image,const Index2dC &offset,bool ignoreImageOrigin) {
    GUIDrawImage(image,Point2dC(offset),ignoreImageOrigin);
  }
    
  //: Draw an image into the canvas with its origin offset by 'offset'.
  // Note: You have to include the RavlGUI2d library to use this function.
  
  void RawZoomCanvasBodyC::GUIDrawImage(const ImageC<ByteT> &image,const Index2dC &offset,bool ignoreImageOrigin) {
    GUIDrawImage(image,Point2dC(offset),ignoreImageOrigin);
  }
  
  //: Translate an expose event.
  // 'rect' is the area to be updated.
  // 'toFollow' is a count of how many expose events queued to follow this one.
  
  bool RawZoomCanvasBodyC::TranslateExposeEvent(const GdkEvent* event,IndexRange2dC &rect,IntT &toFollow) {
    RealRange2dC rec;
    TranslateExposeEvent(event,rec,toFollow);
    rect = rec.IndexRange();
    return true;
  }
  
  //: Translate a configure event.
  // 'rect' is the new size for the widget.
  
  bool RawZoomCanvasBodyC::TranslateConfigureEvent(const GdkEvent* event,IndexRange2dC &widgeSize) {
    RealRange2dC rec;
    TranslateConfigureEvent(event,rec);
    widgeSize = rec.IndexRange();
    return true;    
  }
  
  
}
