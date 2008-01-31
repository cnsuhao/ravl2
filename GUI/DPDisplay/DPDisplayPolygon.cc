// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include "Ravl/GUI/DPDisplayPolygon.hh"
#include "Ravl/GUI/MarkupPolygon2d.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/DP/Converter.hh"

namespace RavlGUIN {

  
  //: Constructor
  
  DPDisplayPolygon2dBodyC::DPDisplayPolygon2dBodyC(const Polygon2dC &polygon) 
    : m_polygon(polygon)
  {}
  
  //: Draw object to canvas.
  
  bool DPDisplayPolygon2dBodyC::Draw(FrameMarkupC &markup) {
    markup.Markup().InsLast(MarkupPolygon2dC(m_id,1,m_polygon,true));
    return true;
  }
  
  //: Find bounding box for object.
  
  IndexRange2dC DPDisplayPolygon2dBodyC::Frame() const 
  { return m_polygon.BoundingRectangle().IndexRange(); }
  
  //: Query a point in the display.
  // Return true if point is within object.
  
  bool DPDisplayPolygon2dBodyC::Query(const Vector2dC &pnt,StringC &text) {
    if(m_polygon.Contains(pnt)) {
      StringC tmp = StringOf(m_polygon);
      tmp.gsub("\n",",");
      text = StringC("Polygon:") + tmp;
      return true;
    }
    return false;
  }
  
  //: Save to a file.
  
  bool DPDisplayPolygon2dBodyC::Save(const StringC &str) const {
    
    return false;
  }

  //------------------------------------------------------------------
  // Register some conversions as well.
  
  DPDisplayObjC Polygon2dPDisplayObj(const Polygon2dC &poly) 
  { return DPDisplayPolygon2dC(poly.Copy()); }
  
  DP_REGISTER_CONVERSION_NAMED(Polygon2dPDisplayObj,1,"DPDisplayObjC Polygon2d2DPDisplayObj(const Polygon2dC &) ");
  
  void InitDPDisplayPolygon2d() 
  {}
  
}
