# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2002, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"

DESCRIPTION = Dimension reduction.

PACKAGE = Ravl/PatternRec

HEADERS=Reduce.hh ReduceSubset.hh ReduceLinear.hh ReducePCA.hh

SOURCES=Reduce.cc ReduceSubset.cc ReduceLinear.cc ReducePCA.cc

PLIB=RavlPatternRec

LIBDEPS = RavlPatternRecDimReduce.def 

USESLIBS=RavlPatternRec
