// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RCHASHAR_HEADER
#define RCHASHAR_HEADER 1
///////////////////////////////////////////////////
//! userlevel=Normal
//! file="Ravl/Core/Container/Hash/RCHash.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="06/05/98"
//! docentry="Ravl.Core.Hash Tables"
//! example=WordFreq.cc
//! rcsid="$Id$"

#include "Ravl/Hash.hh"
#include "Ravl/RCWrap.hh"

namespace RavlN {
  //: Refrence counted auto-resizing hash table.
  // This is a BIG OBJECT.
  // See HashC for more details. <p>
  // NB. This class requires the standard stream operators to
  // be implemented. ie.  operator<<(ostream &os,xxx) etc...
  
  template<class Key,class Dat >
  class RCHashC 
    : public RCWrapC<HashC<Key,Dat> > 
  {
  public:
    RCHashC(const RCHashC<Key,Dat> &oth)
      : RCWrapC<HashC<Key,Dat> >(oth) {}
    //: Copy constructor.
    
    RCHashC(bool makeBod = true) 
      : RCWrapC<HashC<Key,Dat> > (makeBod,true)
      {}
    //: Default constructor.
    // Will make a body by default.
    
    RCHashC(const RCWrapC<HashC<Key,Dat> > &base)
      : RCWrapC<HashC<Key,Dat> > (base)
      {}
    //: Base constructor.
    
    RCHashC(istream &in)
      : RCWrapC<HashC<Key,Dat> > (in)
      {}
    //: Stream constructor.
    
    Dat &operator[] (const  Key &a) 
      { return Data()[a]; }
    //: Accesss an element.
    // Will create an empty element with the default constructor
    // and return a refrence to it, if it doesn't already exist.
    
    const Dat &operator[] (const  Key &a) const
      { return Data()[a]; }
    //: Accesss an element.
    // Will create an empty element with the default constructor
    // and return a refrence to it, if it doesn't already exist.
    
    inline bool Del(const Key &aKey)
      { return Data().Del(aKey); }
    //: Delete member from table.
    // Returns true if Key was in hash table.
    
    inline bool IsElm(const Key &aKey) const 
      { return Data().IsElm(aKey); }
    //: Is key used in the table.
    
    inline void Move(RCHashC<Key,Dat> &oth)
      { Data().Move(oth.Data()); }
    //: Move contents of another table into this one.
    // leave other empty.
    
    inline bool IsEmpty(void) const
      { return Data().IsEmpty(); }
    //: Is table empty ?
    
    inline void Empty(void)
      { Data().Empty(); }
    //: Empty table
    
    inline bool Insert(const Key &aKey,const Dat &data) 
      { return Data().Update(aKey,data); }
    //: Insert Data with Key.
    // Returns: True=Member existed already. False=New one was added.
    
    inline UIntT Size() const 
      { return Data().Size(); }
    //: Get number of elements in table.
    
    inline Dat *Lookup(const Key &aKey)
      { return Data().Lookup(aKey); }
    //: Look to see if data is present in the table.
    // Do not use, Try Lookup(key,data);
    // If data is present return a ptr to it, othersize
    // return a 0 ptr.
    
    inline const Dat *Lookup(const Key &aKey) const
      { return Data().Lookup(aKey); }
    //: Look to see if data is present in the table.
    // Do not use, Try Lookup(key,data);
    // If data is present return a ptr to it, othersize
    // return a 0 ptr.

    inline bool Lookup(const Key &aKey,Dat &data)
      { return Data().Lookup(aKey,data); }
    //: Lookup data for key.
    // Returns true if entry is found, and is assigned to 'data'.
    
    inline bool Update(const Key &key,const Dat &data)
      { return Data().Update(key,data); }
    //: Update member of HashCable, will create new one if it doesn't exist.
    // OBSOLETE: Use Insert(key,data)
    // Returns: True=Member existed already. False=New one was added.
    
    inline Dat &Update(const Key &key)
      { return Data().Update(key); }
    //: Get value, add default if its not there. Return refrence anyway.
    // OBSOLETE: Use operator[].
    
    inline Dat &Access(const Key &key,const Dat &def = Dat())
      { return Data().Access(key,def); }
    //: Access key, if it does exists create a new bin with value 'def'
    // Retuns a refrence to the new entry.
    
  };

}

#endif
