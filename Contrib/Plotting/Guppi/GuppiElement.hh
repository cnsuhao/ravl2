// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGRAPH_GUPPIELEMENT_HEADER
#define RAVLGRAPH_GUPPIELEMENT_HEADER 1
//! author="Charles Galambos"
//! docentry="Ravl.GUI.Data_Plotting.Guppi"
//! rcsid="$Id$"
//! lib=RavlGuppi
//! file="Ravl/Contrib/Plotting/Guppi/GuppiElement.hh"

#include "Ravl/RCHandleV.hh"
#include "Ravl/Plot/GuppiTypes.hh"

namespace RavlPlotN {
  using namespace RavlN;
  
  //! userlevel=Develop
  //: Guppi element body
  
  class GuppiElementBodyC
    : public RCBodyVC
  {
  public:
    GuppiElementBodyC();
    //: Default constructor.
    
    ~GuppiElementBodyC();
    //: Destructor
    
    GuppiElementBodyC(GuppiElementState *state);
    //: Constructor.
    
    virtual void Build();
    //: Build guppi elements.
    
    GuppiElementState *State()
    { return state; }
    //: Get state for element.
    
    GuppiElementView *View()
    { return view; }
    //: Get view for element.
    
    bool IsBuilt() const
    { return view != 0; }
    //: Is Group built ?

  protected:
    GuppiElementState *state;
    GuppiElementView *view;
  };
  
  
  //! userlevel=Normal
  //: Guppi element body
  
  class GuppiElementC
    : public RCHandleC<GuppiElementBodyC>
  {
  public:
    GuppiElementC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    GuppiElementC(GuppiElementState *state)
      : RCHandleC<GuppiElementBodyC>(*new GuppiElementBodyC(state))
    {}
    //: Constructor.

  protected:
    GuppiElementC(GuppiElementBodyC &bod)
      : RCHandleC<GuppiElementBodyC>(bod)
    {}
    //: Body constructor.
    
    GuppiElementBodyC &Body()
    { return RCHandleC<GuppiElementBodyC>::Body(); }
    //: Access body.

    const GuppiElementBodyC &Body() const
    { return RCHandleC<GuppiElementBodyC>::Body(); }
    //: Access body.
    
  public:
    
    GuppiElementState *State()
    { return Body().State(); }
    //: Get state for element.
    
    GuppiElementView *View()
    { return Body().View(); }
    //: Get view for element.
    
    void Build()
    { Body().Build(); }
    //: Build guppi elements.
    
    bool IsBuilt() const
    { return Body().IsBuilt(); }
    //: Is Group built ?
    
  };
}


#endif
