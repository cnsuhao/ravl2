// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/LinearAlgebra/General/MatrixSVD.cc"

#include "Ravl/Matrix.hh"
#include "Ravl/Vector.hh"
#include "Ravl/CCMath.hh"

// General matrix functions.

namespace RavlN {
  // n*m row*col
  
  //: Singular value decomposition, eg. M = U * D * V.T(). 
  // The diagonal matrix D is returned as a vector. Values for the
  // other matrixes are not computed.
  // If the operation failes the returned vector is invalid.
  
  VectorC SVD(const MatrixC &mat) {
    MatrixC ret = mat.Copy();
    return SVD_IP(ret);
  }
  
  //: Singular value decomposition, eg. M = U * D * V.T(). 
  // The diagonal matrix D is returned as a vector. Values for the
  // other matrixes are not computed.
  // If the operation failes the returned vector is invalid. <p>
  // NB. This function destory's the contents of this matrix!
  
  VectorC SVD_IP(MatrixC &mat) {
    RavlAlwaysAssert(mat.IsContinuous()); // Should we cope with this silently ?
    if(mat.Rows() == 0)
      return VectorC(0);
    VectorC ret(mat.Rows());
    if(mat.Rows() > mat.Cols() * 2) { // Pick the best routine.
      if(sv2val(&ret[0],&mat[0][0],mat.Rows(),mat.Cols()) != 0)
	return VectorC();
    } else {
      if(svdval(&ret[0],&mat[0][0],mat.Rows(),mat.Cols()) != 0)
	return VectorC();
    }
    return ret;
  }
  
  //: Singular value decomposition, eg. M = U * D * V.T(). 
  // The diagonal matrix D is returned as a vector.
  // This also returns the matrix u and v matrixes, the passed
  // matrixes will be used to store the results if they are
  // of the correct size.
  // If the operation failes the returned vector is invalid.
  
  VectorC SVD(const MatrixC &mat,MatrixC & u, MatrixC & v) {
    MatrixC ret = mat.Copy();
    return SVD_IP(ret,u,v);
  }
  
  //: Singular value decomposition, eg. M = U * D * V.T(). 
  // The diagonal matrix D is returned as a vector.
  // This also returns the matrix u and v matrixes, the passed
  // matrixes will be used to store the results if they are
  // of the correct size.
  // If the operation failes the returned vector is invalid.
  // NB. This function destory's the contents of this matrix!

#if 1
  VectorC SVD_IP(MatrixC &mat,MatrixC & u, MatrixC & v) {
    RavlAlwaysAssert(mat.IsContinuous()); // Should we cope with this silently ?
    // Check for trivial cases.
    if(mat.Rows() == 0)
      return VectorC(0);
    // Make sure the output matrixes are right.
    if(!u.IsContinuous() || mat.Rows() != v.Rows() || mat.Cols() != v.Cols()) 
      u = MatrixC(mat.Rows(),mat.Cols());
    if(!v.IsContinuous() || mat.Rows() != v.Rows() || mat.Cols() != v.Cols()) 
      v = MatrixC(mat.Rows(),mat.Cols());
    VectorC ret(mat.Rows());
    if(mat.Rows() > mat.Cols() * 2) { // Pick the best routine.
      if(sv2uv(&ret[0],&mat[0][0],&u[0][0],mat.Rows(),&v[0][0],mat.Cols()) != 0)
	return VectorC();
    } else {
      if(svduv(&ret[0],&mat[0][0],&u[0][0],mat.Rows(),&v[0][0],mat.Cols()) != 0)
	return VectorC();
    }
    return ret;
  }
#else

