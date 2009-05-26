# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2006, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! author="Robert Crida"

LICENSE=LGPL

ORGANISATION=SKA/KAT.

DESCRIPTION=Pattern recognition software

PACKAGE=Ravl/Prob

HEADERS= DomainDiscrete.hh \
		 Variable.hh \
         VariableBoolean.hh \
         VariableContinuous.hh \
         VariableDiscrete.hh \
         VariableProposition.hh \
         VariablePropositionBoolean.hh \
         VariablePropositionContinuous.hh \
         VariablePropositionDiscrete.hh

SOURCES= DomainDiscrete.cc \
		 Variable.cc \
         VariableBoolean.cc \
         VariableContinuous.cc \
         VariableDiscrete.cc \
         VariableProposition.cc \
         VariablePropositionBoolean.cc \
         VariablePropositionContinuous.cc \
         VariablePropositionDiscrete.cc

MAINS=

USESLIBS=RavlCore RavlOS

TESTEXES=

PROGLIBS=RavlExtImgIO.opt RavlDPDisplay

PLIB=RavlProb
