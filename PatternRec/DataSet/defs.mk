# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/PatternRec/DataSet/defs.mk"
DESCRIPTION = Pattern Recognition

PACKAGE = Ravl/PatternRec

HEADERS = Sample.hh SampleVector.hh SampleLabel.hh SampleDiscrete.hh \
 DataSetBase.hh \
 DataSet1.hh DataSet1Iter.hh DataSet2.hh DataSet2Iter.hh \
 DataSet3.hh DataSet3Iter.hh

SOURCES = SampleVector.cc SampleLabel.cc DataSetBase.cc

MAINS = exSample.cc

PLIB = RavlPatternRec

TESTEXES=testDataSet.cc

USESLIBS=RavlCore RavlMath

PROGLIBS=RavlOS

EHT=Ravl.Pattern_Recognition.Data_Set.html
