// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLHSET_HEADER
#define RAVLHSET_HEADER 1
///////////////////////////////////////////////////////////////
//! file="Ravl/Core/Container/Hash/HSet.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Charles Galambos"
//! date="2/9/1996"
//! docentry="Ravl.Core.Hash Tables"
//! rcsid="$Id$"

#include "Ravl/RCHash.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/Random.hh"
#include "Ravl/Empty.hh"

namespace RavlN {
  template<class K> class HSetIterC;
  
  //: Set of objects.
  // This is based on the templated hash tables.
  // Object must provide the Hash function needed by HashC.
  // see "amma/Hash.hh" <p>
  // BIG OBJECT
  
  template<class T>
  class HSetC {
  public:
    inline HSetC()
      : set(true)
      { assert(set.IsValid()); }
    //: Default constructor.
    
    inline HSetC(istream &in);
    //: stream constructor.
    
    inline HSetC(const HSetC<T> &Oth);
    //: Copy constructor.
    
    HSetC<T> Copy() const;
    //: Make a Shallow copy of the set.
    
    inline bool IsMember(const T &It) const
      { return set.IsElm(It); }
    //: Is 'It' a member of the set ?

    inline bool Contains(const T &It) const
      { return set.IsElm(It); }
    //: Is 'It' a member of the set ?
    
    inline bool operator[](const T &It) const
      { return set.IsElm(It); }
    //: Is 'It' a member of the set ?
    
    inline bool Insert(const T &It)
      { return !set.Insert(It,EmptyC()); }
    //: Insert an element into the set.
    // Ret = False, member already present.
    //       True, new member added.
    
    inline bool Remove(const T &It)
      { return set.Del(It);  }
    //: Remove an item from the set.
    // Ret = True, item removed.
    //       False, item not in set.
    
    inline void Empty()
      { set.Empty(); }
    //: Remove everthing from the set.
    
    inline UIntT Size() const
      { return set.Size(); }
    //: Number of elements in set.
    
    inline HSetC<T> &operator+=(const T &dat);
    //: Add a member to the set.
    
    inline HSetC<T> &operator-=(const T &dat);
    //: Remove a member from the set.
    
    inline HSetC<T> &operator+=(const HSetC<T> &dat);
    //: Add a set to this set.
  
    inline HSetC<T> &operator-=(const HSetC<T> &dat);
    //: Remove a set from this one.
    
    const T &Random() const;
    //: Select a random member of the set.
    // NOTE: It is the user's responsibility to ensure the
    // set it not empty when this function is called.
    
    const T &First() const;
    //: Return the first member of the set.
    // The exact member this returns is undefined,
    // but it is not random. <p>
    // NOTE: It is the user's responsibility to ensure the
    // set it not empty when this function is called.
    
    inline bool IsEmpty() const
      { return set.IsEmpty(); }
    //: Test if the set is empty.
    
    inline HSetC<T> Union(const HSetC<T> &Oth) const;
    //: Get Union of another set with this one. 
    
    inline bool UnionIP(const HSetC<T> &Oth);
    //: Get Union of another set with this one. 
    // Returns true when resulting set in non-empty. 
    
    HSetC<T> Intersect(const HSetC<T> &Oth) const;
    //: Get intersection of another set with this one. 
    
    bool IntersectIP(const HSetC<T> &Oth);
    //: Intersect this set with another (In Place)
    // Returns true when resulting set in non-empty. 
    
    HSetC<T> Disjunction(const HSetC<T> &Oth) const;
    //: Return the items in either set but not in both.
    
    bool DisjunctionIP(const HSetC<T> &Oth);
    //: Return the items in either set but not in both. (In Place).
    // Returns true when resulting set in non-empty. 
    
    bool IsSubset(const HSetC<T> &oth) const;
    //: is oth a subset of this ?
    
    inline bool Contains(const HSetC<T> &ss) const
      { return IsSubset(ss); }
    //: is ss a subset of this one.
    
    bool operator==(const HSetC<T> &oth) const;
    //: Is equal, ie contains all the same members ?
    
    inline
      bool operator!=(const HSetC<T> &oth) const
      { return !operator==(oth); }
    //: Is not equal, ie contains different members ?
    
    // More comming soon.... (Or on request. )
    
    
  private:
    
    RCHashC<T,EmptyC> set;
    
