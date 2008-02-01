// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include "Ravl/GUI/DPDisplayPoints.hh"
#include "Ravl/GUI/MarkupPoint2d.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/DP/Converter.hh"

namespace RavlGUIN {

  
  //: Constructor
  
  DPDisplayPointsBodyC::DPDisplayPointsBodyC(const DListC<Point2dC> &points) 
    : m_points(points)
  {}
  
  //: Constructor
  
  DPDisplayPointsBodyC::DPDisplayPointsBodyC(const Point2dC &point)
  { m_points.InsLast(point); }
  
  //: Draw object to canvas.
  
  bool DPDisplayPointsBodyC::Draw(FrameMarkupC &markup) {
    for(DLIterC<Point2dC> it(m_points);it;it++) {
      markup.Markup().InsLast(MarkupPoint2dC(m_id,LayerNo(),*it,MP2DS_CrossHair,true));
    }
    return true;
  }
  
  //: Find bounding box for object.
  
  IndexRange2dC DPDisplayPointsBodyC::Frame() const {
    DLIterC<Point2dC> it(m_points);
    if(!it)
      return IndexRange2dC();
    RealRange2dC rng(*it,0);
    for(it++;it;it++)
      rng.Involve(*it);
    return rng.IndexRange();
  }
  
  //: Query a point in the display.
  // Return true if point is within object.
  
  bool DPDisplayPointsBodyC::Query(const Vector2dC &pnt,StringC &text) {
    RealT minDist = Sqr(8);
    bool foundPoint = false;
    Point2dC minPos;
    for(DLIterC<Point2dC> it(m_points);it;it++) {
      RealT dist = pnt.SqrEuclidDistance(*it);
      if(dist < minDist) {
        minDist = dist;
        minPos = *it;
        foundPoint = true;
      }
    }
    if(foundPoint) {
      text = StringC("Point:") + StringOf(minPos);
      return true;
    }
    return false;
  }
  
  //: Save to a file.
  
  bool DPDisplayPointsBodyC::Save(const StringC &str) const {
    
    return false;
  }

  //------------------------------------------------------------------
  // Register some conversions as well.
  
  DPDisplayObjC Point2d2DPDisplayObj(const Point2dC &point) 
  { return DPDisplayPointsC(point); }
  
  DP_REGISTER_CONVERSION_NAMED(Point2d2DPDisplayObj,1,"DPDisplayObjC Point2d2DPDisplayObj(const Point2dC &) ");
  
  
  
  DPDisplayObjC DList_Point2d2DPDisplayObj(const DListC<Point2dC> &points) 
  { return DPDisplayPointsC(points); }
  
  DP_REGISTER_CONVERSION_NAMED(DList_Point2d2DPDisplayObj,1,"DPDisplayObjC DList_Point2d2DPDisplayObj(const DListC<Point2dC> &) ");
  
  void InitDPDisplayPoints() 
  {}
  
}
