// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_APPEARANCEMODEL_HEADER
#define RAVLIMAGE_APPEARANCEMODEL_HEADER 1
//! rcsid="$Id$"
//! lib=RavlImageProc
//! file="ActiveAppearanceModels/AAMAppearanceModel.hh"
//! docentry="Ravl.Images.Misc"
//! author="Charles Galambos"

#include "Ravl/DList.hh"
#include "Ravl/String.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/TriMesh2d.hh"
#include "Ravl/Image/AAMAppearance.hh"
#include "Ravl/Image/AAMShapeModel.hh"
#include "Ravl/Image/WarpMesh2d.hh"

namespace RavlImageN {

  //! userlevel=Develop
  //: Appearnce Model

  class AAMAppearanceModelBodyC 
    : public RCBodyVC
  {
  public:
    AAMAppearanceModelBodyC(RealT nWarpSigma = 2);
    //: Constructor.
    // nWarpSigma, stiffness to use in warping process.

    AAMAppearanceModelBodyC(BinIStreamC &is);
    //: Load from binary stream.

    AAMAppearanceModelBodyC(istream &is);
    //: Load from stream.

    virtual bool Save(BinOStreamC &out) const;
    //: Save to binary stream 'out'.

    virtual bool Save(ostream &out) const;
    //: Save to stream 'out'.

    virtual VectorC Parameters(const AAMAppearanceC &inst);
    //: Convert model instance into a parameter vector.

    virtual VectorC RawParameters(const AAMAppearanceC &inst);
    //: Get raw parameters for 'inst'

    ImageC<ByteT> WarpToMaskShape(const AAMAppearanceC &inst);
    //: Warp appearance to mean shape.

    virtual bool Design(const DListC<StringC> &fileList,const StringC &dir,const StringC &mirrorFile,const Index2dC &maskSize,const RealT varS = 0.95,const RealT varT = 0.95,const RealT varC = 0.95,const UIntT maxS=25,const UIntT maxT=120,const UIntT maxC=80);
    //: Design a model given some data.

    virtual void SetMask(const ImageC<IntT> &mask);
    //: Set mask image to use.

    UIntT Dimensions() const
    { return appearanceModel.OutputSize() + NoFixedParameters(); }
    //: Size of output vector.

    virtual AAMAppearanceC Synthesize(const VectorC &dat,RealT scale = 1);
    //: Synthesis an appearance from a parameter vector.

    virtual bool TextureImage(const VectorC &dat,ImageC<RealT> &res);
    //: Compute texture image (shape free image)

    bool ErrorVector(const VectorC &parm,const ImageC<ByteT> &img,VectorC &errImg) const;
    //: Compute an error vector.

    virtual bool ErrorVector(const VectorC &parm,const ImageC<RealT> &img,VectorC &errImg) const;
    //: Compute an error vector.

    void MakePlausible(VectorC &parm, RealT NbSigma = 3) const;
    //: Constrains parm to be plausible by applying hard limits of 3 std to each element

    const IndexRange2dC &MaskSize() const
    { return maskSize; }
    //: Get size of mask image.

    const IntT &MaskArea() const
    { return maskArea; }
    //: Get number of pixels in the mask.

    const ImageC<IntT> &Mask() const
    { return mask; }
    //: Get mask image.

    const VectorC &EigenValues() const
    { return eigenValues; }
    //: Access eigen values.

    const FunctionC &AppearanceModel() const
    { return appearanceModel; }
    //: Access appearance model      

    const FunctionC &InvAppearanceModel() const
    { return invAppearanceModel; }
    //: Access appearance model      

    IntT NoFixedParameters() const
    { return shape.NoFixedParameters() + 2; }
    //: Find the number of parameters which have fixed meaning.
    // offset,scale for example.

    const VectorC &FixedMean() const
    { return fixedMean; }
    //: Get mean of fixed parameters.

    const VectorC &PixelSize() const
    { return pixelSize; }
    //: Get mean of fixed parameters.

    VectorC ShapeParameters(const VectorC &aamParams);
    //: Extract shape parameters from active appearance model ones.

    virtual bool TextureParameters(const ImageC<RealT> &im, VectorC &res);
    //: Extract texture parameters from shape free image

    AAMShapeModelC &ShapeModel()
    { return shape; }
    //: Access shape model.

    const TriMesh2dC &Mesh() const
    { return warp.Mesh(); }
    //: Access mesh.

    TriMesh2dC &Mesh()
    { return warp.Mesh(); }
    //: Access mesh.

  protected:
    RealT warpSigma;
    AAMShapeModelC shape;
    ImageC<IntT> mask; // Which pixels are we interested in?
    Array1dC<Point2dC> maskPoints; // Position of control points in mask image.
    IndexRange2dC maskSize;
    IntT maskArea;     // Number of pixels in the mask.
    FunctionC appearanceModel;
    FunctionC invAppearanceModel; // Inverse appearance model.
    WarpMesh2dC<ByteT> warp;
    VectorC eigenValues;
    VectorC fixedMean;
    VectorC pixelSize;
  };

  //! userlevel=Normal
  //: Appearnce Model

