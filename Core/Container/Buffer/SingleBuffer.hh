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
    new(data) DataT[size];
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
      : BufferBodyC<DataT>(array,nsize)
    { ConstructRawArray(&array[1],this->Size()-1); }
    //: Default constructor.
    
    ~SingleBufferBodyC() 
    { DestructRawArray(&array[1],this->Size()-1); }
    //: Destructor.
    
  protected:
    DataT array[1];
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

    SingleBufferC(UIntT nsize) 
      : BufferC<DataT>(*AllocBody(nsize))
    {}
    //: Constructor.
    
  protected:
    static SingleBufferBodyC<DataT> *AllocBody(SizeT size) {
      if(size < 1) size = 1;
      SingleBufferBodyC<DataT> *ret = reinterpret_cast<SingleBufferBodyC<DataT> *> (malloc(sizeof(SingleBufferBodyC<DataT>) + (size-1) * sizeof(DataT)));
      new(ret) SingleBufferBodyC<DataT>(size);
      return ret;
    }
    //: Allocate a body object plus some space.
    
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
