// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImage
//! author="Charles Galambos"

#include "Ravl/Image/HomomorphicFilter.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Math.hh"


namespace RavlImageN {
#ifdef __sgi__
  template SArray2dC<double>;
#endif
  

  //: Constructor.
  
  HomomorphicFilterBodyC::HomomorphicFilterBodyC(RealT nSigma,RealT nDepth,const Index2dC &size) 
    : sigma(nSigma),
      depth(nDepth)
  {
    if(size != Index2dC(0,0))
      Init(size);
  }
  
  //: Setup the filter.
  
  bool HomomorphicFilterBodyC::Init(const Index2dC &size) 
  {
    fwd = FFT2dC(size,false);
    bkw = FFT2dC(size,true);
    filter = ImageC<RealT>(size[0],size[1]);
    Index2dC v(0,0);
    RealT sp = (sigma * RavlConstN::sqrt2Pi);
    RealT mod = depth * sp;
    for(Array2dIterC<RealT> it(filter);it;it++) {
      Index2dC at = it.Index();
      RealT dist = Sqrt(at.SqrEuclidDistance(v));
      RealT g = Exp(-0.5 * Sqr(dist/sigma)) / sp;
      *it = 1 - g * mod;
      //cerr << "Index=" << at << " Val=" << *it << "\n";
    }
    return true;
  }
  
  
  ImageC<RealT> HomomorphicFilterBodyC::Apply(const ImageC<RealT> &img) {
    ImageC<RealT> ret(img.Frame());
    Index2dC size(img.Frame().Range1().Size(),img.Frame().Range2().Size());
    if(!fwd.IsValid())
      Init(size);
    else {
      if(fwd.Size() != size)
	Init(size);
    }
    for(Array2dIter2C<RealT,RealT> it(ret,img);it;it++)
      it.Data1() = Log(it.Data2() + 1);
    SArray2dC<RealT> sret(ret.SArray2d(true));
    SArray2dC<ComplexC> fdom = fwd.Apply(sret);
    for(Array2dIter2C<ComplexC,RealT> fit(fdom,filter);fit;fit++)
      fit.Data1() *= fit.Data2();
    SArray2dC<ComplexC> result = bkw.Apply(fdom);
    for(Array2dIter2C<ComplexC,RealT> rit(result,ret);rit;rit++)
      rit.Data2() = Exp(rit.Data1().Mag()) - 1;
    return ret;
  }

}
