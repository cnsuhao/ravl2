// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_MLESAC_HEADER
#define RAVLMATH_MLESAC_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Optimisation"
//! example="OrthogonalRegressionTest.cc"

#include <Ravl/StoredState.hh>

namespace RavlN {
  
  //! userlevel=Normal
  //! autoLink=on
  //: RANSAC algorithm class
  // This is the maximum-likelihood version of RANSAC (MLESAC) as introduced
  // by Phil Torr.
  class MlesacC
    : public StoredStateC
  {
  public:
    MlesacC();
    //: Constructor.

    virtual ~MlesacC(){}
    //: Virtual destructor,

    virtual StateVectorC SampleSolution();
    //: Generate a solution computed from a MLESAC sample

    virtual RealT SampleLikelihood(StateVectorC &state_vec);
    //: Compute negative log-likelihood for given sample state vector

  private:
    RealT likelihood; // current lowest negative log-likelihood

  public:
    bool ProcessSample();
    //: Generate sample, compute likelihood and update best solution

    RealT GetLikelihood() const;
    //: Return the lowest likelihood value found so far 
  };
}


#endif
