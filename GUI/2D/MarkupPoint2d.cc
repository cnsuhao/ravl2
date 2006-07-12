// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, Omniperception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: fixSource.cfg 5642 2006-06-23 10:51:11Z craftit $"
//! lib=RavlGUI2D

#include "Ravl/GUI/MarkupPoint2d.hh"
#include "Ravl/GUI/GUIMarkupCanvas.hh"
#include "Ravl/Projection2d.hh"
#include "Ravl/OS/SysLog.hh"
#include "Ravl/RCWrap.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  
  //: Constructor.
  
  MarkupPoint2dBodyC::MarkupPoint2dBodyC(Int64T id, IntT zOrder, Point2dC & cn)
    : MarkupInfoBodyC(id,zOrder),
      centre(cn),
      sigPosition(Point2dC())
  {}

  
  //: Method for rendering frame.  
  bool MarkupPoint2dBodyC::Render(GUIMarkupCanvasBodyC &mv,const RealRange2dC &area,bool selected) { 
    // Set up the gc
    if (!SetDrawStyle(mv))
      return true;
    GdkGC *dc = mv.GcDrawContext();

    IntT size = 10;
    Point2dC ver(0,size/2);
    Point2dC hor(size/2,0);

    for (int i=0; i<2; i++) {
      for (int j=0; j<2; j++) {
        Point2dC start(centre);
        if (i==0) start += ver;
        else start -= ver;
        if (j==0) start += hor;
        else start -= hor;
        for (int k=0; k<2; k++) {
          Point2dC end(start);
          // Vertical
          if (k==0) {
            if (i==0) end += ver;
            else end -= ver;
          }
          // Horizontal
          else {
            if (j==0) end += hor;
            else end -= hor;
          }	  
          // Draw
          Index2dC from(start);
          Index2dC to(end);
          mv.GUIDrawLine(dc, from, to);
        }
      }
    }
    Index2dC horline(Round(centre.Row()), Round(centre.Col()-5.));
    Index2dC horline2(Round(centre.Row()), Round(centre.Col()+5));
    Index2dC verline(Round(centre.Row()-5.), Round(centre.Col()));
    Index2dC verline2(Round(centre.Row()+5.), Round(centre.Col()));

    mv.GUIDrawLine(dc, horline, horline2);
    mv.GUIDrawLine(dc, verline, verline2);

    return true;
  }

  RealRange2dC MarkupPoint2dBodyC::Extent(GUIMarkupCanvasBodyC &mv) const {
    RealRange2dC rextent(centre.Row()-10, centre.Row()+10, centre.Col()-10, centre.Col()+10);
    // Involve extent of children

    return rextent;
  }

  RealT MarkupPoint2dBodyC::SelectTest(GUIMarkupCanvasBodyC &mv,const Point2dC &at,const MouseEventC &me) {
    RealRange2dC rextent(centre.Row()-5,centre.Row()+5,centre.Col()-5,centre.Col()+5);
    if(rextent.Contains(at))
      return 1;
    return -1;
  }

  bool MarkupPoint2dBodyC::MouseEventPress(GUIMarkupCanvasBodyC &mv,const Point2dC &at,const MouseEventC &me,IntT &state,bool &refresh) {
    //cerr << "MarkupPoint2dBodyC::MouseEventPress() At=" << at << " State=" << state << " " << " ";
    //cerr << " Press " << me.HasChanged(0) << " " << me.HasChanged(1) << " " << me.HasChanged(2) << " " << me.HasChanged(3) << " " << " " << me.HasChanged(4) << " ";
    if(me.HasChanged(0)) { // Button 0 press ?
      mv.GUIClearSelect(false);
      mv.GUIAddSelect(Id());
      oldPosition = mv.MousePressAt();
      refresh = true;
      return true;
    }
    return false;
  }
  
  //: Handle mouse event.
  // Returns true if even has been handled.
  
  bool MarkupPoint2dBodyC::MouseEventMove(GUIMarkupCanvasBodyC &mv,const Point2dC &at,const MouseEventC &me,IntT &state,bool &refresh) {
    //cerr << "MarkupPoint2dBodyC::MouseEventMove() At=" << at << " State=" << state << " " << " ";
    //cerr << " Press " << me.HasChanged(0) << " " << me.HasChanged(1) << " " << me.HasChanged(2) << " " << me.HasChanged(3) << " " << " " << me.HasChanged(4) << " ";
    Point2dC offset = (at - oldPosition);
    centre += offset;
    oldPosition = centre;
    refresh = true;
    return true;
  }
  
  //: Handle mouse event.
  // Returns true if even has been handled.
  
  bool MarkupPoint2dBodyC::MouseEventRelease(GUIMarkupCanvasBodyC &mv,const Point2dC &at,const MouseEventC &me,IntT &state,bool &refresh) {
    //cerr << "MarkupPoint2dBodyC::MouseEventRelease() At=" << at << " State=" << state << " " << " ";
    //cerr << " Press " << me.HasChanged(0) << " " << me.HasChanged(1) << " " << me.HasChanged(2) << " " << me.HasChanged(3) << " " << " " << me.HasChanged(4) << " ";
    //: Signal position change on mouse release
    sigPosition(centre);
    return false;
  }


  bool MarkupPoint2dBodyC::Position(const Point2dC & newPosition) {
    centre = newPosition;
    oldPosition = centre;
    return true;
  }
 

  
}
