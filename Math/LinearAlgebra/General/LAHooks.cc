/*
 * LAHooks.cc
 *
 *  Created on: 2 Mar 2010
 *      Author: Alexey Kostin
 */

#include "Ravl/LAHooks.hh"

#include "Ravl/Vector.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/MatrixRUT.hh"
#include "Ravl/VectorMatrix.hh"
#include "Ravl/Eigen.hh"


namespace RavlN {

static bool EigenVectorsSymmetric_default(VectorC &resVals, MatrixC &resVecs, const MatrixC &mat) {
  EigenValueC<RealT> ev(mat);
  resVals = ev.EigenValues();
  resVecs = ev.EigenVectors();
  return true;
}


//: Add outer product of 'vec' with itself to this matrix.
static void AddOuterProduct_default(MatrixRUTC &matr, const VectorC &vec) {
  SArray2dIterC<RealT> mit(matr);
  int off = 0;
  for(BufferAccessIterC<RealT> it(vec);it;it++) {
    const RealT v1 = (*it);
    for(BufferAccessIterC<RealT> it2 = it;it2;it2++,mit.NextCol())
      *mit += v1 * (*it2);
    mit.NextRow(++off);
  }
}

//: Add outer product of 'vec' with itself to this matrix.
static void AddOuterProduct1_default(MatrixRUTC &matr, const VectorC &vec,RealT a) {
  SArray2dIterC<RealT> mit(matr);
  int off = 0;
  for(BufferAccessIterC<RealT> it(vec);it;it++) {
    const RealT v1 = *it * a;
    for(BufferAccessIterC<RealT> it2 = it;it2;it2++,mit.NextCol())
      *mit += v1 * (*it2);
    mit.NextRow(++off);
  }
}

//: Subtract outer product of 'vec' with itself to this matrix.
static void SubtractOuterProduct_default(MatrixRUTC &matr, const VectorC &vec) {
  SArray2dIterC<RealT> mit(matr);
  int off = 0;
  for(BufferAccessIterC<RealT> it(vec);it;it++) {
    const RealT v1 = (*it);
    for(BufferAccessIterC<RealT> it2 = it;it2;it2++,mit.NextCol())
      *mit -= v1 * (*it2);
    mit.NextRow(++off);
  }
}

//: Subtract outer product of 'vec' with itself to this matrix.
static void SubtractOuterProduct1_default(MatrixRUTC &matr, const VectorC &vec,RealT a) {
  SArray2dIterC<RealT> mit(matr);
  int off = 0;
  for(BufferAccessIterC<RealT> it(vec);it;it++) {
    const RealT v1 = *it * a;
    for(BufferAccessIterC<RealT> it2 = it;it2;it2++,mit.NextCol())
      *mit -= v1 * (*it2);
    mit.NextRow(++off);
  }
}


bool (*g_EigenVectorsSymmetric)(VectorC &resVals, MatrixC &resVecs, const MatrixC &M) = &EigenVectorsSymmetric_default;

void (*g_AddOuterProduct)(MatrixRUTC &matr, const VectorC &vec) = &AddOuterProduct_default;
void (*g_AddOuterProduct1)(MatrixRUTC &matr, const VectorC &vec, RealT a) = &AddOuterProduct1_default;
void (*g_SubtractOuterProduct)(MatrixRUTC &matr, const VectorC &vec) = &SubtractOuterProduct_default;
void (*g_SubtractOuterProduct1)(MatrixRUTC &matr, const VectorC &vec, RealT a) = &SubtractOuterProduct1_default;


}
