// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMEANCOVND_HH
#define RAVLMEANCOVND_HH
//////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! author="Radek Marik"
//! date="01.01.1994"
//! docentry="Ravl.Math.Statistics"
//! lib=RavlMath

#include "Ravl/MeanNd.hh"
#include "Ravl/Matrix.hh"

class istream;
class ostream;

namespace RavlN {
  
  //! userlevel=Normal
  //: Mean and covariance together in N-D space 
  // The class MeanCovarianceNdC serves for computation of the mean
  // and the covariance matrix of a set of N-dimensional data points.
  // The object are able to share a memory with other objects.
  
  class MeanCovarianceNdC {
  public:
    MeanCovarianceNdC::MeanCovarianceNdC(const MeanCovarianceNdC & meanCov)
      : m(meanCov.m), 
      cov(meanCov.cov)
      {}
    // The class MeanCovarianceNdC is implemented as a big object using
    // a reference counter.
    
    MeanCovarianceNdC(const SizeT n)
      : m(n), 
      cov(n,n)
      { cov.Fill(0); }
    // Creates zero mean and zero covariance matrix representing
    // the 'n'-dimensional set containing no data points.

    MeanCovarianceNdC(const VectorC & point)
      : m(point), 
      cov(point.Size(),point.Size())
      { cov.Fill(0); }
    // Creates the mean vector and zero covariance matrix representing
    // the data set containing just one data point. The vector 'point'
    // is shared.
    
    MeanCovarianceNdC(const MeanNdC & mean)
      : m(mean), 
      cov(mean.Mean().Size(),mean.Mean().Size())
      { cov.Fill(0); }
    // Creates the mean vector and zero covariance matrix representing
    // the data set represented by the 'mean'. The structure 'mean'
    // is shared.
    
    MeanCovarianceNdC(SizeT  n, 
                      const VectorC & mean, 
                      const MatrixC & ncov)
      : m(n,mean), 
      cov(ncov)
    {}
    // Creates the mean vector and zero covariance matrix representing
    // the data set containing 'n' points and represented by the 'mean'
    // and the covariance matrix 'cov'. Both 'mean' and 'cov' are
    // shared.
    
    MeanCovarianceNdC Copy() const;
    // Returns a new physical copy of this object.
    
    MeanCovarianceNdC(const SArray1dC<VectorC> & data);
    //: Compute the mean and covariance of an array of vectors.
    
    // Information about an object
    // ---------------------------

    SizeT Number() const
      { return m.Number(); }
    // Returns the number of data points which are represented by this object.
    
    const VectorC & Mean() const
      { return m.Mean(); }
    //: Access the mean.
    // Returns the mean vector of data points which are represented
    // by this object.
    
    const MatrixC & Covariance() const
      { return cov; }
    //: Access the covariance.
    // Returns the covariance matrix of data points which are represented
    // by this object.

    // Object modification
    // -------------------      
    
    const MeanCovarianceNdC & SetZero();
    // Total initialization of this object resulting in the representation
    // the empty set of data points.

    const MeanCovarianceNdC & operator+=(const VectorC & point);
    // Adds one point to the set of data points.

    const MeanCovarianceNdC & operator-=(const VectorC & point);
    // Removes one point from the set of data points. Be carefull to remove
    // a point which was already added to the set, otherwise the representation
    // will not describe a real set.

    const MeanCovarianceNdC & operator+=(const MeanNdC & mean);
    // Adds a number of data poits represented by the 'mean' and zero
    // covariance matrix to this set.

    const MeanCovarianceNdC & operator-=(const MeanNdC & mean);
    // Removes a number of data poits represented by the 'mean' and zero
    // covariance matrix from this set. Be carefull to remove
    // points which were already added to the set, otherwise the representation
    // will not describe a real set.

    const MeanCovarianceNdC & operator+=(const MeanCovarianceNdC & meanCov);
    // Adds a number of data points represented by the 'meanCov' structure
    // to this set.

    const MeanCovarianceNdC & operator-=(const MeanCovarianceNdC & meanCov);
    // Removes a number of data points represented by the 'meanCov' structure
    // from this set. Be carefull to remove
    // points which were already added to the set, otherwise the representation
    // will not describe a real set.

    const MeanCovarianceNdC & Add(const VectorC & point, const VectorC & var);
    // Updates the mean and the covariance matrix by adding one N-d point
    // whose coordinates are known with the error described by the diagonal
    // convariance matrix represented byt the vector 'var'.

    const MeanCovarianceNdC &Remove(const VectorC & point, const VectorC & var);
    // Updates the mean and the covariance matrix by removing one N-d point
    // whose coordinates are known with the error described by the diagonal
    // convariance matrix represented byt the vector 'var'.
    // Be carefull to remove the point which was already added
    // to the set, otherwise the representation
    // will not describe a real set.

    const MeanCovarianceNdC & SetSum(const MeanCovarianceNdC & meanCov1,
                                     const MeanCovarianceNdC & meanCov2);
    // This object is set to be the union of two set of data points 'meanCov1'
    // and 'meanCov2'.

  protected:
    MeanNdC m;   // The mean vector of this data set.
    MatrixC cov; // the covariance matrix of this data set.
    
    friend istream & operator>>(istream & inS, MeanCovarianceNdC & meanCov);
  };
  
  ostream & operator<<(ostream & outS, const MeanCovarianceNdC & meanCov);
  // Saves the statistical description of the set 'meanCov' into the output
  // stream 'outS'.
  
  istream & operator>>(istream & inS, MeanCovarianceNdC & meanCov);
  // Reads and sets the statistical description of the set 'meanCov'
  // according to the information in the input stream 'inS'.
}
#endif

