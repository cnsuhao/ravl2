// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SINGLEBUFFER_HEADER
#define RAVL_SINGLEBUFFER_HEADER 1
///////////////////////////////////////////////////////
//! docentry="Ravl.API.Core.Arrays.Buffer"
//! file="Ravl/Core/Container/Buffer/SingleBuffer.hh"
//! rcsid="$Id$"
//! lib=RavlCore
//! userlevel=Advanced
//! author="Charles Galambos"
//! date="10/04/2002"

#include "Ravl/Buffer.hh"

namespace RavlN {
  
  template<typename DataT>
  inline
  void ConstructRawArray(DataT *data,SizeT size) {
#if RAVL_COMPILER_VISUALCPP
    DataT *at = data;
    DataT *end = &at[size];
	try {
      for(;at != end;at++)
        new(at) DataT();
	} catch(...) {
	  DataT *die = data;
	  for(;die != at;die++)
	    die->~DataT();
	  throw ;
	}
#else
    new(data) DataT[size];
#endif
  }
  
  template<typename DataT>
  inline
  void DestructRawArray(DataT *data,SizeT size) {
    DataT *at = data;
    DataT *end = &at[size];
    for(;at != end;at++)
      at->~DataT();    
  }

  inline
  void ConstructRawArray(IntT *data,SizeT size) 
  {}
  
  inline
  void DestructRawArray(IntT *data,SizeT size) 
  {}

  inline
  void ConstructRawArray(UIntT *data,SizeT size) 
  {}
  
  inline
  void DestructRawArray(UIntT *data,SizeT size) 
  {}
  
  inline
  void ConstructRawArray(RealT *data,SizeT size) 
  {}
  
  inline
  void DestructRawArray(RealT *data,SizeT size) 
  {}

  inline
  void ConstructRawArray(ByteT *data,SizeT size) 
  {}
  
  inline
  void DestructRawArray(ByteT *data,SizeT size) 
  {}

  inline
  void ConstructRawArray(SByteT *data,SizeT size) 
  {}
  
  inline
  void DestructRawArray(SByteT *data,SizeT size) 
  {}
  
  inline
  void ConstructRawArray(FloatT *data,SizeT size) 
  {}
  
  inline
  void DestructRawArray(FloatT *data,SizeT size) 
  {}
  
  inline
  void ConstructRawArray(bool *data,SizeT size) 
  {}
  
  inline
  void DestructRawArray(bool *data,SizeT size) 
  {}

  inline
  void ConstructRawArray(Int16T *data,SizeT size) 
  {}
  
  inline
  void DestructRawArray(Int16T *data,SizeT size) 
  {}
  
  inline
  void ConstructRawArray(UInt16T *data,SizeT size) 
  {}
  
  inline
  void DestructRawArray(UInt16T *data,SizeT size) 
  {}

  inline
  void ConstructRawArray(Int64T *data,SizeT size) 
  {}
  
  inline
  void DestructRawArray(Int64T *data,SizeT size) 
  {}
  
  inline
  void ConstructRawArray(UInt64T *data,SizeT size) 
  {}
  
  inline
  void DestructRawArray(UInt64T *data,SizeT size) 
  {}
  
  //! userlevel=Develop
  //: Single allocation buffer body.
  // Allocate data along with body.
  
  template<typename DataT>
  class SingleBufferBodyC
    : public BufferBodyC<DataT>
  {
  public:
    SingleBufferBodyC(SizeT nsize)
      : BufferBodyC<DataT>(0,nsize,false)
    { 
#if RAVL_CPUTYPE_32
      // Make sure buffer is 8-byte aligned.
      this->buff = reinterpret_cast<DataT *>(&reinterpret_cast<char *>(&(this[1]))[4]);
#else
      this->buff = reinterpret_cast<DataT *>(&(this[1]));
#endif
	 // cerr << "Memory at " << (void*) this->buff << "\n";
      ConstructRawArray(this->buff,this->Size()); 
    }
    //: Default constructor.
    
    SingleBufferBodyC(SizeT nsize,UIntT align)
	: BufferBodyC<DataT>(0,nsize,false)
    {
      // Align memory
      char *buf = reinterpret_cast<char *>(&(this[1]));
      SizeT alignm1 = align-1;
      this->buff = reinterpret_cast<DataT *>(buf + ((align - (((SizeT) buf) & alignm1)) & alignm1));

//reinterpret_cast<DataT *>((IntT) buf + ((align - (((IntT) buf) & alignm1)) & alignm1));
       
//this->buff = reinterpret_cast<DataT *>(buf + ((align - (( reinterpret_cast<IntT>  (buf) ) & alignm1)) & alignm1));
	//reinterpret_cast<IntT>  (buf) 
     
 // Construct array
      ConstructRawArray(this->buff,this->Size()); 
    }
    //: Construct buffer with alignment
    // Note: Aligment must be a power of 2
    
    ~SingleBufferBodyC() 
    { DestructRawArray(this->buff,this->Size()); }
    //: Destructor.
    
  protected:
  }; 
  
  //! userlevel=Advanced
  //: Single allocation buffer handle.
  // Allocate data along with body.
  
  template<typename DataT>
  class SingleBufferC
    : public BufferC<DataT>
  {
  public:
    SingleBufferC()
    {}
    //: Default constructor.
    // Creates an invalid handle.

    SingleBufferC(SizeT nsize) 
      : BufferC<DataT>(*AllocBody(nsize))
    {}
    //: Constructor.
    
    SingleBufferC(SizeT nsize,UIntT align) 
      : BufferC<DataT>(*AllocBody(nsize,align))
    {}
    //: Constructor.
    // Note: Aligment must be a power of 2
    
  protected:
    static SingleBufferBodyC<DataT> *AllocBody(SizeT size) {
#if RAVL_CPUTYPE_32
      // Make sure buffers are 8-byte aligned.
      SingleBufferBodyC<DataT> *ret = reinterpret_cast<SingleBufferBodyC<DataT> *> (malloc(sizeof(SingleBufferBodyC<DataT>) + 4 + (size * sizeof(DataT))));
#else
      SingleBufferBodyC<DataT> *ret = reinterpret_cast<SingleBufferBodyC<DataT> *> (malloc(sizeof(SingleBufferBodyC<DataT>) + (size * sizeof(DataT))));
#endif
      try {
        new(ret) SingleBufferBodyC<DataT>(size);
      } catch(...) {
        free(ret);
      }
      return ret;
    }

    //: Allocate a body object plus some space.
    
    static SingleBufferBodyC<DataT> *AllocBody(SizeT size,UIntT align) {
      SingleBufferBodyC<DataT> *ret = reinterpret_cast<SingleBufferBodyC<DataT> *> (malloc(sizeof(SingleBufferBodyC<DataT>) + (size * sizeof(DataT)) + (align-1) ));
      try {
        new(ret) SingleBufferBodyC<DataT>(size,align);
      } catch(...) {
        free(ret);
      }
      return ret;
    }
    //: Allocate a body object plus some space with alignment.
    
    SingleBufferC(SingleBufferBodyC<DataT> &body)
      : BufferC<DataT>(body)
    {}
    //: Body constructor.
    
    SingleBufferBodyC<DataT> &Body()
    { return static_cast<SingleBufferBodyC<DataT> &>(BufferC<DataT>::Body()); }
    //: Access body.
    
    const SingleBufferBodyC<DataT> &Body() const
    { return static_cast<const SingleBufferBodyC<DataT> &>(BufferC<DataT>::Body()); }
    //: Access body.
    
  public:
  };
  
  
}


#endif
