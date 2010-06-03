// This file is used in conjunction with RAVL, Recognition And Vision Library
// Copyright (C) 2007, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
// $Id: blas2.cc 7674 2010-03-29 16:05:54Z alexkostin $
#include "blas2.hh"
#include "blas2_c.hh"

namespace BlasN
{
  void AddOuterProduct(RavlN::MatrixRUTC &M, const RavlN::VectorC &V, double alpha)
  {
    dsyr_c(M.Size1(), &(M[0][0]), &(V[0]), alpha, 1, true, true);
  }
} //end of namespace
