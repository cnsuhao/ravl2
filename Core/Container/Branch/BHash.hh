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
  //: Hash table.
  
  template<class KeyT,class DataT>
  class BHashC {
  public:
    BHashC()
      : entries(0)
    {}
    //: Default constructor.
    
    BHashC(const BHashC<KeyT,DataT> &other);
    //: Copy constructor.
    
    bool Lookup(const KeyT &key,DataT &data);
    //: Lookup 'key' in hash table.
    // If an entry is found its assigned to data and
    // true is returned.
    
    bool Insert(const KeyT &key,const DataT &data);
    //: Associated value 'data' with key 'key'. 
    
  protected:
    SArray1dC<BListC<BHashEntryC<KeyT,DataT> > > table;
    UIntT entries;
    friend class BHashIterC<KeyT,DataT>;
  };

  template<class KeyT,class DataT>
  BHashC<KeyT,DataT>::BHashC(const BHashC<KeyT,DataT> &other) 
    : table(table.Copy()),
      entries(other.entries)
  {}
  
  template<class KeyT,class DataT>
  bool BHashC<KeyT,DataT>::Lookup(const KeyT &key,DataT &data) {
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
  

}

#endif
