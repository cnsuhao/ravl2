// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////
//! rcsid="$Id: readgrab.cc 5240 2005-12-06 17:16:50Z sennis $"
//! lib=DVSFileFormat
//! file="DVSFileFormat/readgrab.cc"
//! example=readgrab.cc
//! docentry="DVSFileFormat.readgrab.cc"
//! userlevel=Normal
//! author="Simon Ennis"
//! date="21/05/2007"

//: Loading and saving image sequences

#include "Ravl/Option.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ImgIO.hh"
#include "Ravl/Image/ByteYUV422Value.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/IO.hh"
#include "Ravl/Image/ImageConv.hh"
#include "Ravl/DP/Port.hh"
///////////////////////////////////////////////////
#include "Ravl/DVS/Buffer.hh"
#include "Ravl/DVS/CardMode.hh"
#include "Ravl/DVS/Types.hh"

//#include "VerbosityOutput.hh"
#include "Ravl/DVS/NewGrabfileReader.hh"
//#include "Ravl/DVS/DVSCard.hh"
//#include "MTBufferCache.hh"
//#include "Ravl/DVS/GrabManager.hh"

//#include <Ravl/CallMethods.hh>
//#include <Ravl/Option.hh>
//#include <Ravl/Image/Image.hh>
//#include <Ravl/Image/ByteYUV422Value.hh>
//#include <Ravl/Image/ByteRGBValue.hh>
//#include <Ravl/IO.hh>
#include <Ravl/OS/Date.hh>
#include <Ravl/EntryPnt.hh>


//#include "Ravl/DVS/LowLevelCard.hh" // only needed for PrintBits and debugging !!

#include "Ravl/BinStream.hh"
#include   "Ravl/Exception.hh"

//#include "Ravl/DVS/GrabfileReaderV1.hh"
//#include "Ravl/DVS/LegacyGrabfileReader.hh"
//#include "Ravl/DVS/NewGrabfileReader.hh"
/////////////////////////////////////////////////////
using namespace RavlN;
using namespace RavlImageN;
using namespace DVSN;

