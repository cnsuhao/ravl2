//////////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/Tuple2.hh"
#include "amma/VPlay/GUIPlayControl.hh"
#include "amma/GUI/Button.hh"
#include "amma/GUI/Pixmap.hh"
#include "amma/GUI/Slider.hh"
#include "amma/GUI/TextEntry.hh"
#include "Bitmaps/back.xpm"
#include "Bitmaps/fback.xpm"
#include "Bitmaps/ff.xpm"
#include "Bitmaps/jogfwd.xpm"
#include "Bitmaps/jogbkw.xpm"
#include "Bitmaps/play.xpm"
#include "Bitmaps/rewind.xpm"
#include "Bitmaps/stop.xpm"
#include "Bitmaps/theend.xpm"

#define DPDEBUG 1

#if DPDEBUG 
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

using namespace PThread;

void VP_Rewind(GUIButtonC &,DPPlayControlC &pc) 
{ 
  pc.Speed(1);  
  pc.Seek(0); 
}

void VP_TheEnd(GUIButtonC &,DPPlayControlC &pc) 
{ 
  if(pc.FixedEnd() == ((UIntT) -1)) 
    return ;
  pc.Pause();  
  pc.Seek(pc.FixedEnd()-1); 
}

void VP_Backx2(GUIButtonC &,DPPlayControlC &pc) 
{ 
  pc.Speed(-4); 
  pc.Continue();
}

void VP_Back(GUIButtonC &,DPPlayControlC &pc) 
{ 
  pc.Speed(-1); 
  pc.Continue();
}

void VP_JBkw(GUIButtonC &,DPPlayControlC &pc) 
{ pc.Jog(-1); }

void VP_Stop(GUIButtonC &,DPPlayControlC &pc) 
{ 
  pc.Speed(0);
  pc.Pause();
}

void VP_JFwd(GUIButtonC &,DPPlayControlC &pc) 
{ pc.Jog(1);  }

void VP_Play(GUIButtonC &,DPPlayControlC &pc) 
{ 
  pc.Speed(1); 
  pc.Continue();
}

void VP_Playx2(GUIButtonC &,DPPlayControlC &pc) 
{  
  pc.Speed(4); 
  pc.Continue();
}

void VP_frameSlider(RealT &val,DPPlayControlC &pc) 
{
  //ONDEBUG(cerr <<  "From:" << pc.Tell());
  pc.Speed(0);
  pc.Pause();
  pc.Seek((UIntT) val);
  //ONDEBUG(cerr << " Seeking to :" << val << " At " << pc.Tell() << "\n");
}


void VP_SliderUpdate(Tuple2C<DPPlayControlC,GUISliderC> &data) 
{
  UIntT loc = data.Data1().LastFrame();
  if(loc == ((UIntT) -1)) 
    return ; // We don't have a clue!
  data.Data2().UpdateValue(loc);  
  BooleanT updateSlider = FALSE;
  if(data.Data1().FixedEnd() != ((UIntT)-1)) {
    if(data.Data1().FixedEnd() != data.Data2().Upper())
      updateSlider = TRUE;
  }
  if(data.Data1().FixedStart() != data.Data2().Lower() || loc > data.Data2().Upper()) {
      ONDEBUG(cerr << "Setting slider range " << data.Data1().FixedStart() << " " << loc << "\n");
      data.Data2().UpdateRange(data.Data1().FixedStart(),loc);
  } else {
    if(updateSlider) {
      if(data.Data1().FixedEnd() > loc) {
	ONDEBUG(cerr << "Setting slider range " << data.Data1().FixedStart() << " " << data.Data1().FixedEnd()+1 << "\n");
	data.Data2().UpdateRange(data.Data1().FixedStart(),data.Data1().FixedEnd());
      } else {
	ONDEBUG(cerr << "Setting slider range " << data.Data1().FixedStart() << " " << loc+1 << " (loc) \n");
	data.Data2().UpdateRange(data.Data1().FixedStart(),loc);
      }
    }
  }
}

/////////////////////////////

GUIPlayControlBodyC::GUIPlayControlBodyC(const GUIWidgetC &rootwin,const DPPlayControlC &nctrl)
  : GUILBoxBodyC(TRUE,5,TRUE),
    ctrl(nctrl)
{
  using namespace StdGUI;
  //  using namespace StdIO;
  
  UIntT theStart = nctrl.FixedStart();
  UIntT theEnd   = nctrl.FixedEnd();
  RealT maxSize;
  if(theEnd == ((UIntT) -1)) 
    theEnd = nctrl.Size();
  if(theEnd == ((UIntT) -1)) {
    maxSize = theStart;
    //cerr << "GUIPlayControlBodyC(), Sequence size unknown. \n";
  } else {
    maxSize = theEnd;
  }
  ONDEBUG(cerr <<  "Sequence, Start:" << theStart << " Max:" << maxSize << " End:" << theEnd << "\n");
  
  GUISliderC frameS = SliderH(theStart,theStart,maxSize,1,VP_frameSlider,ctrl); 
  Add(
      HBox(Button(GUIPixmapC(rootwin,rewind_xpm),VP_Rewind,ctrl) +
	   Button(GUIPixmapC(rootwin,fback_xpm),VP_Backx2,ctrl) +
	   Button(GUIPixmapC(rootwin,back_xpm),VP_Back,ctrl) +
	   Button(GUIPixmapC(rootwin,jogbkw_xpm),VP_JBkw,ctrl) +
	   Button(GUIPixmapC(rootwin,stop_xpm),VP_Stop,ctrl) +
	   Button(GUIPixmapC(rootwin,jogfwd_xpm),VP_JFwd,ctrl) +
	   Button(GUIPixmapC(rootwin,play_xpm),VP_Play,ctrl) + 
	   Button(GUIPixmapC(rootwin,ff_xpm),VP_Playx2,ctrl) +
	   Button(GUIPixmapC(rootwin,theend_xpm),VP_TheEnd,ctrl),
	   0,FALSE) +
      frameS + 
      GUITextEntryC("",8)
      );
  
  sliderUpdate = PThread::Ticker(0.25,VP_SliderUpdate,Tuple2C<DPPlayControlC,GUISliderC>(nctrl,frameS));
  if(pc.IsInvalid())
    SetState(GTK_STATE_INSENSITIVE);
}

////////////////////////////////////////
//: Destructor.

GUIPlayControlBodyC::~GUIPlayControlBodyC()
{
  ctrl.Speed(0);
  ctrl.Continue(); // Try and stop problems with locked threads.
}


////////////////////////////////////////
//: Constructor.

GUIPlayControlC::GUIPlayControlC(const GUIWidgetC &rootwin,const DPPlayControlC &ctrl)
  : DPEntityC(*new GUIPlayControlBodyC(rootwin,ctrl))
{}

