// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_REDUCE_HEADER
#define RAVL_REDUCE_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/Function.hh"
#include "Ravl/Vector.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Dimension Reduction.
  
  class ReduceBodyC
    : public FunctionBodyC
  {
  public:
    ReduceBodyC()
      : varPreserved(1)
    {}
    //: Default constructor.
    
    ReduceBodyC(RealT varPres)
      : varPreserved(varPres)
    {}
    //: Constructor.
    
    ReduceBodyC(istream &strm);
    //: Load from stream.
    
    ReduceBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual VectorC Apply(const VectorC &data);
    //: Reduce the dimension of 'data'.
    
    RealT VariationPreserved() const
    { return varPreserved; }
    //: An estimate of the variation preserved by the transform.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor
    
  protected:
    RealT varPreserved;
  };

  //! userlevel=Develop
  //: Dimension Reduction.
  
  class ReduceC
    : public FunctionC
  {
  public:
    ReduceC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    ReduceC(ReduceBodyC &bod)
      : FunctionC(bod)
    {}
    //: Body constructor.
    
    ReduceBodyC &Body()
    { return static_cast<ReduceBodyC &>(FunctionC::Body()); }
    //: Access body.
    
    const ReduceBodyC &Body() const
    { return static_cast<const ReduceBodyC &>(FunctionC::Body()); }
    //: Access body.
    
  public:
    VectorC Apply(const VectorC &data)
    { return Body().Apply(data); }
    //: Reduce the dimension of 'data'.
    
    RealT VariationPreserved() const
    { return Body().VariationPreserved(); }
    //: An estimate of the variation preserved by the transform.
    
  };
  
  
}

#endif
