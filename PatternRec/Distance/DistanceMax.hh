// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPATRECDISTANCEMAX_HEADER 
#define RAVLPATRECDISTANCEMAX_HEADER 1
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/Distance.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Distance body.
  
  class DistanceMaxBodyC
    : public DistanceBodyC
  {
  public:
    DistanceMaxBodyC()
      {}
    //: Default constructor.
    
    virtual RealT Measure(const VectorC &d1,const VectorC &d2) const;
    //: Measure the distance from d1 to d2.
    
  };

  //! userlevel=Develop
  //: Distance Metric
  
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
