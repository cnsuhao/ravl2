#ifndef RAVL_NETBYTESTREAM_HEADER
#define RAVL_NETBYTESTREAM_HEADER 1
//! author="Charles Galambos"

#include "Ravl/OS/Socket.hh"
#include "Ravl/DP/ByteStream.hh"

namespace RavlN {
  
  
  //! userlevel=Normal
  //: Network byte stream input
  
  class NetOByteStreamBodyC 
    : public DPOByteStreamBodyC
  {
  public:
    NetOByteStreamBodyC();
    //: Default constructor.
    
    NetOByteStreamBodyC(const SocketC &socket);
    //: Constructor.
    
    NetOByteStreamBodyC(const StringC &address);
    //: Construct from address string
    
    virtual void PutEOS();
    //: Put End Of Stream marker.
    
    virtual bool IsPutReady() const;
    //: Is port ready for data ?
    
    virtual bool Put(const ByteT &);
    //: Put data.
    // This function MUST be provided by client class.
    
    virtual IntT PutArray(const SArray1dC<ByteT> &data);
    //: Put an array of data to stream.
    // returns number of elements processed.
    
    virtual IntT Write(const char *buffer,IntT len);
    //: Write data to stream
    //!param: buffer - Buffer to write data from.
    //!param: len - length of buffer.
    //!return: true if write succeeded.

    virtual IntT WriteAll(const char *buffer,IntT len);
    //: Write data to stream
    // This routine works as Write(), but will handle temporary errors and
    // do its best to ensure the complete buffer is written.
    //!param: buffer - Buffer to write data from.
    //!param: len - length of buffer.
    //!return: Number of bytes written, or -1 on error.
    
    virtual IntT WriteV(const char **buffer,IntT *len,int n);
    //: Write data to stream
    //!param: buffer - Array of buffers to write data from.
    //!param: len - Array of lengths of the buffers.
    //!param: n - Number of buffers involved.
    //!return: Number of bytes written, or -1 on error.
    
    virtual IntT WriteAllV(const char **buffer,IntT *len,int n);
    //: Write data to stream
    // This routine works as Write(), but will handle temporary errors and
    // do its best to ensure the complete buffer is written.
    //!param: buffer - Array of buffers to write data from.
    //!param: len - Array of lengths of the buffers.
    //!param: n - Number of buffers involved.
    //!return: Number of bytes written, or -1 on error.
    
    virtual bool GetAttr(const StringC &attrName,StringC &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    
    virtual bool GetAttr(const StringC &attrName,IntT &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    
    SocketC &Socket()
    { return socket; }
    //: Access socket.
    
  protected:
    void Init();
    //: Build attribute lists etc.
    
    SocketC socket;
  };
  
  //! userlevel=Normal
  //: Network byte stream input
  
  class NetOByteStreamC 
    : public DPOByteStreamC
  {
  public:
    NetOByteStreamC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    // Creates an invalid handle.

    NetOByteStreamC(const SocketC &socket)
      : DPEntityC(*new NetOByteStreamBodyC(socket))
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    NetOByteStreamC(const StringC &address)
      : DPEntityC(*new NetOByteStreamBodyC(address))
    {}
    //: Construct from address string
    
    SocketC &Socket()
    { return Body().Socket(); }
    //: Access socket.
    
  protected:
    NetOByteStreamC(NetOByteStreamBodyC &bod)
      : DPEntityC(bod)
    {}
    //: Body constructor.
    
    NetOByteStreamBodyC &Body()
    { return dynamic_cast<NetOByteStreamBodyC &>(DPEntityC::Body()); }
    //: Access body.
    
    const NetOByteStreamBodyC &Body() const
    { return dynamic_cast<const NetOByteStreamBodyC &>(DPEntityC::Body()); }
    //: Access body.
    
  };
  
  //------------------------------------------------------------------------------
  
  //! userlevel=Normal
  //: Network byte stream input
  
  class NetIByteStreamBodyC 
    : public DPIByteStreamBodyC
  {
  public:
    NetIByteStreamBodyC();
    //: Default constructor.
    
    NetIByteStreamBodyC(const SocketC &socket);
    //: Constructor.
    
    NetIByteStreamBodyC(const StringC &address);
    //: Constructor from address string
    
    virtual bool IsGetReady() const;
    //: Is some data ready ?
    // true = yes.
    // Defaults to !IsGetEOS().
    
    virtual bool IsGetEOS() const;
    //: Has the End Of Stream been reached ?
    // true = yes.
    
    virtual ByteT Get();
    //: Get next piece of data.
    // May block if not ready, or it could throw an 
    // DataNotReadyC exception.
    
    virtual bool Get(ByteT &buff);
    //: Try and get next piece of data.
    // This may not NOT block, if no data is ready
    // it will return false, and not set buff.
    
    virtual IntT GetArray(SArray1dC<ByteT> &data);
    //: Get an array of data from stream.
    // returns the number of elements succesfully processed.
    
    virtual IntT Read(char *buffer,IntT len);
    //: Read data from stream info buffer.
    //!param: buffer - Buffer to read data into.
    //!param: len - length of buffer.
    //!return: Number of bytes read or -1 on error
    
    virtual IntT ReadAll(char *buffer,IntT len);
    //: Read data from stream info buffer.
    // This routine works as Read(), but will handle temporary errors and do
    // its best to ensure a full buffer is read.
    //!param: buffer - Buffer to read data into.
    //!param: len - length of buffer.
    //!return: Number of bytes read or -1 on error

    virtual IntT ReadV(char **buffer,IntT *len,int n);
    //: Read data to stream
    //!param: buffer - Array of buffers to read data into.
    //!param: len - Array of lengths of the buffers.
    //!param: n - Number of buffers involved.
    //!return: Number of bytes read or -1 on error
    
    virtual IntT ReadAllV(char **buffer,IntT *len,int n);
    //: Read data to stream
    // This routine works as Read(), but will handle temporary errors and do
    // its best to ensure a full buffer is read.
    //!param: buffer - Array of buffers to read data into.
    //!param: len - Array of lengths of the buffers.
    //!param: n - Number of buffers involved.
    //!return: Number of bytes read or -1 on error
    
    virtual bool GetAttr(const StringC &attrName,StringC &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    
    virtual bool GetAttr(const StringC &attrName,IntT &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    
    SocketC &Socket()
    { return socket; }
    //: Access socket.
    
  protected:
    void Init();
    //: Build attribute lists etc.
    
    SocketC socket;
  };
  
  //! userlevel=Normal
  //: Network byte stream input
  
  class NetIByteStreamC 
    : public DPIByteStreamC
  {
  public:
    NetIByteStreamC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    NetIByteStreamC(const SocketC &socket)
      : DPEntityC(*new NetIByteStreamBodyC(socket))
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    NetIByteStreamC(const StringC &address)
      : DPEntityC(*new NetIByteStreamBodyC(address))
    {}
    //: Constructor from address string
    
    SocketC &Socket()
    { return Body().Socket(); }
    //: Access socket.
    
  protected:
    NetIByteStreamC(NetIByteStreamBodyC &bod)
      : DPEntityC(bod)
    {}
    //: Body constructor.
    
    NetIByteStreamBodyC &Body()
    { return dynamic_cast<NetIByteStreamBodyC &>(DPEntityC::Body()); }
    //: Access body.
    
    const NetIByteStreamBodyC &Body() const
    { return dynamic_cast<const NetIByteStreamBodyC &>(DPEntityC::Body()); }
    //: Access body.
    
  };
  
  
  
  
}


#endif
