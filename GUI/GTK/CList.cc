// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////////////
//! rcsid="$Id$" 
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/CList.cc"

#include "Ravl/GUI/CList.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/SArray1dIter2.hh"
#include <gtk/gtk.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  
  //: Create a text cell.
  
  CListCellC::CListCellC(const StringC &ntext)
    : text(ntext),
      useFgCol(false),
      useBgCol(false)
  {}
    
  //: Create a cell with a pixmap.
  
  CListCellC::CListCellC(const PixmapC &npixmap)
    : useFgCol(false),
      useBgCol(false),
      pixmap(npixmap)
  {}
  
  //////////////////////////////////////////////////////////////////////
  
  CListBodyC::CListBodyC(const DListC<StringC> &ntitles,GtkSelectionMode nselMode)
    : selMode(nselMode),
      titles(ntitles),
      selectionChanged(0)
  {
    cols = titles.Size();
    ONDEBUG(cerr << "CListBodyC::CListBodyC(), Cols : " << cols << "\n");
    widths = SArray1dC<IntT>(cols);
    widths.Fill(-1);
  }
  
  //: Default constructor
  
  CListBodyC::CListBodyC(const char *ntitles[],int *colWidths,GtkSelectionMode nselMode)
    : selMode(nselMode),
      selectionChanged(0)
  {
    int i = 0;
    if(ntitles != 0) {
      for(;ntitles[i] != 0;i++)
	titles.InsLast(StringC(ntitles[i]));
    } else {
      titles.InsLast("Unknown");
      i++;
    }
    cols = i;
    widths = SArray1dC<IntT>(cols);
    widths.Fill(-1);
    if(colWidths != 0) { // Got some widths ?
      for(i = 0;i < cols;i++)
	widths[i] = colWidths[i];
    }
    ONDEBUG(cerr << "CListBodyC::CListBodyC(), Cols : " << cols << "\n");
  }
  
  //: Called when row is unselected.
  
  bool CListBodyC::GUIRowUnselected(CListEventC &cle) {
    ONDEBUG(cerr << "CListBodyC::GUIRowUnselected. " << cle.RowID() << "\n");
    RWLockHoldC hold(access,false);
    selection -= cle.RowID();
    hold.Unlock();
    selectionChanged(cle.RowID());
    return true;
  }

  //: Called when row is unselected.
  
  bool CListBodyC::GUIRowSelected(CListEventC &cle) {
    ONDEBUG(cerr << "CListBodyC::GUIRowSelected. " << cle.RowID() << "\n");
    RWLockHoldC hold(access,false);
    selection += cle.RowID();
    hold.Unlock();
    selectionChanged(cle.RowID());
    return true;
  }
  
  //: Access current selection.
  
  DListC<IntT> CListBodyC::Selection() {
    DListC<IntT> ret;
    RWLockHoldC hold(access,true);
    for(HSetIterC<IntT> it(selection);it;it++)
      ret += *it;
    return ret;
  }
  
  
  //: Create the widget.
  
  bool CListBodyC::Create() {
    if(widget != 0)
      return true; // Done already!
    
    cols = titles.Size();
    char **tlist = new char *[cols];
    int i = 0;
    for(DLIterC<StringC> it(titles);it;it++,i++) 
      tlist[i] = (char *) it->chars();
    widget = gtk_clist_new_with_titles(cols,tlist);  
    delete [] tlist; // Hope I don't need this now.
    for(int i = 0;i < cols;i++) {
      if(widths[i] < 0)
	continue;
      gtk_clist_set_column_width(GTK_CLIST(widget),i,widths[i]);
    }
    gtk_clist_set_shadow_type (GTK_CLIST(widget), GTK_SHADOW_OUT);    
    gtk_clist_set_selection_mode(GTK_CLIST(widget),selMode);
    // Append lines that we've stored up.
    for(DLIterC<Tuple2C<IntT,SArray1dC<CListCellC> > > it2(data);it2;it2++)
      GUIAppendCLine(it2->Data1(),it2->Data2());
    
    CListEventC defaultInit;
    ConnectRef(Signal("select_row"),*this,&CListBodyC::GUIRowSelected,defaultInit);
    ConnectRef(Signal("unselect_row"),*this,&CListBodyC::GUIRowUnselected,defaultInit);
    ConnectSignals();
    return true;
  }
  
  //: Append a line entry.  
  // GUI thread only.
  
  bool CListBodyC::GUIAppendCLine(int &id,SArray1dC<CListCellC> &line) {
    if(widget == 0) {
      data.InsLast(Tuple2C<IntT,SArray1dC<CListCellC> >(id,line));
      return true;
    }
    // This doesn't to any fancy stuff yet...
    char **tlist = new char *[cols];
    for(int i = 0;i < cols;i++)
      tlist[i] = (char *) line[i].text.chars();  
    int rowNo = gtk_clist_append(GTK_CLIST(widget),tlist);
    for(int i = 0;i < cols;i++) {
      // Look for pixmaps.
      PixmapC &pm = line[i].pixmap;
      if(pm.IsValid()) {
	ONDEBUG(cerr << "CListBodyC::GUIAppendCLine(), Setting pixmap.Row=" << rowNo << " Cell=" << i << "\n");
	if(!pm.Create())
	  cerr << "CListBodyC::GUIAppendCLine(), Failed to create pixmap. \n";
	else
	  gtk_clist_set_pixmap (GTK_CLIST(widget),rowNo,i,pm.Pixmap(),pm.Mask());
      }
    }
    
    gtk_clist_set_row_data (GTK_CLIST(widget),rowNo,(void *) id);
    delete [] tlist;
    return true;
  }
  
  //: Append a line entry.  
  // GUI thread only.
  
  bool CListBodyC::GUIAppendLine(int &id,SArray1dC<StringC> &line) {
    if(widget == 0) {
      SArray1dC<CListCellC> newLine(cols);
      for(SArray1dIter2C<CListCellC,StringC> it(newLine,line);it;it++)
	it.Data1().text = it.Data2();
      data.InsLast(Tuple2C<IntT,SArray1dC<CListCellC> >(id,newLine));
      return true;
    }
    RavlAssert(((int) line.Size()) >= cols); // Do something friendlier ?
    int rowNo = gtk_clist_find_row_from_data (GTK_CLIST(widget),(void *) id);
    if(rowNo >= 0) { // Got row already ?
      for(int i = 0;i< ((int) line.Size());i++)
	gtk_clist_set_text(GTK_CLIST(widget),rowNo,i,line[i]);
    } else {
      char **tlist = new char *[cols];
      for(int i = 0;i < cols;i++)
	tlist[i] = (char *) line[i].chars();  
      rowNo = gtk_clist_append(GTK_CLIST(widget),tlist);
      gtk_clist_set_row_data (GTK_CLIST(widget),rowNo,(void *) id);
      delete [] tlist;
    }
    return true;
  }
  
  //: Remove a line entry.  
  // GUI thread only.
  
  bool CListBodyC::GUIRemoveLine(int &id) {
    if(widget == 0) {
      //cerr << "CListBodyC::GUIRemoveLine(), WARNING: Called before widget constructed. \n";
      for(DLIterC<Tuple2C<IntT,SArray1dC<CListCellC> > > it2(data);it2;it2++) {
	if(it2.Data().Data1() == id) {
	  it2.Del();
	  break;
	}
      }
      return true;
    }
    int rowNo = gtk_clist_find_row_from_data (GTK_CLIST(widget),(void *) id);
    ONDEBUG(cerr << "CListBodyC::GUIRemoveLine(), ID:" << id << "  Row:" << rowNo << "\n");
    if(rowNo < 0)
      return true; // Not found.
    gtk_clist_remove (GTK_CLIST(widget),rowNo);
    return true;
  }
  
  //: Remove a line entry.  
  
  void CListBodyC::RemoveLine(int &id) {
    Manager.Queue(Trigger(CListC(*this),&CListC::GUIRemoveLine,id));
  }
  
  
  //: Append a line entry.  
  // GUI thread only.
  
  void CListBodyC::AppendLine(int &id,SArray1dC<CListCellC> &line) {
    Manager.Queue(Trigger(CListC(*this),&CListC::GUIAppendCLine,id,line));
  }
  
  //: Append a line entry.  
  // GUI thread only.
  
  void CListBodyC::AppendLine(int &id,SArray1dC<StringC> &line) {
    Manager.Queue(Trigger(CListC(*this),&CListC::GUIAppendLine,id,line));
  }

  //: Force an item to be selected.
  
  bool CListBodyC::GUISelect(int &id) {
    if(widget == 0) {
      // FIXME:- This should be handled properly....
      cerr << "WARNING: CListBodyC::GUISelect() called before widget created. \n";
      return true;
    }
    int rowNo = gtk_clist_find_row_from_data (GTK_CLIST(widget),(void *) id);
    if(rowNo < 0)
      return true; // Not found.
    gtk_clist_select_row (GTK_CLIST(widget),rowNo,0);
    return true;
  }
  
  //: Force an item to be unselected.
  
  bool CListBodyC::GUIUnselect(int &id) {
    if(widget == 0) {
      // FIXME:- This should be handled properly.
      cerr << "WARNING: CListBodyC::GUIUnselect() called before widget created. \n";
      return true;
    }
    int rowNo = gtk_clist_find_row_from_data (GTK_CLIST(widget),(void *) id);
    if(rowNo < 0)
      return true; // Not found.
    gtk_clist_unselect_row (GTK_CLIST(widget),rowNo,0);
    return true;
  }

  //: Remove all entries from the selection.
  
  bool CListBodyC::GUIUnselectAll() {
    if(widget == 0) {
      // FIXME:- This should be handled properly.
      cerr << "WARNING: CListBodyC::GUIUnselectAll() called before widget created. \n";
      return true;
    }
    gtk_clist_unselect_all(GTK_CLIST(widget));
    return true;
  }

  //: Add all entries to the selection.
  
  bool CListBodyC::GUISelectAll() {
    if(widget == 0) {
      // FIXME:- This should be handled properly.
      cerr << "WARNING: CListBodyC::GUISelectAll() called before widget created. \n";
      return true;
    }
    gtk_clist_select_all(GTK_CLIST(widget));
    return true;
  }
  
  
  //: Force an item to be selected.
  
  bool CListBodyC::Select(int &id) {
    Manager.Queue(Trigger(CListC(*this),&CListC::GUISelect,id));
    return true;
  }
  
  //: Force an item to be unselected.
  
  bool CListBodyC::Unselect(int &id) {
    Manager.Queue(Trigger(CListC(*this),&CListC::GUIUnselect,id));
    return true;
  }

  //: Remove all entries from the selection.
  
  bool CListBodyC::UnselectAll() {
    Manager.Queue(Trigger(CListC(*this),&CListC::GUIUnselectAll));
    return true;
  }

  //: Add all entries to the selection.
  
  bool CListBodyC::SelectAll() {
    Manager.Queue(Trigger(CListC(*this),&CListC::GUISelectAll));
    return true;
  }

  //: Move the row with the given id to the rowNo .
  
  bool CListBodyC::GUIMoveID2Row(int &id,int &rowNo) {
    if(widget == 0) {
      // FIXME:- This should be handled properly.
      ONDEBUG(cerr << "WARNING: CListBodyC::GUIMoveID2Row() called before widget created. \n");
      // Find the data we want to move.
      DLIterC<Tuple2C<IntT,SArray1dC<CListCellC> > > it(data);
      for(;it && (it.Data().Data1() != id);it++) ;
      if(!it) {
	cerr << "CListBodyC::GUIMoveID2Row(), WARNING: Can't find element with id " << id << "\n";
	return true;
      }
      DLIterC<Tuple2C<IntT,SArray1dC<CListCellC> > > itx(data);
      //if(itx == it)
      //continue; // Already there.
      itx.Nth(rowNo);
      itx.MoveBef(it);
      return true;
    }
    int newRowNo = gtk_clist_find_row_from_data (GTK_CLIST(widget),(void *) id);
    if(rowNo < 0)
      return true; // Not found.
    gtk_clist_row_move(GTK_CLIST(widget),newRowNo,rowNo);
    return true;
  }
  
  //: Move the row with the given id to the rowNo .
  
  bool CListBodyC::MoveID2Row(int id,int rowNo) {
    Manager.Queue(Trigger(CListC(*this),&CListC::GUIMoveID2Row,id,rowNo));
    return true;
  }

  //: Stop rendering updates to CList.
  // Calling this before doing many changes to the list
  // and then calling Thaw() will speed up the updates.
  bool CListBodyC::Freeze() {
    Manager.Queue(Trigger(CListC(*this),&CListC::GUIFreeze));    
    return true;
  }
  
  //: Stop rendering updates to CList.
  // Calling this before doing many changes to the list
  // and then calling Thaw() will speed up the updates.
  bool CListBodyC::GUIFreeze() {
    if(widget == 0) 
      return true;    
    gtk_clist_freeze(GTK_CLIST(widget));
    return true;
  }
  
  //: Start rendering updates to CList.
  bool CListBodyC::Thaw() {
    Manager.Queue(Trigger(CListC(*this),&CListC::GUIThaw));
    return true;
  }
  
  //: Start rendering updates to CList.
  bool CListBodyC::GUIThaw() {
    if(widget == 0) 
      return true;
    gtk_clist_thaw(GTK_CLIST(widget));
    return true;
  }

  //: Clear all entries from the list.
  
  bool CListBodyC::Clear() {
    Manager.Queue(Trigger(CListC(*this),&CListC::GUIClear));
    return true;
  }
  
  //: Clear all entries from the list.
  
  bool CListBodyC::GUIClear() {
    if(widget == 0) {
      data.Empty();
      return true;
    }
    gtk_clist_clear(GTK_CLIST(widget));    
    return true;
  }
  
  //: Find row ID at position.
  
  IntT CListBodyC::GUIFindRowID(const Index2dC &at) {
    if(widget == 0)
      return 0;
    IntT row,col;
    gtk_clist_get_selection_info (GTK_CLIST(widget),at[0].V(),at[1].V(),&row,&col);
    return  (IntT) gtk_clist_get_row_data(GTK_CLIST(widget),row);
  }
  
  //: Undo all references.
  
  void CListBodyC::Destroy() {
    WidgetBodyC::Destroy(); 
  }


}
