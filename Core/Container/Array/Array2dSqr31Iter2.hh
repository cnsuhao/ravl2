#ifndef RAVLARRAY2dSQR31ITER2_HEADER
#define RAVLARRAY2dSQR31ITER2_HEADER 1
//////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"

#include "Ravl/Array2d.hh"
#include "Ravl/BfAcc2Iter2.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Iterate through an array accessing 3x3 area.
  // The square can be accessed with DataBL,DataBR etc...
  // which access the following array elements. <p>
  //  TL TM TR <br>
  //  ML MM MR <br>
  //  BL BM BR <br>
  // for the first array.
  
  template<class Data1T,class Data2T>
  class Array2dSqr31Iter2C 
    : protected BufferAccess2dIter2C<Data1T,Data2T>
  {
  public:
    Array2dSqr31Iter2C()
      {}
    //: Default constructor.
    
    Array2dSqr31Iter2C(const Array2dC<Data1T> &narray1,const Array2dC<Data2T> &narray2) 
      : array1(narray1),
      array2(narray2)
    { First(); }
    //: Constructor.
    
    bool First() {
      rng1 = IndexRangeC(array1.Range2().Min()+1,array1.Range2().Max()-1);
      rng2 = array2.Range2();
      rng2.ClipBy(rng1);
      IndexRangeC srng1(array1.Range1().Min()+1,array1.Range2().Max()-1);
      IndexRangeC srng2 = array2.Range1();
      srng2.ClipBy(srng1);
      if(!rit.First(array1,srng1,
		    array2,srng2)) {
	cit.Invalidate();
	return false;
      }
      cit.First(rit.Data1(),rng1,
		rit.Data2(),rng2);
      if(!cit) {
	cit.Invalidate();
	return false;
      }
      up = &((&(rit.Data1()))[-1][rng1.Min()]);
      dn = &((&(rit.Data1()))[ 1][rng1.Min()]);
      return true;
    }
    //: Goto first element in the array.
    
    bool Next() { 
      up++;
      dn++;
      cit++;
      if(cit)
	return true;
      up = &((rit.Data1())[rng1.Min()]);
      dn = &((&(rit.Data1()))[2][rng1.Min()]);
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
    
    Data1T &DataBL1() 
      { return dn[-1]; }
    //: Access bottom left data element 

    const Data1T &DataBL1() const
      { return dn[-1]; }
    //: Access bottom left data element 

    Data1T &DataBM1() 
      { return *dn; }
    //: Access bottom mid data element 

    const Data1T &DataBM1() const
      { return *dn; }
    //: Access bottom mid data element 

    Data1T &DataBR1() 
      { return dn[1]; }
    //: Access bottom right data element 

    const Data1T &DataBR1() const
      { return dn[1]; }
    //: Access bottom right data element 

    Data1T &DataML1() 
      { return (&(cit.Data1()))[-1]; }
    //: Access middle left data element 
    
    const Data1T &DataML1() const
      { return (&(cit.Data1()))[-1]; }
    //: Access middle left data element 
    
    Data1T &DataMM1() 
      { return cit.Data1(); }
    //: Access middle data element 
    
    const Data1T &DataMM1() const
      { return cit.Data1(); }
    //: Access middle data element 
    
    Data1T &DataMR1() 
      { return (&(cit.Data1()))[1]; }
    //: Access middle right data element 
    
    const Data1T &DataMR1() const
      { return (&(cit.Data1()))[1]; }
    //: Access middle right data element 

    Data1T &DataTL1() 
      { return up[-1]; }
    //: Access top left data element.
    
    const Data1T &DataTL1() const
      { return up[-1]; }
    //: Access top left data element

    Data1T &DataTM1() 
      { return *up; }
    //: Access top middle element 
    
    const Data1T &DataTM1() const
      { return *up; }
    //: Access top middle element
    
    Data1T &DataTR1() 
      { return up[1]; }
    //: Access top right data element 
    
    const Data1T &DataTR1() const
      { return up[1]; }
    //: Access top right data element
    
    Data2T &Data2() 
      { return cit.Data2(); }
    //: Access middle data element of second array.
    
    const Data2T &Data2() const
      { return cit.Data2(); }
    //: Access middle data element of second array.
    
  protected:
    Array2dC<Data1T> array1;
    Array2dC<Data2T> array2;
    Data1T *up;
    Data1T *dn;
  };
}



#endif
