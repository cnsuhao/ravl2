# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"

PACKAGE=Ravl

HEADERS= FFT1d.hh PowerSpectrum1d.hh Correlation1d.hh RealCepstral.hh

SOURCES= FFT1d.cc PowerSpectrum1d.cc Correlation1d.cc RealCepstral.cc

PLIB = RavlMath

LIBDEPS=RavlSignal1.def

EXAMPLES = exFFT1d.cc exPowerSpectrum.cc

USESLIBS= RavlMath
