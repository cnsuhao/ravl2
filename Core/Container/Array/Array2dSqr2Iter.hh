#ifndef RAVLARRAY2dSQR2ITER_HEADER
#define RAVLARRAY2dSQR2ITER_HEADER 1
//////////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Array2d.hh"
#include "Ravl/BfAcc2Iter.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Iterate through an array accessing 2x2 area.
  // The square can be accessed with DataBL,DataBR,DataUL and DataUR
  // which access the following array elements. <p>
  //  UL UR <br>
  //  BL BR <br>
  
  template<class DataT>
  class Array2dSqr2IterC 
    : protected BufferAccess2dIterC<DataT>
  {
  public:
    Array2dSqr2IterC()
      {}
    //: Default constructor.

    Array2dSqr2IterC(const Array2dC<DataT> &narray)
      : array(narray)
      { First(); }
    //: Default constructor.
    
    bool First() { 
      it = array;
      if(!it.Elm())
	return false;
      up = &it.Data();
      return it.NextRow();
    }
    //: Goto first element in the array.
    
    bool Next() { 
      up++;
      cit++;
      if(cit)
	return true;
      up = &(rit[rng.Min()]);
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
    
    DataT &DataUR() 
      { return *up; }
    //: Access upper right data element 
    
    const DataT &DataUR() const
      { return *up; }
    //: Access upper right data element
    
    DataT &DataUL() 
      { return up[-1]; }
    //: Access upper left data element.
    
    const DataT &DataUL() const
      { return up[-1]; }
    //: Access upper left data element
    
  protected:
    Array2dC<DataT> array;
    DataT *up;
  };
}



#endif
