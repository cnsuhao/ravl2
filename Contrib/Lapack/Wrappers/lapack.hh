// This file is used in conjunction with RAVL, Recognition And Vision Library
// Copyright (C) 2007, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
// $Id: lapack.hh 7644 2010-03-02 17:07:52Z alexkostin $
#ifndef LAPACK_H
#define LAPACK_H

#include "Ravl/VectorMatrix.hh"

namespace LapackN
{
  //! compute eigen values and eigen vectors of symmetric matrix
  RavlN::VectorMatrixC EigenVectorsSymmetric(const RavlN::MatrixC &M);

}//end of namespace

#endif
