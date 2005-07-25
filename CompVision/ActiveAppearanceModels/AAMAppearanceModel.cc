// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlAAM
//! file="Ravl/CompVision/ActiveAppearanceModels/AAMAppearanceModel.cc"

#include "Ravl/Image/AAMAppearanceModel.hh"
#include "Ravl/Image/AAMAppearanceUtil.hh"
#include "Ravl/Image/AAMScaleRotationShapeModel.hh"
#include "Ravl/Array2dIter4.hh"
#include "Ravl/Array2dIter3.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array1dIter2.hh"
#include "Ravl/Array1dIter.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/SArray1dIter3.hh"
#include "Ravl/Polygon2d.hh"
#include "Ravl/Image/DrawPolygon.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/PatternRec/SampleVector.hh"
#include "Ravl/PatternRec/DesignFuncPCA.hh"
#include "Ravl/PatternRec/DesignFuncLSQ.hh"
#include "Ravl/PatternRec/FuncLinear.hh"
#include "Ravl/VirtualConstructor.hh"
#include "Ravl/DelaunayTriangulation2d.hh"
#include "Ravl/MeanVariance.hh"
#include "Ravl/Sums1d2.hh"
#include "Ravl/IO.hh"
#include "Ravl/Image/DrawLine.hh"
#include "Ravl/DList.hh"
#include "Ravl/String.hh"
#include "Ravl/DLIter.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/PatternRec/FuncMeanProjection.hh"

#define DODEBUG 0
#if DODEBUG
#include "Ravl/IO.hh"
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

#define OMNIAAM_USE_THINPLATEWARP 0

#if OMNIAAM_USE_THINPLATEWARP 
#include "Ravl/Image/WarpThinPlateSpline.hh"
#else
#include "Ravl/Image/WarpMesh2d.hh"
#endif

namespace RavlImageN {

  using namespace RavlN;
  using namespace RavlImageN;

  //: Constructor.
  // nWarpSigma, stiffness to use in warping process.

  AAMAppearanceModelBodyC::AAMAppearanceModelBodyC(RealT nWarpSigma)
    : warpSigma(nWarpSigma)
  {}

  //: Load from binary stream.

  AAMAppearanceModelBodyC::AAMAppearanceModelBodyC(BinIStreamC &is) 
    : RCBodyVC(is)
  {
    int version;
    ImageC<IntT> newMask;
    is >> version;
    if(version != 1) 
      throw ExceptionOutOfRangeC("AAMAppearanceModelC::AAMAppearanceModelC(BinIStreamC &s), Bad version number in stream. ");
    is >> warpSigma;
    is >> shape;
    is >> newMask;
    is >> maskPoints;
    is >> appearanceModel;
    is >> invAppearanceModel;
    is >> warp;
    is >> eigenValues;
    is >> fixedMean;
    is >> pixelSize;
    SetMask(newMask); // Setup the new mask.
  }

  //: Load from binary stream.

  AAMAppearanceModelBodyC::AAMAppearanceModelBodyC(istream &is) 
    : RCBodyVC(is)
  {
    int version;
    ImageC<IntT> newMask;
    is >> version;
    if(version != 1) 
      throw ExceptionOutOfRangeC("AAMAppearanceModelC::AAMAppearanceModelC(istream &s), Bad version number in stream. ");
    is >> warpSigma >> shape >> newMask >> maskPoints >> appearanceModel >> invAppearanceModel >> warp >> eigenValues >> fixedMean >> pixelSize;
;
    SetMask(newMask); // Setup the new mask.
  }

  //: Save to binary stream 'out'.

  bool AAMAppearanceModelBodyC::Save(BinOStreamC &out) const {
    if(!RCBodyVC::Save(out))
      return false;
    int version = 1;
    out << version << warpSigma << shape << mask << maskPoints << 
      appearanceModel << invAppearanceModel << warp << eigenValues << fixedMean << pixelSize;
    return true;
  }

  //: Save to stream 'out'.

  bool AAMAppearanceModelBodyC::Save(ostream &out) const {
    if(!RCBodyVC::Save(out))
      return false;
    int version = 1;
    out << ' ' << version << ' ' << warpSigma << ' ' << shape << ' ' << mask << ' ' 
	<< maskPoints << ' ' << appearanceModel << ' ' << invAppearanceModel << ' ' 
	<< warp << ' ' << eigenValues << ' ' << fixedMean << ' ' << pixelSize;
    return true;
  }


  //: Convert model instance into a parameter vector.

