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

DONOT_SUPPORT=arm mingw 

PACKAGE=Ravl/Prob

REQUIRES= CPPUnit

HEADERS= 

SOURCES=

MAINS= testRunner.cc

EXAMPLES= testRunnerQt.cc

MUSTLINK= testDomainDiscrete.cc \
		testLottery.cc \
		testVariableSet.cc \
		testCPDBooleanContinuous1.cc \
		testCPDContinuousDiscrete1.cc \
		testCPDDesignerContinuousDiscrete1.cc \
		testCPDDesignerFactory.cc \
		testCPDDiscreteDiscrete.cc \
		testCPDPriorPDF.cc \
		testPDFBoolean.cc \
		testPDFContinuousDesignerNormal.cc \
		testPDFContinuousDesignerUniform.cc \
		testPDFDesignerFactory.cc \
		testPDFDiscrete.cc \
		testPDFNormal.cc \
		testPDFProbit.cc \
		testPDFUniform.cc \
		testPropositionSet.cc \
		testVariableBoolean.cc \
		testVariableContinuous.cc \
		testVariableDiscrete.cc \
		testVariablePropositionBoolean.cc \
		testVariablePropositionContinuous.cc \
		testVariablePropositionDiscrete.cc

USESLIBS= RavlCore RavlOS RavlProb

TESTEXES= testRunner.cc

PROGLIBS= CPPUnit #QtTestRunner

PLIB= RavlProbUnitTest
