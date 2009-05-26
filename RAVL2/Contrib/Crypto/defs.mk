# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id"
#! file="Ravl/Contrib/Crypto/defs.mk"

DONOT_SUPPORT=VCPP

PACKAGE=Ravl/Crypto

USESLIBS=LibMCrypt RavlCore

REQUIRES=libmcrypt

HEADERS=MCrypt.hh

SOURCES=MCrypt.cc

PLIB=RavlCrypto

AUXDIR=lib/RAVL/libdep

AUXFILES=LibMCrypt.def

