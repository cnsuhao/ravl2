// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_IMAGEPYRAMID_HEADER
#define RAVLIMAGE_IMAGEPYRAMID_HEADER 1
//! author="Charles Galambos"
//! docentry="Ravl.Images.Filtering"
//! lib=RavlImageProc
//! rcsid="$Id$"
//! userlevel=Normal 
//! file="Ravl/Image/Processing/Filters/ImageExtend.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ImageExtend.hh"
#include "Ravl/Image/GaussConvolve2d.hh"
#include "Ravl/Collection.hh"
#include "Ravl/CollectionIter.hh"
#include "Ravl/Tuple3.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Image pyramid.
  // This class creates a set of images each filtered such that
  // that its effective resolution is reduced by a power of 2.
  
  template<class PixelT>
  class ImagePyramidC {
  public:
    ImagePyramidC()
    {}
    //: Default constructor.
    
    ImagePyramidC(const ImageC<PixelT> &img,IntT nScales = 2,bool subSample = false,bool recursive = false)
    { ComputeImages(img,nScales,subSample,recursive); }
    //: Constructor.
    //!param: img - Image to filter.
    //!param: nScales - Number of scales to generate. -1 = Generate a complete pyramid.
    //!param: subSample - If true sub-sample the pixels as well as filtering.
    
    void ComputeImages(const ImageC<PixelT> &img,IntT nScales,bool subSample,bool recursive = false);
    //: Compute images over given scales.
    //!param: img - Image to filter.
    //!param: nScales - Number of scales to generate. -1 = Generate a complete pyramid.
    //!param: subSample - If true sub-sample the pixels as well as filtering.
    //!param: recursive - If true when subsampling, then use the results of previous filtering operations as input for the next.
    
    ImageC<PixelT> ScaleImage(const ImageC<PixelT> &img,IntT scale,bool subSample,IntT imgScale = 1);
    //: Compute a scaled image and add it to the pyramid.
    //!param: img - Image to filter.
    //!param: scale - Scaling to apply.
    //!param: subSample - Sub sample the pixels in the image ?
    //!param: imgScale - Scale of image passed to routine, use 1 if the image at the original scale.
    //!return: resulting image.
    
    bool Find(RealT reqScale,ImageC<PixelT> &img,RealT &filterScale,RealT &pixelScale,bool notSmaller = false) const;
    //: Find image with closest scale.
    //!param: reqScale - Requested scale.
    //!param: img - Image found
    //!param: actualScale - Scale of image
    //!param: notSmaller - If true use the image with scale equal or larger size to that requested if one is available.
    //!return: Set to true if image found, only fails if class is not initalised.
    
    CollectionC<Tuple3C<RealT,RealT,ImageC<PixelT> > > &Images()
    { return images; }
    //: Access available images.
    
    const CollectionC<Tuple3C<RealT,RealT,ImageC<PixelT> > > &Images() const
    { return images; }
    //: Access available images.
    
  protected:
    CollectionC<Tuple3C<RealT,RealT,ImageC<PixelT> > > images;
  };
  
  template<class PixelT>
  void ImagePyramidC<PixelT>::ComputeImages(const ImageC<PixelT> &img,IntT nscales,bool subSample,bool recursive) {
    images = CollectionC<Tuple3C<RealT,RealT,ImageC<PixelT> > >(nscales+1);
    images.Insert(Tuple3C<RealT,RealT,ImageC<PixelT> >(1,1,img));
    //cerr << " No Scales=" << nscales << "\n";
    IntT minSize = Min(img.Rows(),img.Cols());
    if(subSample && recursive) {
      ImageC<PixelT> srcImg = img;
      IntT scale = 1;
      for(int i = 1;(i < nscales) || nscales < 0;i ++) {
	if((scale * 4-1) >= minSize)
	  break;
	srcImg = ScaleImage(srcImg,2,true,scale);
	scale *= 2;
      }
    } else {
      for(int i = 1;(i < nscales) || nscales < 0;i ++) {
	IntT scale = 1 << i;
	IntT kernelSize = scale*2 - 1;
	if(kernelSize >= minSize) // No point in scaling beyond the image size.
	  break;
	ScaleImage(img,scale,subSample,1);
      }
    }
  }
  
  //: Generate a single filtered image.
  //!param: img - Image to filter.
  //!param: scale - Scaling to apply.
  //!param: subSample - Sub sample the pixels in the image ?
  //!param: imgScale - Scale of image passed to routine, use 1 if the image at the original scale.
  
  template<class PixelT>
  ImageC<PixelT> ImagePyramidC<PixelT>::ScaleImage(const ImageC<PixelT> &img,IntT scale,bool subSample,IntT imgScale) {
    IntT kernelSize = scale*2 - 1;
    IndexRange2dC outRange = img.Frame();
    ImageC<PixelT> prepImage;
    ExtendImageCopy(img,scale-1,prepImage);
    GaussConvolve2dC<PixelT,PixelT,RealT,PixelT> filter(kernelSize);
    ImageC<PixelT> filteredImage = filter.Apply(prepImage);
    if(!subSample) {
      images.Insert(Tuple3C<RealT,RealT,ImageC<PixelT> >(scale * imgScale,imgScale,filteredImage));
      return filteredImage;
    }
    // FIXME:- This isn't the most efficient way of getting a subsampled image, we could
    // compute filered values for the points we want in the final image. 
    //cerr << " Scale=" << scale << "\n";
    IndexRange2dC alignedFrame = filteredImage.Frame().AlignWithin(scale);
    IndexRange2dC subFrame = alignedFrame / scale;
    ImageC<PixelT> subImage(subFrame);
      //cerr << " Frame=" << alignedFrame << " SF=" << subFrame << "\n";
    Array2dIterC<PixelT> dit(subImage);
    for(Array2dIterC<PixelT> sit(ImageC<PixelT>(filteredImage,alignedFrame));sit;sit += scale,dit++)
      *dit = *sit;
    images.Insert(Tuple3C<RealT,RealT,ImageC<PixelT> >(scale * imgScale,scale * imgScale,subImage));
    return subImage;
  }
  
  //: Find image with closest scale.
  //!param: reqScale - Requested scale.
  //!param: img - Image found
  //!param: actualScale - Scale of image
  
  template<class PixelT>
  bool ImagePyramidC<PixelT>::Find(RealT reqScale,ImageC<PixelT> &img,RealT &filterScale,RealT &pixelScale,bool notSmaller) const {
    CollectionIterC<Tuple3C<RealT,RealT,ImageC<PixelT> > > it(const_cast<CollectionC<Tuple3C<RealT,RealT,ImageC<PixelT> > > &>(images));
    if(!it) return false;
    // The first image should be the unscaled. Which is the default if reqScale is less than 1 and notSmaller is set.
    RealT diff = Abs(it->Data1() - reqScale);
    img = it->Data3();
    RealT bestScale =  diff;
    filterScale = it->Data1();
    pixelScale = it->Data2();
    
    for(it++;it;it++) {
      diff = Abs(it->Data1() - reqScale);
      if(diff < bestScale && (!notSmaller || it->Data1() < reqScale)) {
        img = it->Data3();
	bestScale = diff;
        filterScale = it->Data1();
        pixelScale = it->Data2();
      }
    }
    return true;
  }
  
}

#endif
