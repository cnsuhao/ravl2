// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#include "Ravl/PatternRec/CostFunction1d.hh"
//! rcsid="$Id$"
//! lib=Optimisation
//! file="Ravl/PatternRec/Optimise/CostFunction.cc"

namespace RavlN {

  CostFunction1dBodyC::CostFunction1dBodyC (const ParametersC parameters,
                                            const CostC &cost,
                                            const VectorC &point,
                                            const VectorC &direction)
    : CostBodyC(parameters),
      _cost(cost),
      _point(point),
      _direction(direction)
  {
    RavlAssert (_point.Size() == _direction.Size() == _cost.OutputSize());
  }
  
  CostFunction1dBodyC::CostFunction1dBodyC (istream &in)
    :CostBodyC(in),
     _cost(in)
  {
    in >> _point >> _direction;
  }
  
  RealT CostFunction1dBodyC::Cost (const VectorC &X) const
  {
    return _cost.Cost (Point(X));
  }
  
  VectorC CostFunction1dBodyC::Point (const VectorC &X) const
  {
    return _point + _direction * X[0];
  }
    
  bool CostFunction1dBodyC::Save (ostream &out) const
  {
    CostBodyC::Save (out);
    _cost.Save (out);
    out << _point << "\n" << _direction << "\n";
    return true;
  }
  
}
