// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_REMOVEDISTORTION_HEADER
#define RAVLIMAGE_REMOVEDISTORTION_HEADER 1
//! rcsid="$Id$"
//! lib=RavlImageProc
//! docentry="Ravl.Images.Warping"
//! author="Philip McLauchlan"
//! date="16/07/2002"

#include "Ravl/Image/PixelMixer.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Matrix3d.hh"
#include "Ravl/Vector3d.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/RealRange2d.hh"
#include "Ravl/LinePP2d.hh"

namespace RavlImageN {
  
  // value less than but close to 1 indicating how close you want to get to the
  // model limit before switching to the outer linear model.
  //
#define MODEL_FRACTION 0.95

  // thresholds on change in radial distance R value
#define R_CHANGE_THRES 1.0e-7

  // minimum/maximum number of iterations to apply when applying inverse
  // distortion
#define MIN_UND_ITERATIONS   6
#define MAX_UND_ITERATIONS 100

  // threshold on closness of camera coordinates to optical axis */
#define SMALL_DR_THRES 0.001

  //! userlevel=Normal
  //: Remove distortion from an image.
  
  template <class InT, class OutT = InT,class MixerT = PixelMixerAssignC<InT,OutT> >
  class RemoveDistortionC
  {
  public:
    RemoveDistortionC()
    {}
    //: Default constructor.
    
    RemoveDistortionC(const IndexRange2dC &orec,
		      RealT ncx, RealT ncy,
		      RealT nfx=1.0, RealT nfy=1.0,
		      RealT nK1=0.0,
		      RealT nK2=0.0,
		      bool nFillBackground = true,
		      const MixerT &mix = MixerT())
      : cx(ncx),
	cy(ncy),
	fx(nfx),
	fy(nfy),
	K1(nK1),
	K2(nK2),
	rec(orec),
	fillBackground(nFillBackground),
	mixer(mix)
    { Init(); }
    //: Constructor.
    // Where orec is the size of the output rectangle.
    
    RemoveDistortionC(RealT ncx, RealT ncy,
		      RealT nfx, RealT nfy,
		      RealT nK1=0.0,
		      RealT nK2=0.0,
		      bool nFillBackground = true,
		      const MixerT &mix = MixerT())
      : cx(ncx),
	cy(ncy),
	fx(nfx),
	fy(nfy),
	K1(nK1),
	K2(nK2),
	fillBackground(nFillBackground),
	mixer(mix)
    { Init(); }
    //: Constructor.

    void Apply(const ImageC<InT> &img,ImageC<OutT> &out);
    //: Remove distortion from image 'img' and write it into 'out'
    
    ImageC<OutT> Apply(const ImageC<InT> &img) {
      ImageC<OutT> out(rec);
      Apply(img,out);
      return out;
    }
    //: Remove distortion from input image working rectangle into
    //: output image rectangle.
    // The output rectangle is specified in the constructor.

    Point2dC ProjectPoint(const Point2dC &pnti) const
    {
      /* compute squared radial distance R2 */
      RealT X2 = pnti[0]*pnti[0], Y2 = pnti[1]*pnti[1];
      RealT R2 = X2 + Y2, d;

      /* check if we are at a point outside the distortion model */
      if ( R2 > thres_dR )
	// use outer linear model
	d = outer_a + outer_b/sqrt(R2);
      else
	// calculate distortion and apply it to the image position
	d = 1.0 + (K1 + K2*R2)*R2;

      return Point2dC(cx + d*fx*pnti[0], cy + d*fy*pnti[1]);
    }
    //: Project point from ideal camera coordinates into image coordinates

    Point2dC ProjectPointLinear(const Point2dC &pnti) const
    {
      return Point2dC(cx + fx*pnti[0], cy + fy*pnti[1]);
    }
    //: Project point from ideal camera coordinates into image coordinates
    // Uses linear (pinhole) camera model

