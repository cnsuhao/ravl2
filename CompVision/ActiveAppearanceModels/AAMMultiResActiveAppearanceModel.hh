#ifndef RAVLIMAGE_MULTIRESACTIVEAPPEARANCEMODEL_HEADER
#define RAVLIMAGE_MULTIRESACTIVEAPPEARANCEMODEL_HEADER 1
//! rcsid="$Id$"
//! lib=RavlAAM
//! file="Ravl/CompVision/ActiveAppearanceModels/AAMMultiResActiveAppearanceModel.hh"
//! docentry="Ravl.API.Images.AAM"
//! userlevel="Develop"
//! author="Jean-Yves Guillemaut"
//! example = aamLocaliseFace.cc

#include "Ravl/PatternRec/Sample.hh"
#include "Ravl/Image/AAMActiveAppearanceModel.hh"

namespace RavlImageN {

  //! userlevel=Develop
  //: Multi-resolution Active Appearance Model.
  //  A multi-resolution AAM consists of several AAMs arranged in order of increasing resolution.
  //  Search starts with the coarsest level AAM and is refined progressively by switching to the finer level AAMS.
  //  This allows to increase the range and speed of convergence during the search.

  class AAMMultiResActiveAppearanceModelBodyC
    :public RCBodyVC
  {
  public:

    AAMMultiResActiveAppearanceModelBodyC()
    {}
    //: Default constructor.

    AAMMultiResActiveAppearanceModelBodyC(const AAMActiveAppearanceModelC &aam1);
    //: Constructor from one AAM.

    AAMMultiResActiveAppearanceModelBodyC(const AAMActiveAppearanceModelC &aam1, const AAMActiveAppearanceModelC &aam2);
    //: Constructor from two AAMs.
    //!param: aam1 - Low resolution AAM.
    //!param: aam2 - High resolution AAM.

    AAMMultiResActiveAppearanceModelBodyC(const AAMActiveAppearanceModelC &aam1, const AAMActiveAppearanceModelC &aam2, const AAMActiveAppearanceModelC &aam3);
    //: Constructor from three AAMs.
    //!param: aam1 - Low resolution AAM.
    //!param: aam2 - Medium resolution AAM.
    //!param: aam3 - High resolution AAM.

    AAMMultiResActiveAppearanceModelBodyC(const SampleC<AAMActiveAppearanceModelC> &saam);
    //: Constructor from an arbitrary number of AAMs sorted in order of increasing resolution.

    const AAMActiveAppearanceModelC &Nth(UIntT i) const
    { return maam.Nth(i); }
    //: Access nth level of resolution active appearance model (models are sorted in increasing order of resolution).

    const AAMActiveAppearanceModelC &Low() const
    { return maam.First(); }
    //: Access lowest resolution active appearance model.

    const AAMActiveAppearanceModelC &High() const
    { return maam.Last(); }
    //: Access highest resolution appearance model.

    const AAMActiveAppearanceModelC &First() const
    { return maam.First(); }
    //: Access lowest resolution active appearance model.

    const AAMActiveAppearanceModelC &Last() const
    { return maam.Last(); }
    //: Access highest resolution appearance model.

    UIntT Size() const
    { return maam.Size(); }
    // Return number of levels in the multi-resolution AAM.

    VectorC RefinePose(const ImageC<ByteT> &img,const VectorC &paramEstimate, RealT &diff) const;
    //: Returns the optimum appearance parameters for the image 'img' given an initial estimate 'paramEstimate'.
    //  The optimum parameters are the ones which minimise the residual error between model and image measured in normalised texture frame (i.e. shape free images).
    // This function also returns the value of the corresponding residual error in 'diff'.

    VectorC RefinePose(const ImageC<RealT> &img,const VectorC &paramEstimate, RealT &diff) const;
    //: Returns the optimum appearance parameters for the image 'img' given an initial estimate 'paramEstimate'.
    //  The optimum parameters are the ones which minimise the residual error between model and image measured in normalised texture frame (i.e. shape free images).
    // This function also returns the value of the corresponding residual error in 'diff'.

  protected:
    SampleC<AAMActiveAppearanceModelC> maam;  // Multi-resolution active appearance model.
  };


  //! userlevel=Normal
  //: Multi-resolution Active Appearance Model.
  //  A multi-resolution AAM consists of several AAMs arranged in order of increasing resolution.
  //  Search starts with the coarsest level AAM and is refined progressively by switching to the finer level AAMS.
  //  This allows to increase the range and speed of convergence during the search.

