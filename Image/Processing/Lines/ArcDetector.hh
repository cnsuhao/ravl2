// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_ARCDETECTOR_HEADER
#define RAVLIMAGE_ARCDETECTOR_HEADER 1
//! rcsid="$Id$"
//! lib=RavlImageProc
//! author="Charles Galambos"
//! docentry="Ravl.Images.Lines"

#include "Ravl/Image/Edgel.hh"
#include "Ravl/Arc.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Circular Arc Detector.
  
  class ArcDetectorC {
  public:
    ArcDetectorC();
    //: Default constructor.
    
    DListC<ArcC> Apply(DListC<DListC<Index2dC> > edges);
    //: Given a set of edge lists create a set of arc's.
    
  };
}



#endif
