// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_CLASSIFY_HEADER
#define RAVL_CLASSIFY_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! docentry="Ravl.Pattern Recognition.Classifier"
//! author="Charles Galambos"
//! file="Ravl/PatternRec/Classifier/Classifier.hh"

#include "Ravl/PatternRec/Function.hh"
#include "Ravl/Vector.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Generic classifier body.
  
  class ClassifierBodyC
    : public FunctionBodyC
  {
  public:
    ClassifierBodyC(UIntT nmaxLabels = 0);
    //: Constructor.
    
    ClassifierBodyC(istream &strm);
    //: Load from stream.
    
    ClassifierBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual UIntT Classifier(const VectorC &data) const;
    //: Classifier vector 'data' return the most likely label.
    
    virtual VectorC Apply(const VectorC &data) const;
    //: Estimate the confidence for each label.
    // The meaning of the confidence assigned to each label depends
    // on the classifier used. The higher the confidence the more likely
    // it is the label is correct.
    
    UIntT NoLabels() const
    { return outputSize; }
    //: Returns the maximum number of output labels.
    // Identical to OutputSize().
    
    UIntT NoLabels(UIntT labels)
    { return OutputSize(labels); }
    //: Returns the maximum number of output labels.
    // Identical to OutputSize().
    
  protected:
  };

  //! userlevel=Normal
  //: Generic classifier.
  
  class ClassifierC 
    : public FunctionC
  {
  public:
    ClassifierC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    ClassifierC(istream &strm);
    //: Load from stream.
    
    ClassifierC(BinIStreamC &strm);
    //: Load from binary stream.
    
    ClassifierC(const FunctionC &func)
      : FunctionC(func)
    { 
      if(dynamic_cast<const ClassifierBodyC *>(&FunctionC::Body()) == 0)
	Invalidate();
    }
    //: Create from base class.
    // Creates an invalid handle if 'func' is not a classifer.
    
  protected:
    ClassifierC(ClassifierBodyC &bod)
      : FunctionC(bod)
    {}
    //: Body constructor.

    ClassifierC(ClassifierBodyC *bod)
      : FunctionC(bod)
    {}
    //: Body ptr constructor.
    
    ClassifierBodyC &Body()
    { return static_cast<ClassifierBodyC &>(FunctionC::Body()); }
    //: Access body.
    
    const ClassifierBodyC &Body() const
    { return static_cast<const ClassifierBodyC &>(FunctionC::Body()); }
    //: Access body.
    
  public:
    UIntT Classifier(const VectorC &data) const
    { return Body().Classifier(data); }
    //: Classifier vector 'data' return the most likely label.
    
    VectorC Confidence(const VectorC &data) const
    { return Body().Apply(data); }
    //: Estimate the confidence for each label.
    // The meaning of the confidence assigned to each label depends
    // on the classifier used. The higher the confidence the more likely
    // it is the label is correct. <p>
    // The result is identical to that of the apply method.
    
    UIntT NoLabels() const
    { return Body().NoLabels(); }
    //: Returns the maximum number of output labels.
    
    UIntT NoLabels(UIntT labels)
    { return Body().NoLabels(labels); }
    //: Set the number of labels
    
  };
  
  inline istream &operator>>(istream &strm,ClassifierC &obj) {
    obj = ClassifierC(strm);
    return strm;
  }
  //: Load from a stream.
  // Uses virtual constructor.
  
  inline ostream &operator<<(ostream &out,const ClassifierC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.
  
  inline BinIStreamC &operator>>(BinIStreamC &strm,ClassifierC &obj) {
    obj = ClassifierC(strm);
    return strm;
  }
  //: Load from a binary stream.
  // Uses virtual constructor.
  
  inline BinOStreamC &operator<<(BinOStreamC &out,const ClassifierC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.
  
}

#endif
