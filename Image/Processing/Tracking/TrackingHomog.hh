#ifndef RAVLIMAGE_TRACKINGHOMOGRAPHY_HEADER
#define RAVLIMAGE_TRACKINGHOMOGRAPHY_HEADER 1

//! userlevel=Normal
//! author="Phil McLauchlan, Bill Christmas"
//! docentry="Ravl.Images.Tracking"

#include "Ravl/Image/PointTracker.hh"
#include "Ravl/FitHomog2dPoints.hh"
#include "Ravl/MatrixRS.hh"
#include "Ravl/Observation.hh"
#include "Ravl/FitHomog2dPoints.hh"
#include "Ravl/EvaluateNumInliers.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Projection2d.hh"

namespace RavlImageN {

  //! userlevel=Develop


  //: Computes interframe homographies in an image sequence.
  // Body for TrackingHomogC

  class TrackingHomogBodyC
    : public RCBodyVC
  {
  public:

    TrackingHomogBodyC(bool nVerbose=false);
    //: Constructor

    void SetTracker(IntT cthreshold, IntT cwidth, IntT mthreshold, IntT mwidth,
		    IntT lifeTime, IntT searchSize, IntT newFreq)
      { tracker = PointTrackerC(cthreshold,cwidth,mthreshold,mwidth,
				lifeTime,searchSize,newFreq); }
    //: Set tracker parameters
    // Defaults are respectively: 30, 7, 20, 17, 8, 25, 1

    void SetMask(const ImageC<bool>& nmask)
      { mask = nmask; }
    //: Set binary mask to exclude graphics regions and suchlike from the process
    // Mask coordinate system should match that of image sequence.
    // Pixels set to false are excluded from tracker.

    bool SetMask(const StringC& fileName);
    //: Set binary mask to exclude graphics regions and suchlike from the process
    // Mask coordinate system should match that of image sequence.
    // Pixels set to false are excluded from tracker.

    void SetProjectiveScale(RealT scale)
      { 
	zhomog = scale;
	fitHomog2d = FitHomog2dPointsC(zhomog, zhomog);
      }
    //: Set the projective scale (i.e. 3rd, Z component) for the projective coordinate systems
    // Should be set so that scale is commensurate with typical pixel coordinate values.  <br>
    // Default is 100.

    RealT ProjectiveScale() const 
      { return zhomog; }
    //: Returns projective scale

    void Reset(const ImageC<ByteT> &img)
      { last = tracker.Apply(img); }
    //: Initialise the tracker with first image
    // <b>Must</b> be called before Apply() is used

    Projection2dC Apply(const ImageC<ByteT> &img);
    //: Compute homography between "img" and previous one
    // The result will map points from the previous image into the corresponding location in the current image.


  protected:
    PointTrackerC tracker;
    ImageC<bool> mask;  // identifies regions to be ignored for tracking
    RealT zhomog;
    FitHomog2dPointsC fitHomog2d;
    MatrixRSC epos;
    DListC<ObservationC> compatibleObsList;
    EvaluateNumInliersC evalInliers;
    RCHashC<UIntT,PointTrackC> corners, last;
    bool verbose;

  };
  
  //! userlevel=Normal

  //: Computes interframe homographies in an image sequence.
  // <p>Uses corner tracker to identify suitable features in order to register successive images.</p>
  // <p>The homography will map pixels from the previous image into the corresponding location in the current image.  Thus consecutive homographies <i>must</i> be combined in this order:</p>
  //<pre>    Htotal = Hn. ... .H3.H2.H1</pre>
  //!cwiz:author
  
  class TrackingHomogC
    : public RCHandleC<TrackingHomogBodyC>
  {
  public:
    TrackingHomogC(bool nVerbose = false) 
      : RCHandleC<TrackingHomogBodyC>(*new TrackingHomogBodyC(nVerbose))
    {}
    //!cwiz:author
    
    void SetTracker(IntT cthreshold,IntT cwidth,IntT mthreshold,IntT mwidth,IntT lifeTime,IntT searchSize,IntT newFreq) 
    { Body().SetTracker(cthreshold,cwidth,mthreshold,mwidth,lifeTime,searchSize,newFreq); }
    //: Set tracker parameters 
    // Defaults are respectively: 30, 7, 20, 17, 8, 25, 1
    //!cwiz:author
    
    void SetMask(const ImageC<bool> & nmask) 
    { Body().SetMask(nmask); }
    //: Set binary mask to exclude graphics regions and suchlike from the process
    // Mask coordinate system should match that of image sequence.
    // Pixels set to false are excluded from tracker.
    //!cwiz:author
    
    bool SetMask(const StringC & fileName) 
    { return Body().SetMask(fileName); }
    //: Set binary mask to exclude graphics regions and suchlike from the process
    // Mask coordinate system should match that of image sequence.
    // Pixels set to false are excluded from tracker.
    //!cwiz:author
    
    void SetProjectiveScale(RealT scale) 
    { Body().SetProjectiveScale(scale); }
    //: Set the scale (i.e. 3rd, Z component) for the projective coordinate systems 
    // Should be set so that scale is commensurate with typical pixel coordinate values.  <br>
    // Default is 100.
    //!cwiz:author
    
    RealT ProjectiveScale() const 
    { return Body().ProjectiveScale(); }
    //: Returns projective scale

    void Reset(const ImageC<ByteT> & img) 
    { Body().Reset(img); }
    //: Initialise the tracker with first image 
    // <b>Must</b> be called before Apply() is used
    //!cwiz:author
    
    Projection2dC Apply(const ImageC<ByteT> & img) 
    { return Body().Apply(img); }
    //: Compute homography between "img" and previous one 
    // The result will map pixels from the previous image into the corresponding location in the current image.
    //!cwiz:author
    
  protected:
    TrackingHomogC(TrackingHomogBodyC &bod)
     : RCHandleC<TrackingHomogBodyC>(bod)
    {}
    //: Body constructor. 
    
    TrackingHomogBodyC& Body()
    { return static_cast<TrackingHomogBodyC &>(RCHandleC<TrackingHomogBodyC>::Body()); }
    //: Body Access. 
    
    const TrackingHomogBodyC& Body() const
    { return static_cast<const TrackingHomogBodyC &>(RCHandleC<TrackingHomogBodyC>::Body()); }
    //: Body Access. 
    
  };

}

#endif