  VectorC AAMAppearanceModelBodyC::Parameters(const AAMAppearanceC &inst) {
    VectorC rawParam = RawParameters(inst);
    VectorC fixedParam = rawParam.From(0,NoFixedParameters());
    return fixedParam.Join(appearanceModel.Apply(rawParam.From(NoFixedParameters())));
  }

  //: Set mask image to use.

  void AAMAppearanceModelBodyC::SetMask(const ImageC<IntT> &nmask) {
    maskArea = 0;
    mask = nmask;
    maskSize = mask.Frame();
    for(Array2dIterC<IntT> it(mask);it;it++)
      if(*it != 0)
	maskArea++;
  }

  //: Get raw parameters for 'inst'

  VectorC AAMAppearanceModelBodyC::RawParameters(const AAMAppearanceC &inst) {
    VectorC ret(maskArea + shape.Dimensions() + 2);

    ONDEBUG(RavlN::Save("@X:RawImage",inst.Image()));
    ImageC<ByteT> img = WarpToMaskShape(inst);
    ONDEBUG(RavlN::Save("@X:WarpedImage",img));
    SArray1dIterC<RealT> rit(ret);

    // Get shape parameters.

    VectorC parm = shape.Parameters(inst);
    RavlAssert(parm.Size() == shape.Dimensions());

    // Copy fixed shape parameters.

    for(SArray1dIterC<RealT> cit(parm,shape.NoFixedParameters());cit;cit++) {
      *rit = *cit;
      rit++;
    }

    // Compute mean and variance of texture.
    Sums1d2C textureMeanVar;
    for(Array2dIter2C<IntT,ByteT> it(mask,img);it;it++)
      textureMeanVar += (RealT) it.Data2();

    RealT texmean = textureMeanVar.Mean();
    RealT texstddev = Sqrt(textureMeanVar.Variance());

    ONDEBUG(cerr << "TexMean=" << texmean << " TexVar=" << texstddev << " N=" << textureMeanVar.Size() << "\n");

    // Save fixed texture parameters.
    // The parametrisation is adopted for linearity required
    // for fitting algorithm which uses multivariate linear regression
    *rit = texmean; rit++;
    *rit = texstddev - 1; rit++;

    // Copy rest of shape parameters

    for(SArray1dIterC<RealT> sit(parm.From(shape.NoFixedParameters()));sit;sit++) {
      *rit = *sit;
      rit++;
    }

    // Get texture parameters.

    for(Array2dIter2C<IntT,ByteT> it(mask,img);it;it++) {
      if(it.Data1() != 0) {
	*rit = (((RealT) it.Data2()) - texmean) / texstddev;
	rit++;
      }
    }

    return ret;
  }

  //: Warp appearance to mean shape.

  ImageC<ByteT> AAMAppearanceModelBodyC::WarpToMaskShape(const AAMAppearanceC &inst) {
#if OMNIAAM_USE_THINPLATEWARP 
    ImageC<ByteT> ret(maskSize);
    WarpThinPlateSplineC<ByteT> warp(warpSigma);
    warp.Apply(inst.Image(),Array1dC<Point2dC>(inst.Points()),maskPoints,ret);
#else
    ImageC<ByteT> ret(maskSize);
    warp.Apply(inst.Image(),inst.Points(),ret);
#endif
    return ret;
  }


  //: Design a model given some data.

