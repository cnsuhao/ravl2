// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! file="Ravl/Image/Processing/Tracking/mosaic.cc"
//! lib=RavlImageProc

#include "Ravl/Option.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/Image/MosaicBuilder.hh"
#include "Ravl/Image/WarpProjective.hh"
#include "Ravl/EntryPnt.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Array2dIter3.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/IO.hh"
#include "Ravl/Image/ImgIO.hh"
#include "Ravl/Image/Erode.hh"
#include "Ravl/Image/Dilate.hh"
#include "Ravl/Image/ImageConv.hh"
#include "Ravl/Image/RealRGBValue.hh"

using namespace RavlN;
using namespace RavlImageN;

static void
 Smooth8Way(ImageC<ByteRGBValueC> &img)
{
  ByteRGBValueC pix[9];
  UIntT weight[9];
  UIntT count;
  ImageC<ByteRGBValueC> imcopy(img.Rows(),img.Cols());
  
  for(UIntT i=0; i<img.Rows(); i++)
    for(UIntT j=0; j<img.Cols(); j++) {
      count = 0;
      pix[count] = img[i][j]; weight[count++] = 4;
      if ( i != 0 ) {
	pix[count] = img[i-1][j];
	weight[count++] = 2;
	if ( j != 0 ) {
	  pix[count] = img[i-1][j-1];
	  weight[count++] = 1;
	}

	if ( j != img.Cols()-1 ) {
	  pix[count] = img[i-1][j+1];
	  weight[count++] = 1;
	}
      }

      if ( i != img.Rows()-1 ) {
	pix[count] = img[i+1][j];
	weight[count++] = 2;
	if ( j != 0 ) {
	  pix[count] = img[i+1][j-1];
	  weight[count++] = 1;
	}

	if ( j != img.Cols()-1 ) {
	  pix[count] = img[i+1][j+1];
	  weight[count++] = 1;
	}
      }

      if ( j != 0 ) {
	pix[count] = img[i][j-1];
	weight[count++] = 2;
      }

      if ( j != img.Cols()-1 ) {
	pix[count] = img[i][j+1];
	weight[count++] = 2;
      }

      UIntT total_weight=0;
      RealRGBValueC total_rgb(0,0,0);
      for(UIntT k=0; k<count; k++) {
	total_weight += weight[k];
	total_rgb.Red()   += (RealT)(weight[k]*pix[k].Red());
	total_rgb.Green() += (RealT)(weight[k]*pix[k].Green());
	total_rgb.Blue()  += (RealT)(weight[k]*pix[k].Blue());
      }

      pix[0].Red()   = (ByteT)(total_rgb.Red()/(RealT)total_weight + 0.5);
      pix[0].Green() = (ByteT)(total_rgb.Green()/(RealT)total_weight + 0.5);
      pix[0].Blue()  = (ByteT)(total_rgb.Blue()/(RealT)total_weight + 0.5);
      imcopy[i][j] = pix[0];
    }

  for(UIntT i=0; i<img.Rows(); i++)
    for(UIntT j=0; j<img.Cols(); j++)
      img[i][j] = imcopy[i][j];
}

