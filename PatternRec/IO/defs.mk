# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/PatternRec/IO/defs.mk"

DESCRIPTION= Pattern recognition data IO.

HEADERS= 
#VectorIOText.hh

SOURCES= SampleIO.cc DataSetIO.cc ClassifierIO.cc Classifier2IO.cc \
 FunctionIO.cc GaussianMixtureIO.cc DistanceIO.cc

#VectorIOText.cc

MUSTLINK= RavlPatternRecIO.cc

PLIB= RavlPatternRecIO

USESLIBS=RavlCore RavlIO RavlPatternRec
