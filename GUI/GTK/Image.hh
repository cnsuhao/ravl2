#ifndef GUIIMAGE_HEADER
#define GUIIMAGE_HEADER
////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/GUI/Widget.hh"

//! userlevel=Develop
//: Image body

class GUIImageBodyC 
  : public GUIWidgetBodyC
{
public:
  GUIImageBodyC(const ImageC<ByteRGBValueC> &img);
  //: Constructor.
  
  virtual BooleanT Create();
  //: Create the widget.
  
  virtual BooleanT Service();
  //: Service request.
  // Used to send signals from other
  // threads to the program.  
  
  ImageC<ByteRGBValueC> &Image()
    { return img; }
  //: Access image.
  
protected:
  ImageC<ByteRGBValueC> img;
};

//! userlevel=Normal
//: Image 

class GUIImageC 
  : public GUIWidgetC
{
public:
  GUIImageC(const ImageC<ByteRGBValueC> &img)
    : DPEntityC(*new GUIImageBodyC(img))
    {}
  //: Default constructor
  
protected:

  GUIImageBodyC &Body() 
    { return dynamic_cast<GUIImageBodyC &>(DPEntityC::Body()); }
  //: Access body.
  
  const  GUIImageBodyC &Body() const
    { return dynamic_cast<const GUIImageBodyC &>(DPEntityC::Body()); }
  //: Access body.  
  
public:
  
  ImageC<ByteRGBValueC> &Image()
    { return Body().Image(); }
  //: Access image.
  
};

#endif
