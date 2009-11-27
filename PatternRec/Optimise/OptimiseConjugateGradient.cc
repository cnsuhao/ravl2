// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=Optimisation
//! file="Ravl/PatternRec/Optimise/OptimiseConjugateGradient.cc"

#include "Ravl/PatternRec/OptimiseConjugateGradient.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/SArray1dIter5.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/SArray1dIter3.hh"
#include "Ravl/PatternRec/OptimisePowell.hh"
#include "Ravl/PatternRec/CostFunction1d.hh"
#include "Ravl/PatternRec/BracketMinimum.hh"


#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {

  OptimiseConjugateGradientBodyC::OptimiseConjugateGradientBodyC (UIntT iterations, RealT tolerance,bool useBacketMinimum)
    : OptimiseBodyC("OptimiseConjugateGradientBodyC"),
      _iterations(iterations),
      _tolerance(tolerance),
      _useBracketMinimum(useBacketMinimum)
  {
  }
  
  OptimiseConjugateGradientBodyC::OptimiseConjugateGradientBodyC (istream &in)
    : OptimiseBodyC("OptimiseConjugateGradientBodyC",in)
  {
    in >> _iterations;
  }
  
  static void SetupLimits(const VectorC &dir,const VectorC &P,const CostC &domain,ParametersC &parameters1d) {
    // Find the domain limits along the direction vector.
    
    //RealT min = -RavlConstN::maxReal;
    RealT min = 0; // We only ever want to go down hill.
    RealT max = RavlConstN::maxReal;
    IntT steps = 0;
    for(SArray1dIter5C<RealT,RealT,RealT,RealT,IntT> lit(dir,P,domain.MinX(),domain.MaxX(),domain.Steps());lit;lit++) {
      if(lit.Data1() == 0.0)
        continue; // Avoid division by zero.
      RealT maxv = (lit.Data3() - lit.Data2()) / lit.Data1(); // Limit for MinX
      RealT minv = (lit.Data4() - lit.Data2()) / lit.Data1(); // Limit for MaxX
      if(minv > maxv) // The direction vector could have a negative value, so invert if needed.
        Swap(minv,maxv);
      if(max > maxv) // Pull down maximum if limited
        max = maxv;
      if(minv > min) // Pull up minimum if limited
        min = minv;
      steps += lit.Data5();
    }
    steps /= domain.Steps().Size();
    if(steps < 3) steps = 3; // Check there;s actually some space to optimise in.
    
    //Point in full space to evaulate is given by: _point + _direction * X[0];  Where X[0] is the paramiter we're optimising.
    parameters1d.Setup(0,min,max,steps);
  }
  
  
  // ------------------------------------------------------------------------
  // **********  OptimalX    ************************************************
  // ------------------------------------------------------------------------
  //
  
  VectorC OptimiseConjugateGradientBodyC::MinimalX (const CostC &domain, RealT &minimumCost) const
  {
    UIntT counter = 0;
    VectorC iterX = domain.StartX();         // Copy start into temporary var;
    
#if 0
    cerr << "ClipX=" << domain.ClipX (iterX) << "\n";
    cerr << "    X=" << iterX << "\n";
#endif
    
    ParametersC parameters1d(1);
    OptimiseBrentC _brent(_iterations, _tolerance);
    RealT currentCost = domain.Cost (iterX);      // Evaluate current cost
    
    VectorC dYdX = domain.Jacobian1(iterX) * -1.0; // Determine current Jacobian
    VectorC gdYdX = dYdX.Copy();
    VectorC hdYdX = dYdX.Copy();
    
    do {
      SetupLimits(dYdX,iterX,domain,parameters1d);
      
      // Setup minimisation along line.
      
      CostFunction1dC cost1d(parameters1d, // Limits for paramiters.
                             domain,       // Cost function we're trying to minimise.
                             iterX,        // Current best position.
                             dYdX          // Direction we wish to optimise along.
                             );
      
      if (_useBracketMinimum) {
        BracketMinimum(cost1d);
        iterX = cost1d.Point(_brent.MinimalX(cost1d,currentCost,minimumCost));
      } else
        iterX = cost1d.Point(_brent.MinimalX(cost1d,currentCost,minimumCost));
      
      // Check termination condition.
      
      // Compute the reduction in the cost function.
      RealT costdiff = currentCost-minimumCost;
      
      // Check if we're stopped converging.
      if (2.0*Abs(costdiff) <= _tolerance*(Abs(currentCost)+Abs(minimumCost))) {
        //ONDEBUG(cerr << "CostDiff=" << costdiff << " Tolerance=" << _tolerance*(Abs(currentCost)+Abs(minimumCost)) << "\n");
        break;
      }
      currentCost = minimumCost; // Reset for next iteration.
      
      // Determine current Jacobian
      dYdX = domain.Jacobian1(iterX);
      
      // Compute conjugate direction.
      RealT gg = 0;
      RealT dgg =0;
      for(SArray1dIter2C<RealT,RealT> it(dYdX,gdYdX);it;it++) {
        gg += Sqr(it.Data2());
        dgg += (it.Data1() + it.Data2()) * it.Data1();
      }
      if(gg == 0) {
        ONDEBUG(cerr << "Terminated on gg == 0\n");
        break;
      }
      RealT gama = dgg/gg;
      for(SArray1dIter3C<RealT,RealT,RealT> it(dYdX,gdYdX,hdYdX);it;it++) {
        it.Data2() = -it.Data1();
        it.Data1() = it.Data2() + gama * it.Data3();
        it.Data3() = it.Data1();
      }
      
      
    } while (counter++ < _iterations); 
    ONDEBUG(cerr << "Terminated after " << counter << " iterations. MinCost=" << currentCost << "\n");
    return domain.ConvertX2P (iterX);            // Return final estimate
  }
  
  const StringC OptimiseConjugateGradientBodyC::GetInfo () const
  {
    StrOStreamC stream;
    stream << OptimiseBodyC::GetInfo () << "\n";
    stream << "Gradient descent optimization algorithm. Iterations = " << _iterations;
    return stream.String();
  }
  
  bool OptimiseConjugateGradientBodyC::Save (ostream &out) const
  {
    OptimiseBodyC::Save (out);
    out << _iterations << "\n";
    return true;
  }
  
}
