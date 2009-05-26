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

HEADERS= PDFContinuousDesigner.hh \
         PDFContinuousDesignerNormal.hh \
         PDFContinuousDesignerUniform.hh \
         PDFDesignerFactory.hh \
         PDFAbstract.hh \
         PDFBoolean.hh \
         PDFContinuousAbstract.hh \
         PDFDiscrete.hh \
         PDFNormal.hh \
         PDFProbit.hh \
         PDFUniform.hh \
         ProbabilityDistribution.hh

SOURCES= PDFContinuousDesigner.cc \
         PDFContinuousDesignerNormal.cc \
         PDFContinuousDesignerUniform.cc \
         PDFDesignerFactory.cc \
         PDFAbstract.cc \
         PDFBoolean.cc \
         PDFContinuousAbstract.cc \
         PDFDiscrete.cc \
         PDFNormal.cc \
         PDFProbit.cc \
         PDFUniform.cc \
         ProbabilityDistribution.cc

MAINS=

USESLIBS=RavlCore RavlOS

TESTEXES=

PROGLIBS=

PLIB=RavlProb
