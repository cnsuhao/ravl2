# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
# $Id$
#! rcsid="$Id$"
#! file="Ravl/Core/Container/DList/defs.mk"

DESCRIPTION = Double linked lists.

PACKAGE=Ravl

HEADERS = DLink.hh DList.hh DLIter.hh CDLIter.hh IntrDList.hh IntrDLIter.hh

SOURCES = DLink.cc DList.cc 

PLIB=RavlCore

LIBDEPS=RavlList.def

USESLIBS = RavlCore

TESTEXES= testDList.cc

EXAMPLES= exDList.cc

EHT=Ravl.API.Core.Lists.eht


