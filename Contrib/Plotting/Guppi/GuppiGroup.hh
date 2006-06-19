// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGRAPH_GUPPIGROUP_HEADER
#define RAVLGRAPH_GUPPIGROUP_HEADER 1
//! author="Charles Galambos"
//! docentry="Ravl.GUI.Data_Plotting.Guppi"
//! rcsid="$Id$"
//! lib=RavlGuppi
//! file="Ravl/Contrib/Plotting/Guppi/GuppiGroup.hh"

#include "Ravl/RCHandleV.hh"
#include "Ravl/Plot/GuppiTypes.hh"

namespace RavlPlotN {
  using namespace RavlN;
  class GuppiGroupC;
  class GuppiElementC;
  
  //! userlevel=Develop
  //: Guppi Group.
  
  class GuppiGroupBodyC
    : public RCBodyVC
  {
  public:
    GuppiGroupBodyC();
    //: Constructor.
    
    GuppiGroupBodyC(GuppiGroupView *group);
    //: Constructor.
    
    ~GuppiGroupBodyC();
    //: Destructor
    
    virtual void Build();
    //: Build guppi objects.
    
    GuppiGroupView *GroupView()
    { return group; }
    //: Access group view.
    
    GuppiElementView *View();
    //: Access as element view.
    
    void AddFull(GuppiGroupC &grp);
    //: Add group so that it fills this one.
    
    bool IsBuilt() const
    { return group != 0; }
    //: Is Group built ?
    
  protected:
    GuppiGroupView *group;
  };
  
  //! userlevel=Normal
  //: Guppi Group.
  
  class GuppiGroupC
    : public RCHandleC<GuppiGroupBodyC>
  {
  public:
    GuppiGroupC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    GuppiGroupC(GuppiGroupView *group)
      : RCHandleC<GuppiGroupBodyC>(*new GuppiGroupBodyC(group))
    {}
    //: Constructor.
    
    explicit GuppiGroupC(bool)
      : RCHandleC<GuppiGroupBodyC>(*new GuppiGroupBodyC())
    {}
    //: Constructor.
    
  protected:
    GuppiGroupC(GuppiGroupBodyC &bod)
      : RCHandleC<GuppiGroupBodyC>(bod)
    {}
    //: Body constructor.
    
    GuppiGroupBodyC& Body()
    { return RCHandleC<GuppiGroupBodyC>::Body(); }
    //: Access body.

    const GuppiGroupBodyC& Body() const
    { return RCHandleC<GuppiGroupBodyC>::Body(); }
    //: Access body.
    
  public:
    GuppiGroupView *GroupView()
    { return Body().GroupView(); }
    //: Access group view.
    
    GuppiElementView *View()
    { return Body().View(); }
    //: Access as element view.
    
    void Build()
    { Body().Build(); }
    //: Build guppi objects.
    
    void AddFull(GuppiGroupC &grp)
    { Body().AddFull(grp); }
    //: Add group so that it fills this one.
    
    bool IsBuilt() const
    { return Body().IsBuilt(); }
    //: Is Group built ?
    
  };

}

#endif
