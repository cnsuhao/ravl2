# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2006, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! author="Robert Crida"

LICENSE=LGPL

ORGANISATION=SKA/KAT

DESCRIPTION=Pattern recognition software

PACKAGE=Ravl/Prob

HEADERS= BayesianNetwork.hh \
         BayesianNetworkAbstract.hh \
         BayesianNetworkSimple.hh

SOURCES= BayesianNetwork.cc \
         BayesianNetworkAbstract.cc \
         BayesianNetworkSimple.cc

MAINS= 

USESLIBS=RavlCore RavlOS

TESTEXES= testBayesianNetwork.cc
EXAMPLES= testBayesianNetwork.cc

PROGLIBS=

PLIB=RavlProb
