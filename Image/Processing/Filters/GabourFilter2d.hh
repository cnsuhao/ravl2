// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_GABOURFILTER_HEADER
#define RAVLIMAGE_GABOURFILTER_HEADER 1
////////////////////////////////////////////////////////////////////////////
//! docentry="Ravl.Images.Filtering"
//! rcsid="$Id$"
//! author="Kieron Messer"
//! date="17/10/2000"
//! lib=RavlImageProc
//! example=exGabourFilter.cc
//! file="Ravl/Image/Processing/Filters/GabourFilter2d.hh"

#warning "Use classes GaborFilter... instead"
#include "Ravl/Array1d.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/SArray2dIter2.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/FFT2d.hh"
#include "Ravl/RefCounter.hh"

namespace RavlImageN {
  
  //! userlevel=Deprecated
  //: Gabour filters.
  
  class GabourFilterBank2dBodyC 
    : public RCBodyC
  {
  public:
    GabourFilterBank2dBodyC(Index2dC size);
    //: Constructor.
    // Uses default filter bank: <br>
    // Angles = 0.0, 45.0, 90.0, 135.0 <br>
    // Scales = 0.125, 0.35 
    
    GabourFilterBank2dBodyC(const SArray1dC<RealT> &angles,const SArray1dC<RealT> &scales,Index2dC size = Index2dC(0,0));
    //: Constructor.
    
    GabourFilterBank2dBodyC();
    //: Constructor.
    
    Array1dC<ImageC<RealT> > &Filters()
    { return filter; }
    //: Access filters.
    
    void SetupFilters(Index2dC imgSize);
    //: Setup filters for given image size.
    
    SArray1dC<ImageC<RealT> > Apply(const ImageC<RealT> &rim);
    //: Apply filters to a real image.
    
    void ConvToReal(const ImageC<RealT> &im,ImageC<RealT> &rim)
    { rim = im; }
    //: Image converter.
    
    template<typename PixelT>
    void ConvToReal(const ImageC<PixelT> &im,ImageC<RealT> &rim) { 
      rim = ImageC<RealT>(im.Size());
      for(SArray2dIter2C<RealT,PixelT> it(rim,im);it;it++)
	it.Data1() = it.Data2();
    }
    //: Image converter.
    
    const SArray1dC<RealT> &Angles() const
    { return angleArr; }
    //: Access filter angles.
    
    const SArray1dC<RealT> &Scales() const
    { return angleArr; }
    //: Access filter scales.
    
    void Angles(const SArray1dC<RealT> &angles)  { 
      angleArr = angles; 
      filterSize = Index2dC(0,0);
    }
    //: Access filter angles.
    
    void Scales(const SArray1dC<RealT> &scales) { 
      scaleArr = scales; 
      filterSize = Index2dC(0,0);
    }
    //: Access filter scales.
    
  protected:
    void MakeGabourFilters(int ymax, int xmax);
    //: Generate gabour filters.
    
    Array1dC<ImageC<RealT> > filter;
    //: the filters for the given parameters
    
    Index2dC filterSize;
    
    SArray1dC<RealT> angleArr;
    SArray1dC<RealT> scaleArr;
    
    
    FFT2dC forward;
    FFT2dC backward;

  };

  //! userlevel=Deprecated
  //: Gabour filters.
  
