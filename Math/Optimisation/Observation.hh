// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_OBSERVATION_HEADER
#define RAVLMATH_OBSERVATION_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Optimisation"

#include "Ravl/RefCounter.hh"
#include "Ravl/Vector.hh"
#include "Ravl/MatrixRS.hh"

#include "StateVector.hh"
#include "ObsVector.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Observation body class
  class ObservationBodyC
    : public RCBodyVC
  {
  public:
    ObservationBodyC()
    {}
    //: Default constructor.
    
    ObservationBodyC(const ObsVectorC &nobs_vec);
    //: Constructor.
    
    virtual RealT SquareResidual(const StateVectorC &state_vec);
    //: Compute the Chi-squared residual
    
    virtual bool IncrementLS(const StateVectorC &state_vec,
			     MatrixRSC &A,
			     VectorC &a);
    //: Increment the linear system

    const VectorC& GetZ() const;
    //: Get observation vector z

    const MatrixRSC& GetNi() const;
    //: Get observation inverse covariance N^-1

    const ObsVectorC& GetObsVec() const;
    //: Get observation vector/inverse covariance object

  protected:
    ObsVectorC obs_vec; //: Observation vector
  };

  //! userlevel=Normal
  //! autoLink=on
  //: Observation handle class
  // This is the base class for observations on a state, for the purpose of
  // least-squares optimisation. It contains an observation vector z and its
  // associated inverse covariance matrix N^-1 encapsulated as an ObsVectorC
  // object, plus virtual methods implemented in subclasses that detail how
  // the observation vector relates to the state parameters x being computed,
  // either through an explicit observation equation
  // <blockquote>
  //     z = h(x) + w
  // </blockquote>
  // (w is a noise vector with covariance N) or an implicit equation
  // <blockquote>
  //     F(x,z-w) = 0
  // </blockquote>
  // ObservationC currently provides methods to support the
  // Levenberg-Marquardt algorithm, but it is envisaged that more methods
  // may be added to support other algorithms. Because there are two types
  // of observation, explicit and implicit the specific formulae for
  // implementing the Levenberg-Marquardt updates are placed in corresponding
  // sub-classes, ObservationExplicitC and ObservationImplicitC.
  // ObservationExplicitC and ObservationImplicitC are themselves derived
  // into subclasses that directly evaluate h(x) or F(x,z) and (optionally)
  // their associated Jacobians for a specific type of observation.
  // <p>
  // The class hierarchies represented by the base classes ObsVectorC and
  // StateVectorC encapsulate respectively the observation vector/covariance
  // z,N and the state vector x. The principle is that an ObsVector (z/N)
  // sub-class object (for instance an image point) could be used as an
  // observation on a wide variety of optimisation applications, so z/N
  // "deserve" a class hierarchy in their own right. Also a given state
  // vector sub-class (for instance parameters representing a 3D rotation)
  // can be used for a variety of optimisation tasks, and even within one
  // task a number of different observation types on the state might be
  // envisaged. Finally the ObservationC class hierarchy combines the
  // observation vector and state vector together with specific observation
  // equations (explicit or implicit) relating one to the other.
  class ObservationC
    : public RCHandleC<ObservationBodyC>
  {
  public:    
    ObservationC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    ObservationC(const ObsVectorC &nobs_vec)
      : RCHandleC<ObservationBodyC>(*new ObservationBodyC(nobs_vec))
    {}
    //: Constructor
    
  protected:
    ObservationC(ObservationBodyC &bod)
      : RCHandleC<ObservationBodyC>(bod)
    {}
    //: Body constructor.

    ObservationBodyC &Body()
    { return RCHandleC<ObservationBodyC>::Body(); }
    //: Access body.

    const ObservationBodyC &Body() const
    { return RCHandleC<ObservationBodyC>::Body(); }
    //: Access body.
    
  public:
    RealT SquareResidual(const StateVectorC &state_vec)
    { return Body().SquareResidual(state_vec); }
    //: Compute the Chi-squared residual
    // This is the term in the
    // <a href="/user/cvsspst/ees1pm/Ravl/doc/levmarq/levmarq.html#chi2-def">error function</a>
    // for a single observation. This is a virtual method, and
    // has specific implementations for explicit and implicit observations in
    // the ObservationExplicitC and ObservationImplicitC subclasses.

    bool IncrementLS(const StateVectorC &state_vec,
		     MatrixRSC &A,
		     VectorC &a)
    { return Body().IncrementLS(state_vec,A,a); }
    //: Increment the linear system
    // This adds the relevant terms to the inverse covariance matrix A and
    // vector a accumulated within a Levenberg-Marquardt iteration for a
    // single observation, as given by the
    // <a href="/user/cvsspst/ees1pm/Ravl/doc/levmarq/levmarq.html#LM_update">state update equation</a>
    // for the explicit form of observations. This is a virtual method, and
    // has specific implementations for explicit and implicit observations in
    // the ObservationExplicitC and ObservationImplicitC subclasses.

    const VectorC &GetZ() const
    { return Body().GetZ(); }
    //: Get observation vector z

    const MatrixRSC &GetNi() const
    { return Body().GetNi(); }
    //: Get observation inverse covariance N^-1

    const ObsVectorC& GetObsVec() const
    { return Body().GetObsVec(); }
    //: Get observation vector/inverse covariance object
  };
}


#endif
