// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUICLIST_HEADER
#define RAVLGUICLIST_HEADER 1
////////////////////////////////////////////////////////////////
//! rcsid="$Id$" 
//! file="Ravl/GUI/GTK/CList.hh"
//! lib=RavlGUI
//! userlevel=Normal
//! author="Charles Galambos"
//! date="13/12/2000"
//! docentry="Ravl.GUI.Control"
//! example=exCList.cc

#include "Ravl/GUI/Widget.hh"
#include "Ravl/Threads/RWLock.hh"
#include "Ravl/String.hh"
#include "Ravl/DList.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/GUI/Pixmap.hh"
#include "Ravl/GUI/MouseEvent.hh"
#include "Ravl/Hash.hh"
#include "Ravl/HSet.hh"
#include "Ravl/Tuple2.hh"
#include <gdk/gdktypes.h>

namespace RavlGUIN {

  //! userlevel=Advanced
  //: Cell info.
  
  class CListCellC {
  public:
    CListCellC()
      : useFgCol(false),
	useBgCol(false)
      {}
    //: Constructor.
    
    StringC text;  // Text to display.
    bool useFgCol;
    GdkColor fgCol;  // Text colour
    bool useBgCol;
    GdkColor fbCol;  // Background colour.
    PixmapC pixMap; // Can be invalid.
    PixmapC pixMask;  // Can be invalid.
  };
  
  //! userlevel=Develop
  //: CList widget body.
  
  class CListBodyC
    : public WidgetBodyC
  {
  public:
    CListBodyC(const DListC<StringC> &titles);
    //: Default constructor
    
    CListBodyC(const char *titles[]);
    //: Default constructor
    
    virtual bool Create();
    //: Create the widget.
    
    bool GUIAppendLine(int &id,SArray1dC<StringC> &line);
    //: Append a line entry.  
    // GUI thread only.
    
    bool GUIAppendCLine(int &id,SArray1dC<CListCellC> &line);
    //: Append a line entry.  
    // GUI thread only.
    
    void AppendLine(int &id,SArray1dC<CListCellC> &line);
    //: Append a line entry.  
    // GUI thread only.
    
    void AppendLine(int &id,SArray1dC<StringC> &line);
    //: Append a line entry.  
    // GUI thread only.

    bool GUIRemoveLine(int &id);
    //: Remove a line entry.  
    // GUI thread only.
    
    void RemoveLine(int &id);
    //: Remove a line entry.  
    
    bool GUISelect(int &id);
    //: Force an item to be selected.
    
    bool GUIUnselect(int &id);
    //: Force an item to be unselected.

    bool Select(int &id);
    //: Force an item to be selected.
    
    bool Unselect(int &id);
    //: Force an item to be unselected.
    
    IntT Cols() const
      { return cols ; }
    //: Get the number of cols in the clist.
    
    DListC<IntT> Selection();
    //: Access current selection.
    
  protected:
    virtual void Destroy();
    //: Undo all refrences.
    
    bool GUIRowUnselected(CListEventC &);
    //: Called when row is unselected.
    
    bool GUIRowSelected(CListEventC &);
    //: Called when row is unselected.
    
    GtkSelectionMode  selMode;
    
    RWLockC access;
    
    IntT cols;
    DListC<StringC> titles;
    DListC<Tuple2C<IntT,SArray1dC<CListCellC> > > data;
    HSetC<IntT> selection; // current selection.
    
    //HasARC<IntT,IntT> idMap; // Maps an ID to a row.
  };
  
  //! userlevel=Normal
  //: CList widget.
  
  class CListC
    : public WidgetC
  {
 public:
    CListC()
      {}
    //: Default constructor
    // Creates an invalid handle.
    
    CListC(const DListC<StringC> &titles)
      : WidgetC(* new CListBodyC(titles))
    {}
    //: Constructor
  
    CListC(const char *titles[])
      : WidgetC(* new CListBodyC(titles))
    {}
    //: Constructor
    
    
  protected:
    CListC(CListBodyC &bod)
      : WidgetC(bod)
    {}
    //: Body constructor.
    
    CListBodyC &Body()
      { return static_cast<CListBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const CListBodyC &Body() const
      { return static_cast<const CListBodyC &>(WidgetC::Body()); }
    //: Access body.
    
  public:
    bool GUIAppendLine(int &id,SArray1dC<StringC> &line)
      { return Body().GUIAppendLine(id,line); }
    //: Append a line entry.
    // GUI thread only.
    
    bool GUIAppendCLine(int &id,SArray1dC<CListCellC> &line)
      { return Body().GUIAppendCLine(id,line); }
    //: Append a line entry.
    // GUI thread only.
    
    void AppendLine(int &id,SArray1dC<CListCellC> line)
      { Body().AppendLine(id,line); }
    //: Append a line entry.  
    
    void AppendLine(int &id,SArray1dC<StringC> line)
      { Body().AppendLine(id,line); }
    //: Append a line entry.  
    
    bool GUIRemoveLine(int &id)
      { return Body().GUIRemoveLine(id); }
    //: Remove a line entry.  
    // GUI thread only.
    
    void RemoveLine(int &id)
      { Body().RemoveLine(id); }
    //: Remove a line entry.  

    bool GUISelect(int &id)
      { return Body().GUISelect(id); }
    //: Force an item to be selected.
    
    bool GUIUnselect(int &id)
      { return Body().GUIUnselect(id); }
    //: Force an item to be unselected.
    
    bool Select(int &id)
      { return Body().Select(id); }
    //: Force an item to be selected.
    
    bool Unselect(int &id)
      { return Body().Unselect(id); }
    //: Force an item to be unselected.
    
    IntT Cols() const
      { return Body().Cols(); }
    //: Number of cols in the clist.
    
    DListC<IntT> Selection()
      { return Body().Selection(); }
    //: Access current selection.
    
    friend class CListBodyC;
  };
}
#endif
