// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_PATTERNRECCLASSIFY_HEADER
#define RAVL_PATTERNRECCLASSIFY_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! docentry="Ravl.Pattern Recognition.Classify"
//! author="Charles Galambos"

#include "Ravl/RefCounter.hh"
#include "Ravl/Vector.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Generic classifier body.
  
  class ClassifyVectorBodyC
    : public RCBodyVC
  {
  public:
    ClassifyVectorBodyC(UIntT nmaxLabels = 0);
    //: Default constructor.
    
    virtual UIntT Classify(const VectorC &data) const;
    //: Classify vector 'data' return the most likely label.
    
    virtual VectorC Confidence(const VectorC &data) const;
     //: Estimate the confidence for each label.
    // The meaning of the confidence assigned to each label depends
    // on the classifier used. The higher the confidence the more likely
    // it is the label is correct.
    
    UIntT Labels() const
      { return labels; }
    //: Returns the maximum number of output labels.
    
  protected:
    UIntT labels; // Number of output labels
    
    
  };

  //! userlevel=Normal
  //: Generic classifier.
  
  class ClassifyVectorC 
    : public RCHandleC<ClassifyVectorBodyC>
  {
  public:
    ClassifyVectorC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    ClassifyVectorC(ClassifyVectorBodyC &bod)
      : RCHandleC<ClassifyVectorBodyC>(bod)
    {}
    //: Body constructor.
    
    ClassifyVectorBodyC &Body()
      { return RCHandleC<ClassifyVectorBodyC>::Body(); }
    //: Access body.
    
    const ClassifyVectorBodyC &Body() const
      { return RCHandleC<ClassifyVectorBodyC>::Body(); }
    //: Access body.
    
  public:
    UIntT Classify(const VectorC &data) const
      { return Body().Classify(data); }
    //: Classify vector 'data' return the most likely label.
    
    VectorC Confidence(const VectorC &data) const
      { return Body().Confidence(data); }
    //: Estimate the confidence for each label.
    // The meaning of the confidence assigned to each label depends
    // on the classifier used. The higher the confidence the more likely
    // it is the label is correct.
     
    UIntT Labels() const
      { return Body().Labels(); }
    //: Returns the maximum number of output labels.
    
  };
  
}

#endif
