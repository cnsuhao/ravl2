// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BIHASH_HEADER
#define RAVL_BIHASH_HEADER 1
///////////////////////////////////////////////////////////////
//! file="Ravl/Core/Container/Hash/BiHash.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="1/9/96"
//! example=exBiHash.cc
//! docentry="Ravl.Core.Hash Tables"
//! rcsid="$Id$"
//! userlevel=Default

#include "Ravl/Hash.hh"
#include "Ravl/HashIter.hh"

namespace RavlN {

  template<class D1T,class D2T> class BiHashIterC;
  
  //! userlevel=Normal
  //: Bi-directional hash table.
  // This allows a reversable mapping between two hashed items.
  // For quick mapping in both directions.
  // Forward is nominally from D1T to D2T.
  
  template<class D1T,class D2T>
  class BiHashC {
  public:
    BiHashC(UIntT nBins = 23) 
      : hmap1(nBins),
      hmap2(nBins)
      {}
    //: Constructor.
    
    D2T &Map1(const D1T &key)
      { return hmap1[key]; }
    //: Do a lookup on data type 1
    
    D2T &Fwd(const D1T &key)
      { return hmap1[key]; }
    //: Do a lookup on data type 1
    
    bool LookupFwd(const D1T &key,D2T &data)
    { return hmap1.Lookup(key,data); }
    //: Lookup forward.
    // Return true if entry is found and copy 
    // result into 'data'. Otherwise returns
    // false and data is unaffected.
    
    bool IsFwd(const D1T &key) const
      { return hmap1.IsElm(key); }
    //: Do we have a forward mapping.
    
    D1T &Map2(const D2T &key)
      { return hmap2[key]; }
    //: Do a lookup on data type 2;
    
    D1T &Bkw(const D2T &key)
      { return hmap2[key]; }
    //: Do a lookup on data type 2

    bool LookupBkw(const D2T &key,D1T &data)
    { return hmap2.Lookup(key,data); }
    //: Lookup backward.
    // Return true if entry is found and copy 
    // result into 'data'. Otherwise returns
    // false and data is unaffected.
    
    bool IsBkw(const D2T &key) const
      { return hmap2.IsElm(key); }
    //: Do we have a forward mapping.
    
    bool Insert(const D1T &d1,const D2T &d2) {
      hmap1[d1] = d2;
      hmap2[d2] = d1;
      return true;
    }
    //: Insert a mapping into the table.
    // Should check that they are reversable ?
    
    bool DelMap1(const D1T &key) {
      D2T *d2 = hmap1.Lookup(key);
      if(d2 == 0)
	return false;
      bool ret = hmap2.Del(*d2);
      ret &= hmap1.Del(key);
      return ret;
    }
    //: Delete a mapping from the table, using d1 as the key.
    
    bool DelMap2(const D2T &key) {
      D1T *d1 = hmap2.Lookup(key);
      if(d1 == 0)
	return false;
      bool ret = hmap1.Del(*d1);
      ret &= hmap2.Del(key);
      return ret;
    }
    //: Delete a mapping from the table, using d2 as the key.
    
    UIntT Size() const
      { return hmap1.Size(); }
    //: Get number of mappings.
    
  protected:
    HashC<D1T,D2T> hmap1;
    HashC<D2T,D1T> hmap2;
    
    friend class BiHashIterC<D1T,D2T>;
  };
  
  //! userlevel=Normal
  //: Bi-directional hash table iterator
  
  template<class D1T,class D2T>
  class BiHashIterC
    : public HashIterC<D1T,D2T>
  {
  public:
    BiHashIterC(const BiHashC<D1T,D2T> &bihash)
      : HashIterC<D1T,D2T>(bihash.hmap1)
      {}
    
    D1T &Data1()
      { return Key(); }
    //: Access data1.
    
    D2T &Data2()
      { return Data(); }
    //: Access data1.
  };
}
  
#endif
