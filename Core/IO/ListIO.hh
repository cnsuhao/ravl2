// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_LISTIO_HEADER
#define RAVL_LISTIO_HEADER 1
///////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlIO
//! author="James Smith"
//! date="24/03/2003"
//! docentry="Ravl.Core.Data Processing.IO"
//! file="Ravl/Core/IO/ListIO.hh"

#include "Ravl/DP/SPort.hh"
#include "Ravl/DList.hh"
#include "Ravl/DLIter.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  //////////////////////////////
  //! userlevel=Develop
  //: Seekable port from a DList (body)
  
  template<class DataT>
  class DPISListBodyC 
    : public DPISPortBodyC<DataT> 
  {
  public:
    DPISListBodyC(const DListC<DataT> &dat);
    //: Constructor.
    
    virtual bool IsGetReady() const
    { return iter; }
    //: Is some data ready ?
    
    virtual bool IsGetEOS() const
    { return iter; }
    //: Has the End Of Stream been reached ?
    // true = yes.
    
    virtual DataT Get();
    //: Get next piece of data.
    
    virtual IntT GetArray(SArray1dC<DataT> &data);
    //: Get an array of data from stream.
    // returns the number of elements processed.
    
    virtual bool Get(DataT &buff);
    //: Try and get next piece of data.
    
    virtual bool Seek(UIntT off);
    //: Seek to location in stream.
    // Returns false, if seek failed.
    // if an error occurered (Seek returned False) then stream position will not be changed.

    virtual bool DSeek(IntT off);
    //: Delta Seek, goto location relative to the current one.
    // The default behavour of this functions is : Do some error checking then: 
    // Seek((UIntT)((IntT) Tell() + off)); 
    // if an error occurered (DSeek returned False) then stream position will not be changed.

    virtual UIntT Tell() const;
    //: Find current location in stream.
    // Defined as the index of the next object to be written or read. 
    // May return ((UIntT) (-1)) if not implemented.

    virtual UIntT Size() const;
    //: Find the total size of the stream. (assuming it starts from 0)
    // May return ((UIntT) (-1)) if not implemented.

    virtual UIntT Start() const;
    //: Find the offset where the stream begins, normally zero.
    // Defaults to 0

  protected:
    DListC<DataT> container;
    typename DListC<DataT>::IteratorT iter;
    IntT next;
  };
  
  /////////////////////////////////
  //! userlevel=Normal
  //: Seekable port from a DList (body)
  
  template<class DataT>
  class DPISListC 
    : public DPIPortC<DataT>
  {
  public:
    DPISListC(const DListC<DataT> &dat)
      : DPEntityC(*new DPISListBodyC<DataT>(dat))      
    {}
    //: Constructor.
  };
  
  ////////////////////////////////////////
  //: Some helper functions.
  
  template<class DataT>
  DPISListC<DataT> DPISList(const DListC<DataT> &dat)
  { return DPISList<DataT>(dat); }
  
  //: Use container as source for stream.
  
  ////////////////////////////////////////////////////////
  
  template<class DataT>
  DPISListBodyC<DataT>::DPISListBodyC(const DListC<DataT> &dat)
    : container(dat),
      iter(const_cast<DListC<DataT> &>(dat)),
      next(0)
  {}

  template<class DataT>
  DataT DPISListBodyC<DataT>::Get() {
    const DataT &dat = iter.Data();
    iter++;
    next++;
    ONDEBUG(cerr << "DPISListC::Get -  next frame = " << next << endl);
    return dat;
  }
  
  template<class DataT>
  bool DPISListBodyC<DataT>::Get(DataT &buff) {
    if(!iter)
      return false;
    buff = *iter;
    iter++;
    next++;
    ONDEBUG(cerr << "DPISListC::Get -  next frame = " << next << endl);
    return true;
  }
  
  template<class DataT>
  IntT DPISListBodyC<DataT>::GetArray(SArray1dC<DataT> &data) {
    for(SArray1dIterC<DataT> it(data);it;it++) {
      if(!iter)
	return it.Index().V();
      *it = *iter;
      iter++;
      next++;
    }
    ONDEBUG(cerr << "DPISListC::GetArray -  next frame = " << next << endl);
    return data.Size();
  }

  template<class DataT>
  bool DPISListBodyC<DataT>::Seek(UIntT off) {
    iter.Nth(off);
    next = off;
    ONDEBUG(cerr << "DPISListC::Seek -  target = " << off << ", next frame = " << next << endl);
    return true;
  }
  
  template<class DataT>
  bool DPISListBodyC<DataT>::DSeek(IntT off) {
    iter.RelNth(off);
    next += off;
    ONDEBUG(cerr << "DPISListC::DSeek - offset  = " << off << ", next frame = " << next << endl);
    return true;
  }
  
  template<class DataT>
  UIntT DPISListBodyC<DataT>::Tell() const {
    ONDEBUG(cerr << "DPISListC::Tell - next frame = " << next << endl);
    return next;
  }
  
  template<class DataT>
  UIntT DPISListBodyC<DataT>::Size() const {
    ONDEBUG(cerr << "DPISListC::Size - size = " << container.Size() << endl);
    return container.Size();
  }
  
  template<class DataT>
  UIntT DPISListBodyC<DataT>::Start() const {
    ONDEBUG(cerr << "DPISListC::Start - start = 0" << endl);
    return 0;
  }

#undef ONDEBUG
#undef DODEBUG
  
}

#endif
