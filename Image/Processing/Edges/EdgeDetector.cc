// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! author="Charles Galambos"
//! lib=RavlImageProc

#include "Ravl/Image/EdgeDetector.hh"

namespace RavlImageN {

  //: Constructor.
  
  EdgeDetectorBodyC::EdgeDetectorBodyC(bool useDeriche,RealT nminHyst,RealT nmaxHyst) 
    : minHyst(nminHyst),
      maxHyst(nmaxHyst),
      eightConnect(false)
  {
    
  }

  //: Apply the edge detector to 'img', returning a list of edgels.
  
  bool EdgeDetectorBodyC::Apply(const ImageC<RealT> &img,SArray1dC<EdgelC> &edges) {    
    ImageC<RealT> edgeDx;
    ImageC<RealT> edgeDy;
    ImageC<RealT> edgeMag;
    
    edgeDet.Apply(img,edgeDx,edgeDy);
    
    sqrCompose.Apply(edgeDx,edgeDy,edgeMag);
    RavlAssert(edgeDx.Frame().Area() > 0);
    RavlAssert(edgeDy.Frame().Area() > 0);
    RavlAssert(edgeMag.Frame().Area() > 0);
    
    RealT mean;
    ImageC<RealT> nonMax;
    IntT edgels;
    nonMaxSup.Apply(edgeDx,edgeDy,edgeMag,nonMax,mean,edgels);
    
    EdgeLinkC edgeMap = HysterisisThreshold(nonMax,minHyst,maxHyst);
    
    edges = edgeMap.ListEdgels(edgeDx,edgeDy,nonMax);
    
    return true;
  }

}
