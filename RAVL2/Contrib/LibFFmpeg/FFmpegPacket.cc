// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, Omniperception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlLibFFmpeg


#include "Ravl/Image/FFmpegPacket.hh"

namespace RavlN {

  //: Destructor.
  
  FFmpegPacketBodyC::~FFmpegPacketBodyC() {
    if(packet.data != 0)
      av_free_packet(&packet);
  }
  

}