    friend class HSetIterC<T>;
  };
  
  
  ///////////////////////////////
  //: Set Iterator.
  // SMALL OBJECT <p>
  // This creates a refrence to the set, so the set will not be
  // deleted while an iterator refrences it. <p>
  // You should NOT modify the set while using an iterator on it.
  // The actions of such a code are unpredictable.
  
  template<class T>
  class HSetIterC {
  public:
    HSetIterC()
      {}
    //: Default constructor.
    
    HSetIterC(const HSetIterC<T> &oth);
    //: Copy Constructor.
    
    HSetIterC(const HSetC<T> &oth);
    //: Constructor.
    
    inline bool IsElm() const
      { return iter.IsElm(); }
    //: At valid element ?
    
    inline operator bool() const
      { return iter.IsElm(); }
    //: At valid element ?
    
    inline bool First()
      { return iter.First(); }
    //: Goto first element.
    
    inline bool Next()
    { return iter.Next(); }
    //: Goto next element.
    
    inline bool operator++(int)
      { return iter.Next(); }
    //: Goto next element.
    
    inline const T &Data() const
      { return iter.Key(); }
    //: Access data element.
    
    inline const T &operator*() const
      { return iter.Key(); }
    //: Access data element.
    
    inline const T *operator->() const
      { return &iter.Key(); }
    //: Access data element.
    
    inline bool IsInSet(const HSetC<T> &oth) const 
      { return (oth.set == set); }
    //: Is iterator going through set 'oth' ?
    
  private:
    RCHashC<T,EmptyC> set;   // Make a handle to set.
    HashIterC<T,EmptyC> iter;
  };
  
  ///////////////////////////////////////////////
  
  template<class T>
  HSetIterC<T>::HSetIterC(const HSetIterC<T> &oth)
    : set(oth.set),
      iter(oth.iter)
  {}
  
  template<class T>
  HSetIterC<T>::HSetIterC(const HSetC<T> &oth)
    : set(oth.set),
      iter((const_cast<HSetC<T> &>(oth)).set.Data())
  {}
  
  template<class T>
  HSetC<T> 
  HSetC<T>::Copy() const  {
    HSetC<T> ret;
    for(HSetIterC<T> it(const_cast<HSetC<T> &>(*this));
	it.IsElm();it.Next())
      ret.Insert(it.Data());
    return ret;
  }
  
  //////////////////////////////////////////////////////
  
  template<class T>
  inline 
  HSetC<T>::HSetC(istream &in)
    : set(in)
  { assert(set.IsValid()); }

  template<class T>
  inline 
  HSetC<T>::HSetC(const HSetC<T> &Oth) 
    : set(Oth.set) 
  { assert(set.IsValid()); }

  template<class T>
  inline 
  HSetC<T> &HSetC<T>::operator+=(const T &dat) { 
    Insert(dat);
    return *this; 
  }
  
  template<class T>
  inline 
  HSetC<T> &HSetC<T>::operator-=(const T &dat)  {
    Remove(dat);
    return *this;
  }
  
  template<class T>
  inline 
  HSetC<T> &HSetC<T>::operator+=(const HSetC<T> &dat) {
    set.Data().Add(dat.set.Data(),false);
    return *this;
  }
  
  template<class T>
  inline 
  HSetC<T> &HSetC<T>::operator-=(const HSetC<T> &dat) {
    for(HSetIterC<T> it(dat);it.IsElm();it.Next()) 
      Remove(it.Data());
    return *this;
  }
  
  template<class T>
  const T &HSetC<T>::Random() const  {
    // Maybe not the fastest method, but it'll do for now.
    IntT sel = RandomInt() % Size();
    HashIterC<T,EmptyC> it(set.Data());
    for(;sel > 0 && it.IsElm();sel--,it.Next()) ;
    assert(it.IsElm());
    return it.Key();
  }
  
  template<class T>
  const T &HSetC<T>::First() const {
    HashIterC<T,EmptyC> it(set.Data());
    assert(it.IsElm());  
    return it.Key();
  }
  
  template<class T>
  inline 
  HSetC<T> HSetC<T>::Union(const HSetC<T> &oth) const {
    HSetC<T> ret = Copy();
    ret += oth;
    return ret;
  }
  
