// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_CLASSIFIERLINEAR_HEADER
#define RAVL_CLASSIFIERLINEAR_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Charles Galambos"
//! docentry="Ravl.Pattern Recognition.Numerical Modeling"
//! file="Ravl/PatternRec/Modeling/Basic/ClassifierLinear.hh"

#include "Ravl/PatternRec/Classifier.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/Vector.hh"

namespace RavlN {

  //! userlevel=Develop
  //: Subtract a mean and project a vector
  // This is very similar FuncLinear, except the mean is subtracted first then 
  // the vector is projected.
  
  class ClassifierLinearBodyC
    : public ClassifierBodyC
  {
  public:
    ClassifierLinearBodyC();
    //: Default constructor.
    
    ClassifierLinearBodyC(const SArray1dC<VectorC> & means, const MatrixC & covariance, const SArray1dC<RealT> & priors);
    //: Construct from the mean for each, covariance and prior for each class
    
    ClassifierLinearBodyC(istream &strm);
    //: Load from stream.
    
    ClassifierLinearBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream.
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to binary stream.
    
    virtual UIntT Classify(const VectorC &data) const;
    //: Returns most likely label
    
    
  protected:
    SArray1dC<VectorC>mean;
    //: means of class

    MatrixC invCov;
    //: the inverse covariances
    
    SArray1dC<RealT>konst;
    //: the constant bit
  };
  
  //! userlevel=Normal
  //: Subtract a mean and project a vector
  // This is very similar FuncLinear, except the mean is subtracted first then 
  // the vector is projected.
  
  class ClassifierLinearC
    : public ClassifierC 
  {
  public:
    ClassifierLinearC()
    {}
    //: Default constructor.
    
    ClassifierLinearC(const SArray1dC<VectorC> & mean, const MatrixC & covariance, const SArray1dC<RealT> & priors)
      : ClassifierC(*new ClassifierLinearBodyC(mean, covariance, priors))
    {}
    //: Construct from a mean and a projection matrix.
    
    ClassifierLinearC(istream &is);
    //: Stream constructor.
    
    ClassifierLinearC(BinIStreamC &is);
    //: Stream constructor.
    
    ClassifierLinearC(const ClassifierC &func)
      : ClassifierC(func)
    {
      if(dynamic_cast<ClassifierLinearBodyC *>(&ClassifierC::Body()) == 0)
	Invalidate();
    }
    //: Attempt to create handle from base class.
    // If object is not a ClassifierLinearC, an invalid handle will be created.
    
  protected:
    ClassifierLinearC(ClassifierLinearBodyC &bod)
      : ClassifierC(bod)
    {}
    //: Body constructor.
    
    ClassifierLinearBodyC &Body()
    { return static_cast<ClassifierLinearBodyC &>(ClassifierC::Body()); }
    //: Access body.

    const ClassifierLinearBodyC &Body() const 
    { return static_cast<const ClassifierLinearBodyC &>(ClassifierC::Body()); }
    //: Access body.
    
  public:
    
  };
  
  
  inline istream &operator>>(istream &strm,ClassifierLinearC &obj) {
    obj = ClassifierLinearC(strm);
    return strm;
  }
  //: Load from a stream.
  // Uses virtual constructor.
  
  inline ostream &operator<<(ostream &out,const ClassifierLinearC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.
  
  inline BinIStreamC &operator>>(BinIStreamC &strm,ClassifierLinearC &obj) {
    obj = ClassifierLinearC(strm);
    return strm;
  }
  //: Load from a binary stream.
  // Uses virtual constructor.
  
  inline BinOStreamC &operator<<(BinOStreamC &out,const ClassifierLinearC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.

}



#endif
