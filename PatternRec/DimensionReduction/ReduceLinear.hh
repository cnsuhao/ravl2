// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_REDUCELINEAR_HEADER
#define RAVL_REDUCELINEAR_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Robert Crida and Charles Galambos"
//! docentry="Ravl.Pattern Recognition.Dimension Reduction"
//! file="Ravl/PatternRec/DimensionReduction/ReduceLinear.hh"

#include "Ravl/PatternRec/Reduce.hh"
#include "Ravl/Matrix.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Linear dimension reduction.
  // Uses a linear model. Subtract the mean, rotates
  // and project to a subspace.
  
  class ReduceLinearBodyC
    : public ReduceBodyC
  {
  public:
    ReduceLinearBodyC()
    {}
    //: Default constructor.
    
    ReduceLinearBodyC(const VectorC &mean,const MatrixC &proj,RealT variationPreserved = 1);
    //: Construct from a mean and rotation.
    
    ReduceLinearBodyC(istream &strm);
    //: Load from stream.
    
    ReduceLinearBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual VectorC Apply(const VectorC &data);
    //: Reduce the dimension of 'data'.

    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    const VectorC &Mean() const
    { return mean; }
    //: Access mean vector.
    
    const MatrixC &Projection() const
    { return proj; }
    //: Access projection matrix.
    
  protected:
    VectorC mean; // Mean.
    MatrixC proj;  // Rotation/projection to apply.
  };
  
  //! userlevel=Normal
  //: Linear dimension reduction.
  // Uses a linear model. Subtract the mean, rotates
  // and project to a subspace.
  
  class ReduceLinearC
    : public ReduceC
  {
  public:
    ReduceLinearC()
    {}
    //: Default constructor.
    // Creates an invalid handle.

    ReduceLinearC(const VectorC &mean,const MatrixC &proj,RealT variationPreserved = 0)
      : ReduceC(*new ReduceLinearBodyC(mean,proj,variationPreserved))
    {}
    //: Construct from a mean and rotation.
    
  protected:
    ReduceLinearC(ReduceLinearBodyC &bod)
      : ReduceC(bod)
    {}
    //: Body constructor.
    
    ReduceLinearBodyC &Body()
    { return static_cast<ReduceLinearBodyC &>(ReduceC::Body()); }
    //: Access body.
    
    const ReduceLinearBodyC &Body() const
    { return static_cast<const ReduceLinearBodyC &>(ReduceC::Body()); }
    //: Access body.
    
  public:    
    const VectorC &Mean() const
    { return Body().Mean(); }
    //: Access mean vector.
    
    const MatrixC &Projection() const
    { return Body().Projection(); }
    //: Access projection matrix.
  };

}



#endif
