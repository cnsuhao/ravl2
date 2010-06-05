// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: DesignBayesNormalQuadratic.cc 3563 2003-10-17 12:33:18Z jonstarck $"
//! lib=RavlPatternRec
//! author="Kieron Messer"
//! file="Ravl/PatternRec/Classify/DesignBayesNormalQuadratic.cc"

#include "Ravl/PatternRec/DesignBayesNormalQuadratic.hh"
#include "Ravl/PatternRec/SampleVector.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/PatternRec/ClassifierBayesNormalQuadratic.hh"
#include "Ravl/MatrixRUT.hh"
#include "Ravl/MatrixRS.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/VirtualConstructor.hh"
#include  "Ravl/PatternRec/DataSetVectorLabel.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/SArray1dIter2.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Create least squares designer.
  
  DesignBayesNormalQuadraticBodyC::DesignBayesNormalQuadraticBodyC(const SArray1dC<RealT> & p) 
    : priors(p)
  {
    equalPriors=false;
  }

  DesignBayesNormalQuadraticBodyC::DesignBayesNormalQuadraticBodyC(bool equalP) 
    : equalPriors(equalP)
  {
  }

  
  //: Load from stream.
  
  DesignBayesNormalQuadraticBodyC::DesignBayesNormalQuadraticBodyC(istream &strm)
    : DesignClassifierSupervisedBodyC(strm)
  {
    int ver;
    strm >> ver;
    if(ver != 1)
      cerr << "DesignBayesNormalQuadraticBodyC::DesignBayesNormalQuadraticBodyC(), Unknown format version. \n";
    strm >> priors;
  }
  
  //: Load from binary stream.
  
  DesignBayesNormalQuadraticBodyC::DesignBayesNormalQuadraticBodyC(BinIStreamC &strm)
    : DesignClassifierSupervisedBodyC(strm)
  {
    char ver;
    strm >> ver;
    if(ver != 1)
      cerr << "DesignBayesNormalQuadraticBodyC::DesignBayesNormalQuadraticBodyC(), Unknown format version. \n";
    strm >> priors;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignBayesNormalQuadraticBodyC::Save (ostream &out) const {
    if(!DesignClassifierSupervisedBodyC::Save(out))
      return false;
    char ver = 1;
    out << ((int) ver) << ' ' << priors;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignBayesNormalQuadraticBodyC::Save (BinOStreamC &out) const {
    if(!DesignClassifierSupervisedBodyC::Save(out))
      return false;
    char ver = 1;
    out << ((int) ver) << priors;
    return true;
  }
  
  //: Create new function.C
  
  //: Create function from the given data.
  ClassifierC DesignBayesNormalQuadraticBodyC::Apply(const SampleC<VectorC> &in, const SampleC<UIntT> &out) {
    ONDEBUG(cerr << "DesignBayesNormalQuadraticBodyC::Apply(), Computing coefficients.. \n");
    DataSetVectorLabelC dset(in, out);
    SArray1dC<UIntT>nums = dset.ClassNums();
    if(equalPriors) {
      priors = SArray1dC<RealT>(nums.Size());
      for(SArray1dIterC<RealT>it(priors);it;it++) it.Data1() = 1.0/(RealT)nums.Size();      
    } else if ((!equalPriors) && (priors.Size()<1)) {
      priors = SArray1dC<RealT>(nums.Size());
      RealT tot = (RealT)dset.Size();
      for(SArray1dIter2C<RealT, UIntT>it(priors, nums);it;it++) it.Data1() = (RealT)it.Data2()/tot;
    } else {
      if(priors.Size()!=nums.Size()) 
	RavlIssueError("User set priors not same size as the number of classes");
    }
    ClassifierBayesNormalQuadraticC func(dset.ClassStats(), priors);
    return func;
  }
  
 
  ////////////////////////////////////////////////////////////////////////
  
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(DesignBayesNormalQuadraticBodyC,DesignBayesNormalQuadraticC,DesignClassifierSupervisedC);
  
}
