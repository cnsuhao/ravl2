// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_CLIST_HEADER
#define RAVLGUI_CLIST_HEADER 1
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

#if RAVL_USE_GTK2
#include <gdk/gdkcolor.h>
#else
#include <gdk/gdktypes.h>
#endif

namespace RavlGUIN {

  //! userlevel=Advanced
  //: Cell info.
  
  class CListCellC {
  public:
    CListCellC()
      : useFgCol(false),
	useBgCol(false)
    {}
    //: Default constructor.
    
    CListCellC(const StringC &ntext);
    //: Create a text cell.
    
    CListCellC(const PixmapC &npixmap);
    //: Create a cell with a pixmap.
    
    StringC text;  // Text to display.
    bool useFgCol;
    GdkColor fgCol;  // Text colour
    bool useBgCol;
    GdkColor fbCol;  // Background colour.
    PixmapC pixmap; // Can be invalid.
  };
  
  //! userlevel=Develop
  //: CList widget body.
  
  class CListBodyC
    : public WidgetBodyC
  {
  public:
    CListBodyC(const DListC<StringC> &titles,GtkSelectionMode nselMode = GTK_SELECTION_SINGLE);
    //: Constructor
    
    CListBodyC(const char *titles[],int *colWidths = 0,GtkSelectionMode nselMode = GTK_SELECTION_SINGLE);
    //: Constructor
    
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
    // Use from the GUI thread only.
    
    bool GUIUnselect(int &id);
    //: Force an item to be unselected.
    // Use from the GUI thread only.

    bool GUIUnselectAll();
    //: Remove all entries from the selection.
    // Use from the GUI thread only.

    bool GUISelectAll();
    //: Remove all entries from the selection.
    // Use from the GUI thread only.

    bool Select(int &id);
    //: Force an item to be selected.

    bool SelectAll();
    //: Force all items to be selected.
    
    bool Unselect(int &id);
    //: Force an item to be unselected.
    
    bool UnselectAll();
    //: Remove all entries from the selection.
    
    IntT Cols() const
    { return cols ; }
    //: Get the number of cols in the clist.
    
    DListC<IntT> Selection();
    //: Access current selection.
    
    bool GUIMoveID2Row(int &id,int &rowNo);
    //: Move the row with the given id to the rowNo .
    // Use from the GUI thread only.
    
    bool MoveID2Row(int id,int rowNo);
    //: Move the row with the given id to the rowNo .

    bool Freeze();
    //: Stop rendering updates to CList.
    // Calling this before doing many changes to the list
    // and then calling Thaw() will speed up the updates.

    bool GUIFreeze();
    //: Stop rendering updates to CList.
    // Calling this before doing many changes to the list
    // and then calling Thaw() will speed up the updates. <p>
    // Use from the GUI thread only.
    
    bool Thaw();
    //: Start rendering updates to CList.
    
    bool GUIThaw();
    //: Start rendering updates to CList.
    // Use from the GUI thread only.
    
    bool Clear();
    //: Clear all entries from the list.
    
    bool GUIClear();
    //: Clear all entries from the list.
    // Use from the GUI thread only.
    
    IntT GUIFindRowID(const Index2dC &at);
    //: Find row ID at position.
    
  protected:
    virtual void Destroy();
    //: Undo all references.
    
    bool GUIRowUnselected(CListEventC &);
    //: Called when row is unselected.
    
    bool GUIRowSelected(CListEventC &);
    //: Called when row is selected.
    
    GtkSelectionMode  selMode;
    
    RWLockC access;
    
    IntT cols;
    DListC<StringC> titles;
    SArray1dC<IntT> widths;
    
    DListC<Tuple2C<IntT,SArray1dC<CListCellC> > > data;
    HSetC<IntT> selection; // current selection.    
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
    
    CListC(const char *titles[],int *colWidths = 0,GtkSelectionMode nselMode = GTK_SELECTION_SINGLE)
      : WidgetC(* new CListBodyC(titles,colWidths,nselMode))
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
    
    bool GUIUnselectAll()
    { return Body().GUIUnselectAll(); }
    //: Remove all entries from the selection.
    
    bool GUISelectAll()
    { return Body().GUISelectAll(); }
    //: Add all entries to the selection.
    
    bool Select(int &id)
    { return Body().Select(id); }
    //: Force an item to be selected.
    
    bool Unselect(int &id)
    { return Body().Unselect(id); }
    //: Force an item to be unselected.
    
    bool UnselectAll()
    { return Body().UnselectAll(); }
    //: Remove all entries from the selection.
    
    bool SelectAll()
    { return Body().SelectAll(); }
    //: Add all entries to the selection.
    
    IntT Cols() const
    { return Body().Cols(); }
    //: Number of cols in the clist.
    
    DListC<IntT> Selection()
    { return Body().Selection(); }
    //: Access current selection.
    
    bool GUIMoveID2Row(int &id,int &rowNo)
    { return Body().GUIMoveID2Row(id,rowNo); }
    //: Move the row with the given id to the rowNo .
    
    bool MoveID2Row(int id,int rowNo)
    { return Body().MoveID2Row(id,rowNo); }
    //: Move the row with the given id to the rowNo .

    bool Freeze()
    { return Body().Freeze(); }
    //: Stop rendering updates to CList.
    // Calling this before doing many changes to the list
    // and then calling Thaw() will speed up the updates.

    bool GUIFreeze()
    { return Body().GUIFreeze(); }
    //: Stop rendering updates to CList.
    // Calling this before doing many changes to the list
    // and then calling Thaw() will speed up the updates.
    
    bool Thaw()
    { return Body().Thaw(); }
    //: Start rendering updates to CList.
    
    bool GUIThaw()
    { return Body().GUIThaw(); }
    //: Start rendering updates to CList.

    bool Clear()
    { return Body().Clear(); } 
    //: Clear all entries from the list.
    
    bool GUIClear()
    { return Body().GUIClear(); }
    //: Clear all entries from the list.
    
    IntT GUIFindRowID(const Index2dC &at)
    { return Body().GUIFindRowID(at); }
    //: Find row ID at position.
    
    friend class CListBodyC;
  };
}
#endif
