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
//! example=exDraw.cc

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/DrawLine.hh"
#include "Ravl/DList.hh"
#include "Ravl/DLIter.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array1dIter.hh"
#include "Ravl/Polygon2d.hh"

namespace RavlImageN {
  
  template<class DataT>
  void DrawPolygon(Array2dC<DataT> &dat,const DataT &value,const Polygon2dC &poly, bool fill=false) {
    // Draw one-colour polygon
    if (fill) {
      // TODO: Optimised triangle drawing (scan-line algorithm, probably)
      // Create bounding box for polygon
      ImageRectangleC bbox(poly.First(),0);
      for (DLIterC<Point2dC> it(poly); it; it++) {
	bbox.Involve(*it);
      }
      // This is a bit of a hack - for some reason, the bbox is not big enough...
      bbox.Expand(1);           
      // For each pixel inside bounding box...
      for (Array2dIterC<DataT> it(dat,bbox); it; it++) {
	// Check if pixel is inside polygon
	if (poly.Contains(it.Index())) {
	  *it = value;
	}
      }
    }
    else {
      // Draw individual lines
      for (DLIterC<Point2dC> it(poly); it; it++) {
	DrawLine(dat,value,it.Data(),it.NextCrcData());
      }
    }
  }

  //: This function requires that DataT has a working operator*(double) function
  template<class DataT>
  void DrawPolygon(Array2dC<DataT> &dat,const DListC<DataT>& values,const Polygon2dC &poly, bool fill=false) {
    // Draw shaded polygon
    if (fill) {
      // TODO: Optimised triangle drawing (scan-line algorithm, perhaps)
      // Create bounding box for polygon
      ImageRectangleC bbox(poly.First(),0);
      for (DLIterC<Point2dC> it(poly); it; it++) {
	bbox.Involve(*it);
      }
      // This is a bit of a hack - for some reason, the bbox is not big enough...
      bbox.Expand(1);           
      // For each pixel inside bounding box...
      for (Array2dIterC<DataT> it(dat,bbox); it; it++) {
	// Check if pixel is inside polygon
	Point2dC pnt(it.Index());
	if (poly.Contains(pnt)) {
	  // Calculate barycentric coords
	  SArray1dC<RealT> coord = poly.BarycentricCoordinate(pnt);
	  // Calculate interpolated value
	  DataT value;
	  SetZero(value);
	  SArray1dIterC<RealT> cit(coord);
	  DLIterC<DataT> vit(values);
	  while (cit && vit) {
	    value += DataT(vit.Data() * cit.Data());
	    cit++;
	    vit++;
	  }
	  // Set value
	  *it = value;
	}
      }
    }
    else {
      // Draw individual lines in the first colour specified
      for (DLIterC<Point2dC> it(poly); it; it++) {
	DrawLine(dat,values.First(),it.Data(),it.NextCrcData());
      }
    }      
  }
  
}

#endif
