#ifndef RAVLSARR3ITER2_HEADER
#define RAVLSARR3ITER2_HEADER 1
////////////////////////////////////////////////////////////
//! docentry="Ravl.Core.Arrays.3D"
//! rcsid="$Id$
//! file="amma/Contain/Array/SArray/SArr3Iter2.hh"
//! lib=MSArr1
//! author="Manuel Segovia"
//! date="12/11/98"

#include "Ravl/SArray3d.hh"
#include "Ravl/SArr3Iter.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Duel SArray3dC iterator.
  // Duel Simple 3d array iterator.
  // FIXME:- This could be faster...
  
  template<class Data1T,class Data2T>
  class SArray3dIter2C {
  public:
    SArray3dIter2C();
    //: Default constructor.
    
    SArray3dIter2C(SArray3dC<Data1T> &arr1, SArray3dC<Data2T> &arr2);
    //: Constructor.
    
    inline bool IsElm() const
      { return iter1.IsElm() && iter2.IsElm(); }
    //: At a valid element ?
    
    inline operator bool() const
      { return iter1.IsElm() && iter2.IsElm(); }
    //: At a valid element ?
    
    inline void First();
    //: Goto first element in arrays.
    
    inline void Next();
    //: Goto next element in arrays.
    
    inline void operator++()
      { Next(); }
    //: Goto next element in arrays.
    
    inline void operator++(int)
      { Next(); }
    //: Goto next element in arrays.
    
    inline Data1T &Data1()
      { return iter1.Data(); }
    //: Get data from first array.
    
    inline const Data1T &Data1() const
      { return iter1.Data(); }
    //: Get data from first array.
    
    inline Data2T &Data2()
      { return iter2.Data(); }
    //: Get data from second array.
    
    inline const Data2T &Data2() const
      { return iter2.Data(); }
    //: Get data from second array.
    
  private:
    SArray3dIterC<Data1T> iter1;
    SArray3dIterC<Data2T> iter2;
  };
  
  ////////////////////////////////////////////////////////////////
  
  template<class Data1T,class Data2T>
  SArray3dIter2C<Data1T,Data2T>::SArray3dIter2C()
  {}
  
  template<class Data1T,class Data2T>
  inline void 
  SArray3dIter2C<Data1T,Data2T>::First() {
    iter1.First();
    iter2.First();
  }
  
  template<class Data1T,class Data2T>
  SArray3dIter2C<Data1T,Data2T>::SArray3dIter2C( SArray3dC<Data1T> &arr1, SArray3dC<Data2T> &arr2)
    : iter1(arr1), iter2(arr2)
  {}
  
  template<class Data1T,class Data2T>
  inline 
  void 
  SArray3dIter2C<Data1T,Data2T>::Next() { 
    iter1.Next();
    iter2.Next();
  }
}

#endif
