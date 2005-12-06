// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DPBINIO_HEADER
#define RAVL_DPBINIO_HEADER 1
//////////////////////////////////////////////////////////
//! docentry="Ravl.API.Core.Data Processing.IO" 
//! example=exDataProc.cc
//! lib=RavlIO
//! author="Charles Galambos"
//! date="04/07/1998"
//! rcsid="$Id$"
//! file="Ravl/Core/IO/BinFileIO.hh"
//! userlevel=Default

#include "Ravl/DP/SPort.hh"
#include "Ravl/String.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/BinStream.hh"

namespace RavlN {
  static const UInt16T RAVLBinaryID = 0x4143; // AB Ravl Binary file id.
  static const UInt16T RAVLInvBinaryID = 0x4341; // Swapped endian id.
  
  /////////////////////////////////////////////
  //! userlevel=Develop
  //: Save objects in binary to a file.
  // Object must have a binary stream output function.
  
  template<class DataT>
  class DPOBinFileBodyC 
    : public DPOPortBodyC<DataT>
  {
  public:
    DPOBinFileBodyC() 
    {}
    //: Default constructor.
    
    DPOBinFileBodyC(const StringC &nfname,bool useHeader=false)
      : out(nfname),
        version(0)
    {
#ifdef RAVL_CHECK
      if(!out.Stream().good()) 
	cerr << "DPOBinFileBodyC<DataT>::DPOBinFileBodyC<DataT>(StringC,bool), Failed to open file.\n";
#endif
      if(useHeader) 
	out << RavlN::RAVLBinaryID << TypeName(typeid(DataT)) << version;
    }
    //: Construct from a filename.
    
    inline DPOBinFileBodyC(BinOStreamC &strmout,bool useHeader=false)
      : out(strmout),
	version(0)
    {
#ifdef RAVL_CHECK
      if(!out.Stream().good()) 
	cerr << "DPOBinFileBodyC<DataT>::DPOBinFileBodyC<DataT>(OStreamC,bool), Passed bad output stream. \n";
#endif
      if(useHeader) {
	out << RavlN::RAVLBinaryID << TypeName(typeid(DataT)) << version;
#ifdef RAVL_CHECK
	if(!out.Stream().good()) 
	  cerr << "DPOBinFileBodyC<DataT>::DPOBinFileBodyC<DataT>(BinOStreamC,bool), Bad stream after writting header! \n";
#endif
      }
    }
    //: Stream constructor.
    
    virtual bool Put(const DataT &dat) { 
#ifdef RAVL_CHECK
      if(!out.Stream().good()) {
	cerr << "DPOBinFileBodyC<DataT>::Put(), Failed because of bad output stream (before write!). \n";
	return false;
      }
#endif
      out << dat;
#ifdef RAVL_CHECK
      if(!out.Stream().good()) 
	cerr << "DPOBinFileBodyC<DataT>::Put(), Failed because of bad output stream. \n";
#endif
      return out.Stream().good(); 
    }
    //: Put data.
    
    virtual IntT PutArray(const SArray1dC<DataT> &data) {
      if(!out.Stream().good()) 
	return data.Size();
      for(SArray1dIterC<DataT> it(data);it;it++) {
	out << *it;
	if(!out.Stream().good()) {
#ifdef RAVL_CHECK
	  cerr << "DPOBinFileBodyC<DataT>::PutArray(), Endded early because of bad output stream. \n";	
#endif
	  return it.Index().V();
	}
      }
      return data.Size();
    }
    //: Put an array of data to stream.
    // returns the number of elements processed.
    
    virtual bool IsPutReady() const 
    { return out.Stream().good(); }
    //: Is port ready for data ?
    
    virtual bool Save(ostream &sout) const 
    { sout << out.Name(); return true; }
    //: Save to ostream.
    
  private:
    BinOStreamC out;
    UIntT version;
  };

  /////////////////////////////////////
  //! userlevel=Develop
  //: Load objects in binary from a file.
  // Object must have a binary stream input function
  // and a default constructor.
  
