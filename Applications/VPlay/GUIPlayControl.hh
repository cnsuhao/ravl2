#ifndef GUIPLAYCONTROL_HEADER
#define GUIPLAYCONTROL_HEADER 1
//////////////////////////////////////////////
//! rcsid="$Id$"
//! file="amma/Applications/VPlay/GUIPlayControl.hh"
//! author="Charles Galambos"
//! date="23/03/99"
//! docentry="GUI.Widget"

#include "amma/DP/PlayControl.hh"
#include "amma/GUI/LBox.hh"
#include "amma/PThread/Ticker.hh"

////////////////////////////
//! userlevel=Normal
//: Play Control GUI interface body.

class GUIPlayControlBodyC 
  : public GUILBoxBodyC
{
public:
  GUIPlayControlBodyC(const GUIWidgetC &rootwin,const DPPlayControlC &ctrl);
  //: Constructor.
  
  ~GUIPlayControlBodyC();
  //: Destructor.
  
protected:
  DPPlayControlC ctrl;
  PThread::ThreadC sliderUpdate;
};

////////////////////////////
//! userlevel=Normal
//: Play Control GUI interface.

class GUIPlayControlC 
  : public GUILBoxC
{
public:
  GUIPlayControlC(const GUIWidgetC &rootwin,const DPPlayControlC &ctrl);
  //: Constructor.
  
};

#endif
