// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! author="Charles Galambos"
//! lib=RavlImageProc
//! file="Ravl/Image/Processing/Edges/EdgeDetector.cc"

#include "Ravl/Image/EdgeDetector.hh"
#include "Ravl/Image/EdgeSobel.hh"

namespace RavlImageN {

  //: Constructor.
  
  EdgeDetectorBodyC::EdgeDetectorBodyC(bool nuseDeriche,RealT nminHyst,RealT nmaxHyst) 
    : minHyst(nminHyst),
      maxHyst(nmaxHyst),
      useDeriche(nuseDeriche),
      eightConnect(false)
  { 
  }

  //: Apply the edge detector to 'img', generate an edge link image.
  
  bool EdgeDetectorBodyC::Apply(const ImageC<RealT> &img,EdgeLinkC &edgeMap,ImageC<RealT> &edgeDx,ImageC<RealT> &edgeDy,ImageC<RealT> &nonMax) {     
    ImageC<RealT> edgeMag;
    if(useDeriche)
      edgeDet.Apply(img,edgeDx,edgeDy);
    else {
      EdgeSobelC<RealT,RealT> ed;
      ed.Apply(img,edgeDx,edgeDy);
    }
    
    sqrCompose.Apply(edgeDx,edgeDy,edgeMag);
    RavlAssert(edgeDx.Frame().Area() > 0);
    RavlAssert(edgeDy.Frame().Area() > 0);
    RavlAssert(edgeMag.Frame().Area() > 0);
    
    RealT mean;
    IntT edgels;
    nonMaxSup.Apply(edgeDx,edgeDy,edgeMag,nonMax,mean,edgels);
    
    edgeMap = HysteresisThreshold(nonMax,minHyst,maxHyst);
    
    return true;
  }

  //: Apply the edge detector to 'img', returning a list of edgels.
  
  bool EdgeDetectorBodyC::Apply(const ImageC<RealT> &img,SArray1dC<EdgelC> &edges) {
    ImageC<RealT> edgeDx;
    ImageC<RealT> edgeDy;
    ImageC<RealT> edgeMag;
    EdgeLinkC edgeMap;
    if(!Apply(img,edgeMap,edgeDx,edgeDy,edgeMag))
      return false;    
    edges = edgeMap.ArrayOfEdgels(edgeDx,edgeDy,edgeMag);
    return true;
  }

  //: Apply the edge detector to 'img', generate a list of edgels.
  
  bool EdgeDetectorBodyC::Apply(const ImageC<RealT> &img,DListC<EdgelC> &edges) {
    ImageC<RealT> edgeDx;
    ImageC<RealT> edgeDy;
    ImageC<RealT> nonMax;
    EdgeLinkC edgeMap;
    if(!Apply(img,edgeMap,edgeDx,edgeDy,nonMax))
      return false;    
    edges = edgeMap.ListOfEdgels(edgeDx,edgeDy,nonMax);
    return true;
  }

}
