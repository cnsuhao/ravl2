// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImageProc
//! author="Charles Galambos"

#include "Ravl/Image/SegmentExtrema.hh"
#include "Ravl/Option.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/IO.hh"
#include "Ravl/DP/SequenceIO.hh"

using namespace RavlImageN;

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  IntT minSize = opt.Int("ms",10,"Minimum region size. ");
  RealT minMargin = opt.Real("mm",10,"Minimum margin. ");
  bool seq = opt.Boolean("s",false,"Process a sequence. ");
  bool drawResults = opt.Boolean("d",false,"Draw results into a window.");
  StringC fn = opt.String("","test.pgm","Input image. ");
  StringC ofn = opt.String("","","Output boundries. ");  
  opt.Check();
  
  ImageC<ByteT> img;
  
  SegmentExtremaC<ByteT> lst(minSize,minMargin);
  
  // Open image source.
  DPIPortC<ImageC<ByteT> > inp;
  if(!OpenISequence(inp,fn)) {
    cerr <<  "Failed to open input sequence " << fn << "\n";
    return 1;
  }
  
  DPOPortC<DListC<BoundaryC> > outp;
  if(!ofn.IsEmpty()) {
    if(!OpenOSequence(outp,ofn)) {
      cerr <<  "Failed to open output sequence " << ofn << "\n";
      return 1;
    }
  }
  
  while(inp.Get(img)) {
    DListC<BoundaryC> bounds = lst.Apply(img);
    if(drawResults) {
      // Draw boundries into image and display.
      for(DLIterC<BoundaryC> bit(bounds);bit;bit++)
	for(DLIterC<EdgeC> it(*bit);it;it++)
	  img[it->LPixel()] = 255;
      Save("@X",img);
    }
    if(outp.IsValid()) {
      if(!outp.Put(bounds)) {
	cerr << "ABORT: Failed to write output. \n";
	return 1;
      }
    }
    if(!seq)
      break;
  }
  return 0;
}
