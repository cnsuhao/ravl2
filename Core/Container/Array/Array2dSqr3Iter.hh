#ifndef RAVLARRAY2dSQR3ITER_HEADER
#define RAVLARRAY2dSQR3ITER_HEADER 1
//////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"

#include "Ravl/Array2d.hh"
#include "Ravl/BfAcc2Iter.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Iterate through an array accessing 3x3 area.
  // The square can be accessed with DataBL,DataBR etc...
  // which access the following array elements. <p>
  //  TL TM TR <br>
  //  ML MM MR <br>
  //  BL BM BR <br>
  
  template<class DataT>
  class Array2dSqr3IterC 
    : protected BufferAccess2dIterC<DataT>
  {
  public:
    Array2dSqr3IterC()
      {}
    //: Default constructor.
    
    Array2dSqr3IterC(const Array2dC<DataT> &narray) 
    : array(narray)
    { 
      First(); 
    }
    //: Constructor.
    
    bool First() {
      IndexRangeC nrng(array.Range2().Min()+1,array.Range2().Max());
      RavlAssert(nrng.Min() <= nrng.Max());
      if(!BufferAccess2dIterC<DataT>::First(array,nrng))
	return false;
      up = &(*cit);
      if(!NextRow()) {
	cit.Invalidate();
	return false;
      }
      return true;
    }
    //: Goto first element in the array.
    
    bool Next() { 
      up++;
      dn++;
      cit++;
      if(cit)
	return true;
      up = &((*rit)[rng.Min()]);
      dn = &((&(*rit))[2][rng.Min()]);
      rit++;
      if(!rit)
	return false;
      cit.First(rit.Data(),rng);
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
    
    DataT &operator*() 
      { return *cit; }
    //: Access bottom right data element 
    
    const DataT &operator*() const
      { return *cit; }
    //: Access bottom right data element 
    
    DataT &DataBR() 
      { return *cit; }
    //: Access bottom right data element 

    const DataT &DataBR() const
      { return *cit; }
    //: Access bottom right data element 

    DataT &DataBL() 
      { return (&(*cit))[-1]; }
    //: Access bottom left data element 

    const DataT &DataBL() const
      { return (&(*cit))[-1]; }
    //: Access bottom left data element 
    
    DataT &DataTR() 
      { return *up; }
    //: Access upper right data element 
    
    const DataT &DataTR() const
      { return *up; }
    //: Access upper right data element
    
    DataT &DataTL() 
      { return up[-1]; }
    //: Access upper left data element.
    
    const DataT &DataTL() const
      { return up[-1]; }
    //: Access upper left data element
    
  protected:
    Array2dC<DataT> array;
    DataT *up;
    DataT *dn;
  };
}



#endif
