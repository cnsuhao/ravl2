// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ARRAY2DSQR3ITER_HEADER
#define RAVL_ARRAY2DSQR3ITER_HEADER 1
//////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! docentry="Ravl.Core.Arrays.2D"
//! lib=RavlCore
//! file="Ravl/Core/Container/Array/Array2dSqr3Iter.hh"

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
    { First(); }
    //: Constructor.
    
    bool First() {
      rng = IndexRangeC(array.Range2().Min()+1,array.Range2().Max()-1);
      IndexRangeC srng(array.Range1().Min()+1,array.Range2().Max()-1);
      if(!rit.First(array,srng)) {
	cit.Invalidate();
	return false;
      }
      cit.First(*rit,rng);
      if(!cit) {
	cit.Invalidate();
	return false;
      }
      up = &((&(*rit))[-1][rng.Min()]);
      dn = &((&(*rit))[ 1][rng.Min()]);
      return true;
    }
    //: Goto first element in the array.
    
    bool Next() { 
      up++;
      dn++;
      cit++;
      if(cit)
	return true;
      rit++;
      if(!rit)
	return false;
      up = &((&(*rit))[-1][rng.Min()]);
      dn = &((&(*rit))[ 1][rng.Min()]);
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
    
    DataT &DataBL() 
    { return dn[-1]; }
    //: Access bottom left data element 

    const DataT &DataBL() const
    { return dn[-1]; }
    //: Access bottom left data element 

    DataT &DataBM() 
    { return *dn; }
    //: Access bottom mid data element 

    const DataT &DataBM() const
    { return *dn; }
    //: Access bottom mid data element 

    DataT &DataBR() 
    { return dn[1]; }
    //: Access bottom right data element 

    const DataT &DataBR() const
    { return dn[1]; }
    //: Access bottom right data element 

    DataT &DataML() 
    { return (&(*cit))[-1]; }
    //: Access middle left data element 
    
    const DataT &DataML() const
    { return (&(*cit))[-1]; }
    //: Access middle left data element 
    
    DataT &DataMM() 
    { return *cit; }
    //: Access middle data element 
    
    const DataT &DataMM() const
    { return *cit; }
    //: Access middle data element 
    
    DataT &DataMR() 
    { return (&(*cit))[1]; }
    //: Access middle right data element 
    
    const DataT &DataMR() const
    { return (&(*cit))[1]; }
    //: Access middle right data element 

    DataT &DataTL() 
    { return up[-1]; }
    //: Access top left data element.
    
    const DataT &DataTL() const
    { return up[-1]; }
    //: Access top left data element

    DataT &DataTM() 
    { return *up; }
    //: Access top middle element 
    
    const DataT &DataTM() const
    { return *up; }
    //: Access top middle element
    
    DataT &DataTR() 
    { return up[1]; }
    //: Access top right data element 
    
    const DataT &DataTR() const
    { return up[1]; }
    //: Access top right data element
    
  protected:
    Array2dC<DataT> array;
    DataT *up;
    DataT *dn;
  };
}



#endif
