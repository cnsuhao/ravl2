// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: OptimiseDescent.cc 5398 2006-03-09 16:55:13Z craftit $"
//! lib=Optimisation
//! file="Ravl/PatternRec/Optimise/OptimiseDescent.cc"

#include "Ravl/PatternRec/OptimiseDescent.hh"
#include "Ravl/StrStream.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

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
  VectorC OptimiseDescentBodyC::MinimalX (const CostC &domain, RealT &minimumCost) const
  {
    VectorC dYdX;                            // Jacobian or gradient at location
    UIntT counter = 0;
    VectorC iterX = domain.StartX();         // Copy start into temporary var;
    RealT stepSize = 1;
    
#if 0
    cerr << "ClipX=" << domain.ClipX (iterX) << "\n";
    cerr << "    X=" << iterX << "\n";
#endif
#if USE_BRENT
    ParametersC parameters1d(1);
    OptimiseBrentC _brent(_iterations, _tolerance);
#endif
    
    UIntT maxSteps = 15;  // Allow quite a few steps on the first iteration to get the scale right.
    RealT currentCost = domain.Cost (iterX);      // Evaluate current cost
    
    do {
      // perform something like a binary search along the direction of steepest
      // descent to find a local minima
      //cout << "X=" << X << "\tcurrentcost = " << iterCost <<  "\n";
      RealT startCost = currentCost;
      dYdX = domain.Jacobian(iterX).SliceRow(0); // Determine current Jacobian
      dYdX /= dYdX.Modulus(); // Normalise to unit step.
      //cerr << "Jacobian=" << dYdX << "\n";
      VectorC Xstep;
      VectorC Xat = iterX;
      for (UIntT i = 0; i < maxSteps; i++) {        
	Xstep = domain.ClipX (Xat -(dYdX * stepSize));   // Step in dir of steepest descent
	RealT stepCost = domain.Cost (Xstep);// Evaluate cost after step
	if (stepCost < currentCost) {        // If cost is best so far
	  iterX = Xstep;                     // then keep going with bigger step
	  currentCost = stepCost;
	  stepSize *= 2;                     // Next time try twice as far.
	} else {                             // otherwise go back a bit
	  stepSize *= 0.3333;                 // Try a smaller thats not a multple of 2.
	}
      }
      
      // Check termination condition.
      if(2.0*(startCost - currentCost) < _tolerance * Abs(currentCost + startCost))
        break;
      
      maxSteps = 4; // Only 4 after the first iteration.
    } while (counter++ < _iterations); 
    ONDEBUG(cerr << "Terminated after " << counter << " iterations. MinCost=" << currentCost << "\n");
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
