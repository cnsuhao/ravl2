// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_SHAPEMODEL_HEADER
#define RAVLIMAGE_SHAPEMODEL_HEADER 1
//! rcsid="$Id$"
//! lib=RavlAAM
//! file="Ravl/CompVision/ActiveAppearanceModels/AAMShapeModel.hh"
//! docentry="Ravl.Images.AAM"
//! userlevel="Develop"
//! author="Charles Galambos"

#include "Ravl/Image/AAMAppearance.hh"
#include "Ravl/PatternRec/Function.hh"

namespace RavlImageN {

  //! userlevel=Develop
  //: Statistical shape model.
  
  class AAMShapeModelBodyC 
    : public RCBodyVC
  {
  public:
    AAMShapeModelBodyC()
    {}
    
    AAMShapeModelBodyC(BinIStreamC &is);
    //: Load from bin stream.

    AAMShapeModelBodyC(istream &is);
    //: Load from stream.
    
    virtual bool Save(BinOStreamC &out) const;
    //: Save to binary stream 'out'.

    virtual bool Save(ostream &out) const;
    //: Save to stream 'out'.
    
    virtual bool RawParameters(const AAMAppearanceC &inst,VectorC &fixedParams,VectorC &freeParams) const;
    //: Generate a raw parameter vector.
    
    virtual void RawProject(const VectorC &fixedParams,const VectorC &freeParams,SArray1dC<Point2dC> &out) const;
    //: Generate points from a raw parameter vector.
    
    virtual IntT NoFixedParameters() const;
    //: Find the number of parameters which have fixed meaning.
    // offset,scale for example.
    
    VectorC Parameters(const AAMAppearanceC &inst) const;
    //: Convert model instance into a parameter vector.
    // The results will be stored in 'vec'. 
    
    virtual bool ComputeMean(const SampleC<AAMAppearanceC> &sample);
    //: Compute mean points.
    
    bool Design(const SampleC<AAMAppearanceC> &sample,RealT variation = 0.95,UIntT maxP=25);
    //: Design a model given some data.
    
    UIntT Dimensions() const
    { return shapeModel.OutputSize() + NoFixedParameters(); }
    //: Size of output vector.
    
    const SArray1dC<Point2dC> &MeanPoints() const
    { return meanPoints; }
    //: Mean point positions for faces.
    
    SArray1dC<Point2dC> Synthesize(const VectorC &parm) const;
    //: Synthesis a point set from model parameters.
    
    const VectorC &EigenValues() const
    { return eigenValues; }
    //: Access eigen values.
    
    const VectorC &FixedMean() const
    { return fixedMean; }
    //: Access mean values for fixed parameters.
    
  protected:
    UIntT nPoints; // Number of points in the model.
    
    FunctionC shapeModel;   // Shape model, map location to parameters.
    FunctionC invShapeModel;// Inverse shape model, map parameters to locations
    
    SArray1dC<Point2dC> meanPoints; // Mean positions.
    VectorC fixedMean; // Mean of fixed parameters.
    
    VectorC eigenValues;   // eigenValues from PCA.
  };
  
  //! userlevel=Normal
  //: Statistical shape model.
  
  class AAMShapeModelC 
    : public RCHandleVC<AAMShapeModelBodyC>
  {
  public:
    AAMShapeModelC()
    {}
    //: Default constructor.
    // Creates an invalid handle.

    AAMShapeModelC(BinIStreamC &is);
    //: Binary stream constructor.
    
    AAMShapeModelC(istream &is);
    //: Stream constructor.
    
    AAMShapeModelC(bool)
      : RCHandleVC<AAMShapeModelBodyC>(*new AAMShapeModelBodyC())
    {}
    //: Construct a shape model.
    
  protected:
    AAMShapeModelC(AAMShapeModelBodyC &bod)
      : RCHandleVC<AAMShapeModelBodyC>(bod)
    {}
    //: Body constructor.

    AAMShapeModelC(AAMShapeModelBodyC *bod)
      : RCHandleVC<AAMShapeModelBodyC>(*bod)
    {}
    //: Body ptr constructor.
    
    AAMShapeModelBodyC &Body()
    { return RCHandleVC<AAMShapeModelBodyC>::Body(); }
    //: Access body.
    
    const AAMShapeModelBodyC &Body() const
    { return RCHandleVC<AAMShapeModelBodyC>::Body(); }
    //: Access body.
    
  public:

    bool RawParameters(const AAMAppearanceC &inst,VectorC &fixedParams,VectorC &freeParams)
    { return Body().RawParameters(inst,fixedParams,freeParams); }
    //: Generate a raw parameter vector from an appearance structure.
    
    VectorC Parameters(const AAMAppearanceC &inst)
    { return Body().Parameters(inst); }
    //: Convert model instance into a parameter vector.
    // The results will be stored in 'vec'. 
    
    bool Design(const SampleC<AAMAppearanceC> &sample,RealT variation = 0.95,UIntT maxP=25)
    { return Body().Design(sample,variation,maxP); }
    //: Design a model based on 'sample'.
    // Preserve 'variation' of the original dataset.
    
    UIntT Dimensions() const
    { return Body().Dimensions(); }
    //: Size of output vector.
    
    SArray1dC<Point2dC> MeanPoints() const
    { return Body().MeanPoints(); }
    //: Compute mean point positions for faces.
    
    SArray1dC<Point2dC> Synthesize(const VectorC &parm) const
    { return Body().Synthesize(parm); }
    //: Synthesis a point set from model parameters.
    
    const VectorC &EigenValues() const
    { return Body().EigenValues(); }
    //: Access eigen values.
    
    IntT NoFixedParameters() const
    { return Body().NoFixedParameters(); }
    //: Find the number of parameters which have fixed meaning.
    // offset,scale for example.
    
    const VectorC &FixedMean() const
    { return Body().FixedMean(); }
    //: Access mean values for fixed parameters.
    
  };
  
  inline
  BinOStreamC &operator<<(BinOStreamC &s,const AAMShapeModelC &ap) {
    ap.Save(s);
    return s;
  }
  
  inline
  BinIStreamC &operator<<(BinIStreamC &s,AAMShapeModelC &ap) {
    ap = AAMShapeModelC(s);
    return s;
  }
  
}


#endif
