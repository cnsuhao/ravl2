// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"

#include "Ravl/RansacObsListSampling.hh"
#include "Ravl/Random.hh"

namespace RavlN {

  //: Constructor
  // Stores the given list of point observations and the sample size
  RansacObsListSamplingC::RansacObsListSamplingC(DListC<ObservationC> obs_list,
						 UIntT nsample_size,
						 RealT nchi2_thres)
    : RansacObsListC(obs_list)
  {
    if ( nsample_size == 0 || nsample_size > obs_list.Size() )
      throw ExceptionC("Illegal sample size in RansacObsListSamplingC::RansacObsListSamplingC(). ");

    sample_size = nsample_size;
    chi2_thres = nchi2_thres;
  }

  //: Generate a solution computed from a RANSAC sample
  StateVectorC RansacObsListSamplingC::SampleSolution()
  {
    SArray1dC<IntT> index(sample_size);
    IntT i=0;

    // generate random sample
    for(SArray1dIterC<IntT> it(index);it;it++, i++) {
      for(;;) {
	// add index of random observation to sample
	index[i] = RandomInt() % obs_array.Size();

	// check for repetitions in sample
	IntT ip=0;
	for(SArray1dIterC<IntT> itp(index);ip != i;itp++, ip++)
	  if(index[ip] == index[i])
	    break;

	if(i == ip) break;
      }
    }
      
    // build sample list of observations
    DListC<ObservationC> sample;
    i=0;
    for(SArray1dIterC<IntT> it(index);it;it++, i++)
      sample.InsLast(obs_array[index[i]]);

    // fit state parameters to sample
    return FitToSample(sample);
  }

  //: Compute vote (number of inliers) for given sample state vector
  UIntT RansacObsListSamplingC::SampleVote(StateVectorC &state_vec)
  {
    UIntT total_vote=0;
    for(SArray1dIterC<ObservationC> it(obs_array);it;it++) {
      RealT residual = it.Data().Residual(state_vec);
      if ( residual < chi2_thres )
	total_vote++;
    }

    return total_vote;
  }

  //: Fit parameters to sample of observations
  StateVectorC RansacObsListSamplingC::FitToSample(DListC<ObservationC> sample)
  {
    RavlAssertMsg(0,"RansacObsListSamplingC::FitToSample(DListC<ObservationC> sample), Abstract method called ");
    return StateVectorC();
  }    
}
