# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/PatternRec/Optimise/defs.mk"
DESCRIPTION = Optimisation

PACKAGE = Ravl/PatternRec

#SUPPORT_ONLY = sgi

SOURCES = Parameters.cc Cost.cc CostInvert.cc CostFunction.cc CostFunction1d.cc \
        BracketMinimum.cc \
	Optimise.cc OptimiseDescent.cc OptimiseConjugateGradient.cc  OptimiseRandomUniform.cc \
	OptimiseSobol.cc OptimiseBrent.cc OptimisePowell.cc OptimiseGrid.cc OptimiseLevenbergMarquardt.cc

HEADERS = Parameters.hh Cost.hh CostInvert.hh CostFunction.hh CostFunction1d.hh \
        BracketMinimum.hh \
	Optimise.hh OptimiseDescent.hh OptimiseConjugateGradient.hh OptimiseRandomUniform.hh \
	OptimiseSobol.hh OptimiseBrent.hh OptimisePowell.hh OptimiseGrid.hh OptimiseLevenbergMarquardt.hh

MAINS = 

PLIB = Optimisation

USESLIBS = RavlCore RavlPatternRec

EXAMPLES = testBrent.cc

EHT = Optimise.html

HTML = 

LOCAL_FILES = 

DOCNODE = 

TESTEXES = testBrent.cc