    Point2dC BackProjectPoint(const Point2dC &pnti) const
    {
      RavlAssert ( fx != 0.0 && fy != 0.0 );

      // compute distorted X/Y coordinates of scene point pnti on plane Z=1
      Point2dC pnto((pnti[0] - cx)/fx, (pnti[1] - cy)/fy);

      // compute distortion value
      RealT d = ComputeDistortion(pnto);
                                          
      // remove distortion from camera coordinates
      pnto /= d;
      return pnto;
    }
    //: Back-project point from image into ideal camera coordinates

    Point2dC BackProjectPointLinear(const Point2dC &pnti) const
    {
      RavlAssert ( fx != 0.0 && fy != 0.0 );

      // compute X/Y coordinates of scene point pnti on plane Z=1
      return Point2dC((pnti[0] - cx)/fx, (pnti[1] - cy)/fy);
    }
    //: Back-project point from image into ideal camera coordinates
    // Uses linear (pinhole) camera model

    Point2dC RemoveDist(const Point2dC &pnti) const;
    //: Remove distortion from a point

    Point2dC AddDist(const Point2dC &pnti) const;
    //: Add distortion to a point
    
  protected:
    void Init();

    RealT cx, cy, fx, fy, K1, K2;
    IndexRange2dC rec;
    bool fillBackground;
    MixerT mixer;

    RealT thres_R2, thres_dR; // Thresholds on R^2and d*R
    RealT outer_a, outer_b; // Outer linear model parameters

    RealT ComputeDistortion(const Point2dC &pnti) const;
  };

  template <class InT, class OutT,class MixerT>
  void RemoveDistortionC<InT,OutT,MixerT>::Init() {
    // Compute threshold on radial camera coordinate to see if position
    // is within valid region
    if ( K2 == 0.0 ) {
      if ( K1 < 0.0 )
	thres_R2 = -MODEL_FRACTION*MODEL_FRACTION*0.333333333/K1;
      else
	thres_R2 = thres_dR = outer_a = outer_b = DBL_MAX;
    }
    else {
      RealT disc = 0.09*K1*K1 - 0.2*K2;

      if ( disc > 0.0 ) {
	RealT R2a, R2b;

	disc = sqrt(disc);

	R2a = (-0.3*K1 + disc)/K2;
	R2b = (-0.3*K1 - disc)/K2;
	if ( R2a > 0.0 ) {
	  // two solutions: take solution closest to zero
	  if ( R2a < R2b ) thres_R2 = R2a;
	  else             thres_R2 = R2b;
	}
	else if ( R2b > 0.0 )
	  thres_R2 = R2b;
	else
	  thres_R2 = thres_dR = outer_a = outer_b = DBL_MAX;
      }
      else
	thres_R2 = thres_dR = outer_a = outer_b = DBL_MAX;
    }

    // check whether a limit on radial distance has been imposed
    if ( thres_R2 != DBL_MAX ) {
      double R = sqrt(thres_R2);

      // compute limited on distorted radial distance
      thres_dR = (1.0 + thres_R2*(K1 + thres_R2*K2))*R;

      // compute parameters of outer linear model
      outer_a = 1.0 + thres_R2*(3.0*K1 + thres_R2*5.0*K2);
      outer_b = thres_dR - outer_a*R;
    }
  }
  
