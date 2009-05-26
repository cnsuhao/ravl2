// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/FileFormatStream.cc"

#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/TypeName.hh"

namespace RavlN {
  void IncludeFileFormatStream() 
  {  }
  
  // Some basic file types.
  
  FileFormatStreamC<RealT> FileFormatStream_RealT;
  FileFormatStreamC<IntT> FileFormatStream_IntT;
  FileFormatStreamC<UIntT> FileFormatStream_UIntT;
  FileFormatStreamC<StringC> FileFormatStream_StringC;
  FileFormatStreamC<ByteT> FileFormatStream_ByteT;
}
