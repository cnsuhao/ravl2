// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_REDUCESUBSET_HEADER
#define RAVL_REDUCESUBSET_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Charles Galambos"

#include "Ravl/PatternRec/Reduce.hh"

namespace RavlN {

  //! userlevel=Develop
  //: Reduce dimension by taking a subset of features.
  
  class ReduceSubsetBodyC 
    : public ReduceBodyC
  {
  public:
    ReduceSubsetBodyC()
    {}
    //: Default constructor.
    
    ReduceSubsetBodyC(const SArray1dC<IndexC> &ninds,UIntT inSize,RealT variationPreserved);
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

  class ReduceSubsetC 
    : public ReduceC
  {
  public:
    ReduceSubsetC()
    {}
    //: Default constuctor.
    // Creates an invalid handle.
    
    ReduceSubsetC(const SArray1dC<IndexC> &ninds,UIntT inSize,RealT variationPreserved = 0.5)
      : ReduceC(*new ReduceSubsetBodyC(ninds,inSize,variationPreserved))
    {}
    //: Constuctor from an array of indexes.
    
  protected:
    ReduceSubsetC(ReduceSubsetBodyC &bod)
      : ReduceC(bod)
    {}
    //: Body constructor.
    
    ReduceSubsetBodyC &Body() 
    { return static_cast<ReduceSubsetBodyC &>(FunctionC::Body()); }
    //: Access body.
    
    const ReduceSubsetBodyC &Body() const
    { return static_cast<const ReduceSubsetBodyC &>(FunctionC::Body()); }
    //: Access body.
    
  public:
    
    SArray1dC<IndexC> &Indexes()
    { return Body().Indexes(); }
    //: Get set of indexes that will be used.
  };

}


#endif
