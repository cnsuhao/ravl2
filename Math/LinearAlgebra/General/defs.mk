# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Math/LinearAlgebra/General/defs.mk"

PACKAGE=Ravl

DESCRIPTION= General Linear Algebra

HEADERS = TVector.hh TMatrix.hh Matrix.hh Vector.hh MatrixRUT.hh \
 MatrixRS.hh LeastSquares.hh VectorMatrix.hh MatrixDecomposition.hh \
 TSMatrix.hh TSMatrixFull.hh TSMatrixPartial.hh TSMatrixDiagonal.hh \
 TSMatrixRightUpper.hh TSMatrixLeftLower.hh TSMatrixSparse.hh \
 TSMatrixScaledIdentity.hh TSMatrixPositiveDefinite.hh SMatrix.hh

SOURCES = TMatrix.cc Matrix.cc MatrixInverse.cc MatrixSVD.cc \
 MatrixEigen.cc MatrixSolve.cc MatrixRUT.cc MatrixRS.cc Vector.cc \
 MatrixNearSingular.cc LeastSquares.cc VectorMatrix.cc MatrixRandom.cc \
 MatrixDeterminant.cc MatrixLUDecomposition.cc TSMatrixSparse.cc \
 SMatrix.cc

MAINS= benchmarkSMatrix.cc
#EXAMPLES = exVMT.cc

TESTEXES=testTMatrix.cc testMatInv.cc testMatrix.cc testTSMatrix.cc
#testSVD.cc

PLIB=RavlMath

USESLIBS=Math RavlCore ccmath 

PROGLIBS=RavlOS