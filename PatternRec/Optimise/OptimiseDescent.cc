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
//! file="Ravl/PatternRec/Optimise/OptimiseDescent.cc"

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
  VectorC OptimiseDescentBodyC::MinimalX (const CostC &domain, RealT &minimumCost)
  {
    VectorC dYdX;                            // Jacobian or gradient at location
    UIntT counter = 0;
    VectorC iterX = domain.StartX();         // Copy start into temporary var;
    RealT gradSize = 0;
    RealT stepSize = 1;
#if 0
    cerr << "ClipX=" << domain.ClipX (iterX) << "\n";
    cerr << "    X=" << iterX << "\n";
#endif
    UIntT maxSteps = 15;
    RealT currentCost = domain.Cost (iterX);      // Evaluate current cost
    do {
      // perform something like a binary search along the direction of steepest
      // descent to find a local minima
      //cout << "X=" << X << "\tcurrentcost = " << iterCost <<  "\n";
      dYdX = domain.Jacobian(iterX).SliceRow(0); // Determine current Jacobian
      dYdX /= dYdX.Modulus(); // Normalise to unit step.
      //cerr << "Jacobian=" << dYdX << "\n";
      VectorC Xstep;
      for (UIntT i = 0; i < maxSteps; i++) {
	Xstep = domain.ClipX (iterX-(dYdX * stepSize));   // Step in dir of steepest descent
	RealT stepCost = domain.Cost (Xstep);// Evaluate cost after step
	if (stepCost < currentCost) {        // If cost is best so far
	  iterX = Xstep;                     // then keep going with bigger step
	  currentCost = stepCost;
	  stepSize *= 2;
	} else {                               // otherwise go back a bit
	  stepSize *= 0.25;
	}
      }
      maxSteps = 4; // Only 4 after the first iteration.
      gradSize = dYdX.Modulus ();
      //      cerr << "GradSize=" << gradSize << " StepSize=" << stepSize << "\n";
    } while (gradSize > _tolerance && counter++ < _iterations &&  stepSize > _tolerance); 
    //cout << "\n";
    minimumCost = currentCost;
    return domain.ConvertX2P (iterX);            // Return final estimate
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
