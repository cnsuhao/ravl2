// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: AVMixer.cc 3703 2003-11-19 17:58:41Z craftit $"
//! lib=RavlAV
//! author="Charles Galambos"
#include "Ravl/config.h" 
#include "Ravl/AVMixer.hh"
//! file="Ravl/Image/AV/AVMixer.cc"

#if RAVL_COMPILER_MIPSPRO 
#include "Ravl/Audio/Types.hh"
#pragma instantiate RavlN::DPIPortBodyC<RavlImageN::ImageC<RavlImageN::ByteRGBValueC> >
#pragma instantiate RavlN::DPIPortBodyC<RavlAudioN::SampleElemC<(unsigned int)2,short> >
#endif 

namespace RavlImageN {
  
  //: Default constructor.
  
  AVMixerBodyC::AVMixerBodyC()
  : audioSamplesPerFrame(1024),
  audioFreq(1),
  videoFrameRate(1)
  {}
  
  //: Constructor.
  
  AVMixerBodyC::AVMixerBodyC(const DPISPortC<ImageC<ByteRGBValueC> > &vidPort,const DPISPortC<SampleElemC<2,Int16T> > &audioPort)
  : in1(vidPort),
  in2(audioPort),
  audioSamplesPerFrame(1),
  audioFreq(1),
  videoFrameRate(1)
  { Setup(); }
  
  //: Setup rates.
  
  bool AVMixerBodyC::Setup() {
    
    if(!in1.IsValid())
      haveVideo = false;
    else
      haveVideo = true;
    
    if(!in2.IsValid())
      haveAudio = false;
    else
      haveAudio = true;
    
    videoFrameRate = 25;
    audioFreq = 48000;
    
    if(haveVideo){
      if(!in1.GetAttr("framerate",videoFrameRate)) {
	cerr << "WARNING: Failed to get video frame rate, assuming 25hz \n";
	videoFrameRate = 25;
      }
    }
    if(haveAudio){
      if(!in2.GetAttr("samplerate",audioFreq)) {
	cerr << "WARNING: Failed to get audio sample rate, assuming 44Khz \n";
	audioFreq = 48000;
      }
    }
    
    if(videoFrameRate > 60)
      videoFrameRate = 25;
    
    //cerr << "audio framerate  " << audioFreq << "  " << videoFrameRate;
    
    audioSamplesPerFrame = audioFreq/videoFrameRate;
    SampleElemC<2,Int16T> tempSample;
    tempSample.channel[0] = tempSample.channel[1] = 0;
    dummyAudioFrame = SArray1dC<SampleElemC<2,Int16T> >(Round(audioSamplesPerFrame));
    dummyAudioFrame.Fill(tempSample);
    dummyVideoFrame = ImageC<ByteRGBValueC>(1,1);
    return true;
  }
  
  
  //: Is some data ready ?
  // true = yes.
  
  bool AVMixerBodyC::IsGetReady() const {
    if(haveAudio && haveVideo){
      if(!in1.IsValid() || !in2.IsValid())
	return true;
      return in1.IsGetEOS() && in2.IsGetReady();
    }
    else if(haveVideo && !haveAudio){
       return in1.IsGetReady();
    }
    else if(haveAudio && !haveVideo){
      return in2.IsGetReady();
    }
    return false;
  }
    
  //: Has the End Of Stream been reached ?
  // true = yes.
  
  bool AVMixerBodyC::IsGetEOS() const {
    if(haveAudio && haveVideo){
      if(!in1.IsValid() || !in2.IsValid())
        return true;
    return in1.IsGetEOS() && in2.IsGetEOS();
    }
    else if(haveVideo && !haveAudio){
      return in1.IsGetEOS();
    }
    else if(haveAudio && !haveVideo){ 
      return in2.IsGetEOS();
    }
    return false;
  }
  
  //: List input ports.
  
  DListC<DPIPortBaseC> AVMixerBodyC::IPorts() const {
    DListC<DPIPortBaseC> lst = DPStreamOpBodyC::IPorts();
    lst.InsLast(DPIPortBaseC((DPIPortBaseBodyC &)*this));
    return lst;
  }
  
  //: List input plugs.
  
