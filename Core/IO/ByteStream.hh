// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BYTESTREAM_HEADER
#define RAVL_BYTESTREAM_HEADER 1
//! author="Charles Galambos"
//! docentry="Ravl.Core.Data Processing.IO" 
//! rcsid="$Id$"
//! lib=RavlIO

#include "Ravl/DP/Port.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Abstract class representing an output byte stream
  
  class DPOByteStreamBodyC
    : public DPOPortBodyC<ByteT>
  {
  public:
    DPOByteStreamBodyC()
    {}
    //: Default constructor.
    
    virtual IntT Write(const char *buffer,IntT len);
    //: Write data to stream
    //!param: buffer - Buffer to write data from.
    //!param: len - length of buffer.
    //!return: true if write succeeded.
    
  protected:
    bool fullWrite; // Always write all bytes in buffer before returning.
  };
  
  //! userlevel=Normal
  //: Abstract class representing an output byte stream
  
  class DPOByteStreamC
    : public DPOPortC<ByteT>
  {
  public:
    DPOByteStreamC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    DPOByteStreamC(DPOByteStreamBodyC &bod)
      : DPEntityC(bod)
    {}
    //: Body constructor.
    
    DPOByteStreamBodyC &Body()
    { return dynamic_cast<DPOByteStreamBodyC &>(DPEntityC::Body()); }
    //: Access body.

    const DPOByteStreamBodyC &Body() const
    { return dynamic_cast<const DPOByteStreamBodyC &>(DPEntityC::Body()); }
    //: Access body.
    
  public:
    
    IntT Write(const char *buffer,IntT len)
    { return Body().Write(buffer,len); }
    //: Write data to stream
    //!param: buffer - Buffer to write data from.
    //!param: len - length of buffer.
    //!return: Number of bytes written, or -1 on error.
    
  };

  //! userlevel=Develop
  //: Abstract class representing an input byte stream
  
  class DPIByteStreamBodyC
    : public DPIPortBodyC<ByteT>
  {
  public:
    DPIByteStreamBodyC()
    {}
    //: Default constructor.
    
    virtual IntT Read(char *buffer,IntT len);
    //: Read data from stream info buffer.
    //!param: buffer - Buffer to read data into.
    //!param: len - length of buffer.
    //!return: Number of bytes read or -1 on error
    
  protected:
    bool fullRead; // Always read all bytes in buffer before returning.
  };
  
  //! userlevel=Normal
  //: Abstract class representing an input byte stream
  
  class DPIByteStreamC
    : public DPIPortC<ByteT>
  {
  public:
    DPIByteStreamC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    DPIByteStreamC(DPIByteStreamBodyC &bod)
      : DPEntityC(bod)
    {}
    //: Body constructor.
    
    DPIByteStreamBodyC &Body()
    { return dynamic_cast<DPIByteStreamBodyC &>(DPEntityC::Body()); }
    //: Access body.
    
    const DPIByteStreamBodyC &Body() const
    { return dynamic_cast<const DPIByteStreamBodyC &>(DPEntityC::Body()); }
    //: Access body.
    
  public:
    
    IntT Read(char *buffer,IntT len)
    { return Body().Read(buffer,len); }
    //: Read data from stream info buffer.
    //!param: buffer - Buffer to read data into.
    //!param: len - length of buffer.
    //!return: Number of bytes read or -1 on error
    
  };
  
  
}


#endif

