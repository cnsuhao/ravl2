// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUISCROLLEDAREA_HEADER
#define RAVLGUISCROLLEDAREA_HEADER 1
/////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI
//! author="Charles Galambos"
//! file="Ravl/GUI/GTK/ScrolledArea.hh"
//! date="03/04/99"
//! docentry="Ravl.GUI.Layout"

#include "Ravl/GUI/OneChild.hh"

namespace RavlGUIN {

  //! userlevel=Develop
  //: ScrolledArea body.
  
  class ScrolledAreaBodyC 
    : public OneChildBodyC
  {
  public:
    ScrolledAreaBodyC(const WidgetC &achild,IntT isx = -1,IntT isy = -1,bool vauto = true,bool hauto = true);
    //: Constructor.
    
    virtual bool Create();
    //: Create the widget.
    
  protected:
    IntT isx,isy; // Inital area size.
    bool vauto,hauto; // Automatic scrollbars ?
  };
  
  //! userlevel=Normal
  //: ScrolledArea handle.
  
  class ScrolledAreaC
    : public OneChildC
  {
  public:
    ScrolledAreaC(const WidgetC &achild,IntT isx = -1,IntT isy = -1,bool vauto = true,bool hauto = true)
      : OneChildC(*new ScrolledAreaBodyC(achild,isx,isy,vauto,hauto))
      {}
    //: Create a scrolled area.
    // isx,isy set the inital size of the area.
  };

}
#endif
