// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=LMSMotion
//
// Descripton:    Program calculates optical flow from pair of input images
//
// Synopsis:
//    exLMSOptic image1 image2 [-o op_file_prefix] [-i region_size]
//
// For each pixel, the optic flow is calculated over a square neighbourhood of
// size "region_size" (default = 9 pixels).  The optional PostScript output
// file plots the motion vectors and corresponding covariance matrix ellipses
// over the first image.  The ppm output file option plots the motion as a
// colour overlay.

#include "Ravl/Option.hh"
#include "Ravl/EntryPnt.hh"
#include "Ravl/DP/FileFormatIO.hh"
#include "Ravl/Stream.hh"
#include "Ravl/Pair.hh"
#include "Ravl/Motion/LMSOpticFlow.hh"
#include "Ravl/Image/ConvolveSeparable2d.hh"
#include "Ravl/Image/GaussConvolve.hh"
#include "Ravl/Image/SpatialDifference.hh"

using namespace RavlN;
using namespace RavlImageN;

int exLMSOptic(int argc, char **argv) 
{
  // process command-line parameters
  OptionC opt(argc, argv);
  StringC opFileName = opt.String("o", "", "Output file name prefix");
  StringC opDisplay = opt.String("oi", "@X", "Output file name prefix");
  IntT windowSize  = opt.Int("w", 9, "Window size");
  IntT order       = opt.Int("g", 5, "Set Gaussian antialias filter order (default is Remex 2:1 antialias)");
  IntT diffOrder   = opt.Int("d", 1, "Spatial gradient difference order");
  RealT noise      = opt.Real("n", 1.0, "Noise s.d. estimate for filtered image");
  IntT scale       = opt.Int("s", 1, "Scale factor for arrow on Postscript plot");
  RealT subsample  = opt.Real("S", 5, "Vector subsample factor");
  bool forward_diff  = opt.Boolean("F", false, "Forward diff instead of average diff for spatial gradient");
  StringC ImageFileName1 = opt.String("", "", "Input image 1");
  StringC ImageFileName2 = opt.String("", "", "Input image 2");
  opt.CompulsoryArgs(2);
  opt.Check();
  
  // load 2 images from sequence
  
  PairC<ImageC<RealT> > image, filtered;
  
  if(!Load(ImageFileName1, image[0])) {
    cerr << "Failed to load image '" << ImageFileName1 << "'\n";
    return 1;
  }
  if(!Load(ImageFileName2, image[1])) {    
    cerr << "Failed to load image '" << ImageFileName2 << "'\n";
    return 1;
  }
  
  // filter images with antialias filter
  
  if (opt.IsOnCommandLine("g") || 1) {
    GaussConvolveC<RealT> filter(order);
    for (UIntT i=0; i<=1; ++i) 
      filtered[i] = filter.Apply(image[i]);
  } else {
#if 0
    Array1dC<RealT> coeffs;
    IStrStreamC ("-2 2 0.308037 0.246545 0.114345 0.0105584 -0.0254667") >> coeffs;
    ConvolveSeparable2dC<RealT> filter(coeffs, coeffs);
    for (UIntT i=0; i<=1; ++i) 
      filtered[i] = filter.Apply(image[i]);
#endif
  }
  
  // compute image gradients:
  //   - temporal
  ImageC<RealT>  dt = (filtered[1]-filtered[0]); 
  
  //   - and spatial
  ImageC<RealT> centre ((forward_diff) ? ((ImageC<RealT> &) filtered[0]) : ImageC<RealT>((filtered[0] + filtered[1]) / 2.0));  
  ImageC<Vector2dC> grad;
  SpatialDifference(diffOrder,centre,grad);
  
  // compute motion
  LMSOpticFlowC motion(true);
  motion.SetNoiseLevel(noise);
  motion.SetRegionSize(windowSize);
  motion.Estimate(grad, dt);
  
  ImageC<ByteYUVValueC> img;
  motion.DrawMotion(image[0],img);
  if(!opDisplay.IsEmpty())
    Save(opDisplay,img);
  //cout << motion.Eigenvalues()<<'\n';
  if(!opFileName.IsEmpty())
    OStreamC (opFileName) << motion.Motion() << '\n';
  return 0;
}

RAVL_ENTRY_POINT(exLMSOptic);
