#ifndef RAVLIMAGE_CORNERDETECTOR_HEADER
#define RAVLIMAGE_CORNERDETECTOR_HEADER 1
////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! docentry="Ravl.Images.Corner Detection"
//! date="20/7/2002"

#include "Ravl/RefCounter.hh"
#include "Ravl/DList.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/Corner.hh"

namespace RavlImageN {
  
  //: Abstract corner detector.
  // Where a 'corner' is a defined as a well localised 
  // 2d position in an image.
  
  class CornerDetectorBodyC 
    : public RCBodyVC
  {
  public:
    CornerDetectorBodyC();
    //: Default constructor.
    
    virtual DListC<CornerC> Apply(const ImageC<ByteT> &img);
    //: Get a list of corners from 'img'
    
  };

  //: Abstract corner detector.
  // Where a 'corner' is a defined as a well localised 
  // 2d position in an image.
  
  class CornerDetectorC 
    : public RCHandleC<CornerDetectorBodyC>
  {
  public:
    CornerDetectorC()
    {}
    //: Default constructor.

  protected:
    CornerDetectorC(CornerDetectorBodyC &bod)
      : RCHandleC<CornerDetectorBodyC>(bod)
    {}
    //: Body constructor.
    
    CornerDetectorBodyC &Body()
    { return RCHandleC<CornerDetectorBodyC>::Body(); }
    //: Access body.
    
    const CornerDetectorBodyC &Body() const
    { return RCHandleC<CornerDetectorBodyC>::Body(); }
    //: Access body.
    
  public:
    DListC<CornerC> Apply(const ImageC<ByteT> &img)
    { return Body().Apply(img); }
    //: Get a list of corners from 'img'
    
  };

  
}



#endif
