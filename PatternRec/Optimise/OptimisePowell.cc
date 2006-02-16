// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=Optimisation
//! file="Ravl/PatternRec/Optimise/OptimisePowell.cc"

#include "Ravl/PatternRec/OptimisePowell.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/PatternRec/CostFunction1d.hh"
#include "Ravl/PatternRec/BracketMinimum.hh"
#include "Ravl/SArray1dIter4.hh"

namespace RavlN {

  OptimisePowellBodyC::OptimisePowellBodyC (UIntT iterations, RealT tolerance)
    :OptimiseBodyC("OptimisePowellBodyC"),
     _iterations(iterations),
     _tolerance(tolerance),
     _brent(iterations,tolerance)
  {}
  
  OptimisePowellBodyC::OptimisePowellBodyC (istream &in)
    :OptimiseBodyC("OptimisePowellBodyC",in)
  {
    in >> _iterations;
  }
  
  // ------------------------------------------------------------------------
  // **********  OptimalX    ************************************************
  // ------------------------------------------------------------------------
  //
  // Powell optimiser. Keeps a set of orthogonal directions and searches along
  // each one in turn for the minimum. The final point is then used to create
  // a new direction which replaces one of the existing ones and the process is
  // repeated.
  //
  VectorC OptimisePowellBodyC::MinimalX (const CostC &domain, RealT &minimumCost) const
  {
    VectorC minP(1),maxP(1);
    SArray1dC<IntT> steps(1);
    minP[0] = -10.0;
    maxP[0] = 10.0;
    steps[0] = 1;
    ParametersC parameters1d(minP,maxP,steps);

    VectorC P = domain.StartX();
    IntT numDim = P.Size();
    SArray1dC<VectorC> Di(numDim);
    // initialise directions to basis unit vectors
    for (SArray1dIterC<VectorC> it(Di); it; it++) {
      *it = VectorC(numDim);
      it->Fill(0.0);
      (*it)[it.Index()] = 1.0;
    }
    
    IndexC indexOfBiggest;
    RealT valueOfBiggest,fP,t;
    VectorC Plast;
    VectorC Psameagain;
    VectorC Pdiff;
    minimumCost = domain.Cost(P);
    Plast = P.Copy(); // Make a copy of current best guess.
    for (UIntT iter = 0; iter < _iterations; iter++) {
      fP = minimumCost;
      indexOfBiggest = 0;
      valueOfBiggest = 0.0;
      for (SArray1dIterC<VectorC> it(Di); it; it++) { // Go through direction vectors.
#if 1
	// Find the domain limits along the direction vector.
	
	RealT min = -RavlConstN::maxReal;
	RealT max = RavlConstN::maxReal;
	for(SArray1dIter4C<RealT,RealT,RealT,RealT> lit(*it,P,domain.MinX(),domain.MaxX());lit;lit++) {
	  if(lit.Data1() == 0.0)
	    continue; // Avoid division by zero.
	  RealT maxv = (lit.Data3() - lit.Data2()) / lit.Data1();
	  RealT minv = (lit.Data4() - lit.Data2()) / lit.Data1();
	  if(minv > maxv)
	    Swap(minv,maxv);
	  if(max > maxv)
	    max = maxv;
	  if(minv > min)
	    min = minv;
	}
	//_point + _direction * X[0];
	parameters1d.Setup(0,min,max,1000);
#endif
	
	// Minimise along line.
	
        RealT fPlast = minimumCost;
        CostFunction1dC cost1d(parameters1d,domain,P,*it);
        BracketMinimum(cost1d);
        P = cost1d.Point(_brent.MinimalX(cost1d,minimumCost));
        if (fabs(fPlast - minimumCost) > valueOfBiggest) {
          valueOfBiggest = fabs(fPlast - minimumCost);
          indexOfBiggest = it.Index();
        }
      }
      RealT fPdiff = fP-minimumCost;
      if (2.0*fabs(fPdiff) <= _tolerance*(fabs(fP)+fabs(minimumCost)))
        break;
      // check if we should continue in the same direction
      Pdiff = P - Plast;
      Psameagain = P + Pdiff;
      Plast = P.Copy();
      RealT fPsameagain = domain.Cost(Psameagain);
      // if it has still improved in the same direction
      if (fPsameagain < fP) {
        t = 2.0 * (fP-2.0*minimumCost+fPsameagain)+Sqr(fPdiff-valueOfBiggest)-valueOfBiggest*Sqr(fP-fPsameagain);
        if (t < 0.0) {
          CostFunction1dC cost1d(parameters1d,domain,P,Pdiff);
          BracketMinimum(cost1d);
          P = cost1d.Point(_brent.MinimalX(cost1d,minimumCost));
          Di[indexOfBiggest] = Di[numDim-1].Copy();
          Di[numDim-1] = Pdiff.Copy();
        }
      }
    }
    return P;
  }
  
  const StringC OptimisePowellBodyC::GetInfo () const
  {
    StrOStreamC stream;
    stream << OptimiseBodyC::GetInfo () << "\n";
    stream << "Powell optimization algorithm. Iterations = " << _iterations;
    return stream.String();
  }
  
  bool OptimisePowellBodyC::Save (ostream &out) const
  {
    OptimiseBodyC::Save (out);
    out << _iterations << "\n";
    return true;
  }
  
}
