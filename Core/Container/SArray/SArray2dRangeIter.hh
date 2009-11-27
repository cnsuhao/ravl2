#ifndef SARR2RANGEITER_HEADER
#define SARR2RANGEITER_HEADER 1
////////////////////////////////////////////////////////////
//! docentry="Ravl.Core.Arrays.2D"
//! rcsid="$Id: SArray2dRangeIter.hh 1954 2002-10-30 14:38:15Z vap-james $
//! file="amma/Contain/Array/SArray/SArray2dRangeIter.hh"
//! lib=MSArr1
//! author="Manuel Segovia"
//! date="12/11/98"

#include "amma/SArray2d.hh"
#include "amma/SArray1dRangeIter.hh"
#include "amma/SBfAccRangeIter.hh"

//! userlevel=Normal
//: SArray2RangedC iterator.
// Simple 2d array iterator limited to a smaller rectangular range.

template<class DataT>
class SArray2dRangeIterC {
public:
  SArray2dRangeIterC();
  //: Default constructor.
  
  SArray2dRangeIterC(SArray2dC<DataT> &arr, SizeT dim1, SizeT dim2);
  //: Constructor.
  
//  const SArray2dRangeIterC<DataT> &operator=(SArray2dC<DataT> &arr);
  //: Assignment to an array.
  
  inline BooleanT IsElm() const;
  //: At a valid element ?
  
  inline void First();
  //: Goto first element in range.
  
  inline void Next();
  //: Goto next element in range.

  inline void Origin(SizeT origin1, SizeT origin2);
  //: Define a new origin

  inline BooleanT IsOrigin() const;
  //: At a valid origin ?
  
  inline void FirstOrigin();
  //: Goto first element in array.
  
  inline void NextOrigin();
  //: Goto next element in array.
  
  inline DataT &Data();
  //: Access data.
  
  inline const DataT &Data() const;
  //: Const access to data.
  
  inline DataT &Data1();
  //: Access data.
  // Equivelent to .Data(), for compatability with other iterators.
  
  inline const DataT &Data1() const;
  //: Const access to data.
  // Equivelent to .Data(), for compatability with other iterators.

private:
  SArray1dRangeIterC<SizeBufferAccessC<DataT> > it1;
  SizeBufferAccessRangeIterC<DataT> it2;
};

////////////////////////////////////////////////////////////////

template<class DataT>
SArray2dRangeIterC<DataT>::SArray2dRangeIterC()
{}

template<class DataT>
inline void 
SArray2dRangeIterC<DataT>::First()
{
  it1.First();
  if(it1.IsElm())
    it2 = it1.Data();
  else 
    it2.Invalidate();
}

template<class DataT>
SArray2dRangeIterC<DataT>::SArray2dRangeIterC(SArray2dC<DataT> &arr, SizeT dim1, SizeT dim2)
  : it1(arr, dim1)
{
  if(it1.IsElm())
    {
      SizeBufferAccessRangeIterC<DataT> temp(it1.Data(), dim2);
      it2 = temp;
    }
}

/*template<class DataT>
const SArray2dRangeIterC<DataT> &
SArray2dRangeIterC<DataT>::operator=(SArray2dC<DataT> &arr)
{
  it1 = arr;
  if(!it1.IsElm()) {
    it2.Invalidate();
    return *this;
  }
  it2 = it1.Data();
  return *this;
}*/
  
template<class DataT>
inline 
BooleanT 
SArray2dRangeIterC<DataT>::IsElm() const
{ return it2.IsElm(); }
  
template<class DataT>
inline 
void 
SArray2dRangeIterC<DataT>::Next()
{ 
  it2.Next();
  if(it2.IsElm())
    return;
  it1.Next();
  if(!it1.IsElm())
    return ;
  it2 = it1.Data();
}

template<class DataT>
inline void 
SArray2dRangeIterC<DataT>::FirstOrigin()
{
  it1.FirstOrigin();
  if(it1.IsElm())
    {
      it2 = it1.Data();
      it2.FirstOrigin();
    }
  else 
    it2.Invalidate();
}

template<class DataT>
inline void 
SArray2dRangeIterC<DataT>::Origin(SizeT origin1, SizeT origin2)
{
  it1.Origin(origin1);
  if(it1.IsOrigin())
    {
      it2 = it1.Data;
      it2.Origin(origin2);
    }
  else
    it2.Invalidate();
}

template<class DataT>
inline 
BooleanT 
SArray2dRangeIterC<DataT>::IsOrigin() const
{ return it2.IsOrigin(); }
  
template<class DataT>
inline 
void 
SArray2dRangeIterC<DataT>::NextOrigin()
{ 
  it2.NextOrigin();
  if(it2.IsOrigin())
    return;
  it1.NextOrigin();
  if(!it1.IsOrigin())
    return ;
  it2 = it1.Data();
}

  
template<class DataT>
inline DataT &
SArray2dRangeIterC<DataT>::Data()
{ return it2.Data(); }

template<class DataT>
inline 
const DataT &
SArray2dRangeIterC<DataT>::Data() const 
{ return it2.Data(); }

template<class DataT>
inline DataT &
SArray2dRangeIterC<DataT>::Data1()
{ return it2.Data(); }

template<class DataT>
inline 
const DataT &
SArray2dRangeIterC<DataT>::Data1() const 
{ return it2.Data(); }

#endif
