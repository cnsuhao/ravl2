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

#define RAVL_USE_GTKTHREADS RAVL_OS_WIN32  /* Use thread based event handling stratagy. */
#define RAVL_USE_GTKDIRECT  RAVL_OS_WIN32

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

#if RAVL_USE_GTKTHREADS
#include <glib/gthread.h>
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
      guiThreadID1((UIntT)-1),
      guiThreadID2((UIntT)-1)
  {
    InitDone() = true;
#if !RAVL_USE_GTKTHREADS
    int p[2];
    if(pipe(p) != 0) {
      perror("ManagerC::ManagerC(), Failed. \n");
      exit(0);
    }
    ifp = p[0];
    ofp = p[1];
    ONDEBUG(cerr << "ManagerC::ManagerC(), Using piped event queue. \n");
#else
#if RAVL_USE_GTKDIRECT 
    ONDEBUG(cerr << "ManagerC::ManagerC(), Using direct execution event handler. \n");
#else
    ONDEBUG(cerr << "ManagerC::ManagerC(), Using threaded event queue. \n");
#endif
#endif
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
#if !RAVL_USE_GTKTHREADS
    close(ifp);
    close(ofp);
    ifp = -1;
    ofp = -1;
#endif
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
    ONDEBUG(cerr << "ManagerC::Init(), Called. \n");
    RavlAssert(!initCalled); // Init should only be called once.

#if  RAVL_USE_GTKTHREADS
    g_thread_init(0);
    gdk_threads_init();
#endif
    
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
    ONDEBUG(cerr << "ManagerC::Init(), Done. \n");
  }
  
  
#if !RAVL_USE_GTKTHREADS
  static gboolean manager_input_callback(GIOChannel   *source,
					 GIOCondition  condition,
					 gpointer      data) {
    //cerr << "input_callback(), Called. \n";
    ManagerC &manager =  *((ManagerC *) data);
    if (condition & G_IO_IN)
      manager.HandleNotify();
    return true;
  }
#endif
  
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
    ONDEBUG(cerr << "ManagerC::Start(), Called.\n");
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
    
#if  RAVL_USE_GTKTHREADS
    // Get screen size from GDK
    gdk_threads_enter();
    screensize.Set(gdk_screen_height(),gdk_screen_width());
    physicalScreensize = Point2dC(gdk_screen_height_mm(),gdk_screen_width_mm());
    gdk_threads_leave();
    
    guiThreadID1 = ThisThreadID();
#if !RAVL_USE_GTKDIRECT    
    LaunchThreadR(*this,&ManagerC::HandleNotify);
#else
    startupDone.Post();
#endif
    ONDEBUG(cerr << "ManagerC::Start(), Starting gtk_main().\n");
    gdk_threads_enter();
    gtk_main();
    gdk_threads_leave();
    ONDEBUG(cerr << "ManagerC::Start(), gtk_main() Done.\n");
#else
    // Get screen size from GDK
    screensize.Set(gdk_screen_height(),gdk_screen_width());
    physicalScreensize = Point2dC(gdk_screen_height_mm(),gdk_screen_width_mm());
    
    // Setup IO...
    
    guiThreadID1 = ThisThreadID();
    GIOChannel *channel = g_io_channel_unix_new(ifp);
    g_io_add_watch_full(channel,G_PRIORITY_DEFAULT_IDLE+10,G_IO_IN,manager_input_callback, this,0);
    g_io_channel_unref (channel);
    
    startupDone.Post();
    
    // Pass control over to GTK.
    
    gtk_main ();
#endif
    
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
#if RAVL_USE_GTKTHREADS
    Queue(TriggerC());
#else
    Notify(0);
