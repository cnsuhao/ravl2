// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/LinearAlgebra/General/MatrixInverse.cc"

#include "Ravl/Matrix.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/CCMath.hh"
#include "Ravl/Vector.hh"

#define DODEBUG 0
#if DODEBUG 
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  
  //: Calculate the inverse of this matrix.
  
  MatrixC MatrixC::Inverse() const {
    MatrixC ret = Copy();
    if(!ret.InverseIP()) {
      // Could throw an exception ?
      return MatrixC(); 
    }
    return ret;
  }

  //: Do a pseudo inverse 
  // Uses singular value decomposition to decompose the matrix, and sets
  // the singular values smaller than 'thesh' to zero.
  
  MatrixC MatrixC::PseudoInverse(RealT thresh) const {
    MatrixC U, V;
    ONDEBUG(cerr << "*this=" << *this << "\n");
    VectorC D=SVD(*this,U,V);
    ONDEBUG(cerr << "U=" << U << "\n");
    //ONDEBUG(cerr << "V=" << V << "\n");
    ONDEBUG(cerr << "V=" << V.Size1() << " " << V.Size2() << "\n");
    ONDEBUG(cerr << "D=" << D << "\n");
    
    // Invert diagonal
    RealT aver = D.Sum() / D.Size();
    for(SArray1dIterC<RealT> it(D);it;it++) {
      if(IsSmall(*it,aver,thresh)) {
	//cerr << "Index " << it.Index() << " is small. \n";
	*it = 0;
      } else
	*it = 1 / *it;
    }
    MatrixC md(V.Size2(),U.Size2());
    md.Fill(0);
    int x = Min(D.Size(),md.Size1(),md.Size2());
    for(int i = 0;i < x;i++)
      md[i][i] = D[i]; // Set all the diagonal elements we've got.
    return (V * md).MulT(U);
  }
  
  
  /*
   *------------------------------------------------------------------------
   *
   *		The most general (Gauss-Jordan) matrix inverse
   *
   * This method works for any matrix (which of course must be square and
   * non-singular). Use this method only if none of specialized algorithms
   * (for symmetric, tridiagonal, etc) matrices isn't applicable/available.
   * Also, the matrix to invert has to be _well_ conditioned:
   * Gauss-Jordan eliminations (even with pivoting) perform poorly for
   * near-singular matrices (e.g., Hilbert matrices).
   *
   * The method inverts matrix inplace and returns the determinant if
   * determ_ptr was specified as not nil. determinant will be exactly zero
   * if the matrix turns out to be (numerically) singular. If determ_ptr is
   * nil and matrix happens to be singular, throw up.
   *
   * The algorithm perform inplace Gauss-Jordan eliminations with
   * full pivoting. It was adapted from my Algol-68 "translation" (ca 1986)
   * of the FORTRAN code described in
   * Johnson, K. Jeffrey, "Numerical methods in chemistry", New York,
   * N.Y.: Dekker, c1980, 503 pp, p.221
   *
   * Note, since it's much more efficient to perform operations on matrix
   * columns rather than matrix rows (due to the layout of elements in the
   * matrix), the present method implements a "transposed" algorithm.
   *
   */
  
  struct PivotC { int row, col; };
  
  //: Calculate the inverse of this matrix.
  
  bool MatrixC::InverseIP(RealT &det) {
    RavlAlwaysAssertMsg(Cols() == Rows(),"MatrixC::InverseIP(), Matrix must be square to invert ");
    
    if(IsContinuous())
      return minv(&(*this)[0][0],Rows()) == 0; // ccmath routine.
    
    // FIXME:- Should either copy matrix to continous memory,
    // or make a version of the ccmath routine that will work
    // with seperate rows?
    // ----------------------------------------------------------
    
    // This can cope with non-continous matrixes, but its 
    // a little slower and less accurate.  I figure this 
    // is quicker than coping the matrix ??
    // I'm not sure I like doing this.
    
    double determinant = 1;
    const double singularity_tolerance = 1e-35;
    
    // Locations of pivots (indices start with 0)
    
    SArray1dC<PivotC> pivots(Cols());
    SArray1dC<bool> was_pivoted(Rows());
    was_pivoted.Fill(false);
    
    register PivotC * pivotp;
    const PivotC *endofrow = &(&pivots[0])[Rows()];
    for(pivotp = &pivots[0]; pivotp < endofrow; pivotp++){
      unsigned int prow = 0,pcol = 0;		// Location of a pivot to be
      
      {					// Look through all non-pivoted Cols()
	RealT max_value = 0;		// (and Rows()) for a pivot (max elem)
	for(register unsigned int j=0; j<Rows(); j++)
	  if( !was_pivoted[j] ) {
	    register RealT * cp =0;
	    register unsigned int k = 0;
	    RealT curr_value = 0;
	    for(k=0,cp=(*this)[j].DataStart(); k<Cols(); k++,cp++)
	      if( !was_pivoted[k] && (curr_value = fabs(*cp)) > max_value )
		max_value = curr_value, prow = k, pcol = j;
	  }
	if( max_value < singularity_tolerance ) {
	  //cerr << "Matrix turns out to be singular: can't invert";
	  return 0;
	}
	pivotp->row = prow;
	pivotp->col = pcol;
      }
      
      if( prow != pcol ) {			// Swap prow-th and pcol-th columns to
	                                       // bring the pivot to the diagonal
	register RealT * cr = (*this)[prow].DataStart();
	register RealT * cc = (*this)[pcol].DataStart();
	for(register unsigned int k=0; k<Cols(); k++) {
	  RealT temp = *cr; *cr++ = *cc; *cc++ = temp;
	}
      }
      was_pivoted[prow] = true;
      
      {					// Normalize the pivot column and
	register RealT * pivot_cp = (*this)[prow].DataStart();
	double pivot_val = pivot_cp[prow];	// pivot is at the diagonal
	determinant *= pivot_val;		// correct the determinant
	pivot_cp[prow] = true;
	for(register unsigned int k=0; k<Cols(); k++)
	  *pivot_cp++ /= pivot_val;
      }
      
      {					// Perform eliminations
	register RealT * pivot_rp = (*this)[0].DataStart() + prow;	// pivot row
	for(register unsigned int k=0; k<Cols(); k++, pivot_rp += Cols())
	  if( k != prow ) {
	    double temp = *pivot_rp;
	    *pivot_rp = 0;
	    register RealT * pivot_cp = (*this)[prow].DataStart();	// pivot column
	    register RealT * elim_cp  = (*this)[k].DataStart();		// elimination column
	      for(register unsigned int l=0; l<Cols(); l++)
		*elim_cp++ -= temp * *pivot_cp++;
	  }
      }
    }
    
    int no_swaps = 0;		// Swap exchanged *Rows()* back in place
    for(pivotp = &pivots[Rows()-1]; pivotp >= &pivots[0]; pivotp--)
      if( pivotp->row != pivotp->col ) {
	no_swaps++;
	register RealT * rp = (*this)[0].DataStart() + pivotp->row;
	register RealT * cp = (*this)[0].DataStart() + pivotp->col;
	for(register unsigned int k=0; k<Rows(); k++, rp += Cols(), cp += Cols()) {
	  RealT temp = *rp; *rp = *cp; *cp = temp;
	}
      }
    
    det = (no_swaps & 1 ? -determinant : determinant );
    return (det != 0);
  }

}
