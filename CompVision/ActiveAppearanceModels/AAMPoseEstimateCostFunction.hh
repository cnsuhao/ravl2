#ifndef RAVLIMAGE_AAMPOSEESTIMATECOSTFUNCTION_HEADER
#define RAVLIMAGE_AAMPOSEESTIMATECOSTFUNCTION_HEADER 1
//////////////////////////////////////////////////////////////////////////////
//! author =    "Jean-Yves Guillemaut"
//! lib =       RavlAAM
//! date =      "01/03/2006"
//! rcsid="$Id: AAMPoseEstimateCostFunction.hh,v 1.3 2005/07/25 16:31:07 ees1wc Exp $"
//! file="Ravl/CompVision/ActiveAppearanceModels/AAMPoseEstimateCostFunction.hh"
//! userlevel = Normal
//! docentry =  "Ravl.API.Images.AAM"


#include "Ravl/PatternRec/Cost.hh"
#include "Ravl/PatternRec/Parameters.hh"
#include "Ravl/Vector.hh"

using namespace RavlN;

namespace RavlImageN {

  //! userlevel=Develop
  //: Cost function measuring the residual error between a given appearance and the appearance predicted by the statistical model of pose for a given pose value.
  // The cost function defined is:
  // <p><i>d(theta, phi) = || _C-(_C0 + _CT cos(theta) + _ST sin(theta) + _CP cos(phi) + _SP sin(phi) + _CTCP cos(theta) cos(phi) + _CTSP cos(theta) sin(phi) + _STCP sin(theta) cos(phi) + _STSP sin(theta) sin(phi) ||</i>,</p>
  // where '_C0', '_CT', '_ST', '_CP', '_SP', '_CTCP', '_CTSP', '_STCP', '_STSP' are vectors defining the statitical model of pose variation and '_C' is the parameter vector representing the given appearance. The pose is represented by the pan angle 'theta' and the tilt angle 'phi'; both values are expressed in radians.

  class AAMPoseEstimateCostFunctionBodyC: public CostBodyC
  {

  public:
    AAMPoseEstimateCostFunctionBodyC (const ParametersC &parameters, const VectorC &C0, const VectorC &CT, const VectorC &ST, const VectorC &CP, const VectorC &SP, const VectorC &CTCP, const VectorC &CTSP, const VectorC &STCP, const VectorC &STSP, const VectorC &C);
    //: Constructor.
    //!param: parameters - Parameters of the cost function.
    //!param: C0 - Input value for _C0.
    //!param: CT - Input value for _CT.
    //!param: ST - Input value for _ST.
    //!param: CP - Input value for _CP.
    //!param: SP - Input value for _SP.
    //!param: CTCP - Input value for _CTCP.
    //!param: CTSP - Input value for _CTSP.
    //!param: STCP - Input value for _STCP.
    //!param: STSP - Input value for _STSP.
    //!param: C - Input value for _C.
    // This defines the cost function as defined above.

  protected:
    VectorC _C0;
    VectorC _CT;
    VectorC _ST;
    VectorC _CP;
    VectorC _SP;
    VectorC _CTCP;
    VectorC _CTSP;
    VectorC _STCP;
    VectorC _STSP;
    VectorC _C;

    virtual VectorC Apply (const VectorC &X) const;
    //: Evaluate cost function at pose vector 'X'.
    //  'X = (theta, phi)' is a two-dimensional vector containing the pan angle 'theta' and the tilt angle 'phi' in radians.

    virtual RealT Cost (const VectorC &X) const;
    //: Evaluate cost function at pose vector 'X'.
    //  'X = (theta, phi)' is a two-dimensional vector containing the pan angle 'theta' and the tilt angle 'phi' in radians.
  };


  //! userlevel=Advanced
  //: Cost function measuring the residual error between a given appearance and the appearance predicted by the statistical model of pose for a given pose value.
  // The cost function defined is:
  // <p><i>d(theta, phi) = || _C-(_C0 + _CT cos(theta) + _ST sin(theta) + _CP cos(phi) + _SP sin(phi) + _CTCP cos(theta) cos(phi) + _CTSP cos(theta) sin(phi) + _STCP sin(theta) cos(phi) + _STSP sin(theta) sin(phi) ||</i>,</p>
  // where '_C0', '_CT', '_ST', '_CP', '_SP', '_CTCP', '_CTSP', '_STCP', '_STSP' are vectors defining the statitical model of pose variation and '_C' is the parameter vector representing the given appearance. The pose is represented by the pan angle 'theta' and the tilt angle 'phi'; both values are expressed in radians.

  class AAMPoseEstimateCostFunctionC: public CostC
  {
  public:
    AAMPoseEstimateCostFunctionC (const ParametersC &parameters, const VectorC &C0, const VectorC &CT, const VectorC &ST, const VectorC &CP, const VectorC &SP, const VectorC &CTCP, const VectorC &CTSP, const VectorC &STCP, const VectorC &STSP, const VectorC &C)
      :CostC(*(new AAMPoseEstimateCostFunctionBodyC (parameters, C0, CT, ST, CP, SP, CTCP, CTSP, STCP, STSP, C))) {}
    //: Constructor.
    //!param: parameters - Parameters of the cost function.
    //!param: C0 - Input value for _C0.
    //!param: CT - Input value for _CT.
    //!param: ST - Input value for _ST.
    //!param: CP - Input value for _CP.
    //!param: SP - Input value for _SP.
    //!param: CTCP - Input value for _CTCP.
    //!param: CTSP - Input value for _CTSP.
    //!param: STCP - Input value for _STCP.
    //!param: STSP - Input value for _STSP.
    //!param: C - Input value for _C.
    // This defines the cost function as defined above.
  };

}

#endif
