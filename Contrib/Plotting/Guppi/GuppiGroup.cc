// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! author="Charles Galambos"
//! rcsid="$Id: GuppiGroup.cc 3074 2003-06-13 07:23:52Z craftit $"
//! lib=RavlGuppi
//! file="Ravl/Contrib/Plotting/Guppi/GuppiGroup.cc"

#include "Ravl/Plot/GuppiGroup.hh"
#include "Ravl/Plot/GuppiHeaders.hh"

namespace RavlPlotN {
  
  //: Default constructor.
  
  GuppiGroupBodyC::GuppiGroupBodyC() 
    : group(0)
  { }
  
  //: Constructor.
  
  GuppiGroupBodyC::GuppiGroupBodyC(GuppiGroupView *ngroup) 
    : group(ngroup)
  {}
  
  //: Build guppi objects.
  
  void GuppiGroupBodyC::Build() {
    group  = guppi_group_view_new (); 
  }
  
  //: Access as element view.
  
  GuppiElementView *GuppiGroupBodyC::View() {
    RavlAssert(group != 0);
    return GUPPI_ELEMENT_VIEW (group);
  }
  
  //: Destructor
  
  GuppiGroupBodyC::~GuppiGroupBodyC() {
    guppi_unref (group);
  }
  
  //: Add group so that it fills this one.
  
  void GuppiGroupBodyC::AddFull(GuppiGroupC &grp) {
    if(!IsBuilt()) 
      Build();
    if(!grp.IsBuilt())
      grp.Build();
    guppi_group_view_layout_flush_top (group, grp.View(), 0);
    guppi_group_view_layout_flush_left (group, grp.View(), 0);
    guppi_group_view_layout_flush_right (group, grp.View(), 0);
    guppi_group_view_layout_flush_bottom (group, grp.View(), 0);
  }
  
  
}
