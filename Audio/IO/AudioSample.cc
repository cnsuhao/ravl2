// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlAudioIO

#include "Ravl/Vector.hh"
#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/Types.hh"
#include "Ravl/Audio/Types.hh"

namespace RavlAudioN {
  void InitAudioSample()
  {}
  
  static TypeNameC type1(typeid(SampleElemC<2,Int16T>),"RavlAudioN::SampleElemC<2,Int16T>");
  
  // This could be optimised for converting blocks of data. Later.
  
  static Int16T Sample2Int16ToInt16(const SampleElemC<2,Int16T> &samp) 
  { return (Int16T) (((IntT) samp.channel[0] + (IntT) samp.channel[1])/2); }
  
  static IntT ConvInt162Int(const Int16T &v)
  { return (IntT) v; }

  static RealT ConvFloat2Real(const FloatT &v)
  { return (RealT) v; }

  DP_REGISTER_CONVERSION_NAMED(Sample2Int16ToInt16,1,"Int16T RavlAudioN::Convert(const SampleElemC<2,Int16T> &)");
  DP_REGISTER_CONVERSION_NAMED(ConvInt162Int,1,"IntT RavlAudioN::Convert(const Int16T &)");
  DP_REGISTER_CONVERSION_NAMED(ConvFloat2Real,1,"RealT RavlAudioN::Convert(const FloatT &)");
  
  
}