#endif
    return true;
  }
  
  void ManagerC::Quit() { 
#if RAVL_USE_GTKTHREADS
    Queue(TriggerC());
    Queue(TriggerC());
#else
    Notify(0);
    Notify(0);
#endif
  }
  
  //: Notify interface of event.
  
  bool ManagerC::Notify(IntT id) {
#if !RAVL_USE_GTKTHREADS
    if(write(ofp,&id,sizeof(IntT)) != sizeof(id)) {
      perror("ManagerC::Notify(),  Failed ");
      return false;
    }
#endif
    return true;
  }
  
  
  //: Handle notify request.
  
  bool ManagerC::HandleNotify() {
#if RAVL_USE_GTKTHREADS
    guiThreadID2 = ThisThreadID();
    ONDEBUG(cerr << "ManagerC::HandleNotify(), Started. ThreadID1=" << guiThreadID1 << " ThreadID2=" << guiThreadID2 << "\n");
    startupDone.Post();
    Sleep(0.2);
    while(!shutdownFlag) {
      TriggerC trig = events.Get();
      if(!trig.IsValid()) { // Shutdown notification ?
	gtk_main_quit ();
	break;      
      }
      gdk_threads_enter();
      ONDEBUG(cerr << "ManagerC::HandleNotify(), Event Start... \n");
      trig.Invoke();
      ONDEBUG(cerr << "ManagerC::HandleNotify(), Event Finished.. \n");
      gdk_threads_leave();
    }
    ONDEBUG(cerr << "ManagerC::HandleNotify(), Done. \n");
#else
    IntT r;
    if(read(ifp,&r,sizeof(IntT)) != sizeof(IntT)) {
      perror("ManagerC::HandleNotify(),  Failed ");
      return false;
    }
    ONDEBUG(cerr << "ManagerC::HandleNotify() Called on " << r << " Started.\n");
    if(r == 0) { // Shutdown request ?
      gtk_main_quit ();
      return true;
    }
    if(r == 1) {
      eventProcPending = false;
      TriggerC trig;
      while(events.TryGet(trig))
	trig.Invoke();
      return true;
    }
    ONDEBUG(cerr << "ManagerC::HandleNotify() Called on " << r << " Done.\n");
#endif
    return true;
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
#if RAVL_USE_GTKDIRECT    
    if(IsGUIThread()) {
      ONDEBUG(cerr << "ManagerC::Queue(), Event Start... \n");
      if(se.IsValid())
	const_cast<TriggerC &>(se).Invoke();
      else 
	gtk_main_quit ();
      ONDEBUG(cerr << "ManagerC::Queue(), Event Finished.. \n");
    } else {
      
      gdk_threads_enter();
      // Mark this thread as being GUI.
      UIntT oldId = guiThreadID2;
      guiThreadID2 = ThisThreadID();
      
      ONDEBUG(cerr << "ManagerC::Queue(), Event Start... \n");
      if(se.IsValid())
	const_cast<TriggerC &>(se).Invoke();
      else
	gtk_main_quit ();
      
      // Unmark the current thread.
      guiThreadID2 = oldId;
      ONDEBUG(cerr << "ManagerC::Queue(), Event Finished.. \n");
      gdk_threads_leave();      
    }
#else
    if(shutdownFlag) {
      cerr << "ManagerC::Queue(), WARNING: Called after shutdown started. \n";
      return ;
    }
    if(!events.TryPut(se)) {
      ONDEBUG(cerr << "ManagerC::Queue(), WARNING: Event queue full. \n");
      if(!IsGUIThread()) // Are we running in the GUI thread?
	events.Put(se); // Nope, just wait...
      else {
	do {
	  events.Get().Invoke();
	} while(!events.TryPut(se)) ;
      }
    }
#if RAVL_USE_GTKTHREADS
    if(!eventProcPending) {
      eventProcPending = true;
      Notify(1);
    }
#endif
#endif
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
    static TimedTriggerQueueC teQueue(true);
    teQueue.Schedule(t,se);
  }
  
  //: Test if we're in the GUI thread.
  
  bool ManagerC::IsGUIThread() const { 
    UIntT cid = ThisThreadID();
    // Only one of either the native gtk thread or event handling
    // thread will be in GUI code at a time. So if we're on either 
    // we've got an exclusive lock on gtk functions.
    return !managerStarted || guiThreadID1 == cid || guiThreadID2 == cid; 
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
