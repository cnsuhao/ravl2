# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/PatternRec/defs.mk"

DESCRIPTION = Pattern Recognition Feature Selection

PACKAGE=Ravl/PatternRec

HEADERS= FeatureSelector.hh FeatureSelectAsymmetricAdaBoost.hh

SOURCES= FeatureSelector.cc FeatureSelectAsymmetricAdaBoost.cc

PLIB = RavlPatternRec

LIBDEPS=RavlPatternRecFeatureSelection.def

USESLIBS=RavlPatternRec

EHT=Ravl.Pattern_Recognition.Feature_Selection.html
