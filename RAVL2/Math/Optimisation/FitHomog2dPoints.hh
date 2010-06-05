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
//! rcsid="$Id: FitHomog2dPoints.hh 6819 2008-05-30 12:01:36Z ees1wc $"
//! docentry="Ravl.API.Pattern Recognition.Optimisation2.Examples"
//! example="Homography2dFitTest.cc"
//! lib=RavlOptimise
//! file="Ravl/Math/Optimisation/FitHomog2dPoints.hh"

#include "Ravl/FitToSample.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Body class for fitting a 2D homography to a sample of 2D points
  class FitHomog2dPointsBodyC
    : public FitToSampleBodyC
  {
  public:
    FitHomog2dPointsBodyC(RealT zh1, RealT zh2);
    //: Constructor for a class to fit a 2D homography to pairs of points

    FitHomog2dPointsBodyC();
    //: Constructor for a class to fit a 2D homography to pairs of points
    
    virtual StateVectorC FitModel(DListC<ObservationC> sample);
    //: Fit 2D homography to sample of 2D point observations

  private:
    RealT zh1, zh2; // 3rd homogeneous coordinates of planes on which points lie
  };

  //! userlevel=Normal
  //! autoLink=on
  //: This class fits a 2D homography to a sample of 2D points
  class FitHomog2dPointsC
    : public FitToSampleC
  {
  public:
    FitHomog2dPointsC(RealT zh1, RealT zh2)
      : FitToSampleC(*new FitHomog2dPointsBodyC(zh1,zh2))
    {}
    //: Constructor for a class to fit a 2D homography to pairs of points
    // zh1, zh2 are the 3rd homogeneous coordinates of the two planes on which
    // the point pairs lie.

    FitHomog2dPointsC()
      : FitToSampleC(*new FitHomog2dPointsBodyC())
    {}
    //: Constructor for a class to fit a 2D homography to pairs of points
    // The 3rd homogeneous coordinates of the two planes on which
    // the point pairs lie are set to one.
    
    FitHomog2dPointsC(const FitToSampleC &fitter)
      : FitToSampleC(dynamic_cast<const FitHomog2dPointsBodyC *>(BodyPtr(fitter)))
    {}
    //: Base class constructor.
    
  public:
    FitHomog2dPointsC(FitHomog2dPointsBodyC &bod)
      : FitToSampleC(bod)
    {}
    //: Body constructor.
    
    FitHomog2dPointsBodyC &Body()
    { return static_cast<FitHomog2dPointsBodyC &>(FitToSampleC::Body()); }
    //: Access body.

    const FitHomog2dPointsBodyC &Body() const
    { return static_cast<const FitHomog2dPointsBodyC &>(FitToSampleC::Body()); }
    //: Access body.
  };
}


#endif
