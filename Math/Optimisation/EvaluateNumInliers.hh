// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_EVALUATENUMINLIERS_HEADER
#define RAVLMATH_EVALUATENUMINLIERS_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Optimisation"
//! example="OrthogonalRegressionTest.cc Homography2dFitTest.cc QuadraticFitTest.cc"

#include <Ravl/EvaluateSolution.hh>

namespace RavlN {
  
  //! userlevel=Normal
  //! autoLink=on
  //: Solution evaluation class
  // This class evaluates a proposed solution state vector by counting the
  // number of inlier observations
  class EvaluateNumInliersC
    : public EvaluateSolutionC
  {
  public:
    EvaluateNumInliersC(RealT chi2_thres, RealT compat_chi2_thres=0.0);
    //: Constructor.
    // If compat_chi2_thres is not supplied, it is set to the same value
    // as chi2_thres.

    virtual RealT SolutionScore(const StateVectorC &state_vec,
				DListC<ObservationC> &obs_list) const;
    //: Returns the number of inliers for the given state parameters

    virtual DListC<ObservationC> CompatibleObservations(
					const StateVectorC &state_vec,
					DListC<ObservationC> &obs_list) const;
    //: Returns the observations compatible with the given state parameters

  private:
    RealT chi2_thres; // Threshold on normalised residual
    RealT compat_chi2_thres; // Threshold for comaptibility list
  };
}

#endif
