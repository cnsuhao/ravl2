// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"

#include "Ravl/RansacObsList.hh"

namespace RavlN {

  //: Constructor
  // Stores the given list of point observations
  RansacObsListC::RansacObsListC(DListC<ObservationC> obs_list)
    : RansacC()
  {
    // convert list of points to array
    obs_array = SArray1dC<ObservationC>(obs_list.Size());
    IntT i=0;
    for(DLIterC<ObservationC> it(obs_list);it;it++,i++)
      obs_array[i] = it.Data();
  }
}