  VectorC SVD_IP(MatrixC &mat,MatrixC & u, MatrixC & v) {
    const RealT isSmall = 10e-11;
    MatrixC & a = mat;
    const MySizeT m = mat.RDim();
    const MySizeT n = mat.CDim();
    IntT flag=0,its=0,j=0,jj=0,k=0;
    //IntT nm = -10;
    RealT c=0.0,f=0.0,h=0.0,s=0.0,x=0.0,y=0.0,z=0.0;
    
    IntT l = -1;
    VectorC rv1(n);
    
    RealT anorm = 0.0;
    RealT g     = 0.0;
    RealT scale = 0.0;
    IntT i = -1;
    for (i = 0; i < n; i++) {
#if AMMA_CHECK
      for(k = 0; k < m;k++) {
	if(IsNan(a[k][i]))
	  throw ErrorNumericalC("MatrixC::SVD(VectorC & w, MatrixC & v), ERROR: Not a Number (NaN) in matrix.");
      }
#endif
      l = i+1;
      rv1[i] = scale * g;
      g = 0.0;
      s = 0.0;
      scale = 0.0;
      if (i <= m){
	for (k = i; k < m; k++)
	  scale += ::Abs(a[k][i]);
	if (scale!=0.0) {
	  for (k = i; k < m; k++) {
	    a[k][i] /= scale;
	    s += a[k][i]*a[k][i];
	  }
	  f = a[i][i];
	  g = -Sign(::Sqrt(s),f);
	  h = f*g-s;
	  a[i][i] = f-g;
	  for (j = l; j < n; j++) {
	    for (s = 0.0, k = i; k < m; k++)
	      s += a[k][i]*a[k][j];
	    f = s/h;
	    for (k = i; k < m; k++)
	      a[k][j] += f*a[k][i];
	  }
	  for (k = i; k < m; k++)
	    a[k][i] *= scale;
	}
      }
      w[i] = scale *g;
      g = s = scale=0.0;
      if (i <= m && i != n) {
	for (k = l; k < n; k++)
	  scale += ::Abs(a[i][k]);
	if (scale!=0.0) {
	  for (k = l; k < n; k++) {
	    a[i][k] /= scale;
	    s += a[i][k]*a[i][k];
	  }
	  f = a[i][l];
	  g = -::Sign(::Sqrt(s),f);
	  h = f*g-s;
	  a[i][l]=f-g;
	  for (k=l; k<n; k++)
	    rv1[k] = a[i][k]/h;
	  for (j=l; j<m; j++) {
	    for (s=0.0, k=l; k<n; k++)
	      s += a[j][k]*a[i][k];
	    for (k=l; k<n; k++)
	      a[j][k] += s*rv1[k];
	  }
	  for (k=l; k<n; k++)
	    a[i][k] *= scale;
	}
      }
      anorm=::Max(anorm,(::Abs(w[i])+::Abs(rv1[i])));
    }
    for (i=n-1; i>=0; i--) {
      if (i < (n-1)) {
      if (g!=0.0) {
        for (j=l; j<n; j++)
          v[j][i] = (a[i][j]/a[i][l])/g;
        for (j=l; j<n; j++) {
          for (s=0.0, k=l; k<n; k++)
            s += a[i][k]*v[k][j];
          for (k=l; k<n; k++)
            v[k][j] += s*v[k][i];
        }
      }
      for (j=l; j<n; j++)
        v[i][j] = v[j][i] = 0.0;
      }
      v[i][i] = 1.0;
      g = rv1[i];
      l = i;
    }
    
    for (i=::Min(m,n)-1; i>=0; i--) {
      l=i+1;
      g=w[i];
      for (j=l; j<n; j++)
	a[i][j]=0.0;
      if (g!=0.0) {
	g=1.0/g;
	for (j=l; j<n; j++) {
	  s=0.0;
	  for (k=l; k<m; k++)
	    s += (a[k][i]*a[k][j]);
	  f= (s/a[i][i])*g;
	  for (k=i; k<m; k++)
	    a[k][j] += f*a[k][i];
	}
	for (j=i; j<m; j++)
	  a[j][i] *= g;
      }
      else
	for (j=i; j<m; j++)
	  a[j][i]=0.0;
      ++a[i][i];
    }
    for (k=n-1; k>=0;k--) {
      for (its=1; its<=30; its++) { // iterations
	IntT nm=-1;
	flag=1;
	for (l=k; l>=0; l--) {
        nm=l-1;
        if (IsSmall(rv1[l],anorm,isSmall)) {
          flag=0;
          break;
        }
	if(nm >= ((IntT) w.Size()) || nm < 0) {
	  //	  if(!StdIO::UsingStdMain()) {
	  cerr << "Encounted error in SVD, throwing exception. \n";
	  cerr << "(Using AMMA_ENTRY_POINT() disables this warning.)\n";
	  //	  }
	  //	  throw ErrorOperationFailedC("Strange bug in SVD routine. See amma/NumAlg/LinAlg/MaSVD.cc \n");
	  return v;
	}
        if (IsSmall(w[nm],anorm,isSmall)) 
	  break;   // XXX - see comments at top of file
	}
	if (flag != 0) {
	  c=0.0;
	  s=1.0;
	  for (i=l;i<=k;i++) {
	    f      = s*rv1[i];
	    rv1[i] = c*rv1[i];
	    if (IsSmall(f,anorm,isSmall)) break;
	    g    = w[i];
	    h    = ::Pythag(f,g);
	    w[i] = h;
	    h    =1.0/h;
	    c    =  g*h;
	    s    = -f*h;
	    for (j=0; j<m; j++) {
	      y = a[j][nm];
	      z = a[j][i];
	      a[j][nm] = y*c+z*s;
	      a[j][i]  = z*c-y*s;
	    }
	  }
	}
	z=w[k];
	if (l == k) {
	  if (z < 0.0) {
	    w[k] = -z;
	    for (j=0; j<n; j++)
	      v[j][k] = -v[j][k];
	  }
	  break;
	}
	if (its == 30)
	  throw ErrorNumericalC("MatrixC::SVD(VectorC & w, MatrixC & v), ERROR: No convergence in 30 SVDCMP iterations.");
	x  = w[l];
	nm = k-1;
	y  = w[nm];
	g  = rv1[nm];
	h  = rv1[k];
	f  = ((y-z)*(y+z)+(g-h)*(g+h))/(2.0*h*y);
	g  = ::Pythag(f,1.0);
	f  = ((x-z)*(x+z)+h*((y/(f+ ::Sign(g,f)))-h))/x;
	c = s = 1.0;
	for (j=l; j<=nm; j++) {
	  i = j+1;
	  g = rv1[i];
	  y = w[i];
	  h = s*g;
	  g = c*g;
	  z = ::Pythag(f,h);
	  rv1[j] = z;
	  c = f/z;
	  s = h/z;
	  f = x*c+g*s;
	  g = g*c-x*s;
	  h = y*s;
	  y *= c;
	  for (jj=0; jj<n; jj++) {
	    x = v[jj][j];
	    z = v[jj][i];
	    v[jj][j] = x*c+z*s;
	    v[jj][i] = z*c-x*s;
	  }
	  z = ::Pythag(f,h);
	  w[j] = z;
	  if (z!=0.0) {
	    z = 1.0/z;
	    c = f*z;
	    s = h*z;
	  }
	  f = c*g+s*y;
	  x = c*y-s*g;
	  for (jj=0;jj<m; jj++) {
	    y = a[jj][j];
	    z = a[jj][i];
	    a[jj][j] = y*c+z*s;
	    a[jj][i] = z*c-y*s;
	  }
	}
	rv1[l] = 0.0;
	rv1[k] = f;
	w[k]   = x;
      }
    }
  }
#endif

}
