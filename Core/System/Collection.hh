// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLCOLLECTION_HEADER
#define RAVLCOLLECTION_HEADER 1
//////////////////////////////////////////////////////
//! rcsid=$Id$
//! docentry="Ravl.Core.Misc"
//! author="Charles Galambos"
//! lib=RavlCore

#include "Ravl/SArray1d.hh"
#include "Ravl/Random.hh"
#include "Ravl/RefCounter.hh"

namespace RavlN {
  
  template<class DataT> class CollectionC;
  template<class DataT> class CollectionIterC;
  
  //! userlevel=Develop
  //: Collection of data.
  
  template<class DataT>
  class CollectionBodyC 
    : public RCBodyC
  {
  public:
    CollectionBodyC(SizeT maxSize = 10)
      : data(maxSize+1),
      n(0)
    {}
    //: Create an empty collection.
    // maxSize should be set to maximum number of 
    // elements the collection will contain.
    
    CollectionBodyC(const SArray1dC<DataT> &dat)
      : data(dat),
      n(dat.Size())
    {}
    //: Create a collection from an array of data.
    
    CollectionC<DataT> Copy() const;
    //: Create a copy of this collection.
    
    inline
    UIntT Insert(const DataT &dat);
    //: Add a data item to the collection.
    //  NB. This may cause the storage array to 
    // be reallocated which will invalidate any iterators
    // held on the collection. <p>
    // The index at which the item was placed is returned.
    
    inline
    UIntT InsertRandom(const DataT &dat);
    //: Add a data item to the collection in a random place.
    //  NB. This may cause the storage array to 
    // be reallocated which will invalidate any iterators
    // held on the collection. <p>
    // The index at which the item was placed is returned.
    
    
    DataT Pick();
    //: Pick a random item from the collection.
    // the element will be removed from the set.
    // It is the users responsiblity to ensure the
    // set is not empty when this method is called.
    // See 'IsEmpty()'
    
    CollectionC<DataT> Shuffle() const;
    //: Create a shuffled version of this collection.
    
    void ShuffleIP();
    //: Shuffle collection in place.
    
    void Merge(const CollectionC<DataT> &x);
    //: Merge collection 'x' into this one.
    
    void Merge(const SArray1dC<DataT> &x);
    //: Merge of array 'x' into this collection.
    
    inline bool IsEmpty() const
    { return n == 0; }
    //: Test if collection is empty.
    
    void Empty()
    { n = 0; }
    //: Empty the collection of all its contents.
    
    SizeT Size() const
    { return n; }
    //: Returns the number of data elements in the collection.
    
    SArray1dC<DataT> Array()
    { return SArray1dC<DataT>(data,n); }
    //: Access data as array.
    // Note: The returned array is a direct access
    // to the internal data structure, no operations
    // that modify the collection should be performed 
    // while its in use. 
    
    const SArray1dC<DataT> Array() const
    { return SArray1dC<DataT>(data,n); }
    //: Access data as array.
    // Note: The returned array is a direct access
    // to the internal data structure, no operations
    // that modify the collection should be performed 
    // while its in use. 
    
    CollectionC<DataT> Split(SizeT ne);
    //: Split the collection in two
    // return a random set of 'ne' elements from this one.
    
    CollectionC<DataT> Sample(SizeT ne) const;
    //: Take a random sample from the collection.
    // This collection is not modified. NOTE: Items
    // may be taken more than once.
    
    DataT &operator[](IndexC ind) { 
      RavlAssertMsg(ind < n,"Index out of range.");
      return data[ind];
    }
    //: Array style access.
    
    const DataT &operator[](IndexC ind) const { 
      RavlAssertMsg(ind < n,"Index out of range.");
      return data[ind];
    }
    //: Array style access.
    
    
  protected:
    SArray1dC<DataT> data;
    SizeT n;
  };
  
