// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: GuppiInit.cc 3074 2003-06-13 07:23:52Z craftit $"
//! lib=RavlGuppi
//! file="Ravl/Contrib/Plotting/Guppi/GuppiInit.cc"


#include "Ravl/Stream.hh"
#include "Ravl/Plot/GuppiHeaders.hh"
#include "Ravl/Plot/GuppiTypes.hh"

namespace RavlPlotN {
  using namespace RavlN;
  
  static bool guppiInitDone = false;
  
  void InitGuppi() {
    if(guppiInitDone)
      return ;
    guppiInitDone = true;
    cerr <<"InitGuppi(), Called. \n";
    //int argc =1;
    //char *argv[3] = {"x","y",0};
    //gnome_init ("demo", "0.0", argc, argv);

    glade_gnome_init ();
    
    guppi_useful_init_without_guile ();
    //guppi_set_verbosity (GUPPI_VERY_VERBOSE);
    //guppi_set_verbosity (GUPPI_VERBOSE);
    
    guppi_data_init ();
    guppi_plot_init ();
    
    guppi_plug_in_path_set ("/usr/lib/guppi/plug-ins");
    guppi_plug_in_load_all ();
    //guppi_plug_in_spec_find_all ();
    cerr <<"InitGuppi(), Done. \n";

  }
}
