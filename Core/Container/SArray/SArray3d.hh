#ifndef RAVLSARRAY3D_HEADER
#define RAVLSARRAY3D_HEADER 1
/////////////////////////////////////////////////////////////////////
//! userlevel=Advanced
//! docentry="Ravl.Core.Arrays.3D"
//! rcsid="$Id$"
//! file="amma/Contain/Array/SArray/SArray3d.hh"
//! lib=MSArr1
//! author="Manuel Segovia"
//! date="13/11/98"

#include "Ravl/SArray2d.hh"
#include "Ravl/SArr1Iter.hh"
#include "Ravl/SArr2Iter.hh"
#include "Ravl/Index3d.hh"
#include "Ravl/SArr2Iter2.hh"
#include "Ravl/SArr3Iter.hh"

class istream;
class ostream;

namespace RavlN {
  
  class BinIStreamC;
  class BinOStreamC;
  
  template<class DataC> class SArray3dIterC;
  template<class DataC> class SArray3dRangeIterC;
  
  /
  //: Simple 3 dimentional array
  // This class is from processing real volume arrays. <p>
  // The processing is recommended to be done with iterators:<p>
  // SArray3dIterC, SArray3dIter2C, SArray3dIter3C and SArray3dRangeIterC.
  
  
  template  <class DataC>
  class SArray3dC 
    : private SArray2dC<SizeBufferAccessC <DataC> >
  {
  public:
    typedef DataC ElementT;
    //: Allow function templates to find type of array.
    
    typedef SArray3dIterC<DataC> IteratorT;
    //: Type of iterator.
    
    inline SArray3dC()
      : size3(0)
      {}
    //: Default constructor
    
    SArray3dC(SizeT size1, SizeT size2, SizeT size3);
    //: Constructor
    
    void Fill(const DataC &d);
    //: Fill array with value.
    
    SArray3dC<DataC> Copy();
    //: Deep Copy array.
    
    inline DataC & operator[](const Index3dC & i)
      { return SArray2dC<SizeBufferAccessC<DataC> >::operator[](Index2dC(i.I(),i.J()))[i.K()];  }
    //: access to the item array[(k,j,i)]
    
    inline const DataC & operator[](const Index3dC & i) const
      { return SArray2dC<SizeBufferAccessC<DataC> >::operator[](Index2dC(i.I(),i.J()))[i.K()];  }
    //: return the item array[(k,j,i)]
    
    inline SizeBufferAccessC<DataC> &operator[](const Index2dC & i)
      { return SizeBufferAccessC<DataC>(SArray2dC<SizeBufferAccessC <DataC> >::operator[](i.Row())[i.Col()],size3); }
    //: access to the item array[(i)]
  
    inline const SizeBufferAccessC <DataC> &operator[](const Index2dC & i) const
      { return SizeBufferAccessC<DataC>(SArray2dC<SizeBufferAccessC <DataC> >::operator[](i.Row())[i.Col()],size3); }
    //: access to the item array[(i)]
    
    inline SizeBufferAccessC<SizeBufferAccessC <DataC> > operator[](IndexC i)
    { return SArray2dC<SizeBufferAccessC <DataC> >::operator[](i); }
    //: access to the item array[(i)]
    
    inline const SizeBufferAccessC<SizeBufferAccessC <DataC> > operator[](IndexC i) const
      { return SArray2dC<SizeBufferAccessC <DataC> >::operator[](i); }
    //: return the item array[(i)]
    
    inline SizeT Size1() const
      { return Size(); }
    //: Size in Z axis.

    inline SizeT Size2() const
      { return size2; }
    //: Size in Y axis.
    
    inline SizeT Size3() const
      { return size3; }
    //: Size in X axis.
    
  protected:
    SizeT size3;
    BufferC<DataC> data3d;
    
#ifndef __sgi__  
    friend ostream & operator<< <DataC>(ostream & s,  SArray3dC<DataC> & arr);
    //: prints the array to the ostream s
    
    friend istream & operator>> <DataC>(istream & s, SArray3dC<DataC> & arr);
    //: gets the array for a ostream s
#else
    friend ostream & operator<< (ostream & s,  SArray3dC<DataC> & arr);
    //: prints the array to the ostream s
    
    friend istream & operator>> (istream & s, SArray3dC<DataC> & arr);
    //: gets the array for a ostream s  
#endif
    
    friend class SArray3dIterC<DataC>;
    friend class SArray3dRangeIterC<DataC>;
  }; 
  
  template<class DataC>
  SArray3dC<DataC>::SArray3dC(SizeT size1,SizeT size2, SizeT nsize3)
    : SArray2dC<SizeBufferAccessC<DataC> >(size1, size2),
      size3(nsize3),
      data3d (size1 * size2 * nsize3)
  {
    DataC *at = data3d.ReferenceElm();
    for(SArray2dIterC<SizeBufferAccessC<DataC> > it(*this);
	it.IsElm();
	it.Next(),at += size3)
      it.Data() = BufferAccessC<DataC>(at);
  }
  
  template<class DataC>
  void 
  SArray3dC<DataC>::Fill(const DataC &d) {
    for(SArray2dIterC<SizeBufferAccessC<DataC> > it(*this);
	it.IsElm();
	it.Next())
      it.Data().Fill(d);
  }
  
  template<class DataC>
  SArray3dC<DataC> 
  SArray3dC<DataC>::Copy()  {
    SArray3dC<DataC> newun(Size(),size2, size3); // Allocate new array.
    for(SArray2dIter2C<SizeBufferAccessC<DataC>,BufferAccessC<DataC> > it(*this,newun);
	it.IsElm();
	it.Next())
      it.Data2().CopyFrom(it.Data1());
    return newun;
  }
  
  template <class DataC>
  ostream &
  operator<<(ostream & s, SArray3dC<DataC>  & arr) {
    s << arr.Size1() << " " << arr.Size2() << " " << arr.Size3() << "\n";
    BufferAccessIterC<SizeBufferAccessC<DataC> > it2;
    BufferAccessIterC<DataC> it3;
    for(SArray1dIterC< BufferAccessC<SizeBufferAccessC<DataC> > > it(arr); it.IsElm(); it.Next())
      {
	for(it2 = it.Data(); it2.IsElm(); it2.Next())
	  {
	    for(it3 = it2.Data(); it3.IsElm(); it3.Next())
	      s << it3.Data() << " ";
	    s << "\n";
	  }
	s << "\n\n" ; 
	
      }
    return s;
  }
  
  template <class DataC>
  istream &
  operator>>(istream & s, SArray3dC<DataC> & arr) {
    SizeT size1,size2, size3;
    s >> size1 >> size2 >> size3;
    arr = SArray3dC<DataC>(size1,size2, size3);  
    for(SArray3dIterC<DataC> it(arr);it;it++)
      s >> *it;
    return s;
  }
  
  template<class DataC>
  BinOStreamC &
  operator<<(BinOStreamC & s, const SArray3dC<DataC> & arr) {
    s << arr.Size1() << arr.Size2() << arr.Size3();
    for(SArray3dIterC<DataC> it(arr);it;it++)
      s << *it;
    return s;
  }
  
  template<class DataC>
  BinIStreamC &
  operator>>(BinIStreamC & s, SArray3dC<DataC> & arr) {
    SizeT size1,size2;
    s >> size1 >> size2 >> size3;
    arr = SArray3dC<DataC>(size1,size2,size3);
    for(SArray3dIterC<DataC> it(arr);it;it++)
      s >> *it;
    return s;
  }
}

#endif
