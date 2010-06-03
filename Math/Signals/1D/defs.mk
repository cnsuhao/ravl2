# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 737 2002-01-31 14:55:49Z craftit $"
#! file="Ravl/Math/Signals/1D/defs.mk"

PACKAGE=Ravl

HEADERS= FFT1d.hh PowerSpectrum1d.hh Correlation1d.hh RealCepstral.hh \
 Convolution1d.hh GenerateSignal1d.hh

SOURCES= FFT1d.cc PowerSpectrum1d.cc Correlation1d.cc RealCepstral.cc \
 GenerateSignal1d.cc
# Convolution1d.cc

PLIB = RavlMath

LIBDEPS=RavlSignal1.def

TESTEXES= testGenerateSignal1d.cc testSignal1d.cc

EXAMPLES = exFFT1d.cc exPowerSpectrum.cc

USESLIBS= RavlMath
