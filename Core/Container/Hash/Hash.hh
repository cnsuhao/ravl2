// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLHASHT_HEADER
#define RAVLHASHT_HEADER 1
///////////////////////////////////////////////////////////////
//! file="Ravl/Core/Container/Hash/Hash.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="1/9/96"
//! docentry="Ravl.Core.Hash Tables"
//! example=WordFreq.cc;exHash.cc
//! rcsid="$Id$"
//! userlevel=Normal

#include "Ravl/SArray1d.hh"
#include "Ravl/InDList.hh"
#include "Ravl/InDLIter.hh"
#include "Ravl/SArr1Iter.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/StdHash.hh"

#include <iostream.h>

#define HASHC_DEBUG 0

#if defined(HASHC_DEBUG) || RAVL_CHECK
#include "Ravl/Assert.hh"
#endif

namespace RavlN {
  
  template<class K,class T> class HashIterC;
  template<class K,class T> class HashC;
  template<class K,class T> class HashElemC;
  
  template<class K,class T> ostream &operator<<(ostream &out,const HashC<K,T> &obj);
  template<class K,class T> istream &operator>>(istream &out,HashC<K,T> &obj);
  

  ///////////////////////////
  //! userlevel=Develop
  //: Base class for table.
  // BIG OBJECT!
  // <p>
  // Use HashART<K,T> in HashAR.hh in prefrence to this, in nearly
  // every case its faster. 
  // <p>
  // The following amma classes can be used as a key for this
  // template:
  // <p>
  //   StringC, Index2dC, Index3dC, IndexNdC,  PixelC, RGBValueC,
  //   RGBValueU16C, ByteRGBValueC, RGBXValueC(Doesn't use X component.)
  // <p>
  // If you want a class added e-mail me.
  
  class HashBaseC {
  public:
    HashBaseC()
      : elements(0)
      {}
    //: Default constructor.

    HashBaseC(UIntT nelements)
      : elements(nelements)
      {}
    //: Constructor.
    
    bool IsEmpty() const
      { return elements == 0; }
    //: Is the table empty ?

    UIntT Size() const 
      { return elements; }
    //: Count number of elements in table.
    
    SizeT NextPrime(SizeT v);
    //: Get the next prime not smaller than v.
    
  protected:
    UIntT elements; // Number of elements in the table.
  };

  
  ///////////////////////////////
  //! userlevel=Normal
  //: General hash table.
  // Type K is the hash key, it mush define a function<p>
  //   unsigned int K::Hash();  which returns a number fairly unique to the key.
  //    or a global function of the form UIntT StdHash(const K &x) which returns the key. <p>
  //   bool K::operator== (const K &Oth);  to test equality. <p>
  
  // !!!!! Update() Require's a default constructor & a working assigment operator !!!!! <p>
  
  // A few things to bare in mind when writing StdHash() functions. <p>
  // 1) Try and use all the bits in the values being hashed. <p>
  // 2) Use quick operations that tend to preserve the number of bits in the value.
  //     ie '+' '^' '-' <p>
  // 3) Try and generate a hash value which uses as many bits as possible,
  //    but no more than the thing your hashing.  i.e. ByteRGBValueC only
  //    uses 21 bits, and so does the default hash value. <p>
  // 4) For best results try and generate a function which distributes key values
  //    evenly over the range of hash values. <p>
  
  template<class K,class T>
  class HashC : public HashBaseC {
  public:
    typedef T ElementT;
    //: Allow function templates to find type of array.
    
    typedef K KeyT;
    //: Allow function templates to find type of index.
    
    typedef HashIterC<K,T> IteratorT;
    //: Type of iterator.
    
    HashC(UIntT nBins = 23) 
      : table((int) nBins) 
      {}
    //: Create table with nBins.
    // Bin size must be at least 1.
    
    HashC(const HashC<K,T> &oth) 
      : HashBaseC(oth.elements),
	table(oth.table.Copy())
      {}
    //: Copy access structure.
    
    HashC(Tuple2C<K,T> *data); 
    //: Initalise from simple array.
    // NB. Array must be terminated by a duplicate of 
    // the first key. (i.e. == must return true between them)
    
    HashC(istream &in);
    //: Recreate from stream.
    
    HashC<K,T> Copy() const;
    //: Make a copy of the table.
    
    inline const T *Lookup(const K &Key) const;
    //: Find data matching key.
    // Do not use, Try Lookup(key,data);
    // Ptr == NULL, if matching key not found.
    
