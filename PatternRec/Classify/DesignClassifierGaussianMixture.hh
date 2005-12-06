// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DESIGNCLASSIFIERGAUSIANMIXTURE_HEADER
#define RAVL_DESIGNCLASSIFIERGAUSIANMIXTURE_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! docentry="Ravl.API.Pattern Recognition.Classifier.DesignClassifier"
//! file="Ravl/PatternRec/Classify/DesignClassifierGaussianMixture.hh"

#include "Ravl/PatternRec/DesignClassifierSupervised.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Design a gaussian mixture classifier .
  
  class DesignClassifierGaussianMixtureBodyC
    : public DesignClassifierSupervisedBodyC
  {
  public:
    DesignClassifierGaussianMixtureBodyC(UIntT mixtures);
    //: Constructor.
    
    DesignClassifierGaussianMixtureBodyC(istream &strm);
    //: Load from stream.
    
    DesignClassifierGaussianMixtureBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor

    virtual ClassifierC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out);
    //: Create a clasifier.
    
    virtual ClassifierC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out,const SampleC<RealT> &weight);
    //: Create a clasifier with weights for the samples.
    
  protected:
    UIntT mixtures;
  };
  
  //! userlevel=Normal
  //: Design a gaussian mixture classifier .

  class DesignClassifierGaussianMixtureC
    : public DesignClassifierSupervisedC
  {
  public:
    DesignClassifierGaussianMixtureC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DesignClassifierGaussianMixtureC(UIntT mixtures)
      : DesignClassifierSupervisedC(*new DesignClassifierGaussianMixtureBodyC(mixtures))
    {}
    //: Create a new designer.
    
    DesignClassifierGaussianMixtureC(istream &strm);
    //: Load from stream.
    
    DesignClassifierGaussianMixtureC(BinIStreamC &strm);
    //: Load from binary stream.

  protected:
    DesignClassifierGaussianMixtureC(DesignClassifierGaussianMixtureBodyC &bod)
      : DesignClassifierSupervisedC(bod)
    {}
    //: Body constructor.

    DesignClassifierGaussianMixtureC(DesignClassifierGaussianMixtureBodyC *bod)
      : DesignClassifierSupervisedC(bod)
    {}
    //: Body ptr constructor.
    
    DesignClassifierGaussianMixtureBodyC &Body()
    { return static_cast<DesignClassifierGaussianMixtureBodyC &>(DesignClassifierSupervisedC::Body()); }
    //: Access body.
    
    const DesignClassifierGaussianMixtureBodyC &Body() const
    { return static_cast<const DesignClassifierGaussianMixtureBodyC &>(DesignClassifierSupervisedC::Body()); }
    //: Access body.
    
  public:
    
  };
  
  inline istream &operator>>(istream &strm,DesignClassifierGaussianMixtureC &obj) {
    obj = DesignClassifierGaussianMixtureC(strm);
    return strm;
  }
  //: Load from a stream.
  // Uses virtual constructor.
  
  inline ostream &operator<<(ostream &out,const DesignClassifierGaussianMixtureC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.
  
  inline BinIStreamC &operator>>(BinIStreamC &strm,DesignClassifierGaussianMixtureC &obj) {
    obj = DesignClassifierGaussianMixtureC(strm);
    return strm;
  }
  //: Load from a binary stream.
  // Uses virtual constructor.
  
  inline BinOStreamC &operator<<(BinOStreamC &out,const DesignClassifierGaussianMixtureC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.

}

#endif
