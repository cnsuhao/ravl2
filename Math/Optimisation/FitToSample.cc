// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlOptimise

#include "Ravl/FitToSample.hh"

namespace RavlN {

  //: Constructor.
  FitToSampleC::FitToSampleC()
  {
  }

  //: Fit parameters to sample of observations
  StateVectorC FitToSampleC::FitModel(DListC<ObservationC> sample)
  {
    RavlAssertMsg(0,"FitToSampleC::FitModel(DListC<ObservationC>(), Abstract method called ");
    return StateVectorC();
  }
}
