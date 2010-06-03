# This file is part of RAVL, Recognition And Vision Library
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 7644 2010-03-02 17:07:52Z alexkostin $"

PACKAGE      = Ravl/Lapack

DESCRIPTION  = RAVL wrapper around Lapack library

REQUIRES = LAPACK
#SUPPORT_ONLY = linux

#MAINS        = simpletest.cc

HEADERS      = ev_c.hh   \
               blas2.hh  \
               blas2_c.hh

SOURCES      = ev_c.cc   \
               blas2.cc  \
               blas2_c.cc

PLIB         = RavlLapackWraps

USESLIBS     = LibLapack

AUXDIR       = lib/RAVL/libdep

AUXFILES     = LibLapack.def

PROGLIBS     = #RavlDPDisplay.opt

