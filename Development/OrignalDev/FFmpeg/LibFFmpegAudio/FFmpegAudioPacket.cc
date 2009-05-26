#include "Ravl/Audio/FFmpegAudioPacket.hh"

namespace RavlN {

  //: Destructor.
  
  FFmpegAudioPacketBodyC::~FFmpegAudioPacketBodyC() {
    if(packet.data != 0)
      av_free_packet(&packet);
  }
  

}
