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

#include "Ravl/Buffer2d.hh"
#include "Ravl/IndexRange3d.hh"

//: Ravl global namespace.

namespace RavlN {
  
  //! userlevel=Develop
  //: Buffer 3D
  // This holds a handle to data used in various 3d arrays.
  // There is a slightly confusing coordinate mapping to
  // 2d arrays, this is to allow the 2d buffers to work correctly
  // with 2d slices through them. In other words it makes the
  // 3d buffer look like a stack of 2d ones.
  
  template<class DataT>
  class Buffer3dBodyC 
    : public Buffer2dBodyC<DataT>
  {
  public:
    Buffer3dBodyC()
    {}
    //: Default constructor.

    Buffer3dBodyC(const IndexRange3dC &range)
      : Buffer2dBodyC<DataT>(range.Js(),range.Ks(),
                             range.Volume(),              // Total elements
                             range.Ks() * sizeof(DataT)
                             ), // Stride1.
        m_size0(range.Is()),
        m_stride1(range.Js() * range.Ks() * sizeof(DataT))
    {}
    //: Sized constructor.

    Buffer3dBodyC(SizeT size1,SizeT size2,SizeT size3)
      : Buffer2dBodyC<DataT>(size2,size3,
                             size1*size2*size3,              // Total elements
                             size3 * sizeof(DataT)
                             ), // Stride1.
        m_size0(size1),
        m_stride1(size2 * size3 * sizeof(DataT))
    {}
    //: Sized constructor.
    
    Buffer3dBodyC(DataT *data,SizeT size1,SizeT size2,SizeT size3,bool makeCopy = false,bool deleteable = true)
      : Buffer2dBodyC<DataT>(data,size2,size3,
                             size1 * size2 * size3,  // Total elements
                             size3 * sizeof(DataT), // 2d stride
                             makeCopy,deleteable),
	m_size0(size1),
        m_stride1(size2 * size3 * sizeof(DataT))
    {}
    //: Buffer constructor.    
    
    Buffer3dBodyC(DataT *data,SizeT size1,SizeT size2,SizeT size3,IntT byteStride1,IntT byteStride2,bool makeCopy = false,bool deleteable = true)
      : Buffer2dBodyC<DataT>(data,size2,size3,
                             size1 * size2 * size3,  // Total elements
                             byteStride2,
                             makeCopy,deleteable),
	m_size0(size1),
        m_stride1(byteStride1)
    {}
    //: Buffer constructor.
    
    SizeT Size1() const
    { return m_size0; }
    //: Get size of dimention 1

    SizeT Size2() const
    { return this->m_size1; }
    //: Get size of dimention 2
    
    SizeT Size3() const
    { return this->m_size2; }
    //: Get size of dimention 3
    
    IntT ByteStride1() const
    { return m_stride1; }
    //: Stride in bytes of 2rd index blocks.

    IntT ByteStride2() const
    { return this->m_stride; }
    //: Stride in bytes of 3rd index blocks.

  protected:
    SizeT m_size0;
    IntT m_stride1; // Stride of the
  };
  
  //! userlevel=Develop
  //: Buffer 3D 
  // This holds a handle to data used in various 3d arrays.
  // There is a slightly confusing coordinate mapping to
  // 2d arrays, this is to allow the 2d buffers to work correctly
  // with 2d slices through them. In other words it makes the
  // 3d buffer look like a stack of 2d ones.
  
  template<class DataT>
  class Buffer3dC 
    : public Buffer2dC<DataT>
  {
  public:
    Buffer3dC()
    {}
    //: Default constructor.
    // creates an invalid handle.
    
    Buffer3dC(SizeT size1,SizeT size2,SizeT size3)
      : Buffer2dC<DataT>(new Buffer3dBodyC<DataT>(size1,size2,size3))
    {}
    //: Size constructor.
    
    Buffer3dC(DataT *data,
              SizeT size1,SizeT size2,SizeT size3,
              IntT byteStride1,IntT byteStride2,
              bool makeCopy = false,bool deleteable = true)
      : Buffer2dC<DataT>(new Buffer3dBodyC<DataT>(data,
                                                 size1,size2,size3,
                                                 byteStride1,byteStride2,
                                                 makeCopy,deleteable))
    {}
    //: Buffer constructor.

    Buffer3dC(const IndexRange3dC &frame)
      : Buffer2dC<DataT>(new Buffer3dBodyC<DataT>(frame))
    {}
    //: Construct a buffer big enough to hold 'frame'.

  protected:
    Buffer3dC(const Buffer3dBodyC<DataT> *body)
      : Buffer2dC<DataT>(body)
    {}
    //: Size constructor.

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
