// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DESIGNCLASSIFYVECTORUNSUPERVISED_HEADER
#define RAVL_DESIGNCLASSIFYVECTORUNSUPERVISED_HEADER 1
///////////////////////////////////////////////////////////
//! userlevel=Normal
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! docentry="Ravl.Pattern Recognition.Cluster"
//! file="Ravl/PatternRec/Classify/DesignClassifyVectorSupervised.hh"

#include "Ravl/RCHandleV.hh"
#include "Ravl/Vector.hh"
#include "Ravl/PatternRec/Sample.hh"
#include "Ravl/PatternRec/ClassifyVector.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Abstract unsupervised classifer designer.
  
  class DesignClassifyVectorUnsupervisedBodyC
    : public RCBodyVC
  {
  public:
    DesignClassifyVectorUnsupervisedBodyC()
    {}
    //: Default constructor.
    
    virtual ClassifyVectorC Apply(const SampleC<VectorC> &in);
    //: Create a clasifier.
    
    virtual ClassifyVectorC Apply(const SampleC<VectorC> &in,const SampleC<RealT> &weight);
    //: Create a clasifier with weights for the samples.
    
  };
  
  //! userlevel=Normal
  //: Abstract unsupervised classifer designer.
  
  class DesignClassifyVectorUnsupervisedC
    : public RCHandleC<DesignClassifyVectorUnsupervisedBodyC>
  {
  public:
    DesignClassifyVectorUnsupervisedC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    DesignClassifyVectorUnsupervisedC(DesignClassifyVectorUnsupervisedBodyC &bod)
      : RCHandleC<DesignClassifyVectorUnsupervisedBodyC>(bod)
    {}
    //: Body constructor.
    
    DesignClassifyVectorUnsupervisedBodyC &Body()
    { return RCHandleC<DesignClassifyVectorUnsupervisedBodyC>::Body(); }
    //: Access body.
    
    const DesignClassifyVectorUnsupervisedBodyC &Body() const
    { return RCHandleC<DesignClassifyVectorUnsupervisedBodyC>::Body(); }
    //: Access body.
    
  public:
    ClassifyVectorC Apply(const SampleC<VectorC> &in)
    { return Body().Apply(in); }
    //: Create a clasifier.
    
    ClassifyVectorC Apply(const SampleC<VectorC> &in,const SampleC<RealT> &weight) 
    { return Body().Apply(in,weight); }
    //: Create a clasifier with weights for the samples.
  };
  
}


#endif
