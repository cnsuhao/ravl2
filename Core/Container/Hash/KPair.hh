#ifndef KPAIR_HEADER
#define KPAIR_HEADER 1
///////////////////////////////////////////////////////////////
//! file="amma/Contain/Hash1d/KPair.hh"
//! lib=Hash1d
//! userlevel=Obsolete
//! author="Charles Galambos"
//! docentry="Ravl.Core.Hash Tables"
//! date="27/10/1996"
//! rcsid="$Id: KPair.hh 4 2001-04-11 12:45:55Z craftit $"

//: Keyed pair.
// Don't use this class, use Tuple2C instead.
// This class will be removed in the near future.

template <class K,class D>
class KeyedPairC {
public:
  inline KeyedPairC() {}
  // Default constructor.
  
  inline KeyedPairC(const K &nKey,const D &nData) 
    : PKey(nKey), PData(nData) {}
  // Construct from two elements.
  
  inline KeyedPairC(const K &nKey) 
    : PKey(nKey) {}
  // Construct from key only.
  
  inline KeyedPairC(const KeyedPairC<K,D> &Oth) 
    : PKey(Oth.PKey), PData(Oth.PData) {}
  // Copy constructor.
  
  inline const K &Key(void) const { return PKey; }
  // Contant access to key.
  
  inline K &Key(void) { return PKey; }
  // Acces key.
  
  inline const D &Data(void) const { return PData; }
  // Constant access to data.
  
  inline D &Data(void) { return PData; }
  // Access data.
  
protected:
  K PKey;
  D PData;
};

#endif
