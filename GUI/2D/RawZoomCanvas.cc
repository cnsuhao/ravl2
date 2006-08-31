// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGUI2D
//! file="Ravl/GUI/2D/RawZoomCanvas.cc"

#include "Ravl/GUI/RawZoomCanvas.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/Pixbuf.hh"
#include "Ravl/Image/WarpScale.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/ByteIAValue.hh"
#include "Ravl/Threads/Signal1.hh"
#include "Ravl/QInt.hh"
#include "Ravl/Array2dIter2.hh"

#define DODEBUG 0
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
  
  //: Create the widget.
  
  bool RawZoomCanvasBodyC::Create(GtkWidget *nwidget) {
    ConnectRef(Signal("configure_event"),*this,&RawZoomCanvasBodyC::EventConfigure);
    return RawCanvasBodyC::Create(nwidget);
  }

  bool RawZoomCanvasBodyC::Create() {
    ConnectRef(Signal("configure_event"),*this,&RawZoomCanvasBodyC::EventConfigure);
    return RawCanvasBodyC::Create();
  }
  
  //: Handle configure event.
  
  bool RawZoomCanvasBodyC::EventConfigure(GdkEvent* &event) {    
    RawCanvasBodyC::TranslateConfigureEvent(event,widgetSize);
    ONDEBUG(cerr << "RawZoomCanvasBodyC::EventConfigure(), Called. Size=" << widgetSize << "\n");
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
  
  //: Access current offset.
  
  void RawZoomCanvasBodyC::SetOffset(const Vector2dC &off) {
    Manager.Queue(Trigger(RawZoomCanvasC(*this),&RawZoomCanvasC::GUISetOffset,off));
  }
  
  //: Access current scale.
  
  void RawZoomCanvasBodyC::SetScale(const Vector2dC &scale) {
    Manager.Queue(Trigger(RawZoomCanvasC(*this),&RawZoomCanvasC::GUISetScale,scale));
  }

  //: Draw a line.
  
  void RawZoomCanvasBodyC::GUIDrawLine(GdkGC *gc,Point2dC p1,Point2dC p2) 
  { RawCanvasBodyC::GUIDrawLine(gc,World2GUIi(p1),World2GUIi(p2)); }
  
  //: Draw a rectangle.
  
  void RawZoomCanvasBodyC::GUIDrawRectangle(GdkGC *gc,const RealRange2dC &rect,bool fill) 
  { RawCanvasBodyC::GUIDrawRectangle(gc,World2GUIi(rect.Origin()),World2GUIi(rect.End()) - Index2dC(1, 1), fill); }
  
  //: Draw a rectangle.
  
  void RawZoomCanvasBodyC::GUIDrawRectangle(GdkGC *gc,Point2dC topLeft,Point2dC bottomRight,bool fill) 
  { RawCanvasBodyC::GUIDrawRectangle(gc,World2GUIi(topLeft),World2GUIi(bottomRight) - Index2dC(1, 1),fill); }
  
  //: Draw text.
  // 'at' is the bottom left of the text to be drawn.
  
  void RawZoomCanvasBodyC::GUIDrawText(GdkGC *gc,GdkFont *font,Point2dC at,const StringC &txt)  { 
    // Scale font ?
    RawCanvasBodyC::GUIDrawText(gc,font,World2GUIi(at),txt); 
  }
  
  //: Find the size of 'text' rendered in 'font'.
  
  void RawZoomCanvasBodyC::GUITextSize(GdkFont *font,const StringC &txt,Point2dC &size) {
    size = Point2dC(RawCanvasBodyC::GUITextSize(font,txt))/scale; 
  }
  
  //: Draw a circle.
  
  void RawZoomCanvasBodyC::GUIDrawCircle(GdkGC *gc,Point2dC cent,RealT size,bool fill) 
  { 
    // Should draw an elipse ?
    RawCanvasBodyC::GUIDrawCircle(gc,World2GUIi(cent),Round((scale[0] + scale[1]) * size/2),fill); 
  }
  
  //: Draw an image into the canvas with its origin offset by 'offset'.
  // Note: You have to include the RavlGUI2d library to use this function.
  
  void RawZoomCanvasBodyC::GUIDrawImage(const ImageC<ByteRGBValueC> &image,const Point2dC &doffset,bool ignoreImageOrigin) {
    ONDEBUG(cerr << "RawZoomCanvasBodyC::GUIDrawImage(), Called. Offset=" << offset << "\n");
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    IndexRange2dC imgRect = World2GUIi(IndexRange2dC(image.Frame().RowRange().Min(), image.Frame().RowRange().Max() + 1, image.Frame().ColRange().Min(), image.Frame().ColRange().Max() + 1) + doffset);
    IndexRange2dC drawRect = IndexRange2dC(imgRect.RowRange().Min(), imgRect.RowRange().Max() - 1, imgRect.ColRange().Min(), imgRect.ColRange().Max() - 1);
    ONDEBUG(cerr << "DrawRect=" << drawRect << " widgetSize=" << widgetSize << "\n");
    drawRect.ClipBy(widgetSize);
    if(drawRect.Area() <= 0)
      return ;
    ONDEBUG(cerr << "FinalDrawRect=" << drawRect << "\n");
    
    if(Abs(scale[0] - 1) < 0.0001 && Abs(scale[0] - 1) < 0.0001) {
      RawCanvasBodyC::GUIDrawImage(image,Index2dC(doffset + offset),false);
    } else {
      ImageC<ByteRGBValueC> drawImg(drawRect);
      Vector2dC inc(1/scale[0],1/scale[1]);
      Array2dIterC<ByteRGBValueC> it(drawImg);
      Point2dC pat,start = GUI2World(it.Index()) + doffset;
      pat = start;
      for(;it;) {
        pat[1] = start[1];
        do {
          Index2dC at(QFloor(pat[0] < image.TRow().V() ? image.TRow().V() : pat[0]),
                      QFloor(pat[1] < image.LCol().V() ? image.LCol().V() : pat[1]));
          
          if(image.Frame().Contains(at))
            *it = image[at];
          else
            *it = ByteRGBValueC(255,0,0);
          pat[1] += inc[1];
        } while(it.Next());
        pat[0] += inc[0];
      }
      RawCanvasBodyC::GUIDrawImage(drawImg,Index2dC(0,0),false);
    }
  }
  
  //: Draw an image into the canvas with its origin offset by 'offset'.
  // Note: You have to include the RavlGUI2d library to use this function.
  
  void RawZoomCanvasBodyC::GUIDrawImage(const ImageC<ByteT> &image,const Point2dC &doffset,bool ignoreImageOrigin) {
    ONDEBUG(cerr << "RawZoomCanvasBodyC::GUIDrawImage(), Called. Offset=" << offset << "\n");
    IndexRange2dC imgRect = World2GUIi(IndexRange2dC(image.Frame().RowRange().Min(), image.Frame().RowRange().Max() + 1, image.Frame().ColRange().Min(), image.Frame().ColRange().Max() + 1) + doffset);
    IndexRange2dC drawRect = IndexRange2dC(imgRect.RowRange().Min(), imgRect.RowRange().Max() - 1, imgRect.ColRange().Min(), imgRect.ColRange().Max() - 1);
    ONDEBUG(cerr << "DrawRect=" << drawRect << " widgetSize=" << widgetSize << "\n");
    drawRect.ClipBy(widgetSize);
    if(drawRect.Area() <= 0)
      return ;
    ONDEBUG(cerr << "FinalDrawRect=" << drawRect << "\n");
    
    if(Abs(scale[0] - 1) < 0.0001 && Abs(scale[0] - 1) < 0.0001) {
      
      RawCanvasBodyC::GUIDrawImage(image,Index2dC(doffset + offset),false);
    } else {
      ImageC<ByteT> drawImg(drawRect);
      Vector2dC inc(1/scale[0],1/scale[1]);
      Array2dIterC<ByteT> it(drawImg);
      Point2dC pat,start = GUI2World(it.Index()) + doffset;
      pat = start;
      for(;it;) {
        pat[1] = start[1];
        do {
          Index2dC at(QFloor(pat[0] < image.TRow().V() ? image.TRow().V() : pat[0]),
                      QFloor(pat[1] < image.LCol().V() ? image.LCol().V() : pat[1]));
          if(image.Frame().Contains(at))
            *it = image[at];
          else
            *it = 0;
          pat[1] += inc[1];
        } while(it.Next());
        pat[0] += inc[0];
      }
      RawCanvasBodyC::GUIDrawImage(drawImg,Index2dC(0,0),false);
    }
  }
  
  //: Draw an image into the canvas with its origin offset by 'offset'.
  // Note: You have to include the RavlGUI2d library to use this function.
  
  void RawZoomCanvasBodyC::GUIDrawImage(const ImageC<ByteRGBAValueC> &image,const Point2dC &doffset,bool ignoreImageOrigin) {
    ONDEBUG(cerr << "RawZoomCanvasBodyC::GUIDrawImage(), Called. Offset=" << offset << "\n");
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    IndexRange2dC imgRect = World2GUIi(IndexRange2dC(image.Frame().RowRange().Min(), image.Frame().RowRange().Max() + 1, image.Frame().ColRange().Min(), image.Frame().ColRange().Max() + 1) + doffset);
    IndexRange2dC drawRect = IndexRange2dC(imgRect.RowRange().Min(), imgRect.RowRange().Max() - 1, imgRect.ColRange().Min(), imgRect.ColRange().Max() - 1);
    ONDEBUG(cerr << "DrawRect=" << drawRect << " widgetSize=" << widgetSize << "\n");
    drawRect.ClipBy(widgetSize);
    if(drawRect.Area() <= 0)
      return ;
    ONDEBUG(cerr << "FinalDrawRect=" << drawRect << "\n");
    
    if(Abs(scale[0] - 1) < 0.0001 && Abs(scale[0] - 1) < 0.0001 && 0) {
      PixbufC pixBuf(image);
      RawCanvasBodyC::GUIDrawImage(pixBuf,Index2dC(doffset + offset));
    } else {
      ImageC<ByteRGBAValueC> drawImg(drawRect);
      Vector2dC inc(1/scale[0],1/scale[1]);
      Array2dIterC<ByteRGBAValueC> it(drawImg);
      Point2dC pat,start = GUI2World(it.Index()) + doffset;
      pat = start;
      for(;it;) {
        pat[1] = start[1];
        do {
          Index2dC at(QFloor(pat[0] < image.TRow().V() ? image.TRow().V() : pat[0]),
                      QFloor(pat[1] < image.LCol().V() ? image.LCol().V() : pat[1]));
          if(image.Frame().Contains(at))
            *it = image[at];
          else
            *it = ByteRGBAValueC(255,0,0,255);
          pat[1] += inc[1];
        } while(it.Next());
        pat[0] += inc[0];
      }
      ONDEBUG(cerr << "RawZoomCanvasBodyC::GUIDrawImage, Frame=" << drawImg.Frame() << "\n");
      PixbufC pixBuf(drawImg);
      RawCanvasBodyC::GUIDrawImage(pixBuf,drawImg.Frame().Origin()); // 
    }
    
  }
  
  //: Draw an image into the canvas with its origin offset by 'offset'.
  // Note: You have to include the RavlGUI2d library to use this function.
  
  void RawZoomCanvasBodyC::GUIDrawImage(const ImageC<ByteIAValueC> &image,const Point2dC &doffset,bool ignoreImageOrigin) {
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    ONDEBUG(cerr << "RawZoomCanvasBodyC::GUIDrawImage(), Called. Offset=" << offset << "\n");
    IndexRange2dC imgRect = World2GUIi(IndexRange2dC(image.Frame().RowRange().Min(), image.Frame().RowRange().Max() + 1, image.Frame().ColRange().Min(), image.Frame().ColRange().Max() + 1) + doffset);
    IndexRange2dC drawRect = IndexRange2dC(imgRect.RowRange().Min(), imgRect.RowRange().Max() - 1, imgRect.ColRange().Min(), imgRect.ColRange().Max() - 1);
    ONDEBUG(cerr << "DrawRect=" << drawRect << " widgetSize=" << widgetSize << "\n");
    drawRect.ClipBy(widgetSize);
    if(drawRect.Area() <= 0)
      return ;
    ONDEBUG(cerr << "FinalDrawRect=" << drawRect << "\n");
    
    // A bit crap, but for the moment change this into an RGBA image.
    
    ImageC<ByteRGBAValueC> imgRGB(image.Frame());
    for(Array2dIter2C<ByteRGBAValueC,ByteIAValueC> it(imgRGB,image);it;it++) 
      it.Data1() = ByteRGBAValueC(it.Data2().Intensity(),it.Data2().Intensity(),it.Data2().Intensity(),it.Data2().Alpha());
    
    GUIDrawImage(imgRGB,doffset,ignoreImageOrigin);
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
