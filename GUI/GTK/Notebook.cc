// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/Notebook.cc"
//! docentry="Ravl.GUI.Layout"
//! userlevel=Normal

#include "Ravl/GUI/Notebook.hh"
#include "Ravl/GUI/PackInfo.hh"
#include "Ravl/GUI/Label.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/ReadBack.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/Stream.hh"
#include <gtk/gtk.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {

  //: Default constructor.
  
  NotebookBodyC::NotebookBodyC(GtkPositionType ntabpos,bool nshowtabs,bool nshowborder)
    : tabpos(ntabpos),
      showborder(nshowborder),
      showtabs(nshowtabs)
  {}
  
  //: Constructor
  
  NotebookBodyC::NotebookBodyC(const DListC<WidgetC> &widges,GtkPositionType ntabpos,bool nshowtabs,bool nshowborder)
    : ContainerWidgetBodyC(widges),
      tabpos(ntabpos),
      showborder(nshowborder),
      showtabs(nshowtabs)
  {}
  
  //: Constructor
  
  NotebookBodyC::NotebookBodyC(const WidgetC &widges,GtkPositionType ntabpos,bool nshowtabs,bool nshowborder)
    : tabpos(ntabpos),
      showborder(nshowborder),
      showtabs(nshowtabs)
  { children.InsLast(widges); }
  
  //: Create the widget.
  
  bool NotebookBodyC::Create() {
    if(widget != 0)
      return true;
    
    widget = gtk_notebook_new();
    gtk_notebook_set_tab_pos (GTK_NOTEBOOK (widget),tabpos);  
    if(!showtabs)
      gtk_notebook_set_show_tabs(GTK_NOTEBOOK (widget), showtabs);
    if(!showborder)
      gtk_notebook_set_show_border(GTK_NOTEBOOK (widget), showborder);
    
    gtk_widget_show(widget);
    MutexLockC lock(access);
    for(DLIterC<WidgetC> it(children);it;it++) {
      WidgetC tab;    
      // Check we have a tab widget.
      if(tabWidges.IsElm(*it))
	tab = tabWidges[*it];
      if(!tab.IsValid()) {
	tab = LabelC("Tmp...");
	tabWidges[*it] = tab;
      }
      FixupPage(*it,tab);
    }
    lock.Unlock();
    ConnectSignals();
    return true;
  }
  
  //: Undo all references.
  
  void NotebookBodyC::Destroy() {
    DListC<WidgetC> keys;
    for(HashIterC<WidgetC,WidgetC> it(tabWidges);it;it++) {
      it.Data().Destroy();
      keys += it.Key();
    }
    for(DLIterC<WidgetC> it(keys);it;it++) 
      it.Data().Destroy();
    tabWidges.Empty();
    children.Empty();
    WidgetBodyC::Destroy();
  }

  //: Setup tab widgets.
  // GUI Thread only.
  
  bool NotebookBodyC::GUISetTab(const WidgetC &parent,const WidgetC &tabw) { 
    tabWidges[parent] = tabw; 
    return true;
  }
  
  //: Remove page number 'pageNo'
  // GUI Thread only.
  
  bool NotebookBodyC::GUIRemovePage(IntT &pageNo) {
    if(widget == 0) {
      cerr << "NotebookBodyC::GUIRemovePage(), ERROR: Called before widget initalised. \n";
      return true;
    }
    gtk_notebook_remove_page(GTK_NOTEBOOK (widget),pageNo);
    return true;
  }
  
  
  //: Remove page number 'pageNo'
  
  void NotebookBodyC::RemovePage(IntT &pageNo) {
    Manager.Queue(Trigger(NotebookC(*this),&NotebookC::GUIRemovePage,pageNo));
  }
  
  
  //: Remove page number 'pageNo'
  // GUI Thread only.
  
  bool NotebookBodyC::GUIRemovePageW(WidgetC &page) {
    if(widget == 0) {
      cerr << "NotebookBodyC::GUIRemovePage(), ERROR: Called before widget initalised. \n";
      return true;
    }
    int pageNo = gtk_notebook_page_num(GTK_NOTEBOOK (widget),page.Widget());
    if(pageNo < 0) {
      cerr << "NotebookBodyC::GUIRemovePage(), ERROR: Asked to remove unknown page. \n";
      return true;
    }
    gtk_notebook_remove_page(GTK_NOTEBOOK (widget),pageNo);
    return true;
  }
  
  //: Remove page number 'pageNo'
  
  void NotebookBodyC::RemovePage(WidgetC &pageNo) {
    Manager.Queue(Trigger(NotebookC(*this),&NotebookC::GUIRemovePageW,pageNo));  
  }
  
  //: Do the main bit of AppendPage.
  bool NotebookBodyC::FixupPage(WidgetC &page,WidgetC &tab) {
    if(!page.GUIShow())
      return false;
    if(!tab.GUIShow())
      return false;
    // Add page.
    gtk_notebook_append_page(GTK_NOTEBOOK (widget),page.Widget(),tab.Widget());
    return true;
  }

  //: Append a new page.
  
  bool NotebookBodyC::GUIAppendPage(WidgetC &page,WidgetC &tab) {
    tabWidges[page] = tab;
    MutexLockC lock(access);
    children.InsLast(page);
    lock.Unlock();
    if(widget == 0)
      return true;
    return FixupPage(page,tab);
  }
  
  //: Append a new page.
  
  void NotebookBodyC::AppendPage(const WidgetC &page,const WidgetC &tab) {
    Manager.Queue(Trigger(NotebookC(*this),&NotebookC::GUIAppendPage,
			  const_cast<WidgetC &>(page),const_cast<WidgetC &>(tab))
		  );
  }
  
  //: Show a page from the notebook.
  // GUI Thread only.
  
  bool NotebookBodyC::GUIShowPage(WidgetC &page) {
    if(widget == 0) {
      cerr << "NotebookBodyC::GUIShowPage(), ERROR: Called before widget initalised. \n";
      return true;
    }
    if(page.Widget() == 0)
      page.Create();
    int pageNo = gtk_notebook_page_num(GTK_NOTEBOOK (widget),page.Widget());
    if(pageNo < 0) {
      ONDEBUG(cerr << "NotebookBodyC::GUIShowPage(), Initalising page. \n");
      WidgetC tab;    
      // Check we have a tab widget.
      if(tabWidges.IsElm(page))
	tab = tabWidges[page];
      if(!tab.IsValid()) {
	tab = LabelC("Tmp...");
	tabWidges[page] = tab;
      }
      GUIAppendPage(page,tab);
      pageNo = gtk_notebook_page_num(GTK_NOTEBOOK (widget),page.Widget());
      if(pageNo < 0) {
	cerr << "NotebookBodyC::GUIShowPage(), Failed to find page for widget. \n";
	return true;
      }
    }
    ONDEBUG(cerr << "NotebookBodyC::GUIShowPage(), Showing " << pageNo << "\n");
    gtk_notebook_set_page(GTK_NOTEBOOK (widget),pageNo);
    return true;
  }
  
  //: Show a page from the notebook.
  
  void NotebookBodyC::ShowPage(WidgetC &page) {
    Manager.Queue(Trigger(NotebookC(*this),&NotebookC::GUIShowPage,page));
  }
  
  //: Get the id of the current page being displayed.
  IntT NotebookBodyC::GetCurrentPage() {
    ReadBackLockC readBackLock; // Lock the GUI thread.
    return gtk_notebook_get_current_page(GTK_NOTEBOOK (widget));
  }
  
  ///////////////////////////////////////////
  
  //: Default constructor
  
  NotebookC::NotebookC()
  {}
}
