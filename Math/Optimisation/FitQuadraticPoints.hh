// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_FITQUADRATICPOINTS_HEADER
#define RAVLMATH_FITQUADRATICPOINTS_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Optimisation.Examples"
//! example="QuadraticFitTest.cc"

#include <Ravl/FitToSample.hh>

namespace RavlN {
  
  //! userlevel=Normal
  //! autoLink=on
  //: This class fits a quadratic curve to a sample of (x,y) points
  class FitQuadraticPointsC
    : public FitToSampleC
  {
  public:
    FitQuadraticPointsC();
    //: Constructor for a class to fit a quadratic curve to (x,y) points

    StateVectorC FitModel(DListC<ObservationC> sample);
    //: Fit quadratic curve y = a*x^2 + b*x + c to (x,y) points
  };
}


#endif
