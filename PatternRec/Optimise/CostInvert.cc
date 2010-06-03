// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#include "Ravl/PatternRec/CostInvert.hh"
#include "Ravl/StrStream.hh"
//! rcsid="$Id: CostInvert.cc 3073 2003-06-13 07:18:32Z craftit $"
//! lib=Optimisation
//! file="Ravl/PatternRec/Optimise/CostInvert.cc"

namespace RavlN {

  CostInvertBodyC::CostInvertBodyC (const CostC &cost)
    :CostBodyC(cost.GetParameters()),
     _cost(cost)
  {
  }
  
  CostInvertBodyC::CostInvertBodyC (istream &in)
    :CostBodyC(in),
     _cost(in)
  {
  }
  
  RealT CostInvertBodyC::Cost (const VectorC &X) const
  {
    return - _cost.Cost (X);
  }
  
  MatrixC CostInvertBodyC::Jacobian (const VectorC &X) const
  {
    return _cost.Jacobian (X) * -1.0;
  }
  
  bool CostInvertBodyC::Save (ostream &out) const
  {
    CostBodyC::Save (out);
    _cost.Save (out);
    return true;
  }
  
}
