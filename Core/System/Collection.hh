#ifndef RAVLCOLLECTION_HEADER
#define RAVLCOLLECTION_HEADER 1
//////////////////////////////////////////////////////
//! rcsid=$Id$
//! docentry="Ravl.Core.Collection"

#include "Ravl/SArray1d.hh"
#include "Ravl/Random.hh"
#include "Ravl/RefCounter.hh"

namespace RavlN {
  
  template<class DataT>
  class CollectionC;
  
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
    
    inline
    void Insert(const DataT &dat);
    //: Add a data item to the collection.
    //  NB. This may cause the storage array to 
    // be reallocated which will invalidate any iterators
    // held on the collection.
    
    DataT Pick();
    //: Pick a random item from the collection.
    // the element will be removed from the set.
    // It is the users responsiblity to ensure the
    // set is not empty when this method is called.
    // See 'IsEmpty()'
    
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
    // This collection is not modified.
    
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
    
    inline
    void Insert(const DataT &dat)
    { Body().Insert(dat); }
    //: Add a data item to the collection.
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
  inline
  void CollectionBodyC<DataT>::Insert(const DataT &dat) {
    if(n >= data.Size())
      data = data.Copy(data.Size()); // Double the size of the collection.
    data[n++] = dat;
  } 
  
  //: Pick a random item from the collection.
  // the element will be removed from the set.
  
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
      for(BufferAccessIter2C<DataT,DataT> it(xa,rest);it;it++)
	it.Data2() = it.Data1();
      n+= xa.Size();
      return 0;
    }
    data = Array().Join(xa);
    n += xa.Size();
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
