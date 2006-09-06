# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2004, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/Processing/ChartDetector/defs.mk"

PACKAGE=Ravl/Image

MAINS=chartdet.cc

HEADERS= ChartDetector.hh ChartDetectorRegion.hh ChartLocalise.hh \
 CostAffineImageCorrelation.hh

SOURCES= ChartDetector.cc ChartDetectorRegion.cc ChartLocalise.cc \
 CostAffineImageCorrelation.cc

PLIB=RavlChartDetector

USESLIBS=RavlImage RavlImageProc RavlImageIO  Optimisation

PROGLIBS=RavlDPDisplay.opt RavlExtImgIO RavlOS

AUXFILES=CalibrationChart.ps CalibrationChart.jpg CalibrationChart.coords

AUXDIR=share/RAVL/pixmaps
