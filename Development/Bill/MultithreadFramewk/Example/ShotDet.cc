#include "Ravl/TimeCode.hh"
#include "Ravl/Histogram.hh"
#include "Ravl/TVector.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Image/ShotBoundHistInt.hh"
#include "Ravl/Threads/MemModule.hh"

#include "MiniList.hh"

//! docentry="Ravl.API.OS.Multithreading Framework.Example"
//! userlevel = "Normal"

bool ShotDetBodyC::Run() {
    
    UIntT subsample(Options().Int("sub", 2, "Pixel subsampling factor"));
    UIntT fieldSubsample(Options().Int("fsub", 4, "Field subsampling factor"));
    UIntT noOfBins(Options().Int("bs",16,"Number of bins per colour channel for colour Histogram")); 
    RealT shotDetThr(Options().Real("thr",0.7,"The threshold to which the intesection of colour histograms is compared. Values lower than this threshold indicate shot boundaries"));
    UIntT MinShotLgth(Options().Int("ml", 6, "Minimum length for shot to be included (must be >= 2)"));
    Options().Check();
    if (Verbosity(3)) Options().PrintUsage();
    
    bool InShot(true);
    if (MinShotLgth < 2) {
      MinShotLgth = 2;
      cerr << "Minimum length for shot to be included must be >= 2.  Setting it -> 2" << endl;
      Log() << "---Warning:Minimum length for shot to be included must be >= 2.  Setting it -> 2" << endl;
    }
    
    ShotBoundHistIntC shotDet(shotDetThr, noOfBins, subsample);
    
    //get VAM iterator (memory access)
    VAMAccessC frameIter = GetAccess("frame");
    frameIter.MoveToFirst(false); //go to first elem & wait till available
    
    // Need to declare 1st & last frame TC outside loop for last shot
    TimeCodeC FirstFrame(frameIter->Start()); //get start time of first element
    TimeCodeC LastFrame;
    
    for(;!frameIter.Eof(); frameIter.Next(false)) 
      {
        const MemoryItemC& item = *frameIter; 
        if (item.Start().getFrameCount() % fieldSubsample != 0) continue;
        
        // Compute histogram intersection
        bool isBoundary = shotDet.Apply(item.GetImage("frame"));
        Log(2) << "Shot detector at frame " << item.Start().ToText()
               << "; delta value " << (isBoundary?"+":"")
               << shotDet.Proximity() << endl;
        
        // Look for shot boundary based on intersection value
        TimeCodeC FrameNo(item.Start()); 
        LastFrame = item.End();  // for final shot (maybe)
        if (InShot) {  // look for end of shot
          if (isBoundary) {
            // end of shot found so save shot (if long enough)
            if ((FrameNo-FirstFrame).getFrameCount() >= (int)MinShotLgth) {
                Log(1) << "Shot detector adding shot:" << FirstFrame.ToText() << " - " << LastFrame.ToText() << endl;
              // FrameNo-fieldSubsample is the last field known to be in shot
              Add(MemoryItemC(FirstFrame, FrameNo-fieldSubsample));
            }
            InShot = false;
          } 
        }
        else {  // look for start of shot
          if (!isBoundary) {  // start is found
            FirstFrame = FrameNo;
            InShot = true;
          }
        }
        if(AskedToStop()) //terminate nicely
          return true;
      }
    
    if (InShot && ((LastFrame-FirstFrame+1).getFrameCount() >= (int)MinShotLgth))
      {  // if in shot, last frame is end of shot
        Log(1) << "Shot detector adding last shot:" << FirstFrame.ToText() << " - " << LastFrame.ToText() << endl;
        Add(MemoryItemC(FirstFrame, LastFrame));
      }
    return true;
  }
  
  
