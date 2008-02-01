// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMathIO
//! file="Ravl/Math/IO/Geom2dIO.cc"

#include "Ravl/Point2d.hh"
#include "Ravl/LinePP2d.hh"
#include "Ravl/Polygon2d.hh"
#include "Ravl/PolyLine2d.hh"

#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/DList.hh"

namespace RavlN {
  void InitGeom2dIO()
  {}
  
  static TypeNameC type1(typeid(LinePP2dC),"LinePP2dC");
  static TypeNameC type2(typeid(DListC<LinePP2dC>),"DListC<LinePP2dC>");
  static TypeNameC type3(typeid(Polygon2dC),"RavlN::Polygon2dC");
  static TypeNameC type4(typeid(PolyLine2dC),"RavlN::PolyLine2dC");
  static TypeNameC type5(typeid(RavlN::PointSet2dC),"RavlN::PointSet2dC");
  static TypeNameC type6(typeid(DListC<Point2dC>),"RavlN::DListC<RavlN::Point2dC>");
  
  FileFormatStreamC<Point2dC> FileFormatStream_LinePP2d;
  FileFormatBinStreamC<Point2dC> FileFormatBinStream_LinePP2d;
  
  // Add some IO for listss of lines.
  
  FileFormatStreamC<DListC<LinePP2dC> > FileFormatStream_DListC_LinePP2d;
  FileFormatBinStreamC<DListC<LinePP2dC> > FileFormatBinStream_DListC_LinePP2d;
  
  // Add some IO for polygons
  
  FileFormatStreamC<Polygon2dC> FileFormatStream_Polygon2d;
  FileFormatBinStreamC<Polygon2dC> FileFormatBinStream_Polygon2d;
  
  // Add some IO for PolyLines
  
  FileFormatStreamC<PolyLine2dC> FileFormatStream_PolyLine2d;
  FileFormatBinStreamC<PolyLine2dC> FileFormatBinStream_PolyLine2d;
  
}
