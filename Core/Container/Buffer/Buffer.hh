// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BUFFER_HEADER
#define RAVL_BUFFER_HEADER 1
///////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Arrays.Buffer"
//! file="Ravl/Core/Container/Buffer/Buffer.hh"
//! lib=RavlCore
//! userlevel=Default
//! author="Charles Galambos"
//! date="24/01/2001"

#include "Ravl/Types.hh"
#include "Ravl/RefCounter.hh"
#include "Ravl/SBfAcc.hh"

//: Ravl global namespace.

namespace RavlN {
  
  //! userlevel=Develop
  //: Buffer body.
  // This holds a handle to data used in various arrays.
  
  template<class DataT>
  class BufferBodyC 
    : public RCBodyVC,
      public SizeBufferAccessC<DataT>
  {
  public:
    BufferBodyC(UIntT nsize,const DataT &defaultVal)
      : SizeBufferAccessC<DataT>(new DataT[nsize],nsize),
        deletable(true)
      { Fill(defaultVal); }
    //: Constructor a buffer of 'nsize' items, with default value.
    
    BufferBodyC(UIntT nsize)
      : SizeBufferAccessC<DataT>(new DataT[nsize],nsize),
        deletable(true)
      {}
    //: Constructor a buffer of 'nsize' items.
    
    BufferBodyC()
      : deletable(false)
      {}
    //: Default constructor.
    
    BufferBodyC(UIntT nsize,DataT *dat,bool copy = false,bool deletable = false);
    //: Construct from data.
    
    ~BufferBodyC() { 
      if(buff != 0 && deletable)
	delete [] buff;
    }
    //: Destructor.
    
  protected:    
    bool deletable;
  };
  
  //! userlevel=Develop
  //: Buffer handle.

  template<class DataT>
  class BufferC 
    : public RCHandleC<BufferBodyC<DataT> >
  {
  public:
    BufferC()
      {}
    //: Default constructor
    // creates an invalid handle.

    BufferC(UIntT nsize)
      : RCHandleC<BufferBodyC<DataT> >(*new BufferBodyC<DataT>(nsize))
      {}
    //: Constructor
    // Creates a buffer containing 'nsize' items.

    BufferC(UIntT nsize,DataT *dat,bool copy = false,bool deletable = false)
      : RCHandleC<BufferBodyC<DataT> >(*new BufferBodyC<DataT>(nsize,dat,copy,deletable))
      {}
    //: Constructor
    // Creates a buffer containing 'nsize' items.
    
  protected:
    BufferC(BufferBodyC<DataT> &bod)
      : RCHandleC<BufferBodyC<DataT> >(bod)
      {}
    //: Body constructor
    
    BufferBodyC<DataT> &Body()
      { return RCHandleC<BufferBodyC<DataT> >::Body(); }
    //: Access body.
    
    const BufferBodyC<DataT> &Body() const
      { return RCHandleC<BufferBodyC<DataT> >::Body(); }
    //: Constant access to body.

  public:
    UIntT Size() const
      { return Body().Size(); }
    //: Access size of buffer.
    
    inline DataT * ReferenceElm() const
      { return Body().ReferenceElm(); }
    // Returns the pointer to the reference element of the attached buffer.
    // The reference element need not to be the valid element of the buffer.
    
    void Fill(const DataT &val)
      { return Body().Fill(val); }
    //: Fill buffer with value.
    
    const SizeBufferAccessC<DataT> &BufferAccess() const
      { return Body(); }
    //: Access buffer.

#if 0
    operator SizeBufferAccessC<DataT> &()
      { return Body(); }
    //: Access as a size buffer.
    
    operator const SizeBufferAccessC<DataT> &() const
      { return Body(); }
    //: Access as a size buffer.
#else
    operator SizeBufferAccessC<DataT> &() const
      { return const_cast<SizeBufferAccessC<DataT> &>(((const SizeBufferAccessC<DataT> &)Body())); }
    //: Access as a size buffer.
    // I don't like this, but it gets around an irritating warning from gcc.
#endif
  };

  ////////////////////////////////////////////////////////////
  
  //: Construct from data.
  
  template<class DataT>
  BufferBodyC<DataT>::BufferBodyC(UIntT nsize,DataT *ndat,bool copy,bool ndeletable) 
    : SizeBufferAccessC<DataT>(ndat,nsize),
      deletable(ndeletable)
  {
    if(!copy)
      return ;
    buff = new DataT[nsize];
    DataT *place,*end = &buff[nsize];
    const DataT *source = ndat;
    for(place = buff;place != end;place++,source++)
      *place = *source;
  }
  
}


#endif
