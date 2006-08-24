// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! docentry="Ravl.API.Core.Reference Counting"
//! rcsid="$Id$"
//! lib=RavlCore

#include "Ravl/RCLayer.hh"
#include "Ravl/Stream.hh"
#include "Ravl/SmartLayerPtr.hh"

using namespace RavlN;

class RCLayerTestBodyC 
  : public RCLayerBodyC
{
public:
  RCLayerTestBodyC() {
    cerr << "RCLayerTestBodyC, Constructor.  \n";
    loopyHandle = RCLayerC<RCLayerTestBodyC>(*this,RCLH_CALLBACK);    
  }
  //: Default constructor.
  
  ~RCLayerTestBodyC() {
    cerr << "RCLayerTestBodyC, Destructor.  \n";
  }
  //: Destructor
  
  virtual void ZeroOwners() {
    cerr << "Hurra all the bosses have gone away. \n";
    loopyHandle.Invalidate();
  }
  //: Called when owner handles drop to zero.
  
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
  RCLayerC<RCLayerTestBodyC> layerH1(*new RCLayerTestBodyC(),RCLH_OWNER);
  RCLayerC<RCLayerTestBodyC> layerH2 = layerH1;
  cerr << "Handles=" << layerH2.OwnerHandles() << "\n";
  RCLayerC<RCLayerTestBodyC> layerH3 = RCLayerC<RCLayerTestBodyC>(layerH1,RCLH_OWNER);
  cerr << "Handles=" << layerH2.OwnerHandles() << "\n";
  layerH3 = layerH1;
  if(layerH3.OwnerHandles() != 3) return __LINE__;
  cerr << "Handles=" << layerH2.OwnerHandles() << " All=" << layerH2.References() << "\n";
  if(layerH2.References() != 4) return __LINE__;
  return 0;
}
