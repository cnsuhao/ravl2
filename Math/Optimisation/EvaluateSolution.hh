// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_EVALUATESOLUTION_HEADER
#define RAVLMATH_EVALUATESOLUTION_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Optimisation"
//! example="OrthogonalRegressionTest.cc Homography2dFitTest.cc QuadraticFitTest.cc"
//! lib=RavlOptimise

#include <Ravl/StateVector.hh>
#include <Ravl/Observation.hh>
#include <Ravl/DList.hh>

namespace RavlN {
  
  //! userlevel=Normal
  //! autoLink=on
  //: Solution evaluation class
  // This class evaluates a proposed solution state vector
  class EvaluateSolutionC
  {
  public:
    EvaluateSolutionC();
    //: Constructor.

    virtual RealT SolutionScore(const StateVectorC &state_vec,
				DListC<ObservationC> &obs_list) const;
    //: Returns the score/vote/likelihood for the given state parameters

    virtual DListC<ObservationC> CompatibleObservations(
					const StateVectorC &state_vec,
					DListC<ObservationC> &obs_list) const;
    //: Returns the observations compatible with the given state parameters
  };
}

#endif
