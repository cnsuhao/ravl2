// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_PLAYCONTROL_HEADER
#define RAVLGUI_PLAYCONTROL_HEADER 1
//////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Applications/VPlay/PlayControl.hh"
//! author="Charles Galambos"
//! date="23/03/1999"
//! docentry="Ravl.Applications.VPlay"
//! lib=RavlVPlay

#include "Ravl/GUI/LBox.hh"
#include "Ravl/DP/PlayControl.hh"
#include "Ravl/Threads/Mutex.hh"
#include "Ravl/Threads/Thread.hh"
#include "Ravl/GUI/Slider.hh"
#include "Ravl/GUI/TextEntry.hh"
#include "Ravl/Threads/Signal1.hh"
#include "Ravl/GUI/ToggleButton.hh"

namespace RavlGUIN {
  
  class PlayControlC;
  
  ////////////////////////////
  //! userlevel=Develop
  //: Play Control GUI interface body.
  
  class PlayControlBodyC 
    : public LBoxBodyC
  {
  public:
    PlayControlBodyC(const DPPlayControlC &ctrl);
    //: Constructor.
    
    PlayControlBodyC();
    //: Default constructor.
    
    ~PlayControlBodyC();
    //: Destructor.
    
    bool Rewind();
    //: Rewind to beginning.
    
    bool TheEnd();
    //: Goto end.
    
    bool Backx2();
    //: Backward x2 speed
    
    bool Back();
    //: Backward x1 speed
    
    bool JBkw();
    //: Jog a frame backward
    
    bool Stop();
    //: Stop
    
    bool JFwd();
    //: Jog a frame forward.
    
    bool Play();
    //: Forward x1 speed
    
    bool Playx2();
    //: Forward x2 speed
    
    void SetControl(const DPPlayControlC &ctrl);
    //: Setup control.
    
    void AddStream(DPPlayControlC &strm);
    //: Add stream to control list.
    // If no master stream exists  the new stream
    // will become it.
    
    bool DelStream(DPPlayControlC &strm);
    //: Remove stream from control list.
    // If stream is the master, it will be removed
    // and replace with the first slave.
    
    bool SetSkip(StringC &val);
    //: Set the frame skip value.
    
    bool ShowExtended(bool &doit);
    //: Show/Hide extended controls.
    
    bool EnableExtended(bool &enable);
    //: Enable extended controls option
    
    bool SetSubStart(StringC &text);
    //: Set start of sub-sequence
    
    bool SetSubEnd(StringC &text);
    //: Set end of sub-sequence
    
    bool SetRepeatMode(StringC &text);
    //: Set sub-sequence mode.
    
    Signal1C<IntT> &SigUpdateFrameNo()
    { return sigUpdateFrameNo; }
    //: Access update frame number signal.
    // Note this is NOT called every frame, only about 5 to 10 times
    // a second.
    
  protected:
    virtual void Destroy();
    //: Undo all references.
    
    void InitGUI();
    //: Setup gui.
    
    bool SliderUpdate();
    //: Update the GUI slider.
    
    bool SliderCallback(RealT &num);
    //: Position updates from slider.
    
    void Speed(IntT i);
    void Seek(UIntT pos);
    void Pause();
    void Continue();
    void Jog(IntT i);
    
    MutexC access;
    DPPlayControlC pc; // Master sequence.
    DListC<DPPlayControlC> pcs; // Slave sequences.
    ThreadC sliderUpdate;
    SliderC frameSlider;
    TextEntryC textSkip;  
    LBoxC extraControls;
    CheckButtonC enableextras;
    bool doneAdd;
    IntT baseSpeed; // what speed was last set.
    IntT skip;
    
    Signal1C<IntT> sigUpdateFrameNo; // Signal frame number update.
    
    friend class PlayControlC;
    
  };
  
  ////////////////////////////
  //! userlevel=Normal
  //: Play Control GUI interface.
  
  class PlayControlC 
    : public LBoxC
  {
  public:
    PlayControlC(const DPPlayControlC &ctrl)
      : LBoxC(*new PlayControlBodyC(ctrl))
    {}
    //: Constructor.
    
    PlayControlC(bool)
      : LBoxC(*new PlayControlBodyC())
    {}
    //: Constructor.
    
    PlayControlC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    PlayControlC(PlayControlBodyC &bod)
      : LBoxC(bod)
    {}
    //: Body constructor.
    
    PlayControlBodyC &Body()
    { return static_cast<PlayControlBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const PlayControlBodyC &Body() const
    { return dynamic_cast<const PlayControlBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    bool SliderUpdate()
    { return Body().SliderUpdate(); }
    //: Update the GUI slider.
    
    bool SliderCallback(RealT &num)
    { return Body().SliderCallback(num); }
    //: Position updates from slider.
  
  public:
    
    bool Rewind()
    { return Body().Rewind(); }
    //: Rewind to beginning.
    
    bool TheEnd()
    { return Body().TheEnd(); }
    //: Goto end.
    
    bool Backx2()
    { return Body().Backx2(); }
    //: Backward x2 speed
    
    bool Back()
    { return Body().Back(); }
    //: Backward x1 speed
    
    bool JBkw()
    { return Body().JBkw(); }
    //: Jog a frame backward
    
    bool Stop()
    { return Body().Stop(); }
    //: Stop
    
    bool JFwd()
    { return Body().JFwd(); }
    //: Jog a frame forward.
    
    bool Play()
    { return Body().Play(); }
    //: Forward x1 speed
    
    bool Playx2()
    { return Body().Playx2(); }
    //: Forward x2 speed
    
    bool EnableExtended(bool &enable)
    { return Body().EnableExtended(enable); }
    //: Enable extended controls option
    
    void SetControl(const DPPlayControlC &ctrl)
    { Body().SetControl(ctrl); }
    //: Setup control.
    
    void AddStream(DPPlayControlC &strm)
    { Body().AddStream(strm); }
    //: Add stream to control list.
    // If no master stream exists  the new stream
    // will become it.
    // Thread safe.
    
    bool DelStream(DPPlayControlC &strm)
    { return Body().DelStream(strm); }
    //: Remove stream from control list.
    // If stream is the master, it will be removed
    // and replace with the first slave.
    // Returns true is stream successfully removed.
    // (Can only fail if 'strm' is not in control.)
    // Thread safe.
    
    Signal1C<IntT> &SigUpdateFrameNo()
    { return Body().SigUpdateFrameNo(); }
    //: Access update frame number signal.
    // Note this is NOT called every frame, only about 5 to 10 times
    // a second.
    
    friend class PlayControlBodyC;
  };
}

#endif
