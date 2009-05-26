// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! author="Charles Galambos"
//! userlevel=Advanced
//! docentry="Ravl.GUI.Data_Plotting.Guppi"
//! rcsid="$Id$"
//! lib=RavlGuppi
//! file="Ravl/Contrib/Plotting/Guppi/exGuppi.cc"

#include "Ravl/Option.hh"
#include "Ravl/Plot/GuppiCanvas.hh"
#include "Ravl/Plot/GuppiGraph.hh"

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/Button.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/Array1dIter.hh"
#include "Ravl/StdConst.hh"
#include "Ravl/Math.hh"

using namespace RavlPlotN;

int main(int nargs,char **argv) {
  Manager.Init(nargs,argv);
  OptionC opt(nargs,argv);
  opt.Check();
  
  InitGuppi();
  
  Array1dC<RealT> data(100);
  RealT val = 0;
  for(Array1dIterC<RealT> it(data);it;it++,val += (RavlConstN::pi/40))
    *it = Sin(val);
  //cerr <<"Data=" << data << "\n";
  
  WindowC win(400,400,"Hello");
  GuppiCanvasC gup(72*11, 72*8.5);
  GuppiGraphC graph(data);
  gup.Group().AddFull(graph);  
  win.Add(gup);
  win.Show();
  
  Manager.Start();
  cerr << "Finished... \n";
  
  return 0;
}
