// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPATRECDISTANCESQREUCLIDEAN_HEADER 
#define RAVLPATRECDISTANCESQREUCLIDEAN_HEADER 1
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! docentry="Ravl.Pattern Recognition.Distance"
//! file="Ravl/PatternRec/Distance/DistanceSqrEuclidean.hh"

#include "Ravl/PatternRec/Distance.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Euclidean distance body.
  
  class DistanceSqrEuclideanBodyC
    : public DistanceBodyC
  {
  public:
    DistanceSqrEuclideanBodyC()
      {}
    //: Default constructor.
    
    virtual RealT Measure(const VectorC &d1,const VectorC &d2) const;
    //: Measure the distance from d1 to d2.
    
  };

  //! userlevel=Normal
  //: SqrEuclidean distance metric
  
  class DistanceSqrEuclideanC
    : public DistanceC
  {
  public:
    DistanceSqrEuclideanC()
      : DistanceC(*new DistanceSqrEuclideanBodyC())
      {}
    //: Default constructor.
    
    
  };
  
}



#endif
