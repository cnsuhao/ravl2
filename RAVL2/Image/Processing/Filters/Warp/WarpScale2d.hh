// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_WARPSCALE2D_HEADER
#define RAVLIMAGE_WARPSCALE2D_HEADER 1
///////////////////////////////////////////////////////////////
//! docentry="Ravl.API.Images.Scaling and Warping"
//! lib=RavlImageProc
//! author="Charles Galambos"
//! rcsid="$Id$"
//! date="05/05/1999"
//! file="Ravl/Image/Processing/Filters/Warp/WarpScale2d.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/BilinearInterpolation.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Vector2d.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/RealRange2d.hh"

namespace RavlImageN {

  template <class InT, class OutT>
  bool WarpScaleBilinear(const ImageC<InT> &img,
                           const Vector2dC &scale, // Distance between samples in the input image.
                           ImageC<OutT> &result,    // Output of scaling. The image must be of the appropriate size
                           const Point2dC &offset = Point2dC(0,0) // Position in input image of the origin in output image,
                           )
  {
    Point2dC origin = img.Frame().Origin();
    origin += offset;

    if(result.Frame().IsEmpty()) {
      RealRange2dC sourceFrame(img.Frame());
      Vector2dC invScale(1/scale[0],1/scale[1]);
      IndexRange2dC rng = RavlN::RealRange2dC(sourceFrame*invScale).IndexRange().Expand(-2);
      result = ImageC<OutT>(rng);
    }

    // FIXME:-Check required range of input image isn't exceeded.
    origin += Vector2dC(0.5,0.5);
#if 0
    // Simple implementation.
    Point2dC rowStart = origin;
    for(Array2dIterC<OutT> it(result);it;) {
      Point2dC pnt = rowStart;
      do {
        BilinearInterpolation(img,pnt,*it);
        pnt[1] += scale[1];
      } while(it.Next()); // True while in same row.
      rowStart[0] += scale[0];
    }
#else
    Point2dC rowStart = origin;
    for(Array2dIterC<OutT> it(result);it;) {
      Point2dC pnt = rowStart;

      IntT fx = Floor(pnt[0]); // Row
      RealT u = pnt[0] - fx;
      RealT onemu = (1.0-u);
      do {
        IntT fy = Floor(pnt[1]); // Col
        RealT t = pnt[1] - fy;
        RealT onemt = (1.0-t);

        const InT* pixel1 = &(img)[fx][fy];
        const InT* pixel2 = &(img)[fx+1][fy];
        *it = OutT((pixel1[0] * (onemt*onemu)) +
                    (pixel1[1] * (t*onemu)) +
                    (pixel2[0] * (onemt*u)) +
                    (pixel2[1] * (t*u)));
        pnt[1] += scale[1];
      } while(it.Next()); // True while in same row.

      rowStart[0] += scale[0];
    }
#endif
    return true;
  }
  //: Scale an image
}
#endif
