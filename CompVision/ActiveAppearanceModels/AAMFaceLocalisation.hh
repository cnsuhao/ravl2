#ifndef RAVLIMAGE_FACELOCALISATION_HEADER
#define RAVLIMAGE_FACELOCALISATION_HEADER 1
//! rcsid="$Id$"
//! lib=RavlAAM
//! file="Ravl/CompVision/ActiveAppearanceModels/AAMFaceLocalisation.hh"
//! docentry="Ravl.API.Images.AAM"
//! userlevel="Develop"
//! author="Jean-Yves Guillemaut"
//! example = aamLocaliseFace.cc

#include "Ravl/Image/AAMMultiResActiveAppearanceModel.hh"
#include "Ravl/OS/Filename.hh"

namespace RavlImageN {

  //! userlevel=Develop
  //: AAM-based face localisation.
  //  Use AAM to localise a face in an image. The method requires initialisation with an estimate of the eyes position.

  class AAMFaceLocalisationBodyC
    :public RCBodyVC
  {
  public:

    AAMFaceLocalisationBodyC()
    {}
    //: Default constructor.

    AAMFaceLocalisationBodyC(const AAMMultiResActiveAppearanceModelC &saam, FilenameC exampleFile);
    //: Constructor.
    //!param: saam - Multi-resolution AAM.
    //!param: exampleFile - Example of markup file representing an appearance.
    //  The example is used to learn the indices of the control points representing the eyes from the labels in the XML file. This is necessary to be able to compute the location of the centre of the eyes from an appearance or to compute the position of the appearance in the image from the position of its eye centres.

    AAMFaceLocalisationBodyC(const AAMMultiResActiveAppearanceModelC &saam, FilenameC exampleFile, FilenameC tpDir);
    //: Constructor.
    //!param: saam - Multi-resolution AAM.
    //!param: exampleFile - Example of markup file representing an appearance.
    //!param: tpDir - Name of directory containing list of shape initialisations.
    //  The example is used to learn the indices of the control points representing the eyes from the labels in the XML file. This is necessary to be able to compute the location of the centre of the eyes from an appearance or to compute the position of the appearance in the image from the position of its eye centres. A shape initialisation consists of saved mean points representing an instance of a shape. These are used to provide different initialisations for the AAM search algorithm, which increases the range of convergence of the algorithm. Typically the possible initialisation consists of mean shape corresponding to different poses such as left, right, up, down and frontal, or more if necessary.

    bool FitModel(const ImageC<ByteT> &inImage, const PairC<Point2dC> &eyeCentres, AAMAppearanceC &resAppear, bool useAM = false) const;
    //: Multi-resolution AAM search algorithm.
    //!param: inImage - Input image.
    //!param: eyeCentres - Estimate of the position of the centre of the eyes.
    //!param: resAppear - Output appearance fitted to the image.
    //!param: useAM - Synthesize texture using appearance model? Yes = true. If set to false the texture of the appearance image is obtained from the input image, i.e. the search algorithm is used only to find the location of the feature points defining the shape.

    const AAMMultiResActiveAppearanceModelC &MultiResActiveAppearanceModel() const
    { return maam; }
    //: Get multi-resolution active appearance model.

    AAMMultiResActiveAppearanceModelC &MultiResActiveAppearanceModel()
    { return maam; }
    //: Get multi-resolution active appearance model.

    const DListC<Tuple2C<SArray1dC<Point2dC>, PairC<Point2dC> > > &InitialisationList() const
    { return initialisationList; }
    //: List of initialisation for the search.
    //  Each initialisation instance consists of an array of coordinates of the feature points defining the shape and the coordinates of the eye centres for this initialisation.

    bool GetEyeCentres(const AAMAppearanceC &app, PairC<Point2dC> &eyeCentres) const;
    //: Return coordinates of the eye centres 'eyeCentres' for the appearance defined by 'app'.
    //  This function computes the coordinates of the eye centres from the position of the other feature points.
    //  The eye centre is defined as the midpoint of the segment defined by the left and right corners of the outer contour of the eye.

    bool GetEyeCentres(const SArray1dC<Point2dC> &points, PairC<Point2dC> &eyeCentres) const;
    //: Return coordinates of the eye centres 'eyeCentres' for the appearance with feature points 'points'.
    //  This function computes the coordinates of the eye centres from the position of the other feature points.
    //  The eye centre is defined as the midpoint of the segment defined by the left and right corners of the outer contour of the eye.

  protected:

    bool EyeCentresInit(FilenameC exampleFile);
    //: Sets parameters 'leftEyeIDs' and 'rightEyeIDs' for locating centres of the eyes.

    bool TemplatesInit(FilenameC tpDir = "");
    //: Sets list of initiliasation 'initialisationList' for AAM search.
    // If no value is provided, the search will be initialised with the mean appearance.

    Affine2dC ComputeSimilarityTransf(const PairC<Point2dC> &src, const PairC<Point2dC> &dest) const;
    //: Compute transformation composed of a rotation, translation, and scaling which maps the two eyes from position 'src' to 'dest'.

  protected:
    AAMMultiResActiveAppearanceModelC maam;  // Multi-resolution active appearance model.
    DListC<Tuple2C<SArray1dC<Point2dC>, PairC<Point2dC> > > initialisationList;  // List of initialisations for AAM search.
    DListC<IntT> leftEyeIDs;  // Indices of the feature points used to locate the centre of the left eye.
    DListC<IntT> rightEyeIDs;  // Indices of the feature points used to locate the centre of the right eye.
  };


