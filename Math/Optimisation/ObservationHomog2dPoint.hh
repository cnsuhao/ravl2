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
//! docentry="Ravl.Math.Optimisation.Examples"
//! example="Homography2dFitTest.cc"

#include "Ravl/ObservationExplicit.hh"
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
  //: 2D homography fitting 2D point observation class
  // Use this class to construct an observation consisting of a pair of 2D
  // points, each of which lies on a plane. The two planes are related by
  // a 2D projective transformation represented by a 3x3 homography matrix.
  // This class applies the functional model of the 
  // 2D point pair observations on a plane which
  // are to be used to fit a line through the data. If all the points have
  // the same error isotropic error in the x and y directions, you can use
  // the standard orthogonal regression algorithm. If some points have
  // different errors to others, or there are outliers in the data points,
  // this class may be useful. It allows you to specify errors separately
  // for each point, as well as use a robust error model that accounts for
  // outliers, at least if they are not TOO far away from the good data.
  // <p>
  // This class encapsulates a single data point xc,yc and its associated error
  // inverse covariance matrix estimate N^-1. It assumes that the 2D line
  // parameters are represented by an instance of the StateVectorLine2dC
  // sub-class.
  // <p>
  // To use the data points for optimisation, create one instance of an
  // ObservationLine2dPointC for each data point, place them all in a single
  // list of ObservationC (the base class) objects, and pass the list into the
  // relevant optimisation routines.
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
