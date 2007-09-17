// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_DVSCARDMODE_HEADER
#define RAVLIMAGE_DVSCARDMODE_HEADER 1
////////////////////////////////////////////////////////////////////////
//! lib=DVS
//! author="Lee Gregory"
//! docentry="Ravl.API.Images.Video.Video IO.DVS"
#include "Ravl/RefCounter.hh"
#include "Ravl/Image/Types.hh"
#include "Ravl/Types.hh"


namespace RavlImageN {
class CardC ;
class LowLevelCardC ;
class FifoC ;
// some forward decs.

using namespace RavlN  ;
//! userlevel=Develop

//: A class representing a modes for the Grabber Card.
class CardModeC
{

public:

  CardModeC ( CardT type = UNKNOWN_CARD ) ;
  //: Constructor from card type
  // This construcor tries to make sensible defualts for cvssp grabber configurations

  //:- Functions to manipulate the internal state

  inline const CardT & Type(void) const { return type ; }
  //: Access card type

  inline void Type(const CardT card_type) {type = card_type; Set_Defaults(); }
  //: Set the card type. This will restore many options to sensible
  //: defaults for the chosen card.

  const DMAModeT & DMAMode(void) const ;
  //: Access DMA mode.

  inline void DMAMode(DMAModeT mode) { dmaMode = mode ; }
  //: Set DMA mode.

  inline DMAModeT UsingDMA (void) const { return dmaMode; }
  //: is this card in DMA mode.

  inline VideoModeT VideoMode (void) const { return videoMode ; }
  //: Query the video mode of the card.

  inline void VideoMode (VideoModeT mode) { videoMode = mode ; }
  //: Set the video mode of the card.

  inline InSyncT InputSync (void) const { return inputSync ; }
  //: Get the input sync mode

  inline void InputSync (InSyncT mode) { inputSync = mode ; }
  //: Set the input sync mode

  inline void ByteFormat ( ByteFormatT format)  { byteFormat = format ; }
  //: Get the format of the buffers

  inline ByteFormatT ByteFormat ( void) const { return byteFormat ; }
  //: Get the byte format of the buffers

  inline void ColourMode ( ColourModeT mode ) { colourMode = mode ; }
  //: Set the colour Mode of the card

  inline ColourModeT  ColourMode (void) const { return colourMode ; }
  //: Get the colour mode of the card

  inline DVSMatrixT Matrix(void) const { return matrix ; }
  //: Colour conversion matrix

  inline void Matrix(DVSMatrixT mat) { matrix = mat ; }
  //: Colour conversion matrix

  inline LinkModeT LinkMode (void) const { return linkMode ; }
  //: Get Link mode

  inline void LinkMode(LinkModeT mode) { linkMode = mode; }
  //: Set Link mode.

  //:- Audio
  // ------------------------------------------------------------------------------------------------------
  inline void AudioChannels ( AudioChannelsT channels ) { audioChannels = channels ; }
  //: Set the number of Audio Channel

  inline AudioChannelsT AudioChannels (void)  const { return audioChannels ; }
  //: Get the number of audio channels

  inline void AudioInput ( AudioInputT input ) { audioInput = input ; }
  //: Set the audio input source

  inline AudioInputT AudioInput (void) const { return  audioInput ; }
  //: Get the audio input source.

  inline void AudioBits ( AudioBitsT bits ) { audioBits = bits ; }
  //: Set audio bits

  inline AudioBitsT AudioBits ( void) const { return audioBits ; }
  //: GetAudioBits ;

  inline void AudioFreq (AudioFreqT freq ) { audioFreq = freq ; }
  //: Set the audio frequency

  inline AudioFreqT AudioFreq(void) const { return audioFreq ; }
  //: Get audio frequency

  friend ostream & operator  << ( ostream & stream , const CardModeC & mode)  ;
  friend istream & operator >> ( istream & stream, CardModeC & mode ) ;
  //: Allow IO operators access

protected :
  void Set_Defaults();


  CardT type ;					//: Card type
  VideoModeT  videoMode ;		//: Video mode
  InSyncT  inputSync ;				//: Sync mode`
  ByteFormatT  byteFormat ;		//: Byte format
  ColourModeT colourMode ;		//: Colour mode.
  DMAModeT dmaMode ;			//: DMA mode.
  AudioChannelsT  audioChannels ;   //: Audio channel mode.
  AudioInputT audioInput ;			//: Audio input source.
  AudioBitsT audioBits ;			//: Audio bits.
  AudioFreqT audioFreq ;			//: Audio frequency
  DVSMatrixT matrix ;				//: Which colour conversion mode is the card in.
  LinkModeT linkMode ;			//: Dual or single link ?
};
};
#endif
