// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_REALRANGE3D_HEADER
#define RAVL_REALRANGE3D_HEADER 1
///////////////////////////////////////////////////////////
//! file="Ravl/Core/Base/RealRange3d.hh"
//! lib=RavlCore
//! author="Radek Marik"
//! docentry="Ravl.Core.Indexing"
//! rcsid="$Id$"
//! date="06/08/1995"
//! userlevel=Default

#include "Ravl/Types.hh"
#include "Ravl/RealRange1d.hh"
#include "Ravl/TFVector.hh"

namespace RavlN {
  
  class IndexRange3dC;
  class BinIStreamC;
  class BinOStreamC;
  
  //! userlevel=Normal
  //: Range of real values in 3D
  
  class RealRange3dC {
  public:
    RealRange3dC()
    {}
    //: Default constructor.
    
    RealRange3dC(RealT iNumber, RealT jNumber, RealT kNumber)
      : is(0, iNumber-1), 
	js(0, jNumber-1),
	ks(0, kNumber-1)
    {}
    //: Constructor.
    
    RealRange3dC(const RealRangeC & iRange,
		 const RealRangeC & jRange,
		 const RealRangeC & kRange);
    //: Constructor.
    
    RealRange3dC(const TFVectorC<RealT,3> &org,const TFVectorC<RealT,3> &end)
      : is(org[0], end[0]), 
	js(org[1], end[1]), 
	ks(org[2], end[2])
    {}
    //: Create an 3d range from corner points.
    
    RealRange3dC(RealT minI, RealT maxI,
		 RealT minJ, RealT maxJ,
		 RealT minK, RealT maxK)
      : is(minI,maxI), 
	js(minJ,maxJ),
	ks(minK,maxK)
    {}
    //: Create rectangle from individual values.
    
    inline TFVectorC<RealT,3> Origin() const
    { return TFVector3(is.Min(),js.Min(),ks.Min()); }
    //: Returns the origin index of the rectangle.
    
    inline TFVectorC<RealT,3>  End() const
    { return TFVector3(is.Max(),js.Max(),ks.Min()); }
    //: Returns the end index of the rectangle.
    
    inline TFVectorC<RealT,3> Center() const
    { return TFVector3(is.Center(),js.Center(),ks.Center()); }
    //: Returns the index which is in the middle of the rectangle
    
    inline RealT MinI() const
    { return is.Min(); }
    //: Returns the min value of I.
    
    inline RealT MinJ() const
    { return js.Min(); }
    //: Returns the min value of J.

    inline RealT MinK() const
    { return ks.Min(); }
    //: Returns the min value of K.
    
    inline RealT MaxI() const
    { return is.Max(); }
    //: Returns the max value of I.
    
    inline RealT MaxJ() const
    { return js.Max(); }
    //: Returns the max value of J.

    inline RealT MaxK() const
    { return ks.Max(); }
    //: Returns the max value of K.
    
    inline RealT &MinI()
    { return is.Min(); }
    //: Returns the min value of I.
    
    inline RealT &MinJ()
    { return js.Min(); }
    //: Returns the min value of J.
    
    inline RealT &MinK()
    { return ks.Min(); }
    //: Returns the min value of K.
    
    inline RealT &MaxI()
    { return is.Max(); }
    //: Returns the max value of I.
    
    inline RealT &MaxJ()
    { return js.Max(); }
    //: Returns the max value of J.

    inline RealT &MaxK()
    { return ks.Max(); }
    //: Returns the max value of K.
    
    inline RealT Is() const
    { return is.Size(); }
    //: The number of i's in the rectangle.

    inline RealT Js() const
    { return js.Size(); }
    //: The number of j's in the rectangle.

    inline RealT Ks() const
    { return ks.Size(); }
    //: The number of k's in the rectangle.
    
    inline RealT Volume() const
    { return (SizeT) Is() * Js() * Ks(); }
    //: Returns the volume of the prism expressed in number of indexs.
    
    inline RealRange3dC Dilate() const 
    { return RealRange3dC(is.Expand(1),js.Expand(1),ks.Expand(1)); }
    //: Returns a new rectangle one index larger on each side.
    
    inline RealRange3dC Erode() const
    { return RealRange3dC(is.Shrink(1),js.Shrink(1),ks.Shrink(1)); }
    //: Removes one index layer on each side.
    
    inline RealRange3dC Expand(RealT n) const
    { return RealRange3dC(is.Expand(n),js.Expand(n),ks.Expand(n)); }
    // Expands the rectangle by adding 'n' indexs on each side.
    
    inline RealRange3dC Shrink(RealT n) const
    { return RealRange3dC(is.Shrink(n),js.Shrink(n),ks.Shrink(n)); }
    // Returns a new rectangle which has layer of the width of 'n' indexs
    // removed.
    
    inline RealRange3dC & ClipBy(const RealRange3dC & r) {
      Range1().ClipBy(r.Range1());
      Range2().ClipBy(r.Range2());
      Range3().ClipBy(r.Range3());
      return *this;
    }
    //: This index range is clipped to contain at most the index range 'r'.

