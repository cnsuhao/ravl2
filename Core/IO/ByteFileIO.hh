// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DPBYTEFILEIO_HEADER
#define RAVL_DPBYTEFILEIO_HEADER 1
//////////////////////////////////////////////////////////
//! docentry="Ravl.Core.Data Processing.IO" 
//! example=exDataProc.cc
//! file="Ravl/Core/IO/ByteFileIO.hh"
//! lib=RavlIO
//! author="Charles Galambos"
//! date="04/07/1998"
//! rcsid="$Id$"
//! userlevel=Default

#include "Ravl/DP/SPort.hh"
#include "Ravl/String.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/Stream.hh"

namespace RavlN {
  ////////////////////////////////////////////
  //! userlevel=Develop
  //: Save fixed length objects to a file.
  // Object must have a stream output function.
  
  class DPOByteFileBodyC 
    : public DPOPortBodyC<ByteT>
  {
  public:
    DPOByteFileBodyC() {}
    //: Default constructor.
    
    DPOByteFileBodyC(const StringC &nfname)
      : out(nfname)
    {
#if RAVL_CHECK
      if(!out.good()) 
	cerr << "DPOByteFileBodyC<ByteT>::DPOByteFileBodyC<ByteT>(StringC,bool), Failed to open file '" << nfname << "'.\n";
#endif
    }
    //: Construct from a filename.
    
    inline DPOByteFileBodyC(OStreamC &strmout)
      : out(strmout)
    {
#if RAVL_CHECK
      if(!out.good()) 
	cerr << "DPOByteFileBodyC<ByteT>::DPOByteFileBodyC<ByteT>(OStreamC,bool), Passed bad output stream. \n";
#endif
    }
    //: Stream constructor.
    
    virtual bool Put(const ByteT &dat);
    //: Put data.
    
    virtual IntT PutArray(const SArray1dC<ByteT> &data);
    //: Put an array of data to stream.
    // returns the number of elements processed.
    
    virtual bool IsPutReady() const;
    //: Is port ready for data ?
    
    virtual bool Save(ostream &sout) const;
    //: Save to ostream.
    
  private:
    OStreamC out;
  };
  
  /////////////////////////////////////
  //! userlevel=Develop
  //: Load fixed length objects from a file.
  // Object must have a stream input function
  // and a default constructor.
  
  class DPIByteFileBodyC 
    : public DPISPortBodyC<ByteT>
  {
  public:
    DPIByteFileBodyC() 
      : dataStart(0),
	off(0)
    {}
    //: Default constructor.
    
    DPIByteFileBodyC(const StringC &nfname)
      : in(nfname),
	dataStart(0),
	off(0)
    {
#if RAVL_CHECK
      if(!in.good()) 
	cerr << "DPOByteFileBodyC<ByteT>::DPOByteFileBodyC<ByteT>(StringC,bool), WARNING: Failed to open file '" << nfname << "'.\n";
#endif
      dataStart = in.Tell();
    }
    //: Construct from a filename.
    
    inline DPIByteFileBodyC(IStreamC &strmin)
      : in(strmin),
	dataStart(0),
	off(0)
    {
#if RAVL_CHECK
      if(!in.good()) 
	cerr << "DPIByteFileBodyC<ByteT>::DPIByteFileBodyC<ByteT>(OStreamC,bool), WARNING: Passed bad input stream. \n";
#endif
      dataStart = in.Tell();
    }
    //: Stream constructor.
    
    virtual bool IsGetEOS() const;
    //: Is valid data ?
    
    virtual ByteT Get();
    //: Get next piece of data.
    
    virtual bool Get(ByteT &buff);
    //: Get next piece of data.
    
    virtual IntT GetArray(SArray1dC<ByteT> &data);
    //: Get multiple pieces of input data.
    // returns the number of elements processed.
    
    virtual bool Save(ostream &out) const;
    //: Save to ostream.
    
    virtual bool Seek(UIntT newOff);
    //: Seek to position in stream.
    // Currently will only seek to begining of stream.
    
    virtual UIntT Tell() const;
    //: Get offset in stream.
    
    virtual UIntT Size() const;
    //: Get size of stream. 
  
  private:
    IStreamC in;
    streampos dataStart;
    UIntT off;
  };
  
  ///////////////////////////////
  //! userlevel=Normal
  //: File output stream for fixed length objects.
  // Object must have a stream output function.
  
  class DPOByteFileC 
    : public DPOPortC<ByteT>
  {
  public:
    inline DPOByteFileC() 
      : DPEntityC(true)
    {}
    //: Default constructor.
    
    inline DPOByteFileC(OStreamC &strm)
      : DPEntityC(*new DPOByteFileBodyC(strm))
    {}
    //: Stream constructor.
    
    inline DPOByteFileC(const StringC &fname) 
      : DPEntityC(*new DPOByteFileBodyC(fname))
    {}
    
    //: ByteFilename constructor.  
  };
  
  //////////////////////////////////
  //! userlevel=Normal
  //: Byte file input stream.
  // Object must have a stream input function
  // and a default constructor.
  
  class DPIByteFileC 
    : public DPISPortC<ByteT> 
  {
  public:
    inline DPIByteFileC() 
      : DPEntityC(true)
    {}
    //: Default constructor.
    
    inline DPIByteFileC(IStreamC &strm)
      : DPEntityC(*new DPIByteFileBodyC(strm))
    {}
    //: Stream constructor.
    
    inline DPIByteFileC(const StringC &afname)
      : DPEntityC(*new DPIByteFileBodyC(afname))
    {}
    //: filename constructor.  
  }; 
}
#endif
