// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_OBSERVATIONAFFINE2DPOINT_HEADER
#define RAVL_OBSERVATIONAFFINE2DPOINT_HEADER 1
//! userlevel=Normal
//! author="Charles Galambos"
//! date="1/10/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Optimisation.Examples"
//! lib=RavlOptimise

#include "Ravl/ObservationExplicit.hh"
#include "Ravl/Vector2d.hh"

namespace RavlN {
    //! userlevel=Develop
  //: 2D homography fitting 2D point observation body.
  
  class ObservationAffine2dPointBodyC
    : public ObservationExplicitBodyC
  {
  public:
    ObservationAffine2dPointBodyC(const VectorC &nz1, const MatrixRSC &nNi1,
				 const VectorC &nz2, const MatrixRSC &nNi2);
    //: Constructor.
    
    virtual VectorC EvaluateFunctionH(const StateVectorC &state_vec);
    //: Evaluate the observation function h(x) given x
    
    virtual MatrixC EvaluateJacobianHx(const StateVectorC &state_vec);
    //: Evaluate the Jacobian of an observation for a single point
    
    inline const VectorC& GetZ1() const
    { return z1; }
    //: Get point position on first plane

    inline const MatrixRSC& GetNi1() const
    { return Ni1; }
    //: Get point position inverse covariance on first plane

  private:
    VectorC z1; // point position on first plane
    MatrixRSC Ni1; // point position inverse covariance on first plane    
  };

  //! userlevel=Normal
  //! autoLink=on
  //: 2D affine homography fitting 2D point observation class
  
  class ObservationAffine2dPointC
    : public ObservationExplicitC
  {
  public:
    ObservationAffine2dPointC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    ObservationAffine2dPointC(const VectorC &nz1, const MatrixRSC &nNi1,
			     const VectorC &nz2, const MatrixRSC &nNi2)
      : ObservationExplicitC(*new ObservationAffine2dPointBodyC(nz1,nNi1,nz2,nNi2))
    {}
    //: Constructor.
    
    ObservationAffine2dPointC(const ObservationC &obs)
      : ObservationExplicitC(obs)
    {
      if(dynamic_cast<ObservationAffine2dPointBodyC *>(&ObservationC::Body()) == 0)
	Invalidate();
    }
    //: Base class constructor.
    
  protected:
    ObservationAffine2dPointC(ObservationAffine2dPointBodyC &bod)
      : ObservationExplicitC(bod)
    {}
    //: Body constructor.
    
    ObservationAffine2dPointBodyC &Body()
    { return static_cast<ObservationAffine2dPointBodyC &>(ObservationExplicitC::Body()); }
    //: Access body.

    const ObservationAffine2dPointBodyC &Body() const
    { return static_cast<const ObservationAffine2dPointBodyC &>(ObservationExplicitC::Body()); }
    //: Access body.
    
  public:
    const VectorC& GetZ1() const
    { return Body().GetZ1(); }
    //: Get point position on first plane

    const MatrixRSC& GetNi1() const
    { return Body().GetNi1(); }
    //: Get point position inverse covariance on first plane
  };

  
}


#endif