  bool AAMAppearanceModelBodyC::Design(const DListC<StringC> &fileList,const StringC &dir,const StringC &mirrorFile,const Index2dC &newMaskSize,const RealT varS,const RealT varT,const RealT varC,const UIntT maxS,const UIntT maxT,const UIntT maxC) {
  // This implementation of the function Design avoids loading all the
  // data into memory, which keeps the memory requirement at a minimum

    shape = AAMScaleRotationShapeModelC(true);

    ONDEBUG(cerr << "AAMAppearanceModelBodyC::Design(), Designing shape model. \n");

    // Design the shape model.
    SampleC<AAMAppearanceC> appearanceSet;
    appearanceSet = LoadFeatureSet(fileList,dir,true,false);

    if(!mirrorFile.IsEmpty()) {
      cout << "Reflecting data. \n";
      AAMAppearanceMirrorC mirror(mirrorFile);
      if(!mirror.IsValid()) {
        cerr << "ERROR: Failed to read mirror file. \n";
        return 1;
      }
      mirror.Reflect(appearanceSet);
    }

    IntT NbSamples = appearanceSet.Size();
    cout << "Got " << NbSamples << " samples. \n";

    if(!shape.Design(appearanceSet,varS,maxS))
      return false;


    ONDEBUG(cerr << "AAMAppearanceModelBodyC::Design(), Generating mask. \n");

    // Use mean positions for mask.
    maskPoints = shape.MeanPoints();
    if(maskPoints.Size() == 0)
      return false;

    // Find bounding rectangle of mask points.
    RealRange2dC rng(maskPoints[0],0,0);
    for(Array1dIterC<Point2dC> it(maskPoints);it;it++)
      rng.Involve(*it);

    // Scale control points to desired size.
    Point2dC offset = rng.Origin();
    Vector2dC scale = (Point2dC(newMaskSize) - Point2dC(1.0,1.0)) / (rng.End() - rng.Origin());

    for(Array1dIterC<Point2dC> it(maskPoints);it;it++)
      *it = (*it - offset) * scale;

    // Find bounding rectangle of control points
    pixelSize = Vector2dC(rng.Rows()/newMaskSize.Row(),rng.Cols()/newMaskSize.Col());
    // Create a mask from a convex hull of the control points.
    Polygon2dC bounds = ConvexHull(maskPoints.SArray1d(true));
    maskSize = bounds.BoundingRectangle().IndexRange();

    mask = ImageC<IntT>(maskSize);
    mask.Fill(0);
    DrawPolygon(mask,1,bounds,true); // Draw convex hull into the mask.

    ONDEBUG(cerr << "Mask = " << mask.Frame() << "\n");

    // Create warping mesh.
    TriMesh2dC mesh = DelaunayTriangulation(maskPoints).TriMesh();
    RavlAssert(mesh.IsFlat());
    SetMask(mask); // Setup the new mask.

    // Create warping
    warp.CreateWarpMap(mesh,mask.Frame());

    ONDEBUG(cerr << "AAMAppearanceModelBodyC::Design(), Computing appearance parameters. \n");

    // Now we're ready to compute the parameters

    // number of texture parameters
    const IntT localFixed = NoFixedParameters() - shape.NoFixedParameters();
    SArray1dC<Sums1d2C> stats(localFixed);
    for(SArray1dIterC<Sums1d2C> yit(stats);yit;yit++)
      yit->Reset();

    IntT NoPerFile;
    AAMAppearanceMirrorC mirror;
    if (mirrorFile.IsEmpty()) {
      NoPerFile = 1;
    }
    else {
      mirror = AAMAppearanceMirrorC(mirrorFile);
      if(!mirror.IsValid()) {
        cerr << "ERROR: Failed to read mirror file. \n";
        return 1;
      }
      NoPerFile = 2;
    }

    // vector of parameters
    SampleVectorC textureValues(NbSamples);
    for(DLIterC<StringC> it(fileList);it;it++) {
      for (IntT k=1;k<=NoPerFile;k++) {

        AAMAppearanceC appear = LoadFeatureFile(*it,dir);
        if (k == 2) {
          appear = mirror.Reflect(appear);      
        }

        VectorC vec = RawParameters(appear);
        textureValues.Append(vec.From(NoFixedParameters() - shape.NoFixedParameters() + shape.Dimensions()));
        for(SArray1dIter2C<Sums1d2C,RealT> zit(stats,vec.From(shape.NoFixedParameters(),localFixed));zit;zit++)
    	  zit.Data1() += zit.Data2();
      }
    }

    ONDEBUG(cerr << "AAMAppearanceModelBodyC::Design(), Doing PCA of texture parameters. \n");

    // Do pca on texture values
    DesignFuncPCAC designTexturePCA(varT);
    designTexturePCA.Apply(textureValues);

    // Apply limit on number of parameters
    if(designTexturePCA.Pca().Vector().Size()>maxT) {
      designTexturePCA.Pca().Vector() = designTexturePCA.Pca().Vector().From(0,maxT);
      designTexturePCA.Pca().Matrix() = designTexturePCA.Pca().Matrix().SubMatrix(maxT,designTexturePCA.Pca().Matrix().Cols());
    }

    // Create shape parameter weights
    VectorC textureEigenValues = designTexturePCA.Pca().Vector();
    VectorC shapeEigenValues = shape.EigenValues();
    shapeEigenValues = shapeEigenValues.From(shape.NoFixedParameters());
    RealT w = sqrt(textureEigenValues.Sum()/shapeEigenValues.Sum());
    MatrixC W = MatrixC::Identity(shape.Dimensions()-shape.NoFixedParameters())*w;

    // Create mean
    VectorC mi(shape.Dimensions()-shape.NoFixedParameters());
    mi.Fill(0);
    mi.Append(designTexturePCA.Mean());
    // Create projection matrix for texture model
    MatrixC Pi(shape.Dimensions() - shape.NoFixedParameters()+designTexturePCA.Pca().Matrix().Rows(), shape.Dimensions() - shape.NoFixedParameters() + maskArea);
    Pi.Fill(0);
    Pi.SetSubArray(Index2dC(0,0),W);
    Pi.SetSubArray(Index2dC(W.Rows(),W.Cols()),designTexturePCA.Pca().Matrix());
    // Create "inverse" projection matrix for texture model
    MatrixC invPi(Pi.T());
    invPi.Fill(0);
    invPi.SetSubArray(Index2dC(0,0),W.Inverse());
    invPi.SetSubArray(Index2dC(W.Rows(),W.Cols()),designTexturePCA.Pca().Matrix().T());
    // Create model which compresses both shape and texture
    FuncMeanProjectionC intermediateModel(mi,Pi);

    // Assemble all vectors of parameters
    SampleVectorC combinedValues(NbSamples);
    for(DLIterC<StringC> it(fileList);it;it++) {
      for (IntT k=1;k<=NoPerFile;k++) {
        AAMAppearanceC appear = LoadFeatureFile(*it,dir);
        if (k == 2) {
          appear = mirror.Reflect(appear);      
        }
	VectorC vec = RawParameters(appear);
        combinedValues.Append(intermediateModel.Apply(vec.From(NoFixedParameters())));
      }
    }

    ONDEBUG(cerr << "AAMAppearanceModelBodyC::Design(), Doing PCA of combined parameters. \n");

    // Do pca on combined values
    DesignFuncPCAC designCombinedPCA(varC);
    designCombinedPCA.Apply(combinedValues);

    // Apply limit on number of parameters
    if(designCombinedPCA.Pca().Vector().Size()>maxC) {
      designCombinedPCA.Pca().Vector() = designCombinedPCA.Pca().Vector().From(0,maxC);
      designCombinedPCA.Pca().Matrix() = designCombinedPCA.Pca().Matrix().SubMatrix(maxC,designCombinedPCA.Pca().Matrix().Cols());
    }

    // Create projection matrices for combined model
    MatrixC Pc = designCombinedPCA.Pca().Matrix() * Pi;
    MatrixC invPc =  invPi * designCombinedPCA.Pca().Matrix().T();

    // Create combined model
    appearanceModel = FuncMeanProjectionC(mi,Pc);
    invAppearanceModel = FuncLinearC(invPc,mi);

    // Sort out mean and variance's of fixed parameters.
    fixedMean = VectorC(NoFixedParameters());    
    VectorC fixedVar(NoFixedParameters());
    int i;
    for(i = 0;i < shape.NoFixedParameters();i++) {
      fixedMean[i] = shape.FixedMean()[i];
      fixedVar[i] = shape.EigenValues()[i];
    }

    for(SArray1dIter3C<Sums1d2C,RealT,RealT> xit(stats,fixedMean.From(shape.NoFixedParameters()),fixedVar.From(shape.NoFixedParameters()));xit;xit++) {
      xit.Data2() = xit.Data1().Mean();
      xit.Data3() = xit.Data1().Variance();
    }

    // Sort out eigen values of model.
    eigenValues = fixedVar.Join(designCombinedPCA.Pca().Vector());

    // And we're done!
    ONDEBUG(cerr << "AAMAppearanceModelBodyC::Design(), Done. \n");

    return true;
  }