  class AAMAppearanceModelC 
    : public RCHandleVC<AAMAppearanceModelBodyC>
  {
  public:
    AAMAppearanceModelC()
    {}
    //: Default constructor 
    // Creates an invalid handle.

    AAMAppearanceModelC(RealT nWarpSigma)
      : RCHandleVC<AAMAppearanceModelBodyC>(*new AAMAppearanceModelBodyC(nWarpSigma))
    {}
    //: Constructor.
    // nWarpSigma, stiffness to use in warping process.

    AAMAppearanceModelC(BinIStreamC &is);
    //: Load from binary stream.

    AAMAppearanceModelC(istream &is);
    //: Load from stream.


  protected:
    AAMAppearanceModelC(AAMAppearanceModelBodyC &bod)
      : RCHandleVC<AAMAppearanceModelBodyC>(bod)
    {}
    //: Body constructor.

    AAMAppearanceModelC(AAMAppearanceModelBodyC *bod)
      : RCHandleVC<AAMAppearanceModelBodyC>(*bod)
    {}
    //: Body ptr constructor.

    AAMAppearanceModelBodyC &Body()
    { return RCHandleVC<AAMAppearanceModelBodyC>::Body(); }
    //: Access body.

    const AAMAppearanceModelBodyC &Body() const
    { return RCHandleVC<AAMAppearanceModelBodyC>::Body(); }
    //: Access body.


  public:

    VectorC Parameters(const AAMAppearanceC &inst)
    { return Body().Parameters(inst); }
    //: Convert model instance into a parameter vector.

    VectorC RawParameters(const AAMAppearanceC &inst)
    { return Body().RawParameters(inst); }
    //: Get raw parameters for 'inst'

    ImageC<ByteT> WarpToMaskShape(const AAMAppearanceC &inst)
    { return Body().WarpToMaskShape(inst); }
    //: Warp appearance to mean shape.

    bool Design(const DListC<StringC> &fileList,const StringC &dir,const StringC &mirrorFile,const Index2dC &newMaskSize = Index2dC(50,50),const RealT varS = 0.95,const RealT varT = 0.95,const RealT varC = 0.95,const UIntT maxS=25,const UIntT maxT=120,const UIntT maxC=80)
    { return Body().Design(fileList,dir,mirrorFile,newMaskSize,varS,varT,varC,maxS,maxT,maxC); }
    //: Design a model given some data.

    void SetMask(const ImageC<IntT> &mask)
    { return Body().SetMask(mask); }
    //: Set mask image to use.

    UIntT Dimensions() const
    { return Body().Dimensions(); }
    //: Size of output vector.

    AAMAppearanceC Synthesize(const VectorC &dat,RealT scale = 1)
    { return Body().Synthesize(dat,scale); }
    //: Synthesis an appearance from a parameter vector.

    bool TextureImage(const VectorC &dat,ImageC<RealT> &res)
    { return Body().TextureImage(dat,res);}
    //: Compute texture image (shape free image)

    bool ErrorVector(const VectorC &parm,const ImageC<ByteT> &img,VectorC &errImg) const
    { return Body().ErrorVector(parm,img,errImg); }
    //: Compute an error vector.

    bool ErrorVector(const VectorC &parm,const ImageC<RealT> &img,VectorC &errImg) const
    { return Body().ErrorVector(parm,img,errImg); }
    //: Compute an error vector.

    void MakePlausible(VectorC &parm, RealT NbSigma = 3) const
    { return Body().MakePlausible(parm,NbSigma); }
    //: Constrains parm to be plausible by applying hard limits of 3 std to each element

    const IndexRange2dC &MaskSize() const
    { return Body().MaskSize(); }
    //: Get size of mask image.

    const IntT &MaskArea() const
    { return Body().MaskArea(); }
    //: Get number of points in mask.

    const ImageC<IntT> &Mask() const
    { return Body().Mask(); }
    //: Get mask image.

    const VectorC &EigenValues() const
    { return Body().EigenValues(); }
    //: Access eigen values.

    const FunctionC &AppearanceModel() const
    { return Body().AppearanceModel(); }
    //: Access appearance model      

    const FunctionC &InvAppearanceModel() const
    { return Body().InvAppearanceModel(); }
    //: Access appearance model      

    IntT NoFixedParameters() const
    { return Body().NoFixedParameters(); }
    //: Find the number of parameters which have fixed meaning.
    // offset,scale for example.

    const VectorC &FixedMean() const
    { return Body().FixedMean(); }
    //: Get mean of fixed parameters.

    const VectorC &PixelSize() const
    { return Body().PixelSize(); }
    //: Get mean of fixed parameters.

    VectorC ShapeParameters(const VectorC &aamParams)
    { return Body().ShapeParameters(aamParams); }
    //: Extract shape parameters from active appearance model ones.

    bool TextureParameters(const ImageC<RealT> &im, VectorC &res)
    { return Body().TextureParameters(im,res); }
    //: Extract texture parameters from shape free image

    AAMShapeModelC &ShapeModel()
    { return Body().ShapeModel(); }
    //: Access shape model.

  };

}


#endif
