// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_HOMOMORPHICFILTER_HEADER
#define RAVLIMAGE_HOMOMORPHICFILTER_HEADER 1
//! userlevel=Normal
//! author="Charles Galambos"
//! docentry="Ravl.Images.Filtering"
//! rcsid="$Id$"
//! lib=RavlImageProc
//! file="Ravl/Image/Processing/Filters/HomomorphicFilter.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/FFT2d.hh"

namespace RavlImageN {
  
  //! userlevel=Develop
  //: Homomorphic filter
  
  class HomomorphicFilterBodyC 
    : public RCBodyC
  {
  public:
    HomomorphicFilterBodyC(RealT nSigma = 10,RealT nDepth = 0.5,const Index2dC &size = Index2dC(0,0));
    //: Constructor.
    
    ImageC<RealT> Apply(const ImageC<RealT> &img);
    //: Apply filter to image.
    
  protected:
    bool Init(const  Index2dC &size);
    //: Setup the filter.
    
    RealT sigma;
    RealT depth;
    FFT2dC fwd; // Forward FFT.
    ImageC<RealT> filter;
    FFT2dC bkw; // Backward FFT.
  };
  
  //! userlevel=Normal
  //: Homomorphic filter
  
  class HomomorphicFilterC 
    : public RCHandleC<HomomorphicFilterBodyC>
  {
  public:
    HomomorphicFilterC()
    {}
    //: Default constructor.
    
    HomomorphicFilterC(RealT sigma,RealT depth = 0.5,const Index2dC &size = Index2dC(0,0))
      : RCHandleC<HomomorphicFilterBodyC>(*new HomomorphicFilterBodyC(sigma,depth,size))
    {}
    //: Constructor.
    // depth controls the strength of the effect of the filter on the image 
    // from 0 with no effect to 1 complete removal of some components.
    // sigma controls the width of the filter.
    
    ImageC<RealT> Apply(const ImageC<RealT> &img)
    { return Body().Apply(img); }
    //: Apply filter to image.
    
    
  };
}

#endif
