///////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/Widget.hh"
#include "Ravl/String.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/SignalInfo.hh"
//#include "Ravl/GUI/ToolTips.hh"
#include "Ravl/GUI/MouseEvent.hh"
#include "Ravl/CallMethods.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/Threads/Signal2.hh"
#include <gtk/gtk.h>

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  
  int WidgetBodyC::gtkDestroy (GtkWidget *widget,WidgetBodyC * data) { 
    ONDEBUG(cerr << "Got destroy for widget : " << ((void *) data) << "\n");
    data->WidgetDestroy(); 
    return 1;
  }
  
#define GTKSIG(name,type) Tuple2C<const char *,GTKSignalInfoC>(name,GTKSignalInfoC(name,type))
#define GTKSIG_GENERIC (GtkSignalFunc) WidgetBodyC::gtkGeneric,SigTypeGeneric
#define GTKSIG_EVENT   (GtkSignalFunc) WidgetBodyC::gtkEvent,SigTypeEvent 
#define GTKSIG_EVENT_MOUSEBUTTON   (GtkSignalFunc) WidgetBodyC::gtkEventMouseButton,SigTypeEventMouseButton
#define GTKSIG_EVENT_MOUSEMOTION   (GtkSignalFunc) WidgetBodyC::gtkEventMouseMotion,SigTypeEventMouseMotion 
#define GTKSIG_STRING   (GtkSignalFunc) WidgetBodyC::gtkString,SigTypeString
#define GTKSIG_CLISTSEL (GtkSignalFunc) WidgetBodyC::gtkCListSelect,SigTypeCListSel
#define GTKSIG_CLISTCOL (GtkSignalFunc) WidgetBodyC::gtkCListCol,SigTypeCListCol
#define GTKSIG_TERM    0,SigTypeUnknown

  GTKSignalInfoC &WidgetBodyC::SigInfo(const char *nm)  {
    static Tuple2C<const char *,GTKSignalInfoC> signalInfo [] = {
      // Don't move "destroy", needed to terminate initaliser list.
      GTKSIG("destroy"              ,GTKSIG_GENERIC ), // gtkwidget 
      GTKSIG("event"                ,GTKSIG_EVENT   ), // gtkwidget
      GTKSIG("button_press_event"   ,GTKSIG_EVENT_MOUSEBUTTON ), // gtkwidget
      GTKSIG("button_release_event" ,GTKSIG_EVENT_MOUSEBUTTON ), // gtkwidget
      GTKSIG("motion_notify_event"  ,GTKSIG_EVENT_MOUSEMOTION ), // gtkwidget
      GTKSIG("delete_event"         ,GTKSIG_EVENT   ), // gtkwidget
      GTKSIG("expose_event"         ,GTKSIG_EVENT   ), // gtkwidget
      GTKSIG("key_press_event"      ,GTKSIG_EVENT   ), // gtkwidget
      GTKSIG("key_release_event"    ,GTKSIG_EVENT   ), // gtkwidget
      GTKSIG("enter_notify_event"   ,GTKSIG_EVENT   ), // gtkwidget
      GTKSIG("leave_notify_event"   ,GTKSIG_EVENT   ), // gtkwidget
      GTKSIG("configure_event"      ,GTKSIG_EVENT   ), // gtkwidget
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
      GTKSIG("destroy",GTKSIG_TERM)  // Duplicate first key to terminate array.
    };
    static HashC<const char *,GTKSignalInfoC> signalTable(signalInfo);
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

  int WidgetBodyC::gtkGeneric(GtkWidget *widget,Signal0C *data) { 
    (*data)();
    return 1;
  }
  
  int WidgetBodyC::gtkCListSelect(GtkWidget *widget,
				     gint row,gint column,
				     GdkEventButton *event,
				     Signal0C *data) {
    Signal1C<CListEventC> sig(*data);
    RavlAssert(sig.IsValid());
    IntT rowId = (IntT) gtk_clist_get_row_data(GTK_CLIST(widget),row);
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
  
  //: Default constructor.
  
  WidgetBodyC::WidgetBodyC()
    : widget(0),
      widgetId(0),
      eventMask(GDK_EXPOSURE_MASK),
      tooltip(0)
  {}
  
  WidgetBodyC::WidgetBodyC(const char *ntooltip)
    : widget(0),
      widgetId(0),
      eventMask(GDK_EXPOSURE_MASK),
      tooltip(ntooltip)
  {}
  
  
  //: Destructor.

  WidgetBodyC::~WidgetBodyC() { 
    ONDEBUG(cerr << "WidgetBodyC::~WidgetBodyC(), Started  " << ((void *) this) << "\n");
    //RavlAssert(IsValidObject());
    if(widget != 0) {
      if(GTK_IS_WIDGET(widget)) { // Incase it was destroyed within GTK.
	gtk_widget_hide (widget);
	gtk_widget_destroy(widget);
      }
      widget = 0;
    }
    ONDEBUG(cerr << "WidgetBodyC::~WidgetBodyC(), Done.  " << ((void *) this) << "\n");
  }
  
  //: Get widget's name.
  // Call only from GUI thread.
  
  StringC WidgetBodyC::WidgetName() const {
    if(widget == 0)
      StringC("-Unknown-");
    const char *nm = gtk_widget_get_name(widget);
    if(nm == 0)
      StringC((int) widget); // Use address as dummy.
    return StringC(nm);
  }
  
  StringC WidgetBodyC::Name() const
  { return WidgetName(); }
  
  
  //: Create the widget.
  
  bool WidgetBodyC::Create() {
    cerr << "bool WidgetBodyC::Create(), Abstract function called. \n";
    return true;
  }
  
  //: Set state 
  
  bool WidgetBodyC::GUISetState(GtkStateType &state) {
    reqState = state;
    if(widget == 0)
      return true;
    if(reqState != GTK_WIDGET_STATE(widget))
      gtk_widget_set_state(widget,reqState);
    return true;
  }
  
  
  //: Set state 
  
  void WidgetBodyC::SetState(GtkStateType state) {
    Manager.Queue(Trigger(WidgetC(*this),&WidgetC::GUISetState,state));
  }
  
  void WidgetBodyC::WidgetDestroy() {
    widget = 0;
  }
  
  //: Get handle for named signal.
  // See handle class for description.
  
  Signal0C &WidgetBodyC::Signal(const char *nm) {
    Signal0C &ret = signals[nm];
    if(ret.IsValid()) 
      return ret;
    
    StringC sN(nm); // To make comparison easy.
    GTKSignalInfoC &si = SigInfo(nm);
    switch(si.signalType)
      {
      case SigTypeGeneric: ret = Signal0C(true); break;
      case SigTypeEvent:  ret = Signal2C<GdkEvent *,WidgetC>(0,WidgetC(*this)); break;
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
      case SigTypeUnknown:
      default:
	cerr << "WidgetBodyC::Signal(), ERROR Unknown signal type:" << nm << "\n";
	return ret;
    }
    ConnectUp(nm,ret);
    return ret;
  }

  //: Connect up a signal.


  void WidgetBodyC::ConnectUp(const char *nm,Signal0C &sig) {
    if(widget == 0)
      return ;
    if(StringC(nm) == "combo_activate")
    return ;
    UIntT id = 0;
    GTKSignalInfoC &si = SigInfo(nm);
    if(si.name == 0) {
      cerr << "WidgetBodyC::ConnectUp(), ERROR: Unknown signal: '" << nm << "'\n";
      return ;
    }
    id = gtk_signal_connect (GTK_OBJECT (widget), nm,
			     (GtkSignalFunc) si.func,&sig);
    if(id == 0)
      cerr << "WidgetBodyC::ConnectUp(), Warning failed to connect signal " << nm << "\n";
  }
  
  //: Set the tool tip for the widget.
  // NB. Not all widgets can display tooltips.
  
  void WidgetBodyC::SetToolTip(const char *text,const char *ctxt) {
    tooltip = text;
  }
  
  //: Connect the default signals to the underlying widget.
  
  void WidgetBodyC::ConnectSignals() {
    if(widget == 0)
      return ;
    
    if(eventMask != (int) GDK_EXPOSURE_MASK)  {// Has it changed from default ?
      //if(GTK_WIDGET_NO_WINDOW (widget))
      gtk_widget_set_events (widget,(GdkEventMask) eventMask);
    }
    
    gtk_signal_connect (GTK_OBJECT (widget), "destroy",
			(GtkSignalFunc) gtkDestroy, this);
    for(HashIterC<const char *,Signal0C> it(signals);it.IsElm();it.Next())
      ConnectUp(it.Key(),it.Data());
    
    if(tooltip != 0) {
      WidgetC me(*this);
      //guiGlobalToolTips.AddToolTip(me,tooltip);
    }
  }
  
  //: Show widget to the world.
  // Call only from GUI thread.
  
  bool WidgetBodyC::GUIShow() {
    if(widget == 0)
      Create();
    if(widget == 0)
      return false;
    gtk_widget_show (Widget());
    return true;
  }
  
  //: Hide widget from the world.
  // Call only from GUI thread.
  
  bool WidgetBodyC::GUIHide() {
    if(widget == 0)
      return false;
    gtk_widget_hide (Widget());
    return true;
  }

  //: Show widget to the world.
  
  void WidgetBodyC::Show() {
    Manager.Queue(Trigger(WidgetC(*this),&WidgetC::GUIShow));
  }
  
  //: Hide widget from the world.
  
  void WidgetBodyC::Hide() {
    Manager.Queue(Trigger(WidgetC(*this),&WidgetC::GUIHide));
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
  
  //: Set size of widget.
  // GUI thread only.
  
  bool WidgetBodyC::GUISetUSize(IntT x,IntT y) {
    if(widget == 0) {
      cerr << "WARNING: WidgetBodyC::GUISetUSize() Called on widget before its been displayed. \n";
      return true;
    }
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
  
  //: Undo all refrences.
  // Used to avoid problems with circluar refrences.
  // This should undo all refrences to RAVL and GUI
  // objects which are not in the destroy tree. 
  // The function is called by the root window in its
  // destructor.
  
  void WidgetBodyC::Destroy() { 
    for(HashIterC<const char *,Signal0C> it(signals);it.IsElm();it.Next())
      it.Data().DisconnectAll();
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
  
  void WidgetBodyC::ShapeCombineMask(GdkBitmap &mask,int off_x,int off_y) {
    RavlAssert(widget != 0);
    gtk_widget_shape_combine_mask(widget,&mask,off_x,off_y);
  }
}

