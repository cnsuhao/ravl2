// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_SCALEROTATIONSHAPEMODEL_HEADER
#define RAVLIMAGE_SCALEROTATIONSHAPEMODEL_HEADER 1
//! docentry="Ravl.Images.Misc"
//! rcsid="$Id$"
//! lib=RavlImageProc
//! author="Charles Galambos"
//! file="ActiveAppearanceModels/AAMScaleRotationShapeModel.hh"

#include "Ravl/Image/AAMShapeModel.hh"

namespace RavlImageN {

  //! userlevel=Develop
  //: Shape model with scale and rotation normalisation.
  
  class AAMScaleRotationShapeModelBodyC
    : public AAMShapeModelBodyC
  {
  public:
    AAMScaleRotationShapeModelBodyC();
    //: Default constructor.
    
    AAMScaleRotationShapeModelBodyC(BinIStreamC &is);
    //: Load from bin stream.
    
    AAMScaleRotationShapeModelBodyC(istream &is);
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
  //: Shape model with scale and rotation normalisation.
  
  class AAMScaleRotationShapeModelC
    : public AAMShapeModelC
  {
  public:
    AAMScaleRotationShapeModelC()
    {}
    //: Default constructor.
    
    AAMScaleRotationShapeModelC(bool)
      : AAMShapeModelC(*new AAMScaleRotationShapeModelBodyC())
    {}
    //: Constructor
   
    AAMScaleRotationShapeModelC(BinIStreamC &is);
    //: Binary stream constructor.
    
    AAMScaleRotationShapeModelC(istream &is);
    //: Stream constructor.
    
  protected:
    AAMScaleRotationShapeModelC(AAMShapeModelBodyC &bod)
      : AAMShapeModelC(bod)
    {}
    //: Body constructor.
    
    AAMScaleRotationShapeModelC(AAMScaleRotationShapeModelBodyC *bod)
      : AAMShapeModelC(bod)
    {}
    //: Body ptr constructor.
    
    AAMScaleRotationShapeModelBodyC &Body()
    { return static_cast<AAMScaleRotationShapeModelBodyC &>(AAMShapeModelC::Body()); }
    //: Access body.
    
    const AAMScaleRotationShapeModelBodyC &Body() const
    { return static_cast<const AAMScaleRotationShapeModelBodyC &>(AAMShapeModelC::Body()); }
    //: Access body.
    
  public:
  };
  
  inline
  BinOStreamC &operator<<(BinOStreamC &s,const AAMScaleRotationShapeModelC &ap) {
    ap.Save(s);
    return s;
  }
  
  inline
  BinIStreamC &operator<<(BinIStreamC &s,AAMScaleRotationShapeModelC &ap) {
    ap = AAMScaleRotationShapeModelC(s);
    return s;
  }

}

#endif