    inline T *Lookup(const K &Key);
    //: Find data matching key.
    // Do not use, Try Lookup(key,data);
    // Ptr == NULL, if matching key not found.
    
    inline bool Lookup(const K &Key,T &data) const;
    //: Lookup data for key.
    // Returns true if entry is found, and is assigned to 'data'.
    
    inline bool Update(const K &Key,const T &Data);
    //: Update member of HashTable, will create new one if it doesn't
    // exist. 
    // Require's a default constructor & a working assigment operator !!
    // Returns: True=Member existed already. False=New one was added.
    
    inline T &Update(const K &Key);
    //: Get value, add default if its not there. Return refrence anyway.
    
    inline T &operator[](const K &Key) 
      { return Update(Key); }
    //: Associative array style interface.
    
    inline const T &operator[](const K &Key) const;
    //: Associative array style of access.
    
    inline bool Insert(const K &Key,const T &Data) 
      { return Update(Key,Data); }
    //: Default insertion operation, same as Update(K,T);
    
    inline T &Access(const K &key,const T &def = T());
    //: Access key, if it does not exist create a new bin with value 'def'
    // Retuns a refrence to the entry.
    
    inline T &AccessCopy(const K &key,const T &def = T());
    //: Access key, if it does not exist create a new bin with a copy of value 'def'
    // Retuns a refrence to the entry.
    
    bool Del(const K &Key,bool allowResize = true);
    //: Delete member from table.
    
    inline T Get(const K &Key,bool allowResize = true);
    //: Get data element from table, and remove it.
    
    inline bool IsElm(const K &Key) const 
      { return (Lookup(Key) != 0); }
    //: Is key used in the table ?
    
    void Empty(void); 
    //: Remove all items from table.
          
    inline UIntT Bins(void) const 
      { return (UIntT) table.Size(); }
    //: Number of bins in the HashTable.
    
    void Resize(SizeT NewSize);
    //: Resize hash table.

    const HashC<K,T> &operator= (const HashC<K,T> &oth) { 
      table = oth.table.Copy(); 
      elements = oth.elements;
      return *this; 
    }
    //: Assign from another hash table.
    
    bool operator==(const HashC<K,T> &oth) const;
    //: Are two hash tables identical ?

    bool operator!=(const HashC<K,T> &oth) const
      { return !operator==(oth); }
    //: Are two hash tables different ?
    
    UIntT Hash() const;
    //: Compute a hash value for the hash table.

    inline void Move(HashC<K,T> &oth);
    //: Move contents of another table into this one.
    // leave other empty. The previous contents of this table are removed.
    
    void AddFrom(HashC<K,T> &oth,bool replace = true);
    //: Add contents of another table into this one.
    // leave other empty.  if replace is false the contents of the 
    // old table are not replace by the new entries. 
    
    void Add(const HashC<K,T> &oth,bool replace = true);
    //: Add contents of another table into this one.
    // if replace is false the contents of the 
    // old table are not replace by the new entries. 
    
    typedef HashElemC<K,T> HashElem;
    typedef IntrDListC<HashElemC<K,T> > HashElemLst;
    typedef IntrDLIterC<HashElemC<K,T> > HashElemIter; // Used in Del.
    // These typedef's control the types of lists used in this class
    // and it's iterator.  
    
  protected:
    inline T &Add(const K &Key,const T &Data);
    // Add member to table.
    // !! Doesn't check if member already exists !!
    
    inline T &Add(const K &Key);
    // Add member created with default constructor.
    // !! Doesn't check if member already exists !!
    
    inline HashElemC<K,T> *LookupHV(const K &Value,UIntT &hashVal) const;
    inline bool Del(HashElemC<K,T> *Elem,bool allowResize = true);
    
  protected:
    HashC(const HashC<K,T> &oth,bool) 
      : HashBaseC(oth.elements),
	table(oth.table)
      {}
    //: Make temporary handle.
    
    HashC(const SArray1dC<HashElemLst >  &tab,UIntT nelements)
      : HashBaseC(nelements),
        table(tab)
      {}
    //: Create new table from an array.
    
#if HASHC_DEBUG
    UIntT Count() const;
    //: Do an actual count of elements in the table.
    // Used in debug only.
#endif
    
    void CheckAdd(void) {
#if HASHC_DEBUG
      RavlAssert(elements == Count());
#endif
    if(++elements > (Bins() << 1))
      Resize(NextPrime(elements << 2));
    }
    //: Need to increase size ?
    
