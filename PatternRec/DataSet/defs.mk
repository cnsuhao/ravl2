# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/PatternRec/DataSet/defs.mk"

DESCRIPTION = Basic parts of the Pattern Recognition library.

PACKAGE = Ravl/PatternRec

HEADERS = Sample.hh SampleIter.hh SampleVector.hh SampleLabel.hh SampleDiscrete.hh \
 DataSetBase.hh \
 DataSet1.hh DataSet1Iter.hh DataSet2.hh DataSet2Iter.hh \
 DataSet3.hh DataSet3Iter.hh SampleIO.hh \
 Function.hh Function1.hh Designer.hh DesignFunctionUnsupervised.hh DesignFunctionSupervised.hh \
 VectorLabelIO.hh DataSetVectorLabel.hh SampleStream.hh

SOURCES = SampleVector.cc SampleLabel.cc DataSetBase.cc \
 Function.cc Function1.cc Designer.cc DesignFunctionUnsupervised.cc DesignFunctionSupervised.cc \
 VectorLabelIO.cc DataSetVectorLabel.cc

MAINS = 

PLIB = RavlPatternRec

EXAMPLES = exSample.cc

TESTEXES=testDataSet.cc

USESLIBS=RavlCore RavlMath RavlOSIO RavlIO

PROGLIBS=RavlOS

EHT=Ravl.Pattern_Recognition.Data_Set.html
