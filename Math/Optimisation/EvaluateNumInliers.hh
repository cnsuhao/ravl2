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
//! lib=RavlOptimise

#include "Ravl/EvaluateSolution.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Solution evaluation body class
  class EvaluateNumInliersBodyC
    : public EvaluateSolutionBodyC
  {
  public:
    EvaluateNumInliersBodyC()
    {}
    //: Default constructor

    EvaluateNumInliersBodyC(RealT chi2Thres, RealT compatChi2Thres);
    //: Constructor.

    virtual RealT SolutionScore(const StateVectorC &StateVec,
				DListC<ObservationC> &obsList) const;
    //: Returns the number of inliers for the given state parameters

    virtual DListC<ObservationC> CompatibleObservations(
					const StateVectorC &StateVec,
					DListC<ObservationC> &obsList) const;
    //: Returns the observations compatible with the given state parameters

  private:
    RealT chi2Thres; // Threshold on normalised residual
    RealT compatChi2Thres; // Threshold for comaptibility list
  };

  //! userlevel=Normal
  //! autoLink=on
  //: Solution evaluation class
  // This class evaluates a proposed solution state vector by counting the
  // number of inlier observations
  class EvaluateNumInliersC
    : public EvaluateSolutionC
  {
  public:
    EvaluateNumInliersC()
    {}
    //: Default constructor
    // Creates an invalid handle
    
    EvaluateNumInliersC(RealT chi2Thres, RealT compatChi2Thres=0.0)
      : EvaluateSolutionC(*new EvaluateNumInliersBodyC(chi2Thres,compatChi2Thres))
    {}
    //: Constructor.
    // If compatChi2Thres is not supplied, it is set to the same value
    // as chi2Thres.

    EvaluateNumInliersC(const EvaluateSolutionC &evaluator)
      : EvaluateSolutionC(evaluator)
    {
      if(dynamic_cast<EvaluateNumInliersBodyC *>(&EvaluateSolutionC::Body()) == 0)
	Invalidate();
    }
    //: Base class constructor.
    
  public:
    EvaluateNumInliersC(EvaluateNumInliersBodyC &bod)
      : EvaluateSolutionC(bod)
    {}
    //: Body constructor.
    
    EvaluateNumInliersBodyC &Body()
    { return static_cast<EvaluateNumInliersBodyC &>(EvaluateSolutionC::Body()); }
    //: Access body.

    const EvaluateNumInliersBodyC &Body() const
    { return static_cast<const EvaluateNumInliersBodyC &>(EvaluateSolutionC::Body()); }
    //: Access body.
  };

}

#endif
