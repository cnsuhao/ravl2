// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPERMUTATIONITER_HEADER
#define RAVLPERMUTATIONITER_HEADER 1
///////////////////////////////////////////////////////////////
//! userlevel=Normal
//! author="Charles Galambos"
//! date="14/5/96"
//! docentry="Ravl.Math.Sequences"
//! rcsid="$Id$"
//! file="Ravl/Tools/Misc/PermutationIter.hh"
//! lib=RavlMath

#include "Ravl/DList.hh"
#include "Ravl/DLIter.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/Assert.hh"

namespace RavlN {

  //: Iterate permutations.
  // Basicly this generates a list for each position in an
  // array then iterates through all the possible combinations
  // of values.
  
  template<class T>
  class PermutationIterC {
  public:
    PermutationIterC(UIntT nArity = 0)
      : iters(nArity) 
      {}
    //: Constructor.
    
    PermutationIterC(const PermutationIterC &Oth)
      : iters(Oth.iters)
      {}
    //: Copy constructor.
    
    PermutationIterC<T> Copy() const;
    //: Make a copy of this iterator.
    // This copys the iterators but NOT the
    // lists, so any modification made to lists
    // will affect both iterators. <p>
    // This may be changed in the future.
    
    inline DLIterC<T> &Iter(UIntT i)
      { return iters[i]; }
    //: Access a given iterator.
    
    inline void InsLast(UIntT i,const T &Item)
      { iters[i].InsAft(Item); }
    //: Add item to end of list.
    
    inline void InsLast(const T &Item); 
    //: Add to all lists.
    
    inline void InsLast(UIntT i,DListC<T> &Items);
    //: Add items to end of list.
    
    inline void Del(UIntT i);             
    //: Delete element from given list.
    
    bool First(void);
    //: Goto first permutation.
    
    bool Next(void);
    //: Goto Next permutation.
    
    inline bool IsElm(void) const
      { return iters[0].IsElm(); }
    //: Is a valid element ?
    
    inline const T &Data(UIntT i) const;
    //: Get data.
    
    DListC<T> Data(void) const;
    //: Make a list.
    
    void Reset(UIntT nArity);
    //: Clear Iter & change arity.
    
    UIntT Arity(void) const 
      { return iters.Size(); }
    //: Get Arity of iterator.
    
    void Empty(void);
    //: Empty all lists.
    
    DLIterC<T> GetIter(int i) const 
      { return iters[i]; }
    //: Get a copy of iterator.
    
  private:
    SArray1dC<DLIterC<T> > iters;
  };

  /////////////////////////////////////////////
  
  template<class T>
  PermutationIterC<T> 
  PermutationIterC<T>::Copy() const {
    PermutationIterC ret(Arity());
    for(UIntT i = 0;i < Arity();i++)
      ret.iters[i] = iters[i];
  }
  
  template<class T>
  inline void PermutationIterC<T>::InsLast(const T &Item)  {
    for(UIntT i = 0;i < iters.Size();i++)
      iters[i].InsAft(Item);
  }
  
  template<class T>
  void PermutationIterC<T>::InsLast(UIntT i,DListC<T> &items)  {
    for(DLIterC<T> it(items);it.IsElm();it.Next())
      iters[i].InsAft(it.Data());
  }
  
  template<class T>
  inline void PermutationIterC<T>::Del(UIntT i)  {
    RavlAssert(iters[i].IsElm());
    iters[i].Del();
  }
  
  template<class T>
  bool PermutationIterC<T>::First(void)  {
    for(UIntT i = 0;i < iters.Size();i++)
      iters[i].First();
    return iters[0].IsElm();
  }
  
  template<class T>
  bool PermutationIterC<T>::Next(void)  {
    unsigned int i;
    for(i = 0;i < iters.Size();i++) {
      iters[i].Next();
      if(iters[i].IsElm())
	break;
    }
    if(i == iters.Size())
      return false; // The end.
    int k = (int) i;
    for(k--;k >= 0;k--)
      iters[k].First();
    return true;
  }
  
  template<class T>
  inline const T &PermutationIterC<T>::Data(UIntT i) const {
    RavlAssert(iters[i].IsElm());
    return iters[i].Data(); 
  }
  
  template<class T>
  DListC<T> PermutationIterC<T>::Data(void) const  {
    DListC<T> Ret;
    for(UIntT i = 0;i < iters.Size();i++)
      Ret.InsLast(iters[i].Data());
    return Ret;
  }
  
  template<class T>
  void PermutationIterC<T>::Reset(UIntT nArity) {
    if(nArity == iters.Size()) {
      Empty();
      return ;
    }
    iters = SArray1dC<DLIterC<T> >(nArity);
    for(UIntT i = 0;i < iters.Size();i++) {
      DListC<T> tmp; // Initalise lists.
      iters[i] = tmp;
    }
  }

  template<class T>
  void PermutationIterC<T>::Empty(void) {
    for(UIntT i = 0;i < iters.Size();i++) {
      iters[i].First();
      while(iters[i].IsElm())
	iters[i].DelMoveNext();
    }
  }

}
#endif
