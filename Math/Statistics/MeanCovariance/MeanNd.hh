#ifndef RAVLMATHMEANND_HEADER
#define RAVLMATHMEANND_HEADER 1
/////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! author="Radek Marik"
//! date="26.05.1994"
//! docentry="Ravl.Math.Statistics.N-D"

#include "Ravl/Vector.hh"

namespace RavlN {
  
  //: Mean in N-D space
  // This class computes the mean of a set of vectors.
  
  class MeanNdC {
  public:
    MeanNdC(SizeT dim = 0)
      : n(0),
      total(dim)
      {}
    //: Constructor.
    
    void Reset();
    //: Reset the counters.
    
    VectorC Mean() const
      { return total/((RealT) n); }
    //: Get the mean vector.
    
    SizeT N() const
      { return n; }
    //: Number of elements in mean.
    
    const MeanNdC &operator+=(const VectorC &vec) {
      if(total.Size() == 0) // 
	total = vec;
      else
	total += vec;
      n++;
      return *this;
    }
    //: Add a vector to set.
    
    const MeanNdC &operator-=(const VectorC &vec) {
      RavlAssert(n > 0);
      total -= vec;
      n--;
      return *this;
    }
    //: Remove a vector from the set.

    const MeanNdC &operator+=(const MeanNdC &m) {
      if(total.Size() == 0) {
	total = m.Total();
	n = m.N();
	return *this;
      }
      total += m.Total();
      n += m.N();
      return *this;
    }
    //: Add another mean to this one.
    
    const MeanNdC &operator-=(const MeanNdC &m) {
      RavlAssert(n >= m.N());
      total -= m.Total();
      n -= m.N();
      return *this;
    }
    //: Add another mean to this one.
    
    void Set(SizeT nn, const VectorC & m) {
      n = nn;
      total = m * nn;
    }
    //: Sets the new content of mean object. 
    // It will represent 'n' points with the mean location 'm'.
    
    VectorC &Total()
      { return total; }
    //: Access total of vectors.
    
    const VectorC &Total() const
      { return total; }
    //: Access total of vectors.
    
  protected:
    SizeT n; // Number of elements.
    VectorC total; // Total value.
  };

  inline
  ostream &operator<<(ostream &s,const MeanNdC &mean) {
    s << mean.N() << ' ' << mean.Total(); 
    return s;    
  }
  
  inline
  istream &operator>>(istream &s,MeanNdC &mean) {
    SizeT n;
    VectorC v;
    s >> n >> v;
    mean.Set(n,v);
    return s;    
  }
  
}

#endif
