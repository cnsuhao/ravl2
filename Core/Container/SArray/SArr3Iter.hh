#ifndef RAVLSARR3ITER_HEADER
#define RAVLSARR3ITER_HEADER 1
////////////////////////////////////////////////////////////
//! docentry="Ravl.Core.Arrays.3D"
//! rcsid="$Id$
//! file="amma/Contain/Array/SArray/SArr3Iter.hh"
//! lib=MSArr1
//! author="Manuel Segovia"
//! date="12/11/98"
//! userlevel=Normal

#include "Ravl/SArray3d.hh"
#include "Ravl/SArr1Iter.hh"
#include "Ravl/BfAccIter.hh"

namespace RavlN {
  //: Simple 3d array iterator.
  // A fast iterator to deal with 3d arrays
  
  template <class DataT> class SArray3dC;
  
  template<class DataT>
  class SArray3dIterC {
  public:
    SArray3dIterC()
      {}
    //: Default constructor.
    
    SArray3dIterC(SArray3dC<DataT> &arr);
    //: Constructor.
    
    /*  const SArray3dIterC<DataT> & operator=(SArray3dC<DataT> &arr);
	//: Assignment to an array.*/
    
    inline bool IsElm() const
      { return it3.IsElm(); }  
    //: At a valid element ?
    
    inline operator bool() const
      { return it3.IsElm(); }  
    //: At a valid element ?
    
    inline void First();
    //: Goto first element in array.
    
    inline void Next();
    //: Goto next element in array.
    
    inline void operator++() 
      { Next(); }
    //: Goto next element in array.
    
    inline void operator++(int) 
      { Next(); }
    //: Goto next element in array.
    
    inline void Slice(unsigned int i);
    //: Goto slice number i
    
    inline void NextSameSlice();
    //: goto next element of the current Slice
    
    inline DataT &Data()
      { return it3.Data(); }
    //: Access data.
    
    inline const DataT &Data() const
      { return it3.Data(); }
    //: Const access to data.
    
    inline DataT &operator *()
      { return it3.Data(); }
    //: Access data.
    
    inline const DataT &operator *() const
      { return it3.Data(); }
    //: Const access to data.
    
    inline DataT &Data1()
      { return it3.Data(); }
    //: Access data.
    //: Equivalent to .Data(), for compatability with other iterators.
    
    inline const DataT &Data1() const
      { return it3.Data(); }
    //: Const access to data.
    //: Equivalent to .Data(), for compatability with other iterators.
    
  private:
    SArray1dIterC<SizeBufferAccessC<SizeBufferAccessC<DataT> > > it1;
    BufferAccessIterC<SizeBufferAccessC<DataT> > it2;
    BufferAccessIterC<DataT> it3;
  };
  
  ////////////////////////////////////////////////////////////////
  
  template<class DataT>
  inline void 
  SArray3dIterC<DataT>::First() {
    it1.First();
    if(it1.IsElm())
      {it2 = it1.Data();
      if(it2.IsElm())
	it3 = it2.Data();
      else
	it3.Invalidate();
      }
    else 
      it2.Invalidate();
  }
  
  template<class DataT>
  SArray3dIterC<DataT>::SArray3dIterC(SArray3dC<DataT> &arr)
    : it1(arr)
  {
    if(it1.IsElm()) {
      it2 = it1.Data();
      if(it2.IsElm())
	it3 = it2.Data();
    }
  }
  
  template<class DataT>
  inline 
  void 
  SArray3dIterC<DataT>::Next() { 
    it3.Next();
    if(it3.IsElm())
      return;
    it2.Next();
    if(it2.IsElm()){
      it3 = it2.Data();
      return;
    }
    it1.Next();
    if(!it1.IsElm())
      return ;
    it2 = it1.Data();
    it3 = it2.Data();
  }
  
  template<class DataT>
  inline
  void
  SArray3dIterC<DataT>::Slice(unsigned int i) {
    First();
    for(unsigned int j = 0; j < i; j++) it1.Next();
    if(!it1.IsElm())
      return;
    it2 = it1.Data();
    it3 = it2.Data();
  }
  
  template<class DataT>
  inline
  void
  SArray3dIterC<DataT>::NextSameSlice() {
    it3.Next();
    if(it3.IsElm())
      return;
    it2.Next();
    if(!it2.IsElm())
      return;
    it3 = it2.Data();
  }
  
}
#endif