  class AAMMultiResActiveAppearanceModelC
    : public RCHandleVC<AAMMultiResActiveAppearanceModelBodyC>
  {

  public:

    AAMMultiResActiveAppearanceModelC()
    {}
    //: Default constructor
    // Creates an invalid handle.

    AAMMultiResActiveAppearanceModelC(const AAMActiveAppearanceModelC &aam1)
      : RCHandleVC<AAMMultiResActiveAppearanceModelBodyC>(*new AAMMultiResActiveAppearanceModelBodyC(aam1))
    {}
    //: Constructor from one AAM.

    AAMMultiResActiveAppearanceModelC(const AAMActiveAppearanceModelC &aam1, const AAMActiveAppearanceModelC &aam2)
      : RCHandleVC<AAMMultiResActiveAppearanceModelBodyC>(*new AAMMultiResActiveAppearanceModelBodyC(aam1, aam2))
    {}
    //: Constructor from two AAMs.
    //!param: aam1 - Low resolution AAM.
    //!param: aam2 - High resolution AAM.

    AAMMultiResActiveAppearanceModelC(const AAMActiveAppearanceModelC &aam1, const AAMActiveAppearanceModelC &aam2, const AAMActiveAppearanceModelC &aam3)
      : RCHandleVC<AAMMultiResActiveAppearanceModelBodyC>(*new AAMMultiResActiveAppearanceModelBodyC(aam1, aam2, aam3))
    {}
    //: Constructor from three AAMs.
    //!param: aam1 - Low resolution AAM.
    //!param: aam2 - Medium resolution AAM.
    //!param: aam3 - High resolution AAM.

    AAMMultiResActiveAppearanceModelC(const SampleC<AAMActiveAppearanceModelC> &saam)
      : RCHandleVC<AAMMultiResActiveAppearanceModelBodyC>(*new AAMMultiResActiveAppearanceModelBodyC(saam))
    {}
    //: Constructor from an arbitrary number of AAMs sorted in order of increasing resolution.

  protected:
    AAMMultiResActiveAppearanceModelC(AAMMultiResActiveAppearanceModelBodyC &bod)
      : RCHandleVC<AAMMultiResActiveAppearanceModelBodyC>(bod)
    {}
    //: Body constructor.

    AAMMultiResActiveAppearanceModelC(AAMMultiResActiveAppearanceModelBodyC *bod)
      : RCHandleVC<AAMMultiResActiveAppearanceModelBodyC>(*bod)
    {}
    //: Body ptr constructor.

    AAMMultiResActiveAppearanceModelBodyC &Body()
    { return RCHandleVC<AAMMultiResActiveAppearanceModelBodyC>::Body(); }
    //: Access body.

    const AAMMultiResActiveAppearanceModelBodyC &Body() const
    { return RCHandleVC<AAMMultiResActiveAppearanceModelBodyC>::Body(); }
    //: Access body.

  public:

    const AAMActiveAppearanceModelC &Nth(UIntT i) const
    { return Body().Nth(i); }
    //: Access nth level of resolution active appearance model (models are sorted in increasing order of resolution).

    const AAMActiveAppearanceModelC &Low() const
    { return Body().Low(); }
    //: Access lowest resolution active appearance model.

    const AAMActiveAppearanceModelC &High() const
    { return Body().High(); }
    //: Access highest resolution appearance model.

    const AAMActiveAppearanceModelC &First() const
    { return Body().First(); }
    //: Access lowest resolution active appearance model.

    const AAMActiveAppearanceModelC &Last() const
    { return Body().Last(); }
    //: Access highest resolution appearance model.

    UIntT Size() const
    { return Body().Size(); }
    // Return number of levels in the multi-resolution AAM.

    VectorC RefinePose(const ImageC<ByteT> &img,const VectorC &paramEstimate, RealT &diff) const
    { return Body().RefinePose(img, paramEstimate, diff); }
    //: Returns the optimum appearance parameters for the image 'img' given an initial estimate 'paramEstimate'.
    //  The optimum parameters are the ones which minimise the residual error between model and image measured in normalised texture frame (i.e. shape free images).
    // This function also returns the value of the corresponding residual error in 'diff'.

    VectorC RefinePose(const ImageC<RealT> &img,const VectorC &paramEstimate, RealT &diff) const
    { return Body().RefinePose(img, paramEstimate, diff); }
    //: Returns the optimum appearance parameters for the image 'img' given an initial estimate 'paramEstimate'.
    //  The optimum parameters are the ones which minimise the residual error between model and image measured in normalised texture frame (i.e. shape free images).
    // This function also returns the value of the corresponding residual error in 'diff'.

    friend class AAMMultiResActiveAppearanceModelBodyC;
  };


}


#endif
