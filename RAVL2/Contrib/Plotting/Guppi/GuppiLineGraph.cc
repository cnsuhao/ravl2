// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: GuppiLineGraph.cc 3401 2003-09-06 08:11:47Z craftit $"
//! lib=RavlGuppi
//! file="Ravl/Contrib/Plotting/Guppi/GuppiLineGraph.cc"

#include "Ravl/Plot/GuppiLineGraph.hh"
#include "Ravl/Plot/GuppiHeaders.hh"
#include "Ravl/Stream.hh"
#include "Ravl/Array1dIter.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlPlotN {
  
  //: Constructor
  
  GuppiLineGraphBodyC::GuppiLineGraphBodyC(const GuppiScalarSequenceC &xdata,const GuppiScalarSequenceC &ydata) 
    : dataY(ydata),
      dataX(ydata)
  {}
  

  //: Constructor.
  
  GuppiLineGraphBodyC::GuppiLineGraphBodyC(const Array1dC<RealT> &data) {
    ONDEBUG(cerr << "GuppiLineGraphBodyC::GuppiLineGraphBodyC(const Array1dC<RealT> &), Called. \n");
    dataY = GuppiScalarSequenceC(data);
    dataX = GuppiScalarSequenceC(GSSLinear,0,1,data.Size());
    ONDEBUG(cerr << "GuppiLineGraphBodyC::GuppiLineGraphBodyC(const Array1dC<RealT> &), Done. \n");
  }
  
  //: Construct from an array of points.
  
  GuppiLineGraphBodyC::GuppiLineGraphBodyC(const Array1dC<Point2dC> &data) 
    : dataY(true),
      dataX(true)
  {    
    for(Array1dIterC<Point2dC> it(data);it;it++) {
      dataY.Append(it->Row());
      dataX.Append(it->Col());
    }
  }

  //: Build guppi objects.
  void GuppiLineGraphBodyC::Build() {
    ONDEBUG(cerr << "GuppiLineGraphBodyC::Build(), Called. \n");
    if(!dataX.IsValid() || !dataY.IsValid()) {
      cerr << "GuppiLineGraphBodyC::Build(), Failed. Data missing. \n";
      return ;
    }
    state = guppi_element_state_new ("linegraph",
				     "x_data", dataX.Sequence(),
				     "y_data", dataY.Sequence(),
				     NULL);
    
    GuppiElementBodyC::Build();
    ONDEBUG(cerr << "GuppiLineGraphBodyC::Build(), Done. \n");
  }


  //: Update data in plot.
  
  bool GuppiLineGraphBodyC::Update(const Array1dC<RealT> &data) {
    ONDEBUG(cerr << "GuppiLineGraphBodyC::Update(), Called. \n");
    dataY.Set(data);
    return true;
  }


  //: Update data in plot.
  
  bool GuppiLineGraphBodyC::Update(const Array1dC<Point2dC> &data) {
    //data
    dataY.Set(data,0);
    dataX.Set(data,1);
    return true;
  }

}
