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
//! file="Ravl/Core/System/DArray1d.hh"

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

    DataT &Nth(UIntT i) 
    { return data[data.IMin() + i]; }
    //: Access nth element in the array from the first in this chunk.
    
    const DataT &Nth(UIntT i) const 
    { return data[data.IMin() + i]; }
    //: Access nth element in the array from the first in this chunk
    
    DataT &First()
    { return data[data.IMin()]; }
    //: First element in the array.
    
    const DataT &First() const
    { return data[data.IMin()]; }
    //: First element in the array.
    
    DataT &Last()
    { return data[data.IMax()]; }
    //: First element in the array.
    
    const DataT &Last() const
    { return data[data.IMax()]; }
    //: First element in the array.
    
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
      : nextFree(0),
	allocBlocksize(1024)
    {}
    //: Default constructor.
    
    DArray1dBodyC(IndexRangeC range) 
      : nextFree(0),
	allocBlocksize(1024)
    { chunks.InsLast(*new DChunkC<DataT>(range.Min(),Array1dC<DataT>(range.Size()))); }
    //: Constructor an array with a range allocated.

    
    DArray1dBodyC(SizeT size) 
      : nextFree(0),
	allocBlocksize(1024)
    { chunks.InsLast(*new DChunkC<DataT>(Array1dC<DataT>(size))); }
    //: Constructor an array with size elements allocated.
    
    DArray1dBodyC(SizeT size,bool preAlloc) 
      : lastBlk(size),
	nextFree(0),
	allocBlocksize(1024)
    { 
      if(size > 0 && preAlloc)
	chunks.InsLast(*new DChunkC<DataT>(Array1dC<DataT>(lastBlk,IndexRangeC(0,-1)))); 
    }
    //: Constructor an array with an expected size.
    // This is usefull if you know you'll be appending 'size' elements.
    
    DArray1dBodyC(const Array1dC<DataT> &arr) 
      : nextFree(0),
	allocBlocksize(1024)
    { chunks.InsLast(*new DChunkC<DataT>(arr)); }
    //: Construct from a normal array.

    DArray1dBodyC(const SArray1dC<DataT> &arr) 
      : nextFree(0),
	allocBlocksize(1024)
    { chunks.InsLast(*new DChunkC<DataT>(arr)); }
    //: Construct from a normal array.
    
    DArray1dC<DataT> Copy() const;
    //: Make a copy of this DArray.
    
    DataT &Index(IndexC i);
    //: Find data item with that index.
    
    const DataT &Index(IndexC i) const;
    //: Find data item with that index.
    
    DataT &Nth(UIntT i);
    //: Find the n'th entry, irrespective of index values.
    
    const DataT &Nth(UIntT i) const;
    //: Find the n'th entry, irrespective of index values.
    
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
    
    bool Remove(IndexC i);
    //: Remove single entry from the array.
    
    bool Remove(IndexC min,IndexC max);
    //: Remove entries from min to max from the array.
    // This removes entries from min to max inclusively from
    // the array.
    
    bool RemoveFirst();
    //: Remove first element from the array.
    
    bool RemoveLast();
    //: Remove last element from the array.
    
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
    
    UIntT Size() const;
    //: Find the number of elements in the DArray.
    // This doesn't count holes in the array. <p>
    // At the moment this value is computed, this maybe a little
    // slow for applications, and so maybe changed later.
    
    DataT &First()
    { return chunks.First().First(); }
    //: Access first element in the array.
    
    const DataT &First() const
    { return chunks.First().First(); }
    //: Access first element in the array.
    
    DataT &Last()
    { return chunks.Last().Last(); }
    //: Access last element in the array.
    
    const DataT &Last() const
    { return chunks.Last().Last(); }
    //: Access last element in the array.
    
  protected:
    bool FindChunk(int i,IntrDLIterC<DChunkC<DataT> > &it) const;
    //: Find the chunk containing the interest.
    
    bool FindNthChunk(UIntT i,UIntT &at,IntrDLIterC<DChunkC<DataT> > &it) const;
    //: Find the chunk containing the interest.
    
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
    //: Range constructor.
    // Creates a array with range elements allocated.
    
    DArray1dC(SizeT size)
      : RCHandleC<DArray1dBodyC<DataT> >(*new DArray1dBodyC<DataT>(size))
    {}
    //: Size constructor.
    // Creates an array of the given size starting from index 0.
    
    DArray1dC(SizeT size,bool preAlloc)
      : RCHandleC<DArray1dBodyC<DataT> >(*new DArray1dBodyC<DataT>(size,preAlloc))
    {}
    //: Constructor an array with an expected size.
    // This is usefull if you know you'll be appending 'size' elements.
    
    DArray1dC(const Array1dC<DataT> &arr)
      : RCHandleC<DArray1dBodyC<DataT> >(*new DArray1dBodyC<DataT>(arr))
    {}
    //: Array constructor.
    // Creates an array of the given size starting from index 0.

    DArray1dC(const SArray1dC<DataT> &arr)
      : RCHandleC<DArray1dBodyC<DataT> >(*new DArray1dBodyC<DataT>(arr))
    {}
    //: SArray constructor.
    // Creates an array of the given size starting from index 0.
    
    DArray1dC<DataT> Copy() const
    { return Body().Copy(); }
    //: Make a copy of this DArray.
    
    DataT &Index(IndexC i)
    { return Body().Index(i); }
    //: Find data item with that index.

    const DataT &Index(IndexC i) const
    { return Body().Index(i); }
    //: Find data item with that index.
    
    DataT &Nth(UIntT i)
    { return Body().Nth(i); }
    //: Find the n'th entry, irrespective of index values.
    
    const DataT &Nth(UIntT i) const
    { return Body().Nth(i); }
    //: Find the n'th entry, irrespective of index values.
    
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
    
    bool Remove(IndexC i)
    { return Body().Remove(i); }
    //: Remove single entry from the array.
    
    bool Remove(IndexC min,IndexC max)
    { return Body().Remove(min,max); }
    //: Remove entries from min to max from the array.
    // This removes entries from min to max inclusively from
    // the array.
    
    bool RemoveFirst()
    { return Body().RemoveFirst(); }
    //: Remove first element from the array.
    
    bool RemoveLast()
    { return Body().RemoveLast(); }
    //: Remove last element from the array.
    
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
    
    UIntT Size() const
    { return Body().Size(); }
    //: Find the number of elements in the DArray.
    // This doesn't count holes in the array.

    DataT &First()
    { return Body().First(); }
    //: Access first element in the array.
    
    const DataT &First() const
    { return Body().First(); }
    //: Access first element in the array.
    
    DataT &Last()
    { return Body().Last(); }
    //: Access last element in the array.
    
    const DataT &Last() const
    { return Body().Last(); }
    //: Access last element in the array.
    
  protected:
    friend class DArray1dBodyC<DataT>;
    friend class DArray1dIterC<DataT>;
  };


  
  template<class DataT>
  bool DArray1dBodyC<DataT>::FindChunk(int i,IntrDLIterC<DChunkC<DataT> > &it) const {
    it = IntrDLIterC<DChunkC<DataT> >(chunks);
    for(;it;it++) {
      if(it->Contains(i)) {
	return true;
      }
      if(it->IMax() > i)
	return false;
    }
    return false;
  }
  
  template<class DataT>
  bool DArray1dBodyC<DataT>::FindNthChunk(UIntT i,UIntT &at,IntrDLIterC<DChunkC<DataT> > &it) const {
    it = IntrDLIterC<DChunkC<DataT> >(chunks);
    at = 0;
    for(;it;it++) {
      UIntT next = at + it->Size();
      if(next > i) return true;
      at = next;
    }
    return false;
  }
  
  template<class DataT>
  DArray1dC<DataT> DArray1dBodyC<DataT>::Copy() const {
    DArray1dC<DataT> ret;
    IntrDLIterC<DChunkC<DataT> > it(chunks);
    // FIXME:- Could try and de-fragment here.
    for(;it;it++)
      ret.Body().chunks.InsLast(*new DChunkC<DataT>(it->Data().Copy()));
    return ret;
  }
  
  template<class DataT>
  UIntT DArray1dBodyC<DataT>::Size() const {
    UIntT size = 0;
    for(IntrDLIterC<DChunkC<DataT> > it(chunks);it;it++)
      size += it->Data().Size();
    return size;
  }
  
  template<class DataT>
  DataT &DArray1dBodyC<DataT>::Index(IndexC i) {
    IntrDLIterC<DChunkC<DataT> > it;
    bool x = FindChunk(i.V(),it);
    RavlAssertMsg(x,"Index out of range. ");
    return it->Index(i);
  }
  
  template<class DataT>
  const DataT &DArray1dBodyC<DataT>::Index(IndexC i) const {
    IntrDLIterC<DChunkC<DataT> > it;
    bool x = FindChunk(i.V(),it);
    RavlAssertMsg(x,"Index out of range. ");
    return it->Index(i);
  }
  
  template<class DataT>
  DataT &DArray1dBodyC<DataT>::Nth(UIntT i) {
    IntrDLIterC<DChunkC<DataT> > it;
    UIntT at;
    bool x = FindNthChunk(i,at,it);
    RavlAssertMsg(x,"Index out of range. ");
    return it->Nth(i - at);
  }
  
  template<class DataT>
  const DataT &DArray1dBodyC<DataT>::Nth(UIntT i) const {
    IntrDLIterC<DChunkC<DataT> > it;
    UIntT at;
    bool x = FindNthChunk(i,at,it);
    RavlAssertMsg(x,"Index out of range. ");
    return it->Nth(i - at);    
  }
  
  template<class DataT>
  bool DArray1dBodyC<DataT>::Contains(IndexC i) const {
    IntrDLIterC<DChunkC<DataT> > it;
    return FindChunk(i.V(),it);
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
    chunks.Last().Data().SetIMax(nextFree); // Must be a faster way to extend the array bounds.
    nextFree++;
    return nextFree;
  }
  
  template<class DataT>
  bool DArray1dBodyC<DataT>::Remove(IndexC i) {
    IntrDLIterC<DChunkC<DataT> > it;
    if(!FindChunk(i.V(),it))
      return false;
    if(it->IMax() == i) { // At the end of a chunk ?
      if(it->IMin() == i) { // Is this the last element in the chunk ?
	it.Del(); // If so delete it.
	return true;
      }
      it->Data().SetSubRange(it->IMin(),it->IMax()-1);
      return true;
    }
    if(it->IMin() == i) { // At the beginnig of a chunk ?
      it->Data().SetSubRange(it->IMin()+1,it->IMax());
      return true;
    }
    // Cut the chunk in two removing the element.
    Array1dC<DataT> newArr = it->Data();
    it->Data().SetSubRange(it->IMin(),i-1);
    newArr.SetSubRange(i+1,it->IMax());
    it.InsertAft(*new DChunkC<DataT>(newArr));
    return true;
  }
  
  template<class DataT>  
  bool DArray1dBodyC<DataT>::RemoveFirst() {
    if(chunks.IsEmpty())
      return false;
    DChunkC<DataT> &chunk = chunks.First();
    if(chunk.IMin() != chunk.IMax())
      chunk.Data().SetSubRange(chunk.IMin()+1,chunk.IMax());
    else
      chunks.DelFirst();
    // FIXME :- We could actually be more clever about manging the lastBlk
    lastBlk = Array1dC<DataT>(); // Empty last block holder.
    return true;    
  }

  template<class DataT>  
  bool DArray1dBodyC<DataT>::RemoveLast() {
    if(chunks.IsEmpty())
      return false;
    DChunkC<DataT> &chunk = chunks.Last();
    if(chunk.IMin() != chunk.IMax())
      chunk.Data().SetSubRange(chunk.IMin(),chunk.IMax()-1);
    else
      chunks.DelLast();
    // FIXME :- We could actually be more clever about manging the lastBlk
    lastBlk = Array1dC<DataT>(); // Empty last block holder.
    return true;
  }

  template<class DataT>  
  bool DArray1dBodyC<DataT>::Remove(IndexC min,IndexC max){
    RavlAssert(min <= max);
    IntrDLIterC<DChunkC<DataT> > it(chunks);
    for(;it;it++) {
      if(it->IMax() >= min)
	break;
    }
    if(!it) return false;
    if(it->IMin() > max) // Was range missed entirely ?
      return false;
    // Cut off end of chunk after min.
    if(it->IMin() < min) { // Check we don't need to delete the whole chunk.
      Array1dC<DataT> newArr = it->Data();
      it->Data().SetSubRange(it->IMin(),min-1);
      // Is max within the same chunk ?
      if(it->IMax() > max) { 
	newArr.SetSubRange(max+1,it->IMax());
	it.InsertAft(*new DChunkC<DataT>(newArr));
	return true;
      }
    }
    // Cut out whole chunks between min and max.
    for(;it;it++) {
      if(it->IMax() <= max)
	it.Del();
    }
    // Cut off begining of chunk before max.
    if(it->Contains(max))
      it->Data().SetSubRange(max+1,it->IMax());
    return true;
  }

}

#endif
