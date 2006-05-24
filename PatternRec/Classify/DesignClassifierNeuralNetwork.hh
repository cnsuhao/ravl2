// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DESIGNCLASSIFIERNEURALNETWORK_HEADER
#define RAVL_DESIGNCLASSIFIERNEURALNETOWRK_HEADER 1
//! rcsid="$Id: DesignClassifierGaussianMixture.hh,v 1.4 2005/12/06 17:16:50 plugger Exp $"
//! lib=RavlPatternRec
//! docentry="Ravl.API.Pattern Recognition.Classifier.DesignClassifier"
//! file="Ravl/PatternRec/Classify/DesignClassifierGaussianMixture.hh"

#include "Ravl/PatternRec/DesignClassifierSupervised.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Design a gaussian mixture classifier .
  
  class DesignClassifierNeuralNetworkBodyC
    : public DesignClassifierSupervisedBodyC
  {
  public:
    DesignClassifierNeuralNetworkBodyC(UIntT nLayers, UIntT nInputs, UIntT nHidden, UIntT nOutputs);
    //: Constructor.
    
    DesignClassifierNeuralNetworkBodyC(istream &strm);
    //: Load from stream.
    
    DesignClassifierNeuralNetworkBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor

    virtual ClassifierC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out);
    //: Train a neural network.  The number of input dimensions must be the same as specified in the
    //: constructor.  The number of different labels must be the same as the number of outputs.  Also
    //: the output labels must run from 0 to nOutputs-1.
    
    virtual ClassifierC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out,const SampleC<RealT> &weight);
    //: Create a clasifier with weights for the samples.
    
  protected:
    UIntT m_nLayers;
    UIntT m_nInputs;
    UIntT m_nHidden;
    UIntT m_nOutputs;
  };
  
  //! userlevel=Normal
  //: Design a gaussian mixture classifier .

  class DesignClassifierNeuralNetworkC
    : public DesignClassifierSupervisedC
  {
  public:
    DesignClassifierNeuralNetworkC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DesignClassifierNeuralNetworkC(UIntT nLayers, UIntT nInputs, UIntT nHidden, UIntT nOutputs)
      : DesignClassifierSupervisedC(*new DesignClassifierNeuralNetworkBodyC(nLayers, nInputs, nHidden, nOutputs))
    {}
    //: Create a new designer.
    
    DesignClassifierNeuralNetworkC(istream &strm);
    //: Load from stream.
    
    DesignClassifierNeuralNetworkC(BinIStreamC &strm);
    //: Load from binary stream.

  protected:
    DesignClassifierNeuralNetworkC(DesignClassifierNeuralNetworkBodyC &bod)
      : DesignClassifierSupervisedC(bod)
    {}
    //: Body constructor.

    DesignClassifierNeuralNetworkC(DesignClassifierNeuralNetworkBodyC *bod)
      : DesignClassifierSupervisedC(bod)
    {}
    //: Body ptr constructor.
    
    DesignClassifierNeuralNetworkBodyC &Body()
    { return static_cast<DesignClassifierNeuralNetworkBodyC &>(DesignClassifierSupervisedC::Body()); }
    //: Access body.
    
    const DesignClassifierNeuralNetworkBodyC &Body() const
    { return static_cast<const DesignClassifierNeuralNetworkBodyC &>(DesignClassifierSupervisedC::Body()); }
    //: Access body.
    
  public:
    
  };
  
  inline istream &operator>>(istream &strm,DesignClassifierNeuralNetworkC &obj) {
    obj = DesignClassifierNeuralNetworkC(strm);
    return strm;
  }
  //: Load from a stream.
  // Uses virtual constructor.
  
  inline ostream &operator<<(ostream &out,const DesignClassifierNeuralNetworkC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.
  
  inline BinIStreamC &operator>>(BinIStreamC &strm,DesignClassifierNeuralNetworkC &obj) {
    obj = DesignClassifierNeuralNetworkC(strm);
    return strm;
  }
  //: Load from a binary stream.
  // Uses virtual constructor.
  
  inline BinOStreamC &operator<<(BinOStreamC &out,const DesignClassifierNeuralNetworkC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.

}

#endif
