// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////////
//! rcsid="$Id: FixedPointIO.cc 737 2002-01-31 14:55:49Z craftit $"
//! lib=RavlMathIO
//! file="Ravl/Math/IO/FixedPointIO.cc"

#include "Ravl/Point2d.hh"
#include "Ravl/Point3d.hh"
#include "Ravl/Point4d.hh"
#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/SArray1d.hh"

namespace RavlN {
  void InitFixedPointIO()
  {}
  
  static TypeNameC type1(typeid(Point2dC),"Point2dC");
  static TypeNameC type2(typeid(Point3dC),"Point3dC");
  static TypeNameC type3(typeid(Point4dC),"Point4dC");
  
  static TypeNameC type4(typeid(SArray1dC<Point2dC>),"SArray1dC<Point2dC>");
  static TypeNameC type5(typeid(SArray1dC<Point3dC>),"SArray1dC<Point3dC>");
  static TypeNameC type6(typeid(SArray1dC<Point4dC>),"SArray1dC<Point4dC>");
  
  
  FileFormatStreamC<Point2dC> FileFormatStream_Point2d;
  FileFormatStreamC<Point3dC> FileFormatStream_Point3d;
  FileFormatStreamC<Point4dC> FileFormatStream_Point4d;
  
  FileFormatBinStreamC<Point2dC> FileFormatBinStream_Point2d;
  FileFormatBinStreamC<Point3dC> FileFormatBinStream_Point3d;
  FileFormatBinStreamC<Point4dC> FileFormatBinStream_Point4d;
  
  // Add some IO for arrays of Points.

  FileFormatStreamC<SArray1dC<Point2dC> > FileFormatStream_SArray1dC_Point2d;
  FileFormatStreamC<SArray1dC<Point3dC> > FileFormatStream_SArray1dC_Point3d;
  FileFormatStreamC<SArray1dC<Point4dC> > FileFormatStream_SArray1dC_Point4d;
  
  FileFormatBinStreamC<SArray1dC<Point2dC> > FileFormatBinStream_SArray1dC_Point2d;
  FileFormatBinStreamC<SArray1dC<Point3dC> > FileFormatBinStream_SArray1dC_Point3d;
  FileFormatBinStreamC<SArray1dC<Point4dC> > FileFormatBinStream_SArray1dC_Point4d;
  
}
