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
#include "Ravl/Tuple3.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Image pyramid.
  
  template<class PixelT>
  class ImagePyramidC {
  public:
    ImagePyramidC()
    {}
    //: Default constructor.
    
    ImagePyramidC(const ImageC<PixelT> &img,IntT nScales = 2,bool subSample = false)
    { ComputeImages(img,nScales,subSample); }
    //: Default constructor.
    
    void ComputeImages(const ImageC<PixelT> &img,IntT nscales,bool subSample);
    //: Compute images over given scales.
    
    bool Find(RealT reqScale,ImageC<PixelT> &img,RealT &filterScale,RealT &pixelScale);
    //: Find image with closest scale.
    //!param: reqScale - Requested scale.
    //!param: img - Image found
    //!param: actualScale - Scale of image
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
  void ImagePyramidC<PixelT>::ComputeImages(const ImageC<PixelT> &img,IntT nscales,bool subSample) {
    images = CollectionC<Tuple3C<RealT,RealT,ImageC<PixelT> > >(nscales+1);
    images.Insert(Tuple3C<RealT,RealT,ImageC<PixelT> >(1,1,img));
    IndexRange2dC outRange = img.Frame();
    //cerr << " No Scales=" << nscales << "\n";
    for(int i = 1;i < nscales;i ++) {
      IntT scale = 1 << i;
      IntT kernelSize = scale*2 - 1;
      ImageC<PixelT> prepImage;
      ExtendImageCopy(img,scale-1,prepImage);
      GaussConvolve2dC<PixelT,PixelT,RealT,PixelT> filter(kernelSize);
      ImageC<PixelT> filteredImage = filter.Apply(prepImage);
      if(!subSample) {
        images.Insert(Tuple3C<RealT,RealT,ImageC<PixelT> >(scale,1.0,filteredImage));
      } else {
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
        images.Insert(Tuple3C<RealT,RealT,ImageC<PixelT> >(scale,scale,subImage));
      }
    }
  }
  
  //: Find image with closest scale.
  //!param: reqScale - Requested scale.
  //!param: img - Image found
  //!param: actualScale - Scale of image
  
  template<class PixelT>
  bool ImagePyramidC<PixelT>::Find(RealT reqScale,ImageC<PixelT> &img,RealT &filterScale,RealT &pixelScale) {
    RealT bestScale = 10000000 ;
    for(CollectionIterC<Tuple3C<RealT,RealT,ImageC<PixelT> > > it(images);it;it++) {
      RealT diff = Abs(it->Data1() - reqScale);
      if(diff < bestScale) {
        img = it->Data3();
        filterScale = it->Data1();
        pixelScale = it->Data2();
      }
    }
    return true;
  }
  
}

#endif
