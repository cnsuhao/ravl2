// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImage

#include "Ravl/Image/Image.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Image/ImgIO.hh"
#include "Ravl/Option.hh"

#include "Ravl/IO.hh"

using namespace RavlImageN;

// Note: If you wish image IO to work the 'ImageIO' library must be
// specified in USESLIBS or PROGLIBS is the defs.mk file. To use
// many common image file formats you must include 'RavlExtImgIO'.

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  StringC inf = opt.String("","in.pgm","Input image. ");
  StringC outf = opt.String("","out.pgm","Input image. ");
  opt.Check();
  
  ImageC<ByteT> image;
  
  // Load an image from a file.
  
  if(!Load(inf,image)) {
    cerr << "Failed to load file '" << inf << "' \n";
    return 1;
  }
  
  // Sum all the pixel in an image.
  
  UIntT total = 0;
  for(Array2dIterC<ByteT> it(image);it;it++)
    total += *it;
  
  cerr << "Total of pixels in the image = " << total << "\n";
  
  // Set a pixel to a value.
  
  image[2][3] = 2; 
  
  // Save image to a file.
  
  if(!Load(outf,image)) {
    cerr << "Failed to save to file '" << inf << "' \n";
    return 1;
  }
  
  return 0;
}
