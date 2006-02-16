// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_OPTIMISE_HH
#define RAVL_OPTIMISE_HH
////////////////////////////////////////////////////////////////////////////
//! author="Robert Crida"
//! lib=Optimisation
//! date="9/2/1998"
//! userlevel=Normal
//! example=testOptimise.cc
//! file="Ravl/PatternRec/Optimise/Optimise.hh"
//! docentry="Ravl.API.Pattern Recognition.Optimisation"
//! rcsid="$Id$"

#include "Ravl/RCHandleV.hh"
#include "Ravl/String.hh"
#include "Ravl/Vector.hh"
#include "Ravl/PatternRec/Cost.hh"

namespace RavlN {
  
  // --------------------------------------------------------------------------
  // **********  OptimiseBodyC  ***********************************************
  // --------------------------------------------------------------------------
  //: Implementation base class for numerical optimisation functions.
  //
  // Class hierarchy for numerical optimisation in the PatternRec set of tools.
  // You should not use this class directly but rather the handle class
  // OptimiseC.
  
  class OptimiseBodyC: public RCBodyVC
  {
    StringC _name;
  public:
    OptimiseBodyC (const StringC &name);
    //: Constructor with derived class name
    // The name is provided by the concrete class at instantiation so that the
    // base class knows what derived type it is.
    
    OptimiseBodyC (const StringC &name, istream &in);
    //: Contructs from stream with derived class name
    // The name or type must be known so that the correct virtual constructor
    // can be called.

    virtual VectorC MinimalX (const CostC &domain, RealT &minimumCost) const=0;
    //: Determines Xmin=arg min_{X} domain(X)
    //!param: domain      - the cost function that will be minimised
    //!param: minimumCost - the maximum cost value found
    //!return: the X value which gives the minimum cost
    // A minimisation algorithm must be provided for each derived optimisation
    // algorithm. It is not necessary to provide one for maximisation since
    // that is achieved using a cost function inverter as described in the next
    // member function.
    
    virtual VectorC MaximalX (const CostC &domain, RealT &maximumCost) const;
    //: Determines Xmax=arg max_{X} domain(X)
    //!param: domain - the cost function that will be maximised
    //!param: maximumCost - the maximum cost value found
    //!return: the X value which gives the maximum cost
    
    virtual const StringC GetInfo () const;
    //: Prints derived class information
    
    const StringC GetName () const;
    //: Derived class type
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
  };
  
  // --------------------------------------------------------------------------
  // **********  OptimiseC  ************************************************
  // --------------------------------------------------------------------------
  //: Handle class for numerical opimisers
  //
  // Handle class for numerical optimisers. It is used in conjunction with cost
  // functions derived from NumCostC. The cost function is used to specify the
  // range of parameters for optimisation etc. The optimiser is simply used by
  // providing a cost function and requesting the X vector that minimises or
  // maximises the cost function given a guess at the solution. See any of the
  // derived optimisers for specific algorithm implementations.
  
  class OptimiseC: public RCHandleVC<OptimiseBodyC>
  {
  public:
    OptimiseC ();
    //: Default constructor
    
    OptimiseC (istream &in);
    //: Constructs from stream
    
    OptimiseC (OptimiseBodyC &oth);
    //: Constructs from base class
    
  protected:
    inline OptimiseBodyC & Body ()
    { return RCHandleC<OptimiseBodyC>::Body(); }
    
    inline const OptimiseBodyC & Body () const
    { return RCHandleC<OptimiseBodyC>::Body(); }
    

  public:
    
    inline VectorC MinimalX (const CostC &domain, RealT &minimumCost) const;
    //: Do the Optimisation.
    // Determines which X gives minimum cost function value and gives access to 
    // calculated minimum cost

    inline VectorC MinimalX (const CostC &domain) const;
    //: Do the Optimisation. Determines which X gives minimum cost function value
    
    inline VectorC MaximalX (const CostC &domain, RealT &maximumCost) const;
    //: Do the Optimisation.
    // Determines which X gives maximum cost function value and gives access to 
    // calculated maximum cost

    inline VectorC MaximalX (const CostC &domain) const;
    //: Do the Optimisation. Determines which X gives maximum cost function value
    
    inline const StringC GetInfo () const;
    //: Gets string describing object
    
    inline const StringC GetName () const;
    //: Gets type name of the object
    
    inline bool Save (ostream &out) const;
    //: Writes object to stream, cna be loaded using constructor
  };
  
  ////////////////////////////////////////////////////
  
  
  VectorC OptimiseC::MinimalX (const CostC &domain,RealT &minimumCost) const
  { return Body().MinimalX (domain,minimumCost); }
  
  VectorC OptimiseC::MinimalX (const CostC &domain) const
  { RealT minimumCost; return Body().MinimalX (domain,minimumCost); }
  
  VectorC OptimiseC::MaximalX (const CostC &domain,RealT &maximumCost) const
  { return Body().MaximalX (domain,maximumCost); }
  
  VectorC OptimiseC::MaximalX (const CostC &domain) const
  { RealT maximumCost; return Body().MaximalX (domain,maximumCost); }
  
  const StringC OptimiseC::GetInfo () const
  { return Body().GetInfo (); }
  
  const StringC OptimiseC::GetName () const
  { return Body().GetName (); }
  
  bool OptimiseC::Save (ostream &out) const
  { return Body().Save (out); }
  
}

#endif
