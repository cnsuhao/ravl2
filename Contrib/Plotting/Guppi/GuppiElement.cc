// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: GuppiElement.cc 3074 2003-06-13 07:23:52Z craftit $"
//! lib=RavlGuppi
//! file="Ravl/Contrib/Plotting/Guppi/GuppiElement.cc"

#include "Ravl/Plot/GuppiElement.hh"
#include "Ravl/Stream.hh"
#include "Ravl/Plot/GuppiHeaders.hh"

namespace RavlPlotN {
  //: Default constructor.
  
  GuppiElementBodyC::GuppiElementBodyC()
    : state(0),
      view(0)
  {}
  
  //: Constructor.
  
  GuppiElementBodyC::GuppiElementBodyC(GuppiElementState *nstate)
    : state(nstate),
      view(0)
  {}
  
  //: Build guppi elements.
  
  void GuppiElementBodyC::Build() {
    if(state == 0) {
      cerr << "GuppiElementBodyC::Build(), Can't build element. No state! \n";
      return ;
    }
    view = guppi_element_view_new (state, NULL);
  }
  
  //: Destructor
  
  GuppiElementBodyC::~GuppiElementBodyC() {
    guppi_unref (state);
    guppi_unref (view);
  }
  
}
