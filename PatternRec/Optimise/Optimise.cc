// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#include "Ravl/PatternRec/Optimise.hh"
#include "Ravl/PatternRec/CostInvert.hh"
#include "Ravl/VirtualConstructor.hh"
//! rcsid="$Id$"
//! lib=Optimisation
//! file="Ravl/PatternRec/Optimise/Optimise.cc"

namespace RavlN {

  OptimiseBodyC::OptimiseBodyC (const StringC &name)
    :_name(name)
  {
  }
  
  OptimiseBodyC::OptimiseBodyC (const StringC &name, istream &)
    :_name(name)
  {
  }
  
  VectorC OptimiseBodyC::MinimalX (const CostC &domain, RealT &minimumCost) const
  {
    RealT startCost = domain.Cost(domain.StartX());
    return MinimalX (domain,startCost,minimumCost);
  }
  
  VectorC OptimiseBodyC::MinimalX (const CostC &domain, RealT startCost, RealT &minimumCost) const
  {
    return MinimalX (domain,minimumCost);
  }
  
  VectorC OptimiseBodyC::MaximalX (const CostC &domain, RealT &maximumCost) const
  {
    CostInvertC inverse (domain);
    VectorC minimumX = MinimalX (inverse,maximumCost);
    maximumCost = -maximumCost;
    return minimumX;
  }
  
  VectorC OptimiseBodyC::MaximalX (const CostC &domain, RealT startCost, RealT &maximumCost) const
  {
    CostInvertC inverse (domain);
    VectorC minimumX = MinimalX (inverse,startCost,maximumCost);
    maximumCost = -maximumCost;
    return minimumX;
  }
  
  const StringC OptimiseBodyC::GetInfo () const
  {
    //StrOStreamC stream;
    //stream << "Numerical Optimization Base Class Type: " << _name;
    //stream.String();
    return StringC("Numerical Optimization Base Class Type: ") + _name;
  }
  
  const StringC OptimiseBodyC::GetName () const
  {
    return _name;
  }
  
  bool OptimiseBodyC::Save (ostream &out) const
  {
    return RCBodyVC::Save (out);
  }
  
  OptimiseC::OptimiseC ()
  {
  }
  
  OptimiseC::OptimiseC (istream &in)
    : RCHandleVC<OptimiseBodyC>(RAVL_VIRTUALCONSTRUCTOR(in,OptimiseBodyC))
  {
    CheckHandleType(Body());
  }
  
  OptimiseC::OptimiseC (OptimiseBodyC &oth)
    :RCHandleVC<OptimiseBodyC> (oth)
  {}
  
}





