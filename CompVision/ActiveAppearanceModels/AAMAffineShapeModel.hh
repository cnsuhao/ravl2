// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_AFFINESHAPEMODEL_HEADER
#define RAVLIMAGE_AFFINESHAPEMODEL_HEADER 1
//! rcsid="$Id$"
//! lib=RavlAAM
//! author="Charles Galambos"
//! docentry="Ravl.API.Images.AAM"
//! file="Ravl/CompVision/ActiveAppearanceModels/AAMAffineShapeModel.hh"

#include "Ravl/Image/AAMShapeModel.hh"

namespace RavlImageN {

  //! userlevel=Develop
  //: Shape model with affine normalisation.
  
  class AAMAffineShapeModelBodyC
    : public AAMShapeModelBodyC
  {
  public:
    AAMAffineShapeModelBodyC();
    //: Default constructor.
    
    AAMAffineShapeModelBodyC(BinIStreamC &is);
    //: Load from bin stream.
    
    AAMAffineShapeModelBodyC(istream &is);
    //: Load from stream.
    
    virtual bool Save(BinOStreamC &out) const;
    //: Save to binary stream 'out'.

    virtual bool Save(ostream &out) const;
    //: Save to stream 'out'.
    
    virtual bool ComputeMean(const SampleC<AAMAppearanceC> &sample);
    //: Compute mean points.
    
    virtual bool RawParameters(const AAMAppearanceC &inst,VectorC &fixedParams,VectorC &freeParams) const;
    //: Generate a raw parameter vector.
    
    virtual void RawProject(const VectorC &fixedParams,const VectorC &freeParams,SArray1dC<Point2dC> &out) const;
    //: Generate points from a raw parameter vector.
    
    virtual IntT NoFixedParameters() const;
    //: Find the number of parameters which have fixed meaning.
    // offset,scale for example.
    
  protected:
    
  };

  //! userlevel=Normal
  //: Shape model with affine normalisation.
  
  class AAMAffineShapeModelC
    : public AAMShapeModelC
  {
  public:
    AAMAffineShapeModelC()
    {}
    //: Default constructor.
    
    AAMAffineShapeModelC(bool)
      : AAMShapeModelC(*new AAMAffineShapeModelBodyC())
    {}
    //: Constructor
   
    AAMAffineShapeModelC(BinIStreamC &is);
    //: Binary stream constructor.
    
    AAMAffineShapeModelC(istream &is);
    //: Stream constructor.
    
  protected:
    AAMAffineShapeModelC(AAMShapeModelBodyC &bod)
      : AAMShapeModelC(bod)
    {}
    //: Body constructor.
    
    AAMAffineShapeModelC(AAMAffineShapeModelBodyC *bod)
      : AAMShapeModelC(bod)
    {}
    //: Body ptr constructor.
    
    AAMAffineShapeModelBodyC &Body()
    { return static_cast<AAMAffineShapeModelBodyC &>(AAMShapeModelC::Body()); }
    //: Access body.
    
    const AAMAffineShapeModelBodyC &Body() const
    { return static_cast<const AAMAffineShapeModelBodyC &>(AAMShapeModelC::Body()); }
    //: Access body.
    
  public:
  };

  inline
  BinOStreamC &operator<<(BinOStreamC &s,const AAMAffineShapeModelC &ap) {
    ap.Save(s);
    return s;
  }
  
  inline
  BinIStreamC &operator<<(BinIStreamC &s,AAMAffineShapeModelC &ap) {
    ap = AAMAffineShapeModelC(s);
    return s;
  }

}

#endif
