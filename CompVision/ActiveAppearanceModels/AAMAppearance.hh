// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_APPEARANCE_HEADER
#define RAVLIMAGE_APPEARANCE_HEADER 1
//! rcsid="$Id$"
//! lib=RavlAAM
//! file="Ravl/CompVision/ActiveAppearanceModels/AAMAppearance.hh"
//! docentry="Ravl.Images.Misc"
//! userlevel=Normal
//! author="Charles Galambos"

#include "Ravl/SArray1d.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/RCHash.hh"
#include "Ravl/PatternRec/Sample.hh"

namespace RavlImageN {

  using namespace RavlImageN;
  using namespace RavlN;

  //! userlevel=Normal
  //: Instance of an object and its control points.
  
  class AAMAppearanceC {
  public:
    AAMAppearanceC()
    {}
    //: Default constructor.
    
    AAMAppearanceC(const SArray1dC<Point2dC> &npoints,const ImageC<ByteT> &img)
      : points(npoints),
	image(img)
    {}
    //: Constructor.

    AAMAppearanceC(const SArray1dC<Point2dC> &npoints)
      : points(npoints)
    {}
    //: Constructor.
    
    SArray1dC<Point2dC> &Points()
    { return points; }
    //: Access point list.

    const SArray1dC<Point2dC> &Points() const
    { return points; }
    //: Access point list.
    
    ImageC<ByteT> &Image() 
    { return image; }
    //: Access original image.

    const ImageC<ByteT> &Image() const
    { return image; }
    //: Access original image.

    StringC &SourceFile()
    { return sourceFile; }
    //: Source file.

    bool IsValid() const
    { return points.Size() > 0; }

    bool Draw(const StringC & filename,StringC fileformat = "",bool verbose = false) const;    //: Draw appearance image to filename

  protected:
    StringC sourceFile;
    SArray1dC<Point2dC> points; // Control points in image.
    ImageC<ByteT> image;       // Image.
  };
  
  inline
  BinOStreamC &operator<<(BinOStreamC &s,const AAMAppearanceC &ap) {
    s << ap.Points() << ap.Image();
    return s;
  }
  //: Write appearance to binary stream.
  
  inline
  BinIStreamC &operator>>(BinIStreamC &s,AAMAppearanceC &ap) {
    s >> ap.Points() >> ap.Image();
    return s;
  }
  //: Read appearance from binary stream.

  inline
  ostream &operator<<(ostream &s,const AAMAppearanceC &ap) {
    s << ap.Points() << ' ' << ap.Image();
    return s;
  }
  //: Write appearance to stream.
  
  inline
  istream &operator>>(istream &s,AAMAppearanceC &ap) {
    s >> ap.Points() >> ap.Image();
    return s;
  }
  //: Read appearance from stream.
  
  //:-
  
  //! userlevel=Normal
  //: Appearance mirror.
  // Used to reflect data about the vertical axis.
  
  class AAMAppearanceMirrorC
  {
  public:
    AAMAppearanceMirrorC()
    {}
    //: Default constructor.

    AAMAppearanceMirrorC(const StringC &filename)
    { ReadMirror(filename); }
    //: Default constructor.
    
    bool ReadMirror(const StringC &filename);
    //: Read in a mirror mapping.
    
    bool Reflect(SampleC<AAMAppearanceC> &sample);
    //: Reflect a sample set and append at the end of sample

    AAMAppearanceC Reflect(AAMAppearanceC &appear);
    //: Return reflected appearance
    
    bool IsValid()
    { return map.Size() > 0; }
    //: Is this a valid mirror ?
  protected:
    RCHashC<IntT,IntT> mirror;
    SArray1dC<UIntT> map;
  };
  
    
  
  
}



#endif
