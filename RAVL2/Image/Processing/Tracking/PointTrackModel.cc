// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: PointTrackModel.cc 2954 2003-05-27 13:14:18Z craftit $"
//! file="Ravl/Image/Processing/Tracking/PointTrackModel.cc"
//! lib=RavlImageProc

#include "Ravl/Image/PointTrackModel.hh"

namespace RavlImageN {
  
  //: Save to ostream.
  
  ostream &operator<<(ostream &strm,const PointTrackModelC &pt) {
    RavlAssertMsg(0,"ostream &operator<<(ostream &strm,const PointTrackModelC &pt), Not implemented. ");
    return strm;
  }
  
  //: Load from istream.
  
  istream &operator>>(istream &strm,PointTrackModelC &pt) {
    RavlAssertMsg(0,"istream &operator>>(istream &strm,PointTrackModelC &), Not implemented. ");
    return strm;
  }

  RealT PointTrackModelBodyC::Confidence() const {
    if(removeThreshold ==0)
      return 0;
    return 1-((matchScore / removeThreshold) * 0.75); // Gives number between 0.25 and 1    
  }

}
