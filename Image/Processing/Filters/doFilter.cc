// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImage
//! author="Charles Galambos"

#include "Ravl/Option.hh"
#include "Ravl/IO.hh"
#include "Ravl/Image/HomomorphicFilter.hh"

using namespace RavlN;
using namespace RavlImageN;

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  bool bypass = opt.Boolean("b",false,"Bypass filter. ");
  StringC inf = opt.String("","in.ppm","Input file.");
  StringC outf = opt.String("","out.ppm","Input file.");
  RealT depth = opt.Real("d",0.5,"Depth of momomorphic filter. ");
  RealT sigma = opt.Real("s",5,"Width of filter. ");
  opt.Check();
  
  ImageC<RealT> img;
  ImageC<RealT> res;
  if(!Load(inf,img)) {
    cerr << "Failed to load image '" << inf << "'\n";
    return 1;
  }
  if(!bypass) {
    HomomorphicFilterC hf(sigma,depth);
    res = hf.Apply(img);
  }else
    res = img;
  if(!Save(outf,res)) {
    cerr << "Failed to save image '" << outf << "'\n";
    return 1;
  }
  
  return 0;
}
