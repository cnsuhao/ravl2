// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_OBSERVATIONMANAGER_HEADER
#define RAVLMATH_OBSERVATIONMANAGER_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Optimisation"
//! example="OrthogonalRegressionTest.cc Homography2dFitTest.cc FitQuadraticTest.cc"
//! lib=RavlOptimise

#include <Ravl/StateVector.hh>
#include <Ravl/Observation.hh>
#include "Ravl/DList.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //! autoLink=on
  //: Observation sampling base class
  // This class manages the set of observations to fitted to by RANSAC etc.
  // Derive a sub-class directly from this class if you don't want to construct
  // the complete set of candidate observations up front.
  class ObservationManagerC
  {
  public:
    ObservationManagerC();
    //: Constructor.

    virtual void UnselectAllObservations();
    //: Set the "selected" flag for all observations to false

    virtual DListC<ObservationC> RandomSample(UIntT min_num_constraints);
    //: Generate a random sample of observations
    // This virtual function generates a small random sample of observations,
    // which provide at least the given number of constraints. The constraints
    // may contain degeneracies, which should be picked up when you attempt to
    // fit the state vector parameters to the sample observations;
    // see the class FitToSampleC.
    // <p>
    // The sample should ignore all previously selected observations since the
    // last call to UnselectAllObservations(). This allows you to specify a
    // second (usually larger) samples excluding the original sample.

    virtual DListC<ObservationC> ObservationList(const StateVectorC &state_vec) const;
    //: Generate the set of observations to be evaluated
    // This virtual function returns the set of observations to be evaluated
    // by RANSAC. It can use the provided fitted state vector as a context for
    // preselecting observations from a larger internal list.
    // <p>
    // This can be written to ignore all previously selected observations,
    // so that observations from samples already selected will be ignored,
    // on the assumption that their contribution to the evaluation is already
    // known. Use the "selected" flags in the ObservationC class to achieve
    // this.
  };

  //! userlevel=Normal
  //! autoLink=on
  //: Observation sampling class with explicit observation list
  // This class manages the set of observations to fitted to by RANSAC etc,
  // given an explicit list of the complete set of observations.
  class ObservationListManagerC
    : public ObservationManagerC
  {
  public:
    ObservationListManagerC(DListC<ObservationC> obs_list);
    //: Constructor.

    virtual ~ObservationListManagerC(){}
    //: Virtual destructor,

    void UnselectAllObservations();
    //: Set the "selected" flag for all observations to false

    virtual DListC<ObservationC> RandomSample(UIntT min_num_constraints);
    //: Generate a random sample of observations
    // This virtual function generates a small random sample of observations,
    // which provide at least the given number of constraints. The constraints
    // may contain degeneracies, which should be picked up when you attempt to
    // fit the state vector parameters to the sample observations;
    // see the class FitToSampleC.
    // <p>
    // The sample should ignore all previously selected observations since the
    // last call to UnselectAllObservations(). This allows you to specify a
    // second (usually larger) samples excluding the original sample.

    virtual DListC<ObservationC> ObservationList(const StateVectorC &state_vec) const;
    //: Generate the set of observations to be evaluated
    // This virtual function returns the set of observations to be evaluated
    // by RANSAC. It can use the provided fitted state vector as a context for
    // preselecting observations from a larger internal list.
    // <p>
    // This can be written to ignore all previously selected observations,
    // so that observations from samples already selected will be ignored,
    // on the assumption that their contribution to the evaluation is already
    // known.

  protected:
    DListC<ObservationC> obs_list; // list of observations
    SArray1dC<ObservationC> obs_array; // array of observations
  };
}


#endif
