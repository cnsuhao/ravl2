// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlIO

#include "Ravl/DP/ByteStream.hh"

namespace RavlN {

  //: Write data to stream
  //!param: buffer - Buffer to write data from.
  //!param: len - length of buffer.
  //!return: true if write succeeded.
  
  IntT DPOByteStreamBodyC::Write(const char *buffer,IntT len) {
    SArray1dC<ByteT> tmp(reinterpret_cast<ByteT *>(const_cast<char *>(buffer)),len,false);
    return PutArray(tmp);
  }
  
  //: Read data from stream info buffer.
  //!param: buffer - Buffer to read data into.
  //!param: len - length of buffer.
  //!return: Number of bytes read or -1 on error
  
  IntT DPIByteStreamBodyC::Read(char *buffer,IntT len) {
    SArray1dC<ByteT> org(reinterpret_cast<ByteT *>(buffer),len,false);
    SArray1dC<ByteT> buf = org;
    IntT n = GetArray(buf);
    RavlAssert(buf.Buffer() == org.Buffer());
    return n;
  }

}