  template<class T>
  inline 
  bool HSetC<T>::UnionIP(const HSetC<T> &oth) { 
    (*this) += oth;
    return !IsEmpty();
  }
  
  template<class T>
  HSetC<T> HSetC<T>::Intersect(const HSetC<T> &oth) const {
    HSetC<T> ret;
    // Iterate through the smaller set.
    if(Size() < oth.Size()) { 
      for(HSetIterC<T> it(const_cast<HSetC<T> &>(*this));it.IsElm();it.Next()) {
	if(oth.IsMember(it.Data()))
	  ret.Insert(it.Data());
      }
    } else {
      for(HSetIterC<T> it(const_cast<HSetC<T> &>(oth));it.IsElm();it.Next()) {
	if(IsMember(it.Data()))
	  ret.Insert(it.Data());
      }
    }
    return ret;
  }
  
  template<class T>
  bool HSetC<T>::IntersectIP(const HSetC<T> &Oth) {
    for(HSetIterC<T> Iter(*this);Iter.IsElm();Iter.Next()) 
      if(!Oth.IsMember(Iter.Data()))
	Remove(Iter.Data());
    return !IsEmpty();
  }
  
  template<class T>
  HSetC<T> HSetC<T>::Disjunction(const HSetC<T> &Oth) const {
    HSetC<T> ret;
    for(HSetIterC<T> Iter(Oth);Iter;Iter++) {
      if(!IsMember(Iter.Data()))
	ret.Insert(Iter.Data());
    }
    for(HSetIterC<T> Iter2(*this);Iter2;Iter2++) {
      if(!Oth.IsMember(Iter2.Data()))
	ret.Insert(Iter2.Data());
    }
    return ret;
  }
  
  template<class T>
  bool HSetC<T>::DisjunctionIP(const HSetC<T> &Oth) {
    for(HSetIterC<T> Iter(Oth);Iter.IsElm();Iter.Next()) {
      if(IsMember(Iter.Data()))
	Remove(Iter.Data()); // Remove common members.
      else
	Insert(Iter.Data()); // Add those in both.
    }
    return !IsEmpty();
  }

  template<class T>
  bool HSetC<T>::IsSubset(const HSetC<T> &oth) const {
    if(Size() < oth.Size())
      return false; // Can't be its bigger !
    for(HSetIterC<T> it(const_cast<HSetC<T> &>(oth));it.IsElm();it.Next())
      if(!IsMember(it.Data()))
	return false;
    return true;
  }
  
  //: Is equal, ie contains all the same members ?
  
  template<class T>
  bool HSetC<T>::operator==(const HSetC<T> &oth) const {
    if(this == &oth)
      return true; // They're the same set !!
    if(Size() != oth.Size()) // Must be the same size to start with.
      return false;
    for(HSetIterC<T> it(const_cast<HSetC<T> &>(oth));it.IsElm();it.Next())
      if(!IsMember(it.Data()))
	return false;
    return true; // Member can't be duplicated, so must be the same.
  }
  
  template<class T>
  ostream &operator<<(ostream &out,const HSetC<T> &obj) {
    out << obj.Size() << "\n";  
    for(HSetIterC<T> it(const_cast<HSetC<T> &>(obj));it.IsElm();it.Next()) 
      out << it.Data() << "\n"; 
    return out;
  }
  
  template<class T>
  istream &operator>>(istream &in,HSetC<T> &obj) {
    UIntT size;
    in >> size;
    T tmp;
    obj = HSetC<T>();
    for(UIntT i = 0;i < size;i++) {
      in >> tmp;
      obj.Insert(tmp);
    }
    return in;
  }
  
  class BinOStreamC;
  class BinIStreamC;
  
  template<class T>
  BinOStreamC &operator<<(BinOStreamC &out,const HSetC<T> &obj) {
    out << obj.Size();  
    for(HSetIterC<T> it(const_cast<HSetC<T> &>(obj));it.IsElm();it.Next()) 
      out << it.Data();
    return out;
  }
  
  template<class T>
  BinIStreamC &operator>>(BinIStreamC &in,HSetC<T> &obj) {
    UIntT size;
    in >> size;
    T tmp;
    obj = HSetC<T>();
    for(UIntT i = 0;i < size;i++) {
      in >> tmp;
      obj.Insert(tmp);
    }
    return in;
  }
}

#endif