    void CheckDel(bool allowResize = true) {
      elements--;
#if HASHC_DEBUG
      RavlAssert(elements == Count());
#endif
      if(allowResize) {
	if(elements < (Bins() >> 3)
	 && elements >= (7 << 1))
	  Resize(NextPrime(elements >> 1));
      }
    }
    //: Need to decrease size ?
    
    SArray1dC<IntrDListC<HashElemC<K,T> > > table; // Table of lists.

    friend class HashIterC<K,T>;

    //  friend HashIterT<K,T>;
#if !defined(__sgi__) && !defined(VISUAL_CPP)
    friend ostream &operator<< <> (ostream &out,const HashC<K,T> &obj);
#else
    friend ostream &operator<<(ostream &out,const HashC<K,T> &obj);
#endif
  };
  
  ///////////////////////////////////////
  //! userlevel=Develop
  // Element in hash table.
  //  K - Key class.
  //  T - Data class.
  
  template<class K,class T>
  class HashElemC 
    : public DLinkC
  {
  public:
    HashElemC() 
      {}
    //: Default constructor.
    // To keep the compiler happy.
    
    inline HashElemC(istream &in);
    //: Load from stream.
    
    HashElemC(const K &nKey,const T &Data) 
      : Key(nKey), 
      Hold(Data) 
      {}
    //: Constructor.
    
    HashElemC(const K &nKey,UIntT nHashVal,const T &Data) 
      : hashVal(nHashVal), 
        Key(nKey), 
        Hold(Data) 
      {}
    //: Constructor.
    
    const T &Data() const 
      { return Hold; }
    //: Get constant refrence to data.
    
    T &Data() { return Hold; }
    //: Get refrence to data.
    
    T GetData() { return Hold; }
    //: Get copy of data.
    
    const K &GetKey() const { return Key; }
    //: Get value key.
    
    bool operator==(const K &Another) const 
      { return HashIsEqual(Key,Another); }
    //: Does key equal that of this element ?
    
    UIntT GetHashVal() const { return hashVal; }
    //: Get hash value.
    
  protected:
    UIntT hashVal;
    K Key;
    T Hold;
    
    friend class HashC<K,T>;
  };
  
  //////////////////////////////////////////////////
  
  template<class K,class T>
  inline HashElemC<K,T>::HashElemC(istream &in) { 
    in >> Key >> Hold;
    hashVal = StdHash(Key); 
  }

  template<class K,class T>
  ostream &operator<<(ostream &out,const HashElemC<K,T> &obj) {  
    out << obj.GetKey() << ' ' << obj.Data(); 
    return out;
  }
  
  template<class K,class T>
  istream &operator>>(istream &in,HashElemC<K,T> &obj) { 
    obj = HashElemC<K,T>(in);
    return obj;
  }
  
  
  ///////////////////////////////////////////////////////////////////
  template<class K,class T>
  HashC<K,T>::HashC(Tuple2C<K,T> *data) 
    : table(1)
  {
    K &firstKey = data->Data1();
    Insert(data->Data1(),data->Data2());
    data++;
    for(;data->Data1() != firstKey;data++)
      Insert(data->Data1(),data->Data2());
  }

  template<class K,class T>
  ostream &operator<<(ostream &out,const HashC<K,T> &obj) { 
    out << obj.elements << '\n';
    for(SArray1dIterC<IntrDListC<HashElemC<K,T> > > it(obj.table);it;it++) {
      for(IntrDLIterC<HashElemC<K,T> > place(*it);place;place++)
	out << *place << '\n';
    }
    return out; 
  }
  
  
  template<class K,class T>
  istream &operator>>(istream &in,HashC<K,T> &obj) { 
    obj = HashC<K,T>(in);
    return in;
  }

   template<class K,class T>
   HashC<K,T>::HashC(istream &in)  {
     UIntT size;
     in >> size;
     for(;size > 0;size--) {
       HashElemC<K,T> t(in);
       Add(t.GetKey(),t.Data());
     }
   }
  
  template<class K,class T>
  HashC<K,T> HashC<K,T>::Copy() const  { 
    return *this; 
  }
  
  template<class K,class T>
  inline HashElemC<K,T> *HashC<K,T>::LookupHV(const K &value,UIntT &hashVal) const {
    hashVal = StdHash(value);
    IntrDLIterC<HashElemC<K,T> > place(table[hashVal % table.Size()]);
    for(;place;place++) {
      if(place.Data() == value)
	return (HashElemC<K,T> *) &place.Data();
    }
    return 0;
  }
  
  template<class K,class T>
  inline const T *HashC<K,T>::Lookup(const K &Key) const  {
    UIntT hashVal;
    HashElemC<K,T> *elem = LookupHV(Key,hashVal);
    if(elem == 0) 
      return 0;
    return &elem->Data();
  }
  
