// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DARRAY1DITER3_HEADER
#define RAVL_DARRAY1DITER3_HEADER 1
//! docentry="Ravl.Core.Misc"
//! lib=RavlCore
//! author="Charles Galambos"
//! rcsid="$Id$"
//! file="Ravl/Core/System/DArray1dIter3.hh"

#include "Ravl/DArray1dIter2.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: Dynamic array iterator.
  
  template<class Data1T,class Data2T,class Data3T>
  class DArray1dIter3C 
    : public DArray1dIter2C<Data1T,Data2T>
  {
  public:
    DArray1dIter3C()
    {}
    //: Default constructor.
    
    DArray1dIter3C(const DArray1dC<Data1T> &narr1,const DArray1dC<Data2T> &narr2,const DArray1dC<Data3T> &narr3)
      : DArray1dIter2C<Data1T,Data2T>(narr1,narr2),
	it3(narr3)
    { First(); }
    //: Constructor.
    
    void First() {
      it1.First();
      it2.First();
      it3.First();
    }
    //: Goto first element in the array.
    
    Data3T &Data3()
    { return it3.Data(); }
    //: Access data.
    
    const Data3T &Data3() const
    { return it3.Data(); }
    //: Access data.
    
    void Next();
    //: Goto next element.
    // This skips elements that are not present in both arrays.
    
    void operator++(int)
    { Next(); }
    //: Goto next element.
    
    IndexC Index() 
    { return it1.Index(); }
    //: Get index of current element.
    
  protected:
    DArray1dIterC<Data3T> it3;
  };


  template<class Data1T,class Data2T,class Data3T>
  void DArray1dIter3C<Data1T,Data2T,Data3T>::Next() { 
    it1++; 
    it2++;
    it3++;
    while(it1 && it2 && it3) {
      if(it1.Index() == it2.Index() && it1.Index() == it3.Index())
	return ;
      if(it1.Index() < it2.Index()) {
	it1++;
	if(it3.Index() < it2.Index())
	  it3++;
	continue;
      }
      if(it3.Index() < it2.Index()) {
	it3++;
	continue;
      }
      it2++;
    }
    it1.Invalidate();
  }
    

}


#endif
