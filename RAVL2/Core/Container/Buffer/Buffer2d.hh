// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BUFFER2D_HEADER
#define RAVL_BUFFER2D_HEADER 1
///////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Buffer/Buffer2d.hh"
//! lib=RavlCore
//! docentry="Ravl.API.Core.Arrays.Buffer"
//! author="Charles Galambos"

#include "Ravl/Buffer.hh"
#include "Ravl/SingleBuffer.hh"

//: Ravl global namespace.

namespace RavlN {
  
  //! userlevel=Develop
  //: Buffer2D
  // This holds a handle to data used in various 2d arrays.
  
  template<class DataT>
  class Buffer2dBodyC :
    public BufferBodyC<DataT>
  {
  public:
    Buffer2dBodyC()
    {}
    //: Default constructor.

    Buffer2dBodyC(SizeT size1,SizeT size2)
     : BufferBodyC<DataT >(size1 * size2),
       m_size1(size1),
       m_size2(size2),
       m_stride(size2 * sizeof(DataT))
    {}
    //: Sized constructor.
    
    Buffer2dBodyC(SizeT size1,SizeT size2,DataT *data,bool makeCopy = false,bool deletable = true)
     : BufferBodyC<DataT >(size1 * size2,data,makeCopy,deletable),
       m_size1(size1),
       m_size2(size2),
       m_stride(size2 * sizeof(DataT))
    {}
    //: Sized constructor.

    Buffer2dBodyC(SizeT size1,SizeT size2,IntT byteStride,DataT *data,bool makeCopy = false,bool deletable = true)
     : BufferBodyC<DataT >(size1 * size2,data,makeCopy,deletable),
       m_size1(size1),
       m_size2(size2),
       m_stride(byteStride)
    {}
    //: Sized constructor.
    
    SizeT Size1() const
    { return m_size1; }
    //: Get size 1
    
    SizeT Size2() const
    { return m_size2; }
    //: Get size 2 (estimate.)

    IntT ByteStride() const
    { return m_stride; }
    //: Access the size of each row in the buffer in bytes.
    // Note this may be negative.
  protected:
    SizeT m_size1; // Number of rows.
    SizeT m_size2; // Number of valid elements in a row.
    IntT m_stride; // Distance in bytes between each row.
  };
  
  //! userlevel=Develop
  //: Buffer2D 
  // This holds a handle to data used in various 2d arrays.

  template<class DataT>
  class Buffer2dC 
    : public BufferC<DataT>
  {
  public:
    Buffer2dC()
    {}
    //: Default constructor.
    // creates an invalid handle.
    
    Buffer2dC(SizeT size1,SizeT size2)
     : BufferC<DataT>(new Buffer2dBodyC<DataT>(size1,size2))
    {}
    //: Sized constructor.
    
    Buffer2dC(SizeT size1,SizeT size2,DataT *data,bool copy = false,bool deletable = true) 
      : BufferC<DataT>(new Buffer2dBodyC<DataT>(size1,size2,data,copy,deletable))
    {}
    //: Construct from an existing buffer.
    
    Buffer2dC(SizeT size1,SizeT size2,IntT byteStride,DataT *data,bool copy = false,bool deletable = true) 
      : BufferC<DataT>(new Buffer2dBodyC<DataT>(size1,size2,byteStride,data,copy,deletable))
    {}
    //: Construct from an existing buffer.

  protected:    
    Buffer2dBodyC<DataT> &Body()
    { return static_cast<Buffer2dBodyC<DataT> &>(BufferC<DataT>::Body()); }
    //: Access body.
    
    const Buffer2dBodyC<DataT> &Body() const
    { return static_cast<const Buffer2dBodyC<DataT> &>(BufferC<DataT>::Body()); }
    //: Constant access to body.
    
  public:
    
    SizeT Size1() const
    { return Body().Size1(); }
    //: Get size of buffer along dimention 1

    SizeT Size2() const
    { return Body().Size2(); }
    //: Get size of buffer along dimention 2 (estimate.)

    IntT ByteStride() const
    { return Body().ByteStride(); }
    //: Access the size of each row in the buffer in bytes.
    // Note this may be negative.
    
  };
  
}
  
#endif
