// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! file="Ravl/Image/Processing/Tracking/mosaic.cc"
//! author="Phil McLauchlan"
//! lib=RavlImageProc
//! docentry="Ravl.Applications.Mosaic.mosaic"
//! userlevel=Normal

#include "Ravl/Option.hh"
#include "Ravl/StdConst.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/Image/MosaicBuilder.hh"
#include "Ravl/Image/WarpProjective.hh"
#include "Ravl/Image/RemoveDistortion.hh"
#include "Ravl/Image/ImageMatcher.hh"
#include "Ravl/EntryPnt.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Array2dIter3.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/IO.hh"
#include "Ravl/Image/ImgIO.hh"
#include "Ravl/Image/Erode.hh"
#include "Ravl/Image/Dilate.hh"
#include "Ravl/Image/ImageConv.hh"
#include "Ravl/Image/RealRGBValue.hh"
#include "Ravl/Image/GaussConvolve.hh"

using namespace RavlN;
using namespace RavlImageN;


#define IMAGE_ZHOMOG 100.0
#define MOSAIC_ZHOMOG 1.0

  
int Mosaic(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  opt.Comment("Creates mosaic image from video sequence, and generates sequence of foreground images based on difference between input images and mosaic.\n");
  opt.Comment("Preprocessing:");
  int cropT = opt.Int("crt", 0, "Width of cropping region at top of image");
  int cropB = opt.Int("crb", 0, "Width of cropping region at bottom of image");
  int cropL = opt.Int("crl", 0, "Width of cropping region at left of image");
  int cropR = opt.Int("crr", 0, "Width of cropping region at right of image");
  opt.Comment("Camera details:");
  RealT cx_ratio = opt.Real("cx",0.5,"Image centre x coordinate as ratio of image width. ");
  RealT cy_ratio = opt.Real("cy",0.5,"Image centre y coordinate as ratio of image height. ");
  RealT fx = opt.Real("fx",1.0,"Focal distance in vertical pixels. ");
  RealT fy = opt.Real("fy",1.0,"Focal distance in horizontal pixels. ");
  RealT K1 = opt.Real("K1",0.0,"Cubic radial distortion coefficient. ");
  RealT K2 = opt.Real("K2",0.0,"Quintic radial distortion coefficient. ");
  opt.Comment("Tracking:");
  int newFreq    = opt.Int("nf",5,"Frequency of introducing new features. ");
  int cthreshold = opt.Int("ct",30,"Corner threshold. ");
  int cwidth     = opt.Int("cw",7,"Corner filter width. ");
  int mthreshold = opt.Int("mt",20,"Match threshold. ");
  int mwidth     = opt.Int("mw",17,"Tracker feature width. ");
  int lifeTime   = opt.Int("ml",8,"Lifetime of a point without a match in the incoming images. ");
  int searchSize = opt.Int("ss",25,"Search size. How far to look from the predicted position of the feature.");
  opt.Comment("Mosaic:");
  int borderC    = opt.Int("bc", 200, "Width of horizontal border around initial mosaic image");
  int borderR    = opt.Int("br", 200, "Width of vertical border around initial mosaic image");
  Point2dC pointTL = opt.Point2d("ptl", 0.0, 0.0, "Top-left coordinates of projection of first image");
  Point2dC pointTR = opt.Point2d("ptr", 0.0, 1.0, "Top-right coordinates of projection of first image");
  Point2dC pointBL = opt.Point2d("pbl", 1.0, 0.0, "Bottom-left coordinates of projection of first image");
  Point2dC pointBR = opt.Point2d("pbr", 1.0, 1.0, "Bottom-right coordinates of projection of first image");
  StringC mosaicFile = opt.String("mo", "/tmp/mosaic.ppm", "Output file for mosaic");
  StringC homogFile = opt.String("hf", "", "Output file for interframe projections used to construct mosaic (default: no output)");
  opt.Comment("Foreground image generation:");
  bool noForeground = opt.Boolean("nofg", false, "Suppress foreground image generation");
  int fgThreshold = opt.Int("ft",24,"Minimum distance between image and mosaic pixel values to be a foreground pixel");
  opt.Comment("Input and output video:");
  int maxFrames = opt.Int("mf",200,"Maximum number of frames to process");
  StringC ifn = opt.String("","@V4LH:/dev/video0","Input sequence. ");
  StringC ofn = opt.String("","@X","Output sequence. ");
  opt.Check();
  if (maxFrames < 0) maxFrames = 200;  // a hack; currently program fails if default is used.

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
  
  // Create a mosaic class instance
  MosaicBuilderC mosaicBuilder(cthreshold, cwidth, mthreshold, mwidth,
			       lifeTime, searchSize, newFreq,
			       borderC, borderR, IMAGE_ZHOMOG,
			       cropT, cropB, cropL, cropR,
			       pointTL, pointTR, pointBL, pointBR,
			       maxFrames);

  // declare distortion correction object
  RemoveDistortionC<ByteRGBValueC,ByteRGBValueC> distortionRemover;
  ImageC<ByteRGBValueC> linearImg;

  for(IntT frameNo = 0;frameNo < maxFrames;frameNo++) {
    if(!inp.Get(img))
      break;
    cout << "Tracking frame " << frameNo << endl;

    if(K1 == 0.0 && K2 == 0.0) {
      // no distortion, so build mosaic from original images
      if(!mosaicBuilder.Apply(img))
	return 1;
    }
    else {
      if(frameNo==0) {
	// create distortion correction object at the first frame
	distortionRemover = RemoveDistortionC<ByteRGBValueC,ByteRGBValueC>(
						cx_ratio*(RealT)img.Rows(),
						cy_ratio*(RealT)img.Cols(),
						fx, fy, K1, K2);
	
	// create linear camera image at first frame
	linearImg = img.Copy();
      }

      // apply distortion correction
      distortionRemover.Apply(img,linearImg);
      if(!mosaicBuilder.Apply(linearImg))
	return 1;
    }

#if 0
    Save("@X:Mosaic",mosaicBuilder.GetMosaic());
#endif
  }

  ImageC<ByteRGBValueC> mosaicRGB = ByteRGBMedianImageC2ByteRGBImageCT(mosaicBuilder.GetMosaic());

  // save constructed mosaic
  Save(mosaicFile,mosaicRGB);

  // save interframe projections if required
  if (homogFile != "") {
    OStreamC homogStream(homogFile);
    homogStream<<mosaicBuilder.GetMotion() << mosaicBuilder.GetCropRect() << endl;
    homogStream.Close();
  }

  if (noForeground) return 0;

  // reopen input sequence
  if(!OpenISequence(inp,ifn)) {
    cerr << "Failed to open input '" << ifn << "'\n";
    return 1;
  }

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

  // first motion estimate for registration with the mosaic
  Projection2dC proj(mosaicBuilder.GetMotion(0),IMAGE_ZHOMOG,MOSAIC_ZHOMOG);

  // convert mosaic to grey level
  ImageC<ByteT> mosaicGrey = RGBImageCT2ByteImageCT(mosaicRGB);

  // set up image matcher, used to improve estimate of homography
  ImageMatcherC matcher(mosaicGrey, cropT, cropB, cropL, cropR,
			17, 25, 20, MOSAIC_ZHOMOG, IMAGE_ZHOMOG );

  // compute foreground segmented image
  for(IntT frameNo = 0;frameNo < maxFrames;frameNo++) {
    // Read an image from the input.
    if(!inp.Get(img))
      break;
    cout << "Projection for frame " << frameNo << endl;

    // convert image to grey level
    ImageC<ByteT> imgGrey = RGBImageCT2ByteImageCT(img);

    // match image to mosaic and update the motion
    if(!matcher.Apply(imgGrey, proj))
      continue;

    Matrix3dC P = mosaicBuilder.GetMotion(frameNo).Inverse();
    P /= P[2][2];

    cout << "Mosaic: (" << P[0][0] << " " << P[0][1] << " " << P[0][2] << ")" << endl;
    cout << "        (" << P[1][0] << " " << P[1][1] << " " << P[1][2] << ")" << endl;
    cout << "        (" << P[2][0] << " " << P[2][1] << " " << P[2][2] << ")" << endl;

    // crop image to ensure it fits withing mosaic
    img = ImageC<ByteRGBValueC>(img,mosaicBuilder.GetCropRect()).Copy();
    // (The .Copy() is a temporary fix to get round DPOPort / @X bug 

    // warp mosaic onto image
    ImageC<ByteRGBValueC> warped_img(mosaicBuilder.GetCropRect());
    WarpProjectiveC<ByteRGBValueC,ByteRGBValueC> pwarp(mosaicBuilder.GetCropRect(),proj.Matrix(),MOSAIC_ZHOMOG,IMAGE_ZHOMOG,true);
    pwarp.Apply(mosaicRGB,warped_img);

    // smooth both images to suppress artefacts
    GaussConvolveC<ByteRGBValueC, ByteRGBValueC, RealT, RealRGBValueC> lpf(7);
    img = lpf.Apply(img);
    warped_img = lpf.Apply(warped_img);



    // subtract and threshold
    ImageC<bool> mask(mosaicBuilder.GetCropRect());
    mask.Fill(false);
    for(Array2dIter3C<ByteRGBValueC,ByteRGBValueC,bool> it(img,warped_img,mask,false);
	it.IsElm(); it.Next()) {
      IntT diff2 = Sqr((IntT)it.Data1().Red()   - (IntT)it.Data2().Red()) +
                   Sqr((IntT)it.Data1().Green() - (IntT)it.Data2().Green()) +
	           Sqr((IntT)it.Data1().Blue()  - (IntT)it.Data2().Blue());
      if ( diff2 > fgThreshold*fgThreshold )
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
    for(Array2dIter2C<ByteRGBValueC,bool> it(img,mask,false);
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