  //! userlevel=Normal
  //: AAM-based face localisation.
  //  Use AAM to localise a face in an image. The method requires initialisation with an estimate of the eyes position.

  class AAMFaceLocalisationC
    : public RCHandleVC<AAMFaceLocalisationBodyC>
  {
  public:

    AAMFaceLocalisationC()
    {}
    //: Default constructor 
    // Creates an invalid handle.

    AAMFaceLocalisationC(const AAMMultiResActiveAppearanceModelC &saam, FilenameC exampleFile)
      : RCHandleVC<AAMFaceLocalisationBodyC>(*new AAMFaceLocalisationBodyC(saam, exampleFile))
    {}
    //: Constructor.
    //!param: saam - Multi-resolution AAM.
    //!param: exampleFile - Example of markup file representing an appearance.
    //  The example is used to learn the indices of the control points representing the eyes from the labels in the XML file. This is necessary to be able to compute the location of the centre of the eyes from an appearance or to compute the position of the appearance in the image from the position of its eye centres.

    AAMFaceLocalisationC(const AAMMultiResActiveAppearanceModelC &saam, FilenameC exampleFile, FilenameC tpDir)
      : RCHandleVC<AAMFaceLocalisationBodyC>(*new AAMFaceLocalisationBodyC(saam, exampleFile, tpDir))
    {}
    //: Constructor.
    //!param: saam - Multi-resolution AAM.
    //!param: exampleFile - Example of markup file representing an appearance.
    //!param: tpDir - Name of directory containing list of shape initialisations.
    //  The example is used to learn the indices of the control points representing the eyes from the labels in the XML file. This is necessary to be able to compute the location of the centre of the eyes from an appearance or to compute the position of the appearance in the image from the position of its eye centres. A shape initialisation consists of saved mean points representing an instance of a shape. These are used to provide different initialisations for the AAM search algorithm, which increases the range of convergence of the algorithm. Typically the possible initialisation consists of mean shape corresponding to different poses such as left, right, up, down and frontal, or more if necessary.

  protected:
    AAMFaceLocalisationC(AAMFaceLocalisationBodyC &bod)
      : RCHandleVC<AAMFaceLocalisationBodyC>(bod)
    {}
    //: Body constructor.

    AAMFaceLocalisationC(AAMFaceLocalisationBodyC *bod)
      : RCHandleVC<AAMFaceLocalisationBodyC>(*bod)
    {}
    //: Body ptr constructor.

    AAMFaceLocalisationBodyC &Body()
    { return RCHandleVC<AAMFaceLocalisationBodyC>::Body(); }
    //: Access body.

    const AAMFaceLocalisationBodyC &Body() const
    { return RCHandleVC<AAMFaceLocalisationBodyC>::Body(); }
    //: Access body.

  public:

    bool FitModel(const ImageC<ByteT> &inImage, const PairC<Point2dC> &eyeCentres, AAMAppearanceC &resAppear, bool useAM = false) const
    {  return Body().FitModel(inImage, eyeCentres, resAppear, useAM); }
    //: Multi-resolution AAM search algorithm.
    //!param: inImage - Input image.
    //!param: eyeCentres - Estimate of the position of the centre of the eyes.
    //!param: resAppear - Output appearance fitted to the image.
    //!param: useAM - Synthesize texture using appearance model? Yes = true. If set to false the texture of the appearance image is obtained from the input image, i.e. the search algorithm is used only to find the location of the feature points defining the shape.

    bool GetEyeCentres(const AAMAppearanceC &app, PairC<Point2dC> &eyeCentres) const
    {  return Body().GetEyeCentres(app, eyeCentres); }
    //: Return coordinates of the eye centres 'eyeCentres' for the appearance defined by 'app'.
    //  This function computes the coordinates of the eye centres from the position of the other feature points.
    //  The eye centre is defined as the midpoint of the segment defined by the left and right corners of the outer contour of the eye.

    bool GetEyeCentres(const SArray1dC<Point2dC> &points, PairC<Point2dC> &eyeCentres) const
    {  return Body().GetEyeCentres(points, eyeCentres); }
    //: Return coordinates of the eye centres 'eyeCentres' for the appearance with feature points 'points'.
    //  This function computes the coordinates of the eye centres from the position of the other feature points.
    //  The eye centre is defined as the midpoint of the segment defined by the left and right corners of the outer contour of the eye.

    const AAMMultiResActiveAppearanceModelC &MultiResActiveAppearanceModel() const
    { return Body().MultiResActiveAppearanceModel(); }
    //: Multi-resolution active appearance model.

    const DListC<Tuple2C<SArray1dC<Point2dC>, PairC<Point2dC> > > &InitialisationList() const
    { return Body().InitialisationList(); }
    //: List of initialisation for the search.
    //  Each initialisation instance consists of an array of coordinates of the feature points defining the shape and the coordinates of the eye centres for this initialisation.

    friend class AAMFaceLocalisationBodyC;
  };


}


#endif
