// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////////////
//! author="Charles Galambos"
//! date="24/7/2002"
//! rcsid="$Id$"

#include "Ravl/Image/PointTrack.hh"
#include "Ravl/Stream.hh"

namespace RavlImageN {
  
  //: Save to ostream.
  
  ostream &operator<<(ostream &strm,const PointTrackC &pt) {
    strm << pt.ID() << ' ' << pt.Location() << ' ' << pt.Confidence() << "\n";
    return strm;
  }
  
  //: Load from istream.
  
  istream &operator>>(istream &strm,PointTrackC &pt) {
    strm >> pt.id >> pt.at >> pt.conf;
    return strm;
  }
  
}
