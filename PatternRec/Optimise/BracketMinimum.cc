// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#include "Ravl/PatternRec/BracketMinimum.hh"
//! rcsid="$Id$"
//! lib=Optimisation
//! file="Ravl/PatternRec/Optimise/BracketMinimum.cc"

namespace RavlN {

  void BracketMinimum(CostFunction1dC &cost) {
    ParametersC parameters(1);
    const RealT gold = 1.618034;
    const RealT small = 1.0e-20;
    const RealT glimit = 100.0;
    VectorC vax(1);
    RealT &x0 = vax[0];
    x0 = 0.0;
    VectorC vbx(1);
    RealT &x1 = vbx[0];
    x1 = 1.0;
    VectorC vcx(1);
    RealT &x2 = vcx[0];
    VectorC vux(1);
    RealT &xn = vux[0];
    RealT fxn;
    RealT fx0 = cost.Cost(vax); 
    RealT fx1 = cost.Cost(vbx);
    if (fx1 > fx0) {
      RealT t;
      t = x0; x0 = x1; x1 = t;
      t = fx0; fx0 = fx1; fx1 = t;
    }
    x2 = x1 + gold * (x1 - x0);
    RealT fx2 = cost.Cost(vcx);
    while (fx1 > fx2) {
      RealT r = (x1 - x0) * (fx1 - fx2);
      RealT q = (x1 - x2) * (fx1 - fx0);
      xn = x1 - ((x1 - x2) * q - (x1 - x0) * r) / (2.0 * Sign(Max(fabs(q-r),small),q-r));
      RealT xlim = x1 + glimit * (x2 - x1);
      if ((x1 - xn) * (xn - x2) > 0.0) {
        fxn = cost.Cost(vux);
        if (fxn < fx2) {
          x0 = x1;
          x1 = xn;
          parameters.Setup(0, x0, x2, 1, x1);
          cost.SetParameters(parameters);
          return;
        }
        else
          if (fxn > fx1) {
            x2 = xn;
            parameters.Setup(0, x0, x2, 1, x1);
            cost.SetParameters(parameters);
            return;
          }
        xn = x2 + gold * (x2 - x1);
        fxn = cost.Cost(vux);
      }
      else
        if ((x2 - xn) * (xn - xlim) > 0.0) {
          fxn = cost.Cost(vux);
          if (fxn < fx2) {
            x1 = x2; x2 = xn; xn = xn+gold*(xn-x2);
            fx1 = fx2; fx2 = fxn; fxn = cost.Cost(vux);
          }
        }
        else
          if ((xn - xlim) * (xlim - x2) >= 0.0) {
            xn = xlim;
            fxn = cost.Cost(vux);
          }
          else {
            xn = x2 + gold * (x2 - x1);
            fxn = cost.Cost(vux);
          }
      x0 = x1; x1 = x2; x2 = xn;
      fx0 = fx1; fx1 = fx2; fx2 = fxn;
    }
  }

}