    inline bool Contains(const TFVectorC<RealT,3> & oth) const
    { return Range1().Contains(oth[0]) && Range2().Contains(oth[1]) && Range3().Contains(oth[2]); }
    //: Returns true if this range contains the subrange 'oth'.
    
    inline bool Contains(const RealRange3dC & oth) const
    { return Range1().Contains(oth.Range1()) && Range2().Contains(oth.Range2()) && Range3().Contains(oth.Range3()); }
    //: Returns true if this range contains the subrange 'oth'.
    
    inline const RealRange3dC & operator+=(const TFVectorC<RealT,3> & offset);
    //: Shifts the rectangle to the new position.
    
    inline const RealRange3dC & operator-=(const TFVectorC<RealT,3> & offset);
    //: Shifts the rectangle to the new position.

    inline RealRange3dC operator+(const TFVectorC<RealT,3> & offset) const
    { return RealRange3dC(is + offset[0],js + offset[1],ks + offset[2]); }
    //: Shifts the rectangle to the new position.
    
    inline RealRange3dC operator-(const TFVectorC<RealT,3> & offset) const
    { return RealRange3dC(is - offset[0],js - offset[1],ks - offset[2]); }
    //: Shifts the rectangle to the new position.
    
    inline const RealRangeC & IRange() const
    { return is; }
    //: Access i range.
    
    inline const RealRangeC & JRange() const
    { return js; }
    //: Access j range.

    inline const RealRangeC & KRange() const
    { return ks; }
    //: Access k range.
    
    inline RealRangeC & IRange()
    { return is; }
    //: Access i range.
    
    inline RealRangeC & JRange()
    { return js; }
    //: Access j range.
    
    inline RealRangeC & KRange()
    { return ks; }
    //: Access k range.
    
    inline const RealRangeC & Range1() const
    { return is; }
    //: Access i range.
    
    inline const RealRangeC & Range2() const
    { return js; }
    //: Access j range.

    inline const RealRangeC & Range3() const
    { return ks; }
    //: Access k range.
    
    inline RealRangeC & Range1()
    { return is; }
    //: Access i range.
    
    inline RealRangeC & Range2()
    { return js; }
    //: Access j range.
    
    inline RealRangeC & Range3()
    { return ks; }
    //: Access k range.
    
    inline const RealRange3dC &Involve(const TFVectorC<RealT,3> & index);
    //: Checks and changes, if necessary, the 2 dimensional range
    //: to contain the 'index'.
    
    inline const RealRange3dC &Involve(const RealRange3dC & subRange);
    //: Checks and changes, if necessary, the 2 dimensional range
    //: to contain the 'subRange'.
    
    inline 
    bool IsValid() const 
    { return is.IsValid() && js.IsValid() && ks.IsValid(); }
    // Returns true if this rectangle contains at least one index.

    bool operator==(const RealRange3dC &oth) const
    { return oth.Range1() == Range1() && oth.Range2() == Range2() && oth.Range3() == Range3(); }
    //: Are two ranges equal ?

    bool operator!=(const RealRange3dC &oth) const
    { return oth.Range1() != Range1() || oth.Range2() != Range2() || oth.Range3() != Range3(); }
    //: Are two ranges unequal ?
    
  protected:
    inline const RealRange3dC & Range() const
    { return(*this); }
    
  private:
    RealRangeC is;
    RealRangeC js;
    RealRangeC ks;
  };
  
  IndexRange3dC operator*(const RealRange3dC &realRange,const IndexRange3dC &indexRange);
  //: Multiply a 2d index range by a real 2d range.
  // Multiplying by a real range of 0-1,0-1 is a unit transform.
  
  ostream &operator<<(ostream &s,const RealRange3dC &ir);
  istream &operator>>(istream &s,RealRange3dC &ir);
  
  BinOStreamC &operator<<(BinOStreamC &s,const RealRange3dC &ir);  
  BinIStreamC &operator>>(BinIStreamC &s,RealRange3dC &ir);
  
  ///////////////////////////////////////////////////////
  
  inline const RealRange3dC &RealRange3dC::operator+=(const TFVectorC<RealT,3> & offset) {
    is += offset[0];
    js += offset[1];
    ks += offset[2];
    return *this;
  }
  
  inline const RealRange3dC & RealRange3dC::operator-=(const TFVectorC<RealT,3> & offset) {
    is -= offset[0];
    js -= offset[1];
    ks -= offset[2];
    return *this;
  }
  
  inline const RealRange3dC &RealRange3dC::Involve(const TFVectorC<RealT,3> & index) {
    Range1().Involve(index[0]);
    Range2().Involve(index[1]);
    Range3().Involve(index[2]);
    return *this;
  }

  
  inline const RealRange3dC &RealRange3dC::Involve(const RealRange3dC & subRange) {
    Range1().Involve(subRange.Range1());
    Range2().Involve(subRange.Range2());
    Range3().Involve(subRange.Range3());
    return *this;
  }
  
}
#endif
