// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: RealHist1dBinaryIO.cc 2391 2003-02-14 07:36:12Z craftit $"
//! lib=RavlMath
//! file="Ravl/Math/Statistics/Histogram/RealHist1dBinaryIO.cc"

#include "Ravl/RealHistogram1d.hh"
#include "Ravl/BinStream.hh"

namespace RavlN {
  
  BinOStreamC &operator<<(BinOStreamC & strm,const RealHistogram1dC &hist)  {
    strm << hist.Offset() << hist.Scale() << ((const SArray1dC<UIntC> &)hist);
    return strm;
  }
  
  BinIStreamC &operator<<(BinIStreamC & strm,RealHistogram1dC &hist) {
    RealT offset,scale;
    SArray1dC<UIntC> xhist;
    strm >> offset >> scale >> xhist;
    hist = RealHistogram1dC(scale,offset,xhist);
    return strm;
  }
  
}
