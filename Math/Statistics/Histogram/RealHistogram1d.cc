// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Statistics/Histogram/RealHistogram1d.cc"

#include "Ravl/RealHistogram1d.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/DList.hh"

namespace RavlN {
  
  //: Create a histogram.
  
  RealHistogram1dC::RealHistogram1dC(RealT min,RealT max,UIntT steps) 
    : SArray1dC<UIntC>(steps)
  {
    scale = (max - min) / ((RealT) steps - 1e-8);
    offset = min;
    Reset();
  }
  
  //: Find the total number of votes cast.
  
  UIntT RealHistogram1dC::TotalVotes() const {
    UIntT c = 0;
    for(SArray1dIterC<UIntC> it(*this);it;it++) 
      c += *it;
    return c;
  }
  
  //: Calculate the amount of information represented by the histogram.
  // This is also known as the entropy of the histogram.
  
  RealT RealHistogram1dC::Information() const {
    RealT totalp = 0;
    RealT total = TotalVotes();
    for(SArray1dIterC<UIntC> it(*this);it;it++) {
      RealT prob = (RealT) *it / total;
      totalp += -prob * Log2(prob);
    }
    return totalp;
  }
  
  //: Calculate the energy represented by the original signal.
  
  RealT RealHistogram1dC::Energy() const {
    UIntT total = TotalVotes();
    RealT sum = 0;
    for(SArray1dIterC<UIntC> it(*this);it;it++)
      sum += Pow((RealT) *it / total,2);
    return sum;
  }

  //: Evaluate histogram as a smoothed pdf.
  
  RealT RealHistogram1dC::SmoothedPDF(IntT bin,RealT sigma) const {
    RealT smoothedMeasure = 0.0;
    for(SArray1dIterC<UIntC> it(*this);it;it++) {
      RealT arg = (RealT) (it.Index() - bin) /( sigma * scale);
      smoothedMeasure += (RealT) *it * Exp(-RavlConstN::pi * Sqr(arg));
    }
    return smoothedMeasure / (TotalVotes() * sigma * scale);
  }

  //: Find a list of peaks in the histogram.
  // The peaks are bigger than 'threshold' and larger than all those within +/- width.
  
  DListC<RealT> RealHistogram1dC::Peaks(UIntT width,UIntT threshold) const {
    DListC<RealT> ret;    
    for(SArray1dIterC<UIntC> it(*this);it;it++) {
      UIntT max = *it;
      if(max < threshold)
	continue;
      IndexC at = it.Index();
      IndexRangeC rng(at - (int) width,at + (int) width);
      rng.ClipBy(Range());
      BufferAccessIterC<UIntC> sit(*this,rng);
      for(;sit;sit++)
	if(*sit >= max && (&(*it)) != (&(*sit))) break;
      if(!sit) // Found a peak ?
	ret.InsLast(MidBin(at));
    }
    return ret;
  }


  ostream &operator<<(ostream &strm,const RealHistogram1dC &hist) {
    strm << hist.Offset() << ' ' << hist.Scale() << ' ' << (const SArray1dC<UIntC> &)(hist);
    return strm;
  }
  
  istream &operator>>(istream &strm,RealHistogram1dC &hist) {
    RealT offset,scale;
    SArray1dC<UIntC> xhist;
    strm >> offset >> scale >> xhist;
    hist = RealHistogram1dC(scale,offset,xhist);
    return strm;
  }

}
