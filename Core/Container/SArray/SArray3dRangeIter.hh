#ifndef SARR3RANGEITER_HEADER
#define SARR3RANGEITER_HEADER 1
////////////////////////////////////////////////////////////
//! docentry="Ravl.Core.Arrays.3D"
//! rcsid="$Id$
//! file="amma/Contain/Array/SArray/SArray3dRangeIter.hh"
//! lib=MSArr1
//! author="Manuel Segovia"
//! date="12/11/98"

#include "amma/SArray3d.hh"
#include "amma/SArray1dRangeIter.hh"
#include "amma/SBfAccRangeIter.hh"

//! userlevel=Normal
//: SArray3dC Range iterator limited to a certain cubic region.

template <class DataT> class SArray3dC;

template<class DataT>
class SArray3dRangeIterC {
public:
  SArray3dRangeIterC();
  //: Default constructor.
  
  SArray3dRangeIterC(SArray3dC<DataT> &arr, SizeT dim1, SizeT dim2, SizeT dim3);
  //: Constructor.
  

  inline BooleanT IsElm() const;
  //: At a valid element ?
  
  inline void First();
  //: Goto first element in the range.
  
  inline void Next();
  //: Goto next element in the range.

 
  inline BooleanT IsOrigin() const;
  //: At a valid origin ?

  inline void Origin(SizeT origin1, SizeT origin2, SizeT origin3);
  //: Define a new origin
  
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
  //: Equivalent to .Data(), for compatability with other iterators.
  
  inline const DataT &Data1() const;
  //: Const access to data.
  //: Equivalent to .Data(), for compatability with other iterators.

private:
  SArray1dRangeIterC<SizeBufferAccessC<SizeBufferAccessC<DataT> > > it1;
  SizeBufferAccessRangeIterC<SizeBufferAccessC<DataT> > it2;
  SizeBufferAccessRangeIterC<DataT> it3;
};

////////////////////////////////////////////////////////////////

template<class DataT>
SArray3dRangeIterC<DataT>::SArray3dRangeIterC()
{}

template<class DataT>
inline void 
SArray3dRangeIterC<DataT>::First()
{
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
SArray3dRangeIterC<DataT>::SArray3dRangeIterC(SArray3dC<DataT> &arr, SizeT dim1, SizeT dim2, SizeT dim3)
  : it1(arr, dim1)
{
  if(it1.IsElm())
    {
      SizeBufferAccessRangeIterC<SizeBufferAccessC<DataT> > temp(it1.Data(), dim2);
      it2 = temp;
      if(it2.IsElm())
	{
	  SizeBufferAccessRangeIterC<DataT> temp2(it2.Data(), dim3);
	  it3 = temp2;
	  
	}
    }
}

template<class DataT>
inline void 
SArray3dRangeIterC<DataT>::Origin(SizeT origin1, SizeT origin2, SizeT origin3)
{
  it1.Origin(origin1);
  if(it1.IsOrigin())
    {
      it2 = it1.Data();
      it2.Origin(origin2);
      if(it2.IsElm())
	{
	 it3 = it2.Data();
	 it3.Origin(origin3);
	}
      else
	it3.Invalidate();
    }
  else
    it2.Invalidate();
}
template<class DataT>
inline void 
SArray3dRangeIterC<DataT>::FirstOrigin()
{
  it1.FirstOrigin();
  if(it1.IsElm())
    {it2 = it1.Data();
     it2.FirstOrigin();
     if(it2.IsElm())
       {
	 it3 = it2.Data();
	 it3.FirstOrigin();
       }
     else
       it3.Invalidate();
    }
  else 
    it2.Invalidate();
}
  
template<class DataT>
inline 
BooleanT 
SArray3dRangeIterC<DataT>::IsElm() const
{ return it3.IsElm(); }
  
template<class DataT>
inline 
void 
SArray3dRangeIterC<DataT>::Next()
{ 
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
BooleanT 
SArray3dRangeIterC<DataT>::IsOrigin() const
{ return it3.IsOrigin(); }
  
template<class DataT>
inline 
void 
SArray3dRangeIterC<DataT>::NextOrigin()
{ 
  it3.NextOrigin();
  if(it3.IsOrigin())
    return;
  it2.NextOrigin();
  if(it2.IsOrigin()){
    it3 = it2.Data();
    return;
    }
  it1.NextOrigin();
  if(!it1.IsOrigin())
    return ;
  it2 = it1.Data();
  it3 = it2.Data();
}



  
template<class DataT>
inline DataT &
SArray3dRangeIterC<DataT>::Data()
{ return it3.Data(); }

template<class DataT>
inline 
const DataT &
SArray3dRangeIterC<DataT>::Data() const 
{ return it3.Data(); }

template<class DataT>
inline DataT &
SArray3dRangeIterC<DataT>::Data1()
{ return it3.Data(); }

template<class DataT>
inline 
const DataT &
SArray3dRangeIterC<DataT>::Data1() const 
{ return it3.Data(); }

#endif
