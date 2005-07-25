// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlAAM
//! file="Ravl/CompVision/ActiveAppearanceModels/AAMActiveAppearanceModel.cc"

#include "Ravl/Image/AAMActiveAppearanceModel.hh"
#include "Ravl/Image/AAMAppearanceUtil.hh"
#include "Ravl/Image/AAMSampleStream.hh"
#include "Ravl/PatternRec/DesignFuncLSQ.hh"
#include "Ravl/PatternRec/FuncLinear.hh"
#include "Ravl/PatternRec/FuncLinearCoeff.hh"
#include "Ravl/PatternRec/SampleVector.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/Affine2d.hh"
#include "Ravl/Image/WarpAffine.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/SArray1dIter3.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Angle.hh"
#include "Ravl/VirtualConstructor.hh"
#include "Ravl/Random.hh"
#include "Ravl/DList.hh"
#include "Ravl/String.hh"
#include "Ravl/DLIter.hh"
#include "Ravl/Slice1d.hh"
#include "Ravl/Slice1dIter.hh"
#include "Ravl/MatrixRUT.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/MatrixRS.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/DP/FileFormatIO.hh"

#define DODEBUG 0
#if DODEBUG
#include "Ravl/OS/Date.hh"
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {

  using namespace RavlImageN;
  
  //: Constructor.
  
  AAMActiveAppearanceModelBodyC::AAMActiveAppearanceModelBodyC()
    : smooth(3)
  {}
  
  //: Load from bin stream.
  
  AAMActiveAppearanceModelBodyC::AAMActiveAppearanceModelBodyC(BinIStreamC &is)
    : RCBodyVC(is)
  {
    int version;
    is >> version;
    if(version != 1)
      throw ExceptionOutOfRangeC("AAMActiveAppearanceModelC:SAAMActiveAppearanceModelC(BinIStreamC &s), Bad version number in stream. ");
    
    is >> refHome >> appearanceModel >> refiner >> smooth;
  }
  
  //: Load from stream.
  
  AAMActiveAppearanceModelBodyC::AAMActiveAppearanceModelBodyC(istream &is) 
    : RCBodyVC(is)
  {
    int version;
    is >> version;
    if(version != 1)
      throw ExceptionOutOfRangeC("AAMActiveAppearanceModelC:SAAMActiveAppearanceModelC(istream &s), Bad version number in stream. ");
    
    is >> refHome >> appearanceModel >> refiner >> smooth;
  }
  
  //: Save to binary stream 'out'.
  
  bool AAMActiveAppearanceModelBodyC::Save(BinOStreamC &out) const {
    if(!RCBodyVC::Save(out))
      return false;    
    int version = 1;
    out << version << refHome << appearanceModel << refiner << smooth;
    return true;
  }

  //: Save to stream 'out'.
  
  bool AAMActiveAppearanceModelBodyC::Save(ostream &out) const {
    if(!RCBodyVC::Save(out))
      return false;
    int version = 1;
    out << ' ' << version << ' ' << ' ' << refHome << ' ' << appearanceModel << ' ' << refiner << ' ' << smooth;    
    return true;
  }
  
  //: Refine pose parameters based on an initial estimate of parameters.
  VectorC AAMActiveAppearanceModelBodyC::RefinePose(const ImageC<ByteT> &img,VectorC paramEstimate) {    
    RealT diff;
    return RefinePose(img,paramEstimate,diff);
  }

  //: Refine pose parameters based on an initial estimate of parameters.
  VectorC AAMActiveAppearanceModelBodyC::RefinePose(const ImageC<ByteT> &img,VectorC paramEstimate, RealT &diff) {
    ImageC<RealT> rimg(img.Frame());
    for(Array2dIter2C<RealT,ByteT> it(rimg,img);it;it++)
      it.Data1() = (RealT) it.Data2();
    
    rimg = smooth.Apply(rimg); // Filter the image a little.
    
    return RefinePose(rimg,paramEstimate,diff);
  }
  
  //: Refine pose parameters based on an initial estimate of parameters.
  VectorC AAMActiveAppearanceModelBodyC::RefinePose(const ImageC<RealT> &rimg,VectorC paramEstimate, RealT &diff) {
    VectorC lastParm = paramEstimate.Copy();
    VectorC errVec,lastErr;
    
    appearanceModel.ErrorVector(lastParm,rimg,errVec); // Compute residual error.
    diff = errVec.SumOfSqr()/errVec.Size();
    RealT oldDiff;
    UIntT iters =0;
    do {
      oldDiff = diff;
      
      VectorC newDelta = refiner.Apply(errVec);
      VectorC newEst = lastParm - newDelta;
      appearanceModel.ErrorVector(newEst,rimg,errVec); // Compute residual error.
      RealT nErr = errVec.SumOfSqr()/errVec.Size();
      iters++;
      if(nErr < diff) {
	lastParm = newEst;
	diff = nErr;
	continue; 
      }
      RealT mul = 1.5;
      UIntT scanLimit = 6;
      // Go through successively smaller steps until we fine one thats better.
      for(UIntT i = 0;i < scanLimit;i++,mul /= 2.0) {
	VectorC newEst = lastParm - newDelta * mul;
	appearanceModel.ErrorVector(newEst,rimg,errVec); // Compute residual error.
	RealT nErr = errVec.SumOfSqr()/errVec.Size();
        if(nErr < diff) {
	  lastParm = newEst;
	  diff = nErr;
	  continue; 
        }
      }
    }
    while(diff < oldDiff);

    cerr << "Finished refinement. Raw Error=" << diff << "\t"  << iters << "\n";
    
    return lastParm;
  }
    
  //: Design a model given some data and an existing appearance model.
  
  bool AAMActiveAppearanceModelBodyC::Design(const AAMAppearanceModelC apm,const DListC<StringC> &fileList,const StringC &dir,const StringC &mirrorFile, const UIntT incrSize) {
    ONDEBUG(cerr << "AAMActiveAppearanceModelBodyC::Design(), Called. \n");
    appearanceModel = apm;
    AAMSampleStreamC ss(appearanceModel,smooth,fileList,dir,mirrorFile,incrSize);
    DesignFuncLSQC design(1,false);
    refiner = design.Apply(ss);
    ONDEBUG(cerr << "\nAAMActiveAppearanceModelBodyC::Design(), Done. \n");
    
    // Should check how well the function works ?
    return true;
  }
  
  //: Design a model given some data and an existsing appearance model.
  
  bool AAMActiveAppearanceModelBodyC::PreDesign(const AAMAppearanceModelC apm,const DListC<StringC> &fileList,const StringC &dir,const StringC &mirrorFile, const UIntT incrSize, const StringC &op) {
    ONDEBUG(cerr << "AAMActiveAppearanceModelBodyC::PreDesign(), Called. \n");
    appearanceModel = apm;
    AAMSampleStreamC ss(appearanceModel,smooth,fileList,dir,mirrorFile,incrSize);

    Tuple2C<VectorC,VectorC> tup;
    if(!ss.Get(tup)) {
      cerr << "AAMActiveAppearanceModelBodyC::PreDesign(), WARNING: Dataset empty. ";
      return false;
    }

    // initialise the matrices    
    MatrixRUTC aaTu(tup.Data1().Size());
    aaTu.Fill(0);
    MatrixC aTb(tup.Data1().Size(),tup.Data2().Size());
    aTb.Fill(0);
    
     // Reset to the first element.
    ss.First();
    // Do some sums without duplicating data.
    while(ss.Get(tup)) {
      aaTu.AddOuterProduct(tup.Data1());
      aTb.AddOuterProduct(tup.Data1(),tup.Data2());
    }

    // to garantee correct conversion from MatrixRUTC to MatrixC    
    aaTu.ZeroLowerLeft();
    
    SArray1dC<MatrixC> res(2);
    res[0] = aaTu;
    res[1] = aTb;
    
    if(!RavlN::Save(op,res)) {
      return false;
    }
    
    ONDEBUG(cerr << "\nAAMActiveAppearanceModelBodyC::PreDesign(), Done. \n");

    return true;
  }
  
  //: Design a model given some data and an existsing appearance model.
  
  bool AAMActiveAppearanceModelBodyC::PostDesign(const AAMAppearanceModelC apm,const DListC<StringC> &fileList,const StringC &dir, const StringC &op) {
    ONDEBUG(cerr << "AAMActiveAppearanceModelBodyC::PostDesign(), Called. \n");
    appearanceModel = apm;
 
    // initialise the matrices    
    MatrixRUTC aaTu(appearanceModel.MaskArea());
    aaTu.Fill(0);
    MatrixC aTb(appearanceModel.MaskArea(),appearanceModel.Dimensions());
    aTb.Fill(0);

    SArray1dC<MatrixC> res;
    for(DLIterC<StringC> it(fileList);it;it++) {
      if(!RavlN::Load(dir + *it,res)) {
        return false;
      }
      aaTu += res[0];
      aTb += res[1];
    }
     
    aaTu.MakeSymmetric();
    MatrixRSC aaT = aaTu.Copy();
    
    ONDEBUG(cerr << "AAMActiveAppearanceModelBodyC::PostDesign(), Solving equations.. \n");

    if(!aaT.InverseIP()) {
      cerr << "AAMActiveAppearanceModelBodyC::PostDesign(), WARNING: Covariance of input has singular values. \n";
      aaT = aaTu.PseudoInverse();
    }
    
    MatrixC A =  (aaT * aTb).T();

    VectorC offset(appearanceModel.Dimensions());
    offset.Fill(0); 
    refiner = FuncLinearC(A,offset);
    
    ONDEBUG(cerr << "\nAAMActiveAppearanceModelBodyC::PostDesign(), Done. \n");

    return true;
  }
  
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(AAMActiveAppearanceModelBodyC,AAMActiveAppearanceModelC,RCHandleVC<AAMActiveAppearanceModelBodyC>);
  
}
