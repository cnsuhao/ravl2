// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGERECTANGLEITER_HEADER
#define RAVLIMAGERECTANGLEITER_HEADER 1
//! rcsid="$Id$"
//! lib=RavlImageProc
//! author="Charles Galambos"
//! docentry="Ravl.Images.Misc"

#include "Ravl/Image/ImageRectangle.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Rectangle iterator.
  // Slide a window over all possible positions in a
  // larger rectangle.
  
  class Rectange2dIterC {
  public:
    Rectange2dIterC(const ImageRectangleC &nImageRect,const ImageRectangleC &nwindow)
      : size1(nwindow.Range1().Size()),
      imageRect(nImageRect),
      window(nwindow)
      { First(); }
    //: Constructor.
    
    ImageRectangleC &Window()
      { return window; }
    //: Access current window.

    const ImageRectangleC &Window() const
      { return window; }
    //: Access current window.
    
    void First() { 
      UIntT size2 = window.Range2().Size();
      window.Range1().Min() = imageRect.Range1().Min();
      window.Range1().Max() = window.Range1().Min() + size1;
      window.Range2().Min() = imageRect.Range2().Min();
      window.Range2().Max() = window.Range1().Min() + size2;
    }
    //: Goto first position.
    
    void Next() {
      ++(window.Range1());
      if(window.Range1().Max() <= imageRect.Range1().Max())
	return ;
      window.Range1().Min() = imageRect.Range1().Min();
      window.Range1().Max() = window.Range1().Min() + size1;
      ++(window.Range2());
    }
    // Goto next position.
    
    bool IsElm() const
      { return window.Range2().Max() <= imageRect.Range2().Max(); }
    //: At a valid position ?
    
  public:
    UIntT size1;
    ImageRectangleC imageRect;
    ImageRectangleC window;
  };
}


#endif
