// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FUNCSUBSET_HEADER
#define RAVL_FUNCSUBSET_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! docentry="Ravl.API.Pattern Recognition.Dimension Reduction"
//! author="Charles Galambos"
//! file="Ravl/PatternRec/Modeling/DimensionReduction/FuncSubset.hh"

#include "Ravl/PatternRec/Function.hh"

namespace RavlN {

  //! userlevel=Develop
  //: Reduce dimension by taking a subset of features.
  
  class FuncSubsetBodyC 
    : public FunctionBodyC
  {
  public:
    FuncSubsetBodyC()
    {}
    //: Default constructor.
    
    FuncSubsetBodyC(const SArray1dC<IndexC> &ninds,UIntT inSize);
    //: Constructor from an array of indexes.
    
    virtual VectorC Apply(const VectorC &data);
    //: Reduce the dimension of 'data'.
    
    SArray1dC<IndexC> &Indexes()
    { return inds; }
    //: Get set of indexes that will be used.
    
  protected:
    SArray1dC<IndexC> inds; // Indexes of features we're interested in.
  };

  //! userlevel=Develop
  //: Reduce dimension by taking a subset of features.

  class FuncSubsetC 
    : public FunctionC
  {
  public:
    FuncSubsetC()
    {}
    //: Default constuctor.
    // Creates an invalid handle.
    
    FuncSubsetC(const SArray1dC<IndexC> &ninds,UIntT inSize)
      : FunctionC(*new FuncSubsetBodyC(ninds,inSize))
    {}
    //: Constuctor from an array of indexes.
    
  protected:
    FuncSubsetC(FuncSubsetBodyC &bod)
      : FunctionC(bod)
    {}
    //: Body constructor.
    
    FuncSubsetBodyC &Body() 
    { return static_cast<FuncSubsetBodyC &>(FunctionC::Body()); }
    //: Access body.
    
    const FuncSubsetBodyC &Body() const
    { return static_cast<const FuncSubsetBodyC &>(FunctionC::Body()); }
    //: Access body.
    
  public:
    
    SArray1dC<IndexC> &Indexes()
    { return Body().Indexes(); }
    //: Get set of indexes that will be used.
  };

}


#endif
