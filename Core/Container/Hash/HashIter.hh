// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLHASHITERT_HEADER
#define RAVLHASHITERT_HEADER 1
///////////////////////////////////////////////////////////////
//! file="Ravl/Core/Container/Hash/HashIter.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Charles Galambos"
//! date="1/9/1996"
//! example=exHash.cc
//! docentry="Ravl.Core.Hash Tables"
//! rcsid="$Id$"

#include "Ravl/Hash.hh"

#define HASHITER_ALLOW_DELETE 0

namespace RavlN {
  
  //: Hash table iterator.
  // This iterator works with both HashC and HashARC. <p>
  // Small object !
  
  template<class K,class T>
  class HashIterC {
  public:
    HashIterC() 
      {}
    // Don't use this if you can help it.
    
    HashIterC(const HashC<K,T> &nTab) 
      : bIt(nTab.table)
      { First(); } 
    // Normal constructor.
    
    HashIterC(const HashIterC<K,T> &Oth) 
      : lIt(Oth.lIt), 
        bIt(Oth.bIt) 
      {} 
    // Copy constructor.
    
    bool First(void)  { 
      bIt.First(); 
      RavlAssert(bIt);
      lIt = *bIt; 
      return CheckValid(); 
    }
    // Goto first item in table.
    
    bool Next(void) { 
      lIt.Next(); 
      return CheckValid(); 
    }
    // Goto next iterm in table.
    // Once this returns false (or IsElm() is false) this 
    // should not be called again.
    
    void operator++(int) { 
      lIt.Next(); 
      CheckValid(); 
    }
    //: Goto next element.
    
    void operator++() { 
      lIt.Next(); 
      CheckValid(); 
    }
    //: Goto next element.
    
    bool IsElm() const 
      { return lIt.IsElm(); }
    // Pointing to valid element ?
    
    operator bool() const
      { return lIt.IsElm(); }
    //: At a valid element ?
    
    const K &Key(void) const 
      { return lIt.Data().GetKey(); }
    // Key for current item. IsElm() Must be true.
    
    const T &Data(void) const 
      { return lIt.Data().Data(); }
    //: Data for current item.IsElm() Must be true.
    
    T &Data(void) 
      { return const_cast<T &>(lIt.Data().Data()); }
    //: Data for current item.IsElm() Must be true.
    
    T &operator*() 
      { return const_cast<T &>(lIt.Data().Data()); }
    //: Access data.
    
    const T &operator*() const
    { return const_cast<T &>(lIt.Data().Data()); }
    //: Access data.
    
#if HASHITER_ALLOW_DELETE
    void Del(void);
    // Delete current item from table, move to next.
    // -> this breaks HashAR, if required I'll
    //     make a new non-constant iterator which can do this.
#endif
    
    HashIterC<K,T> &operator=(const HashC<K,T> &oth) { 
      bIt = oth.table; 
      First(); 
      return *this; 
    }
    // Assign to another table.
    
    HashIterC<K,T> &operator=(const HashIterC<K,T> &oth)  { 
      bIt = oth.bIt; 
      lIt = oth.lIt; 
      return *this; 
    }
    // Assign to another iterator.
    
    //const HashC<K,T> &GetTable() const { return hashTab; }
    // Which table ?
    
  protected:
    bool CheckValid(void);
    
  private:
    IntrDLIterC<HashElemC<K,T> > lIt; // List iterator.
    SArray1dIterC<IntrDListC<HashElemC<K,T> > > bIt;  // Current bin.
  };
  
  //////////////////////////////////
  // Check current iterator is valid, if not
  // move to next valid one.
  
  template<class K,class T>
  bool HashIterC<K,T>::CheckValid(void) {
    while(!lIt.IsElm()) {
      bIt.Next();
      if(!bIt)
	return false;
      lIt = *bIt;
    }
    return true;
  }
  
#if HASHITER_ALLOW_DELETE
  ///////////////////////////////////
  // Delete current item from table, move to next.
  
  template<class K,class T>
  void HashIterC<K,T>::Del(void) {
    HashC<K,T>::HashElemConstIter Oldie(lIt);
    Next();
    Oldie.Del();// Delete old member from list.
  }
#endif
  
}

#endif

