// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SINGLEBUFFER2D_HEADER
#define RAVL_SINGLEBUFFER2D_HEADER 1
///////////////////////////////////////////////////////
//! docentry="Ravl.API.Core.Arrays.Buffer"
//! file="Ravl/Core/Container/Buffer/SingleBuffer.hh"
//! lib=RavlCore
//! userlevel=Advanced
//! author="Charles Galambos"
//! date="10/04/2002"

#include "Ravl/SingleBuffer.hh"
#include "Ravl/Buffer2d.hh"

namespace RavlN {

  //! userlevel=Develop
  //: Single allocation buffer body.
  // Allocate data along with body.
  
  template<typename DataT>
  class SingleBuffer2dBodyC
    : public Buffer2dBodyC<DataT>
  {
  public:
    static SizeT StartAlignmentOffset(SizeT align = 16) {
      const SizeT objSize = sizeof(SingleBuffer2dBodyC<DataT>);
      return ((objSize % align) == 0) ? 0 : (objSize - (objSize % align));
    }
    //: Get the offset needed to align start.
    // Internal use only.
    
    SingleBuffer2dBodyC(SizeT size1,SizeT size2)
      : Buffer2dBodyC<DataT>(static_cast<DataT *>(0),size1,size2,0,false)
    {
      this->m_stride = size2 * sizeof(DataT);
      // Make sure buffer is 8-byte aligned.
      this->m_buff = ShiftPointerInBytes(reinterpret_cast<DataT *>(this),
                                         StartAlignmentOffset() + sizeof(SingleBuffer2dBodyC<DataT>));
      // cerr << "Memory at " << (void*) this->buff << "\n";
#if RAVL_COMPILER_GCC43
      // This is a bug workaround for a problem with gcc-4.3.x compilers
      new(this->m_buff) DataT[size1 * size2];
#else
      ConstructRawArray(this->m_buff,size1 * size2);
#endif
      RavlAssert(!this->IsDeletable());
    }
    //: Default constructor.
    
    SingleBuffer2dBodyC(SizeT size1,SizeT size2,IntT byteStride,UIntT align)
      : Buffer2dBodyC<DataT>(static_cast<DataT *>(0),size1,size2,byteStride,false)
    {
      this->m_stride = byteStride;
      RavlAssert(this->m_stride >= static_cast<IntT>(size2 * sizeof(DataT)));
      // Align start of memory
      char *buf = reinterpret_cast<char *>(&(this[1]));
      SizeT alignm1 = align-1;
      this->m_buff = reinterpret_cast<DataT *>(buf + ((align - (((SizeT) buf) & alignm1)) & alignm1));
      //std::cerr << "Buffer=" << ((void *) buf) << " Aligned="<< ((void *) this->m_buff) << "\n";
      
      // Construct array
      DataT *ptr = this->m_buff;
      for(unsigned i = 0;i < size1;i++,ptr = ShiftPointerInBytes(ptr,this->m_stride)) {
#if RAVL_COMPILER_GCC43
        // This is a bug workaround for a problem with gcc-4.3.x compilers
        new(ptr) DataT[this->m_size2];
#else
        ConstructRawArray(ptr,this->m_size2);
#endif
      }
      RavlAssert(!this->IsDeletable());
    }
    //: Construct buffer with alignment
    // Note: Aligment must be a power of 2
    
    ~SingleBuffer2dBodyC()
    {
      if((this->m_size2 * sizeof(DataT)) == static_cast<SizeT>(this->m_stride)) {
        DestructRawArray(this->m_buff,this->m_size2 * this->m_size1);
      } else {
        DataT *ptr = this->m_buff;
        for(unsigned i = 0;i < this->m_size1;i++,ptr = ShiftPointerInBytes(ptr,this->m_stride)) {
          DestructRawArray(ptr,this->m_size2);
        }
      }
    }
    //: Destructor.

    virtual void Fill(const DataT &value) {
      DataT *ptr = this->m_buff;
      for(unsigned i = 0;i < this->m_size1;i++,ptr = ShiftPointerInBytes(ptr,this->m_stride)) {
        for(unsigned i = 0;i < this->m_size2;i++)
          ptr[i] = value;
      }
    }
    //: Fill buffer with value.


  }; 
  
  //! userlevel=Advanced
  //: Single allocation buffer handle.
  // Allocate data along with body.
  
  template<typename DataT>
  class SingleBuffer2dC
    : public Buffer2dC<DataT>
  {
  public:
    SingleBuffer2dC()
    {}
    //: Default constructor.
    // Creates an invalid handle.

    SingleBuffer2dC(SizeT size1,SizeT size2)
      : Buffer2dC<DataT>(AllocBody(size1,size2))
    {}
    //: Constructor.
    
    SingleBuffer2dC(SizeT size1,SizeT size2,UIntT align)
      : Buffer2dC<DataT>(AllocBody(size1,size2,align))
    {}
    //: Constructor.
    // Note: Aligment must be a power of 2
    
  protected:
    static SingleBuffer2dBodyC<DataT> *AllocBody(SizeT size1,SizeT size2) {
      const SizeT startAlign = SingleBuffer2dBodyC<DataT>::StartAlignmentOffset();

      // Make sure buffers are 8-byte aligned.
      SizeT allocSize = sizeof(SingleBuffer2dBodyC<DataT>) + startAlign + (size1 * size2 * sizeof(DataT));
      
      SingleBuffer2dBodyC<DataT> *ret = reinterpret_cast<SingleBuffer2dBodyC<DataT> *> (malloc(allocSize));
      try {
        new(ret) SingleBuffer2dBodyC<DataT>(size1,size2);
      } catch(...) {
        free(ret);
	throw ;
      }
      return ret;
    }

    //: Allocate a body object plus some space.
    
    static SingleBuffer2dBodyC<DataT> *AllocBody(SizeT size1,SizeT size2,UIntT align) {
      IntT stride = size2 * sizeof(DataT);
      IntT rem = stride % align;
      if(rem > 0)
        stride += align - rem;
      RavlAssert(align > 0);
      IntT allocSize = sizeof(SingleBuffer2dBodyC<DataT>) + (size1 * stride) + (align-1);
      SingleBuffer2dBodyC<DataT> *ret = reinterpret_cast<SingleBuffer2dBodyC<DataT> *> (malloc(allocSize));
      try {
        new(ret) SingleBuffer2dBodyC<DataT>(size1,size2,stride,align);
      } catch(...) {
        free(ret);
	throw ;
      }
      return ret;
    }
    //: Allocate a body object plus some space with alignment.
    
    SingleBuffer2dC(SingleBuffer2dBodyC<DataT> &body)
      : BufferC<DataT>(body)
    {}
    //: Body constructor.

    SingleBuffer2dC(SingleBuffer2dBodyC<DataT> *body)
      : BufferC<DataT>(body)
    {}
    //: Body pointer constructor.

    SingleBuffer2dBodyC<DataT> &Body()
    { return static_cast<SingleBuffer2dBodyC<DataT> &>(BufferC<DataT>::Body()); }
    //: Access body.
    
    const SingleBuffer2dBodyC<DataT> &Body() const
    { return static_cast<const SingleBuffer2dBodyC<DataT> &>(BufferC<DataT>::Body()); }
    //: Access body.
    
  public:

    friend class Buffer2dC<DataT>;
  };
  
  template<typename DataT>
  Buffer2dC<DataT>::Buffer2dC(SizeT size1,SizeT size2)
    : BufferC<DataT>(SingleBuffer2dC<DataT>::AllocBody(size1,size2))
  {}
  //: Sized constructor.

  
}


#endif