  //: Synthesize an appearance from a parameter vector.

  AAMAppearanceC AAMAppearanceModelBodyC::Synthesize(const VectorC &dat,RealT scale) {
    RavlAssert(Dimensions() == dat.Size());

    VectorC tmp(dat);
    VectorC rv = invAppearanceModel.Apply(tmp.From(NoFixedParameters()));

    SArray1dIterC<RealT> rit(rv);

    // Get fixed shape parameters.

    VectorC sp(shape.Dimensions());
    SArray1dIterC<RealT> sit(sp);
    for(int i = 0;i < shape.NoFixedParameters();i++,sit++)
      *sit = dat[i];

    // Get fixed texture parameters.

    RealT texMean = dat[shape.NoFixedParameters() + 0];
    RealT texStdDev = dat[shape.NoFixedParameters() + 1] + 1;

    // Get rest of shape parameters.

    for(;sit;sit++) {
      *sit = *rit;
      rit++;
    }

    // Create texture image

    ImageC<RealT> image(mask.Frame());
    for(Array2dIter2C<IntT,RealT> it(mask,image);it;it++) {
      if(it.Data1() != 0) {
	it.Data2() = (*rit * texStdDev) + texMean;
	rit++;
      } else
	it.Data2() = 0;
    }

    SArray1dC<Point2dC> pnts = shape.Synthesize(sp);
    RealRange2dC rng(pnts[0],0,0);
    for(SArray1dIterC<Point2dC> it(pnts);it;it++) {
      *it *= scale;
      rng.Involve(*it);
    }

    // Warp it.

    ImageC<RealT> nimg(rng.IndexRange());
#if OMNIAAM_USE_THINPLATEWARP 
    WarpThinPlateSplineC<RealT,RealT> warp(warpSigma);
    warp.Apply(image,Array1dC<Point2dC>(maskPoints),Array1dC<Point2dC>(pnts),nimg);
#else
    nimg.Fill(0);
    WarpMesh2dC<RealT,RealT> rwarp(warp);
    rwarp.InvApply(image,pnts,nimg);
#endif
    ImageC<ByteT> nimgB(rng.IndexRange());
    for(Array2dIter2C<RealT,ByteT> it(nimg,nimgB);it;it++)
      it.Data2() = (ByteT) it.Data1();

    return  AAMAppearanceC(pnts,nimgB);
  }


