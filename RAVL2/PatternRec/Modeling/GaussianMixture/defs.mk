# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2002, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/PatternRec/Modeling/GaussianMixture/defs.mk"

DESCRIPTION = Gaussian Mixture Modelling

PACKAGE = Ravl/PatternRec

MAINS=

TESTEXES=testGaussianMixture.cc 

HEADERS=GaussianMixture.hh DesignGaussianMixture.hh

SOURCES=GaussianMixture.cc DesignGaussianMixture.cc

PLIB=RavlPatternRec

LIBDEPS=RavlPatternGaussianMixture.def

USESLIBS=RavlCore RavlIO RavlMath RavlOS RavlPatternRec

AUXFILES=class5.strm

AUXDIR=share/RAVL/data
