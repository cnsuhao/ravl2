// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_FITLINE2DPOINTS_HEADER
#define RAVLMATH_FITLINE2DPOINTS_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Optimisation.Examples"
//! example="OrthogonalRegressionTest.cc"
//! lib=RavlOptimise

#include <Ravl/FitToSample.hh>

namespace RavlN {
  
  //! userlevel=Normal
  //! autoLink=on
  //: This class fits a 2D line to a sample of 2D points
  class FitLine2dPointsC
    : public FitToSampleC
  {
  public:
    FitLine2dPointsC(RealT zh);
    //: Constructor for a class to fit a 2D line to points on a plane
    // zh is the 3rd homogeneous coordinate of the plane on which the line and
    // the points lie.

    FitLine2dPointsC();
    //: Constructor for a class to fit a 2D line to points on a plane
    // The 3rd homogeneous coordinate of the plane on which the line and points
    // lie is set to one.

    StateVectorC FitModel(DListC<ObservationC> sample);
    //: Fit 2D line to sample of 2D point observations

 private:
   RealT zh; // 3rd homogeneous coordinate of plane on which line lies
  };
}


#endif
