// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_POINTTRACKMODEL_HEADER
#define RAVLIMAGE_POINTTRACKMODEL_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! date="24/7/2002"
//! docentry="Ravl.Images.Tracking"
//! file="Ravl/Image/Processing/Tracking/PointTrackModel.hh"
//! lib=RavlImageProc

#include "Ravl/Array2d.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/Vector2d.hh"
#include "Ravl/Image/PointTrack.hh"

namespace RavlImageN {
  using namespace RavlN;
  
  class PointTrackModelC;
  
  ostream &operator<<(ostream &strm,const PointTrackModelC &pt);
  //: Save to ostream.
  
  istream &operator>>(istream &strm,PointTrackModelC &pt);
  //: Load from istream.

  //:-
  
  //! userlevel=Normal
  //: Tracking information on a single point.
  
  class PointTrackModelC {
  public:
    PointTrackModelC(UIntT nid,const Index2dC &nat,IntT frameNo,const Array2dC<ByteT> &ntempl)
      : id(nid),
	at(nat),
	vel(0,0),
	frame(frameNo),
	templ(ntempl)
    {}
    //: Create new track.
    
    UIntT ID() const
    { return id; }
    //: Access track ID.
    
    const Point2dC &Location() const
    { return at; }
    //: Access last location that object was seen.
    
    Point2dC EstimateLocation(IntT frameNo)
    { return at + vel * (frameNo - frame); }
    //: Estimate location in given frame.
    // Simple estimate on next position based on the points velocity.
    
    IntT Frame() const
    { return frame; }
    //: Access frame number object was last seen.
    
    void Update(const Point2dC &nat,UIntT frameNo,IntT nmatchScore) { 
      vel = (nat - at) / (RealT)(frameNo - frame);
      at = nat;
      frame = frameNo;
      matchScore = nmatchScore;
    }
    //: Update a track.
    
    Array2dC<ByteT> &Template()
    { return templ; }
    //: Access template.
    
    const Vector2dC &Velocity() const
    { return vel; }
    //: Estimated velocity of point.
    
    IntT MatchScore() const
    { return matchScore; }
    //: Get the last match score.
    
  protected:
    UIntT id;      // Point ID.
    Point2dC at;  // Point at which it was last seen.
    Vector2dC vel; // Difference between previous two positions.
    UIntT frame;   // Frame number.
    IntT matchScore; // Last match score.
    Array2dC<ByteT> templ; // Template of feature.
  };
  
}


#endif
