// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlOptimise

#include "Ravl/ObservationManager.hh"
#include "Ravl/Random.hh"

namespace RavlN {

  //: Constructor.
  ObservationManagerC::ObservationManagerC()
  {
  }

  //: Set the "selected" flag for all observations to false
  void ObservationManagerC::UnselectAllObservations()
  {
    RavlAssertMsg(0,"ObservationManagerC::UnselectAllObservations(), Abstract method called ");
  }

  //: Generate a random sample of observations
  DListC<ObservationC> ObservationManagerC::RandomSample(UIntT min_num_constraints)
  {
    DListC<ObservationC> empty_obs_list;
    RavlAssertMsg(0,"ObservationManagerC::RandomSample(UIntT), Abstract method called ");
    return empty_obs_list;
  }
    
  //: Generate the set of observations to be evaluated
  DListC<ObservationC> ObservationManagerC::ObservationList(
					const StateVectorC &state_vec) const
  {
    DListC<ObservationC> empty_obs_list;
    RavlAssertMsg(0,"ObservationManagerC::ObservationList(DListC<ObservationC>, const StateVectorC &), Abstract method called ");
    return empty_obs_list;
  }
}

namespace RavlN {

  //: Constructor.
  ObservationListManagerC::ObservationListManagerC(DListC<ObservationC> nobs_list)
    : ObservationManagerC()
  {
    // copy a reference to the list
    obs_list = nobs_list;

    // convert list of observations to array
    obs_array = SArray1dC<ObservationC>(obs_list.Size());
    IntT i=0;
    for(DLIterC<ObservationC> it(obs_list);it;it++,i++)
      obs_array[i] = it.Data();
  }

  //: Set the "selected" flag for all observations to false
  void ObservationListManagerC::UnselectAllObservations()
  {
    for(SArray1dIterC<ObservationC> it(obs_array);it;it++)
      it.Data().SetUnSelected();
  }

  //: Generate a random sample of observations
  DListC<ObservationC> ObservationListManagerC::RandomSample(UIntT min_num_constraints) {
    SArray1dC<IntT> index(min_num_constraints);
    IntT i=0;
    UIntT num_constraints=0;

    // check that there are enough observations
    for(SArray1dIterC<ObservationC> it(obs_array);it;it++) {
      num_constraints += it.Data().GetNumConstraints();
      if(num_constraints >= min_num_constraints)
	break;
    }

    if(num_constraints < min_num_constraints)
      throw ExceptionC("Not enough data for sample in ObservationListManagerC::RandomSample(UIntT). ");

    // generate random sample
    num_constraints = 0;
    for(SArray1dIterC<IntT> it2(index);it2;it2++) {
      for(;;) {
	// add index of random observation to sample
	*it2 = RandomInt() % obs_array.Size();
	
	// check whether this observation is already selected
	if(obs_array[*it2].GetSelected())
	  continue;

	// set selected flag for observation
	obs_array[*it2].SetSelected();
	
	// accumulate the number of constraints
	num_constraints += obs_array[*it2].GetNumConstraints();
	
	// get next element in sample
	break;
      }

      // check whether we have got enough constraints now
      if(num_constraints >= min_num_constraints)
	break;
    }
    
    // build sample list of observations
    DListC<ObservationC> sample;
    for(;i>=0;i--)
      sample.InsLast(obs_array[index[i]]);

    return sample;
  }
    
  //: Generate the set of observations to be evaluated
  DListC<ObservationC> ObservationListManagerC::ObservationList(
					const StateVectorC &state_vec) const
  {
    return obs_list;
  }
}
