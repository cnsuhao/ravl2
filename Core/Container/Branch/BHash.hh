// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BHASH_HEADER
#define RAVL_BHASH_HEADER 1
/////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Branch"
//! lib=RavlCore
//! author="Charles Galambos"
//! file="Ravl/Core/Container/Branch/BHash.hh"

#include "Ravl/BList.hh"
#include "Ravl/BListIter.hh"
#include "Ravl/SArray1d.hh"

namespace RavlN {
  
  template<class KeyT,class DataT> class BHashIterC;
  
  //! userlevel=Develop
  //: Entry in the hash table.
  
  template<class KeyT,class DataT>
  class BHashEntryC {
  public:
    BHashEntryC(const KeyT &nkey,const DataT &ndata)
      : key(nkey),
	data(ndata)
    {}
    //: Constructor.
    
    const KeyT &Key() const
    { return key; }
    //: Access key.
    
    const DataT &Data() const
    { return data; }
    //: Access data.
    
    DataT &Data() 
    { return data; }
    //: Access data.
    
  protected:
    KeyT key;
    DataT data;
  };
  
  //! userlevel=Develop
  //: Branching hash table.
  // This behaves as a non-reference counted object.
  
  template<class KeyT,class DataT>
  class BHashC {
  public:
    BHashC()
      : entries(0)
    {}
    //: Default constructor.

    BHashC(const BHashC<KeyT,DataT> &oth)
      : table(oth.table.Copy()),
	entries(oth.entries)
    {}
    //: Copy constructor.
    
    bool Lookup(const KeyT &key,DataT &data) const;
    //: Lookup 'key' in hash table.
    // If an entry is found its assigned to data and
    // true is returned.
    
    bool Insert(const KeyT &key,const DataT &data);
    //: Associated value 'data' with key 'key'. 
    
    BHashC<KeyT,DataT> Copy() const
    { return *this; }
    //: Copy table.
    // Since this is a small object, its a trivial operation.
    
    const DataT &operator[](const KeyT &key);
    //: Array style access.
    
    bool IsEmpty() const;
    //: Test if hash table is empty.
    
    bool IsElm(const KeyT &key) const;
    //: Is 'key' an key in the table ?
    
    UIntT Size() const
    { return entries; }
    //: Return the number of entries in the table.
    
    DataT *Lookup(const KeyT &key);
    //: Lookup 'key' in hash table.
    // If an entry is found return a pointer to it.
    // otherwise return 0.

    const DataT *Lookup(const KeyT &key) const;
    //: Lookup 'key' in hash table.
    // If an entry is found return a pointer to it.
    // otherwise return 0.
    
  protected:
    SArray1dC<BListC<BHashEntryC<KeyT,DataT> > > table;
    UIntT entries;
    friend class BHashIterC<KeyT,DataT>;
  };
  
  template<class KeyT,class DataT>
  DataT *BHashC<KeyT,DataT>::Lookup(const KeyT &key) {
    if(table.Size() == 0)
      return 0;
    for(BListIterC<BHashEntryC<KeyT,DataT> > it(table[StdHash(key) % table.Size()]);it;it++)
      if(it.Data().Key() == key)
	return &it.Data().Data();
    return 0;
  }

  template<class KeyT,class DataT>
  const DataT *BHashC<KeyT,DataT>::Lookup(const KeyT &key) const {
    if(table.Size() == 0)
      return 0;
    for(BListIterC<BHashEntryC<KeyT,DataT> > it(table[StdHash(key) % table.Size()]);it;it++)
      if(it.Data().Key() == key)
	return &it.Data().Data();
    return 0;
  }
  
  template<class KeyT,class DataT>
  bool BHashC<KeyT,DataT>::IsElm(const KeyT &key) const {
    if(table.Size() == 0)
      return false;
    for(BListIterC<BHashEntryC<KeyT,DataT> > it(table[StdHash(key) % table.Size()]);it;it++) {
      if(it.Data().Key() == key)
	return true;
    }
    return false;
  }
  
  template<class KeyT,class DataT>
  bool BHashC<KeyT,DataT>::Lookup(const KeyT &key,DataT &data) const {
    if(table.Size() == 0)
      return 0;
    for(BListIterC<BHashEntryC<KeyT,DataT> > it(table[StdHash(key) % table.Size()]);it;it++) {
      if(it.Data().Key() == key) {
	data = it.Data().Data();
	return true;
      }
    }
    return false;
  }
  
  template<class KeyT,class DataT>
  bool BHashC<KeyT,DataT>::Insert(const KeyT &key,const DataT &data) {
    if(table.Size() == 0) // Need to initalise the table ?
      table = SArray1dC<BListC<BHashEntryC<KeyT,DataT> > > (7); // How to best choose the inital size ?
    table[StdHash(key) % table.Size()].InsFirst(BHashEntryC<KeyT,DataT>(key,data) );
    return true;
  }
  
  template<class KeyT,class DataT>
  const DataT &BHashC<KeyT,DataT>::operator[](const KeyT &key) {
    if(table.Size() == 0)
      table = SArray1dC<BListC<BHashEntryC<KeyT,DataT> > >(7);
    BListC<BHashEntryC<KeyT,DataT> > &list =  table[StdHash(key) % table.Size()];
    for(BListIterC<BHashEntryC<KeyT,DataT> > it(list);it;it++)
      if(it.Data().Key() == key)
	return it.Data().Data();
    RavlAssertMsg(0,"Attempt to access item with operator[] thats not in the table. ");
    static DataT dummy;
    return dummy;
  }
  
  template<class KeyT,class DataT>
  bool BHashC<KeyT,DataT>::IsEmpty() const {
    for(SArray1dIterC<BListC<BHashEntryC<KeyT,DataT> > > it(table);it;it++)
      if(!it->IsEmpty())
	return false;
    return true;
  }
  
}

#endif
