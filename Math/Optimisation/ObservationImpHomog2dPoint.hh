// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_OBSERVATIONIMPHOMOG2DPOINT_HEADER
#define RAVLMATH_OBSERVATIONIMPHOMOG2DPOINT_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Optimisation"

#include "ObservationImplicit.hh"
#include "Ravl/Vector2d.hh"

namespace RavlN {

  //! userlevel=Develop
  //: 2D homography fitting implicit 2D point observation body.
  
  class ObservationImpHomog2dPointBodyC
    : public ObservationImplicitBodyC
  {
  public:

    ObservationImpHomog2dPointBodyC(const VectorC &nz1, const MatrixRSC &nNi1,
				    const VectorC &nz2, const MatrixRSC &nNi2);
    //: Constructor.
    
    ObservationImpHomog2dPointBodyC(const VectorC &nz1, const MatrixRSC &nNi1,
				    const VectorC &nz2, const MatrixRSC &nNi2,
				    RealT var_scale, RealT chi2_thres);
    //: Constructor for robust bi-Gaussian observation.

    virtual VectorC EvaluateFunctionF(const StateVectorC &state_vec);
    //: Evaluate the observation function F(x,z) given x and z
#if 1
    virtual MatrixC EvaluateJacobianFz(const StateVectorC &state_vec);
    //: Evaluate the Jacobian dF/dz given x and z

    virtual MatrixC EvaluateJacobianFx(const StateVectorC &state_vec);
    //: Evaluate the Jacobian dF/dx given x and z
#endif
  private:
    Vector2dC p2; // last evaluation of projected position in image 2
    RealT z2; // last evaluation of z-coordinate of image 2 projection
  };

  //! userlevel=Normal
  //! autoLink=on
  //: 2D homography fitting implicit 2D point observation handle class
  class ObservationImpHomog2dPointC
    : public ObservationImplicitC
  {
  public:
    ObservationImpHomog2dPointC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    ObservationImpHomog2dPointC(const VectorC &nz1, const MatrixRSC &nNi1,
				const VectorC &nz2, const MatrixRSC &nNi2)
      : ObservationImplicitC(*new ObservationImpHomog2dPointBodyC(nz1,nNi1,nz2,nNi2))
    {}
    //: Constructor.
    
    ObservationImpHomog2dPointC(const VectorC &nz1, const MatrixRSC &nNi1,
				const VectorC &nz2, const MatrixRSC &nNi2,
				RealT var_scale, RealT chi2_thres)
      : ObservationImplicitC(*new ObservationImpHomog2dPointBodyC(nz1,nNi1,nz2,nNi2,var_scale,chi2_thres))
    {}
    //: Constructor for robust bi-Gaussian observation.

    ObservationImpHomog2dPointC(const ObservationC &obs)
      : ObservationImplicitC(obs)
    {
      if(dynamic_cast<ObservationImpHomog2dPointBodyC *>(&ObservationC::Body()) == 0)
	Invalidate();
    }
    //: Base class constructor.
    
  protected:
    ObservationImpHomog2dPointC(ObservationImpHomog2dPointBodyC &bod)
      : ObservationImplicitC(bod)
    {}
    //: Body constructor.
    
    ObservationImpHomog2dPointBodyC &Body()
    { return static_cast<ObservationImpHomog2dPointBodyC &>(ObservationImplicitC::Body()); }
    //: Access body.

    const ObservationImpHomog2dPointBodyC &Body() const
    { return static_cast<const ObservationImpHomog2dPointBodyC &>(ObservationImplicitC::Body()); }
    //: Access body.
    
  public:
  };
}  


#endif
