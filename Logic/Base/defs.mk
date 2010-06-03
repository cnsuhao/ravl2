# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 5240 2005-12-06 17:16:50Z plugger $"
#! file="Ravl/Logic/Base/defs.mk"

PACKAGE=Ravl/Logic

MAINS= 
#testLogic.cc

HEADERS=Literal.hh Var.hh Unify.hh BindSet.hh Tuple.hh LList.hh Condition.hh \
 MinTerm.hh Or.hh And.hh Not.hh LiteralIter.hh LiteralIterWrap.hh LiteralMapIter.hh \
 LiteralMapListIter.hh State.hh LiteralIter1.hh StateOrIter.hh StateSet.hh \
 LiteralFilterIter.hh StateAndIter.hh NamedLiteral.hh NamedVar.hh LiteralIO.hh \
 MinTermIter.hh Value.hh Context.hh

SOURCES=Literal.cc Var.cc Unify.cc BindSet.cc Tuple.cc LList.cc Condition.cc \
 MinTerm.cc Or.cc And.cc Not.cc LiteralIter.cc State.cc LiteralIter1.cc \
 StateOrIter.cc StateSet.cc  LiteralFilterIter.cc StateAndIter.cc \
 NamedLiteral.cc NamedVar.cc LiteralIO.cc MinTermIter.cc Value.cc Context.cc

TESTEXES=testLogic.cc

PLIB=RavlLogic

USESLIBS=RavlCore RavlPatternRec

EHT=Ravl.API.Logic.Condition.html
