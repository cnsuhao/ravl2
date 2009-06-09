#include "Ravl/OS/Date.hh"
#include "Ravl/TimeCode.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/RemoveDistortion.hh"
#include "Ravl/IO.hh"
#include "Ravl/Image/ImgIO.hh"
#include "Ravl/DList.hh"
#include "Ravl/CDLIter.hh"
#include "Ravl/AVFrame.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/Threads/MemModule.hh"

#include "MiniList.hh"

//! docentry="Ravl.API.OS.Multithreading Framework.Example"
//! userlevel = "Normal"

bool UnWarpBodyC::Run() {
  StringC source(Options().String("i", "", "Video source"));
  IntT noOfFrames(Options().Int("n", -1, "No. of frames"));
  IntT startFrame(Options().Int("s", 0, "Start frame"));
  RealT cx_ratio = Options().Real("cx",0.5,"Image centre x coordinate as ratio of image width. ");
  RealT cy_ratio = Options().Real("cy",0.5,"Image centre y coordinate as ratio of image height. ");
  RealT fx = Options().Real("fx",1.0,"Focal distance in vertical pixels. ");
  RealT fy = Options().Real("fy",1.0,"Focal distance in horizontal pixels. ");
  RealT K1 = Options().Real("K1",2.0e-7,"Cubic radial distortion coefficient. ");
  RealT K2 = Options().Real("K2",0.0,"Quintic radial distortion coefficient. ");
  Options().Check();
  if (Verbosity(3)) Options().PrintUsage();

  DPIPortC<ImageC<ByteRGBValueC> > in;
  if(!OpenISequence(in, source)) {
    StringC msg("Failed to open video file: " + source);
    cerr << msg << endl;
    Log() << msg << endl;   
  }

  ImageC<ByteRGBValueC> frame;
  RemoveDistortionC<ByteRGBValueC,ByteRGBValueC> distortionRemover;
  bool distortionRemoverCreated = false;
  for (TimeCodeC time(startFrame,25); 
       time.getFrameCount()!=noOfFrames+startFrame;
       ++time) { 
    if (!in.Get(frame)) break;

    //Remove lens distortion if required
    if (K1!=0.0 || K2!=0.0) {
      if(!distortionRemoverCreated){
        distortionRemover = RemoveDistortionC<ByteRGBValueC,ByteRGBValueC>(
                                           cx_ratio*(RealT)frame.Rows(), 
                                           cy_ratio*(RealT)frame.Cols(),
                                           fx, fy, K1, K2);
        distortionRemoverCreated = true;
      }
      distortionRemover.Apply(frame.Copy(),frame);
    }
    
    //add image to VAM
    MemoryItemC newItem(time, time);
    newItem.SetImage("frame", frame);
    Add(newItem);
    
    //write log
    Log(2) << "Frame stored in memory:" << time.ToText() << endl;
    Log(2, "@X:frame", frame);
  }
  return true;
}