  class GabourFilterBank2dC 
    : public RCHandleC<GabourFilterBank2dBodyC>
  {
  public:
    GabourFilterBank2dC(Index2dC size)
      : RCHandleC<GabourFilterBank2dBodyC>(*new GabourFilterBank2dBodyC(size))
    {}
    //: Constructor.
    
    GabourFilterBank2dC(const SArray1dC<RealT> &angles,const SArray1dC<RealT> &scales,Index2dC size = Index2dC(0,0))
      : RCHandleC<GabourFilterBank2dBodyC>(*new GabourFilterBank2dBodyC(angles,scales,size))
    {}
    //: Constructor.
    
  protected:
    GabourFilterBank2dC(GabourFilterBank2dBodyC &bod)
      : RCHandleC<GabourFilterBank2dBodyC>(bod)
    {}
    //: Body constructor
    
    GabourFilterBank2dBodyC &Body()
    { return RCHandleC<GabourFilterBank2dBodyC>::Body(); }
    //: Access body.
    
    const GabourFilterBank2dBodyC &Body() const
    { return RCHandleC<GabourFilterBank2dBodyC>::Body(); }
    //: Access body.
    
  public:
    Array1dC<ImageC<RealT> > &Filters()
    { return Body().Filters(); }
    //: Access filters.
    
    const SArray1dC<RealT> &Angles() const
    { return Body().Angles(); }
    //: Access filter angles.
    
    const SArray1dC<RealT> &Scales() const
    { return Body().Scales(); }
    //: Access filter scales.
    
    void Angles(const SArray1dC<RealT> &angles)
    { Body().Angles(angles); }
    //: Access filter angles.
    
    void Scales(const SArray1dC<RealT> &scales) 
    { Body().Scales(scales); }
    //: Access filter scales.
    
  };
  
  //! userlevel=Deprecated
  //: Body class for computing set of Gabor filters
  //
  // You should not use this class directly, but rather the handle class
  // GaborFilter2dC.
  //
  
  template <class PixelT>
  class GaborFilter2dBodyC
    : public GabourFilterBank2dBodyC
  {
  public:
    GaborFilter2dBodyC();
    //: Default constructor
    
    GaborFilter2dBodyC(Index2dC size)
      : GabourFilterBank2dBodyC(size)
    {}
    //: Constructor with image size.
    // Uses default filter bank: <br>
    // Angles = 0.0, 45.0, 90.0, 135.0 <br>
    // Scales = 0.125, 0.35 

    GaborFilter2dBodyC(Index2dC size,const SArray1dC<RealT> &angles,const SArray1dC<RealT> &scales)
      : GabourFilterBank2dC(size,angles,scales)
    {}
    //: Constructor
    
    SArray1dC<ImageC<RealT> > Apply (const ImageC<PixelT> &im)   {
      ImageC<RealT> rim;
      ConvToReal(im,rim); // At some point this we will do fft from native image type.
      return GabourFilterBank2dBodyC::Apply(rim);    
    }    
    //: Apply Gabour filters to image 'im'.
    
  };
  
  ///////////////////////////////////////////////////


  // --------------------------------------------------------------------------
  // **********  IPGaborC  ********************************************
  // --------------------------------------------------------------------------

  //! userlevel=Deprecated
  //: Compute Gabor feature images
  
  template <class PixelT>
  class GabourFilter2dC
    : public GabourFilterBank2dC
  {
  public:
    GabourFilter2dC()
      : GabourFilterBank2dC(*new GaborFilter2dBodyC<PixelT>())
    {}
    //: Constructor 
    // Uses default filter bank: <br>
    // Angles = 0.0, 45.0, 90.0, 135.0 <br>
    // Scales = 0.125, 0.35 
    
    GabourFilter2dC(Index2dC size)
      : GabourFilterBank2dC(*new GaborFilter2dBodyC<PixelT>(size))
    {}
    //: Constructor 
    // Uses default filter bank: <br>
    // Angles = 0.0, 45.0, 90.0, 135.0 <br>
    // Scales = 0.125, 0.35 
    
    GabourFilter2dC(const SArray1dC<RealT> &angles,const SArray1dC<RealT> &scales,Index2dC size = Index2dC(0,0))
      : GabourFilterBank2dC(*new GaborFilter2dBodyC<PixelT>(angles,scales,size))      
    {}
    //: Constructor.
    
  protected:
    GaborFilter2dBodyC<PixelT> &Body()
    { return static_cast<GaborFilter2dBodyC<PixelT> &>(GabourFilterBank2dC::Body()); }
    //: Access body.

    const GaborFilter2dBodyC<PixelT> &Body() const
    { return static_cast<const GaborFilter2dBodyC<PixelT> &>(GabourFilterBank2dC::Body()); }
    //: Access body.
    
  public:
    SArray1dC<ImageC<RealT> > Apply (const ImageC<PixelT> &im)
    { return Body().Apply(im); }
    //: Apply Gabour filters to im.
    
  };
  
}


#endif
