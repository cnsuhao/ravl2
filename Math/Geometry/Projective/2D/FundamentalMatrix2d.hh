#ifndef RAVL_FUNDAMENTALMATRIX2D_HEADER
#define RAVL_FUNDAMENTALMATRIX2D_HEADER 1

#include "Ravl/SArray1d.hh"
#include "Ravl/PPoint2d.hh"
#include "Ravl/PLine2d.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/Vector2d.hh"
#include "Ravl/Matrix3d.hh"
#include "Ravl/PProjection2d.hh"

namespace RavlN {
  class MatrixC;
  class LineABC2dC;
  
  //! userlevel=Normal
  //: Fundamental Matrix.
  
  class FundamentalMatrix2dC 
    : public PProjection2dC
  {
  public:
    FundamentalMatrix2dC()
    {}
    
    FundamentalMatrix2dC(Matrix3dC &mat)
      : PProjection2dC(mat)
    {}
    
    FundamentalMatrix2dC(RealT a00,RealT a01,RealT a02,
			 RealT a10,RealT a11,RealT a12,
			 RealT a20,RealT a21,RealT a22)
      : PProjection2dC(a00,a01,a02,
		       a10,a11,a12,
		       a20,a21,a22)
    {}
    //: Construct from matrix elements.
    
    RealT Error(const PPoint2dC &p1,const PPoint2dC &p2) const;
    //: Compute the error distance from epipolar line.
    
    LineABC2dC EpipolarLine(const PPoint2dC &p1);
    //: Compute the epipolar line in image 2 from 'p1' in image 1.
    
    void NormaliseScale();
    //: Normalise scale.
    // Normalise the magnitude of the elements in the matrix by dividing them by
    
    void MakeRank2();
    //: Make the matrix rank 2
    // Uses SVD method.
    
    PLine2dC operator()(const PPoint2dC &pnt) const
    { return (*this) * pnt; }
    
    static FundamentalMatrix2dC FitLinear(const SArray1dC<PPoint2dC> &pnts1,const SArray1dC<PPoint2dC> &pnts2);
    //: Compute the fundamental matrix from 2 sets of points.
    // This computes tbe fundamental matrix using a linear method (Sometimes called the normalised 8-point alogorithm),
    // you need least 8 points, but more may be used to obtain a least squares fit.
    
  protected:

    static MatrixC BuildDesignMatrix(const SArray1dC<PPoint2dC> &pnts1,const Vector2dC &offset1,RealT scale1,
				     const SArray1dC<PPoint2dC> &pnts2,const Vector2dC &offset2,RealT scale2);
    //: Build a design matrix given two sets of points.
    
    static void NormalisePointSet(const SArray1dC<PPoint2dC> &pnts,Vector2dC &offset,RealT &scale);
    //: Compute the translation and scale normalisation
    // such that the mean of the points is zero and their average magnitude is equal to the average scale factor. 
    
  };

  
}


#endif
