#ifndef RAVLARRAY2dSQR2ITER2_HEADER
#define RAVLARRAY2dSQR2ITER2_HEADER 1
//////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"

#include "Ravl/Array2d.hh"
#include "Ravl/BfAcc2Iter2.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Iterate through two arrays accessing 2x2 area.
  // The square can be accessed with DataBL,DataBR,DataUL and DataUR
  // which access the following array elements. <p>
  //  TL TR <br>
  //  BL BR <br>
  
  template<class Data1T,class Data2T>
  class Array2dSqr2Iter2C 
    : protected BufferAccess2dIter2C<Data1T,Data2T>
  {
  public:
    Array2dSqr2Iter2C()
      {}
    //: Default constructor.
    
    Array2dSqr2Iter2C(const Array2dC<Data1T> &narray1,const Array2dC<Data2T> &narray2) 
    : array1(narray1),
      array2(narray2)
    { 
      First(); 
    }
    //: Constructor.
    
    bool First() { 
      IndexRangeC nrng1(array1.Range2().Min()+1,array1.Range2().Max());
      IndexRangeC nrng2(array2.Range2().Min()+1,array2.Range2().Max());
      RavlAssert(nrng1.Min() <= nrng1.Max());
      RavlAssert(nrng2.Min() <= nrng2.Max());
      if(!BufferAccess2dIter2C<Data1T,Data2T>::First(array1,nrng1,
						     array2,nrng2))
	return false;
      up1 = &(cit.Data1());
      up2 = &(cit.Data2());
      if(!NextRow()) {
	cit.Invalidate();
	return false;
      }
      return true;
    }
    //: Goto first element in the array.
    
    bool Next() { 
      up1++;
      up2++;
      cit++;
      if(cit)
	return true;
      up1 = &(rit.Data1()[rng1.Min()]);
      up2 = &(rit.Data2()[rng2.Min()]);
      rit++;
      if(!rit)
	return false;
      cit.First(rit.Data1(),rng1,
		rit.Data2(),rng2);
      return false;
    }
    //: Goto next element.
    
    bool IsElm() const
      { return cit.IsElm(); }
    //: Test if iterator is at a valid element.
    
    operator bool() const
      { return cit.IsElm(); }
    //: Test if iterator is at a valid element.
    
    void operator++() 
      { Next(); }
    //: Goto next element.

    void operator++(int) 
      { Next(); }
    //: Goto next element.
    
    Data1T &DataBR1() 
      { return cit.Data1(); }
    //: Access bottom right data element 

    const Data1T &DataBR1() const
      { return cit.Data1(); }
    //: Access bottom right data element 

    Data1T &DataBL1() 
    { return (&(cit.Data1()))[-1]; }
    //: Access bottom left data element 

    const Data1T &DataBL1() const
      { return (&(cit.Data1()))[-1]; }
    //: Access bottom left data element 
    
    Data1T &DataTR1() 
      { return *up1; }
    //: Access upper right data element 
    
    const Data1T &DataTR1() const
      { return *up1; }
    //: Access upper right data element
    
    Data1T &DataTL1() 
      { return up1[-1]; }
    //: Access upper left data element.
    
    const Data1T &DataTL1() const
      { return up1[-1]; }
    //: Access upper left data element
    
    Data2T &DataBR2() 
    { return cit.Data2(); }
    //: Access bottom right data element 

    const Data1T &DataBR2() const
      { return cit.Data2(); }
    //: Access bottom right data element 

    Data2T &DataBL2() 
    { return (&(cit.Data2()))[-1]; }
    //: Access bottom left data element 

    const Data2T &DataBL2() const
      { return (&(cit.Data2()))[-1]; }
    //: Access bottom left data element 
    
    Data2T &DataTR2() 
      { return *up2; }
    //: Access upper right data element 
    
    const Data2T &DataTR2() const
      { return *up2; }
    //: Access upper right data element
    
    Data2T &DataTL2() 
      { return up2[-1]; }
    //: Access upper left data element.
    
    const Data2T &DataTL2() const
      { return up2[-1]; }
    //: Access upper left data element
    
  protected:
    Array2dC<Data1T> array1;
    Array2dC<Data2T> array2;
    Data1T *up1;
    Data2T *up2;
  };
}



#endif
