// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////
//! docentry="GUI"
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/CWidget.cc"

#include "Ravl/GUI/CWidget.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/DLIter.hh"
#include "Ravl/CDLIter.hh"
#include "Ravl/CallMethods.hh"
#include <gtk/gtk.h>

namespace RavlGUIN {

  //: Create the widget.
  
  bool ContainerWidgetBodyC::Create() {
    MutexLockC lock(access);
    for(DLIterC<WidgetC> it(children);it.IsElm();it.Next()) 
      it.Data().Create();
    return true;
  }
  
  //: Undo all refrences.
  // Used to avoid problems with circluar refrences.
  // This should undo all refrences to RAVL and GUI
  // objects which are not in the destroy tree. 
  // The function is called by the root window in its
  // destructor.
  
  void ContainerWidgetBodyC::Destroy() {
    for(DLIterC<WidgetC> it(children);it.IsElm();it.Next()) 
      it.Data().Destroy();
    WidgetBodyC::Destroy();
  }
  
  //: Add widget.
  // GUI thread only.
  
  bool ContainerWidgetBodyC::GUIAdd(WidgetC &widge) {
    MutexLockC lock(access);
    if(widget == 0) {
      cerr << "ContainerWidgetBodyC::GUIAdd(), ERROR: Widget not created. \n";
      return true;
    }
    RavlAssert(widge.IsValid());
    if(widge.Widget() == 0) {
      if(!widge.Create()) {
	cerr << "ContainerWidgetBodyC::Create(), Widget create failed ! \n";
	return true;
      }
    }
    gtk_container_add(GTK_CONTAINER(widget),widge.Widget());
    return true;
  }
  
  //: Add child widget.
  
  bool ContainerWidgetBodyC::Add(const WidgetC &widge) {
    MutexLockC lock(access);
    children.InsLast(widge);
    if(widget == 0)
      return true; // Done !
    lock.Unlock();
    Manager.Queue(Trigger(ContainerWidgetC(*this),&ContainerWidgetC::GUIAdd,widge));
    return true;
  }
  
  //: Remove a child widget.
  
  bool ContainerWidgetBodyC::Remove(WidgetC &widge)  {
    MutexLockC lock(access);
    for(DLIterC<WidgetC> it(children);it.IsElm();it.Next()) {
      if(it.Data() == widge) {
	it.Del();
	break;
      }
    }
    if(widget == 0)
      return true; // Done !
    gtk_container_remove(GTK_CONTAINER(widget),widge.Widget());
    return true;
  }
  
  //: Add children.
  
  bool ContainerWidgetBodyC::Add(const DListC<WidgetC> &widges) {
    for(ConstDLIterC<WidgetC> it(widges);it.IsElm();it.Next())
      Add(it.Data());
    return true;
  }
  
}





