// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_CLASSIFYVECTOR_HEADER
#define RAVL_CLASSIFYVECTOR_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! docentry="Ravl.Pattern Recognition.Classify"
//! author="Charles Galambos"
//! file="Ravl/PatternRec/Classify/ClassifyVector.hh"

#include "Ravl/PatternRec/Function.hh"
#include "Ravl/Vector.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Generic classifier body.
  
  class ClassifyVectorBodyC
    : public FunctionBodyC
  {
  public:
    ClassifyVectorBodyC(UIntT nmaxLabels = 0);
    //: Constructor.
    
    ClassifyVectorBodyC(istream &strm);
    //: Load from stream.
    
    ClassifyVectorBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual UIntT Classify(const VectorC &data) const;
    //: Classify vector 'data' return the most likely label.
    
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
  
  class ClassifyVectorC 
    : public FunctionC
  {
  public:
    ClassifyVectorC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    ClassifyVectorC(istream &strm);
    //: Load from stream.
    
    ClassifyVectorC(BinIStreamC &strm);
    //: Load from binary stream.
    
  protected:
    ClassifyVectorC(ClassifyVectorBodyC &bod)
      : FunctionC(bod)
    {}
    //: Body constructor.
    
    ClassifyVectorBodyC &Body()
    { return static_cast<ClassifyVectorBodyC &>(FunctionC::Body()); }
    //: Access body.
    
    const ClassifyVectorBodyC &Body() const
    { return static_cast<const ClassifyVectorBodyC &>(FunctionC::Body()); }
    //: Access body.
    
  public:
    UIntT Classify(const VectorC &data) const
    { return Body().Classify(data); }
    //: Classify vector 'data' return the most likely label.
    
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
  
  inline istream &operator>>(istream &strm,ClassifyVectorC &obj) {
    obj = ClassifyVectorC(strm);
    return strm;
  }
  //: Load from a stream.
  // Uses virtual constructor.
  
  inline ostream &operator<<(ostream &out,const ClassifyVectorC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.
  
  inline BinIStreamC &operator>>(BinIStreamC &strm,ClassifyVectorC &obj) {
    obj = ClassifyVectorC(strm);
    return strm;
  }
  //: Load from a binary stream.
  // Uses virtual constructor.
  
  inline BinOStreamC &operator<<(BinOStreamC &out,const ClassifyVectorC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.
  
}

#endif
