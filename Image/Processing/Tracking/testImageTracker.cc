// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! file="Ravl/Image/Processing/Tracking/PointTrackModel.cc"
//! lib=RavlImageProc

#include "Ravl/Image/ImageTracker.hh"
#include "Ravl/Option.hh"
#include "Ravl/IO.hh"

using namespace RavlImageN;

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  StringC inFile1 = opt.String("i1","","Input file. ");
  StringC inFile2 = opt.String("i2","","Input file. ");
  IntT off1 = opt.Int("o1",0,"Offset. ");
  IntT off2 = opt.Int("o2",0,"Offset. ");
  IntT patchSize = opt.Int("p",16,"Patch size used in tracking.");
  IntT searchSize = opt.Int("s",25,"Search size. ");
  IntT matchThresh = opt.Int("m",20,"Match threshold ");
  opt.Check();
  
  ImageC<ByteT> img;
  if(!Load(inFile1,img)) {
    cerr << "Failed to load input image '" << inFile1 << "' \n";
    return 1;
  }
  Projection2dC ident;
  
  ImageC<ByteT> img2 = img.CopyAccess(off1,off2);
  
  ImageTrackerC track(patchSize,searchSize,matchThresh);
  
  DListC<PairC<Point2dC> > pairs = track.TrackImage(img,img2,ident);
  
  cerr << "Pairs=" << pairs << "\n";
  
  return 0;
}
