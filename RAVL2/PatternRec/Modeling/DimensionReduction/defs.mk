# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2002, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 6979 2008-09-29 16:29:05Z ees1wc $"
#! file="Ravl/PatternRec/Modeling/DimensionReduction/defs.mk"

DESCRIPTION = Dimension reduction.

PACKAGE = Ravl/PatternRec

HEADERS=FuncSubset.hh DesignFuncReduce.hh DesignFuncPCA.hh  DesignFuncLDA.hh

SOURCES=FuncSubset.cc DesignFuncReduce.cc DesignFuncPCA.cc  DesignFuncLDA.cc

PLIB=RavlPatternRec

LIBDEPS = RavlPatternRecDimReduce.def 

USESLIBS=RavlPatternRec

EHT = Dimension_Reduction.html
