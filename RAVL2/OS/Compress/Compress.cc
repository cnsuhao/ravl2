// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! author="Charles Galambos"
//! docentry="Ravl.OS.Compression"

#include "Ravl/Compress.hh"
#include <zlib.h>

namespace RavlN {
  
  //: Compress data into 'buff'
  
  bool CompressZLib(const SArray1dC<char> &data,SArray1dC<char> &buff,IntT level) {
    if(data.Size() == 0) {
      buff = SArray1dC<char>();
      return true;
    }
    uLongf len = compressBound(data.Size());
    buff = SArray1dC<char>(len);
    int ret = 0;
    if((ret = compress2(reinterpret_cast<Bytef *>(&(buff[0])),&len,reinterpret_cast<const Bytef *>(&(data[0])),data.Size(),level)) != Z_OK) {
      //cerr << "Compress failed " << ret << "\n";
      return false;
    }
    buff = SArray1dC<char>(buff,len);
    return true;
  }
  
  //: Decompress buff into data.
  
  bool DecompressZLib(const SArray1dC<char> &buff,SArray1dC<char> &data,UIntT originalSize) {
    if(buff.Size() == 0) {
      data = SArray1dC<char>();
      return true;
    }
    uLongf len = originalSize;
    data = SArray1dC<char>(len);
    if(uncompress(reinterpret_cast<Bytef *>(&(data[0])),&len,reinterpret_cast<const Bytef *>(&(buff[0])),buff.Size()) != Z_OK)
      return false;
    if(len != originalSize) // Need to trim the buffer?
      data = SArray1dC<char>(data,len);
    return true;    
  }
  
  
}

