// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/ByteFileIO.cc"

#include "Ravl/DP/ByteFileIO.hh"

namespace RavlN {
  
  //:------------------------------------------------------------------
  // DPOByteFileC
  
  //: Put data.
  
  bool DPOByteFileBodyC::Put(const ByteT &dat) { 
    out.write((char *) &dat,1); 
    return out.good(); 
  }
  
  //: Put an array of data to stream.
  // returns the number of elements processed.
  
  IntT DPOByteFileBodyC::PutArray(const SArray1dC<ByteT> &data) {
    if(!out.good() || data.Size() == 0) 
      return 0;
    out.write((char *) &(data[0]),data.Size());
    return data.Size();
  }
  
  //: Is port ready for data ?
  
  bool DPOByteFileBodyC::IsPutReady() const 
  { return out.good(); }
  
  //: Save to ostream.
  
  bool DPOByteFileBodyC::Save(ostream &sout) const  { 
    sout << out.Name(); 
    return true; 
  }

  //:------------------------------------------------------------------
  // DPIByteFileC
  
  
  //: Is valid data ?
  
  bool DPIByteFileBodyC::IsGetEOS() const 
  { return (in.eof()) || !in.good(); }
    
  //: Get next piece of data.
  
  ByteT DPIByteFileBodyC::Get() { 
    if(in.IsEndOfStream())
      throw DataNotReadyC("DPIByteFileBodyC::Get(), End of input stream. ");
    ByteT ret;
    in.read((char *) &ret,1);
    off++;
    if(!in.good())
      throw DataNotReadyC("DPIByteFileBodyC::Get(), Bad input stream. ");    
    return ret; 
  }
  
  //: Get next piece of data.
  
  bool DPIByteFileBodyC::Get(ByteT &buff) { 
    if(in.IsEndOfStream())
      return false;
    in.read((char *)&buff,1);
    off++;
    return in.good();
  }
    
  //: Get multiple pieces of input data.
  // returns the number of elements processed.
  
  IntT DPIByteFileBodyC::GetArray(SArray1dC<ByteT> &data) {
    if(!in.good() || data.Size() == 0) 
	return 0;
    in.read((char *) &data[0],data.Size());
    off += data.Size();
    return data.Size();
  }
    
  //: Save to ostream.
  
  bool DPIByteFileBodyC::Save(ostream &out) const { 
    out << in.Name(); 
    return true; 
  }
    
  //: Seek to position in stream.
  // Currently will only seek to begining of stream.
  
  bool DPIByteFileBodyC::Seek(UIntT newOff) {
    in.is().clear(); // Clear any end of stream errors.
    in.Seek(static_cast<UIntT>(dataStart + static_cast<streampos>(newOff)));
    off = newOff;
    return true;
  }
  
  //: Get offset in stream.
  
  UIntT DPIByteFileBodyC::Tell() const
  { return static_cast<UIntT>(off); }
  
  //: Get size of stream. 
  
  UIntT DPIByteFileBodyC::Size() const
  { return (UIntT) (-1); }
  
  
  //: Seek to position in stream.
  // Currently will only seek to begining of stream.
  
  bool DPIByteFileBodyC::Seek64(StreamPosT newOff) {
    in.is().clear(); // Clear any end of stream errors.
    in.Seek(static_cast<streamoff>(dataStart +  newOff));
    off = newOff;
    return true;
  }
  
  
  //: Get offset in stream.
  
  StreamPosT DPIByteFileBodyC::Tell64() const 
  { return off; }
  
  //: Get size of stream. 
  
  StreamPosT DPIByteFileBodyC::Size64() const 
  { return streamPosUnknown; }
  
}
