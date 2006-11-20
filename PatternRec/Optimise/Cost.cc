// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#include "Ravl/PatternRec/Cost.hh"
//! rcsid="$Id$"
//! lib=Optimisation
//! file="Ravl/PatternRec/Optimise/Cost.cc"

//////////////////////////////////////////
//: Constructor
//!param: name       - derived class type name

namespace RavlN {
  
  CostBodyC::CostBodyC (const ParametersC &parameters)
    : _parameters(parameters)
  {
    InputSize (_parameters.MinX().Size());
    OutputSize (1);
  }
  
  CostBodyC::CostBodyC (istream &in)
    : Function1BodyC(in),
      _parameters(in)
  {}
  
  //: Apply function to 'data'
  
  VectorC CostBodyC::Apply(const VectorC &X) const {
    VectorC Y (1);
    Y[0] = Cost (X);
    return Y;    
  }
  
  VectorC CostBodyC::Evaluate (const VectorC &X) const
  {
    VectorC Y (1);
    Y[0] = Cost (X);
    return Y;
  }
  
  void CostBodyC::SetMask (const SArray1dC<IntT> &mask)
  {
    _parameters.SetMask (mask);
    InputSize (_parameters.MinX().Size());
  }
  
  void CostBodyC::SetConstP (const VectorC &constP)
  { _parameters.SetConstP (constP); }
  
  const VectorC CostBodyC::MinX () const
  { return _parameters.MinX (); }
  
  const VectorC CostBodyC::MaxX () const
  { return _parameters.MaxX (); }
  
  const VectorC CostBodyC::StartX () const
  { return _parameters.StartX (); }
  
  VectorC CostBodyC::ConvertX2P (const VectorC &X) const
  { return _parameters.TransX2P()*X + _parameters.ConstP(); }

  VectorC CostBodyC::ClipX (const VectorC &X) const
  {
    VectorC minX = MinX();
    VectorC maxX = MaxX();
    VectorC outX = X.Copy();
    for (IndexC i = 0; i < X.Size(); i++) {
      if (X[i] < minX[i]) outX[i] = minX[i];
      if (X[i] > maxX[i]) outX[i] = maxX[i];
    }
    return outX;
  }
  
  const SArray1dC<IntT> CostBodyC::Steps () const
  { return _parameters.Steps (); }
  
  const ParametersC & CostBodyC::GetParameters () const
  { return _parameters; }

  void CostBodyC::SetParameters (const ParametersC &parameters)
  {
    InputSize (parameters.MinX().Size());
    _parameters = parameters;
  }
  
  const MatrixC CostBodyC::TransP2X () const
  { return _parameters.TransP2X (); }
  
  const MatrixC CostBodyC::TransX2P () const
  { return _parameters.TransX2P (); }
  
  const VectorC CostBodyC::ConstP () const
  { return _parameters.ConstP (); }
  
  bool CostBodyC::Save (ostream &out) const
  {
    FunctionBodyC::Save (out);
    _parameters.Save (out);
    return true;
  }
  
  
}
