// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef SUBSAMP2INTL_HEADER
#define SUBSAMP2INTL_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id: SubSamp2Intl.hh 5412 2006-03-15 11:12:35Z ees1wc $"
//! file="amma/Image/VidIO/SubSamp2Intl.hh"
//! lib=RavlImage
//! docentry="Ravl.API.Images.IO"
//! author="Charles Galambos"
//! date="02/12/99"

#include "amma/DP/StreamOp.hh"
#include "amma/Date.hh"
#include "amma/Image.hh"
#include "amma/DP/FrameInfo.hh"
#include "amma/RGBValue.hh"
#include "amma/YUVValue.hh"
#include "amma/VYUValue.hh"
#include "amma/GreyVal.hh"

namespace StdMath {
  
  template<class DataT>
  inline DataT Average(const DataT &d1,const DataT &d2,const DataT &d3,const DataT &d4)
  { return (d1 + d2 + d3 + d4)/4; }
  //: Average of 4 values.
  
  inline
  ByteT Average(const ByteT &d1,const ByteT &d2,const ByteT &d3,const ByteT &d4)
  { return ((IntT) d1 + (IntT) d2 + (IntT) d3 + (IntT) d4)/4; }
  //: Average of 4 values.

  inline
  ByteRGBValueC Average(const ByteRGBValueC &d1,const ByteRGBValueC &d2,
			const ByteRGBValueC &d3,const ByteRGBValueC &d4)
   { 
     return ByteRGBValueC(((IntT) d1.Red() + (IntT) d2.Red() + (IntT) d3.Red() + (IntT) d4.Red())/4,
			  ((IntT) d1.Green() + (IntT) d2.Green() + (IntT) d3.Green() + (IntT) d4.Green())/4,
			  ((IntT) d1.Blue() + (IntT) d2.Blue() + (IntT) d3.Blue() + (IntT) d4.Blue())/4
			  );
   }
  //: Average of 4 values.

  inline
  ByteYUVValueC Average(const ByteYUVValueC &d1,const ByteYUVValueC &d2,
				  const ByteYUVValueC &d3,const ByteYUVValueC &d4)
   { 
     return ByteYUVValueC(((IntT) d1.Y() + (IntT) d2.Y() + (IntT) d3.Y() + (IntT) d4.Y())/4,
			  ((IntT) d1.U() + (IntT) d2.U() + (IntT) d3.U() + (IntT) d4.U())/4,
			  ((IntT) d1.V() + (IntT) d2.V() + (IntT) d3.V() + (IntT) d4.V())/4
			  );
   }
  //: Average of 4 values.
  
  inline
  ByteVYUValueC Average(const ByteVYUValueC &d1,const ByteVYUValueC &d2,
				  const ByteVYUValueC &d3,const ByteVYUValueC &d4)
   { 
     return ByteVYUValueC(((IntT) d1.V() + (IntT) d2.V() + (IntT) d3.V() + (IntT) d4.V())/4,
			  ((IntT) d1.Y() + (IntT) d2.Y() + (IntT) d3.Y() + (IntT) d4.Y())/4,
			  ((IntT) d1.U() + (IntT) d2.U() + (IntT) d3.U() + (IntT) d4.U())/4
			  );
   }
  //: Average of 4 values.
  
}

////////////////////////////////////
//! userlevel=Develop
//: SubSample2Intl base body.

class DPSubSample2IntlBaseBodyC 
  : virtual public DPEntityBodyC
{
public:
  DPSubSample2IntlBaseBodyC(BooleanT ndoSum = FALSE)
    : doSum(ndoSum)
    {}
  //: Constructor
  
  DPSubSample2IntlBaseBodyC(const DPSubSample2IntlBaseBodyC &oth) 
    {}
  //: Copy Constructor
  
protected:
  void Dummy(void);
  //: Dummy func.
  
  BooleanT doSum;
};

////////////////////////////////////
//! userlevel=Normal
//: SubSample2Intl base Handle.
// Cut out every other field, and remove every other pixel.

class DPSubSample2IntlBaseC 
  : virtual public DPEntityC
{
public:
  DPSubSample2IntlBaseC()
    : DPEntityC(TRUE)
    {}
  //: Default constructor.
  
  DPSubSample2IntlBaseC(DPSubSample2IntlBaseBodyC &bod)
    : DPEntityC(bod)
    {}
  //: Body Constructor
  
  DPSubSample2IntlBaseC(const DPSubSample2IntlBaseC &bod)
    : DPEntityC(bod)
    {}
  //: Copy Constructor
  
protected:
  DPSubSample2IntlBaseBodyC &Body() 
    { return dynamic_cast<DPSubSample2IntlBaseBodyC &>(DPEntityC::Body()); }
  //: Access body.
  
  const DPSubSample2IntlBaseBodyC &Body() const 
    { return dynamic_cast<const DPSubSample2IntlBaseBodyC &>(DPEntityC::Body()); }
  //: Access body.
  
public:
    
};

///////////////////////////
//! userlevel=Develop
//: SubSample2Intl body.
// Cut out every other field, and remove every other pixel.
// DataT is the Pixel type.

