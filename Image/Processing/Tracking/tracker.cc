// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! file="Ravl/Image/Processing/Tracking/tracker.cc"
//! lib=RavlImageProc

#include "Ravl/Option.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/Image/PointTracker.hh"
#include "Ravl/Image/DrawFrame.hh"

using namespace RavlN;
using namespace RavlImageN;

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  int cthreshold = opt.Int("ct",30,"Corner threshold. ");
  int cwidth     = opt.Int("cw",7,"Corner filter width. ");
  int mthreshold = opt.Int("mt",20,"Matching threshold. ");
  int mwidth     = opt.Int("mw",15,"Tracker feature width. ");
  int lifeTime   = opt.Int("ml",8,"Lifetime of a point without a match in the incoming images. ");
  int searchSize = opt.Int("ss",25,"Search size. How far to look from the predicted position of the feature.");
  StringC ifn = opt.String("","@V4LH:/dev/video0","Input sequence. ");
  StringC ofn = opt.String("","@X","Output sequence. ");
  opt.Check();
  
  // Open an input stream.
  DPIPortC<ImageC<ByteT> > inp;
  if(!OpenISequence(inp,ifn)) {
    cerr << "Failed to open input '" << ifn << "'\n";
    return 1;
  }
  
  // Open an output stream.
  DPOPortC<ImageC<ByteT> > outp;
  if(!OpenOSequence(outp,ofn)) {
    cerr << "Failed to output input '" << ofn << "'\n";
    return 1;
  }
  
  // Creat a tracker.
  PointTrackerC tracker(cthreshold,cwidth,mthreshold,mwidth,lifeTime,searchSize);
  
  ImageC<ByteT> img;
  for(;;) {
    // Read an image from the input.
    if(!inp.Get(img))
      break;

    // Apply tracker.
    DListC<PointTrackC> corners = tracker.Apply(img);
    
    // Draw boxes around the corners.
    ByteT val = 255;
    for(DLIterC<PointTrackC> it(corners);it;it++) {
      IndexRange2dC rect(it->Location(),5,5);
      DrawFrame(img,val,rect);
    }
    
    // Write an image out.
    outp.Put(img);
  }
  return 0;
}