  template <class InT, class OutT,class MixerT>
  RealT RemoveDistortionC<InT,OutT,MixerT>::ComputeDistortion(const Point2dC &pnti) const {
    RealT dR = sqrt(pnti[0]*pnti[0]+pnti[1]*pnti[1]);

    // return immediately with zero distortion if the distortion coefficients
    // are zero or the distorted radial distance is small
    if ( (K1 == 0.0 && K2 == 0.0) || dR < SMALL_DR_THRES )
      return 1.0;

    // check whether d*R is outside range of distortion model
    if ( dR > thres_dR )
      // use outer linear model
      // compute distortion value dR/R by solving linear equation for R
      return ( dR*outer_a/(dR - outer_b) );

    // if initialization takes us outside the range of the camera,
    // move the start point back to the middle of the range
    RealT R;
    if ( dR*dR >= thres_R2 )
      R = 0.5*sqrt(thres_R2);
    else
      // initialise assuming zero distortion
      R = dR;

    for ( IntT it = 1; ; it++ ) {
      RealT R2 = R*R;
      RealT deriv = 1.0 + R2*(3.0*K1 + 5.0*R2*K2);
      if ( deriv == 0.0 )
	throw ExceptionNumericalC("Division by zero in template <class InT, class OutT,class MixerT> RealT RemoveDistortionC<InT,OutT,MixerT>::ComputeDistortion(const Point2dC &) const");

      // compute change to make to R
      RealT Rdiff = (R*(1.0 + R2*(K1 + R2*K2)) - dR)/deriv;
      R -= Rdiff;

      // check whether the new R is outside the range
      if ( R < 0.0 || R*R >= thres_R2 )
	throw ExceptionNumericalC("Outside range in template <class InT, class OutT,class MixerT> RealT RemoveDistortionC<InT,OutT,MixerT>::ComputeDistortion(const Point2dC &) const");

      // check whether we have converged, observing the minimum number of
      // iterations
      if ( fabs(Rdiff) < R_CHANGE_THRES && it >= MIN_UND_ITERATIONS )
         break;
        
      // check whether we have exceeded the maximum number of iterations
      if ( it > MAX_UND_ITERATIONS )
	throw ExceptionC("Too many iterations in template <class InT, class OutT,class MixerT> RealT RemoveDistortionC<InT,OutT,MixerT>::ComputeDistortion(const Point2dC &) const");
    }

    // compute distortion and remove it from camera coordinates
    return (1.0 + R2*(K1 + R2*K2));
  }

  template <class InT, class OutT,class MixerT>
  Point2dC RemoveDistortionC<InT,OutT,MixerT>::RemoveDist(const Point2dC &pnti) const
  {
    // backproject point
    Point2dC pnto = BackProjectPoint(pnti);

    // reproject point using linear camera model
    return ProjectPointLinear(pnto);
  }
  
  template <class InT, class OutT,class MixerT>
  Point2dC RemoveDistortionC<InT,OutT,MixerT>::AddDist(const Point2dC &pnti) const
  {
    // backproject point using linear camera model
    Point2dC pnto = BackProjectPointLinear(pnti);

    // reproject point with distortion
    return ProjectPoint(pnto);
  }

  template <class InT, class OutT,class MixerT>
  void RemoveDistortionC<InT,OutT,MixerT>::Apply(const ImageC<InT> &src,ImageC<OutT> &outImg) {
    
    RealRange2dC irng(src.Frame());
    
    // adjust source window for area where bilinear interpolation can be
    // computed safely. Using 0.51 instead of 0.5 ensures that points on the
    // boundary are not used, for safety.
    irng.TRow() += 0.51; irng.BRow() -= 0.51;
    irng.LCol() += 0.51; irng.RCol() -= 0.51;

    // set pat as top-left pixel in output image
    Point2dC pat(outImg.Frame().Origin());
    pat[0] += 0.5;
    pat[1] += 0.5;
    
    Array2dIterC<OutT> it(outImg);  
    
    // Do simple check for each pixel that its contained in the input image.
    for(;it;) {
      if(fillBackground) {
	do {
	  Point2dC ipat = AddDist(pat);
	  if(irng.Contains(ipat))
	    mixer(*it,src.BiLinear(ipat - Point2dC(0.5,0.5)));
	  else
	    SetZero(*it);
	} while(it.Next()) ;
      } else {
	do {
	  Point2dC ipat = AddDist(pat);
	  if(irng.Contains(ipat))
	    mixer(*it,src.BiLinear(ipat - Point2dC(0.5,0.5)));
	} while(it.Next()) ;
      }
      pat[0]++;
    }
  }
}


#endif
