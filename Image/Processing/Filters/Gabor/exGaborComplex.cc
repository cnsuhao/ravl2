// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! docentry="Ravl.API.Images.Filtering"
//! userlevel=Normal
//! rcsid="$Id: exGaborFilter.cc 5240 2005-12-06 17:16:50Z plugger $"
//! lib=RavlImageProc
//! author="Charles Galambos"
//! file="Ravl/Image/Processing/Filters/exGaborComplex.cc"

#include "Ravl/Image/GaborComplex.hh"
#include "Ravl/Array2d.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/IO.hh"
#include "Ravl/Option.hh"
#include "Ravl/FFT2d.hh"

using namespace RavlN;
using namespace RavlImageN;

int main(int argc, char* argv[]) {

  OptionC opt(argc, argv);
  IntT ntheta      = opt.Int ("t", 6,   "no. of angles");
  IntT nscale      = opt.Int ("s", 3,   "no. of scales");
  RealT centreFreq = opt.Real("U", 0.4, "prototype filter centre frequency");
  RealT ratio      = opt.Real("R", 2,   "filter radial scale ratio");
  RealT sfactor    = opt.Real("S", 1,   "rescaling sigma");
  RealT efactor    = opt.Real("E", 1,   "rescaling filter aspect ratio");
  bool offset      = opt.Boolean("O",   "alternate scales are offset");
  StringC ipfile   = opt.String("i","", "Name of input image (default: uses impulse)");
  StringC opfile   = opt.String("p","@X", "Name of filter plot");
  IntT im_size     = opt.Int ("is",200, "image size (if using impulse image)");
  opt.DependXor("i is");
  opt.Check();

  // if no image specified, create image of delta function
  ImageC<RealT> in(im_size,im_size);
  if (ipfile.IsEmpty()) {
    in.Fill(0);
    in[im_size/2][im_size/2] = 255;
  }
  else
    Load (ipfile, in, "", true);

  // create Gabor filter bank and apply it
  GaborComplexC bank(in.Frame(), ntheta, nscale, offset);
  if (opt.IsOnCommandLine("U")) bank.SetFreq(centreFreq);  
  if (opt.IsOnCommandLine("S")) bank.AdjustSigma(sfactor);  
  if (opt.IsOnCommandLine("E")) bank.AdjustLambda(efactor);
  if (opt.IsOnCommandLine("R")) bank.SetRadialScale(ratio);  
  Array2dC<ImageC<RealT> > out = bank.Apply(in);

  // plot filter magnitudes
  ImageC<ComplexC> fft_filt(in.Frame());
  fft_filt.ShiftArray(-(in.Frame().Center()));
  fft_filt.Fill(0.0);
  for (IntT iscale=0; iscale < nscale; ++iscale) {
    for (IntT itheta=0; itheta < ntheta; ++itheta) {
      fft_filt += bank.Mask()[itheta][iscale];
      // Next commented-out line generates plots of point spread functions
      // Save(StringC("@X:frequency = ")+centreFreq/pow(ratio,iscale) + "f_s; orientation = " + itheta + "pi/" + ntheta, out[itheta][iscale]);
    }
  }
  Save(opfile, FFT2dC::Mag(fft_filt)*128);

}
