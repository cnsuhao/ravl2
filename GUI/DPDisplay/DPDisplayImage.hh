// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_DPDISPLAYIMAGE_HEADER
#define RAVLGUI_DPDISPLAYIMAGE_HEADER 1
//! rcsid="$Id: DPDisplayImage.hh 6701 2008-04-09 16:07:40Z ees1wc $"
//! lib=RavlDPDisplay
//! file="Ravl/GUI/DPDisplay/DPDisplayImage.hh"
//! author="Charles Galambos"
//! docentry="Ravl.API.Graphics.Data Display"

#include "Ravl/GUI/DPDisplayObj.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"

namespace RavlGUIN {
  using namespace RavlImageN;
  
  //! userlevel=Develop
  //: DPDisplayObj to handle images.
  
  class DPDisplayImageRGBBodyC
    : public DPDisplayObjBodyC
  {
  public:
    DPDisplayImageRGBBodyC(const ImageC<ByteRGBValueC> &img);
    //: Constructor
    
    virtual ~DPDisplayImageRGBBodyC() { }
    //: Need virtual destructor for class with virtual methods

    virtual bool Draw(FrameMarkupC &markup);
    //: Draw object to canvas.
    
    virtual IndexRange2dC Frame() const;
    //: Find bounding box for object.
    
    virtual bool Query(const Vector2dC &pnt,StringC &text);
    //: Query a point in the display.
    // Return true if point is within object.
    
    virtual bool Save(const StringC &str) const;
    //: Save to a file.
    
  protected:
    ImageC<ByteRGBValueC> img;
  };
  
  //! userlevel=Normal
  //: DPDisplayObj to handle images.
  
  class DPDisplayImageRGBC
    : public DPDisplayObjC
  {
  public:
    DPDisplayImageRGBC(const ImageC<ByteRGBValueC> &img)
      : DPDisplayObjC(*new DPDisplayImageRGBBodyC(img))
    {}
    //: Construct from an image.
    
    DPDisplayImageRGBC()
    {}
    //: Default constructor.
    // creates an invalid handle.
    
    DPDisplayImageRGBC(DPDisplayObjC &base)
      : DPDisplayObjC(dynamic_cast<const DPDisplayImageRGBBodyC *>(BodyPtr(base)))
    {}
    //: Base class contructor.
    // If types do not match an invalid handle is created.
    
  };

  //:---------------------------------------------------------------------------------------
  
  //! userlevel=Develop
  //: DPDisplayObj to handle images.
  
  class DPDisplayImageRealBodyC
    : public DPDisplayObjBodyC
  {
  public:
    DPDisplayImageRealBodyC(const ImageC<RealT> &img);
    //: Constructor
    
    virtual ~DPDisplayImageRealBodyC() { }
    //: Need virtual destructor for class with virtual methods

    virtual bool Draw(FrameMarkupC &markup);
    //: Draw object to canvas.
    
    virtual IndexRange2dC Frame() const;
    //: Find bounding box for object.
    
    virtual bool Query(const Vector2dC &pnt,StringC &text);
    //: Query a point in the display.
    // Return true if point is within object.
    
    virtual bool Save(const StringC &str) const;
    //: Save to a file.
    
  protected:
    ImageC<ByteT> ScaleImage(const ImageC<RealT> &inimg);
    //: Offset and scale image, then convert to ByteT image.
    
    ImageC<ByteT> img;
    ImageC<RealT> realImg;
  };
  
  //! userlevel=Normal
  //: DPDisplayObj to handle images.
  
  class DPDisplayImageRealC
    : public DPDisplayObjC
  {
  public:
    DPDisplayImageRealC(const ImageC<RealT> &img)
      : DPDisplayObjC(*new DPDisplayImageRealBodyC(img))
    {}
    //: Construct from an image.
    
    DPDisplayImageRealC()
    {}
    //: Default constructor.
    // creates an invalid handle.

    DPDisplayImageRealC(DPDisplayObjC &base)
      : DPDisplayObjC(dynamic_cast<const DPDisplayImageRealBodyC *>(BodyPtr(base)))
    {}
    //: Base class contructor.
    // If types do not match an invalid handle is created.
  };
  
  //:---------------------------------------------------------------------------------------
  
  //! userlevel=Develop
  //: DPDisplayObj to handle images.
  
  class DPDisplayImageByteBodyC
    : public DPDisplayObjBodyC
  {
  public:
    DPDisplayImageByteBodyC(const ImageC<ByteT> &img);
    //: Constructor
    
    virtual ~DPDisplayImageByteBodyC() { }
    //: Need virtual destructor for class with virtual methods

    virtual bool Draw(FrameMarkupC &markup);
    //: Draw object to canvas.
    
    virtual IndexRange2dC Frame() const;
    //: Find bounding box for object.
    
    virtual bool Query(const Vector2dC &pnt,StringC &text);
    //: Query a point in the display.
    // Return true if point is within object.
    
    virtual bool Save(const StringC &str) const;
    //: Save to a file.

  protected:
    ImageC<ByteT> img;
  };
  
  //! userlevel=Normal
  //: DPDisplayObj to handle images.
  
  class DPDisplayImageByteC
    : public DPDisplayObjC
  {
  public:
    DPDisplayImageByteC(const ImageC<ByteT> &img)
      : DPDisplayObjC(*new DPDisplayImageByteBodyC(img))
    {}
    //: Construct from an image.
    
    DPDisplayImageByteC()
    {}
    //: Default constructor.
    // creates an invalid handle.

    DPDisplayImageByteC(DPDisplayObjC &base)
      : DPDisplayObjC(dynamic_cast<const DPDisplayImageByteBodyC *>(BodyPtr(base)))
    {}
    //: Base class contructor.
    // If types do not match an invalid handle is created.
  };

  
}


#endif
