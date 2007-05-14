// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/Widget.cc"

#include "Ravl/GUI/Widget.hh"
#include "Ravl/GUI/WidgetStyle.hh"
#include "Ravl/String.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/SignalInfo.hh"
#include "Ravl/GUI/ToolTips.hh"
#include "Ravl/GUI/MouseEvent.hh"
#include "Ravl/GUI/DragAndDrop.hh"
#include "Ravl/CallMethods.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/Threads/Signal2.hh"
#include "Ravl/Threads/Signal3.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/GUI/TreeModel.hh"
#include "Ravl/GUI/ReadBack.hh"
#include "WidgetDNDInfo.hh"
#include <gtk/gtk.h>
#include <gdk/gdktypes.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  
  using namespace RavlImageN;
  
  int WidgetBodyC::gtkDestroy (GtkWidget *widget,WidgetBodyC * data) { 
    ONDEBUG(cerr << "Got destroy for widget : " << ((void *) data) << "\n");
    data->WidgetDestroy(); 
    return 1;
  }

  // How to add a new signal:
  //
  // 1) Check if a method with a suitable prototype already exists
  //    the names of the functions can be seen in the list of defines below, with
  //    a WidgetBodyC:: before them. If it does skip to step 6. 
  // 2) Add a new signal type to SignalTypeT in SignalInfo.hh 
  // 3) Write a new function to convert the gtk signal into a c++ one.
  //    an example is WidgetBodyC::gtkEventMouseMotion(..)
  // 4) Add your new enumerated type to the switch statement in WidgetBodyC::Signal(const char *nm)
  //    its here you create the SignalC you want to use. Its also a good place to do any general 
  //    configuration needed BEFORE the widget is created.
  // 5) If you need to do any configuration after the widget has been created, then 
  //    WidgetBodyC::ConnectSignals() is the place to put this. Note: This is for generic stuff.
  //    widget specific code should be put in the class for that widget.
  // 6) Add a line to the signalInfo[] list
  //    in SigInfoInit().  i.e. GTKSIG("some_event"         ,GTKSIG_EVENT   ),
  // 7) Done!

