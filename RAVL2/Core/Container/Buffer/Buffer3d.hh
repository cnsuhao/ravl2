// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BUFFER3D_HEADER
#define RAVL_BUFFER3D_HEADER 1
///////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Buffer/Buffer3d.hh"
//! lib=RavlCore
//! docentry="Ravl.API.Core.Arrays.Buffer"
//! author="Charles Galambos"

#include "Ravl/Buffer.hh"
#include "Ravl/RangeBufferAccess2d.hh"

//: Ravl global namespace.

namespace RavlN {
  
  //! userlevel=Develop
  //: Buffer 3D
  // This holds a handle to data used in various 3d arrays.
  
  template<class DataT>
  class Buffer3dBodyC 
    : public BufferBodyC<DataT>
  {
  public:
    Buffer3dBodyC()
    {}
    //: Default constructor.
    
    Buffer3dBodyC(SizeT size1,SizeT size2,SizeT size3)
      : BufferBodyC<DataT>(size1*size2*size3),
	m_size1(size1),
	m_size2(size2),
	m_size3(size3),
        m_stride1(size2 * size3 * sizeof(DataT)),
        m_stride2(size3 * sizeof(DataT))
    {}
    //: Sized constructor.
    
    Buffer3dBodyC(DataT *data,SizeT size1,SizeT size2,SizeT size3,bool makeCopy = false,bool deleteable = true)
      : BufferBodyC<DataT>(size1 * size2 * size3,data,makeCopy,deleteable),
	m_size1(size1),
	m_size2(size2),
	m_size3(size3),
        m_stride1(size2 * size3 * sizeof(DataT)),
        m_stride2(size3 * sizeof(DataT))
    {}
    //: Buffer constructor.    
    
    Buffer3dBodyC(DataT *data,SizeT size1,SizeT size2,SizeT size3,IntT byteStride1,IntT byteStride2,bool makeCopy = false,bool deleteable = true)
      : BufferBodyC<DataT>(size1 * size2 * size3,data,makeCopy,deleteable),
	m_size1(size1),
	m_size2(size2),
	m_size3(size3),
        m_stride1(byteStride1),
        m_stride2(byteStride2)
    {}
    //: Buffer constructor.
    
    SizeT Size1() const
    { return m_size1; }
    //: Get size of dimention 1
    
    SizeT Size2() const
    { return m_size2; }
    //: Get size of dimention 2
    
    SizeT Size3() const
    { return m_size3; }
    //: Get size of dimention 3
    
    IntT ByteStride1() const
    { return m_stride1; }
    //: Stride in bytes of 2rd index blocks.

    IntT ByteStride2() const
    { return m_stride2; }
    //: Stride in bytes of 3rd index blocks.

  protected:
    SizeT m_size1;
    SizeT m_size2;
    SizeT m_size3;
    IntT m_stride1; // Stride of the
    IntT m_stride2; // Stride of the
  };

  //! userlevel=Develop
  //: Buffer 3D 
  // This holds a handle to data used in various 3d arrays.
  
  template<class DataT>
  class Buffer3dC 
    : public BufferC<DataT>
  {
  public:
    Buffer3dC()
    {}
    //: Default constructor.
    // creates an invalid handle.
    
    Buffer3dC(SizeT size1,SizeT size2,SizeT size3)
      : BufferC<DataT>(*new Buffer3dBodyC<DataT>(size1,size2,size3))
    {}
    //: Size constructor.
    
    Buffer3dC(DataT *data,SizeT size1,SizeT size2,SizeT size3,IntT byteStride1,IntT byteStride2,bool makeCopy = false,bool deleteable = true)
      : BufferC<DataT>(*new Buffer3dBodyC<DataT>(data,size1,size2,size3,byteStride1,byteStride2,makeCopy,deleteable))
    {}
    //: Buffer constructor.

  protected:
    
    Buffer3dBodyC<DataT> &Body()
    { return static_cast<Buffer3dBodyC<DataT> &>(BufferC<DataT>::Body()); }
    //: Access body.
    
    const Buffer3dBodyC<DataT> &Body() const
    { return static_cast<const Buffer3dBodyC<DataT> &>(BufferC<DataT>::Body()); }
    //: Constant access to body.
    
  public:
        
    SizeT Size1() const
    { return Body().Size1(); }
    //: Get size of dimention 1
    
    SizeT Size2() const
    { return Body().Size2(); }
    //: Get size of dimention 2
    
    SizeT Size3() const
    { return Body().Size3(); }
    //: Get size of dimention 3
    
    IntT ByteStride1() const
    { return Body().ByteStride1(); }
    //: Stride in bytes of 2rd index blocks.

    IntT ByteStride2() const
    { return Body().ByteStride2(); }
    //: Stride in bytes of 3rd index blocks.
    
  };
  
}
  
#endif
