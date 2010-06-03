// This file is used in conjunction with RAVL, Recognition And Vision Library
// Copyright (C) 2007, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
// $Id: lapack.cc 7644 2010-03-02 17:07:52Z alexkostin $

#include "lapack.hh"
#include "ev_c.hh"

namespace LapackN
{

//! compute eigen values and eigen vectors of symmetric matrix
RavlN::VectorMatrixC EigenVectorsSymmetric(const RavlN::MatrixC &M)
{
  /*//copy double precision matrix to single precision storage
  //float *m = (float*)alloca(M.Size() * sizeof(float));
  float *m = (float*)malloc(M.Size() * sizeof(float));
  float *mPtr = m;
  for(RavlN::SArray2dIterC<double> it(M); it; it++, mPtr++)
    *mPtr = *it;

  //float *eValues = (float*)alloca(M.Size()*sizeof(float));
  float *eValues = (float*)malloc(M.Size()*sizeof(float));

  ssyev_c(M.Size1(), m, eValues, true, true, true, false);

  RavlN::VectorMatrixC res(M.Size1());

  //copy results to double precision
  mPtr = m;
  for(RavlN::SArray2dIterC<double> it(res.Matrix()); it; it++, mPtr++)
    *it = *mPtr;

  float *eValuesPtr = eValues;
  for(RavlN::SArray1dIterC<double> it(res.Vector()); it; it++, eValuesPtr++)
    *it = *eValuesPtr;

  free(m);
  free(eValues);
  return res;*/
  RavlN::VectorMatrixC res(RavlN::VectorC(M.Size1()), M.Copy());
  dsyev_c(M.Size1(), &(res.Matrix()[0][0]), &(res.Vector()[0]),
          true, true, true, false);
  return res;
}

}//end of namespace
