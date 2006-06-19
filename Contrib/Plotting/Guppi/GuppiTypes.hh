// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGRAPH_GUPPITYPES_HEADER
#define RAVLGRAPH_GUPPITYPES_HEADER 1
//! author="Charles Galambos"
//! userlevel=Advanced
//! docentry="Ravl.GUI.Data_Plotting.Guppi"
//! rcsid="$Id: GuppiTypes.hh 3317 2003-08-20 14:50:13Z ees1wc $"
//! lib=RavlGuppi
//! file="Ravl/Contrib/Plotting/Guppi/GuppiTypes.hh"

extern "C" {
  typedef struct _GuppiElementState GuppiElementState;
  typedef struct _GuppiElementView GuppiElementView;
  typedef struct _GuppiSeqScalar GuppiSeqScalar;
  typedef struct _GuppiGroupView GuppiGroupView;
  typedef struct _GuppiRootGroupView GuppiRootGroupView;
}

namespace RavlPlotN {
  //! uselevel=Normal
  void InitGuppi();
  //: Initialise guppi.
  
}

#endif