template<class DataT>
class DPSubSample2IntlBodyC 
  : public DPIStreamOpBodyC<StdDP::FrameC<ImageC<DataT> >,StdDP::FrameC<ImageC<DataT> > >,
    public DPSubSample2IntlBaseBodyC 
{
public:
  DPSubSample2IntlBodyC(BooleanT ndoSum)
    : DPSubSample2IntlBaseBodyC(ndoSum)
  {}
  //: Constructor
  
  DPSubSample2IntlBodyC(const DPSubSample2IntlBodyC<DataT> &oth) 
    : DPIStreamOpBodyC<StdDP::FrameC<ImageC<DataT> >,StdDP::FrameC<ImageC<DataT > > >(oth),
      DPSubSample2IntlBaseBodyC(oth)
  {}
  //: Copy Constructor
  
  StdDP::FrameC<ImageC<DataT> > ProcessImage(const StdDP::FrameC<ImageC<DataT> > &img) {
    
    ImageC<DataT> procIn = img.Data();
    ImageRectangleC prect(procIn.Rectangle());
    if(!(procIn.Rnum() & 1)) {
      prect.RCol()--;
      procIn = ImageC<DataT>(procIn,prect);
    }
    ImageRectangleC orect(prect.Rnum(),((prect.Cnum() + 1)/2)-1);
    ImageC<DataT> ret(orect);

    IndexT atrow = procIn.TRow();
    IndexT brow  = procIn.BRow();    
    IndexT off1 = procIn.LCol();
    IndexT off2 = orect.LCol();
    IntT width   = orect.Cnum();;
  
    for(;atrow <= brow;atrow++) {
      DataT *pin  = &(procIn[atrow][off1]);
      DataT *pout = &(ret[atrow][off2]);
      DataT *pend = &pout[width];
      for(;pout != pend;pout++,pin += 2) 
	*pout = *pin;
    }
    
    return StdDP::FrameC<ImageC<DataT> >(ret,img);
  }

  StdDP::FrameC<ImageC<DataT> > ProcessImageSum(const StdDP::FrameC<ImageC<DataT> > &img1,
						const StdDP::FrameC<ImageC<DataT> > &img2) {
    using namespace StdMath;
    
    ImageC<DataT> procIn1 = img1.Data();
    ImageC<DataT> procIn2 = img2.Data();
    ImageRectangleC prect(procIn1.Rectangle());
    
    ImageRectangleC orect(prect.Rnum(),((prect.Cnum() - 1)/2)-1);
    ImageC<DataT> ret(orect);

    IndexT atrow = procIn1.TRow();
    IndexT brow  = procIn1.BRow();    
    IndexT off1  = procIn1.LCol();
    IndexT off2  = orect.LCol();
    IntT width   = orect.Cnum();;
    
    for(;atrow <= brow;atrow++) {
      DataT *pin1  = &(procIn1[atrow][off1]);
      DataT *pin2  = &(procIn2[atrow][off1]);
      DataT *pout = &(ret[atrow][off2]);
      DataT *pend = &pout[width];
      for(;pout != pend;pout++,pin1++,pin2++)
	*pout = StdMath::Average(*pin1,*(++pin1),*pin2,*(++pin2));
    }
    
    return StdDP::FrameC<ImageC<DataT> >(ret,img1);
  }

  virtual StdDP::FrameC<ImageC<DataT> > Get() 
  { 
    if(doSum)
      return ProcessImageSum(input.Get(),input.Get()); 
    input.Get(); // Discard one field.
    return ProcessImage(input.Get()); 
  }
  //: Process next piece of data.
  
  virtual BooleanT Get(StdDP::FrameC<ImageC<DataT> > &outbuff) {
    StdDP::FrameC<ImageC<DataT> > tmp1;
    StdDP::FrameC<ImageC<DataT> > tmp2;
    if(!input.Get(tmp1)) // Discard one field.
      return false;
    if(!input.Get(tmp2))
      return false;
    if(doSum) 
      outbuff = ProcessImageSum(tmp1,tmp2);
    else {
      tmp1 = StdDP::FrameC<ImageC<DataT> > (); //Make sure memory for unneed frame is free'd
      outbuff = ProcessImage(tmp2);
    }
    return true;
  }
  //: Process some data.
  
  virtual BooleanT IsGetReady() const {
    if(!input.IsValid())
      return false;
    return input.IsGetReady(); 
  }
  
  virtual BooleanT IsGetEOS() const { 
    if(!input.IsValid())
      return true;
    return input.IsGetEOS(); 
  }
  //: Has the End Of Stream been reached ?
  // TRUE = yes.
  
  virtual BodyRefCounterVC &Copy() const 
  { return *new DPSubSample2IntlBodyC(*this); }
  //: Creat a copy of this object.
  
};

////////////////////////////////////
//! userlevel=Normal
//: SubSample2Intl Handle.
// Cut out every other field, and remove every other pixel.
// DataT is the Pixel type.

template<class DataT>
class DPSubSample2IntlC 
  : public DPIStreamOpC<StdDP::FrameC<ImageC<DataT> >,StdDP::FrameC<ImageC<DataT> > >,
    public DPSubSample2IntlBaseC 
{
public:
  DPSubSample2IntlC(BooleanT ndoSum)
    : DPEntityC(*new DPSubSample2IntlBodyC<DataT>(ndoSum))
  {}
  //: Constructor  
};

////////////////////////////////////

#endif
