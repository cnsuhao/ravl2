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

HEADERS= CPDAbstract.hh \
	 CPDBooleanContinuous1.hh \
         CPDContinuousDiscrete1.hh \
         CPDDiscreteDiscrete.hh \
         CPDDesigner.hh \
         CPDDesignerContinuousDiscrete1.hh \
         CPDDesignerFactory.hh \
         CPDPriorPDF.hh \
         ConditionalProbabilityDistribution.hh

SOURCES= CPDAbstract.cc \
         CPDBooleanContinuous1.cc \
         CPDContinuousDiscrete1.cc \
         CPDDiscreteDiscrete.cc \
         CPDDesigner.cc \
         CPDDesignerContinuousDiscrete1.cc \
         CPDDesignerFactory.cc \
         CPDPriorPDF.cc \
         ConditionalProbabilityDistribution.cc

MAINS=

USESLIBS=RavlCore RavlOS

TESTEXES=

PROGLIBS=

PLIB=RavlProb
