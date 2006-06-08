# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Logic/NonLinearPlanner/defs.mk"

PACKAGE=Ravl/Logic

MAINS=

HEADERS=NLPCausalLink.hh NLPStep.hh NLPAgendaItem.hh NLPAction.hh NLPAgenda.hh \
 NonLinearPlan.hh NLPTypes.hh NLPlanner.hh

SOURCES=NLPCausalLink.cc NLPStep.cc NLPAgendaItem.cc NLPAction.cc NLPAgenda.cc \
 NonLinearPlan.cc NLPlanner.cc

TESTEXES=testNonLinearPlanner.cc

PLIB=RavlLogicNLP

USESLIBS=RavlLogic

EXAMPLES= exNonlinearPlanner.cc

EHT=Ravl.API.Logic.Planning.html
