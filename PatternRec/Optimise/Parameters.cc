// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=Optimisation

#include "Ravl/PatternRec/Parameters.hh"
#include "Ravl/config.h"
#include <stdlib.h>

namespace RavlN {

  ParametersBodyC::ParametersBodyC (const VectorC &minP,
				    const VectorC &maxP,
				    const SArray1dC<IntT> &steps)
    : _minP(minP),
      _maxP(maxP),
      _constP(steps.Size()),
      _steps(steps),
      _mask(steps.Size())
  {
    RavlAssertMsg (minP.Size() == maxP.Size() && minP.Size() == steps.Size(), "Error: all arguments for parameters must have same dimension");
    _mask.Fill(1);
    _constP.Fill(0);
  }
  
  ParametersBodyC::ParametersBodyC (const VectorC &minP,
				    const VectorC &maxP,
				    const SArray1dC<IntT> &steps,
				    const SArray1dC<IntT> &mask)
    : _minP(minP),
      _maxP(maxP),
      _constP(steps.Size()),
      _steps(steps),
      _mask(mask)
  {
    RavlAssertMsg (minP.Size() == maxP.Size() && minP.Size() == steps.Size() && minP.Size() == mask.Size(), "Error: all arguments for parameters must have same dimension");
    _constP.Fill(0);
  }
  
  /////////////////////////////////////////
  //: Constructor.
  // This setsup nparams with defaults settings of :
  // minP=0 maxP=1 Steps=1 mask=0 (constP = 0)
  
  ParametersBodyC::ParametersBodyC (SizeT nparams)
    :_minP(nparams),
     _maxP(nparams),
     _constP(nparams),
     _steps(nparams),
     _mask(nparams)
  {
    _minP.Fill(0);
    _maxP.Fill(1);
    _steps.Fill(1);
    _mask.Fill(0);
    _constP.Fill(0);
  }
  
  ParametersBodyC::ParametersBodyC (istream &in)
  { in >> _minP >> _maxP >> _constP >> _steps >> _mask; }
  
  ParametersBodyC::ParametersBodyC (const ParametersBodyC &oth)
    :_minP(oth._minP.Copy()),
     _maxP(oth._maxP.Copy()),
     _constP(oth._constP.Copy()),
     _steps(oth._steps.Copy()),
     _mask(oth._mask.Copy())
  {}
  
  ParametersBodyC & ParametersBodyC::Copy () const
  { return *(new ParametersBodyC (*this)); }
  
  void ParametersBodyC::SetMask (const SArray1dC<IntT> &mask)
  {
    if (mask.Size() != _mask.Size()) {
      cerr << "Error: parameter mask must be same size!\n";
      exit(1);
    }
    _mask = mask;
  }
  
  void ParametersBodyC::SetConstP (const VectorC &constP)
  { _constP = constP.Copy(); }
  
  const VectorC ParametersBodyC::MinX () const
  { return TransP2X() * _minP; }
  
  const VectorC ParametersBodyC::MaxX () const
  { return TransP2X() * _maxP; }
  
  const SArray1dC<IntT> ParametersBodyC::Steps () const
  {
    SArray1dC<IntT> steps (_mask.Sum());
    IndexC counter = 0;
    for (SArray1dIterC<IntT> it (_mask); it; it++)
      if (*it == 1)
	steps[counter++] = _steps[it.Index()];
    return steps;
  }
  
  const MatrixC ParametersBodyC::TransP2X () const
  {
    MatrixC P2X (_mask.Sum(),_mask.Size());
    P2X.Fill (0);
    IndexC counter = 0;
    for (SArray1dIterC<IntT> it (_mask); it; it++)
      if (*it == 1)
	P2X[counter++][it.Index()] = 1;
    return P2X;
  }
  
  const MatrixC ParametersBodyC::TransX2P () const
  {
    MatrixC X2P (_mask.Size(),_mask.Sum());
    X2P.Fill (0);
    IndexC counter = 0;
    for (SArray1dIterC<IntT> it (_mask); it; it++)
      if (*it == 1)
	X2P[it.Index()][counter++] = 1;
    return X2P;
  }
  
  const VectorC ParametersBodyC::ConstP () const
  {
    VectorC constP (_mask.Size());
    constP.Fill (0);
    for (SArray1dIterC<IntT> it (_mask); it; it++)
      if (*it != 1)
	constP[it.Index()] = _constP[it.Index()];
    return constP;
  }
  
  const VectorC ParametersBodyC::StartX () const
  { return TransP2X() * _constP; }
  
  
  //////////////////////////////////
  //: Setup paramiter p.
  
  void ParametersBodyC::Setup(IndexC p,RealT min,RealT max,IntT steps,IntT mask)
  {
    _minP[p] = min;
    _maxP[p] = max;
    _steps[p] = steps;
    _mask[p] = mask;
  }
  
  //////////////////////////////////
  //: Setup paramiter p, and constant value.
  
  void ParametersBodyC::Setup(IndexC p,RealT min,RealT max,IntT steps,RealT constV,IntT mask) 
  {
    _minP[p] = min;
    _maxP[p] = max;
    _steps[p] = steps;
    _mask[p] = mask;
    _constP[p] = constV;
  }
  
  
  void ParametersBodyC::Save (ostream &out) const
  {
    out << _minP << "\n" << _maxP << "\n" << _constP << "\n";
    out << _steps << "\n" << _mask << "\n";
  }
  
  ParametersC::ParametersC (const VectorC &minP, 
			    const VectorC &maxP, 
			    const SArray1dC<IntT> &steps)
    : RCHandleC<ParametersBodyC>(*new ParametersBodyC (minP,maxP,steps))
  {}
  
  ParametersC::ParametersC (const VectorC &minP, 
			    const VectorC &maxP, 
			    const SArray1dC<IntT> &steps,
			    const SArray1dC<IntT> &mask)
    : RCHandleC<ParametersBodyC>(*new ParametersBodyC (minP,maxP,steps,mask))
  {}
  
  ParametersC::ParametersC (SizeT nparams)
    : RCHandleC<ParametersBodyC>(*new ParametersBodyC (nparams))
  {}
  
  ParametersC::ParametersC (istream &in)
    : RCHandleC<ParametersBodyC>(*new ParametersBodyC (in))
  {}
  
}
