// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRecIO

#include "Ravl/Vector.hh"
#include "Ravl/PatternRec/Classifier.hh"
#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/Types.hh"

namespace RavlN {
  void InitRavlClassifierIO()
  {}
  
  static TypeNameC type1(typeid(ClassifierC),"RavlN::ClassifierC");
  
  FileFormatStreamC<ClassifierC> FileFormatStream_ClassifierC;
  FileFormatBinStreamC<ClassifierC> FileFormatBinStream_ClassifierC;
  
}
