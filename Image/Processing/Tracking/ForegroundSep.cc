// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImageProc
//! file="Ravl/Image/Processing/Tracking/ForegroundSep.cc"

#include "Ravl/Image/ForegroundSep.hh"
#include "Ravl/Image/ImageConv.hh"
#include "Ravl/Image/WarpProjective.hh"
#include "Ravl/Image/GaussConvolve.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Array2dIter3.hh"
#include "Ravl/Image/Erode.hh"
#include "Ravl/Image/Dilate.hh"
#include "Ravl/IO.hh"
#include "Ravl/Image/ImgIO.hh"
#include "Ravl/Image/RealRGBValue.hh"

namespace RavlImageN {
  using namespace RavlN;
  
  ForegroundSepC::ForegroundSepC(const ImageC<ByteRGBValueC>& nmosaic, RealT nmosaicZHomog, RealT nimageZHomog, int nfgThreshold) 
    : mosaic(nmosaic), mosaicZHomog(nmosaicZHomog), imageZHomog(nimageZHomog),
      matcher(RGBImageCT2ByteImageCT(mosaic), 0, 0, 0, 0,
	      17, 25, 20, mosaicZHomog, imageZHomog),
      fgThreshold(nfgThreshold)
{
  // 5x5 kernel for morphological operations, with this shape:
  //  ***
  // *****
  // *****
  // *****
  //  ***
  IndexRangeC centred(-2,2);
  kernel = ImageC<bool>(centred,centred);
  kernel.Fill(true);
  kernel[-2][-2] = kernel[-2][2] = kernel[2][-2] = kernel[2][2] = false;

}
  
  
  //: Set binary mask to exclude regions from tracker
  bool ForegroundSepC::SetMask(const StringC& fileName) {
    if (!Load(fileName, mask)) {
      cerr << "Failed to load file: " << fileName << endl;
      return false;
    }
    return true;
  }
  
  
  ImageC<ByteRGBValueC> ForegroundSepC::Apply(const ImageC<ByteRGBValueC>& img, const Matrix3dC& homog) {
    // match image to mosaic and update the motion "proj"
    Projection2dC proj(homog,imageZHomog,mosaicZHomog);
    if(!matcher.Apply(RGBImageCT2ByteImageCT(img), proj)) {
      cerr << "Couldn't match image" << endl;
      return ImageC<ByteRGBValueC>();
    }
    // warp mosaic onto image
    ImageC<ByteRGBValueC> warped_img(img.Rectangle());
    WarpProjectiveC<ByteRGBValueC,ByteRGBValueC> pwarp(img.Rectangle(),proj);
    pwarp.Apply(mosaic,warped_img);
    
    // smooth both images to suppress artefacts
    GaussConvolveC<ByteRGBValueC, ByteRGBValueC, RealT, RealRGBValueC> lpf(7);
    ImageC<ByteRGBValueC> fg = lpf.Apply(img);
    warped_img = lpf.Apply(warped_img);
    
    // subtract and threshold
    ImageC<bool> outmask(img.Rectangle());
    for (Array2dIter3C<ByteRGBValueC,ByteRGBValueC,bool>
	   it(fg,warped_img,outmask,fg.Rectangle()); it.IsElm(); it.Next()) {
      IntT diff2 = 
	Sqr((IntT)it.Data1().Red()   - (IntT)it.Data2().Red()) +
	Sqr((IntT)it.Data1().Green() - (IntT)it.Data2().Green()) +
	Sqr((IntT)it.Data1().Blue()  - (IntT)it.Data2().Blue());
      it.Data3() = (diff2 > fgThreshold*fgThreshold);
    }
    
    // exclude pixels from graphics mask (if used)
    if (mask.Rectangle().Contains(outmask.Rectangle())) {
      // (will be true if mask has been used)
      for (Array2dIter2C<bool,bool> it(mask,outmask,outmask.Rectangle());
	   it.IsElm(); it.Next()) {
	it.Data2() &= it.Data1();
      }
    }
    
    // erode and dilate binary mask
    ImageC<bool> result;
    BinaryErode(outmask, kernel, result);
    BinaryDilate(result, kernel, outmask);
    // blank out background pixels
    ByteRGBValueC black(0,0,0);
    for(Array2dIter2C<ByteRGBValueC,bool> it(fg,outmask,fg.Rectangle());
	it.IsElm(); it.Next()) {
      if ( !it.Data2() ) it.Data1() = black;
    }
    return fg;
  }
}
