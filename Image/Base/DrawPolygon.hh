// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_DRAWPOLYGON_HEADER
#define RAVLIMAGE_DRAWPOLYGON_HEADER 1
///////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="James"
//! date="27/10/2002"
//! docentry="Ravl.Images"
//! lib=RavlImage
//! userlevel=Normal
//! file="Ravl/Image/Base/DrawPolygon.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/DrawLine.hh"
#include "Ravl/DList.hh"
#include "Ravl/CDLIter.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Polygon2d.hh"

namespace RavlImageN {
  
  template<class DataT>
  void DrawPolygon(Array2dC<DataT> &dat,const DataT &value,const Polygon2dC &poly, bool fill=false) {
    // Draw one-colour polygon
    if (fill) {
      // TODO: Optimised triangle drawing (scan-line algorithm, probably)
      // Create bounding box for polygon
      ImageRectangleC bbox(UVToPixel(oPolygon.List()[0],Rectangle()),0);
      for (DLIterC<Point2dC> it(polygon); it; it++) {
	bbox.Involve(*i);
      }
      // This is a bit of a hack - for some reason, the bbox is not big enough...
      recBBox.Expand(1);           
      // For each pixel inside bounding box...
      for (Array2dIterC<DataT> it(dat,bbox); it; it++) {
	// Check if pixel is inside polygon
	if (polygon.Contains(it.Index())) {
	  *it = value;
	}
      }
    }
    else {
      // Draw individual lines
      for (DLIterC<Point2dC> it(polygon); it; it++) {
	DrawLine(dat,value,it.Data(),it.NextCrcData());
      }
    }
  }

  template<class DataT>
  void DrawPolygon(Array2dC<DataT> &dat,const DListC<DataT>& values,const Polygon2dC &poly, bool fill=false) {
    // TODO: Optimised triangle drawing (scan-line algorithm, perhaps)
    // Create bounding box for polygon
    ImageRectangleC bbox(UVToPixel(oPolygon.List()[0],Rectangle()),0);
    for (DLIterC<Point2dC> it(polygon); i; i++) {
      bbox.Involve(*i);
    }
    // This is a bit of a hack - for some reason, the bbox is not big enough...
    recBBox.Expand(1);           
    // For each pixel inside bounding box...
    for (Array2dIterC<DataT> it(dat,bbox); it; it++) {
      // Check if pixel is inside polygon
      if (polygon.Contains(it.Index())) {
	// Calculate barycentric coords
	DListC<RealT> coord = polygon.BCoord(it.Data());
	// Calculate interpolated value
	DataT val;
	DLIterC<RealT> cit(coord);
	ConstDLIterC<RealT> vit(values);
	while (cit && vit) {
	  val += cit.Data() * vit.Data();
	  cit++;
	  vit++;
	}
	// Set value
	*it = value;
      }
    }
  }

}

#endif
