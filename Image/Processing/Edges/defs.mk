# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
# $Id$
#! rcsid="$Id$"

DESCRIPTION =Edge detection

PACKAGE=Ravl/Image

HEADERS=EdgeSobel.hh EdgeDeriche.hh SqrComposition.hh \
 EdgeNonMaxSuppression.hh Edgel.hh

# EdgeLink.hh

SOURCES=EdgeSobel.cc EdgeDeriche.cc SqrComposition.cc \
 EdgeNonMaxSuppression.cc Edgel.cc
# EdgeLink.cc

PLIB=RavlImageProc

LIBDEPS=RavlImageEdges.def

USESLIBS=RavlImage RavlThreads
