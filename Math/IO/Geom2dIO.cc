// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMathIO

#include "Ravl/Point2d.hh"
#include "Ravl/LinePP2d.hh"

#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/DList.hh"

namespace RavlN {
  void InitGeom2dIO()
  {}
  
  static TypeNameC type1(typeid(LinePP2dC),"LinePP2dC");
  static TypeNameC type2(typeid(DListC<LinePP2dC>),"DListC<LinePP2dC>");
  
  FileFormatStreamC<Point2dC> FileFormatStream_LinePP2d;
  
  FileFormatBinStreamC<Point2dC> FileFormatBinStream_LinePP2d;
  
  // Add some IO for arrays of Points.
  
  FileFormatStreamC<DListC<LinePP2dC> > FileFormatStream_DListC_LinePP2d;
  
  FileFormatBinStreamC<DListC<LinePP2dC> > FileFormatBinStream_DListC_LinePP2d;
  
}
