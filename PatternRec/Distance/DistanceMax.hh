// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DISTANCEMAX_HEADER 
#define RAVL_DISTANCEMAX_HEADER 1
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! docentry="Ravl.Pattern Recognition.Distance"
//! file="Ravl/PatternRec/Distance/DistanceMax.hh"

#include "Ravl/PatternRec/Distance.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Distance max body.
  // Returns the maximum difference between elements corresponding 
  // elements of the vector.
  
  class DistanceMaxBodyC
    : public DistanceBodyC
  {
  public:
    DistanceMaxBodyC()
      {}
    //: Default constructor.
    
    virtual RealT Measure(const VectorC &d1,const VectorC &d2) const;
    //: Measure the distance from d1 to d2.
    
    virtual RealT Magnitude(const VectorC &d1) const;
    //: Measure the magnitude of d1.
    
    virtual MatrixC Jacobian (const VectorC &X) const;
    //: Calculates Jacobian matrix at X
    
  };

  //! userlevel=Normal
  //: Distance max Metric
  // Returns the maximum difference between elements corresponding 
  // elements of the vector.
  
  class DistanceMaxC
    : public DistanceC
  {
  public:
    DistanceMaxC()
      : DistanceC(*new DistanceMaxBodyC())
      {}
    //: Default constructor.
    
    
  };
  
}



#endif