  bool AAMAppearanceModelBodyC::TextureImage(const VectorC &dat,ImageC<RealT> &res) {
    RavlAssert(Dimensions() == dat.Size());
    RavlAssert(res.Frame() == mask.Frame());

    VectorC tmp(dat);
    VectorC rv = invAppearanceModel.Apply(tmp.From(NoFixedParameters()));

    SArray1dIterC<RealT> rit(rv.From(shape.Dimensions()-shape.NoFixedParameters()));

    // Get fixed texture parameters.
    RealT texMean = dat[shape.NoFixedParameters() + 0];
    RealT texStdDev = dat[shape.NoFixedParameters() + 1] + 1;

    // Create texture image
    for(Array2dIter2C<IntT,RealT> it(mask,res);it;it++) {
      if(it.Data1() != 0) {
	it.Data2() = (*rit * texStdDev) + texMean;
	rit++;
      } else
	it.Data2() = 0;
    }

    return 1;
  }


  bool AAMAppearanceModelBodyC::TextureParameters(const ImageC<RealT> &im, VectorC &res) {
    RavlAssert(im.Frame() == mask.Frame());
    RavlAssert(maskArea+NoFixedParameters()-shape.NoFixedParameters() == res.Size());

    SArray1dIterC<RealT> rit(res);
    rit.First();

    Sums1d2C textureMeanVar;
    for(Array2dIter2C<IntT,RealT> it(mask,im);it;it++) {
      if(it.Data1() != 0) {
        textureMeanVar += (RealT) it.Data2();
      }
    }
    RealT texmean = textureMeanVar.Mean();
    RealT texstddev = Sqrt(textureMeanVar.Variance());
    *rit=texmean;
    rit++;
    *rit=texstddev-1;
    rit++;

    for(Array2dIter2C<IntT,RealT> it(mask,im);it;it++) {
      if(it.Data1() != 0) {
	*rit = (it.Data2() - texmean) / texstddev;
	rit++;
      }
    }

    return true;
  }


  //: Extract shape parameters from active appearance model ones.

  VectorC AAMAppearanceModelBodyC::ShapeParameters(const VectorC &dat) {
    RavlAssert(Dimensions() == dat.Size());

    VectorC res(shape.Dimensions());
    VectorC tmp(dat);
    VectorC rv = invAppearanceModel.Apply(tmp.From(NoFixedParameters()));
    for(int i = 0;i < shape.NoFixedParameters();i++)
      res[i] = dat[i];
    for(SArray1dIter2C<RealT,RealT> it(res.From(shape.NoFixedParameters()),rv.From(0,shape.Dimensions() - shape.NoFixedParameters()));it;it++)
      it.Data1() = it.Data2();
    return res;
  }


  //: Compute error vector.

