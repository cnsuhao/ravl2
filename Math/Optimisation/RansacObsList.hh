// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_RANSACOBSLIST_HEADER
#define RAVLMATH_RANSACOBSLIST_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Optimisation"
//! example="OrthogonalRegressionTest.cc"

#include "Ravl/Ransac.hh"
#include "Ravl/DList.hh"
#include "Ravl/Observation.hh"
#include "Ravl/Array1d.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //! autoLink=on
  //: RANSAC algorithm class for 2D line fitting
  // RANSAC using a list of observations as the data to be fitted to
  class RansacObsListC
    : public RansacC
 {
 public:
   RansacObsListC(DListC<ObservationC> obs_list);
   //: Constructor.

 protected:
   SArray1dC<ObservationC> obs_array; // array of observations
  };
}


#endif
