// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPLOT_GUPPIGRAPH_HEADER
#define RAVLPLOT_GUPPIGRAPH_HEADER 1
//! author="Charles Galambos"
//! docentry="Ravl.GUI.Data_Plotting.Guppi"
//! rcsid="$Id: GuppiGraph.hh 3317 2003-08-20 14:50:13Z ees1wc $"
//! lib=RavlGuppi
//! file="Ravl/Contrib/Plotting/Guppi/GuppiGraph.hh"

#include "Ravl/Plot/GuppiGroup.hh"
#include "Ravl/Plot/GuppiElement.hh"
#include "Ravl/DList.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/Plot/GraphData2d.hh"

namespace RavlPlotN {
  
  //! userlevel=Develop
  //: Generic graph group. 
  // With ticks, background etc.
  
  class GuppiGraphBodyC 
    : public GuppiGroupBodyC 
  {
  public:
    GuppiGraphBodyC();
    //: Constructor.
    
    GuppiGraphBodyC(const DListC<GuppiElementC> &plots);
    //: Constructor from a list of plots.
    
    GuppiGraphBodyC(GuppiElementC &plot);
    //: Constructor from a single plot
    
    GuppiGraphBodyC(const Array1dC<RealT> &data);
    //: Constructor a line graph directly from some data.
    
    GuppiGraphBodyC(const GraphData2dC &data);
    //: Constructor a line graph directly from some data.
    
    virtual void Build();
    //: Build guppi objects
    
    DListC<GuppiElementC> &Plots(const DListC<GuppiElementC> &plots);
    //: Set plots to use.
    
    bool AddPlot(GuppiElementC &plot);
    //: Add new plot to graph.
    
  protected:
    DListC<GuppiElementC> plots;
  };

  //! userlevel=Develop
  //: Generic graph group. 
  // With ticks, background etc.

  class GuppiGraphC 
    : public GuppiGroupC
  {
  public:
    GuppiGraphC()
    {}
    //: Default constructor.
    
    GuppiGraphC(const DListC<GuppiElementC> &plots)
      : GuppiGroupC(*new GuppiGraphBodyC(plots))
    {}
    //: Constructor from a list of plots
    
    GuppiGraphC(GuppiElementC &plot)
      : GuppiGroupC(*new GuppiGraphBodyC(plot))
    {}
    //: Constructor from a single plot
    
    GuppiGraphC(bool)
      : GuppiGroupC(*new GuppiGraphBodyC())
    {}
    //: Constructor.
    
    GuppiGraphC(const Array1dC<RealT> &data)
      : GuppiGroupC(*new GuppiGraphBodyC(data))
    {}
    //: Constructor a line graph directly from some data.
    
    GuppiGraphC(const GraphData2dC &data)
      : GuppiGroupC(*new GuppiGraphBodyC(data))
    {}
    //: Constructor a line graph directly from some data.
    
  protected:
    GuppiGraphBodyC &Body()
    { return static_cast<GuppiGraphBodyC &>(GuppiGroupC::Body()); }
    //: Access body.
    
    const GuppiGraphBodyC &Body() const
    { return static_cast<const GuppiGraphBodyC &>(GuppiGroupC::Body()); }
    //: Access body.
    
  public:
    DListC<GuppiElementC> &Plots(const DListC<GuppiElementC> &plots)
    { return Body().Plots(plots); }
    //: Set plots to use.
    
    bool AddPlot(GuppiElementC &plot)
    { return Body().AddPlot(plot); }
    //: Add new plot to graph.
    
  };
  
  
}

#endif
