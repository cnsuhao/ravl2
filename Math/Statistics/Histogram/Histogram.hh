// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLHISTOGRAM_HEADER
#define RAVLHISTOGRAM_HEADER 1
//////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! example=exHistogram.cc
//! docentry="Ravl.Math.Statistics.Histogram"
//! lib=RavlMath

#include "Ravl/StdMath.hh"
#include "Ravl/Hash.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/IntC.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Histogram with discrete bins. 
  
  template<class KeyT>
  class HistogramC 
    : public HashC<KeyT,UIntC>
  {
  public:
    HistogramC()
      : total(0)
      {}
    //: Default constructor.
    
    UIntT Vote(const KeyT &bin)
      { total++; return ++HashC<KeyT,UIntC>::operator[](bin); }
    //: Vote for 'bin'
    // returns the count of the bin after voting.
    
    UIntT Unvote(const KeyT &bin)
      { total--; return --HashC<KeyT,UIntC>::operator[](bin); }
    //: Unvote for 'bin'
    // returns the count of the bin after unvoting.
    
    UIntT Total() const
      { return total; }
    //: Sum of all the bins.
    
    RealT Information() const;
    //: Calculate the amount of information represented by the histogram.
    
    UIntT SumIntersection(const HistogramC<KeyT> &oth) const;
    //: Return the sum of the intersection between the two histograms.
    
  protected:
    UIntT total; // Total of count in all bins
  };
  
  template<class KeyT>
  RealT HistogramC<KeyT>::Information() const {
    RealT totalp = 0;
    for(HashIterC<KeyT,UIntC> it(*this);it;it++) {
      RealT prob = (RealT) it.Data() / total;
      totalp += -prob * Log2(prob);
    }
    return totalp;
  }
  
  template<class KeyT>
  UIntT HistogramC<KeyT>::SumIntersection(const HistogramC<KeyT> &oth) const {
    UIntT ret = 0;
    if(Size() > oth.Size())
      return oth.SumIntersection(*this); // Turn it around, its faster.
    UIntT v;
    for(HashIterC<KeyT,UIntC> it(*this);it;it++) {
      if(!oth.Lookup(it.Key(),v))
	continue;
      ret += Min(v,it.Data());
    }
    return ret;
  }
}

#endif