  DListC<DPIPlugBaseC> AVMixerBodyC::IPlugs() const {
    DListC<DPIPlugBaseC> lst = DPStreamOpBodyC::IPlugs();
    lst.InsLast(DPIPlugC<ImageC<ByteRGBValueC> >(in1,"Video",DPEntityC((DPEntityBodyC &)*this)));
    lst.InsLast(DPIPlugC<SampleElemC<2,Int16T> >(in2,"Audio",DPEntityC((DPEntityBodyC &)*this)));
    return lst;
  }
    
  //: Process next piece of data.
  
  AVFrameC AVMixerBodyC::Get()  { 
    AVFrameC ret;
    if(!Get(ret))
      throw DataNotReadyC("Get failed. ");
    return ret;
  }
  
  //: Process some data.
  
  bool AVMixerBodyC::Get(AVFrameC &outbuff) {
    SArray1dC<SampleElemC<2,Int16T> > audio(Round(audioSamplesPerFrame));
    if(haveVideo && haveAudio){
      SArray1dC<SampleElemC<2,Int16T> > audio1;
      IntT temp = (in2.Tell()-in2.Start())-Round(audioSamplesPerFrame*(in1.Tell()-in1.Start()));
      RealT err = 0.01*audioSamplesPerFrame; //select amount of desireable error
      if(Abs(temp)>1000*err){
	in2.Seek(in2.Start()+Round(audioSamplesPerFrame*(in1.Tell()-in1.Start())));
	in2.GetArray(audio);
      }
      else if(temp < -err){
        audio1 = SArray1dC<SampleElemC<2,Int16T> >(Round(Abs(temp)));
        in2.GetArray(audio1);
        in2.GetArray(audio);
      }
      else if(temp > err){
	if(temp > 0 && temp < audioSamplesPerFrame){
	  audio = SArray1dC<SampleElemC<2,Int16T> > (Round(audioSamplesPerFrame-temp));
	  in2.GetArray(audio);
	}
	else
	  audio = dummyAudioFrame;
      }
      else
	if(in2.GetArray(audio) <= 0);
      
    }
    else if(haveAudio){
      if(in2.GetArray(audio) <= 0)
	return false;
    }
    
    if(!haveAudio)
      audio = dummyAudioFrame;
    
    ImageC<ByteRGBValueC> img;
    
    if(!haveVideo)
      img = dummyVideoFrame;
    else if(!in1.Get(img))
      img = dummyVideoFrame;
    
    outbuff = AVFrameC(AudioFrameC(audio,audioFreq),img);
    return true;
  }
  
  //: Seek to location in stream.
  
  bool AVMixerBodyC::Seek(UIntT off) {
    if(haveAudio && haveVideo){
      in2.Seek(Round(audioSamplesPerFrame * (RealT) off));
      return in1.Seek(off);
    }
    else if(!haveAudio && haveVideo)
      return in1.Seek(off);
    else if(haveAudio && !haveVideo)
      return in2.Seek(off+in2.Start());  
    else 
      return false;
  }
  
  //: Delta Seek, goto location relative to the current one.
  
  bool AVMixerBodyC::DSeek(IntT off) {
    if(haveAudio && haveVideo){
      in2.DSeek(Round(audioSamplesPerFrame * (RealT) off));
      return in1.DSeek(off);
    }
    else if(!haveAudio && haveVideo)
      return in1.DSeek(off);
    else if(haveAudio && !haveVideo)
      return in2.DSeek(Round(audioSamplesPerFrame * (RealT) off));  
    else 
      return false;
  }
  
  //: Find current location in stream.
  
  UIntT AVMixerBodyC::Tell() const {
    if(haveVideo)
      return in1.Tell();
    else if(haveAudio)
      return in2.Tell();
    else 
      return 0;
  }
  
  //: Find the total size of the stream. (assuming it starts from 0)
  
  UIntT AVMixerBodyC::Size() const {
    if(haveVideo)
      return in1.Size();
    else if(haveAudio)
      return in2.Size();
    else 
      return 0;
  }
  
  //: Find the offset where the stream begins, normally zero.
  
  UIntT AVMixerBodyC::Start() const {
    if(haveVideo)
      return in1.Start();
    else if(haveAudio)
      return in2.Start();
    else 
      return 0;
  }

}
