// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_CORNERHARRIS_HEADER
#define RAVLIMAGE_CORNERHARRIS_HEADER 1
//! rcsid="$Id$"
//! userlevel=Normal
//! date="1/10/1991"
//! lib=RavlImage
//! docentry="Ravl.Images.Corner Detection"
//! example=exCorner.cc
//! author="Radek Marik, modified by Charles Galambos"

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/Corner.hh"
#include "Ravl/DList.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Harris corner detector.
  // Also known as the Plessey corner detector. Proposed by C.Harris in 1987.<p>
  // Note: the implementation of this detector could be faster.
  
  class CornerDetectorHarrisC {
  public:
    CornerDetectorHarrisC(int theshold = 20,int w = 3,RealT sigma = 3.0);
    //: Defa
    
    DListC<CornerC> Apply(ImageC<ByteT> &img);
    //: Get a list of corners from 'img'
    
  protected:    
    void ImagGrad(ImageC<ByteT> &In,ImageC<IntT> &ixix,ImageC<IntT> &iyiy,ImageC<IntT> &ixiy);
    
    ImageC<RealT> Gauss2D(RealT sigma = 3.0,int w = 5);
    
    ImageC<IntT> CornerHarris(ImageC<ByteT> &img);
    
    int Peak(ImageC<IntT> &result,ImageC<ByteT> &in,DListC<CornerC> &cornerOut);
    
  private:
    const int w;
    const int threshold;
    const ImageC<RealT> mask;
    
  };
  
}

#endif
