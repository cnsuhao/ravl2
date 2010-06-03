/*
 * LAHooksLAPACK.cc
 *
 *  Created on: 2 Mar 2010
 *      Author: Alexey Kostin
 */

#include "Ravl/LAHooks.hh"

#include "Ravl/Vector.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/Lapack/ev_c.hh"
#include "Ravl/Lapack/blas2.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {

//! compute eigen values and eigen vectors of symmetric matrix
static bool EigenVectorsSymmetric_LAPACK(VectorC &resVals, MatrixC &resVecs, const MatrixC &mat) {
  const SizeT mSize = mat.Size1();
  resVals = VectorC(mSize);
  resVecs = mat.Copy();
  dsyev_c(mSize, &(resVecs[0][0]), &(resVals[0]), true, true, true, false);
  return true;
}


//: Add outer product of 'vec' with itself to this matrix.
static void AddOuterProduct_LAPACK(MatrixRUTC &matr, const VectorC &vec) {
  AddOuterProduct(matr, vec, 1.);
}

//: Add outer product of 'vec' with itself to this matrix.
static void AddOuterProduct1_LAPACK(MatrixRUTC &matr, const VectorC &vec,RealT a) {
  AddOuterProduct(matr, vec, a);
}

//: Subtract outer product of 'vec' with itself to this matrix.
static void SubtractOuterProduct_LAPACK(MatrixRUTC &matr, const VectorC &vec) {
  AddOuterProduct(matr, vec, -1.);
}

//: Subtract outer product of 'vec' with itself to this matrix.
static void SubtractOuterProduct1_LAPACK(MatrixRUTC &matr, const VectorC &vec,RealT a) {
  AddOuterProduct(matr, vec, a);
}



int LAHooksLAPACKInit() {
  ONDEBUG(cerr << "using LAPACK\n");
  g_EigenVectorsSymmetric = &EigenVectorsSymmetric_LAPACK;
  g_AddOuterProduct = &AddOuterProduct_LAPACK;
  g_AddOuterProduct1 = &AddOuterProduct1_LAPACK;
  g_SubtractOuterProduct = &SubtractOuterProduct_LAPACK;
  g_SubtractOuterProduct1 = &SubtractOuterProduct1_LAPACK;
  return 0;
}

static int a = LAHooksLAPACKInit();

}
