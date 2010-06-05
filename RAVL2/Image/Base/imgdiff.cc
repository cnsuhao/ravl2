// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: imgdiff.cc 5240 2005-12-06 17:16:50Z plugger $"
//! lib=RavlImage
//! author="Charles Galambos"
//! file="Ravl/Image/Base/imgdiff.cc"
//! userlevel=Normal
//! date="24/01/2001"
//! docentry="Ravl.API.Images"

//: Calculate the difference of two images that are the same size.

#include "Ravl/Option.hh"
#include "Ravl/IO.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Array2dIter3.hh"

using namespace RavlN;
using namespace RavlImageN;


int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  StringC fout = opt.String("o","@X","Output image ");
  bool abs = opt.Boolean("a",false,"Calculate the absolute difference. ");
  StringC fin1 = opt.String("","in1.pgm","Input image 1 ");
  StringC fin2 = opt.String("","in1.pgm","Input image 2 ");
  opt.Check();
  ImageC<IntT> in1;
  ImageC<IntT> in2;
  if(!Load(fin1,in1)) {
    cerr << "Failed to load image '" << fin1 << "' \n";
    return 1;
  }
  if(!Load(fin2,in2)) {
    cerr << "Failed to load image '" << fin2 << "' \n";
    return 1;
  }
  if(in1.Rectangle() != in2.Rectangle()) {
    cerr << "Image size mismatch.\n";
    return 1;
  }
  ImageC<IntT> res;
  if(!abs) 
    res = in1 - in2;
  else {
    res = ImageC<IntT>(in1.Rectangle()); // Allocate some space.
    for(Array2dIter3C<IntT,IntT,IntT> it(res,in1,in2);it;it++)
      it.Data1() = Abs(it.Data2() - it.Data3());
  }
  
  if(!Save(fout,res)) {
    cerr << "Failed to save output image '" << fout << "'\n";
    return 1;
  }
  return 0;
}
