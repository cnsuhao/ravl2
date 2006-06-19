// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include "Ravl/Option.hh"
#include "Ravl/Image/ImgIOJasper.hh"
#include "Ravl/IO.hh"

using namespace RavlN;
using namespace RavlImageN;

int main(int nargs,char **argv) {
  OptionC opts(nargs,argv);
  StringC infile = opts.String("","test.jpg","Input image");
  StringC outfile = opts.String("","@X","Output image");
  opts.Check();
  
#if 1
  ImageC<ByteRGBValueC> img;
  if(!RavlN::Load(infile,img)) {
    cerr <<  "Failed to load image '" << infile << "' \n";
    return 1;
  }
  
  if(!RavlN::Save(outfile,img,"JasperLossy1",false)) {
    cerr <<  "Failed to save image '" << outfile << "' \n";
    return 1;
  }
  
#else
  DPImageIOJasperBaseC imgio;
  if(!imgio.OpenRead(infile)) {
    cerr << "Failed to load image '" << infile << "' \n";
    return 1;
  }
  
  //: Load image from current stream.
  
  jas_image_t *img = imgio.LoadImage();
  if(img == 0) {
    cerr << "Failed to load image. \n";
    return 1;
  }
  
  ImageC<ByteRGBValueC> ximg;
  if(!imgio.Jas2Ravl(img,ximg)) {
    cerr << "Failed to covert image. \n";
    return 1;
  }
#endif  
  
  return 0;
}