  template<class K,class T>
  inline T *HashC<K,T>::Lookup(const K &key)  {
    UIntT hashVal;
    HashElemC<K,T> *elem = LookupHV(key,hashVal);
    if(elem == 0) return 0;
    return &elem->Data();
  }
  
  template<class K,class T>
  inline 
  bool HashC<K,T>::Lookup(const K &Key,T &data) const{
    UIntT hashVal;
    HashElemC<K,T> *elem = LookupHV(Key,hashVal);
    if(elem == 0) 
      return false;
    data = elem->Data();  
    return true;
  }
  
  template<class K,class T>
  inline 
  const T &HashC<K,T>::operator[](const K &key) const {
#if RAVL_CHECK
    const T *data = Lookup(key);
    RavlAssert(data != 0);
    return *data;
#else
    return *Lookup(key);
#endif
  }
  
  
  template<class K,class T>
  inline 
  bool HashC<K,T>::Del(HashElemC<K,T> *elem,bool allowResize) {
    delete elem;
    CheckDel(allowResize);
    return true;
  }
  
  template<class K,class T>
  inline T &HashC<K,T>::Add(const K &key,const T &data)  {
    CheckAdd();
    const UIntT hashVal = StdHash(key);
    const UIntT ind = hashVal % table.Size();
    table[ind].InsFirst(*new HashElem(key,hashVal,data));
    return table[ind].First().Data();
  }
  
  template<class K,class T>
  inline T &HashC<K,T>::Add(const K &key)  {
    CheckAdd();
    const UIntT hashVal = StdHash(key);
    const UIntT ind = hashVal % table.Size();
    table[ind].InsFirst(*new HashElem(key,hashVal,T()));
    return table[ind].First().Data();
  }
  
  template<class K,class T>
  inline bool HashC<K,T>::Update(const K &key,const T &data) {
    UIntT hashVal;
    HashElemC<K,T> *elem = LookupHV(key,hashVal);
    if(elem != 0) {
      elem->Data() = data;
      return true; // There already.
    }
    CheckAdd();
    const UIntT ind = hashVal % table.Size();
    table[ind].InsFirst(*new HashElem(key,hashVal,data));
    return false;  // Had to be added.
  }
  
  template<class K,class T>
  inline T &HashC<K,T>::Access(const K &key,const T &def) {
    UIntT hashVal;
    HashElemC<K,T> *elem = LookupHV(key,hashVal);
    if(elem != 0) 
      return elem->Data(); // Exists already.
    CheckAdd();
    const UIntT ind = hashVal % table.Size();
    HashElem &v = *new HashElem(key,hashVal,def);
    table[ind].InsFirst(v);
    return v.Data(); // Had to be added.  
  }
  
  template<class K,class T>
  inline T &HashC<K,T>::AccessCopy(const K &key,const T &def) {
    UIntT hashVal;
    HashElemC<K,T> *elem = LookupHV(key,hashVal);
    if(elem != 0) 
      return elem->Data(); // Exists already.
    CheckAdd();
    const UIntT ind = hashVal % table.Size();
    HashElem &v = *new HashElem(key,hashVal,StdCopy(def));
    table[ind].InsFirst(v);
    return v.Data(); // Had to be added.  
  }
  
  template<class K,class T>
  inline T &HashC<K,T>::Update(const K &key) {
    UIntT hashVal;
    HashElemC<K,T> *elem = LookupHV(key,hashVal);
    if(elem != 0)
      return elem->Data();
    CheckAdd();
    const UIntT ind = hashVal % table.Size();
    HashElem &v = *new HashElem(key,hashVal,T());
    table[ind].InsFirst(v);
    return v.Data(); 
  }
  
  template<class K,class T>
  bool HashC<K,T>::Del(const K &key,bool allowResize) {
    UIntT hashVal = StdHash(key);
    HashElemIter place(table[hashVal % table.Size()]);
    for(;place;place++) {
      if(place.Data() == key) {
	place.Del();
	CheckDel(allowResize);
	return true;
      }
    }
    return false;
  }
  
  template<class K,class T>
  inline T HashC<K,T>::Get(const K &Key,bool allowResize) {
    UIntT hashVal = StdHash(Key);
    HashElemIter place(table[hashVal % table.Size()]);
    for(;place;place++) {
      if(*place == Key) {
	T ret(place->Data());
	place.Del();
	CheckDel(allowResize);
	return ret;
      }
    }
    return T();
  }
  
