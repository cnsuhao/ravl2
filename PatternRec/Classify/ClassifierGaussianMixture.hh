// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_CLASSIFIERGUASSIANMIXTURE_HEADER
#define RAVL_CLASSIFIERGUASSIANMIXTURE_HEADER 1
///////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! docentry="Ravl.Pattern Recognition.Classifier"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Classifier/ClassifierDiscriminantFunction.hh"

#include "Ravl/PatternRec/Classifier.hh"
#include "Ravl/PatternRec/GaussianMixture.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Create a classifier based on a descriminant function.
  //  This classifier returns the label with the highest value.
  
  class ClassifierGuassianMixtureBodyC 
    : public ClassifierBodyC
  {
  public:
    ClassifierGuassianMixtureBodyC(const SArray1dC<GaussianMixtureC> &model);
    //: Create classifier from a discriminant function.
    
    ClassifierGuassianMixtureBodyC(istream &strm);
    //: Load from stream.
    
    ClassifierGuassianMixtureBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual UIntT Classify(const VectorC &data) const;
    //: Classifier vector 'data' return the most likely label.
    
    virtual VectorC Confidence(const VectorC &data) const;
    //: Estimate the confidence for each label.
    // The meaning of the confidence assigned to each label depends
    // on the function used. The higher the confidence the more likely
    // it is the label is correct. The sum of the vector has been normalised
    // to 1.
    
    const SArray1dC<GaussianMixtureC> &MixtureModel() const
    { return models; }
    //: Access mixture model directly.
    
  protected:
    SArray1dC<GaussianMixtureC > models;
  };
  
  //! userlevel=Develop
  //: Create a classifier based on a descriminant function.
  //  This classifier returns the label with the highest value.
  
  class ClassifierGuassianMixtureC 
    : public ClassifierC
  {
  public:
    ClassifierGuassianMixtureC(const SArray1dC<GaussianMixtureC> &model)
      : ClassifierC(*new ClassifierGuassianMixtureBodyC(model))
    {}
    //: Create classifier from a discriminant function.
    
    ClassifierGuassianMixtureC(istream &strm);
    //: Load from stream.
    
    ClassifierGuassianMixtureC(BinIStreamC &strm);
    //: Load from binary stream.
    
  protected:
    ClassifierGuassianMixtureC(ClassifierGuassianMixtureBodyC &bod)
      : ClassifierC(bod)
    {}
    //: Body constructor.

    ClassifierGuassianMixtureC(ClassifierGuassianMixtureBodyC *bod)
      : ClassifierC(bod)
    {}
    //: Body constructor.
    
    ClassifierGuassianMixtureBodyC &Body()
    { return static_cast<ClassifierGuassianMixtureBodyC &>(ClassifierC::Body()); }
    //: Access body.

    const ClassifierGuassianMixtureBodyC &Body() const
    { return static_cast<const ClassifierGuassianMixtureBodyC &>(ClassifierC::Body()); }
    //: Access body.
    
  public:
    const SArray1dC<GaussianMixtureC > &MixtureModel() const
    { return Body().MixtureModel(); }
    //: Access mixture model directly.
    
  };
  
  inline istream &operator>>(istream &strm,ClassifierGuassianMixtureC &obj) {
    obj = ClassifierGuassianMixtureC(strm);
    return strm;
  }
  //: Load from a stream.
  // Uses virtual constructor.
  
  inline ostream &operator<<(ostream &out,const ClassifierGuassianMixtureC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.
  
  inline BinIStreamC &operator>>(BinIStreamC &strm,ClassifierGuassianMixtureC &obj) {
    obj = ClassifierGuassianMixtureC(strm);
    return strm;
  }
  //: Load from a binary stream.
  // Uses virtual constructor.
  
  inline BinOStreamC &operator<<(BinOStreamC &out,const ClassifierGuassianMixtureC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.
  
}


#endif
