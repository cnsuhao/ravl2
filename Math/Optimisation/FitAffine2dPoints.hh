// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_FITAFFINEPOINTS_HEADER
#define RAVLMATH_FITAFFINEPOINTS_HEADER 1
//! userlevel=Normal
//! author="Charles Galambos"
//! date="1/10/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Optimisation.Examples"
//! example="AffineFitTest.cc"
//! lib=RavlOptimise

#include "Ravl/FitToSample.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //! autoLink=on
  //: This class fits a affine curve to a sample of (x,y) points
  
  class FitAffine2dPointsC
    : public FitToSampleC
  {
  public:
    FitAffine2dPointsC();
    //: Constructor for a class to fit a affine curve to (x,y) points
    
    StateVectorC FitModel(DListC<ObservationC> sample);
    //: Fit affine curve y = a*x^2 + b*x + c to (x,y) points
  };
}


#endif
