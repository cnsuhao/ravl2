// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
#include "Ravl/config.h"
#include "Ravl/Matrix.hh"
#include "Ravl/Vector.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/LineABC2d.hh"
#include "Ravl/Vector3d.hh"

#include "Ravl/FundamentalMatrix2d.hh"

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x) 
#endif

namespace RavlN {
  
  //: Compute the fundamental matrix from 2 sets of points.
  // This computes tbe fundamental matrix using a linear method (Sometimes called the normalised 8-point alogorithm),
  // you need least 8 points, but more may be used to obtain a least squares fit.
  
  FundamentalMatrix2dC FundamentalMatrix2dC::FitLinear(const SArray1dC<PPoint2dC> &pnts1,const SArray1dC<PPoint2dC> &pnts2) {
    Vector2dC offset1,offset2;
    RealT scale1,scale2;
    
    NormalisePointSet(pnts1,offset1,scale1);
    NormalisePointSet(pnts2,offset2,scale2);
    
    MatrixC A = BuildDesignMatrix(pnts2,offset2,scale2,
				  pnts1,offset1,scale1);
    
    Matrix3dC norm1(1/scale1,0       ,-offset1[0]/scale1,
		    0       ,1/scale1,-offset1[1]/scale1,
		    0       ,0       ,1);
    
    Matrix3dC norm2(1/scale2,0       ,-offset2[0]/scale2,
		    0       ,1/scale2,-offset2[1]/scale2,
		    0       ,0       ,1);
    
    ONDEBUG(cerr << "Norm1=" << norm1 << "\n");
    ONDEBUG(cerr << "Norm2=" << norm2 << "\n");
    
    //A.NormaliseRows();
    
    MatrixC u, v;
    VectorC d = SVD_IP(A,u,v);
    UIntT col = v.Cols()-1;
    
    FundamentalMatrix2dC ret(v[0][col],v[1][col],v[2][col],
			     v[3][col],v[4][col],v[5][col],
			     v[6][col],v[7][col],v[8][col]);
    
    ret.MakeRank2();
    
    ((Matrix3dC &)ret) = norm2.TMul(ret) * norm1; // Undo normalisation.
    
    ret.NormaliseScale();
    
    return ret;
  }
  
  //: Normalise scale.
  
  void FundamentalMatrix2dC::NormaliseScale() {
    // Normalise magnitude.
    RealT norm = 1/Sqrt(SumOfSqr());
    (*this) *= norm;
  }

  //: Compute the error (distance from line) of p2 with respect to p1 in the first image.
  
  RealT FundamentalMatrix2dC::Error(const PPoint2dC &p1,const PPoint2dC &p2) const {
    Vector3dC lp =  (*this)(p1);
    return Abs((p2.T() * lp)[0]) / Sqrt(Sqr(lp[0]) + Sqr(lp[1]));
  }
  
  //: Compute the epipolar line in image 2 from 'p1' in image 1.
  
  LineABC2dC FundamentalMatrix2dC::EpipolarLine(const PPoint2dC &p1) {
    Vector3dC l = (*this)(p1);
    return LineABC2dC(l[0],l[1],l[2]);
  }
  
  //: Make the matrix rank 2
  // Uses SVD method.
  
  void FundamentalMatrix2dC::MakeRank2() {
    MatrixC u, v;
    MatrixC me(*this);
    VectorC d = SVD_IP(me,u,v);
    // Generate rank 2 matrix.
    MatrixC newf = (u * MatrixC(d[0],0   ,0,
				0   ,d[1],0,
				0   ,0   ,0)).MulT(v);
    
#if RAVL_COMPILER_MIPSPRO || RAVL_COMPILER_VISUALCPP
    static_cast<Matrix3dC &>(*this) = (Matrix3dC) (TFMatrixC<RealT,3,3>&) newf ; // help the compiler a bit  !
#else 
    static_cast<Matrix3dC &>(*this) = (Matrix3dC)  newf;
#endif 

 }
  
  //: Build a design matrix given two sets of points.
  
  MatrixC FundamentalMatrix2dC::BuildDesignMatrix(const SArray1dC<PPoint2dC> &pnts1,const Vector2dC &offset1,RealT scale1,
						  const SArray1dC<PPoint2dC> &pnts2,const Vector2dC &offset2,RealT scale2) {
    RavlAssert(pnts1.Size() == pnts2.Size());
    UIntT size = pnts1.Size();
    if(size < 9)
      size = 9;
    MatrixC A(size,9);
    IndexC i = 0;
    PPoint2dC p1,p2;
    for(SArray1dIter2C<PPoint2dC,PPoint2dC> it(pnts1,pnts2);it;it++,i++) {
      p1[0] = (it.Data1()[0] - offset1[0]) / scale1;
      p1[1] = (it.Data1()[1] - offset1[1]) / scale1;
      p1[2] = it.Data1()[2];
      p2[0] = (it.Data2()[0] - offset2[0]) / scale2;
      p2[1] = (it.Data2()[1] - offset2[1]) / scale2;
      p2[2] = it.Data2()[2];
      ONDEBUG(cerr << "P1=" << p1 << "     P2=" << p2 << "\n");
      A[i][0] = p1[0] * p2[0];
      A[i][1] = p1[0] * p2[1];
      A[i][2] = p1[0] * p2[2];
      A[i][3] = p1[1] * p2[0];
      A[i][4] = p1[1] * p2[1];
      A[i][5] = p1[1] * p2[2];
      A[i][6] = p1[2] * p2[0];
      A[i][7] = p1[2] * p2[1];
      A[i][8] = p1[2] * p2[2];
    }
    // Hack to make sure design matrix is at least 9x9
    // Copy first row into last to make sure
    while(size > pnts1.Size()) {
      size--;
      for(i = 0;i < 9;i++)
	A[size][i] = A[0][i];
    }
    return A;
  }
  
  //: Normalise points to have a mean of zero and have an magnitude of 1
  
  void FundamentalMatrix2dC::NormalisePointSet(const SArray1dC<PPoint2dC> &pnts,Vector2dC &offset,RealT &scale) {
    // Compute the mean position.
    offset = Vector2dC(0,0);
    scale = 0;
    RealT mscale = 0;
    for(SArray1dIterC<PPoint2dC> it(pnts);it;it++) {
      //cerr << "Point=" << *it << "\n";
      Point2dC p = it->Point2d();
      mscale += (*it)[2];
      offset += p;
    }
    offset /= (RealT) pnts.Size();
    mscale /= (RealT) pnts.Size(); 
    
    // Go through and subtract the mean.
    for(SArray1dIterC<PPoint2dC> it(pnts);it;it++) {
      Point2dC p((*it)[0] - offset[0],(*it)[1] - offset[1]);
      scale += Sqrt(p.SumOfSqr());
    }
    scale *= mscale / (RealT) pnts.Size();
    ONDEBUG(cerr << "FundamentalMatrix2dC::NormalisePointSet(), Offset=" << offset << " Scale=" << scale << "\n");
  }
  
}