  //! userlevel=Normal
  //: Collection of data
  // An unordered collection of data.
  
  
  template<class DataT>
  class CollectionC 
    : public RCHandleC<CollectionBodyC<DataT> >
  {
  public:
    CollectionC()
    {}
    //: Default constructor.
    // creates an invalid handle.
    
    CollectionC(SizeT maxSize)
      : RCHandleC<CollectionBodyC<DataT> >(*new CollectionBodyC<DataT>(maxSize))
      
    {}
    //: Creat an empty collection.
    // maxSize should be set to maximum number of 
    // elements the collection will contain.
    
    CollectionC(const SArray1dC<DataT> &dat)
      : RCHandleC<CollectionBodyC<DataT> >(*new CollectionBodyC<DataT>(dat))
    {}
    //: Create a collection from an array of data.
    
    CollectionC<DataT> Copy() const
      { return Body().Copy(); }
    //: Create a copy of this collection.
    
    inline
    UIntT Insert(const DataT &dat)
    { return Body().Insert(dat); }
    //: Add a data item to the collection.
    //  NB. This may cause the storage array to 
    // be reallocated which will invalidate any iterators
    // held on the collection.
    
    inline
    UIntT InsertRandom(const DataT &dat)
    { return Body().InsertRandom(dat); }
    //: Add a data item to the collection in a random place.
    //  NB. This may cause the storage array to 
    // be reallocated which will invalidate any iterators
    // held on the collection.

    void operator+=(const DataT &dat)
      { Body().Insert(dat); }
    //: Add data item to the collection.
    //  NB. This may cause the storage array to 
    // be reallocated which will invalidate any iterators
    // held on the collection.
    
    DataT Pick()
    { return Body().Pick(); }
    //: Pick a random item from the collection.
    // the element will be removed from the set.
    // It is the users responsiblity to ensure the
    // set is not empty when this method is called.
    // See 'IsEmpty()'
    
    CollectionC<DataT> Shuffle() const
    { return Body().Shuffle(); }
    //: Create a shuffled version of this collection.
    
    void ShuffleIP()
      { Body().ShuffleIP(); }
    //: Shuffle collection in place.
    
    void Merge(const CollectionC<DataT> &x)
    { Body().Merge(x); }
    //: Merge collection 'x' into this one.
    
    void Merge(const SArray1dC<DataT> &x)
    { Body().Merge(x); }
    //: Merge of array 'x' into this collection.
    
    inline bool IsEmpty() const
    { return Body().IsEmpty(); }
    //: Test if collection is empty.
    
    void Empty()
    { Body().Empty(); }
    //: Empty the collection of all its contents.
    
    SizeT Size() const
    { return Body().Size(); }
    //: Returns the number of data elements in the collection.
    
    SArray1dC<DataT> Array()
    { return Body().Array(); }
    //: Access data as array.
    // Note: The returned array is a direct access
    // to the internal data structure, no operations
    // that modify the collection should be performed 
    // while its in use. 
    
    const SArray1dC<DataT> Array() const
    { return Body().Array(); }
    //: Access data as array.
    // Note: The returned array is a direct access
    // to the internal data structure, no operations
    // that modify the collection should be performed 
    // while its in use. 
    
    CollectionC<DataT> Split(SizeT ne)
    { return Body().Split(ne); }
    //: Split the collection in two
    // return a random set of 'ne' elements from this one.
    // ne must be smaller than the size of the collection.
    
    CollectionC<DataT> Sample(SizeT ne) const
    { return Body().Sample(ne); }
    //: Take a random sample from the collection.
    // This collection is not modified.  There is no
    // garantee that an element will be picked only once.
    // 'ne' may be bigger than the size of this collection.
    
    DataT &operator[](IndexC ind)
      { return Body().operator[](ind); }
    //: Array style access.
    
    const DataT &operator[](IndexC ind) const
      { return Body().operator[](ind); }
    //: Array style access.
    
    typedef CollectionIterC<DataT> IteratorT;
    //: Type of iterator.

  };

  template<class DataT>
  ostream &operator<<(ostream &s,const CollectionC<DataT> &d) {
    s << d.Array();
    return s;
  }

  template<class DataT>
  istream &operator>>(istream &s,CollectionC<DataT> &d) {
    SArray1dC<DataT> ad;
    s >> ad;
    d = CollectionC<DataT>(ad);
    return s;
  }
  
  template<class DataT>
  CollectionC<DataT> CollectionBodyC<DataT>::Copy() const {
    return CollectionC<DataT>(Array().Copy());
  }
  
  template<class DataT>
  inline
  UIntT CollectionBodyC<DataT>::Insert(const DataT &dat) {
    if(n >= data.Size())
      data = data.Copy(data.Size() * 2); // Double the size of the collection.
    int i = n;
    data[n++] = dat;
    return i;
  } 

  template<class DataT>
  inline
  UIntT CollectionBodyC<DataT>::InsertRandom(const DataT &dat) {
    if(n >= data.Size())
      data = data.Copy(data.Size() * 2); // Double the size of the collection.
    SizeT p = (SizeT)((RealT) Random1() * n);
    if(p > n-1)
      p = n-1; // Incase of rounding errors.
    data[n++] = data[p];
    data[p] = dat;
    return p;
  }
  
  template<class DataT>
  DataT CollectionBodyC<DataT>::Pick() {
    RavlAssert(n != 0);
    SizeT i = (SizeT)((RealT) Random1() * n);
    if(i >= n-1)
      i = n-1; // Incase of rounding errors.
    DataT ret = data[i];
    data[i] = data[--n];
    return ret;
  }

  template<class DataT>
  void CollectionBodyC<DataT>::Merge(const CollectionC<DataT> &x) {
    Merge(x.Array());
  }
  
  template<class DataT>
  void CollectionBodyC<DataT>::Merge(const SArray1dC<DataT> &x) {
    SizeT spair = data.Size() - n;
    if(spair >= x.Size()) { // Is there space in existing array ?
      // Copy in data.
      SArray1dC<DataT> rest(data,spair,n);
      for(BufferAccessIter2C<DataT,DataT> it(x,rest);it;it++)
	it.Data2() = it.Data1();
      n+= x.Size();
      return ;
    }
    data = Array().Join(x);
    n += x.Size();
  }
  
  template<class DataT>
  CollectionC<DataT> CollectionBodyC<DataT>::Split(SizeT ne) {
    RavlAssert(ne <= Size());
    CollectionC<DataT> ret(ne);
    for(SizeT i = 0;i < ne;i++)
      ret.Insert(Pick());
    return ret;
  }
  
  template<class DataT>
  CollectionC<DataT>  CollectionBodyC<DataT>::Shuffle() const {
    CollectionC<DataT> ret(n);
    for(BufferAccessIterC<DataT> it(data);it;it++)
      ret.InsertRandom(*it);
    return ret;
  }

  template<class DataT>
  void CollectionBodyC<DataT>::ShuffleIP() {
    for(BufferAccessIterC<DataT> it(data);it;it++) {
      SizeT p = (SizeT)((RealT) Random1() * n);
      if(p > n-1)
	p = n-1; // Incase of rounding errors.
      DataT tmp = *it;
      *it = data[p];
      data[p] = tmp;
    }
  }
  
  template<class DataT>
  CollectionC<DataT> CollectionBodyC<DataT>::Sample(SizeT ne) const {
    CollectionC<DataT> ret(ne);
    for(SizeT i = 0;i < ne;i++) {
      SizeT p = (SizeT)((RealT) Random1() * n);
      if(p > n-1)
	p = n-1; // Incase of rounding errors.
      ret.Insert(data[p]);
    }
    return ret;
  }

}

#endif