  template<class DataT>
  class DPIBinFileBodyC 
    : public DPISPortBodyC<DataT>
  {
  public:
    DPIBinFileBodyC() 
      : version(-1),
	off(0),
	dataStart(0)
    {}
    //: Default constructor.
    
    DPIBinFileBodyC(const StringC &nfname,bool useHeader = false)
      : in(nfname),
	version(0),
	off(0)
    {
      if(useHeader) {
	StringC classname;
	UInt16T id;
	in >> id;
	if(id == RAVLInvBinaryID) {
#if RAVL_ENDIAN_COMPATILIBITY
	  in.UseNativeEndian(!in.NativeEndian());
#else
	  throw ExceptionOperationFailedC("Stream is incompible. endian mismatch. ");
#endif
	} else {
	  if(id != RavlN::RAVLBinaryID){
	    cerr << "DPIBinFileC ERROR: Bad file id. \n";
	    throw ExceptionOperationFailedC("Bad file id. ");
	  }
	}
	in >> classname >> version;  // Read class name & version
	if(classname != TypeName(typeid(DataT))) {
	  cerr << "DPIBinFileC ERROR: Bad file type: " << classname << " Expected:" << TypeName(typeid(DataT)) << " \n";
	  throw ExceptionOperationFailedC("File type mismatch. ");
	}
      }
      dataStart = in.Tell(); // Remember where data starts.
    }
    //: Construct from a filename.
    
    inline DPIBinFileBodyC(BinIStreamC &strmin,bool useHeader = false)
      : in(strmin),
        version(0),
	off(0)
    {
      if(useHeader) {
	StringC classname; 
	UInt16T id;
	in >> id;
	if(id == RAVLInvBinaryID) {
#if RAVL_ENDIAN_COMPATILIBITY
	  in.UseNativeEndian(!in.NativeEndian());
#else
	  throw ExceptionOperationFailedC("Stream is incompible. endian mismatch. ");
#endif
	} else {
	  if(id != RavlN::RAVLBinaryID) {
	    cerr << "DPIBinFileC ERROR: Bad file id. \n";
	    throw ExceptionOperationFailedC("Bad file id. ");
	  }
	}
	in >> classname >> version;  // Read class name & version
	if(classname != TypeName(typeid(DataT))) {
	  cerr << "DPIBinFileC ERROR: Bad file type. " << classname << " Expected:" << TypeName(typeid(DataT)) << " \n";
	  throw ExceptionOperationFailedC("File type mismatch. ");
	}
      }
      dataStart = in.Tell(); // Remember where data starts.
    }
    //: Stream constructor.
    
    virtual bool IsGetEOS() const 
    { return (!in.Stream().good() || in.Stream().eof()); }
    //: Is valid data ?
  
    virtual DataT Get() { 
      DataT ret;
      in >> ret;
      off++;
      return ret; 
    }
    //: Get next piece of data.
    
    virtual bool Get(DataT &buff) { 
      if(in.IsEndOfStream())
	return false;
      in >> buff;
      off++;
      return true; 
    }
    //: Get next piece of data.
    
    virtual IntT GetArray(SArray1dC<DataT> &data) {
      for(SArray1dIterC<DataT> it(data);it;it++) {
	in >> *it;
	off++;
	if(!in.Stream().good()) {
#ifdef RAVL_CHECK
	  cerr << "DPIBinFileBodyC<DataT>::GetArray(), Ended early because of bad input stream. \n";	
#endif
	  return it.Index().V();
	}
      }
      return data.Size();
    }
    //: Get multiple pieces of input data.
    
    virtual bool Save(ostream &out) const 
    { out << in.Name(); return true; }
    //: Save to ostream.
    
    virtual bool Seek(UIntT newOff) {
      if(newOff == 0) {
	in.Seek(dataStart);
	off = newOff;
	return true;
      }
      return false;
    }
    //: Seek to position in stream.
    // Currently only understands seek to start.
    
    virtual UIntT Tell() const
    { return off; }
    //: Get current offset in stream.
    
    virtual UIntT Size() const
    { return (UIntT) (-1); }
    //: Get size of stream. 
    
  private:
    BinIStreamC in;
    UIntT version;
    UIntT off;
    streampos dataStart;
  };
  
  ///////////////////////////////
  //! userlevel=Normal
  //: Binary file output stream.
  // Object must have a binary stream output function.
  
  template<class DataT>
  class DPOBinFileC 
    : public DPOPortC<DataT> 
  {
  public:
    inline DPOBinFileC() {}
    //: Default constructor.
    
    inline DPOBinFileC(BinOStreamC &strm,bool useHeader=false)
      : DPEntityC(*new DPOBinFileBodyC<DataT>(strm,useHeader))
    {}
    //: Stream constructor.
    
    inline DPOBinFileC(const StringC &fname,bool useHeader=false) 
      : DPEntityC(*new DPOBinFileBodyC<DataT>(fname,useHeader))
    {}
    
    //: Filename constructor.  
  };
  
  //////////////////////////////////
  //! userlevel=Normal
  //: Binary file input stream.
  // Object must have a binary stream input function
  // and a default constructor.
  
  template<class DataT>
  class DPIBinFileC 
    : public DPISPortC<DataT> 
  {
  public:
    inline DPIBinFileC() {}
    //: Default constructor.
    
    inline DPIBinFileC(BinIStreamC &strm,bool useHeader=false)
      : DPEntityC(*new DPIBinFileBodyC<DataT>(strm,useHeader))
    {}
    //: Stream constructor.
    
    inline DPIBinFileC(const StringC &afname,bool useHeader=false)
      : DPEntityC(*new DPIBinFileBodyC<DataT>(afname,useHeader))
    {}
    //: Filename constructor.  
  };
}


#endif
