// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/Manager.cc"

#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/ToolTips.hh"
#include "Ravl/Threads/LaunchThread.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/Threads/TimedTriggerQueue.hh"

//#include "Ravl/GUI/Label.hh"
#if RAVL_HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef WIN32
#include <io.h>
#include <fcntl.h>
#endif

#include <gtk/gtk.h>
#include <gdk/gdkrgb.h>
#include <stdio.h>
#include <glib.h>
#include <stdlib.h>

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  
  ManagerC Manager;
  
  extern "C" {   
    void manager_input_callback(gpointer data,gint,GdkInputCondition);
    gint timeout_callback( gpointer data );
  };
  
  //: Default constructor.
  
  ManagerC::ManagerC()
    : events(20),
      eventProcPending(false),
      idc(3),
      initCalled(false),
      managerStarted(false),
      shutdownFlag(false),
      guiThreadID(0)
  {
    InitDone() = true;
    int p[2];
    if(pipe(p) != 0) {
      perror("ManagerC::ManagerC(), Failed. \n");
      exit(0);
    }
    ifp = p[0];
    ofp = p[1];
  } 
  
  
  //: Tidy up before exiting..
  
  void ManagerC::TidyUp() {
    if(shutdownFlag)
      return ;
    shutdownFlag = true;
    while(!wins.IsEmpty()) {
      WidgetC awin;
      int key;
      {
	HashIterC<IntT,WidgetC> it(wins);
	awin = it.Data();
	key = it.Key();
      }
      awin.Destroy();
      wins.Del(key); // Make sure its removed...
    }
    ONDEBUG(cerr << "ManagerC::~ManagerC(), Removing final reference to root win.. \n");
    
    delayEvents.Empty();
    close(ifp);
    close(ofp);
    ifp = -1;
    ofp = -1;
  }
  
  //: Desructor.
  
  ManagerC::~ManagerC() {
    ONDEBUG(cerr << "ManagerC::~ManagerC(), Started. \n");
    TidyUp();
    if(startupDone) {
      startupDone.WaitForFree();
      if(shutdownDone)
	shutdownDone.WaitForFree();
      else {
	cerr << "ERROR: Destroying manager before shutdown occured. \n";
      }
    } else {
      if(startupDone.ThreadsWaiting() > 0)
	cerr << "ERROR: Destroying manager before its event statered, (Threads wating) \n";
    }
    
    ONDEBUG(cerr << "ManagerC::~ManagerC(), Done.. \n");
  }
  
  //: Initalise system.
  
  void ManagerC::Init(int &nargs,char *args[])  {
    RavlAssert(!initCalled); // Init should only be called once.
    /* this is called in all GTK applications.  arguments are parsed from
     * the command line and are returned to the application. */
    gtk_init (&nargs, &args);
    
    initCalled = true;
    
    //gdk_rgb_set_verbose (true);
    gdk_rgb_init ();  
    gtk_widget_set_default_colormap (gdk_rgb_get_cmap ());
    gtk_widget_set_default_visual (gdk_rgb_get_visual ());
    if(!guiGlobalToolTips.Create())
      cerr << "ManagerC::Init(), ERROR : Failed to creat global tool tips. \n";
  }
  
  
  static gboolean manager_input_callback(GIOChannel   *source,
					 GIOCondition  condition,
					 gpointer      data) {
    //cerr << "input_callback(), Called. \n";
    ManagerC &manager =  *((ManagerC *) data);
    if (condition & G_IO_IN)
      manager.HandleNotify();
    return true;
  }
  
  bool StartFunc() {
    Manager.Start();  
    return true;
  }
  
  //: Start manager on seperate thread.
  // Call only ONCE.
  
  void ManagerC::Execute() {
    if(managerStarted) {
      cerr << "ManagerC::Execute(), WARNING: Manager already started. \n";
      return ;
    }
    LaunchThread(Trigger(StartFunc)); // Bit of a hack, but it'll do.
  }
  
  //: Handle over control to manager.
  
  void ManagerC::Start()  {
    // Make sure only one manager is started...
    
    MutexLockC lock(access);
    if(managerStarted) {
      cerr << "ManagerC::Start(), WARNING: Manager already started. \n";
      return ;
    }
    managerStarted = true;
    lock.Unlock();
    
    // Check setup is done...
    
    if(!initCalled) {
      static int nargs = 2;
      static char *args[3] = {"aprog","arg",0 };
      Init(nargs, args);
    }
    
    // Get screen size from GDK
    screensize.Set(gdk_screen_height(),gdk_screen_width());
    physicalScreensize = Point2dC(gdk_screen_height_mm(),gdk_screen_width_mm());
    // Setup IO...
    
    guiThreadID = ThisThreadID();
    GIOChannel *channel = g_io_channel_unix_new(ifp);
    g_io_add_watch_full(channel,G_PRIORITY_DEFAULT_IDLE+10,G_IO_IN,manager_input_callback, this,0);
    g_io_channel_unref (channel);
  
    startupDone.Post();
    
    // Pass control over to GTK.
    
    gtk_main ();
  
    managerStarted = false;
    
    shutdownDone.Post();  
    ONDEBUG(cerr << "ManagerC::Start(), Start tidy.... \n");
    TidyUp();
    ONDEBUG(cerr << "ManagerC::Start(), Start done.... \n");
    
  }
  
  //: Wait for the GUI to be shutdown by the user.
  
  bool ManagerC::Wait() {
    shutdownDone.Wait();
    return true;
  }

  //: Wait for the GUI to be started.
  
  bool ManagerC::WaitForStartup()  {
    startupDone.Wait();
    return true;
  }
  
  //: Finishup and exit.
  
  bool ManagerC::Shutdown() {
    Notify(0);
    return true;
  }
  
  void ManagerC::Quit() { 
    Notify(0); 
    Notify(0); 
  }
  
  //: Notify interface of event.
  
  bool ManagerC::Notify(IntT id) {
    if(write(ofp,&id,sizeof(IntT)) != sizeof(id)) {
      perror("ManagerC::Notify(),  Failed ");
      return false;
    }
    return true;
  }
  
  
  //: Handle notify request.
  
  void ManagerC::HandleNotify() {
    IntT r;
    if(read(ifp,&r,sizeof(IntT)) != sizeof(IntT)) {
      perror("ManagerC::HandleNotify(),  Failed ");
      return ;
    }
    ONDEBUG(cerr << "ManagerC::HandleNotify() Called on " << r << " Started.\n");
    if(r == 0) { // Shutdown request ?
      gtk_main_quit ();
      return ;
    }
    if(r == 1) {
      eventProcPending = false;
      TriggerC trig;
      while(events.TryGet(trig))
	trig.Invoke();
      return ;
    }
    ONDEBUG(cerr << "ManagerC::HandleNotify() Called on " << r << " Done.\n");
  }
  
  //: Access window.
  
  WindowC &ManagerC::GetRootWindow() {
    static WindowC rootWin;
    return rootWin;
  }
  
  
  //: Access init flag.
  
  bool &ManagerC::InitDone() {
    static bool initDone = false;
    return initDone;
  }
  
  //: Set root window.
  
  void ManagerC::SetRootWindow(WindowC &nw) {
    GetRootWindow() = nw;
  }
  
  //: Queue an event for running in the GUI thread.
  
  void ManagerC::Queue(const TriggerC &se) {
    if(shutdownFlag) {
      cerr << "ManagerC::Queue(), Called after shutdown started. \n";
      return ;
    }
    if(!events.TryPut(se)) {
      if(!IsGUIThread()) // Are we running in the GUI thread?
	events.Put(se); // Nope, just wait...
      else {
	do {
	  events.Get().Invoke();
	} while(!events.TryPut(se)) ;
      }
    }
    if(!eventProcPending) {
      eventProcPending = true;
      Notify(1);
    }
  }
  
  static bool doUnrefPixmap(GdkPixmap *&pixmap) {
    gdk_pixmap_unref(pixmap);  
    return true;
  }
  
  //: Ensure that an unref takes place for pixmap on the GUIThread.
  
  void ManagerC::UnrefPixmap(GdkPixmap *pixmap) {
    if(IsGUIThread()) {  // Do this ASAP, to free space in the X server.
      gdk_pixmap_unref(pixmap);
      return ;
    }
    Queue(Trigger(&doUnrefPixmap,pixmap));
  }
  
  
  //: Queue an event for running in the GUI thread after delay 't'.
  
  void ManagerC::Queue(RealT t,const TriggerC &se) {
    if(shutdownFlag) {
      cerr << "ManagerC::Queue(), Called after shutdown started. \n";
      return ;
    }
    TimedTriggerQueueC teQueue(true);
    teQueue.Schedule(t,se);
  }
  
  //: Test if we're in the GUI thread.
  
  bool ManagerC::IsGUIThread() const {
    return !managerStarted || guiThreadID == ThisThreadID();
  }
  
  //: Register new window.
  
  IntT ManagerC::Register(WidgetBodyC &win) {
    if(shutdownFlag) {
      cerr << "ManagerC::Register(), Called after shutdown started. \n";
      return 0;
    }
    MutexLockC lock(access);
    int nid = idc++;
    wins[nid] = WidgetC(win);
    RavlAssert(wins[nid].IsValid());
    return nid;
  }
  
  //: Deregister widget.
  
  void ManagerC::Deregister(IntT widgeID) {
    if(widgeID == 0)
      return ;
    ONDEBUG(cerr << "ManagerC::Deregister() WidgetID " << widgeID << " Started. \n");
    MutexLockC lock(access);
    wins.Del(widgeID);
    ONDEBUG(cerr << "ManagerC::Deregister() WidgetID " << widgeID << " Done. \n");
  }
  
  //: Deregister new window.
  
  void ManagerC::Deregister(WidgetBodyC &win) {
    if(win.WidgetID() == 0)
      return ;
    int tmpID = win.WidgetID();
    ONDEBUG(cerr << "ManagerC::Deregister() WidgetID " << tmpID << " Started. (" << &win << ") \n");
    win.widgetId = 0; // Stop recursions!
    MutexLockC lock(access);
    wins.Del(tmpID);
    ONDEBUG(cerr << "ManagerC::Deregister() WidgetID " << tmpID << " Done. (" << &win << ") \n");
  }

}
