// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_OPTIMISEPOWELL_HH
#define RAVL_OPTIMISEPOWELL_HH
////////////////////////////////////////////////////////////////////////////
//! author="Robert Crida"
//! lib=Optimisation
//! date="6/8/2003"
//! userlevel=Normal
//! example=testOptimise.cc
//! file="Ravl/PatternRec/Optimise/OptimisePowell.hh"
//! docentry="Ravl.API.Pattern Recognition.Optimisation.Implementation"
//! rcsid="$Id$"

#include "Ravl/PatternRec/Optimise.hh"
#include "Ravl/PatternRec/OptimiseBrent.hh"

namespace RavlN {

  // --------------------------------------------------------------------------
  // **********  OptimisePowellBodyC  *****************************************
  // --------------------------------------------------------------------------
  //: Powell's (roughly) quadratically convergent non-gradient optimiser
  //: implementation class.
  //
  // This is the implementation class of the non-gradient Powell optimiser for the
  // PatternRec toolbox. The OptimisePowellC handle class should be used.
  
  class OptimisePowellBodyC: public OptimiseBodyC
  {    
  public:
    OptimisePowellBodyC (UIntT iterations, RealT tolerance, bool useBracketMinimum,bool verbose = false);
    //: Constructor requires the number of iterations to use
    
    OptimisePowellBodyC (istream &in);
    //: Constructs from stream
    
  protected:
    VectorC MinimalX (const CostC &domain, RealT startCost, RealT &minimumCost) const;
    //: Determines Xmin=arg min_{X} |f(X)-Yd|
    
    virtual const StringC GetInfo () const;
    //: Prints information about the optimiser
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor

  private:
    UIntT _iterations;
    RealT _tolerance;
    OptimiseBrentC _brent;
    bool _useBracketMinimum;
    bool _verbose; 
  };
  
  //: Powell's (roughly) quadratically convergent non-gradient optimisation
  //: algorithm
  //
  // Optimisation algorithm that does not use gradient but has roughly quadratic
  // convergence.
  
  class OptimisePowellC: public OptimiseC
  {
  public:
    OptimisePowellC (UIntT iterations, RealT tolerance = 1e-6, bool useBracketMinimum = true,bool verbose = false)
      :OptimiseC(*(new OptimisePowellBodyC (iterations, tolerance, useBracketMinimum,verbose))) 
    {}
    //: Constructor
    //!param: iterations - maximum number of iterations to use
  };
}

#endif
