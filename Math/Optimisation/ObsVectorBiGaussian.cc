// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlOptimise

#include "Ravl/ObsVectorBiGaussian.hh"

namespace RavlN {

  //: Constructor
  ObsVectorBiGaussianBodyC::ObsVectorBiGaussianBodyC(const VectorC &nz,
						     const MatrixRSC &nNi,
						     RealT nvar_scale,
						     RealT nchi2_thres)
    : ObsVectorBodyC(nz,nNi)
  {
    var_inv_scale = 1.0/nvar_scale;
    chi2_thres = nchi2_thres;
    chi2_offset = (1.0 - var_inv_scale)*chi2_thres;
    outlier = previous_outlier_flag = true;
  }

  //: Constructor
  ObsVectorBiGaussianBodyC::ObsVectorBiGaussianBodyC(const VectorC &nz,
						     const MatrixRSC &nNi,
						     const VectorC &nzstep,
						     RealT nvar_scale,
						     RealT nchi2_thres)
    : ObsVectorBodyC(nz,nNi,nzstep)
  {
    var_inv_scale = 1.0/nvar_scale;
    chi2_thres = nchi2_thres;
    chi2_offset = (1.0 - var_inv_scale)*chi2_thres;
    outlier = previous_outlier_flag = true;
  }

  //: Return residual adjusted for robust aspects to the observation
  double ObsVectorBiGaussianBodyC::Residual(const VectorC &v,
					    const MatrixRSC &Ni)
  {
    // firstly store outlier flag
    previous_outlier_flag = outlier;

    // now compute residual as usual

    // compute N^-1*v
    VectorC Niv = Ni*v;

    // compute v^T*N^-1*v
    double residual = Niv.Dot(v);

    if ( residual <= chi2_thres )
      // inlier distribution: increment residual with squared innovation as
      // normal
      outlier = false;
    else { // residual > chi2_thres
      // adjust residual using outlier distribution offset
      residual = residual*var_inv_scale + chi2_offset;
      outlier = true;
    }

    return residual;
  }

  //: Adjust information matrix/vector term for any robustness
  bool ObsVectorBiGaussianBodyC::AdjustInformation(MatrixRSC &Aterm,
						   VectorC &aterm)
  {
    if ( outlier ) {
      // adjust increments to information matrix and vector
      Aterm *= var_inv_scale;
      aterm *= var_inv_scale;
    }

    return true;
  }

  //: Restore values are an aborted modification
  bool ObsVectorBiGaussianBodyC::Restore()
  {
    // restore previous outlier flag
    outlier = previous_outlier_flag;
    return true;
  }

  //: Get outlier flag
  const bool ObsVectorBiGaussianBodyC::Outlier() const
  {
    return outlier;
  }

  //: Set observation to be an inlier
  void ObsVectorBiGaussianBodyC::SetAsInlier()
  {
    outlier = false;
  }

  //: Set observation to be an outlier
  void ObsVectorBiGaussianBodyC::SetAsOutlier()
  {
    outlier = true;
  }
}
