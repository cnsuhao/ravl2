#ifndef SARR1RANGEITER_HEADER
#define SARR1RANGEITER_HEADER 1
///////////////////////////////////////////////////
//! docentry="Ravl.Core.Arrays.1D"
//! rcsid="$Id: SArray1dRangeIter.hh 1954 2002-10-30 14:38:15Z vap-james $"
//! file="amma/Contain/Array/SArray/SArray1dRangeIter.hh"
//! lib=MSArr1
//! author="Charles Galambos"
//! date="10/09/98"

#include "Ravl/SArray1d.hh"
#include <assert.h>

//! userlevel=Normal
//: SArray1d iterator.
// Fast simple array iterator limited to a range.

template<class DataT>
class SArray1dRangeIterC {
public:
  SArray1dRangeIterC();
  //: Default constructor.
  
  SArray1dRangeIterC(const SArray1dC<DataT> &arr, SizeT length);
  //: Constructor.
  
  
  inline BooleanT IsElm() const;
  //: At a valid element ?
  
  inline void First();
  //: Goto first element in Range Iterator.
  
  inline void Next();
  //: Goto next element in Range Iterator.

  inline void Origin(SizeT origin);
  //: Define a new origin

  inline BooleanT IsOrigin() const;
  //: At a valid origin

  inline void FirstOrigin();
  //: Send origin to first element of Array.

  inline void NextOrigin();
  //: Send origin to the next element of Array.
  
  inline DataT &Data();
  //: Access data.

  inline const DataT &Data() const;
  //: Const access to data.

  inline DataT &Data1();
  //: Access data.
  // Equivelent to .Data(), for compatability with other iterators.
  
  inline const DataT &Data1() const;
  //: Const access data.
  // Equivelent to .Data(), for compatability with other iterators.
  
  SArray1dC<DataT> &Array();
  //: Access array.
  
  IndexT Index() const;
  //: Get current index.
  // This is a little slow.

  void Invalidate();
  //: Invalidate iterator. Makes IsElm() return False.
  
private:
  SArray1dC<DataT> arr;
  DataT *at;
  DataT *endOfRow;
  DataT *endOfArray;
  SizeT origin;
  SizeT length;
};

///////////////////////////////////////////


template<class DataT>
SArray1dRangeIterC<DataT>::SArray1dRangeIterC()
  : at(0),
    endOfRow(0),
    endOfArray(0)
{}

template<class DataT>
inline 
void 
SArray1dRangeIterC<DataT>::First()
{ 
  if(arr.Size() < 1) { // Check for zero length arrays.
    at = 0;
    endOfRow = 0;
    return ;
  }
  if(origin < arr.N())
    {
      at = &arr[origin]; 
      endOfRow = &(at)[length];
    }
  else
    Invalidate();
}

template<class DataT>
inline 
BooleanT SArray1dRangeIterC<DataT>::IsElm() const 
{ return at != endOfRow; }

template<class DataT>
inline 
void 
SArray1dRangeIterC<DataT>::Next() 
{ 
  assert(at != endOfRow);
  at++; 
}

template<class DataT>
SArray1dRangeIterC<DataT>::SArray1dRangeIterC(const SArray1dC<DataT> &narr, SizeT length_in)
  : arr(narr)
{ 
  length = length_in;
  FirstOrigin(); 
}

template<class DataT>
inline void 
SArray1dRangeIterC<DataT>::Origin(SizeT norigin)
{
  if(arr.Size() < norigin + length) { 
    at = 0;
    endOfRow = 0;
    endOfArray = 0;
    return ;
  }
  origin = norigin;
  First();
}
 

template<class DataT>
inline 
BooleanT SArray1dRangeIterC<DataT>::IsOrigin() const 
{ return endOfRow != endOfArray; }

template<class DataT>
inline 
void 
SArray1dRangeIterC<DataT>::NextOrigin() 
{ 
  assert(endOfRow != endOfArray);
  origin++; 
  First();
}

template<class DataT>
inline 
void 
SArray1dRangeIterC<DataT>::FirstOrigin()
{ 
  if(arr.N() < length) { // Check Range Iterator greater than Array.
    at = 0;
    endOfRow = 0;
    endOfArray = 0;
    return ;
  }
  origin = 0;
  at = &arr[origin]; 
  endOfRow = &(at)[length];
  endOfArray = &(at)[arr.N()+1];
}



template<class DataT>
inline 
DataT &
SArray1dRangeIterC<DataT>::Data() 
{ return *at; }

template<class DataT>
inline 
const DataT &
SArray1dRangeIterC<DataT>::Data() const 
{ return *at; }

template<class DataT>
inline 
DataT &
SArray1dRangeIterC<DataT>::Data1() 
{ return *at; }

template<class DataT>
inline 
const DataT &
SArray1dRangeIterC<DataT>::Data1() const 
{ return *at; }

template<class DataT>
SArray1dC<DataT> &
SArray1dRangeIterC<DataT>::Array() 
{ return arr; }

template<class DataT>
IndexT SArray1dRangeIterC<DataT>::Index() const
{ 
  return (IntT) (at - &arr[0]);
  //return off / sizeof(DataT);
}

template<class DataT>
void 
SArray1dRangeIterC<DataT>::Invalidate()
{ 
  endOfRow = endOfArray;
  at = endOfArray; 
}

#endif
