// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DESIGNFUNCPCA_HEADER
#define RAVL_DESIGNFUNCPCA_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Charles Galambos"
//! docentry="Ravl.Pattern Recognition.Dimension Reduction"
//! file="Ravl/PatternRec/Modeling/DimensionReduction/DesignFuncPCA.hh"

#include "Ravl/PatternRec/DesignFuncReduce.hh"
#include "Ravl/Matrix.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Design a dimension reducing function using Principle Component Anaylsis (PCA)
  
  class DesignFuncPCABodyC
    : public DesignFuncReduceBodyC
  {
  public:
    DesignFuncPCABodyC()
    {}
    //: Default constructor.
    
    DesignFuncPCABodyC(RealT variationPreserved = 0.98);
    //: Construct from a mean and rotation.
    
    DesignFuncPCABodyC(istream &strm);
    //: Load from stream.
    
    DesignFuncPCABodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual FunctionC Apply(const SampleC<VectorC> &in);
    //: Create function from the given data.
    
    virtual FunctionC Apply(SampleStreamC<VectorC> &in);
    //: Create function from the given data.
    
    VectorMatrixC &Pca()
    { return pca; }
    //: Access eigen vectors and values.

    const VectorMatrixC &Pca() const
    { return pca; }
    //: Access eigen vectors and values.
    
    VectorC &Mean()
    { return mean; }
    //: Access mean vector.

    const VectorC &Mean() const
    { return mean; }
    //: Access mean vector.
    
  protected:
    
    FunctionC DesignHighDim(const SampleC<VectorC> &sample,RealT variation);
    //: Design the transform.
    
    FunctionC DesignLowDim(const SampleC<VectorC> &sample,RealT variation);
    //: Design the transform.
    
    VectorC mean; // Last mean vector.
    VectorMatrixC pca; // Last set of eigen values and vectors.
    
    bool forceHimDim;
  };
  
  //! userlevel=Normal
  //: Design a dimension reducing function using Principle Component Anaylsis (PCA)
  
  class DesignFuncPCAC
    : public DesignFuncReduceC
  {
  public:
    DesignFuncPCAC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DesignFuncPCAC(RealT variationPreserved)
      : DesignFuncReduceC(*new DesignFuncPCABodyC(variationPreserved))
    {}
    //: Construct from a mean and rotation.
    
  protected:
    DesignFuncPCAC(DesignFuncPCABodyC &bod)
      : DesignFuncReduceC(bod)
    {}
    //: Body constructor.
    
    DesignFuncPCABodyC &Body()
    { return static_cast<DesignFuncPCABodyC &>(DesignerC::Body()); }
    //: Access body.
    
    const DesignFuncPCABodyC &Body() const
    { return static_cast<const DesignFuncPCABodyC &>(DesignerC::Body()); }
    //: Access body.
    
  public:    
    VectorMatrixC &Pca()
    { return Body().Pca(); }
    //: Access eigen vectors and values.

    const VectorMatrixC &Pca() const
    { return Body().Pca(); }
    //: Access eigen vectors and values.
    
    VectorC &Mean()
    { return Body().Mean(); }
    //: Access mean vector.
    
    const VectorC &Mean() const
    { return Body().Mean(); }
    //: Access mean vector.
  };

}



#endif
