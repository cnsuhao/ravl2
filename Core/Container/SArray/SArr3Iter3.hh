#ifndef RAVLSARR3ITER3_HEADER
#define RAVLSARR3ITER3_HEADER 
////////////////////////////////////////////////////////////
//! docentry="Ravl.Core.Arrays.3D"
//! rcsid="$Id$
//! file="amma/Contain/Array/SArray/SArr3Iter3.hh"
//! lib=MSArr1
//! author="Charles Galambos"
//! date="13/11/98"

#include "Ravl/SArray3d.hh"
#include "Ravl/SArr3Iter.hh"

namespace RavlN {
  //! userlevel=Normal
  //: Triple SArray3dC iterator.
  // Triple Simple 3d array iterator.
  
  template<class Data1T,class Data2T, class Data3T>
  class SArray3dIter3C {
  public:
    SArray3dIter3C()
      {}
    //: Default constructor.
    
    SArray3dIter3C(SArray3dC<Data1T> &arr1, SArray3dC<Data2T> &arr2, SArray3dC<Data3T> &arr3);
    //: Constructor.
    
    inline bool IsElm() const
      { return iter1.IsElm() && iter2.IsElm() && iter3.IsElm(); }
    //: At a valid element ?

    operator bool()
      { return iter1.IsElm() && iter2.IsElm() && iter3.IsElm(); }
    //: At a valid element ?
    
    inline void First();
    //: Goto first element in arrays.
    
    inline void Next();
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
    
    inline Data3T &Data3()
      { return iter3.Data(); }
    //: Get data from third array.
    
    inline const Data3T &Data3() const
      { return iter3.Data(); }
    //: Get data from third array.
    
  private:
    SArray3dIterC<Data1T> iter1;
    SArray3dIterC<Data2T> iter2;  
    SArray3dIterC<Data3T> iter3;
  };
  
  ////////////////////////////////////////////////////////////////
  
  template<class Data1T,class Data2T, class Data3T>
  SArray3dIter3C<Data1T,Data2T,Data3T>::SArray3dIter3C( SArray3dC<Data1T> &arr1, SArray3dC<Data2T> &arr2, SArray3dC<Data3T> &arr3)
    : iter1(arr1), 
      iter2(arr2), 
      iter3(arr3)
  {}

  template<class Data1T,class Data2T,class Data3T>
  inline void 
  SArray3dIter3C<Data1T,Data2T, Data3T>::First() {
    iter1.First();
    iter2.First();
    iter3.First();
  }
  
  template<class Data1T,class Data2T,class Data3T>
  inline 
  void 
  SArray3dIter3C<Data1T,Data2T,Data3T>::Next() { 
    iter1.Next();
    iter2.Next();
    iter3.Next();
  }
  
}
#endif
