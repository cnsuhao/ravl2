// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DARRAY1D_HEADER
#define RAVL_DARRAY1D_HEADER 1
//! docentry="Ravl.Core.Misc"
//! lib=RavlCore
//! author="Charles Galambos"
//! rcsid="$Id$"

#include "Ravl/InDList.hh"
#include "Ravl/Array1d.hh"

namespace RavlN {

  template<class DataT> class DArray1dC;
  template<class DataT> class DArray1dIterC;
  
  //! userlevel=Develop
  //: Chunk of a dynamic array.

  template<class DataT>
  class DChunkC 
    : public DLinkC
  {
  public:
    DChunkC()
    {}
    //: Default constructor.

    DChunkC(IndexC noff,const Array1dC<DataT> &dat)
      : data(dat,noff)
    {}
    //:Constructor.

    DChunkC(const Array1dC<DataT> &dat)
      : data(dat)
    {}
    //: Constructor.
    
    IndexC Offset() const
    { return data.Range().Min(); }
    //: Offset from start of list.
    
    IndexC &Offset()
    { return data.Range().Min(); }
    //: Offset from start of list.
    
    UIntT Size() const
    { return data.Size(); }
    //: Size of chunk.
    
    IndexC IMax() const
    { return data.IMax(); }
    //: Maximum offset used.

    IndexC IMin() const
    { return data.IMin(); }
    //: Maximum offset used.
    
    const Array1dC<DataT> &Data() const
    { return data; }
    //: Access data.

    Array1dC<DataT> &Data()
    { return data; }
    //: Access data.

    bool Contains(IndexC i) const 
    { return data.Contains(i); }
    //: Does this chunk contain the offset?
    
    DataT &Index(IndexC i) 
    { return data[i]; }
    //: Access data.
    
    const DataT &Index(IndexC i) const
    { return data[i]; }
    //: Access data.
    
  protected:
    Array1dC<DataT> data;
  };


  //! userlevel=Develop
  //: Dynamic arrays.
  
  template<class DataT>
  class DArray1dBodyC
    : public RCBodyC
  {
  public:
    DArray1dBodyC()
      : allocBlocksize(1024)
    {}
    //: Default constructor.

    DArray1dBodyC(IndexRangeC range) {
      chunks.InsLast(*new DChunkC<DataT>(range.Min(),Array1dC<DataT>(range.Size())));
    }
    //: Constructor an array with a range allocated.
    
    DArray1dBodyC(SizeT size) {
      chunks.InsLast(*new DChunkC<DataT>(Array1dC<DataT>(size)));
    }
    //: Constructor an array with size elements allocated.

    DArray1dBodyC(const Array1dC<DataT> &arr) {
      chunks.InsLast(*new DChunkC<DataT>(arr));
    }
    //: Construct from a normal array.
    
    DataT &Index(IndexC i);
    //: Find data item with that index.
    
    const DataT &Index(IndexC i) const;
    //: Find data item with that index.
    
    UIntT Append(const Array1dC<DataT> &newData);
    //: Append data to this array.
    // Note the data is not copied! 
    // The number of items appended is returned.
    
    UIntT Append(const DArray1dC<DataT> &newData);
    //: Append data to this array.
    // Note the data is not copied!
    // The number of items appended is returned.
    
    IndexC Append(const DataT &newData);
    //: Append data to this array.
    // Returns index of new item.
    
    bool Contains(IndexC i) const;
    //: Test if container contains index.
    
    void Fill(const DataT &value);
    //: Fill array with given value.
    
    IndexRangeC Range() const { 
      if(chunks.IsEmpty())
	return IndexRangeC(0);
      return IndexRangeC(chunks.First().IMin(),chunks.Last().IMax());
    }
    //: Get range of indexes covered by array.
    // There may be holes in the range.

    IndexC IMax() const { 
      if(chunks.IsEmpty())
	return -1;// Together with IMin this should indicate an empty array.
      return chunks.Last().IMax();
    }
    //: Maximum offset used.
    // If range is empty the results are undefined.
    
    IndexC IMin() const {
      if(chunks.IsEmpty())
	return 0; // Together with IMax this should indicate an empty array.
      return chunks.Last().IMin();
    }
    //: Minimum offset used.
    // If range is empty the results are undefined.
    
    bool IsEmpty() const
    { return chunks.IsEmpty(); }
    //: Is array empty ?
    
    void Empty()
    { chunks.Empty(); }
    //: Empty this array of all its contents.
    
  protected:
    IntrDListC<DChunkC<DataT> > chunks;
    
    // Some extra stuff to make appending single items faster. 
    Array1dC<DataT> lastBlk; 
    IndexC nextFree;
    UIntT allocBlocksize;
    friend class DArray1dIterC<DataT>;
  };

  //! userlevel=Develop
  //: Dynamic arrays.
  