#define ZHOMOG 100.0

  
int Mosaic(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  int newFreq    = opt.Int("nf",5,"Frequency of introducing new features. ");
  int cthreshold = opt.Int("ct",30,"Corner threshold. ");
  int cwidth     = opt.Int("cw",7,"Corner filter width. ");
  int mthreshold = opt.Int("mt",20,"Match threshold. ");
  int mwidth     = opt.Int("mw",17,"Tracker feature width. ");
  int lifeTime   = opt.Int("ml",8,"Lifetime of a point without a match in the incoming images. ");
  int searchSize = opt.Int("ss",25,"Search size. How far to look from the predicted position of the feature.");
  int borderC    = opt.Int("bc", 200, "Width of horizontal border around image");
  int borderR    = opt.Int("br", 200, "Width of vertical border around image");
  int cropT = opt.Int("crt", 0, "Width of cropping region at top of image");
  int cropB = opt.Int("crb", 0, "Width of cropping region at bottom of image");
  int cropL = opt.Int("crl", 0, "Width of cropping region at left of image");
  int cropR = opt.Int("crr", 0, "Width of cropping region at right of image");
  Point2dC pointTL = opt.Point2d("ptl", 0.0, 0.0, "Top-left coordinates of first image");
  Point2dC pointTR = opt.Point2d("ptr", 0.0, 1.0, "Top-right coordinates of first image");
  Point2dC pointBL = opt.Point2d("pbl", 1.0, 0.0, "Bottom-left coordinates of first image");
  Point2dC pointBR = opt.Point2d("pbr", 1.0, 1.0, "Bottom-right coordinates of first image");
  int maxFrames = opt.Int("mf",-1,"Maximum number of frames to process ");
  StringC ifn = opt.String("","@V4LH:/dev/video0","Input sequence. ");
  StringC ofn = opt.String("","@X","Output sequence. ");
  opt.Check();

  // Open an input stream.
  DPIPortC<ImageC<ByteRGBValueC> > inp;
  if(!OpenISequence(inp,ifn)) {
    cerr << "Failed to open input '" << ifn << "'\n";
    return 1;
  }
#if 0
  inp.SetAttr("FrameBufferSize","2");
#endif
  ImageC<ByteRGBValueC> img;
#if 0
  for(UIntT frameNo = 0;frameNo < 200;frameNo++)
    // Read an image from the input.
    if(!inp.Get(img)) {
      cerr << "Failed to read image from input '" << ifn << "'\n";
      return 1;
    }
#endif
  
  // Create a mosaic class instance
  MosaicBuilderC mosaicBuilder(cthreshold, cwidth, mthreshold, mwidth,
			       lifeTime, searchSize, newFreq,
			       borderC, borderR, ZHOMOG,
			       cropT, cropB, cropL, cropR,
			       pointTL, pointTR, pointBL, pointBR,
			       maxFrames);

  for(IntT frameNo = 0;frameNo < maxFrames;frameNo++) {
    if(!inp.Get(img))
      return 1;

    if(!mosaicBuilder.Apply(img))
      return 1;

    Save("@X:Mosaic",mosaicBuilder.GetMosaic());
  }

  ImageC<ByteRGBValueC> mosaicRGB = DPConvByteRGBMedianImageC2ByteRGBValueImageCT(mosaicBuilder.GetMosaic());

  // save constructed mosaic
  Save("/tmp/mosaic.ppm",mosaicRGB);

  // reopen input sequence
  if(!OpenISequence(inp,ifn)) {
    cerr << "Failed to open input '" << ifn << "'\n";
    return 1;
  }

#if 0
  for(UIntT frameNo = 0;frameNo < 200;frameNo++)
    // Read an image from the input.
    if(!inp.Get(img)) {
      cerr << "Failed to read image from input '" << ifn << "'\n";
      return 1;
    }
#endif
  // Open the output stream for the foreground segmentation images.
  DPOPortC<ImageC<ByteRGBValueC> > outp;
  if(!OpenOSequence(outp,ofn,"")) {
    cerr << "Failed to open output '" << ofn << "'\n";
    return 1;
  }

  // 5x5 kernel for morphological operations, with this shape:
  //  ***
  // *****
  // *****
  // *****
  //  ***
  IndexRangeC centred(-2,2);
  ImageC<bool> kernel(centred,centred);
  kernel.Fill(true);
  kernel[-2][-2] = kernel[-2][2] = kernel[2][-2] = kernel[2][2] = false;

  // compute foreground segmented image
  for(IntT frameNo = 0;frameNo < maxFrames;frameNo++) {
    // Read an image from the input.
    if(!inp.Get(img))
      break;
    img = ImageC<ByteRGBValueC>(img,mosaicBuilder.GetCropRect());

    ImageC<ByteRGBValueC> warped_img(mosaicBuilder.GetCropRect());
    WarpProjectiveC<ByteRGBValueC,ByteRGBValueC> pwarp(mosaicBuilder.GetCropRect(),mosaicBuilder.GetMotion(frameNo),1.0,ZHOMOG,true);
    pwarp.Apply(mosaicRGB,warped_img);

    // smooth both images to suppress artefacts
    for(IntT i=0; i < 3; i++) {
      Smooth8Way(img);
      Smooth8Way(warped_img);
    }

    // subtract and threshold
    ImageC<bool> mask(mosaicBuilder.GetCropRect());
    mask.Fill(false);
    for(Array2dIter3C<ByteRGBValueC,ByteRGBValueC,bool> it(img,warped_img,mask);
	it.IsElm(); it.Next()) {
      IntT diff2 = Sqr((IntT)it.Data1().Red()   - (IntT)it.Data2().Red()) +
                   Sqr((IntT)it.Data1().Green() - (IntT)it.Data2().Green()) +
	           Sqr((IntT)it.Data1().Blue()  - (IntT)it.Data2().Blue());
      if ( diff2 > 600 )
	it.Data3() = true;
    }

    // erode and dilate binary mask
    ImageC<bool> result(mosaicBuilder.GetCropRect());
    BinaryErode(mask, kernel, result);
    cout << "result.TL=(" << result.Frame().TRow() << "," << result.Frame().LCol() << ") result.BR=(" << result.Frame().BRow() << "," << result.Frame().RCol() << ")" << endl;
    BinaryDilate(result, kernel, mask);
    cout << "mask.TL=(" << mask.Frame().TRow() << "," << mask.Frame().LCol() << ") mask.BR=(" << mask.Frame().BRow() << "," << mask.Frame().RCol() << ")" << endl;
    cout << "mask.Rows()=" << mask.Rows() << " mask.Cols()=" << mask.Cols() << endl;

    ByteRGBValueC val(0,0,0);
    for(Array2dIter2C<ByteRGBValueC,bool> it(img,mask);
	it.IsElm(); it.Next()) {
      if ( !it.Data2() )
	it.Data1() = val;
    }

    // Write an image out.
    outp.Put(img);
  }

  cout << "Output finished" << endl;
  return 0;
}

RAVL_ENTRY_POINT(Mosaic)
