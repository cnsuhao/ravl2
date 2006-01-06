#ifndef SHOTBOUNDHISTINT
#define SHOTBOUNDHISTINT 1

#include "Ravl/SArray1d.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/Image.hh"

//! docentry="Ravl.API.Images.Shot Boundary Detection"
//! author="Bill Christmas"
//! userlevel=Normal

namespace RavlImageN {
  using namespace RavlN;

  //: Basic video shot boundary detector, based on colour histogram intersection, for ByteRGBValueC pixel type

  class ShotBoundHistIntC {
    
  public:
    
    ShotBoundHistIntC()
      :firstFrame(true)
    {}
    //: Default constructor
    
    ShotBoundHistIntC(UIntT NoOfBins, UIntT Subsample, RealT ShotDetThr);
    //: Constructor on shot detection parameters
    
    bool Apply(const ImageC<ByteRGBValueC>& frame);
    //: Process next video frame
    // Returns <code>true</code> if boundary detected

    RealT Proximity() const
    { return (shotDetThr - value);}
    //: Returns proximity to threshold of last decision
    // +ve / -ve value indicates boundary / not boundary respectively
    
  private:
    
    UIntT noOfBins;
    UIntT subsample; // spatial subsampling factor
    RealT shotDetThr;
    bool firstFrame;
    SArray1dC<int> prevColourHist;
    RealT value;
    
    SArray1dC<int> CalcHist(const ImageC<ByteRGBValueC> &Image);

  };
  

}




#endif
