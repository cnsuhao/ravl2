// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlChartDetector

//! author="Charles Galambos"

#include "Ravl/Image/CostAffineImageCorrelation.hh"
#include "Ravl/Image/WarpAffine.hh"
#include "Ravl/Image/NormalisedCorrelation.hh"
#include "Ravl/IO.hh"

namespace RavlImageN {
  //: Constructor.
  //!param:refImage - Image of which we're try to get a match.
  //!param:sceneImage - Scene in which we're searching.
  //!param:est - Initial estimate of transform.
  //!param:range - Range of parameter values over which to search. If null vector will be set automaticly.
  
  
  CostAffineImageCorrelationBodyC::CostAffineImageCorrelationBodyC(const ImageC<ByteT> &nrefImage,
								   const ImageC<ByteT> &nsceneImage,
								   const Affine2dC &est,
								   const VectorC &range) 
    : refImage(nrefImage),
      sceneImage(nsceneImage)
  {
    VectorC start = Affine2Vector(est);
    ParametersC xyz(6);
    if(range.Size() > 0) {
      // Use given paramiter ranges.
      for(int i = 0;i < 6;i++) {
	RealT x = start[i];
	xyz.Setup(i,x - range[i],x + range[i],1000,x);
      }
    } else {
      // Guess paramiter ranges....
      // FIXME :- This could do with some looking at.
      for(int i = 0;i < 6;i++) {
	RealT x = start[i];
	RealT p1 = (x * 0.9);
	RealT p2 = (x * 1.1);
	xyz.Setup(i,Min(p1,p2)-0.7,Max(p1,p2)+0.7,1000,x);
      }
    }
    SetParameters(xyz);
  }
  
  //: Convert affine transform to vector form.
  
  VectorC CostAffineImageCorrelationBodyC::Affine2Vector(const Affine2dC &affine) const {
    VectorC ret(6);
    ret[0] = affine.Translation()[0];
    ret[1] = affine.Translation()[1];
    ret[2] = affine.SRMatrix()[0][0];
    ret[3] = affine.SRMatrix()[0][1];
    ret[4] = affine.SRMatrix()[1][0];
    ret[5] = affine.SRMatrix()[1][1];
    return ret;
  }
  
  //: Convert vector to affine transform.
  
  Affine2dC CostAffineImageCorrelationBodyC::Vector2Affine(const VectorC &data) const {
    Vector2dC translation (data[0], data[1]);
    Matrix2dC srMatrix (data[2], data[3], data[4], data[5]);
    return Affine2dC(srMatrix, translation);
  }
  
  //: Determines cost of X
  
  RealT CostAffineImageCorrelationBodyC::Cost (const VectorC &x) const {
    Affine2dC trans = Vector2Affine(x);
    WarpAffineC<ByteT> warp(refImage.Frame(),trans);
    ImageC<ByteT> result = warp.Apply(sceneImage);
    //RavlN::Save("@X:Ref",refImage);
    //RavlN::Save("@X:Opt",result);
    RealT cost =-NormalisedCorrelation(refImage,result);
    //cerr << "Cost=" << cost << "\n";
    return cost;
  }

  //: Evaluate cost function at X
  
  VectorC CostAffineImageCorrelationBodyC::Apply(const VectorC &X) const {
    VectorC ret(1);
    ret[0] = Cost(X);
    return ret;
  }
  
  //: Calculate Jacobian matrix at X
  
  MatrixC CostAffineImageCorrelationBodyC::Jacobian (const VectorC &X) const {
    RavlAssert(X.Size() == inputSize);
    MatrixC J (outputSize,inputSize);
    VectorC dX (inputSize);
    dX.Fill(0);
    for(UIntT index = 0;index < inputSize;index++) {
      dX[index] = 1e-6;
      VectorC temp = Apply(X+dX) - Apply(X-dX);
      temp /= 2e-6;
      J.SetColumn (index,temp);
      dX[index] = 0;
    }
    return J;
  }
  
}
