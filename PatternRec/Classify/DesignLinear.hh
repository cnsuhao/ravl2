// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DESIGNLINEARDISCRIMINANT_HEADER
#define RAVL_DESIGNLINEARDISCRIMINANT_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Kieron Messer"
//! docentry="Ravl.Pattern Recognition.Numerical Modeling"
//! file="Ravl/PatternRec/Modeling/Basic/DesignLinear.hh"

#include "Ravl/PatternRec/DesignClassifierSupervised.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Design function with Least Squares Fitting.
  
  class DesignLinearBodyC
    : public DesignClassifierSupervisedBodyC
  {
  public:
    DesignLinearBodyC()
    {}
    //: Default constructor.
    
    DesignLinearBodyC(istream &strm);
    //: Load from stream.
    
    DesignLinearBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor

    DesignLinearBodyC(bool equalPriors);
    //: Assume equal priors for the classes? otherwise compute from the training data
    
    DesignLinearBodyC(const SArray1dC<RealT> & priors);
    //: Specify the priors for each class
        
    virtual ClassifierC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out);
    //: Create function from the a labelled dataset.
        
  protected:
    SArray1dC<RealT> priors;
    //: The means for each class

  };

  //! userlevel=Normal
  //: Design function with Least Squares Fitting.
  
  class DesignLinearC
    : public DesignClassifierSupervisedC
  {
  public:

    DesignLinearC(istream &strm);
    //: Load from stream.
    
    DesignLinearC(BinIStreamC &strm);
    //: Load from binary stream.

    DesignLinearC(bool equalPriors=true)
      : DesignClassifierSupervisedC(*new DesignLinearBodyC(equalPriors))
    {}
    //: Create designer.
    
    DesignLinearC(const SArray1dC<RealT> & priors)
      : DesignClassifierSupervisedC(*new DesignLinearBodyC(priors))
    {}
    //: Create designer.
    
  protected:
    DesignLinearC(DesignLinearBodyC &bod)
      : DesignClassifierSupervisedC(bod)
    {}
    //: Body constructor.
    
    DesignLinearC(DesignLinearBodyC *bod)
      : DesignClassifierSupervisedC(bod)
    {}
    //: Body ptr constructor.
    
     DesignLinearBodyC &Body()
    { return static_cast<DesignLinearBodyC &>(DesignLinearC::Body()); }
    //: Access body.
    
    const DesignLinearBodyC &Body() const
    { return static_cast<const DesignLinearBodyC &>(DesignLinearC::Body()); }
    //: Access body.

  public:


  };
  
  inline istream &operator>>(istream &strm,DesignLinearC &obj) {
    obj = DesignLinearC(strm);
    return strm;
  }
  //: Load from a stream.
  // Uses virtual constructor.
  
  inline ostream &operator<<(ostream &out,const DesignLinearC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.
  
  inline BinIStreamC &operator>>(BinIStreamC &strm,DesignLinearC &obj) {
    obj = DesignLinearC(strm);
    return strm;
  }
  //: Load from a binary stream.
  // Uses virtual constructor.
  
  inline BinOStreamC &operator<<(BinOStreamC &out,const DesignLinearC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.

}


#endif
