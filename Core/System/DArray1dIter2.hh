// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DARRAY1DITER2_HEADER
#define RAVL_DARRAY1DITER2_HEADER 1
//! docentry="Ravl.Core.Misc"
//! lib=RavlCore
//! author="Charles Galambos"
//! rcsid="$Id$"

#include "Ravl/DArray1dIter.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: Dynamic array iterator.
  
  template<class Data1T,class Data2T>
  class DArray1dIter2C {
  public:
    DArray1dIter2C()
    {}
    //: Default constructor.
    
    DArray1dIter2C(const DArray1dC<Data1T> &narr1,const DArray1dC<Data2T> &narr2)
      : it1(narr1),
	it2(narr2)
    { First(); }
    //: Constructor.
    
    void First() {
      it1.First();
      it2.First();
    }
    //: Goto first element in the array.
    
    bool IsElm() const
    { return it1.IsElm(); }
    //: At a valid element ?
    
    operator bool() const
    { return it1.IsElm(); }
    //: At a valid element ?

    Data1T &Data1()
    { return it1.Data(); }
    //: Access data.
    
    const Data1T &Data1() const
    { return it1.Data(); }
    //: Access data.

    Data2T &Data2()
    { return it2.Data(); }
    //: Access data.
    
    const Data2T &Data2() const
    { return it2.Data(); }
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
    DArray1dIterC<Data1T> it1;
    DArray1dIterC<Data2T> it2;
  };


  template<class Data1T,class Data2T>
  void DArray1dIter2C<Data1T,Data2T>::Next() { 
    it1++; 
    it2++;
    while(it1 && it2) {
      if(it1.Index() == it2.Index())
	return ;
      if(it1.Index() < it2.Index()) {
	it1++;
	continue;
      }
      it2++;
    }
    it1.Invalidate();
  }
    

}


#endif
