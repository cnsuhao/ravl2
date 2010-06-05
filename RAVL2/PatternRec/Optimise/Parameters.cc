// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: Parameters.cc 6651 2008-03-05 14:16:39Z craftit $"
//! lib=Optimisation
//! file="Ravl/PatternRec/Optimise/Parameters.cc"

#include "Ravl/PatternRec/Parameters.hh"
#include "Ravl/SArray1dIter5.hh"
#include "Ravl/Random.hh"
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
      _mask(steps.Size()),
      m_cacheDirty(true)
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
      _mask(mask),
      m_cacheDirty(true)
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
     _mask(nparams),
      m_cacheDirty(true)
  {
    _minP.Fill(0);
    _maxP.Fill(1);
    _steps.Fill(1);
    _mask.Fill(0);
    _constP.Fill(0);
  }
  
  ParametersBodyC::ParametersBodyC (istream &in)
    : m_cacheDirty(true)
  { in >> _minP >> _maxP >> _constP >> _steps >> _mask; }
  
  ParametersBodyC::ParametersBodyC (const ParametersBodyC &oth)
    :_minP(oth._minP.Copy()),
     _maxP(oth._maxP.Copy()),
     _constP(oth._constP.Copy()),
     _steps(oth._steps.Copy()),
     _mask(oth._mask.Copy()),
     m_cacheDirty(true)
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
    m_cacheDirty = true;
  }
  
  void ParametersBodyC::SetConstP (const VectorC &constP)
  { 
    _constP = constP.Copy(); 
    m_cacheDirty = true;
  }
  
  void ParametersBodyC::UpdateCache() const {
    UIntT maskSum = _mask.Sum();
    if(m_stepsP.Size() != maskSum)
      m_stepsP = SArray1dC<IntT>(maskSum);
    
    if(m_transP2X.Rows() != maskSum || m_transX2P.Cols() != _mask.Size())
      m_transP2X = MatrixC(maskSum,_mask.Size());
    m_transP2X.Fill (0);
    
    if(m_transX2P.Rows() != _mask.Size() || m_transX2P.Cols() != maskSum)
        m_transX2P = MatrixC(_mask.Size(),maskSum);
    m_transX2P.Fill (0);
    
    if(m_constP.Size() != _mask.Size())
      m_constP = VectorC(_mask.Size());
    m_constP.Fill (0);
    
    IndexC counter = 0;
    for (SArray1dIterC<IntT> it (_mask); it; it++) {
      if (*it == 1) {
        m_transX2P[it.Index()][counter] = 1;      
        m_transP2X[counter][it.Index()] = 1;
        m_stepsP[counter] = _steps[it.Index()];
        counter++;
      } else {
        m_constP[it.Index()] = _constP[it.Index()];
      }
    }
    RavlAssert(counter == maskSum);
    
    m_minX = m_transP2X * _minP;
    m_maxX = m_transP2X * _maxP;
    m_startX = m_transP2X * _constP;
    
    m_cacheDirty = false;
  }
  
  
  //////////////////////////////////
  //: Setup paramiter p.
  
  void ParametersBodyC::Setup(IndexC p,RealT min,RealT max,IntT steps,IntT mask)
  {
    _minP[p] = min;
    _maxP[p] = max;
    _steps[p] = steps;
    _mask[p] = mask;
    m_cacheDirty = true;
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
    m_cacheDirty = true;
  }
  
  
  void ParametersBodyC::Save (ostream &out) const
  {
    out << _minP << "\n" << _maxP << "\n" << _constP << "\n";
    out << _steps << "\n" << _mask << "\n";
  }


  //: Generate a random positon in the parameter space.
  
  VectorC ParametersBodyC::Random() {
    VectorC ret(_minP.Size());
    for(SArray1dIter5C<RealT,RealT,RealT,RealT,IntT> it(ret,_minP,_maxP,_constP,_mask);it;it++) {
      if(it.Data5() == 0) { // Use constant value ?
        it.Data1() = it.Data4();
        continue;
      }
      RealT diff = it.Data3() - it.Data2();
      it.Data1() = it.Data2() + diff * Random1();
    }
    return ret;
  }

  
  
}
