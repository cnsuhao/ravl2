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
//! lib=RavlImageProc
//! docentry="Ravl.Images.Corner Detection"
//! example=exCorner.cc
//! author="Radek Marik, modified by Charles Galambos"
//! file="Ravl/Image/Processing/Corners/CornerDetectorHarris.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/Corner.hh"
#include "Ravl/DList.hh"
#include "Ravl/Image/ConvolveSeparable2d.hh"
#include "Ravl/Image/CornerDetector.hh"

namespace RavlImageN {
  
  //! userlevel=Develop
  //: Harris corner detector.
  // Also known as the Plessey corner detector. Proposed by C.Harris in 1987.<p>
  // Note: the implementation of this detector could be faster.
  
  class CornerDetectorHarrisBodyC 
    : public CornerDetectorBodyC
  {
  public:
    CornerDetectorHarrisBodyC(int threshold = 700,int w = 5);
    //: Constructor.
    // threshold = Minimum level of cornerness to accept. <br>
    // w = width of filter to use for corners.
    
    DListC<CornerC> Apply(const ImageC<ByteT> &img);
    //: Get a list of corners from 'img'
    
  protected:    
    void ImagGrad(const ImageC<ByteT> &in,ImageC<TFVectorC<IntT,3> > &val);
    
    ImageC<IntT> CornerHarris(const ImageC<ByteT> &img);
    
    int Peak(ImageC<IntT> &result,const ImageC<ByteT> &in,DListC<CornerC> &cornerOut);

  private:
    const int w;
    const int threshold;
    ConvolveSeparable2dC<TFVectorC<IntT,3>,TFVectorC<IntT,3>,IntT,TFVectorC<IntT,3> > filter;    
    RealT maskSum;
    
    // Working images, so we don't have to repeatedly allocate them.
    ImageC<TFVectorC<IntT,3> > vals;
    ImageC<TFVectorC<IntT,3> > fvals;
    ImageC<IntT> var;
  };

  //! userlevel=Normal
  //: Harris corner detector.
  // Also known as the Plessey corner detector. Proposed by C.Harris in 1987.<p>
  // Note: the implementation of this detector could be faster.
  
  class CornerDetectorHarrisC
    : public CornerDetectorC
  {
  public:
    CornerDetectorHarrisC(int threshold = 700,int w = 5)
      : CornerDetectorC(*new CornerDetectorHarrisBodyC(threshold,w)) 
    {}
    //: Corner detector.
    
  };
}

#endif
