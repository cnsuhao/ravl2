// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Statistics/Histogram/RealHistogram2d.cc"
//! date="28/04/2002"
//! author="Charles Galambos"

#include "Ravl/RealHistogram2d.hh"
#include "Ravl/SArray2dIter.hh"

namespace RavlN {
  
  //: Create a histogram.
  
  RealHistogram2dC::RealHistogram2dC(const Point2dC &min,const Point2dC &max,const Index2dC &steps) 
    : SArray2dC<UIntC>(steps)
  {
    scale = max - min;
    //cerr << "Diff=" << scale << "\n";
    scale /= Vector2dC(((RealT) steps[0]) - (1e-8),
		       ((RealT) steps[1]) - (1e-8));
    //cerr << "Scale=" << scale << "\n";
    offset = min;
    Reset();
  }
  
  //: Find the total number of votes cast.
  
  UIntT RealHistogram2dC::TotalVotes() const {
    UIntT c = 0;
    for(SArray2dIterC<UIntC> it(*this);it;it++) 
      c += *it;
    return c;
  }
  
  //: Calculate the amount of information represented by the histogram.
  // This is also known as the entropy of the histogram.
  
  RealT RealHistogram2dC::Information() const {
    RealT totalp = 0;
    RealT total = TotalVotes();
    for(SArray2dIterC<UIntC> it(*this);it;it++) {
      RealT prob = (RealT) *it / total;
      totalp += -prob * Log2(prob);
    }
    return totalp;
  }
  
  //: Calculate the energy represented by the original signal.
  
  RealT RealHistogram2dC::Energy() const {
    UIntT total = TotalVotes();
    RealT sum = 0;
    for(SArray2dIterC<UIntC> it(*this);it;it++)
      sum += Pow((RealT) *it / total,2);
    return sum;
  }
  
  ostream &operator<<(ostream &strm,const RealHistogram2dC &hist) {
    strm << hist.Offset() << ' ' << hist.Scale() << ' ' << (const SArray2dC<UIntC> &)(hist);
    return strm;
  }
  
  istream &operator>>(istream &strm,RealHistogram2dC &hist) {
    Point2dC offset;
    Vector2dC scale;
    SArray2dC<UIntC> xhist;
    strm >> offset >> scale >> xhist;
    hist = RealHistogram2dC(offset,scale,xhist);
    return strm;
  }

}
