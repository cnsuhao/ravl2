// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_RANSAC_HEADER
#define RAVLMATH_RANSAC_HEADER 1
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
  // This is a generic implementation of RANSAC based on the original
  // idea of maximising the number of inlier measurements over a number of
  // samples
  class RansacC
    : public StoredStateC
  {
  public:
    RansacC();
    //: Constructor.

    virtual ~RansacC(){}
    //: Virtual destructor,

    virtual StateVectorC SampleSolution();
    //: Generate a solution computed from a RANSAC sample

    virtual UIntT SampleVote(StateVectorC &state_vec);
    //: Compute vote (number of inliers) for given sample state vector

  private:
    UIntT vote; // best vote so far

  public:
    bool ProcessSample();
    //: Generate sample, compute vote and update best solution and vote

    RealT GetVote() const;
    //: Return the highes vote found so far 
  };
}


#endif
