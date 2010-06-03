// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: GaussianMixtureIO.cc 3073 2003-06-13 07:18:32Z craftit $"
//! lib=RavlPatternRecIO
//! file="Ravl/PatternRec/IO/GaussianMixtureIO.cc"

#include "Ravl/Vector.hh"
#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/Types.hh"

#include "Ravl/PatternRec/GaussianMixture.hh"

namespace RavlN {
  void InitRavlGaussianMixtureIO()
  {}
  
  static TypeNameC type1(typeid(GaussianMixtureC),"RavlN::GaussianMixtureC");
  
  FileFormatStreamC<GaussianMixtureC> FileFormatStream_GaussianMixture;
  FileFormatBinStreamC<GaussianMixtureC> FileFormatBinStream_GaussianMixture;
  
  FunctionC GaussianMixture2Function(const GaussianMixtureC &func)
  { return func; }
  
  DP_REGISTER_CONVERSION_NAMED(GaussianMixture2Function ,1,
			       "RavlN::FunctionC RavlN::Convert(const RavlN::GaussianMixture2FunctionC &)");


}
