// Original Copyright:
//    This file forms a part of ImageLib, a C++ class library for image 
//    processing.
//
//    Copyright (C) 1998-2003 Brendt Wohlberg  <brendt@dip1.ee.uct.ac.za>
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Library General Public
//    License as published by the Free Software Foundation; either
//    version 2 of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Library General Public License for more details.
//
//    You should have received a copy of the GNU Library General Public
//    License along with this library; if not, write to the Free
//    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
// Modified by Charles Galambos.
#ifndef RAVLIMAGE_DCT2D_HEADER
#define RAVLIMAGE_DCT2D_HEADER 1
//! userlevel=Normal
//! author="Brendt Wohlberg, Modified by Charles Galambos"
//! license=own
//! rcsid="$Id$"
//! lib=RavlImageProc
//! docentry="Ravl.API.Images.Transforms"
//! file="Ravl/Image/Processing/Filters/DCT2d.hh"

#include "Ravl/Image/Image.hh"

namespace RavlN {
  class VectorC;
};

namespace RavlImageN {
  
  void DCT(const ImageC<RealT>& src,ImageC<RealT>& dest);
  //: Perform DCT on src, result in dest
  // Note: the classes ChanDCTC or VecRadDCTC should be faster than this.
  
  // Only works on square images.
  
  void IDCT(const ImageC<RealT>& src, ImageC<RealT>& dest);
  //: Perform Inverse DCT on src, result in dest
  // Only works on square images.
  
  VectorC PackZigZag(const ImageC<RealT> &img,UIntT n);
  //: Pack first n components of image 'img' in a zig zag pattern from the to left corner of 'img'.
  
  void UnpackZigZag(const VectorC &vec,ImageC<RealT> &img);
  //: Unpack components of image vec in a zig zag pattern from the to left corner of 'img'.
  
  //:-
  //! userlevel=Normal
  //: Class implementing Fast DCT
  // class ChanDCT is an encapsulation of sofware (URL:
  // ftp://etro.vub.ac.be/pub/COMPRESSION/DCT_ALGORITHMS/) written by
  // Charilaos A. Christopoulos (Email:chchrist@etro.vub.ac.be), based on
  // the paper: <p>
  // S. C. Chan and K. L. Ho, "A new two-dimensional fast cosine transform 
  // algorithm", IEEE Trans. on Signal Processing, Vol. 39, No. 2, pp. 481-485,
  // Feb. 1991.
  
  class ChanDCTC {
  public:
    ChanDCTC();
    //: Default constructor.
    
    ChanDCTC(unsigned int size);
    //: Construct DCT for image of 'size' rows by 'size' columns
    
    ~ChanDCTC();
    //: Destructor.
    
    void Setup(unsigned int size);
    //: Setup tables for dct of given size.
    //!param:size - Size of dct image.
    
    void dct_in_place(ImageC<RealT>& im) const;
    //: Do an inplace dct of im.
    
    ImageC<RealT> operator()(const ImageC<RealT>& im) const
    { return DCT(im); }
    //: Compute the dct of im.
    
    ImageC<RealT> DCT(const ImageC<RealT>& im) const;
    //: Compute the DCT of im, return the result.
    
    void DCT(const ImageC<RealT>& src, ImageC<RealT>& dest) const;
    //: Compute the dct of 'src', place the result in 'dest'.
    
    IntT Size() const
    { return N; }
    //: Access the size of a side of the dct rectangle.
    
  private:
    const ChanDCTC &operator=(const ChanDCTC &oth)
    { return *this; }
    //: Make assigment operator private.
    
    int N;
    int m;
    RealT *cosines;

    RealT scaleDC;
    RealT scaleMix;
    RealT scaleAC;

    void makecosinetable();
    void columnspostadditions(ImageC<RealT>& fi) const;
    void rowspostadditions(ImageC<RealT>& fi) const;
    void rowsbitreversal(ImageC<RealT>& fi) const;
    void columnsbitreversal(ImageC<RealT>& fi) const;
    void columnsinputmapping(ImageC<RealT>& fi) const;
    void rowsinputmapping(ImageC<RealT>& fi) const;

  };

  //! userlevel=Normal
  
  //: Class implementing Fast DCT
  
  // class VecRadDCT is an encapsulation of sofware (URL:
  // ftp://etro.vub.ac.be/pub/COMPRESSION/DCT_ALGORITHMS/) written by
  // Charilaos A. Christopoulos (Email:chchrist@etro.vub.ac.be), based on
  // the papers: <p>
  //
  // C.A. Christopoulos, J. Bormans, A.N. Skodras and J. Cornelis, "Efficient 
  // computation of the two-dimensional fast cosine transform", SPIE Hybrid Image 
  // and Signal Processing IV, 5-8 April 1994, Orlando, Florida, USA. Accepted. <p>
  // 
  // and <P>
  //
  // C.A. Christopoulos and A.N. Skodras, "Pruning the two-dimensional fast cosine 
  // transform", To be presented at the VII European Signal Processing Conference ,
  // September 13-16, 1994, Edinburgh, Scotland.
  
  class VecRadDCTC {
  public:
    VecRadDCTC(unsigned int size, unsigned int pts);
    //: Constructor.
    
    VecRadDCTC();
    //: Default constructor.
    
    ~VecRadDCTC();
    //: Destructor.
    
    void Initialise(unsigned int size, unsigned int pts);
    //: Initialise for image of 'size' by 'size'
    
    void dct_in_place(ImageC<RealT>& im) const;
    
    ImageC<RealT> operator()(const ImageC<RealT>& im) const
    { return DCT(im); }
    
    ImageC<RealT> DCT(const ImageC<RealT>& im) const;
    //: Compute the DCT of img.
    
    void DCT(const ImageC<RealT>& src, ImageC<RealT>& dest) const;
    //: Compute the DCT of src, place the result in 'dest'.
    
  private:
    const VecRadDCTC &operator=(const VecRadDCTC &oth)
    { return *this; }
    //: Make assigment operator private.
    
    int N;
    int N0;
    int m;
    float *ct;
    float *ct2d;
    unsigned int **r;
    float *cosine_array;
    unsigned int MASK[2];

    float scaleDC;
    float scaleMix;
    float scaleAC;

    void lut_of_cos();
    void expand1d_lookup_table();
    void make2Darray();
    void bitreversalrows() const;
    void bitreversalcolumns() const;
    void firo3(ImageC<RealT>& fi) const;
    void post_adds(ImageC<RealT>& fi) const;

  };
  
}


#endif
