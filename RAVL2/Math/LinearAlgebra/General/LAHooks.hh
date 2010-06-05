/*
 * LAHooks.hh
 *
 *  Created on: 2 Mar 2010
 *      Author: Alexey Kostin
 */

#ifndef LAHOOKS_HH_
#define LAHOOKS_HH_

namespace RavlN {
  class VectorC;
  class MatrixC;
  class MatrixRUTC;

  extern bool (*g_EigenVectorsSymmetric)(VectorC &resVals, MatrixC &resVecs, const MatrixC &M);

  inline bool EigenVectorsSymmetric(VectorC &resVals, MatrixC &resVecs, const MatrixC &M)
  { return (*g_EigenVectorsSymmetric)(resVals, resVecs, M); }



  extern void (*g_AddOuterProduct)(MatrixRUTC &matr, const VectorC &vec);
  inline void AddOuterProduct(MatrixRUTC &matr, const VectorC &vec)
  { (*g_AddOuterProduct)(matr, vec); }

  extern void (*g_AddOuterProduct1)(MatrixRUTC &matr, const VectorC &vec, double a);
  inline void AddOuterProduct(MatrixRUTC &matr, const VectorC &vec, double a)
  { (*g_AddOuterProduct1)(matr, vec, a); }

  extern void (*g_SubtractOuterProduct)(MatrixRUTC &matr, const VectorC &vec);
  inline void SubtractOuterProduct(MatrixRUTC &matr, const VectorC &vec)
  { (*g_SubtractOuterProduct)(matr, vec); }

  extern void (*g_SubtractOuterProduct1)(MatrixRUTC &matr, const VectorC &vec, double a);
  inline void SubtractOuterProduct(MatrixRUTC &matr, const VectorC &vec, double a)
  { (*g_SubtractOuterProduct1)(matr, vec, a); }

}

#endif /* LAHOOKS_HH_ */
