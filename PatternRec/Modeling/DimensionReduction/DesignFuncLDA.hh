// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DESIGNFUNCLDA_HEADER
#define RAVL_DESIGNFUNCLDA_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Mohammad Sadeghi"
//! docentry="Ravl.Pattern Recognition.Dimension Reduction"
//! file="Ravl/PatternRec/Modeling/DimensionReduction/DesignFuncLDA.hh"

#include "Ravl/PatternRec/DesignFuncReduce.hh"
#include "Ravl/PatternRec/DesignFuncPCA.hh"
#include "Ravl/PatternRec/FuncMeanProjection.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/PatternRec/DataSetVectorLabel.hh"
#include "Ravl/Collection.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/MeanCovariance.hh"
#include "Ravl/Matrix.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Design a dimension reducing function using Linear Discriminant Anaylsis (LDA)
  
  class DesignFuncLDABodyC
    : public DesignFuncReduceBodyC
  {
  public:
    DesignFuncLDABodyC()
    {}
    //: Default constructor.
    
    DesignFuncLDABodyC(RealT variationPreserved = 0.98);
    //: Construct from a mean and rotation.
    
    DesignFuncLDABodyC(istream &strm);
    //: Load from stream.
    
    DesignFuncLDABodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual FunctionC Apply(const DataSetVectorLabelC &in);
    //: Create function from the given data.
    
    MatrixC &Lda()
    { return lda; }
    //: Access eigen vectors and values.

    const MatrixC &Lda() const
    { return lda; }
    //: Access eigen vectors and values.
    
    VectorC &Mean()
    { return mean; }
    //: Access mean vector.

    const VectorC &Mean() const
    { return mean; }
    //: Access mean vector.
    
  protected:
    
    MatrixC DesignMatrixTransformation(const MatrixC &sw,const MatrixC &sb);
    //: Design the lda transform using the matrix transformation method.
    
    VectorC mean; // Last mean vector.
    MatrixC lda; // Last lda transform matrix.
    
    bool forceHimDim;
  };
  
  //! userlevel=Normal
  //: Design a dimension reducing function using Principle Component Anaylsis (LDA)
  
  class DesignFuncLDAC
    : public DesignFuncReduceC
  {
  public:
    DesignFuncLDAC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DesignFuncLDAC(RealT variationPreserved)
      : DesignFuncReduceC(*new DesignFuncLDABodyC(variationPreserved))
    {}
    //: Construct from a mean and rotation.
    
  protected:
    DesignFuncLDAC(DesignFuncLDABodyC &bod)
      : DesignFuncReduceC(bod)
    {}
    //: Body constructor.
    
    DesignFuncLDABodyC &Body()
    { return static_cast<DesignFuncLDABodyC &>(DesignerC::Body()); }
    //: Access body.
    
    const DesignFuncLDABodyC &Body() const
    { return static_cast<const DesignFuncLDABodyC &>(DesignerC::Body()); }
    //: Access body.
    
  public:    
    inline MatrixC &Lda()
    { return Body().Lda(); }
    //: Access eigen vectors and values.

    inline const MatrixC &Lda() const
    { return Body().Lda(); }
    //: Access eigen vectors and values.
    
    inline VectorC &Mean()
    { return Body().Mean(); }
    //: Access mean vector.
    
    inline const VectorC &Mean() const
    { return Body().Mean(); }
    //: Access mean vector.

    inline FunctionC Apply(const DataSetVectorLabelC &in)
    { return Body().Apply(in) ; } 
    //: Create function from the given data.

  };

}



#endif
