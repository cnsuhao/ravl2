// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html

%include "Ravl/Swig/Types.i"
%include typemaps.i

%{
#include "Ravl/Hash.hh"
#include "Ravl/HashIter.hh"
%}

namespace RavlN
{
  template<class K, class T>
  class HashC
  {
  public:
    HashC(UIntT nBins = 23) ;
    //: Create table with nBins.
    // Bin size must be at least 1.
    //!param: nBins - Number of bin to initially put in the table.
    
    bool Lookup(const K &key,T &OUTPUT) const;
    //: Lookup data for key.
    //!param: key - Key value to be used in lookup.
    //!param: data - Place to hold data if lookup is successfull.
    //!return: true if entry is found, and is assigned to 'data'.
    // otherwise 'data' is not modified.
    
    bool Update(const K &key,const T &data);
    //: Update member of hash table, will create new one if it doesn't
    //: exist. 
    // Require's a default constructor & a working assigment operator !!
    //!param: key - Key for element to update.
    //!param: data - Data to update entry with.
    //!returns: true=Member existed already. false=New one was added.
    
    T &Update(const K &key);
    //: Get value, add default if its not there. Return reference anyway.
    //!param: key - Key for element to access.
    //!return: Reference to element in table
    
    bool Insert(const K &key,const T &data);
    //: Default insertion operation, same as Update(K,T);
    //!param: key - Key for element to update.
    //!param: data - Data to update entry with.
    //!returns: true=Member existed already. false=New one was added.
    
    T &Access(const K &key,const T &def = T());
    //: Access key, if it does exists create a new bin with value 'def'
    //!param: key - Key to lookup.
    //!param: def - Default value to assign to entry if it doesn't exist.
    //!return: Reference to the new entry.
    
    T &AccessCopy(const K &key,const T &def = T());
    //: Access key, if it does not exist create a new bin with a copy of value 'def'
    //!param: key - Key to lookup.
    //!param: def - Default value to assign a copy of if entry doesn't exist.
    //!return: Reference to the new entry.
    
    bool Del(const K &key,bool allowResize = true);
    //: Delete member from table.
    //!param: key - Key to remove from table.
    //!param: allowResize - if true allow table resize.
    // Note, if your deleting a large fraction of the entries it is more efficient to set
    // allowResize to false, then to call the Resize() method to rebin entries after. (If
    // your going to add an equive
    
    T Get(const K &key,bool allowResize = true);
    //: Get data element from table, and remove it.
    //!param: key - Element to get from the table.
    
    bool IsElm(const K &key) const;
    //: Is key used in the table ?
    //!param: key - Element to check for in the table.
    //!return: true if element is present in the table, false otherwise.
    
    void Empty(void); 
    //: Remove all items from table.
    
    UIntT Bins(void) const;
    //: Number of bins in the HashTable.
    //!return: Number of bins in the hash table.
    
    void Resize(SizeT newSize);
    //: Resize hash table.
    //!param: newSize - New number of bins for the hashtable.
  };

  template<class K, class T>
  class HashIterC
  {
  public:
    HashIterC();
    // Don't use this if you can help it.
    
    HashIterC(const HashC<K,T> &nTab);
    // Normal constructor.
    
    HashIterC(const HashIterC<K,T> &oth);
    // Copy constructor.

    bool First(void);
    // Goto first item in table.
    
    bool Next(void);
    // Goto next iterm in table.
    // Once this returns false (or IsElm() is false) this 
    // should not be called again.
    
    bool IsElm() const;
    // Pointing to valid element ?
    
    const K &Key(void) const;
    // Key for current item. IsElm() Must be true.
    
    const T &Data(void) const;
    //: Data for current item.IsElm() Must be true.
    
    T &Data(void);
    //: Data for current item.IsElm() Must be true.
    
    bool Del(void);
    //: Delete current item from table, move to next.
    // Returns true if at a valid element.
  };
}

%define HASH_TYPE(name, typeKey, typeVal)

%template(Hash ## name ## C) RavlN::HashC<typeKey, typeVal>; 
%template(Hash ## name ## IterC) RavlN::HashIterC<typeKey, typeVal>;

%enddef

HASH_TYPE(Int64Int64, RavlN::Int64T, RavlN::Int64T)

%define HASH_OBJECT(name, typeKey, typeVal)

%template(Hash ## name ## C) RavlN::HashC<typeKey, typeVal>; 
%template(Hash ## name ## IterC) RavlN::HashIterC<typeKey, typeVal>;

%enddef