#define GTKSIG(name,type) Tuple2C<const char *,GTKSignalInfoC>(name,GTKSignalInfoC(name,type))
#define GTKSIG_GENERIC (GtkSignalFunc) WidgetBodyC::gtkGeneric,SigTypeGeneric
#define GTKSIG_EVENT   (GtkSignalFunc) WidgetBodyC::gtkEvent,SigTypeEvent 
#define GTKSIG_EVENTDELETE (GtkSignalFunc) WidgetBodyC::gtkEventDelete,SigTypeEventDelete
#define GTKSIG_EVENT_MOUSEBUTTON   (GtkSignalFunc) WidgetBodyC::gtkEventMouseButton,SigTypeEventMouseButton
#define GTKSIG_EVENT_MOUSEMOTION   (GtkSignalFunc) WidgetBodyC::gtkEventMouseMotion,SigTypeEventMouseMotion 
#define GTKSIG_STRING   (GtkSignalFunc) WidgetBodyC::gtkString,SigTypeString
#define GTKSIG_CLISTSEL (GtkSignalFunc) WidgetBodyC::gtkCListSelect,SigTypeCListSel
#define GTKSIG_CLISTCOL (GtkSignalFunc) WidgetBodyC::gtkCListCol,SigTypeCListCol
#define GTKSIG_TERM    0,SigTypeUnknown
#define GTKSIG_KEYBOARD (GtkSignalFunc) WidgetBodyC::gtkEventKeyboard,SigTypeEventKeyboard
#define GTKSIG_DNDCONTEXT      (GtkSignalFunc) WidgetBodyC::gtkDNDContext,SigTypeDNDContext
#define GTKSIG_DNDPOSITION     (GtkSignalFunc) WidgetBodyC::gtkDNDPosition,SigTypeDNDPosition
#define GTKSIG_DNDLEAVE        (GtkSignalFunc) WidgetBodyC::gtkDNDContextTime,SigTypeDNDPosition
#define GTKSIG_DNDDATAGET      (GtkSignalFunc) WidgetBodyC::gtkDNDDataGet,SigTypeDNDData
#define GTKSIG_DNDDATARECIEVED (GtkSignalFunc) WidgetBodyC::gtkDNDDataRecieved,SigTypeDNDData
#define GTKSIG_INT      (GtkSignalFunc) WidgetBodyC::gtkInt,SigTypeInt
#define GTKSIG_WIDGET_INT (GtkSignalFunc) WidgetBodyC::gtkWidgetInt,SigTypeWidgetInt
#define GTKSIG_TREEROW (GtkSignalFunc) WidgetBodyC::gtkTreeRow,SigTypeTreeRow
#define GTKSIG_TREEPATHCOL (GtkSignalFunc) WidgetBodyC::gtkTreePathCol,SigTypeTreePathCol
#define GTKSIG_TREEPATH (GtkSignalFunc) WidgetBodyC::gtkTreePath,SigTypeTreePath

  //: Get init information about signals.

  Tuple2C<const char *,GTKSignalInfoC> *WidgetBodyC::SigInfoInit() {
    static Tuple2C<const char *,GTKSignalInfoC> signalInfo [] = {
      // Don't move "destroy", needed to terminate initaliser list.
      GTKSIG("destroy"              ,GTKSIG_GENERIC ), // gtkwidget 
      GTKSIG("event"                ,GTKSIG_EVENT   ), // gtkwidget
      GTKSIG("button_press_event"   ,GTKSIG_EVENT_MOUSEBUTTON ), // gtkwidget
      GTKSIG("button_release_event" ,GTKSIG_EVENT_MOUSEBUTTON ), // gtkwidget
      GTKSIG("motion_notify_event"  ,GTKSIG_EVENT_MOUSEMOTION ), // gtkwidget
      GTKSIG("delete_event"         ,GTKSIG_EVENTDELETE   ), // gtkwidget
      GTKSIG("expose_event"         ,GTKSIG_EVENT   ), // gtkwidget
      GTKSIG("key_press_event"      ,GTKSIG_KEYBOARD), // gtkwidget
      GTKSIG("key_release_event"    ,GTKSIG_KEYBOARD), // gtkwidget
      GTKSIG("enter_notify_event"   ,GTKSIG_EVENT   ), // gtkwidget
      GTKSIG("leave_notify_event"   ,GTKSIG_EVENT   ), // gtkwidget
      GTKSIG("configure_event"      ,GTKSIG_EVENT   ), // gtkwidget
      GTKSIG("scroll_event"         ,GTKSIG_EVENT   ), // gtkwidget
      GTKSIG("hide"                 ,GTKSIG_GENERIC ), // gtkwidget
      GTKSIG("show"                 ,GTKSIG_GENERIC ), // gtkwidget
      GTKSIG("map"                  ,GTKSIG_GENERIC ), // gtkwidget
      GTKSIG("unmap"                ,GTKSIG_GENERIC ), // gtkwidget
      GTKSIG("activate"             ,GTKSIG_GENERIC ), // gtkmenu
      GTKSIG("toggled"              ,GTKSIG_GENERIC ), // gtktogglebutton
      GTKSIG("pressed"              ,GTKSIG_GENERIC ), // gtkbutton
      GTKSIG("released"             ,GTKSIG_GENERIC ), // gtkbutton
      GTKSIG("clicked"              ,GTKSIG_GENERIC ), // gtkbutton
      GTKSIG("enter"                ,GTKSIG_GENERIC ), // gtkbutton
      GTKSIG("leave"                ,GTKSIG_GENERIC ), // gtkbutton
      GTKSIG("select"               ,GTKSIG_GENERIC ), // gtkitem
      GTKSIG("deselect"             ,GTKSIG_GENERIC ), // gtkitem
      GTKSIG("toggled"              ,GTKSIG_GENERIC ), // gtkitem
      GTKSIG("collapse"             ,GTKSIG_GENERIC ), // gtktreeitem
      GTKSIG("expand"               ,GTKSIG_GENERIC ), // gtktreeitem
      GTKSIG("changed"              ,GTKSIG_GENERIC ), // gtkadjustment
      GTKSIG("value_changed"        ,GTKSIG_GENERIC ), // gtkadjustment
      GTKSIG("selection_changed"    ,GTKSIG_GENERIC ), // 
      GTKSIG("combo_activate"       ,GTKSIG_STRING  ), // String...
      GTKSIG("select_row"           ,GTKSIG_CLISTSEL), // CList
      GTKSIG("unselect_row"         ,GTKSIG_CLISTSEL), // CList
      GTKSIG("click_column"         ,GTKSIG_CLISTCOL), // CList
      GTKSIG("drag_begin"           ,GTKSIG_DNDCONTEXT),     // gtkwidget
      GTKSIG("drag_end"             ,GTKSIG_DNDCONTEXT),     // gtkwidget
      GTKSIG("drag_data_delete"     ,GTKSIG_DNDCONTEXT),     // gtkwidget
      GTKSIG("drag_leave"           ,GTKSIG_DNDLEAVE),       // gtkwidget
      GTKSIG("drag_drop"            ,GTKSIG_DNDPOSITION),    // gtkwidget
      GTKSIG("drag_motion"          ,GTKSIG_DNDPOSITION),    // gtkwidget
      GTKSIG("drag_data_get"        ,GTKSIG_DNDDATAGET),     // gtkwidget
      GTKSIG("drag_data_received"   ,GTKSIG_DNDDATARECIEVED),// gtkwidget
      GTKSIG("change-current-page"  ,GTKSIG_INT),// gtkNotebook
      GTKSIG("switch-page"          ,GTKSIG_WIDGET_INT),     // gtkNotebook
      GTKSIG("row-collapsed"        ,GTKSIG_TREEROW ),       // GtkTreeView
      GTKSIG("row-expanded"         ,GTKSIG_TREEROW ),       // GtkTreeView
      GTKSIG("row-activated"        ,GTKSIG_TREEPATHCOL ),   // GtkTreeView
      GTKSIG("item-activated"       ,GTKSIG_TREEPATH ),  // GtkIconView
      GTKSIG("destroy",GTKSIG_TERM)  // Duplicate first key to terminate array.
    };
    return signalInfo;
  }
  
  static GTKSignalInfoC &tmpSignalInit = WidgetBodyC::SigInfo("show"); // Make sure signal table gets setup before we go multithreaded.
  
  GTKSignalInfoC &WidgetBodyC::SigInfo(const char *nm)  { 
    static HashC<const char *,GTKSignalInfoC> signalTable(WidgetBodyC::SigInfoInit());
    
    return signalTable[nm]; 
  }
  
  int WidgetBodyC::gtkEventMouseButton(GtkWidget *widget,GdkEvent *event,Signal0C *data)  {
    MouseEventC me((GdkEventButton &) *event);
    Signal1C<MouseEventC> sig(*data);
    RavlAssert(sig.IsValid());
    sig(me);
    return 1;
  }
  
  int WidgetBodyC::gtkEventMouseMotion(GtkWidget *widget,GdkEvent *event,Signal0C *data) {
    MouseEventC me((GdkEventMotion &) *event);
    Signal1C<MouseEventC> sig(*data);
    RavlAssert(sig.IsValid());
    sig(me);
    return 1;
  }
  
  int WidgetBodyC::gtkString(GtkWidget *widget,Signal0C *data) {
    Signal1C<StringC> sig(*data);
    RavlAssert(sig.IsValid());
    StringC sendStr(gtk_entry_get_text(GTK_ENTRY(widget)));
    sig(sendStr);
    return 1;
  }
  
  int WidgetBodyC::gtkEvent(GtkWidget *widget,GdkEvent *event,Signal0C *data) { 
    Signal1C<GdkEvent *> sig(*data);
    RavlAssert(sig.IsValid());
    sig(event); 
    return 1;
  }
  
  int WidgetBodyC::gtkEventDelete(GtkWidget *widget,GdkEvent *event,Signal0C *data) 
  { 
    Signal3C<GdkEvent*, WidgetC, bool> sig(*data);
    RavlAssert(sig.IsValid());
    bool ret = true;	//Set the default to true. For "destroy" to be called, set this value to false in the implementation
    sig(event, sig.DefaultValue2(), ret);
    return ret;
  }
  
  int WidgetBodyC::gtkEventKeyboard(GtkWidget *widget,GdkEvent *event,Signal0C *data) { 
    Signal1C<GdkEventKey *> sig(*data);
    RavlAssert(sig.IsValid());
    sig((GdkEventKey *)event); 
    return 1;
  }
  

  int WidgetBodyC::gtkGeneric(GtkWidget *widget,Signal0C *data) 
  { 
    (*data)();
    return 1;
  }
  
  int WidgetBodyC::gtkCListSelect(GtkWidget *widget,
                                  gint row,gint column,
                                  GdkEventButton *event,
                                  Signal0C *data) {
    Signal1C<CListEventC> sig(*data);
    RavlAssert(sig.IsValid());
#if RAVL_OS_LINUX64    
    IntT rowId = (Int64T) gtk_clist_get_row_data(GTK_CLIST(widget),row);
#else
    IntT rowId = (IntT) gtk_clist_get_row_data(GTK_CLIST(widget),row);
#endif

    ONDEBUG(cerr << "WidgetBodyC::gtkCListSelect(), RowID: " << rowId << " Event: " << ((void *) event)  << "\n");
    CListEventC cle(rowId,row,column);
    sig(cle);
    return 1;
  }
  
  int WidgetBodyC::gtkCListCol(GtkWidget *widget,gint column,Signal0C *data)  {
    Signal1C<IntT> sig(*data);
    RavlAssert(sig.IsValid());
    sig(column);
    return 1;
  }

  int WidgetBodyC::gtkDNDContext(GtkWidget *widget,GdkDragContext *context,Signal0C *data) {
    Signal1C<GdkDragContext *> sig(*data);
    RavlAssert(sig.IsValid());
    sig(context);
    return 1;
  }
  
  int WidgetBodyC::gtkDNDContextTime(GtkWidget *widget,GdkDragContext *context,unsigned int time,Signal0C *data) {
    Signal2C<GdkDragContext *,PositionTimeC> sig(*data);
    RavlAssert(sig.IsValid());
    PositionTimeC pt(0,0,time);    
    sig(context,pt);
    return 1;
  }
  
  int WidgetBodyC::gtkDNDPosition(GtkWidget *widget,GdkDragContext *context,int x,int y,unsigned int time,Signal0C *data) {
    Signal2C<GdkDragContext *,PositionTimeC> sig(*data);
    RavlAssert(sig.IsValid());
    PositionTimeC pt(x,y,time);    
    sig(context,pt);
    return 1;
  }
  
  int WidgetBodyC::gtkDNDDataRecieved(GtkWidget *widget,GdkDragContext *context,int x,int y,GtkSelectionData *data,unsigned int info,unsigned int time,Signal0C *sigptr) {
    
    // Do some sanity checks
    if(data == 0) {
      cerr << "WidgetBodyC::gtkDNDDataRecieved(), WARNING: Recieved NULL selection. \n";
      return 1;
    }
    if(data->length < 0) {
      cerr << "WidgetBodyC::gtkDNDDataRecieved(), WARNING: Recieved invalid selection. \n";
      return 1;
    }
    Signal1C<DNDDataInfoC> sig(*sigptr);
    RavlAssert(sig.IsValid());
    DNDDataInfoC inf(context,data,info,time,x,y);
    sig(inf);
    return 1;
  }
  
  int WidgetBodyC::gtkDNDDataGet(GtkWidget *widget,
                                 GdkDragContext *context,
                                 GtkSelectionData *data,
                                 unsigned int info,
                                 unsigned int time,
                                 Signal0C *sigptr) {
    Signal1C<DNDDataInfoC> sig(*sigptr);
    RavlAssert(sig.IsValid());
    DNDDataInfoC inf(context,data,info,time);
    sig(inf);
    return 1;
  }
  
  int WidgetBodyC::gtkInt(GtkWidget *widget,int page, Signal0C *sigptr) {
    Signal1C<IntT> sig(*sigptr);
    RavlAssert(sig.IsValid());
    sig(page);
    return 1;
  }

  int WidgetBodyC::gtkWidgetInt(GtkWidget *widget,GtkWidget *notebookpage, unsigned int page, Signal0C *sigptr) {
    Signal1C<UIntT> sig(*sigptr);
    RavlAssert(sig.IsValid());
    sig(page);
    return 1;
  }

  int WidgetBodyC::gtkTreeRow(GtkWidget *widge, GtkTreeIter *iter, GtkTreePath *path, Signal0C *sigptr) {
    RavlAssert(sigptr != 0);
    // Get signal
    Signal2C<TreeModelIterC,TreeModelPathC> sig(*sigptr);
    RavlAssert(sig.IsValid());
    // Convert data
    TreeModelIterC riter(gtk_tree_view_get_model(GTK_TREE_VIEW(widge)),iter);
    TreeModelPathC rpath(path,false);
    // Send signal
    sig(riter,rpath);
    // Done
    return 1;
  }

  
  int WidgetBodyC::gtkTreePathCol(GtkWidget *widget, GtkTreePath *path, GtkTreeViewColumn *col, Signal0C *sigptr) {
    RavlAssert(sigptr != 0);
    // Get signal
    Signal2C<TreeModelPathC,StringC> sig(*sigptr);
    
    RavlAssert(sig.IsValid());
    // Convert data
    
    TreeModelPathC rpath(path,false);
    StringC name(gtk_tree_view_column_get_title (col));
    
    // Send signal
    sig(rpath,name);
    
    // Done
    return 1;
  }
  
  int WidgetBodyC::gtkTreePath(GtkWidget *widget, GtkTreePath *path, Signal0C *sigptr) {
    RavlAssert(sigptr != 0);
    // Get signal
    Signal1C<TreeModelPathC> sig(*sigptr);
    
    RavlAssert(sig.IsValid());
    // Convert data
    
    TreeModelPathC rpath(path,false);
    
    // Send signal
    sig(rpath);
    
    // Done
    return 1;    
  }


  //: Default constructor.
  
  WidgetBodyC::WidgetBodyC()
    : widget(0),
      widgetId(0),
      eventMask(GDK_EXPOSURE_MASK),
      tooltip(0),
      gotRef(false),
      dndInfo(0),
      destroySigId(-1)
  {}
  
  WidgetBodyC::WidgetBodyC(const char *ntooltip)
    : widget(0),
      widgetId(0),
      eventMask(GDK_EXPOSURE_MASK),
      tooltip(ntooltip),
      gotRef(false),
      dndInfo(0)
  {}
  
  
  //: Destructor.

  WidgetBodyC::~WidgetBodyC() { 
    ONDEBUG(cerr << "WidgetBodyC::~WidgetBodyC(), Started  " << ((void *) this) << " Name=" << GUIWidgetName() << "\n");
    //RavlAssert(IsValidObject());

    // Disconnect signals
    for(HashIterC<const char *,Tuple2C<Signal0C,IntT> > it(signals);it.IsElm();it.Next()) {
      if(widget != 0 && GTK_IS_WIDGET(widget) && it.Data().Data2() >= 0) // Incase it was destroyed within GTK.
        gtk_signal_disconnect (GTK_OBJECT(widget), it.Data().Data2() );
      it.Data().Data1().DisconnectAll();
    }
    signals.Empty();
    
    // Clean up other stuff.
    if(widget != 0) {
      if(GTK_IS_WIDGET(widget)) { // Incase it was destroyed within GTK.
        if(destroySigId >= 0)
          gtk_signal_disconnect (GTK_OBJECT(widget), destroySigId);
        gtk_widget_hide (widget);
        if(gotRef) {
          gtk_object_unref(GTK_OBJECT(widget));
        }
      }
      widget = 0;
    }
    // Have we got some drag and drop info ?
    if(dndInfo != 0) {
      delete dndInfo;
      dndInfo = 0;
    }
    ONDEBUG(cerr << "WidgetBodyC::~WidgetBodyC(), Done.  " << ((void *) this) << "\n");
  }
  
  //: Get widget's name.
  // Call only from GUI thread.
  
  StringC WidgetBodyC::GUIWidgetName() const {
    if(widget == 0)
      return StringC("-Unknown-");
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    const char *nm = gtk_widget_get_name(widget);
    if(nm == 0) {
#if RAVL_OS_LINUX64
      StringC((Int64T) widget); // Use address as dummy.
#else
      StringC((int) widget); // Use address as dummy.
#endif
    }
    return StringC(nm);
  }
  
  StringC WidgetBodyC::Name() const { 
    ReadBackLockC lock;
    return GUIWidgetName(); 
  }
  
  
  //: Create the widget.
  
  bool WidgetBodyC::Create() {
    cerr << "bool WidgetBodyC::Create(), Abstract function called. \n";
    return true;
  }
  
  //: Create with a widget supplied from elsewhere.
  
  bool WidgetBodyC::Create(GtkWidget *newWidget) {
    //cerr << "bool WidgetBodyC::Create(GtkWidget *), Called.. \n";
    widget = newWidget;
    ConnectSignals();
    return false;
  }
  
  //: Set state 
  
  bool WidgetBodyC::GUISetState(GtkStateType state) {
    reqState = state;
    if(widget == 0)
      return true;
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    if(reqState != GTK_WIDGET_STATE(widget)) {
      gtk_widget_set_state(widget,reqState);
      if(reqState != GTK_STATE_INSENSITIVE)
        gtk_widget_set_sensitive(widget,true);
    }
    return true;
  }
  
  
  //: Set state 
  
  void WidgetBodyC::SetState(GtkStateType state) {
    Manager.Queue(Trigger(WidgetC(*this),&WidgetC::GUISetState,state));
  }
  
  void WidgetBodyC::WidgetDestroy() {
    ONDEBUG(cerr << "WidgetBodyC::WidgetDestroy(), Called. \n");
    if(gotRef && widget != 0)
      gtk_object_unref(GTK_OBJECT(widget));  // Not sure if this can happen....
    widget = 0;
  }
  
  //: Get handle for named signal.
  // See handle class for description.
  
  Signal0C &WidgetBodyC::Signal(const char *nm) {
    ReadBackLockC lock;
    Signal0C &ret = signals[nm].Data1();
    if(ret.IsValid()) 
      return ret;
    
    StringC sN(nm); // To make comparison easy.
    GTKSignalInfoC &si = SigInfo(nm);
    switch(si.signalType)
      {
      case SigTypeGeneric: ret = Signal0C(true); break;
      case SigTypeEvent:  
        ret = Signal2C<GdkEvent *,WidgetC>(0,WidgetC(*this)); 
        break;
	
       case SigTypeEventDelete:
       {
         bool bDefault = true;	//Default means that the "destroy" signal is not triggered. 
	 			//To trigger "destroy" set this param to false in calling code
         ret = Signal3C<GdkEvent *,WidgetC, bool>(0,WidgetC(*this), bDefault);
       }
        break;
      case SigTypeEventKeyboard: 
        if(sN == "key_press_event") // Enable press events.
          AddEventMask(GDK_KEY_PRESS_MASK); 
        if(sN == "key_release_event") // Enable Release events.
          AddEventMask(GDK_KEY_RELEASE_MASK);
        
        ret = Signal2C<GdkEventKey *,WidgetC>(0,WidgetC(*this)); 
        break;
      case SigTypeEventMouseButton:
        if(sN == "button_press_event") // Enable press events.
          AddEventMask(GDK_BUTTON_PRESS_MASK); 
        if(sN == "button_release_event") // Enable Release events.
          AddEventMask(GDK_BUTTON_RELEASE_MASK); 
        ret = Signal1C<MouseEventC>(MouseEventC(0,0,0));  break;
        break;
      case SigTypeEventMouseMotion:   // Motion events..
        AddEventMask((int) GDK_POINTER_MOTION_MASK | 
                     GDK_POINTER_MOTION_HINT_MASK | 
                     GDK_LEAVE_NOTIFY_MASK);
        ret = Signal1C<MouseEventC>(MouseEventC(0,0,0));  break;
        break;
      case SigTypeCListSel: {CListEventC val; ret = Signal1C<CListEventC>(val); }  break;
      case SigTypeCListCol: ret = Signal1C<IntT>(-1);  break;
      case SigTypeString: // HACK!!
        cerr << "WidgetBodyC::Signal(), Got SigTypeString from:" << nm << "\n";
        return ret;
      case SigTypeDNDContext: ret = Signal1C<GdkDragContext *>((GdkDragContext *)0); break;
      case SigTypeDNDPosition: ret = Signal2C<GdkDragContext *,PositionTimeC>((GdkDragContext *)0); break;
      case SigTypeDNDData: { DNDDataInfoC dnd; ret = Signal1C<DNDDataInfoC>(dnd); } break;
      case SigTypeInt:         ret = Signal1C<IntT>(0); break;
      case SigTypeWidgetInt:         ret = Signal1C<UIntT>((UIntT)0); break;
      case SigTypeTreeRow:      ret = Signal2C<TreeModelIterC,TreeModelPathC>(TreeModelIterC(),TreeModelPathC()); break;
      case SigTypeTreePathCol: ret = Signal2C<TreeModelPathC,StringC>(TreeModelPathC(),StringC()); break;
      case SigTypeTreePath: ret = Signal1C<TreeModelPathC>(TreeModelPathC()); break;
      case SigTypeUnknown:
      default:
        cerr << "WidgetBodyC::Signal(), ERROR Unknown signal type:" << nm << " Type:" << (IntT) (si.signalType) << "\n";
        return ret;
    }
    
    // Remember the connection id.
    signals[nm].Data2() = ConnectUp(nm,ret);
    return ret;
  }

  //: Connect up a signal.


  IntT WidgetBodyC::ConnectUp(const char *nm,Signal0C &sig) {
    if(widget == 0)
      return -1;
    if(StringC(nm) == "combo_activate")
      return -1;
    IntT id = 0;
    GTKSignalInfoC &si = SigInfo(nm);
    if(si.name == 0) {
      cerr << "WidgetBodyC::ConnectUp(), ERROR: Unknown signal: '" << nm << "'\n";
      return -1;
    }
    id = gtk_signal_connect (GTK_OBJECT (widget), nm,
                             (GtkSignalFunc) si.func,&sig);
    if(id == 0)
      cerr << "WidgetBodyC::ConnectUp(), Warning failed to connect signal " << nm << "\n";
    return id;
  }
  
  //: Set the tool tip for the widget.
  // NB. Not all widgets can display tooltips.
  
  void WidgetBodyC::SetToolTip(const char *text,const char *ctxt) {
    tooltip = text;
  }
  
  //: Connect the default signals to the underlying widget.
  
  void WidgetBodyC::ConnectSignals() 
  {
    RavlAssert(Manager.IsGUIThread());
    
    if(widget == 0)
      return ;
    
    gtk_object_ref(GTK_OBJECT(widget));  // Make reference to object.
    gotRef = true;
#if 1
    if(dndInfo != 0) { // Setup drag and drop ?
      //gtk_widget_realize(widget); // Make sure widget is realised.
      //RavlAssertMsg(!GTK_WIDGET_NO_WINDOW(widget),"Widget must have a window to initalise drag and drop.");
      if(dndInfo->isSource)
        gtk_drag_source_set(widget, 
                            (GdkModifierType) dndInfo->SrcFlags,
                            &(dndInfo->SrcEntries[0]),
                            dndInfo->SrcEntries.Size(),
                            (GdkDragAction) dndInfo->SrcActions);
      if(dndInfo->isTarget)
        gtk_drag_dest_set(widget,
                          (GtkDestDefaults) dndInfo->TargFlags,
                          &(dndInfo->TargEntries[0]),
                          dndInfo->TargEntries.Size(),
                          (GdkDragAction) dndInfo->TargActions);
      delete dndInfo; // No needed after this.
      dndInfo = 0;
    }
#endif
    if(eventMask != (int) GDK_EXPOSURE_MASK)  {// Has it changed from default ?
      //if(GTK_WIDGET_NO_WINDOW (widget))
      gtk_widget_add_events (widget,(GdkEventMask) eventMask);
    }
    if(eventMask & (GDK_KEY_PRESS_MASK | GDK_KEY_RELEASE_MASK))
      GTK_WIDGET_SET_FLAGS(widget,GTK_CAN_FOCUS);    
    destroySigId = gtk_signal_connect (GTK_OBJECT (widget), "destroy",(GtkSignalFunc) gtkDestroy, this);
    if (!signals.IsEmpty()) {
      for(HashIterC<const char *,Tuple2C<Signal0C,IntT> > it(signals);it.IsElm();it.Next())
        it.Data().Data2() = ConnectUp(it.Key(),it.Data().Data1());
    }
    if(tooltip != 0) 
    {
      WidgetC me(*this);
      guiGlobalToolTips.GUIAddToolTip(me,tooltip);
    }
  }
  
  //: Show widget to the world.
  // Call only from GUI thread.
  
  bool WidgetBodyC::GUIShow() {
    if(widget == 0) {
      if(!Create()) {
        cerr << "WARNING: WidgetBodyC::GUIShow(), Failed. \n";
        return false;
      }
    }
    if(widget == 0)
      return false;
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    gtk_widget_show (Widget());
    return true;
  }
  
  //: Hide widget from the world.
  // Call only from GUI thread.
  
  bool WidgetBodyC::GUIHide() {
    if(widget == 0)
      return false;
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    gtk_widget_hide (Widget());
    return true;
  }

  //: Show widget to the world.
  
  bool WidgetBodyC::Show() {
    Manager.Queue(Trigger(WidgetC(*this),&WidgetC::GUIShow));
    return true;
  }
  
  //: Hide widget from the world.
  
  bool WidgetBodyC::Hide() {
    Manager.Queue(Trigger(WidgetC(*this),&WidgetC::GUIHide));
    return true;
  }
  
  
  //: Widget position.
  
  Index2dC WidgetBodyC::Position() const {  
    if(widget == 0)
      return Index2dC(0,0);
    return Index2dC(widget->allocation.x,widget->allocation.y);
  }
  
  //: Size of wiget.
  
  Index2dC WidgetBodyC::Size() const {
    if(widget == 0)
      return Index2dC(0,0);
    return Index2dC(widget->allocation.height,widget->allocation.width);
  }

  bool WidgetBodyC::SetUSize(IntT x,IntT y) {
    Manager.Queue(Trigger(WidgetC(*this),&WidgetC::GUISetUSize,x,y));
    return true;
  }
  
  //: Set size of widget.
  // GUI thread only.
  
  bool WidgetBodyC::GUISetUSize(IntT& x,IntT& y) {
    if(widget == 0) {
      cerr << "WARNING: WidgetBodyC::GUISetUSize() Called on widget before its been displayed. \n";
      return true;
    }
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    gtk_widget_set_usize(widget,x,y);
    return true;
  }
  
  //: Widget position and extent within its parent window.
  
  
  IndexRange2dC WidgetBodyC::Rectangle() const {
    if(widget == 0)
      return IndexRange2dC(0,0,0,0);
    Index2dC tl(widget->allocation.x,widget->allocation.y);
    return IndexRange2dC(tl,
                           tl + Index2dC((int) widget->allocation.height,(int) widget->allocation.width));
  }
  
  //: Undo all references.
  // Used to avoid problems with circluar references.
  // This should undo all references to RAVL and GUI
  // objects which are not in the destroy tree. 
  // The function is called by the root window in its
  // destructor.
  
  void WidgetBodyC::Destroy() { 
    for(HashIterC<const char *,Tuple2C<Signal0C,IntT> > it(signals);it.IsElm();it.Next()) {
      if(widget != 0 && GTK_IS_WIDGET(widget) && it.Data().Data2() >= 0) // Incase it was destroyed within GTK.
        gtk_signal_disconnect (GTK_OBJECT(widget), it.Data().Data2() );
      it.Data().Data1().DisconnectAll();
    }
    signals.Empty();
    widgetId = 0;
  }
  
  
  //: Add to the event mask.
  
  void WidgetBodyC::AddEventMask(IntT event) {
    ((int &) eventMask) |= event;
  }
  
  //: Remove from the event mask.
  
  void WidgetBodyC::DelEventMask(IntT event) {
    ((int &)eventMask) &= ~((int)event);
  }
  
  //: Make a shape mask for the widget.
  
  bool WidgetBodyC::GUIShapeCombineMask(GdkBitmap *mask,int off_x,int off_y) {
    RavlAssert(widget != 0);
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    gtk_widget_shape_combine_mask(widget,mask,off_x,off_y);
    return true;
  }
  
  //: Grab keyboard focus.
  
  void WidgetBodyC::GrabFocus() {
    Manager.Queue(Trigger(WidgetC(*this),&WidgetC::GUIGrabFocus));
  }
  
  //: Grab keyboard focus.
  
  void WidgetBodyC::GUIGrabFocus() {
    if(widget == 0)
      return ;
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    gtk_widget_grab_focus(widget);
  }
  
  //: Setup widget as drag and drop source.
  
  bool WidgetBodyC::GUIDNDSource(ModifierTypeT flags,const SArray1dC<GtkTargetEntry> &entries,DragActionT actions) {
    if(dndInfo == 0)
      dndInfo = new WidgetDndInfoC();
    dndInfo->isSource = true;
    dndInfo->SrcFlags = flags;
    dndInfo->SrcEntries = entries;
    dndInfo->SrcActions = actions;
    if(widget == 0)
      return true;
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    gtk_drag_source_set(widget, 
                        (GdkModifierType) flags,
                        &(entries[0]),
                        entries.Size(),
                        (GdkDragAction) actions);
    return true;
  }
  
  //: Disable widget as a drag and drop source.
  
  bool WidgetBodyC::GUIDNDSourceDisable() {
    if(dndInfo != 0)
      dndInfo->isSource = false;
    if(widget == 0) return true;
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    gtk_drag_source_unset(widget);
    return true;
  }
  
  //: Setup widget as drag and drop target.
  
  bool WidgetBodyC::GUIDNDTarget(DestDefaultsT flags,const SArray1dC<GtkTargetEntry> &entries,DragActionT actions) {
    if(dndInfo == 0)
      dndInfo = new WidgetDndInfoC();
    dndInfo->TargFlags = flags;
    dndInfo->TargEntries = entries;
    dndInfo->TargActions = actions;
    dndInfo->isTarget = true;
    if(widget == 0) 
      return true;
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    gtk_drag_dest_set(widget,
                      (GtkDestDefaults) flags,
                      &(entries[0]),
                      entries.Size(),
                      (GdkDragAction) actions);
    return true;
  }
  
  //: Disable widget as a drag and drop source.
  
  bool WidgetBodyC::GUIDNDTargetDisable() {
    if(dndInfo != 0)
      dndInfo->isSource = false;
    if(widget == 0) return true;
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    gtk_drag_dest_unset(widget);
    return true;
  }
  
  //: Initiate a drag operation.
  //!param: button - Button that started the drag.
  //!param: event - Event that started the drag.
  //!return: true, Drag started ok.
  
  bool WidgetBodyC::GUIDNDBegin(IntT button,GdkEvent *event) {
    if(dndInfo == 0) {
      cerr << "WidgetBodyC::GUIDNDBegin, ERROR: Drag and drop not setup. \n";
      return false;
    }
    if(widget == 0) {
      cerr << "WidgetBodyC::GUIDNDBegin, ERROR: No widget! \n";
      return false;
    }
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");

    GtkTargetList *targList = gtk_target_list_new(&(dndInfo->SrcEntries[0]),
                                                   dndInfo->SrcEntries.Size());
    
    GdkDragContext *dndCtxt = gtk_drag_begin(widget,
                                             targList,
                                             (GdkDragAction)dndInfo->SrcActions,
                                             button,
                                             event);
    
    if(dndCtxt == 0)
      return false;
    return true;
  }
  
  static SArray1dC<GtkTargetEntry> InitCommonTargetEntries() {
    SArray1dC<GtkTargetEntry> te(4);
    te[0].target = "text/plain";
    te[0].flags = 0;
    te[0].info = 0;
    te[1].target = "text/uri-list";
    te[1].flags = 0;
    te[1].info = 1;
    te[2].target = "application/x-rootwin-drop";
    te[2].flags = 0;
    te[2].info = 1;
    te[3].target = "STRING";
    te[3].flags = 0;
    te[3].info = 2;
    return te;
  }
  //: Get a list of common target entries.
  // name="text/plain" info=0 <br>
  // name="text/uri-list" info=1 <br>
  // name="STRING" info=2 <br>
  
  SArray1dC<GtkTargetEntry> WidgetBodyC::CommonTargetEntries() {
    static SArray1dC<GtkTargetEntry> te = InitCommonTargetEntries();
    return te;
  }

  //: Set the widget position    
  bool WidgetBodyC::GUISetUPosition(int &width, int &height) {
    if(widget == 0)
      return false;
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    gtk_widget_set_uposition (GTK_WIDGET (widget), width, height);
    return true;
  }

  //: Set the widget position  
  bool WidgetBodyC::SetUPosition(int &width, int &height) {
    Manager.Queue(Trigger(WidgetC(*this),&WidgetC::GUISetUPosition,width,height));
    return true;
  }

  //: Set the widget style
  bool WidgetBodyC::GUISetStyle(WidgetStyleC& style) {
    if(widget == 0) return false;
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    gtk_widget_set_style(GTK_WIDGET (widget),style.Style());
    return true;
  }

  //: Set the widget style
  void WidgetBodyC::SetStyle(WidgetStyleC& style) {
    Manager.Queue(Trigger(WidgetC(*this),&WidgetC::GUISetStyle,style));
  }
  
  
  //: Set background colour.
  
  bool WidgetBodyC::SetBackgroundColour(const ByteRGBValueC &colour,GtkStateType &state) {
    Manager.Queue(Trigger(WidgetC(*this),&WidgetC::GUISetBackgroundColour,colour,state));
    return true;
  }
  
  //: Set background colour.
  
  bool WidgetBodyC::SetForgroundColour(const ByteRGBValueC &colour,GtkStateType &state) {
    Manager.Queue(Trigger(WidgetC(*this),&WidgetC::GUISetForgroundColour,colour,state));
    return true;
  }
  
  //: Set text colour.
  
  bool WidgetBodyC::SetTextColour(const ByteRGBValueC &colour,GtkStateType &state) {
    Manager.Queue(Trigger(WidgetC(*this),&WidgetC::GUISetTextColour,colour,state));
    return true;
  }

  //: Set base colour.
  
  bool WidgetBodyC::SetBaseColour(const ByteRGBValueC &colour,GtkStateType &state) {
    Manager.Queue(Trigger(WidgetC(*this),&WidgetC::GUISetBaseColour,colour,state));
    return true;
  }
  
  bool WidgetBodyC::GUISetTextColour(const ByteRGBValueC &colour,GtkStateType &state) {
    GdkColor color;
    color.red = (IntT) colour.Red() * 255;
    color.green = (IntT) colour.Green() * 255;
    color.blue = (IntT) colour.Blue() * 255;
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    gtk_widget_modify_text (widget, state, &color);
    return true;
  }

  //: Set base colour.
  
  bool WidgetBodyC::GUISetBaseColour(const ByteRGBValueC &colour,GtkStateType &state) {
    GdkColor color;
    color.red = (IntT) colour.Red() * 255;
    color.green = (IntT) colour.Green() * 255;
    color.blue = (IntT) colour.Blue() * 255;
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    gtk_widget_modify_base (widget, state, &color);    
    return true;
  }

  //: Set background colour.
  
  bool WidgetBodyC::GUISetBackgroundColour(const ByteRGBValueC &colour,GtkStateType &state) {
    GdkColor color;
    color.red = (IntT) colour.Red() * 255;
    color.green = (IntT) colour.Green() * 255;
    color.blue = (IntT) colour.Blue() * 255;
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    gtk_widget_modify_bg (widget, state, &color);
    return true;
  }
  
  //: Set background colour.
  
  bool WidgetBodyC::GUISetForgroundColour(const ByteRGBValueC &colour,GtkStateType &state) {
    GdkColor color;
    color.red = (IntT) colour.Red() * 255;
    color.green = (IntT) colour.Green() * 255;
    color.blue = (IntT) colour.Blue() * 255;
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    gtk_widget_modify_fg (widget, state, &color);
    return true;
  }
  
  void GUIBeep() {
    gdk_beep();
  }
  //: Emit a short beep
  
  
}


