// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! lib=RavlIO
//! file="Ravl/Core/IO/ByteFileIO.cc"

#include "Ravl/DP/ByteFileIO.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //:------------------------------------------------------------------
  // DPOByteFileC



  DPOByteFileBodyC::~DPOByteFileBodyC()
  {
    ONDEBUG(cerr << "DPOByteFileBodyC::~DPOByteFileBodyC" << endl);
    out.Close();
  }

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



  void DPOByteFileBodyC::PutEOS()
  {
    out.Close();
  }



  bool DPOByteFileBodyC::Seek(UIntT offset)
  {
    return Seek64(offset);
  }



  bool DPOByteFileBodyC::DSeek(IntT offset)
  {
    return DSeek64(offset);
  }



  UIntT DPOByteFileBodyC::Tell() const
  {
    const StreamPosT tell = Tell64();
    if (tell < 0 || tell > static_cast<UIntT>(-1))
      return static_cast<UIntT>(-1);
    return static_cast<UIntT>(tell);
  }



  UIntT DPOByteFileBodyC::Size() const
  {
    return static_cast<UIntT>(-1);
  }



  UIntT DPOByteFileBodyC::Start() const
  {
    return 0;
  }



  bool DPOByteFileBodyC::Seek64(StreamPosT offset)
  {
    if (!out.IsOpen())
      return false;

    out.os().clear();
    out.seekp(offset);
    return !out.fail();
  }



  bool DPOByteFileBodyC::DSeek64(StreamPosT offset)
  {
    if (!out.IsOpen())
      return false;

    out.os().clear();
    out.seekp(offset, ios_base::cur);
    return !out.fail();
  }



  StreamPosT DPOByteFileBodyC::Tell64() const
  {
    if (!out.IsOpen())
      return streamPosUnknown;

    //TODO(WM) Clear flags here? Unfortunately clear is not a const function.
    StreamPosT tell = out.tellp();
    return (out.fail() ? streamPosUnknown : tell);
  }



  StreamPosT DPOByteFileBodyC::Size64() const
  {
    return streamPosUnknown;
  }



  StreamPosT DPOByteFileBodyC::Start64() const
  {
    return 0;
  }

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
    IntT dataRead = in.gcount();
    off += dataRead;
    return dataRead;
  }
    
  //: Save to ostream.
  
  bool DPIByteFileBodyC::Save(ostream &out) const { 
    out << in.Name(); 
    return true; 
  }
    
  //: Seek to position in stream.
  // Currently will only seek to begining of stream.
  
  bool DPIByteFileBodyC::Seek(UIntT newOff) {
    ONDEBUG(cerr << "DPIByteFileBodyC::Seek newOff=" << newOff << endl);
    in.is().clear(); // Clear any end of stream errors.
    in.Seek(static_cast<UIntT>(static_cast<streampos>(dataStart) + static_cast<streampos>(newOff)));
    off = newOff;
    return true;
  }
  
  //: Get offset in stream.
  
  UIntT DPIByteFileBodyC::Tell() const
  {
    ONDEBUG(cerr << "DPIByteFileBodyC::Tell off=" << off << endl);
    return static_cast<UIntT>(off);
  }
  
  //: Get size of stream. 
  
  UIntT DPIByteFileBodyC::Size() const
  {
    ONDEBUG(cerr << "DPIByteFileBodyC::Size..." << endl);
    return static_cast<UIntT>(Size64());
  }
  
  //: Seek to position in stream.
  // Currently will only seek to begining of stream.
  
  bool DPIByteFileBodyC::Seek64(StreamPosT newOff) {
    ONDEBUG(cerr << "DPIByteFileBodyC::Seek64 newOff=" << newOff << endl);
    in.is().clear(); // Clear any end of stream errors.
    in.Seek(static_cast<streamoff>(dataStart +  newOff));
    off = newOff;
    return true;
  }
  
  //: Get offset in stream.
  
  StreamPosT DPIByteFileBodyC::Tell64() const 
  {
    ONDEBUG(cerr << "DPIByteFileBodyC::Tell64 off=" << off << endl);
    return off;
  }
  
  //: Get size of stream. 
  
  StreamPosT DPIByteFileBodyC::Size64() const 
  {
    ONDEBUG(cerr << "DPIByteFileBodyC::Size64 size=" << size << endl);
    return size;
  }

  void DPIByteFileBodyC::Init()
  {
    if (in.IsOpen())
    {
      dataStart = in.tellg();
      in.seekg(0, ios::end);
      size = in.tellg();
      size -= dataStart;
      in.seekg(dataStart, ios::beg);
    }
  }

}
