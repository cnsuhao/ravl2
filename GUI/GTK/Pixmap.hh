// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUIPIXMAP_HEADER
#define RAVLGUIPIXMAP_HEADER 1
////////////////////////////////////////////////////
//! file="Ravl/GUI/GTK/Pixmap.hh"
//! lib=RavlGUI
//! author="Charles Galambos"
//! date="23/03/99"
//! docentry="Ravl.GUI.Layout"
//! rcsid="$Id$"

#include "Ravl/GUI/Widget.hh"
#include "Ravl/String.hh"

struct _GdkVisual;
typedef struct _GdkVisual        GdkVisual;

namespace RavlGUIN {
  
  //! userlevel=Develop
  //: Pixmap body
  
  class PixmapBodyC 
    : public WidgetBodyC
  {
  public:
    PixmapBodyC(const char **data,const WidgetC &rwin = WidgetC());
    //: Constructor.
    
    PixmapBodyC(const StringC &filename,const WidgetC &rwin = WidgetC());
    //: Constructor.
    // Currently this will ONLY load xpm's
    
    PixmapBodyC(int width,int height,int depth);
    //: Constructor.
    
    virtual bool Create();
    //: Create the widget.
    
    GdkPixmap * &Pixmap() { return pixmap; }
    //: Access pixmap.
    
    GdkBitmap &Mask()
      { return *mask; }
    //: Access pixmap mask.
    
  protected:
    WidgetC rootWin;  // Handle to root win, invalidated after Create.
    GdkPixmap *pixmap;  
    GdkBitmap *mask;
    StringC filename;
    const char **data;
    int width,height,depth;
  };
  
  
  //! userlevel=Normal
  //: Pixmap 
  // Note: Its an unfortunate fact that the root application window
  // MUST be instanciated before the pixmap is created.
  
  class PixmapC 
    : public WidgetC
  {
  public:
    PixmapC(const WidgetC &rootWin,char **data)
      : WidgetC(*new PixmapBodyC((const char **) data,rootWin))
      {}
    //: Constructor
    
    PixmapC(const WidgetC &rootWin,const StringC &filename)
      : WidgetC(*new PixmapBodyC(filename,rootWin))
      {}
    //: Constructor
    
    explicit PixmapC(char **data)
      : WidgetC(*new PixmapBodyC((const char **) data))
      {}
    //: Constructor
    
    explicit PixmapC(const StringC &filename)
    : WidgetC(*new PixmapBodyC(filename))
      {}
    //: Constructor
    
    explicit PixmapC(int width,int height,int depth)
      : WidgetC(*new PixmapBodyC(width,height,depth))
      {}
    //: Constructor.
    
    PixmapC()
      {}
    //: Default constructor.
    
  protected:
    PixmapBodyC &Body()
      { return static_cast<PixmapBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const PixmapBodyC &Body() const
      { return static_cast<const PixmapBodyC &>(WidgetC::Body()); }
    //: Access body.
    
  public:
    
    GdkBitmap &Mask()
      { return Body().Mask(); }
    //: Access pixmap mask.
    
  };
  
  extern const char * xpmData_OpenFile[];
};

#endif
