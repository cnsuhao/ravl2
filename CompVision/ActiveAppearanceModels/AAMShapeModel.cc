// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlAAM
//! file="Ravl/CompVision/ActiveAppearanceModels/AAMShapeModel.cc"

#include "Ravl/Image/AAMShapeModel.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/PatternRec/SampleVector.hh"
#include "Ravl/PatternRec/DesignFuncPCA.hh"
#include "Ravl/PatternRec/DesignFuncLSQ.hh"
#include "Ravl/PatternRec/FuncLinear.hh"
#include "Ravl/VirtualConstructor.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/Moments2d2.hh"
#include "Ravl/Sums1d2.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/SArray1dIter3.hh"
#include "Ravl/PatternRec/FuncMeanProjection.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {

  using namespace RavlN;
  
  //: Load from bin stream.
  
  AAMShapeModelBodyC::AAMShapeModelBodyC(BinIStreamC &s)
    : RCBodyVC(s)
  {
    int version;
    s >> version;
    if(version != 1)
      throw ExceptionOutOfRangeC("AAMShapeModelC::AAMShapeModelC(BinIStreamC &s), Bad version number in stream. ");
    s >> shapeModel >> invShapeModel >> meanPoints >> eigenValues >> fixedMean;
#if 0
    if(fixedMean.Size() != (UIntT) NoFixedParameters())
      throw ExceptionOutOfRangeC("AAMShapeModelC::AAMShapeModelC(BinIStreamC &s), Bad parameter in stream. ");
#endif
    nPoints = meanPoints.Size();
  }

  AAMShapeModelBodyC::AAMShapeModelBodyC(istream &s)
    : RCBodyVC(s)
  {
    int version;
    s >> version;
    if(version != 1)
      throw ExceptionOutOfRangeC("AAMShapeModelC::AAMShapeModelC(istream &s), Bad version number in stream. ");
    s >> shapeModel >> invShapeModel >> meanPoints >> eigenValues >> fixedMean; 
#if 0
    if(fixedMean.Size() != (UIntT) NoFixedParameters())
      throw ExceptionOutOfRangeC("AAMShapeModelC::AAMShapeModelC(BinIStreamC &s), Bad parameter in stream. ");
#endif
    nPoints = meanPoints.Size();
  }
  
  //: Save to binary stream 'out'.
  
  bool AAMShapeModelBodyC::Save(BinOStreamC &s) const {
    if(!RCBodyVC::Save(s))
      return false;
    int version = 1;
    s << version << shapeModel << invShapeModel << meanPoints << eigenValues << fixedMean;
    return true;
  }

  //: Save to binary stream 'out'.
  
  bool AAMShapeModelBodyC::Save(ostream &s) const {
    if(!RCBodyVC::Save(s))
      return false;    
    int version = 1;
    s << ' ' << version << ' ' << shapeModel << ' ' << invShapeModel << ' ' << meanPoints << ' ' << eigenValues << ' ' << fixedMean;
    return true;
  }
  
  //: Generate a raw parameter vector.
  
  bool AAMShapeModelBodyC::RawParameters(const AAMAppearanceC &inst,VectorC &fixedParams,VectorC &freeParams) const {
    IntT size = inst.Points().Size() * 2;
    freeParams = VectorC (size);
    fixedParams = VectorC(NoFixedParameters());
    SArray1dIterC<Point2dC> pi(inst.Points());
    
    // Sort out parameters with fixed meanings.
    Moments2d2C moments;    
    for(;pi;pi++)
      moments += *pi;
    
    Point2dC mean = moments.Centroid();
    RealT scale = Sqrt(moments.VarX() + moments.VarY());
    
    fixedParams = VectorC(3);
    fixedParams[0] = mean[0];
    fixedParams[1] = mean[1];
    fixedParams[2] = scale;
    
    // Sort out the point positions.
    
    SArray1dIterC<RealT> vi(freeParams);
    for(pi.First();pi;pi++) {
      *vi = ((*pi)[0] - mean[0]) / scale;
      vi++;
      *vi = ((*pi)[1] - mean[1]) / scale;
      vi++;
    }
    return true;
  }

  //: Generate points from a raw parameter vector.
  
  void AAMShapeModelBodyC::RawProject(const VectorC &fixedParams,const VectorC &freeParams,SArray1dC<Point2dC> &out) const {
    //cerr << "nPoints=" << nPoints << "\n";
    RavlAssert((freeParams.Size()/2) == nPoints);
    if(nPoints != out.Size())
      out = SArray1dC<Point2dC>(nPoints);
    SArray1dIterC<RealT> vi(freeParams);
    Point2dC mean(fixedParams[0],fixedParams[1]);
    RealT scale = fixedParams[2];
    for(SArray1dIterC<Point2dC> pi(out);pi;pi++) {
      (*pi)[0] = ((*vi) * scale) + mean[0];
      vi++;
      (*pi)[1] = ((*vi) * scale) + mean[1];
      vi++;
    }
  }
  
  
  //: Convert model instance into a parameter vector.
  
  VectorC AAMShapeModelBodyC::Parameters(const AAMAppearanceC &inst) const {
    VectorC fixedParams;
    VectorC freeParams;
    RawParameters(inst,fixedParams,freeParams);
    return fixedParams.Join(const_cast<FunctionC &>(shapeModel).Apply(freeParams));
  }
  
  //: Compute mean points.
  
  bool AAMShapeModelBodyC::ComputeMean(const SampleC<AAMAppearanceC> &sample) {
    // Don't need to do anything by default.
    return true;
  }
  
  //: Design a model given some data.
  
  bool AAMShapeModelBodyC::Design(const SampleC<AAMAppearanceC> &sample,RealT variation, UIntT maxP) {
    SampleVectorC vectors(sample.Size());
    
    //: Do some initial processing, needed for some models.
    
    if(!ComputeMean(sample))
      return false;
    
    //: Generate sample of raw vectors.
    
    SampleIterC<AAMAppearanceC> it(sample);
    if(!it)
      return false; // No data points!
    nPoints = it->Points().Size();
    
    SArray1dC<Sums1d2C> stats(NoFixedParameters());
    for(SArray1dIterC<Sums1d2C> yit(stats);yit;yit++)
      yit->Reset();
    
    for(;it;it++) {
      VectorC vec,nfixed;
      RawParameters(*it,nfixed,vec);
      vectors.Append(vec);
      for(SArray1dIter2C<Sums1d2C,RealT> zit(stats,nfixed);zit;zit++)
	zit.Data1() += zit.Data2();
    }
    
    fixedMean = VectorC(NoFixedParameters());
    VectorC fixedVar(NoFixedParameters());
    for(SArray1dIter3C<Sums1d2C,RealT,RealT> xit(stats,fixedMean,fixedVar);xit;xit++) {
      xit.Data2() = xit.Data1().Mean();
      xit.Data3() = xit.Data1().Variance();
    }
    
    ONDEBUG(cerr << "FixedMean=" << fixedMean << "\n");
    ONDEBUG(cerr << "FixedVar=" << fixedVar << "\n");
    
    // Do pca.
    
    DesignFuncPCAC designPCA(variation);
    designPCA.Apply(vectors); // Design parameter to shape function.

    // Apply limit on number of parameters
    if(designPCA.Pca().Vector().Size()>maxP) {
      designPCA.Pca().Vector() = designPCA.Pca().Vector().From(0,maxP);
      designPCA.Pca().Matrix() = designPCA.Pca().Matrix().SubMatrix(maxP,designPCA.Pca().Matrix().Cols());
    }

    // Create model
    shapeModel = FuncMeanProjectionC(designPCA.Mean(),designPCA.Pca().Matrix());
    
    eigenValues = fixedVar.Join(designPCA.Pca().Vector());
    
    // compute inverse model
    invShapeModel = FuncLinearC(designPCA.Pca().Matrix().T(),designPCA.Mean());
    
    RawProject(fixedMean,designPCA.Mean(),meanPoints);
    return true;
  }
  
  //: Synthesis a point set from model parameters.
  
  SArray1dC<Point2dC> AAMShapeModelBodyC::Synthesize(const VectorC &parm) const {
    SArray1dC<Point2dC> ret;
    VectorC tmp(parm);
    VectorC fixed = tmp.From(0,NoFixedParameters());
    VectorC params = tmp.From(NoFixedParameters());
    VectorC vec = invShapeModel.Apply(params);
    RawProject(fixed,vec,ret);
    return ret;
  }

  //: Find the number of parameters which have fixed meaning.
  // offset,scale for example.
  
  IntT AAMShapeModelBodyC::NoFixedParameters() const { 
    return 3; 
  }
  
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(AAMShapeModelBodyC,AAMShapeModelC,RCHandleVC<AAMShapeModelBodyC>);

}
