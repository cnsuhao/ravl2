// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_OBSERVATIONHOMOG2DPOINT_HEADER
#define RAVLMATH_OBSERVATIONHOMOG2DPOINT_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Optimisation"

#include "ObservationExplicit.hh"
#include "Ravl/Vector2d.hh"

namespace RavlN {

  //! userlevel=Develop
  //: 2D homography fitting 2D point observation body.
  
  class ObservationHomog2dPointBodyC
    : public ObservationExplicitBodyC
  {
  public:

    ObservationHomog2dPointBodyC(const VectorC &nz1, const MatrixRSC &nNi1,
				 const VectorC &nz2, const MatrixRSC &nNi2);
    //: Constructor.
    
    ObservationHomog2dPointBodyC(const VectorC &nz1, const MatrixRSC &nNi1,
				 const VectorC &nz2, const MatrixRSC &nNi2,
				 RealT var_scale, RealT chi2_thres);
    //: Constructor for robust bi-Gaussian observation.

    virtual VectorC EvaluateFunctionH(const StateVectorC &state_vec);
    //: Evaluate the observation function h(x) given x

    virtual MatrixC EvaluateJacobianHx(const StateVectorC &state_vec);
    //: Evaluate the Jacobian of an observation for a single point

    const VectorC& GetZ1() const;
    //: Get point position in first image

    const MatrixRSC& GetNi1() const;
    //: Get point position inverse covariance in first image

  private:
    VectorC z1; // point position in first image
    MatrixRSC Ni1; // point position inverse covariance in first image

    Vector2dC p2; // last evaluation of observation function
    RealT z2; // last evaluation of z-coordinate of image 2 projection
  };

  //! userlevel=Normal
  //! autoLink=on
  //: 2D homography fitting 2D point observation handle class
  class ObservationHomog2dPointC
    : public ObservationExplicitC
  {
  public:
    ObservationHomog2dPointC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    ObservationHomog2dPointC(const VectorC &nz1, const MatrixRSC &nNi1,
			     const VectorC &nz2, const MatrixRSC &nNi2)
      : ObservationExplicitC(*new ObservationHomog2dPointBodyC(nz1,nNi1,nz2,nNi2))
    {}
    //: Constructor.
    
    ObservationHomog2dPointC(const VectorC &nz1, const MatrixRSC &nNi1,
			     const VectorC &nz2, const MatrixRSC &nNi2,
			     RealT var_scale, RealT chi2_thres)
      : ObservationExplicitC(*new ObservationHomog2dPointBodyC(nz1,nNi1,nz2,nNi2,var_scale,chi2_thres))
    {}
    //: Constructor for robust bi-Gaussian observation.

    ObservationHomog2dPointC(const ObservationC &obs)
      : ObservationExplicitC(obs)
    {
      if(dynamic_cast<ObservationHomog2dPointBodyC *>(&ObservationC::Body()) == 0)
	Invalidate();
    }
    //: Base class constructor.
    
  protected:
    ObservationHomog2dPointC(ObservationHomog2dPointBodyC &bod)
      : ObservationExplicitC(bod)
    {}
    //: Body constructor.
    
    ObservationHomog2dPointBodyC &Body()
    { return static_cast<ObservationHomog2dPointBodyC &>(ObservationExplicitC::Body()); }
    //: Access body.

    const ObservationHomog2dPointBodyC &Body() const
    { return static_cast<const ObservationHomog2dPointBodyC &>(ObservationExplicitC::Body()); }
    //: Access body.
    
  public:
    const VectorC& GetZ1() const
    { return Body().GetZ1(); }
    //: Get point position in first image

    const MatrixRSC& GetNi1() const
    { return Body().GetNi1(); }
    //: Get point position inverse covariance in first image
  };
}  


#endif