int main(int argc,char **argv) 
{  
  // Process options.
  
  OptionC option(argc,argv);
  //StringC ifmt = option.String("if","","Input format. ");
  StringC ifilename = option.String("i","","Input grab file.");
  //StringC ofilename = option.String("o","@X","Output stream.");
  //StringC gfilename = option.String("g","","grab file.");
  option.Check();
  
  //DPIPortC<ImageC<ByteRGBValueC> > inputStream;
  //DPOPortC<ImageC<ByteRGBValueC> > outputStream;
  //ImageC<ByteRGBValueC> image;
  //ImageC<ByteRGBValueC> image2;

///////////////////////////////////////////////////
//test grabfilereader.

//  GrabfileReader* file_reader_pointer = 0;

  //if(legacy_reader) {
    //file_reader_pointer = new LegacyGrabfileReader();
  //} else {
//    file_reader_pointer = new GrabfileReaderV1();
  //}

  // Configure the card mode correctly depending on the hardware.
  //CardModeC mode;
  //GrabfileReader& file_reader = new GrabfileReaderV1();   //= *file_reader_pointer;

  //file_reader.Open(gfilename, mode);
  //cout << "file_reader was successful" << endl;



//////////////////////////////////////////////////////////////



/*
    //Test generic load and save mechamism.
  if(!Load(ifilename,image)) {
    cerr << "Failed to load file '" << ifilename << "' \n";
    return 1;
  }

  //ImageC<ByteRGBValueC> convert = ByteDVSYUV422ImageCT2ByteDVSRGBImageCT(image);

  if(!Save(ofilename,image)) {
    cerr << "Failed to save to file '" << ofilename << "' \n";
    return 1;
  }
  */
//////////////////////////////////////////////////////////////////////////////
/*  CardModeC mode;
  GrabfileReader* file_reader_pointer = 0;

  file_reader_pointer = NewGrabfileReader(ifilename, false);

  if(!file_reader_pointer) {
    cerr<<"Unable to find suitable file reader for "<<ifilename<<endl;
    cerr<<"File version: "<<GrabfileReader::FileVersion(ifilename)<<endl;
    return 1;
  }

  GrabfileReader& file_reader = *file_reader_pointer;

  file_reader.Open(ifilename, mode);

  cout << "ColourMode b4 getnextframe is " << mode.ColourMode() << endl;

  DVSBufferC buf;
  file_reader.GetNextFrame(buf);
  cout << "ColourMode after getnextframe is " << buf.ColourMode() << endl;
*/
///////////////////////////////////////////////////////////////////////////////
/*
    //Test DPIO stream for a sequence of images.
    if(!OpenISequence(inputStream,ifilename)) {
      // Failed to open input file.
      // Report an error...
      cout << "failed to open in put stream" << endl;
      return 1;
    }

    if(!OpenOSequence(outputStream,ofilename)) {
      // Failed to open output file.
      // Report an error..
      cout << "failed to open out put stream" << endl;
      return 1;
    }
    //cout << "new compiled readgrab" << endl;
    //image2 = inputStream.Get();
    //cout << "inputStream.IsGetEOS() is " << inputStream.IsGetEOS() << endl;
    //for(;inputStream.IsGetEOS();) { // Get next image, stop if none.
    //while(!inputStream.IsGetEOS()) {
    while(inputStream.Get(image)) { // Get next image, stop if none.
      try {
          //cout << "getting image" << endl;
	  //cout << "IsGetReady() is " << inputStream.IsGetReady() << endl;
         //image2 = inputStream.Get();
         //cout << "converting image" << endl;
         //ImageC<ByteRGBValueC> conv = ByteDVSYUV422ImageCT2ByteDVSRGBImageCT(image);
         //cout << "saving image" << endl;
         outputStream.Put(image);
      }
      catch(RavlN::DataNotReadyC) {
         break;
      }
    }
   */

      // Configure the card mode correctly depending on the hardware.
  CardModeC mode;
  //switch(card_type) {
  //case SDBOARD:
    cout<<"SDBOARD detected."<<endl;
    mode.Type(SDBOARD);
    mode.DMAMode(FIFO_DMA);
    mode.InputSync(SYNC_AUTO);
    mode.AudioInput(AIV);
    mode.AudioBits(AUDIO_32BIT);
    mode.AudioFreq(AUDIO_FREQ_48000);
    mode.AudioChannels(AUDIO_CHANNELS_4);
    mode.Matrix(CCIR601);
  /*  break;
  case CENTAURUS:
    vout(3)<<"CENTAURUS detected."<<endl;
    mode.Type(CENTAURUS);
    mode.DMAMode(FIFO_DMA);
    mode.InputSync(SYNC_AUTO);
    mode.AudioInput(AIV);
    mode.AudioBits(AUDIO_32BIT);
    mode.AudioFreq(AUDIO_FREQ_48000);
    mode.AudioChannels(AUDIO_CHANNELS_8);
    mode.Matrix(SMPTE274);
    break;
  case UNKNOWN_CARD:
  default:
    cerr<<"Unknown card detected or detection failed."<<endl;
    return 1;
  }*/
  cout << "Grab file reader pointer created" << endl;
  GrabfileReader* file_reader_pointer = 0;
  cout << "file reader new object allocated." << endl;
  file_reader_pointer = NewGrabfileReader(ifilename, false);
  cout << "after file reader object created." << endl;
  if(!file_reader_pointer) {
    cout<<"Unable to find suitable file reader for "<<ifilename<<endl;
    cout<<"File version: "<<GrabfileReader::FileVersion(ifilename)<<endl;
    return 1;
  }
  cout << "creating file_reader from file reader pointer" << endl;
  GrabfileReader& file_reader = *file_reader_pointer;
  cout << "about to open file_reader" << endl;
  if(file_reader.Open(ifilename, mode)) {
   cout << "Grab file was successfully opened. " << endl;
  }
  else {
     cout << "Grab file open was unsuccessful." << endl;
  }
  if(mode.ByteFormat() == BITS_10_DVS) {
     cout << "mode ByteFormat is BITS_10_DVS " << endl;
  }
  if(mode.ByteFormat() == BITS_8) {
     cout << "mode ByteFormat is BITS_8" << endl;
  }   
  file_reader.Close();
 
  return 0;
};