  template<class K,class T>
  void HashC<K,T>::Empty(void) {
    table = SArray1dC<HashElemLst>(23);
    elements = 0;
  }
  
  template<class K,class T>
  void HashC<K,T>::Resize(SizeT newSize) {
    if(newSize == table.Size()) return;
#if HASHC_DEBUG
    RavlAssert(newSize > 0);
#endif
    SArray1dC<HashElemLst> newTable(newSize);
    for(SArray1dIterC<HashElemLst> it(table);it;it++) {
      while(!it->IsEmpty()) {
	const UIntT hashVal = it->First().GetHashVal();
	newTable[hashVal % newSize].InsFirst(it->PopFirst());
      }
    }
    table = newTable;
  }

#if HASHC_DEBUG
  template<class K,class T>
  UIntT HashC<K,T>::Count() const {
    UIntT ret = 0;
    for(SArray1dIterC<HashElemLst> it(table);it;it++) 
      ret += it->Size();
    return ret;
  }
#endif

  template<class K,class T>
  bool HashC<K,T>::operator==(const HashC<K,T> &oth) const {
    // Are two hash tables identical ?
    if(&oth == this)
      return true;
    if(elements != oth.elements)
      return false;
    const T *dat;
    for(SArray1dIterC<IntrDListC<HashElemC<K,T> > > it(oth.table);it;it++) {
      for(IntrDLIterC<HashElemC<K,T> > place(*it);place;place++) {
	if((dat = Lookup(place->GetKey())) == 0)
	  return false;
	if(*dat != place->Data())
	  return false;
      }
    }
    return true;
  }
  
  template<class K,class T>
  UIntT HashC<K,T>::Hash() const {
    // Compute a hash value for the hash table.
    UIntT ret = elements + (elements << 17);
    for(SArray1dIterC<IntrDListC<HashElemC<K,T> > > it(table);it;it++) {
      for(IntrDLIterC<HashElemC<K,T> > place(*it);place;place++) {
	UIntT hv = StdHash(place->Data());
	ret += (StdHash(place->GetKey()) + hv) ^ (hv << 11);
      }
    }
    return ret;
  }
  
  template<class K,class T>
  inline 
  void HashC<K,T>::Move(HashC<K,T> &oth) {
    // Get the contents from the other...
    table = oth.table;
    elements = oth.elements;
    // Then set it to empty.
    oth.table = SArray1dC<IntrDListC<HashElemC<K,T> > >();
    oth.elements = 0;
  }
  
  template<class K,class T>
  void HashC<K,T>::AddFrom(HashC<K,T> &oth,bool replace) {
    for(SArray1dIterC<HashElemLst> it(oth.table);it;it++) {
      while(!it->IsEmpty()) {
	HashElemC<K,T> &org =it->First();
	bool found = false;
	// Check the item isn't already in the table.
	IntrDListC<HashElemC<K,T> > &tabEntry = table[org.GetHashVal() % table.Size()]; 
	for(IntrDLIterC<HashElemC<K,T> > place(tabEntry);place;place++) {
	  if(place.Data().GetKey() != org.GetKey()) 
	    continue;
	  if(replace)
	    place.Data().Data() = org.Data();
	  place.Del();
	  found = true;
	  break;
	}
	
	// If its not in, added it.
	if(!found) {
	  tabEntry.InsFirst(it->PopFirst());
	  elements++;
	}
      }
    }
    elements--; // Check add will increment back to proper value.
    CheckAdd();
    oth.elements = 0; // The other table's now empty.
  }
  
  template<class K,class T>
  void HashC<K,T>::Add(const HashC<K,T> &oth,bool replace) {
    for(SArray1dIterC<HashElemLst> it(oth.table);it;it++) {
      for(IntrDLIterC<HashElemC<K,T> > place(*it);place;place++) {
	HashElemC<K,T> &org = *place;
	IntrDListC<HashElemC<K,T> > &tabEntry = table[org.GetHashVal() % table.Size()]; 
	bool found = false;
	for(IntrDLIterC<HashElemC<K,T> > place(tabEntry);place;place++) {
	  if(place.Data().GetKey() != org.GetKey()) 
	    continue;
	  if(replace)
	    place.Data().Data() = org.Data();
	  found = true;
	  break;
	}
	if(!found) { // Add in a copy.
	  tabEntry.InsFirst(*new HashElemC<K,T>(org));
	  elements++;
	}
      }
    }
    elements--; // Check add will increment back to proper value.
    CheckAdd();
  }
  
}

#endif

