// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/FileFormatBinStream.cc"

#include "Ravl/DP/FileFormatBinStream.hh"

namespace RavlN {
  
  void InitFileFormatBinStream() 
  {}
  
  // Some basic file types.
  
  FileFormatBinStreamC<RealT>   FileFormatBinStream_RealT;
  FileFormatBinStreamC<IntT>    FileFormatBinStream_IntT;
  FileFormatBinStreamC<UIntT>   FileFormatBinStream_UIntT;
  FileFormatBinStreamC<StringC> FileFormatBinStream_StringC;
  FileFormatBinStreamC<ByteT>   FileFormatBinStream_ByteT;
}
