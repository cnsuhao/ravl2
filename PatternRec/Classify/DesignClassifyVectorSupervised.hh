// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DESIGNCLASSIFYVECTORSUPERVISED_HEADER
#define RAVL_DESIGNCLASSIFYVECTORSUPERVISED_HEADER 1
///////////////////////////////////////////////////////////
//! userlevel=Normal
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! docentry="Ravl.Pattern Recognition.Classify"
//! file="Ravl/PatternRec/Classify/DesignClassifyVectorSupervised.hh"

#include "Ravl/RCHandleV.hh"
#include "Ravl/Vector.hh"
#include "Ravl/PatternRec/Sample.hh"
#include "Ravl/PatternRec/ClassifyVector.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Abstract supervised classifer designer.
  
  class DesignClassifyVectorSupervisedBodyC
    : public RCBodyVC
  {
  public:
    DesignClassifyVectorSupervisedBodyC()
    {}
    //: Default constructor.
    
    virtual ClassifyVectorC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out);
    //: Create a clasifier.
    
    virtual ClassifyVectorC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out,const SampleC<RealT> &weight);
    //: Create a clasifier with weights for the samples.
    
  };
  
  //! userlevel=Normal
  //: Abstract supervised classifer designer.
  
  class DesignClassifyVectorSupervisedC
    : public RCHandleC<DesignClassifyVectorSupervisedBodyC>
  {
  public:
    DesignClassifyVectorSupervisedC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    DesignClassifyVectorSupervisedC(DesignClassifyVectorSupervisedBodyC &bod)
      : RCHandleC<DesignClassifyVectorSupervisedBodyC>(bod)
    {}
    //: Body constructor.
    
    DesignClassifyVectorSupervisedBodyC &Body()
    { return RCHandleC<DesignClassifyVectorSupervisedBodyC>::Body(); }
    //: Access body.
    
    const DesignClassifyVectorSupervisedBodyC &Body() const
    { return RCHandleC<DesignClassifyVectorSupervisedBodyC>::Body(); }
    //: Access body.
    
  public:
    ClassifyVectorC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out)
    { return Body().Apply(in,out); }
    //: Create a clasifier.
    
    ClassifyVectorC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out,const SampleC<RealT> &weight) 
    { return Body().Apply(in,out,weight); }
    //: Create a clasifier with weights for the samples.
  };
  
}


#endif
