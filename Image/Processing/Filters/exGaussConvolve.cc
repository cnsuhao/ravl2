//! rcsid="$Id$"
//! lib=RavlFace
//! author="Kieron J Messer"

#include "Ravl/Option.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/DP/FileFormatIO.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/GaussConvolve.hh"

using namespace RavlImageN;

int main(int argc, char **argv)
{  
  OptionC   opt(argc,argv);
  FilenameC   inIm = opt.String("i","in.pgm", "input image");
  FilenameC   outIm = opt.String("o","out.pgm", "output image");
  UIntT       order = opt.Int("order", 5, "order of gauss convolve");
  bool    Verbose = opt.Boolean("v", false, "verbose");
  opt.Compulsory("i");
  opt.Check();

  // Working image...
  ImageC<RealT> im;
  
  // Setup filter.
  GaussConvolveC<RealT> gc(order);
  
  // load in an image
  
  Load(inIm, im, "", Verbose);
  
  // Filter image.
  im = gc.Apply(im);
  
  // Save result.
  Save(outIm,im, "", Verbose);
  
  return 0;
}

