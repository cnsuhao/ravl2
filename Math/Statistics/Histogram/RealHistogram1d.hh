// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_REALHISTOGRAM1D_HEADER
#define RAVL_REALHISTOGRAM1D_HEADER 1
/////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! docentry="Ravl.Math.Statistics.Histogram"
//! lib=RavlMath
//! file="Ravl/Math/Statistics/Histogram/RealHistogram1d.hh"

#include "Ravl/StdMath.hh"
#include "Ravl/IntC.hh"
#include "Ravl/Array1d.hh"


namespace RavlN {
  class MeanVarianceC;
  
  //! userlevel=Normal
  //: Create a histogram of real values.
  
  class RealHistogram1dC
    : public SArray1dC<UIntC>
  {
  public:
    RealHistogram1dC()
    {}
    //: Default constructor.
    
    RealHistogram1dC(RealT min,RealT max,UIntT steps);
    //: Create a histogram.
    
    RealHistogram1dC(RealT nscale,RealT noffset,const SArray1dC<UIntC> &array)
      : SArray1dC<UIntC>(array),
	scale(nscale),
	offset(noffset)
    {}
    //: Create a histogram from an offset, scale and a SArray1d.
    
    RealT Scale() const
    { return scale; } 
    //: Scaling.
    
    RealT Offset() const
    { return offset; }
    //: Offset used in table.
    
    IndexC Bin(RealT v) const
    { return IndexC((RealT) (v-offset)/scale); }
    //: Get the bin which value 'v' falls into.
    
    RealT MidBin(IndexC bin) const
    { return (RealT) (((RealT) bin + 0.5)* scale) + offset; }
    //: Get the middle of given bin.
    
    void Reset()
    { Fill(0); }
    //: Reset counters in histogram to zero.
    
    void Vote(RealT v)
    { (*this)[Bin(v)]++; }
    //: Vote for value.
    // Note, this will not check that the value is within the histogram.
    // In check mode this will cause an error, in optimised it will corrupt
    // memory.
    
    bool CheckVote(RealT v) { 
      UIntT b = (UIntT) Bin(v).V();
      if(b >= Size())
	return false;
      (*this)[b]++; 
      return true;
    }
    //: Vote for value.
    // Returns false if value is out of range.
    
    UIntT TotalVotes() const;
    //: Find the total number of votes cast.
    // This is computed not stored, and so is relatively slow.
    
    RealT Information() const;
    //: Calculate the amount of information represented by the histogram.
    // This is also known as the entropy of the histogram.
    
    RealT Energy() const;
    //: Calculate the energy represented by the original signal.

    MeanVarianceC MeanVariance() const;
    //: Calculate the mean and variance for the signal.
    
    RealT SmoothedPDF(IntT bin,RealT sigma = 1) const;
    //: Evaluate histogram as a smoothed pdf.
    
  protected:
    RealT scale; // Scale factor.
    RealT offset;   // Offset.
  };
  
  ostream &operator<<(ostream &strm,const RealHistogram1dC &hist);
  //: Write to stream.
  
  istream &operator>>(istream &strm,RealHistogram1dC &hist);
  //: Read from stream.

  BinOStreamC &operator<<(BinOStreamC & s,const RealHistogram1dC &hist);
  //: Binary stream IO.
  
  BinIStreamC &operator<<(BinIStreamC & s,RealHistogram1dC &hist);
  //: Binary stream IO.
  
}
#endif
