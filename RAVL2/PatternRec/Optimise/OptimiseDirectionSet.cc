// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: OptimiseDirectionSet.cc 5349 2006-02-16 10:29:10Z omn-crida $"
//! lib=Optimisation
//! file="Ravl/PatternRec/Optimise/OptimiseSobol.cc"

#include "Ravl/PatternRec/OptimiseDirectionSet.hh"
#include "Ravl/StrStream.hh"

namespace RavlN {

  OptimiseDirectionSetBodyC::OptimiseDirectionSetBodyC (const SArray1dC<VectorC> &initState)
    : OptimiseBodyC("OptimiseDirectionSetBodyC"),
      state(initState)
  {}
  
  OptimiseDirectionSetBodyC::OptimiseDirectionSetBodyC (istream &in)
    : OptimiseBodyC("OptimiseDirectionSetBodyC",in)
  {}
  
  // Random optimizer with uniform density. Randomly samples the parameter
  // space to find the minimum cost position.
  
  VectorC OptimiseDirectionSetBodyC::MinimalX (const CostC &domain) const
  {
    VectorC start = domain.StartX();
    UIntT n = start.Size();
    SArray1dC<VectorC> u(n);
    
    // Initialise u.
    for(UIntT i = 0;i < u;i++) {
      u.Fill(0);
      u[i] = 1;
    }
    
    RavlAssert(0);
    //return domain.ConvertX2P (currentX);     // Return final estimate
  }
  
  
  //: Find minimum along direction 'dir' from start, 
  
  VectorC OptimiseDirectionSetBodyC::FindMin(const VectorC &start,const VectorC &dir) {
    VectorC P = start;
    RealT p1 = domain.Cost (P + dir);
    RealT p2 = domain.Cost (P);
    RealT p3 = domain.Cost (P - dir);
    
    
    return at;
  }

  const StringC OptimiseDirectionSetBodyC::GetInfo () const
  {
    StrOStreamC stream;
    stream << OptimiseBodyC::GetInfo () << "\n";
    stream << "DirectionSet parameter space search optimisation. ";
    return stream.String();
  }
  
  bool OptimiseDirectionSetBodyC::Save (ostream &out) const {
    OptimiseBodyC::Save (out);
    return true;
  }
  
}