  bool AAMAppearanceModelBodyC::ErrorVector(const VectorC &dat,const ImageC<RealT> &img,VectorC &errVec) const {
    RavlAssert(Dimensions() == dat.Size());
    VectorC tmp(dat);
    VectorC rv = invAppearanceModel.Apply(tmp.From(NoFixedParameters()));

    SArray1dIterC<RealT> rit(rv);

    // Get shape parameters.

    VectorC sp(shape.Dimensions());
    SArray1dIterC<RealT> sit(sp);

    for(int i = 0;i < shape.NoFixedParameters();i++,sit++)
      *sit = dat[i];

    // Get texture mean and variance.

    RealT texMean = dat[shape.NoFixedParameters() + 0];
    RealT texStdDev = dat[shape.NoFixedParameters() + 1] + 1;

    // Copy rest of shape parameters

    for(;sit;sit++) {
      *sit = *rit;
      rit++;
    }

    SArray1dC<Point2dC> pnts = shape.Synthesize(sp);

    // Find bounding rectangle of points
    RealRange2dC rng(pnts[0],0,0);
    for(Array1dIterC<Point2dC> it(pnts);it;it++)
      rng.Involve(*it);

    bool isInRange;
    if((rng.TRow()<img.Frame().TRow())||(rng.BRow()>img.Frame().BRow())||(rng.LCol()<img.Frame().LCol())||(rng.RCol()>img.Frame().RCol()))
      isInRange=false;
    else
      isInRange=true;

    // Warp original image into original mask position.

    ImageC<RealT> nimg(maskSize);
    ONDEBUG(nimg.Fill(0));
#if OMNIAAM_USE_THINPLATEWARP 
    WarpThinPlateSplineC<RealT,RealT> warp(warpSigma,true);
    warp.Apply(img,Array1dC<Point2dC>(pnts),Array1dC<Point2dC>(maskPoints),nimg);
#else
    WarpMesh2dC<RealT,RealT> rwarp(warp);
    rwarp.Apply(img,pnts,nimg);
#endif

    // Generate difference vector.

    //if(errVec.Size() != (UIntT) maskArea)
    errVec = VectorC(maskArea);

#if DODEBUG && 1
    Array1dIterC<RealT> eit(errVec);
    ImageC<RealT> errImg(mask.Frame());
    errImg.Fill(0);
    // model
    ImageC<RealT> mImg(mask.Frame());
    mImg.Fill(0);
    for(Array2dIter4C<IntT,RealT,RealT,RealT> it(mask,nimg,errImg,mImg,maskSize);it;it++) {
      if(it.Data1() != 0) {
	*eit = ((it.Data2() - texMean) / texStdDev)  - *rit;
	it.Data3() = *eit;
	it.Data4() = (*rit) * texStdDev + texMean;
	rit++;
	eit++;
      }
    }
    RavlN::Save("@X:Image",nimg);
    RavlN::Save("@X:Model",mImg);
    RavlN::Save("@X:Error",errImg);
#else
    Array1dIterC<RealT> eit(errVec);
    for(Array2dIter2C<IntT,RealT> it(mask,nimg,maskSize);it;it++) {
      if(it.Data1() != 0) {
	*eit = ((it.Data2() - texMean) / texStdDev) - *rit;
	rit++;
	eit++;
      }
    }
#endif

  return isInRange;

  }

  bool AAMAppearanceModelBodyC::ErrorVector(const VectorC &dat,const ImageC<ByteT> &img,VectorC &errVec) const {

    // Create real image
    ImageC<RealT> rimg(img.Frame());
    for(Array2dIter2C<RealT,ByteT> it(rimg,img);it;it++)
      it.Data1() = (RealT) it.Data2();

    // Compute error vector
    return ErrorVector(dat,rimg,errVec);

  }

  void AAMAppearanceModelBodyC::MakePlausible(VectorC &dat, RealT NbSigma) const {

    VectorC tmp = eigenValues;
    for(Array1dIter2C<RealT,RealT> it(dat.From(NoFixedParameters()),tmp.From(NoFixedParameters()));it;it++) {
      if(Abs(it.Data1())>NbSigma*Sqrt(it.Data2())) {
        cerr << ".";
        if(it.Data1()>0) {
	  it.Data1() = NbSigma*Sqrt(it.Data2());
	}
	else {
	  it.Data1() = -NbSigma*Sqrt(it.Data2());
	}
      }
    }

  }


  RAVL_INITVIRTUALCONSTRUCTOR_FULL(AAMAppearanceModelBodyC,AAMAppearanceModelC,RCHandleVC<AAMAppearanceModelBodyC>);

}
