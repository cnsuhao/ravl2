// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Applications/VPlay/PlayControl.cc"

#include "Ravl/Tuple2.hh"
#include "Ravl/VPlay/PlayControl.hh"
#include "Ravl/GUI/Button.hh"
#include "Ravl/GUI/Pixmap.hh"
#include "Ravl/GUI/Slider.hh"
#include "Ravl/GUI/TextEntry.hh"
#include "Ravl/GUI/PackInfo.hh"
#include "Ravl/GUI/Label.hh"
#include "Ravl/GUI/ToggleButton.hh"
#include "Ravl/GUI/Combo.hh"
#include "Ravl/GUI/List.hh"
#include "Ravl/StringList.hh"
#include "Bitmaps/back.xpm"
#include "Bitmaps/fback.xpm"
#include "Bitmaps/ff.xpm"
#include "Bitmaps/jogfwd.xpm"
#include "Bitmaps/jogbkw.xpm"
#include "Bitmaps/play.xpm"
#include "Bitmaps/rewind.xpm"
#include "Bitmaps/stop.xpm"
#include "Bitmaps/theend.xpm"
#include "Ravl/Threads/TickerTrigger.hh"

#include <ctype.h>
#include <stdlib.h>

//#include "Ravl/DListExtra.hh"

#define DPDEBUG 0
#if DPDEBUG 
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {

  
  void PlayControlBodyC::Speed(IntT i) {
    MutexLockC hold(access);
    if(!pc.IsValid())
      return ;
    baseSpeed = i;
    pc.Speed(i * skip);
    for(DLIterC<DPPlayControlC> it(pcs);it.IsElm();it.Next())
      it.Data().Speed(i);
  }
  
  void PlayControlBodyC::Seek(UIntT pos) {
    MutexLockC hold(access);
    if(!pc.IsValid())
      return ;
    pc.Seek(pos);
    for(DLIterC<DPPlayControlC> it(pcs);it.IsElm();it.Next())
      it.Data().Seek(pos);
  }
  
  void PlayControlBodyC::Pause() {
    MutexLockC hold(access);
    if(!pc.IsValid())
      return ;
    pc.Pause();
    for(DLIterC<DPPlayControlC> it(pcs);it.IsElm();it.Next())
      it.Data().Pause();  
  }
  
  void PlayControlBodyC::Continue() {
    MutexLockC hold(access);
    if(!pc.IsValid())
      return ;
    pc.Continue();
    for(DLIterC<DPPlayControlC> it(pcs);it.IsElm();it.Next())
      it.Data().Continue();  
  }
  
  void PlayControlBodyC::Jog(IntT i) {
    MutexLockC hold(access);
    if(!pc.IsValid())
      return ;
    pc.Jog(i);
    for(DLIterC<DPPlayControlC> it(pcs);it.IsElm();it.Next())
      it.Data().Jog(i);  
  }
  
  
  bool PlayControlBodyC::Rewind() {
    Speed(0);
    MutexLockC hold(access);
    if(!pc.IsValid())
      return true;
    pc.ToBeginning();
    int tell = pc.Tell();
    if(tell >= 0) {
      for(DLIterC<DPPlayControlC> it(pcs);it.IsElm();it.Next())
	it.Data().Seek(tell);      
    } else {
      for(DLIterC<DPPlayControlC> it(pcs);it.IsElm();it.Next())
	it.Data().ToBeginning();
    }
    return true;
  }
  
  bool PlayControlBodyC::TheEnd() { 
    MutexLockC hold(access);
    if(!pc.IsValid())
      return true;
    if(pc.FixedEnd() == ((UIntT) -1)) 
      return true;
    UIntT seekTo = pc.FixedEnd()-1;
    hold.Unlock();
    Pause();  
    Seek(seekTo); 
    return true;
  }
  
  bool PlayControlBodyC::Backx2() { 
    Speed(-4); 
    Continue();
    return true;
  }
  
  bool PlayControlBodyC::Back() { 
    Speed(-1); 
    Continue();
    return true;
  }
  
  bool PlayControlBodyC::JBkw() { 
    Jog(-skip); 
    return true;
  }
  
  bool PlayControlBodyC::Stop() { 
    Speed(0);
    Pause();
    return true;
  }
  
  bool PlayControlBodyC::JFwd() { 
    Jog(skip);  
    return true;
  }
  
  bool PlayControlBodyC::Play() { 
    Speed(1);  
    Continue();
    return true;
  }
  
  bool PlayControlBodyC::Playx2() {
    Speed(4); 
    Continue();
    return true;
  }
  
  //: Setup control.
  
  void PlayControlBodyC::SetControl(const DPPlayControlC &ctrl) {
    MutexLockC hold(access);
    if(ctrl.IsValid())
      SetState(GTK_STATE_NORMAL);
    else
      SetState(GTK_STATE_INSENSITIVE);
    pc = ctrl;
  }
  
  //: Add stream to control list.
  // If no master stream exists  the new stream
  // will become it.
  
  void PlayControlBodyC::AddStream(DPPlayControlC &strm) {
    if(!strm.IsValid())
      return ;
    strm.Pause();
    MutexLockC hold(access);
    if(!pc.IsValid()) {
      pc = strm;
      SetState(GTK_STATE_NORMAL);
    } else {
      if(!pcs.Contains(strm))
	pcs.InsLast(strm);
      strm.Seek(pc.Tell()); // Sync new stream with master.
    }
  }
  
  //: Remove stream from control list.
  // If stream is the master, it will be removed
  // and replace with the first slave.
  
  bool PlayControlBodyC::DelStream(DPPlayControlC &strm) {
    MutexLockC hold(access);
    if(pc == strm) {
      if(!pcs.IsEmpty()) {
	pc = pcs.First(); // Take first slave as master control.
	pcs.DelFirst();
      } else {
	pc = DPPlayControlC();
	SetState(GTK_STATE_INSENSITIVE); // Last control gone...
      }
      return true;
    }
    return pcs.Del(strm);
  }
  
  //: Undo all references.
  
  void PlayControlBodyC::Destroy() {
    if(sliderUpdate.IsValid())
      sliderUpdate.Terminate();  
    LBoxBodyC::Destroy();
  }
  
  bool PlayControlBodyC::SliderCallback(RealT &val) {
    //ONDEBUG(cerr <<  "From:" << pc.Tell());
    Pause();
    Speed(0);
    Seek((UIntT) val);
    //ONDEBUG(cerr << " Seeking to :" << val << " At " << pc.Tell() << "\n");
    return true;
  }
  
  //: Set the frame skip value.
  
  bool PlayControlBodyC::SetSkip(StringC &val) {
    if(val.length() < 1)
      return true;
    if(!isdigit(val[0]))
      return true;
    skip = atoi(val);
    if(skip == 0) {
      skip = 1;
      StringC nv(skip);
      textSkip.SetText(nv);
    }
    // Make sure skip text is accurate...
    Speed(baseSpeed); // Update the current speed.
    return true;
  }
  
  bool PlayControlBodyC::SliderUpdate() {
    MutexLockC hold(access,true);
    if(!hold.IsLocked()) // Did lock succeed ?
      return true; // We'll do the update next time.
    //  cerr << "PlayControlBodyC::SliderUpdate(),\n";
    
    if(!pc.IsValid())
      return true;
    UIntT loc = pc.LastFrame();
    //cerr << "PlayControlBodyC::SliderUpdate(), Called at " << loc << "\n";
    if(loc == ((UIntT) -1)) 
      return true; // We don't have a clue!
    frameSlider.UpdateValue(loc);
    bool updateSlider = false;
    if(pc.FixedEnd() != ((UIntT)-1)) {
      if(pc.FixedEnd() != frameSlider.Upper())
	updateSlider = true;
    }
    if(pc.FixedStart() != frameSlider.Lower() || loc > frameSlider.Upper()) {
      ONDEBUG(cerr << "Setting slider range " << pc.FixedStart() << " " << loc << "\n");
      frameSlider.UpdateRange(pc.FixedStart(),loc);
    } else {
      if(updateSlider) {
	if(pc.FixedEnd() > loc) {
	  ONDEBUG(cerr << "Setting slider range " << pc.FixedStart() << " " << pc.FixedEnd()+1 << "\n");
	  frameSlider.UpdateRange(pc.FixedStart(),pc.FixedEnd());
	} else {
	  ONDEBUG(cerr << "Setting slider range " << pc.FixedStart() << " " << loc+1 << " (loc) \n");
	  frameSlider.UpdateRange(pc.FixedStart(),loc);
	}
      }
    }
    return true;
  }
  
  /////////////////////////////
  
  //: Default constructor.
  
  PlayControlBodyC::PlayControlBodyC()
    : LBoxBodyC(true,5,true),
      doneAdd(false),
      baseSpeed(1),
      skip(1)
  { InitGUI(); }
  
  PlayControlBodyC::PlayControlBodyC(const DPPlayControlC &nctrl)
    : LBoxBodyC(true,5,true),
      pc(nctrl),
      doneAdd(false),
      baseSpeed(1),
      skip(1)
  { InitGUI(); }
  
  //: Show/Hide extended controls.
  
  bool PlayControlBodyC::ShowExtended(bool &doit)  {
    ONDEBUG(cerr << "PlayControlBodyC::ShowExtended(), Called. \n");
    if(doit) {
      if(!doneAdd) {
	Add(extraControls);
	doneAdd = true;
      }
      extraControls.Show();
    } else
      extraControls.Hide();
    return true;
  }
  
  //: Set start of sub-sequence
  
  bool PlayControlBodyC::SetSubStart(StringC &text) {
    IntT val = atoi(text);
    if(val < 0)
      val = 0;
    pc.SubSeqStart() = (UIntT) val;
    ONDEBUG(cerr << "PlayControlBodyC::SetStart(), Start: " << val << " \n");
    return true;
  }
  
  //: Set end of sub-sequence
  
  bool PlayControlBodyC::SetSubEnd(StringC &text) {
    IntT val = atoi(text);
    if(val < 0)
      val = 0;
    pc.SubSeqEnd() = (UIntT) val;  
    ONDEBUG(cerr << "PlayControlBodyC::SetEnd(), End: " << val << " \n");
    return true;
  }

  //: Set sub-sequence mode.
  
  bool PlayControlBodyC::SetRepeatMode(StringC &text) {
    if(text == "Full")
      pc.SubSeqMode() = 0;
    else if(text == "Single") 
      pc.SubSeqMode() = 1;
    else if(text == "Loop") 
      pc.SubSeqMode() = 2;
    else if(text == "Palindrome") 
      pc.SubSeqMode() = 3;
    else
      cerr << "WARNING: Unknown repeat mode :" << text << "\n";
    ONDEBUG(cerr << "PlayControlBodyC::SetRepeatMode(),  '" << text << "' \n"); 
    return true;
  }
  
  void PlayControlBodyC::InitGUI() {
    ONDEBUG(cerr << "PlayControlBodyC::InitGUI(), Called. \n");
    //: Setup gui.
    
    UIntT theEnd;
    UIntT theStart;
    RealT maxSize;
    
    if(pc.IsValid()) {
      theStart = pc.FixedStart();
      theEnd   = pc.FixedEnd();
      if(theEnd == ((UIntT) -1)) 
	theEnd = pc.Size();
      if(theEnd == ((UIntT) -1)) {
	maxSize = theStart;
	//cerr << "PlayControlBodyC(), Sequence size unknown. \n";
      } else {
	maxSize = theEnd;
      }
    } else {
      theEnd = 1;
      theStart = 0;
      maxSize = 1;
    }
    ONDEBUG(cerr <<  "Sequence, Start:" << theStart << " Max:" << maxSize << " End:" << theEnd << "\n");
    
    frameSlider = SliderH(theStart,theStart,maxSize,1,PlayControlC(*this),&PlayControlC::SliderCallback); 
    
    Add(PackInfoC(HBox(HBox(Button(PixmapC(rewind_xpm),PlayControlC(*this),&PlayControlC::Rewind) +
			    Button(PixmapC(fback_xpm) ,PlayControlC(*this),&PlayControlC::Backx2) +
			    Button(PixmapC(back_xpm)  ,PlayControlC(*this),&PlayControlC::Back) +
			    Button(PixmapC(jogbkw_xpm),PlayControlC(*this),&PlayControlC::JBkw) +
			    Button(PixmapC(stop_xpm)  ,PlayControlC(*this),&PlayControlC::Stop) +
			    Button(PixmapC(jogfwd_xpm),PlayControlC(*this),&PlayControlC::JFwd) +
			    Button(PixmapC(play_xpm)  ,PlayControlC(*this),&PlayControlC::Play) + 
			    Button(PixmapC(ff_xpm)    ,PlayControlC(*this),&PlayControlC::Playx2) +
			    Button(PixmapC(theend_xpm),PlayControlC(*this),&PlayControlC::TheEnd),
			    0,false)),
		  false,false,2) +
	PackInfoC(frameSlider,false,true,2)
	);
    
    textSkip = TextEntryR(StringC(skip),*this,&PlayControlBodyC::SetSkip,-1,true);
    Add(PackInfoC(CheckButtonR("Extended controls","Show extended control panel",false,*this,&PlayControlBodyC::ShowExtended),false,false));
    
    extraControls = PackInfoC(VBox(HBox(LabelC("skip:") + textSkip) +
				   HBox(LabelC("Start:") + TextEntryR(StringC(skip),*this,&PlayControlBodyC::SetSubStart,-1,true)) +
				   HBox(LabelC("End:") + TextEntryR(StringC(skip),*this,&PlayControlBodyC::SetSubEnd,-1,true)) +
				   ComboR(StringListC("Full Single Loop Palindrome"),*this,&PlayControlBodyC::SetRepeatMode,false)
				   ),false,true);
    sliderUpdate = TickerTrigger(0.2,PlayControlC(*this),&PlayControlC::SliderUpdate);
  }
  
  ////////////////////////////////////////
  //: Destructor.
  
  PlayControlBodyC::~PlayControlBodyC() {
    Speed(0);
    Continue(); // Try and stop problems with locked threads.
  }
  
  
  ////////////////////////////////////////
  //: Constructor.
  
  
}
