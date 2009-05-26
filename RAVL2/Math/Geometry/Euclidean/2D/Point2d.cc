// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Geometry/Euclidean/2D/Point2d.cc"

#include "Ravl/Point2d.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/Matrix3d.hh"

namespace RavlN {
  
  //: Normalise an array of points.
  // This finds the mean and variation of euclidean point position. It corrects the mean to zero
  // and the average variation to 1.
  //!param: raw - Raw points to be normalised
  //!param: norm - Normalised points.
  //!param: normMat - Normalisation matrix 
  //!return: Normalisation found and applied.
  
  bool Normalise(const SArray1dC<Point2dC> &raw,SArray1dC<Point2dC> &norm,Matrix3dC &normMat) {
    if(raw.Size() == 0)
      return true;
    norm = SArray1dC<Point2dC>(raw.Size());
    Point2dC mean(0,0);
    for(SArray1dIter2C<Point2dC,Point2dC> it(raw,norm);it;it++) {
      RavlAssert(!IsNan(it.Data1()[0]) && !IsNan(it.Data1()[1]));
      it.Data2() = it.Data1();
      mean += it.Data1();
    }
    mean /= static_cast<RealT>(raw.Size());
    RealT d = 0;
    for(SArray1dIterC<Point2dC> it(norm);it;it++) {
      (*it) -= mean;
      d += Hypot((*it)[0],(*it)[1]);
    }
    d = IsSmall(d) ? 1.0 : (static_cast<RealT>(raw.Size())/d);
    for(SArray1dIterC<Point2dC> it(norm);it;it++)
      (*it) *= d;
    normMat = Matrix3dC(d,0,-mean[0] * d,
			0,d,-mean[1] * d,
			0,0,1);
    return true;    
  }

}
