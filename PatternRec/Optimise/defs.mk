# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
DESCRIPTION = Optimisation

PACKAGE = Ravl/PatternRec

#SUPPORT_ONLY = sgi

SOURCES = Parameters.cc Cost.cc CostInvert.cc CostFunction.cc \
	Optimise.cc OptimiseDescent.cc OptimiseRandomUniform.cc

HEADERS = Parameters.hh Cost.hh CostInvert.hh CostFunction.hh \
	 Optimise.hh OptimiseDescent.hh OptimiseRandomUniform.hh

PLIB = Optimisation

USESLIBS = RavlCore RavlPatternRec

EXAMPLES = 

EHT = 

HTML = 

LOCAL_FILES = 

DOCNODE = 