  template<class DataT>
  class DArray1dC
    : public RCHandleC<DArray1dBodyC<DataT> >
  {
  public:
    DArray1dC()
      : RCHandleC<DArray1dBodyC<DataT> >(*new DArray1dBodyC<DataT>())
    {}
    //: Default constructor.
    // Creates an empty array.

    DArray1dC(IndexRangeC range)
      : RCHandleC<DArray1dBodyC<DataT> >(*new DArray1dBodyC<DataT>(range))
    {}
    //: Default constructor.
    // Creates a array with range elements allocated.
    
    DArray1dC(SizeT size)
      : RCHandleC<DArray1dBodyC<DataT> >(*new DArray1dBodyC<DataT>(size))
    {}
    //: Default constructor.
    // Creates an array of the given size starting from index 0.

    DArray1dC(const Array1dC<DataT> &arr)
      : RCHandleC<DArray1dBodyC<DataT> >(*new DArray1dBodyC<DataT>(arr))
    {}
    //: Default constructor.
    // Creates an array of the given size starting from index 0.
    
    DataT &Index(IndexC i)
    { return Body().Index(i); }
    //: Find data item with that index.

    const DataT &Index(IndexC i) const
    { return Body().Index(i); }
    //: Find data item with that index.
    
    DataT &operator[](IndexC i)
    { return Index(i); }
    //: Access element.
    
    const DataT &operator[](IndexC i) const
    { return Index(i); }
    //: Access element.

    UIntT Append(const Array1dC<DataT> &newData)
    { return Body().Append(newData); }
    //: Append data to this array.
    // Note the data is not copied!
    // The number of items appended is returned.
    
    UIntT Append(const DArray1dC<DataT> &newData)
    { return Body().Append(newData); }
    //: Append data to this array.
    // Note the data is not copied!
    // The number of items appended is returned.
    
    IndexC Append(const DataT &newData)
    { return Body().Append(newData); }
    //: Append data to this array.
    // Returns index of new item.
    
    bool Contains(IndexC i) const
    { return Body().Contains(i); }
    //: Test if container contains index.
    
    void Fill(const DataT &value)
    { Body().Fill(value); }
    //: Fill array with given value.
    
    IndexRangeC Range() const;
    //: Get range of indexes covered by array.
    // Note, there may be holes in the range.
    
    IndexC IMax() const 
    { return Body().IMax(); }
    //: Maximum offset used.
    // If range is empty the results are undefined.
    
    IndexC IMin() const 
    { return Body().IMin(); }
    //: Minimum offset used.
    // If range is empty the results are undefined.
    
    bool IsEmpty() const
    { return Body().IsEmpty(); }
    //: Is array empty ?
    
    void Empty()
    { Body().Empty(); }
    //: Empty this array of all its contents.
  protected:
    friend class DArray1dBodyC<DataT>;
    friend class DArray1dIterC<DataT>;
  };
  
  template<class DataT>
  DataT &DArray1dBodyC<DataT>::Index(IndexC i) {
    IntrDLIterC<DChunkC<DataT> > it(chunks);
    for(;it;it++) {
      if(it->Contains(i))
	break;
    }
    RavlAssertMsg(it,"Index out of range. ");
    return it->Index(i);
  }
  
  template<class DataT>
  const DataT &DArray1dBodyC<DataT>::Index(IndexC i) const {
    IntrDLIterC<DChunkC<DataT> > it(chunks);
    for(;it;it++) {
      if(it->Contains(i))
	break;
    }
    RavlAssertMsg(it,"Index out of range. ");
    return it->Index(i);
  }

  template<class DataT>
  bool DArray1dBodyC<DataT>::Contains(IndexC i) const {
    IntrDLIterC<DChunkC<DataT> > it(chunks);
    for(;it;it++) {
      if(it->Contains(i))
	return true;
      if(it->IMax() > i)
	break;
    }
    return false;
  }
  
  template<class DataT>
  void DArray1dBodyC<DataT>::Fill(const DataT &value) {
    for(IntrDLIterC<DChunkC<DataT> > it(chunks);it;it++)
      it->Data().Fill(value);
  }
  
  template<class DataT>
  UIntT DArray1dBodyC<DataT>::Append(const Array1dC<DataT> &newData) {
    if(chunks.IsEmpty())
      chunks.InsLast(*new DChunkC<DataT>(0,newData));
    else
      chunks.InsLast(*new DChunkC<DataT>(chunks.Last().IMax()+1,newData));
    lastBlk = Array1dC<DataT>(); // Empty last block holder.
    return newData.Size();
  }
  
  template<class DataT>
  UIntT DArray1dBodyC<DataT>::Append(const DArray1dC<DataT> &newData) {
    if(!newData.IsValid())
      return 0;
    IntrDLIterC<DChunkC<DataT> > it(newData.Body().chunks);
    if(!it) return 0;
    UIntT size = 0;
    if(chunks.IsEmpty())
      chunks.InsLast(*new DChunkC<DataT>(it->Data()));
    else
      chunks.InsLast(*new DChunkC<DataT>(chunks.Last().IMax()+1,it->Data()));
    size += it->Size();
    for(it++;it;it++) {
      size += it->Size();
      chunks.InsLast(*new DChunkC<DataT>(chunks.Last().IMax()+1,it->Data()));
    }
    lastBlk = Array1dC<DataT>(); // Empty last block holder.
    return size;
  }
  
  template<class DataT>
  IndexC DArray1dBodyC<DataT>::Append(const DataT &newData) {
    if(lastBlk.Size() == 0) {
      IndexC imax = IMax() + 1;
      Array1dC<DataT> newBlk(imax,imax + (allocBlocksize-1));
      nextFree = imax+1;
      newBlk[imax] = newData;
      Append(Array1dC<DataT>(newBlk,IndexRangeC(imax,imax)));
      lastBlk = newBlk;
      return imax;
    }
    RavlAssert(chunks.Last().Data().Buffer() == lastBlk.Buffer());
    lastBlk[nextFree] = newData;
    if(lastBlk.IMax() == nextFree)
      lastBlk = Array1dC<DataT>(); // Empty last block holder.
    IndexC used = nextFree++;
    chunks.Last().Data().SetIMax(used); // Must be a faster way to extend the array bounds.
    return used;
  }
}

#endif
