// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPLOT_GUPPILINEGRAPH_HEADER
#define RAVLPLOT_GUPPILINEGRAPH_HEADER 1
//! author="Charles Galambos"
//! docentry="Ravl.GUI.Data_Plotting.Guppi"
//! rcsid="$Id: GuppiLineGraph.hh 3401 2003-09-06 08:11:47Z craftit $"
//! lib=RavlGuppi
//! file="Ravl/Contrib/Plotting/Guppi/GuppiLineGraph.hh"

#include "Ravl/Plot/GuppiElement.hh"
#include "Ravl/Plot/GuppiScalarSequence.hh"
#include "Ravl/Point2d.hh"

namespace RavlPlotN {

  //! userlevel=Develop
  //: Single line graph.
  
  class GuppiLineGraphBodyC 
    :  public GuppiElementBodyC
  {
  public:
    GuppiLineGraphBodyC(const GuppiScalarSequenceC &xdata,const GuppiScalarSequenceC &ydata);
    //: Constructor
    
    GuppiLineGraphBodyC(const Array1dC<RealT> &data);
    //: Construct from an array of values
    
    GuppiLineGraphBodyC(const Array1dC<Point2dC> &data);
    //: Construct from an array of points.
    
    void Build();
    //: Build guppi objects.
    
    GuppiScalarSequenceC &DataY()
    { return dataY; }
    //: Access y data
    
    GuppiScalarSequenceC &DataX()
    { return dataX; }
    //: Access x data
    
    bool Update(const Array1dC<RealT> &data);
    //: Update data in plot.
    
    bool Update(const Array1dC<Point2dC> &data);
    //: Update data in plot.
    
  protected:
    GuppiScalarSequenceC dataY;
    GuppiScalarSequenceC dataX;
  };
  
  //! userlevel=Normal
  //: Single line graph.
  
  class GuppiLineGraphC
    : public GuppiElementC
  {
  public:
    GuppiLineGraphC()
    {}
    //: Default constructor
    // creates an invalid handle.
    
    GuppiLineGraphC(const Array1dC<RealT> &data)
      : GuppiElementC(*new GuppiLineGraphBodyC(data))
    {}
    //: Construct directly from some data.
    
    GuppiLineGraphC(const Array1dC<Point2dC> &data)
      : GuppiElementC(*new GuppiLineGraphBodyC(data))
    {}
    //: Construct from an array of points.
    
  protected:
    GuppiLineGraphBodyC &Body()
    { return static_cast<GuppiLineGraphBodyC &>(GuppiElementC::Body()); }
    //: Access body.
    
    const GuppiLineGraphBodyC &Body() const
    { return static_cast<const GuppiLineGraphBodyC &>(GuppiElementC::Body()); }
    //: Access body.
    
  public:
    GuppiScalarSequenceC &DataY()
    { return Body().DataY(); }
    //: Access y data
    
    GuppiScalarSequenceC &DataX()
    { return Body().DataX(); }
    //: Access x data
    
    bool Update(const Array1dC<RealT> &data)
    { return Body().Update(data); }
    //: Update data in plot.
    
    bool Update(const Array1dC<Point2dC> &data)
    { return Body().Update(data); }
    //: Update data in plot.
    
  };
  
}


#endif
