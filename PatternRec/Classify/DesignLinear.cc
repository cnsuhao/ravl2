// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Charles Galambos"
//! file="Ravl/PatternRec/Modeling/Basic/DesignLinear.cc"

#include "Ravl/PatternRec/DesignLinear.hh"
#include "Ravl/PatternRec/SampleVector.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/PatternRec/ClassifierLinear.hh"
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
  
  DesignLinearBodyC::DesignLinearBodyC(const SArray1dC<RealT> & p) 
    : priors(p)
  {
  }

  DesignLinearBodyC::DesignLinearBodyC(bool equalPriors) 
    : priors(1)
  {
   if(equalPriors) priors[0]  = -1.0;
   else priors[0] = -2.0;
  }

  
  //: Load from stream.
  
  DesignLinearBodyC::DesignLinearBodyC(istream &strm)
    : DesignClassifierSupervisedBodyC(strm)
  {
    int ver;
    strm >> ver;
    if(ver != 1)
      cerr << "DesignLinearBodyC::DesignLinearBodyC(), Unknown format version. \n";
    strm >> priors;
  }
  
  //: Load from binary stream.
  
  DesignLinearBodyC::DesignLinearBodyC(BinIStreamC &strm)
    : DesignClassifierSupervisedBodyC(strm)
  {
    char ver;
    strm >> ver;
    if(ver != 1)
      cerr << "DesignLinearBodyC::DesignLinearBodyC(), Unknown format version. \n";
    strm >> priors;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignLinearBodyC::Save (ostream &out) const {
    if(!DesignLinearBodyC::Save(out))
      return false;
    char ver = 1;
    out << ((int) ver) << ' ' << priors;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignLinearBodyC::Save (BinOStreamC &out) const {
    if(!DesignLinearBodyC::Save(out))
      return false;
    char ver = 1;
    out << ((int) ver) << priors;
    return true;
  }
  
  //: Create new function.C
  
  //: Create function from the given data.
  ClassifierC DesignLinearBodyC::Apply(const SampleC<VectorC> &in, const SampleC<UIntT> &out) {
    ONDEBUG(cerr << "DesignLinearBodyC::Apply(), Computing coefficients.. \n");
    DataSetVectorLabelC dset(in, out);
    SArray1dC<UIntT>nums = dset.ClassNums();
    if(priors[0] == -1.0) {
      priors = SArray1dC<RealT>(nums.Size());
      for(SArray1dIterC<RealT>it(priors);it;it++) it.Data1() = 1.0/(RealT)nums.Size();      
    } else if (priors[0] == -2.0) {
      priors = SArray1dC<RealT>(nums.Size());
      RealT tot = (RealT)dset.Size();
      for(SArray1dIter2C<RealT, UIntT>it(priors, nums);it;it++) it.Data1() = (RealT)it.Data2()/tot;
    }
    cout << priors << endl;
    ClassifierLinearC func(dset.ClassMeans(), dset.WithinClassScatter(), priors);
    return func;
  }
  
 
  ////////////////////////////////////////////////////////////////////////
  
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(DesignLinearBodyC,DesignLinearC,DesignClassifierSupervisedC);
  
}
