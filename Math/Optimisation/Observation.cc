// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"

#include "Observation.hh"
#include "ObsVectorBiGaussian.hh"

namespace RavlN {
  
  //: Constructor.
  ObservationBodyC::ObservationBodyC(const ObsVectorC &nobs_vec)
  {
    obs_vec = nobs_vec;
  }

  //: Compute the Chi-squared residual
  RealT ObservationBodyC::SquareResidual(const StateVectorC &state_vec) {
    RavlAssertMsg(0,"ObservationBodyC::SquareResidual(const VectorC &), Abstract method called ");
    return 0;
  }
  
  //: Accumulate the linear system
  bool ObservationBodyC::IncrementLS(const StateVectorC &state_vec,
				     MatrixRSC &A,
				     VectorC &a) {
    RavlAssertMsg(0,"ObservationBodyC::IncrementLS(const VectorC &,MatrixRSC &,VectorC &) const, Abstract method called ");
    return false;
  }
  
  //: Get observation vector
  const VectorC& ObservationBodyC::GetZ() const
  {
    return obs_vec.GetZ();
  }

  //: Get observation inverse covariance
  const MatrixRSC& ObservationBodyC::GetNi() const
  {
    return obs_vec.GetNi();
  }

  //: Get observation vector/inverse covariance object
  const ObsVectorC& ObservationBodyC::GetObsVec() const
  {
    return obs_vec;
  }
}
