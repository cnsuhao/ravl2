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
//! docentry="Ravl.Pattern Recognition.Dimension Reduction"
//! author="Charles Galambos"
//! file="Ravl/PatternRec/DimensionReduction/Funcsubset.hh"

#include "Ravl/PatternRec/Function.hh"
#include "Ravl/MeanCovariance.hh"

namespace RavlN {

  //! userlevel=Develop
  //: Reduce dimension by taking a subset of features.
  
  class GaussianMixtureBodyC 
    : public FunctionBodyC
  {
  public:
    GaussianMixtureBodyC()
    {}
    //: Default constructor.
    
    GaussianMixtureBodyC(const SArray1dC<MeanCovarianceC> & params, const SArray1dC<RealT> & weights, bool isDiagonal);
    //: Construct from mixture parameters and mixing coefficients

    GaussianMixtureBodyC(const SArray1dC<VectorC> & means, const SArray1dC<MatrixRSC> & covariances, const SArray1dC<RealT> & weights, bool isDiagonal);
    //: Construct from mixture parameters and mixing coefficients
    
    GaussianMixtureBodyC(istream &strm);
    //: Load from stream.

    GaussianMixtureBodyC(BinIStreamC &strm);
    //: Load from binary stream.

    virtual bool Save (ostream &out) const;
    //: Writes object to stream.

    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to binary stream.
    
    virtual VectorC Apply(const VectorC &data) const;
    //: Reduce the dimension of 'data'.

    RealT DensityValue(const VectorC & X) const
      { return Apply(X).Sum(); }
    //: Return the denisty value at point X

  protected:
    void precompute();
    //: precompute the inverse covariances, determinants e.t.c.
    
    SArray1dC<MeanCovarianceC>params; 
    //: The parameters of the distribution
    
    SArray1dC<RealT>weights;
    //: Mixing coefficients of the distribution
    
    SArray1dC<MatrixRSC>invCov;
    //: We pre-compute inverse of covariance matrix

    SArray1dC<RealT> det;
    //: We pre-compute the determinant of cov

    RealT konst;
    //: The constant used in pdf. 

    bool isDiagonal;
    //: Flag which determines whether full covariances should computed

  };

  //! userlevel=Develop
  //: Reduce dimension by taking a subset of features.

  class GaussianMixtureC 
    : public FunctionC
  {
  public:
    GaussianMixtureC()
    {}
    //: Default constuctor.
    // Creates an invalid handle.
    
    GaussianMixtureC(const SArray1dC<MeanCovarianceC> & params, SArray1dC<RealT> & weights, bool isDiagonal=false)
      : FunctionC(*new GaussianMixtureBodyC(params, weights, isDiagonal))
      {}
    //: Construct from mixture parameters and mixing coefficients
    
    GaussianMixtureC(const SArray1dC<VectorC> & means, const SArray1dC<MatrixRSC> & covariances, const SArray1dC<RealT> & weights, bool isDiagonal=false)
      : FunctionC(*new GaussianMixtureBodyC(means, covariances, weights, isDiagonal))
      {}
    //: Construct from mixture parameters and mixing coefficients

    GaussianMixtureC(istream &is);
    //: Stream constructor.

    GaussianMixtureC(const FunctionC &func)
      : FunctionC(func)
    {
      if(dynamic_cast<GaussianMixtureBodyC *>(&FunctionC::Body()) == 0)
	Invalidate();
    }
    //: Attempt to create handle from base class.
    // If object is not a FuncMeanProjectionC, an invalid handle will be created.

    GaussianMixtureC(BinIStreamC &is);
    //: Stream constructor.

    
  protected:
    GaussianMixtureC(GaussianMixtureBodyC &bod)
      : FunctionC(bod)
    {}
    //: Body constructor.
    
    GaussianMixtureBodyC &Body() 
    { return static_cast<GaussianMixtureBodyC &>(FunctionC::Body()); }
    //: Access body.
    
    const GaussianMixtureBodyC &Body() const
    { return static_cast<const GaussianMixtureBodyC &>(FunctionC::Body()); }
    //: Access body.
    
  public:
    RealT DensityValue(const VectorC & X) const
      { return Body().DensityValue(X); }
    //: Return the density value at point X

  };

  inline istream &operator>>(istream &strm,GaussianMixtureC &obj) {
    obj = GaussianMixtureC(strm);
    return strm;
  }
  //: Load from a stream.
  // Uses virtual constructor.
  
  inline ostream &operator<<(ostream &out,const GaussianMixtureC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.


  inline BinIStreamC &operator>>(BinIStreamC &strm,GaussianMixtureC &obj) {
    obj = GaussianMixtureC(strm);
    return strm;
  }
  //: Load from a binary stream.
  // Uses virtual constructor.
  
  inline BinOStreamC &operator<<(BinOStreamC &out,const GaussianMixtureC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.

}


#endif
