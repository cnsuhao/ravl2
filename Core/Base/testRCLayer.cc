// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! docentry="Ravl.Core.Reference Counting"
//! rcsid="$Id$"
//! lib=RavlCore

#include "Omni/RCLayer.hh"
#include "Ravl/Stream.hh"

using namespace RavlN;

class RCLayerTestBodyC 
  : public RCLayerBodyC
{
public:
  RCLayerTestBodyC() {
    cerr << "RCLayerTestBodyC, Constructor.  \n";
    loopyHandle = RCLayerC<RCLayerTestBodyC>(*this,RCLH_INFERIOR);    
  }
  //: Default constructor.
  
  ~RCLayerTestBodyC() {
    cerr << "RCLayerTestBodyC, Destructor.  \n";
  }
  //: Destructor
  
  virtual void ZeroSuperiors() {
    cerr << "Hurra all the bosses have gone away. \n";
    loopyHandle.Invalidate();
  }
  //: Called when superior handles drop to zero.
  
protected:
  RCLayerC<RCLayerTestBodyC> loopyHandle;
};


int testRCLayer();

int main() {
  int lineno;
  if((lineno = testRCLayer()) != 0) {
    cerr << "Test failed " << lineno << "\n";
    return 1;
  }
  
  return 0;
}

int testRCLayer() {
  RCLayerC<RCLayerTestBodyC> layerH1(*new RCLayerTestBodyC(),RCLH_SUPERIOR);
  RCLayerC<RCLayerTestBodyC> layerH2 = layerH1;
  cerr << "Handles=" << layerH2.Superiors() << "\n";
  RCLayerC<RCLayerTestBodyC> layerH3 = RCLayerC<RCLayerTestBodyC>(layerH1,RCLH_SUPERIOR);
  cerr << "Handles=" << layerH2.Superiors() << "\n";
  layerH3 = layerH1;
  if(layerH3.Superiors() != 3) return __LINE__;
  cerr << "Handles=" << layerH2.Superiors() << " All=" << layerH2.References() << "\n";
  if(layerH2.References() != 4) return __LINE__;
  return 0;
}
