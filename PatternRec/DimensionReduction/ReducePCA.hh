// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_REDUCEPCA_HEADER
#define RAVL_REDUCEPCA_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/ReduceLinear.hh"
#include "Ravl/VectorMatrix.hh"
#include "Ravl/PatternRec/Sample.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Dimention reduction by Principle Component Analysis
  
  class ReducePCABodyC
    : public ReduceLinearBodyC
  {
  public:
    ReducePCABodyC()
    {}
    //: Default constructor.
    
    void DesignHighDim(SampleC<VectorC> &sample,RealT variation);
    //: Design the transform.
    
    void DesignLowDim(SampleC<VectorC> &sample,RealT variation);
    //: Design the transform.
    
  protected:
    VectorMatrixC pca;
  };
  
  //! userlevel=Normal
  //: Dimention reduction by Principle Component Analysis
  
  class ReducePCAC
    : public ReduceLinearC
  {
  public:
    ReducePCAC()
    {}
    //: Default constructor.

  protected:
    ReducePCAC(ReducePCABodyC &bod)
      : ReduceLinearC(bod)
    {}
    //: Body constructor.
    
    ReducePCABodyC &Body()
    { return static_cast<ReducePCABodyC &>(Body()); }
    //: Access body.
    
    const ReducePCABodyC &Body() const
    { return static_cast<const ReducePCABodyC &>(Body()); }
    //: Access body.
    
  public:
    void DesignHighDim(SampleC<VectorC> &sample,RealT variation)
    { Body().DesignHighDim(sample,variation); }
    //: Design the PCA transform.
    
    void DesignLowDim(SampleC<VectorC> &sample,RealT variation)
    { Body().DesignHighDim(sample,variation); }
    //: Design the PCA transform.
    
  };
}


#endif
