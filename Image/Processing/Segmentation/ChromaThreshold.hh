// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImage
//! author="Joel Mitchelson"
#ifndef _CHROMA_THRESHOLD_HH_
#define _CHROMA_THRESHOLD_HH_

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/ByteRGBAValue.hh"

namespace RavlImageN
{
  class ChromaThresholdRGBC
  {
    friend ostream& operator<<(ostream& os, const ChromaThresholdRGBC& c);
    friend istream& operator>>(istream& is, ChromaThresholdRGBC& c);

  public:
    ChromaThresholdRGBC()
    {}
    //: default constructor

    ChromaThresholdRGBC(RealT nr0, RealT ng0, RealT nb0,
			RealT nrw = 33.33, RealT ngw = 33.33, RealT nbw = 33.33,
			RealT nblack_thresh = 0.1,
			ByteT nlabel_match = 255,
			ByteT nlabel_no_match = 0,
			ByteT nlabel_black = 0) :
      r0(nr0), g0(ng0), b0(nb0),
      rw(nrw), gw(ngw), bw(nbw),
      black_thresh(nblack_thresh),
      label_match(nlabel_match),
      label_no_match(nlabel_no_match),
      label_black(nlabel_black)
    {} 
    //: Construct with user-specified params
    
    ChromaThresholdRGBC(const ImageC<ByteRGBValueC>& image,
			RealT tolerance = 1.0,
			RealT black_thresh = 0.01,
			ByteT nlabel_match = 255,
			ByteT nlabel_no_match = 0,
			ByteT nlabel_black = 0);
    //: Construct from example image
    
  public:
    void Apply(ImageC<ByteT>& result, const ImageC<ByteRGBValueC>& image) const;
    //: perform threshold on RGB image and return binary result

    void Apply(ImageC<ByteT>& result, 
	       const ImageC<ByteRGBAValueC>& image, 
	       ImageC<ByteRGBAValueC>& auximage) const;
    //: perform threshold on RGBA image, return binary result
    //: and copy results to alpha channel of aux image if non-empty

    void Apply(ImageC<ByteT>& result,
	       ImageC<ByteRGBAValueC>& image,
	       bool copy_to_alpha = false)
    {
      if (copy_to_alpha)
      {
	Apply(result, image, image);
      }
      else
      {
	ImageC<ByteRGBAValueC> empty_image;
	Apply(result, image, empty_image);
      }
    }
    //: perform threshold on RGBA image, return binary result
    //: and optionally copy results to alpha channel of original image


  protected:
    RealT r0;
    RealT g0;
    RealT b0;

    RealT rw;
    RealT gw;
    RealT bw;

    RealT black_thresh;

    ByteT label_match;
    ByteT label_no_match;
    ByteT label_black;
  };

  ostream& operator<<(ostream& os, const ChromaThresholdRGBC& c);
  istream& operator>>(istream& is, ChromaThresholdRGBC& c);
}

#endif
