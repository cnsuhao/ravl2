// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////////
#include "Ravl/Image/CardMode.hh"
#include "Ravl/Exception.hh"
//! rcsid="$Id: fixSource.cfg,v 1.6 2005/03/02 09:28:41 craftit Exp $"
//! lib=DVS
namespace RavlImageN
{
using namespace RavlN ;

//: Constructor from card type.
//: --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CardModeC::CardModeC ( CardT type )
  : type(type),
    videoMode(UNKNOWN_VIDEOMODE),
    inputSync(UNKNOWN_SYNC),
    byteFormat(UNKNOWN_BYTEFORMAT),
    colourMode(UNKNOWN_COLOURMODE),
    dmaMode(UNKNOWN_DMAMODE),
    audioChannels(UNKNOWN_AUDIOCHANNELS),
    audioInput(UNKNOWN_AUDIOINPUT),
    audioBits(UNKNOWN_AUDIOBITS),
    audioFreq(UNKNOWN_AUDIOFREQ),
    matrix(UNKNOWN_MATRIX),
    linkMode(UNKNOWN_LINKMODE)
{
  Set_Defaults();
}

void CardModeC::Set_Defaults()
{
  switch (type) {
  case CENTAURUS:
    videoMode = SMPTE274_25P;
    byteFormat = BITS_10_DVS;
    colourMode = YUV422;
    dmaMode = FIFO_DMA;
    audioChannels = AUDIO_CHANNELS_8;
    audioInput = AIV;
    audioBits = AUDIO_32BIT;
    audioFreq = AUDIO_FREQ_48000;
    linkMode = SINGLE_LINK;
    break;

  case SDBOARD:
    videoMode = PAL;
    byteFormat = BITS_8;
    colourMode =  YUV422;
    dmaMode = FIFO_DMA;
    audioChannels = AUDIO_CHANNELS_8;
    audioInput = NOAUDIO;
    audioBits = AUDIO_16BIT;
    audioFreq = AUDIO_FREQ_48000;
    linkMode = SINGLE_LINK;
    break;

  case UNKNOWN_CARD:
    videoMode = UNKNOWN_VIDEOMODE;
    inputSync = UNKNOWN_SYNC;
    byteFormat = UNKNOWN_BYTEFORMAT;
    colourMode = UNKNOWN_COLOURMODE;
    dmaMode = UNKNOWN_DMAMODE;
    audioChannels = UNKNOWN_AUDIOCHANNELS;
    audioInput = UNKNOWN_AUDIOINPUT;
    audioBits = UNKNOWN_AUDIOBITS;
    audioFreq = UNKNOWN_AUDIOFREQ;
    matrix = UNKNOWN_MATRIX;
    linkMode = UNKNOWN_LINKMODE;
    break;

  default:
    RavlIssueWarning("\nCardModeC::CardModeC ( CardT type ) \t Unknown card type !!! ") ;
    break;
  }

}


//: Write mode to stream
//: The internal enums, are lookup up from the hash table and written in their String form.
//: -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ostream & operator << ( ostream & stream, const CardModeC & mode )
{
  stream
    << LookupNameM(mode.videoMode) << "\n"
    << LookupNameM(mode.inputSync) << "\n"
    << LookupNameM(mode.byteFormat) << "\n"
    << LookupNameM(mode.colourMode) << "\n"
    << LookupNameM(mode.dmaMode) << "\n"
    << LookupNameM(mode.audioChannels) << "\n"
    << LookupNameM(mode.audioInput) << "\n"
    << LookupNameM(mode.audioBits) << "\n"
    << LookupNameM(mode.audioFreq) << "\n"
    << LookupNameM(mode.matrix) << "\n"
    << LookupNameM(mode.linkMode) ;
  return stream ;
}


//: Read mode from stream.
//: -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
istream & operator >> ( istream & stream,CardModeC & mode )
{
  RavlAlwaysAssertMsg(0,"Not implemented yet" ) ;
  return stream ;
}


};
