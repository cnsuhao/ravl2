// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#include "Ravl/PatternRec/OptimiseDescent.hh"
#include "Ravl/StrStream.hh"
//! rcsid="$Id$"
//! lib=Optimisation

namespace RavlN {

  OptimiseDescentBodyC::OptimiseDescentBodyC (UIntT iterations, RealT tolerance)
    :OptimiseBodyC("OptimiseDescentBodyC"),
     _iterations(iterations),
     _tolerance(tolerance)
  {
  }
  
  OptimiseDescentBodyC::OptimiseDescentBodyC (istream &in)
    :OptimiseBodyC("OptimiseDescentBodyC",in)
  {
    in >> _iterations;
  }
  
  // ------------------------------------------------------------------------
  // **********  OptimalX    ************************************************
  // ------------------------------------------------------------------------
  //
  // Steepest descent optimizer. From each point determines the direction of
  // steepest descent and proceeds along that vector by a certain amount. The
  // amount is initially chosen as the magnitude of the gradient and is 
  // halved until the cost is less than at the current location. The search 
  // quits when the change in cost becomes small or more than _iterations 
  // steps have been taken.
  //
  VectorC OptimiseDescentBodyC::MinimalX (const CostC &domain)
  {
    VectorC X = domain.StartX().Copy();      // Copy start into temporary var
    VectorC dYdX;                            // Jacobian or gradient at location
    UIntT counter = 0;
    VectorC iterX = X.Copy();
    do {
      // perform something like a binary search along the direction of steepest
      // descent to find a local minima
      X = iterX.Copy();
      RealT iterCost = domain.Cost (X);      // Evaluate current cost
      cout << "X=" << X << "\tcurrentcost = " << iterCost <<  "\n";
      RealT currentCost = iterCost;
      dYdX = domain.Jacobian(X).SliceRow(0); // Determine current Jacobian

      VectorC Xstep;
      for (UIntT i = 0; i < 10; i++) {
	Xstep = domain.ClipX (iterX-dYdX);   // Step in dir of steepest descent
	RealT stepCost = domain.Cost (Xstep);// Evaluate cost after step
	if (stepCost < currentCost) {        // If cost is best so far
	  iterX = Xstep;                     // then keep going with bigger step
	  currentCost = stepCost;
	  dYdX *= 2;
	}
	else {                               // otherwise go back a bit
	  dYdX *= 0.25;
	}
      }
    } while (dYdX.Modulus () > _tolerance && counter++ < _iterations && VectorC(iterX - X).Modulus () > _tolerance); 
    cout << "\n";
    return domain.ConvertX2P (X);            // Return final estimate
  }
  
  const StringC OptimiseDescentBodyC::GetInfo () const
  {
    StrOStreamC stream;
    stream << OptimiseBodyC::GetInfo () << "\n";
    stream << "Gradient descent optimization algorithm. Iterations = " << _iterations;
    return stream.String();
  }
  
  bool OptimiseDescentBodyC::Save (ostream &out) const
  {
    OptimiseBodyC::Save (out);
    out << _iterations << "\n";
    return true;
  }
  
}
