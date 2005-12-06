// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_ACTIVEAPPEARANCEMODEL_HEADER
#define RAVLIMAGE_ACTIVEAPPEARANCEMODEL_HEADER 1
//! rcsid="$Id$"
//! lib=RavlAAM
//! file="Ravl/CompVision/ActiveAppearanceModels/AAMActiveAppearanceModel.hh"
//! docentry="Ravl.API.Images.AAM"
//! userlevel="Develop"
//! author="Charles Galambos"

#include "Ravl/Image/AAMAppearanceModel.hh"
#include "Ravl/PatternRec/Function.hh"
#include "Ravl/Image/GaussConvolve2d.hh"

namespace RavlImageN {

  //! userlevel=Develop
  //: Active Appearance Model

  class AAMActiveAppearanceModelBodyC 
    :public RCBodyVC
  {
  public:
    AAMActiveAppearanceModelBodyC();
    //: Constructor.

    AAMActiveAppearanceModelBodyC(BinIStreamC &is);
    //: Load from bin stream.

    AAMActiveAppearanceModelBodyC(istream &is);
    //: Load from stream.

    virtual bool Save(BinOStreamC &out) const;
    //: Save to binary stream 'out'.

    virtual bool Save(ostream &out) const;
    //: Save to stream 'out'.

    VectorC RefinePose(const ImageC<ByteT> &img,VectorC paramEstimate);
    //: Refine pose parameters based on an initial estimate of parameters.

    VectorC RefinePose(const ImageC<ByteT> &img,VectorC paramEstimate,RealT &diff);
    //: Refine pose parameters based on an initial estimate of parameters.

    VectorC RefinePose(const ImageC<RealT> &img,VectorC paramEstimate,RealT &diff);
    //: Refine pose parameters based on an initial estimate of parameters.

    bool Design(const AAMAppearanceModelC apm,const DListC<StringC> &fileList,const StringC &dir,const StringC &mirrorFile, const UIntT incrSize);
    //: Design a model given some data and an existsing appearance model.

    bool PreDesign(const AAMAppearanceModelC apm,const DListC<StringC> &fileList,const StringC &dir,const StringC &mirrorFile, const UIntT incrSize, const StringC &op);
    //: Pre-process some data in preparation of design of AAM

    bool PostDesign(const AAMAppearanceModelC apm,const DListC<StringC> &fileList,const StringC &dir, const StringC &op);
    //: Terminate the design of AAM by merging results of pre-design

    AAMAppearanceModelC &AppearanceModel()
    { return appearanceModel; }
    //: Access active model.

    const AAMAppearanceModelC &AppearanceModel() const
    { return appearanceModel; }
    //: Access active model.

    AAMShapeModelC &ShapeModel()
    { return appearanceModel.ShapeModel(); }
    //: Access active model.

    VectorC ShapeParameters(const VectorC &aamParams)
    { return appearanceModel.ShapeParameters(aamParams); }
    //: Extract shape parameters from active appearance model ones.

    SArray1dC<Point2dC> &RefrenceHome()
    { return refHome; }
    //: Access refrence points.

    UIntT Dimensions() const
    { return appearanceModel.Dimensions(); }
    //: Get number of dimension in the model.

  protected:
    SArray1dC<Point2dC> refHome; // Home position of reference points.
    AAMAppearanceModelC appearanceModel;
    FunctionC refiner;
    GaussConvolve2dC<RealT> smooth; // Gauss convolver for clean up input a little.    
  };


  //! userlevel=Normal
  //: Active Appearnce Model

  class AAMActiveAppearanceModelC 
    : public RCHandleVC<AAMActiveAppearanceModelBodyC>
  {
  public:

    AAMActiveAppearanceModelC(BinIStreamC &is);
    //: Load from bin stream.

    AAMActiveAppearanceModelC(istream &is);
    //: Load from stream.

    AAMActiveAppearanceModelC()
      : RCHandleVC<AAMActiveAppearanceModelBodyC>(*new AAMActiveAppearanceModelBodyC())
    {}
    //: Constructor.


  protected:
    AAMActiveAppearanceModelC(AAMActiveAppearanceModelBodyC &bod)
      : RCHandleVC<AAMActiveAppearanceModelBodyC>(bod)
    {}
    //: Body constructor.

    AAMActiveAppearanceModelC(AAMActiveAppearanceModelBodyC *bod)
      : RCHandleVC<AAMActiveAppearanceModelBodyC>(*bod)
    {}
    //: Body ptr constructor.

    AAMActiveAppearanceModelBodyC &Body()
    { return RCHandleVC<AAMActiveAppearanceModelBodyC>::Body(); }
    //: Access body.

    const AAMActiveAppearanceModelBodyC &Body() const
    { return RCHandleVC<AAMActiveAppearanceModelBodyC>::Body(); }
    //: Access body.

  public:

    VectorC RefinePose(const ImageC<ByteT> &img,VectorC paramEstimate)
    { return Body().RefinePose(img,paramEstimate); }
    //: Refine pose parameters based on an initial estimate of parameters.

    VectorC RefinePose(const ImageC<ByteT> &img,VectorC paramEstimate,RealT &diff)
    { return Body().RefinePose(img,paramEstimate,diff); }
    //: Refine pose parameters based on an initial estimate of parameters.

    VectorC RefinePose(const ImageC<RealT> &img,VectorC paramEstimate,RealT &diff)
    { return Body().RefinePose(img,paramEstimate,diff); }
    //: Refine pose parameters based on an initial estimate of parameters.

    bool Design(const AAMAppearanceModelC apm,const DListC<StringC> &fileList,const StringC &dir,const StringC &mirrorFile, const UIntT incrSize)
    { return Body().Design(apm,fileList,dir,mirrorFile,incrSize); }
    //: Design a model given some data and an existsing appearance model.

    bool PreDesign(const AAMAppearanceModelC apm,const DListC<StringC> &fileList,const StringC &dir,const StringC &mirrorFile, const UIntT incrSize, const StringC &op)
    { return Body().PreDesign(apm,fileList,dir,mirrorFile,incrSize,op); }
    //: Pre-process some data in preparation of design of AAM

    bool PostDesign(const AAMAppearanceModelC apm,const DListC<StringC> &fileList,const StringC &dir, const StringC &op)
    { return Body().PostDesign(apm,fileList,dir,op); }
    //: Terminate the design of AAM by merging results of pre-design

    AAMAppearanceModelC &AppearanceModel()
    { return Body().AppearanceModel(); }
    //: Access active model.

    const AAMAppearanceModelC &AppearanceModel() const
    { return Body().AppearanceModel(); }
    //: Access active model.

    AAMShapeModelC &ShapeModel()
    { return Body().ShapeModel(); }
    //: Access active model.

    SArray1dC<Point2dC> &RefrenceHome()
    { return Body().RefrenceHome(); }
    //: Access refrence points.

    VectorC ShapeParameters(const VectorC &aamParams)
    { return Body().ShapeParameters(aamParams); }
    //: Extract shape parameters from active appearance model ones.

    UIntT Dimensions() const
    { return Body().Dimensions(); }
    //: Get number of dimension in the model.

    friend class AAMActiveAppearanceModelBodyC;
  };

}


#endif
