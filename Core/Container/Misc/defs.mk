# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
# $Id$
#! rcsid="$Id$"

PACKAGE=Ravl

HEADERS=Stack.hh StackIt.hh \
 Tuple2.hh Tuple3.hh Tuple4.hh

SOURCES=Stack.cc

PLIB=RavlCore

LIBDEPS=RavlCMisc.def

USESLIBS=RavlCore

TESTEXES=testStack.cc testQueue.cc

EHT=Ravl.Core.Stacks.eht Ravl.Core.Tuples.eht
