// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_TSMATRIXPOSITIVEDEFINITE_HEADER
#define RAVL_TSMATRIXPOSITIVEDEFINITE_HEADER 1
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! date="15/8/2002"
//! lib=RavlMath
//! docentry="Ravl.Math.Linear Algebra"
//! file="Ravl/Math/LinearAlgebra/General/TSMatrixFull.hh"

#include "Ravl/TSMatrixFull.hh"

namespace RavlN {
  //! userlevel=Develop
  //: Symmetric positive definite matrix.
  
  template<class DataT>
  class TSMatrixPositiveDefiniteBodyC 
    : public TSMatrixFullBodyC<DataT>
  {
  public:
    TSMatrixPositiveDefiniteBodyC()
    {}
    //: Default constructor.
    
    TSMatrixPositiveDefiniteBodyC(UIntT rows,UIntT cols)
      : TSMatrixFullBodyC<DataT>(rows,cols)
    {}
    //: Create a matrix of rows by cols
    
    TSMatrixPositiveDefiniteBodyC(const TMatrixC<DataT> &mat)
      : TSMatrixBodyC<DataT>(mat)
    {}
    //: Constructor.
    
    virtual RCBodyVC &Copy() const
    { return *new TSMatrixPositiveDefiniteBodyC<DataT>(matrix.Copy()); }
    //: Create a copy of this matrix.
    
    virtual const type_info &MatrixType() const
    { return typeid(TSMatrixPositiveDefiniteBodyC<DataT>); }
    //: Find the type of the matrix.    
    
    virtual void Element(UIntT i,UIntT j,const DataT &val) { 
      matrix[i][j] = val; 
      matrix[j][i] = val; 
    }
    //: Set element.
    
  protected:
  };
  
  //! userlevel=Normal
  //: Symmetric positive definite matrix.
  
  template<class DataT>
  class TSMatrixPositiveDefiniteC 
    : public TSMatrixFullC<DataT>
  {
  public:
    TSMatrixPositiveDefiniteC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    TSMatrixPositiveDefiniteC(const TMatrixC<DataT> &mat)
      : TSMatrixFullC<DataT>(*new TSMatrixPositiveDefiniteBodyC<DataT>(mat))
    {}
    //: Constructor.
    
    TSMatrixPositiveDefiniteC(const TSMatrixC<DataT> &mat)
      : TSMatrixFullC<DataT>(mat)
    {
      if(dynamic_cast<TSMatrixPositiveDefiniteBodyC<DataT> *>(&TSMatrixC<DataT>::Body()) == 0)
	Invalidate();
    }
    //: Base constructor.
    
  protected:
    TSMatrixPositiveDefiniteC(TSMatrixPositiveDefiniteBodyC<DataT> &bod)
      : TSMatrixFullC<DataT>(bod)
    {}
    //: Body constructor.
    
    TSMatrixPositiveDefiniteBodyC<DataT> &Body()
    { return static_cast<TSMatrixPositiveDefiniteBodyC<DataT> &>(TSMatrixC<DataT>::Body()); }
    //: Access body.
    
    const TSMatrixPositiveDefiniteBodyC<DataT> &Body() const
    { return static_cast<const TSMatrixPositiveDefiniteBodyC<DataT> &>(TSMatrixC<DataT>::Body()); }
    //: Access body.
    
  public:
  };
  
  
}


#endif
