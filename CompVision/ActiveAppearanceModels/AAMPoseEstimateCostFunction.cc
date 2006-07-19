//////////////////////////////////////////////////////////////////////////////
//! author =    "Jean-Yves Guillemaut"
//! lib =       RavlAAM
//! date =      "01/03/2006"
//! file="Ravl/CompVision/ActiveAppearanceModels/AAMPoseEstimateCostFunction.cc"
//! rcsid="$Id: AAMPoseEstimateCostFunction.cc,v 1.3 2005/07/25 16:31:07 ees1wc Exp $"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

#include "Ravl/PatternRec/Cost.hh"
#include "Ravl/PatternRec/Parameters.hh"
#include "Ravl/Vector.hh"

#include "AAMPoseEstimateCostFunction.hh"

using namespace RavlN;

namespace RavlImageN {

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
  AAMPoseEstimateCostFunctionBodyC::AAMPoseEstimateCostFunctionBodyC (const ParametersC &parameters, const VectorC &C0, const VectorC &CT, const VectorC &ST, const VectorC &CP, const VectorC &SP, const VectorC &CTCP, const VectorC &CTSP, const VectorC &STCP, const VectorC &STSP, const VectorC &C)
    :CostBodyC(parameters),
     _C0(C0),
     _CT(CT),
     _ST(ST),
     _CP(CP),
     _SP(SP),
     _CTCP(CTCP),
     _CTSP(CTSP),
     _STCP(STCP),
     _STSP(STSP),
     _C(C)
  {
  }

  //: Evaluate cost function at pose vector 'X'.
  //  'X = (theta, phi)' is a two-dimensional vector containing the pan angle 'theta' and the tilt angle 'phi' in radians.
  RealT AAMPoseEstimateCostFunctionBodyC::Cost (const VectorC &X) const
  {

    PairC<RealT> angles(X[0],X[1]);

    // residual
    VectorC r = _C - (_C0+_CT*Cos(angles.Data1())+_ST*Sin(angles.Data1())+_CP*Cos(angles.Data2())+_SP*Sin(angles.Data2())+_CTCP*Cos(angles.Data1())*Cos(angles.Data2())+_CTSP*Cos(angles.Data1())*Sin(angles.Data2())+_STCP*Sin(angles.Data1())*Cos(angles.Data2())+_STSP*Sin(angles.Data1())*Sin(angles.Data2()));

    return r.SumOfSqr();
  }

  //: Evaluate cost function at pose vector 'X'.
  //  'X = (theta, phi)' is a two-dimensional vector containing the pan angle 'theta' and the tilt angle 'phi' in radians.
  VectorC AAMPoseEstimateCostFunctionBodyC::Apply(const VectorC &X) const {
    VectorC ret(1);
    ret[0] = Cost(X);
    return ret;
  }

}
