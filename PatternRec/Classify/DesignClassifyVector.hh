// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DESIGNCLASSIFYVECTOR_HEADER
#define RAVL_DESIGNCLASSIFYVECTOR_HEADER 1
///////////////////////////////////////////////////////////
//! userlevel=Normal
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! docentry="Ravl.Pattern Recognition.Classify"

#include "Ravl/RCHandleV.hh"
#include "Ravl/Vector.hh"
#include "Ravl/PatternRec/Sample.hh"
#include "Ravl/PatternRec/ClassifyVector.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Abstract classifer designer.
  
  class DesignClassifyVectorBodyC
    : public RCBodyVC
  {
  public:
    DesignClassifyVectorBodyC()
    {}
    //: Default constructor.
    
    virtual ClassifyVectorC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out);
    //: Create a clasifier.
    
    virtual ClassifyVectorC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out,const SampleC<RealT> &weight);
    //: Create a clasifier with weights for the samples.
    
  };
  
  //! userlevel=Normal
  //: Abstract classifer designer.
  
  class DesignClassifyVectorC
    : public RCHandleC<DesignClassifyVectorBodyC>
  {
  public:
    DesignClassifyVectorC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    DesignClassifyVectorC(DesignClassifyVectorBodyC &bod)
      : RCHandleC<DesignClassifyVectorBodyC>(bod)
    {}
    //: Body constructor.
    
    DesignClassifyVectorBodyC &Body()
    { return RCHandleC<DesignClassifyVectorBodyC>::Body(); }
    //: Access body.
    
    const DesignClassifyVectorBodyC &Body() const
    { return RCHandleC<DesignClassifyVectorBodyC>::Body(); }
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
