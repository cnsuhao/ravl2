// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_FITHOMOG2DPOINTS_HEADER
#define RAVLMATH_FITHOMOG2DPOINTS_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Optimisation.Examples"
//! example="Homography2dFitTest.cc"

#include <Ravl/FitToSample.hh>

namespace RavlN {
  
  //! userlevel=Normal
  //! autoLink=on
  //: This class fits a 2D homography to a sample of 2D points
  class FitHomog2dPointsC
    : public FitToSampleC
  {
  public:
    FitHomog2dPointsC(RealT zh1, RealT zh2);
    //: Constructor for a class to fit a 2D homography to pairs of points
    // zh1, zh2 are the 3rd homogeneous coordinates of the two planes on which
    // the point pairs lie.

    FitHomog2dPointsC();
    //: Constructor for a class to fit a 2D homography to pairs of points
    // The 3rd homogeneous coordinates of the two planes on which
    // the point pairs lie are set to one.

    StateVectorC FitModel(DListC<ObservationC> sample);
    //: Fit 2D homography to sample of 2D point observations

 private:
   RealT zh1, zh2; // 3rd homogeneous coordinates of planes on which points lie
  };
}


#endif
