# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
# $Id$
#! rcsid="$Id$"
#! file="Ravl/Core/Container/Hash/defs.mk"

PACKAGE=Ravl

HEADERS= Hash.hh HashIter.hh BiHash.hh RCHash.hh HSet.hh HSetExtra.hh

SOURCES= Hash.cc

PLIB=RavlCore

LIBDEPS=RavlHash.def

USESLIBS=RavlCore

EXAMPLES=exHash.cc WordFreq.cc

TESTEXES = testHash.cc testHSet.cc

EHT= Ravl.Core.Hash_Tables.eht

