#ifndef RAVLGUIBITMAP_HEADER
#define RAVLGUIBITMAP_HEADER 1
////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/GUI/GTK/Bitmap.hh"
//! lib=GUI
//! userlevel=Normal
//! docentry="Ravl.GUI.Layout"
//! author="Charles Galambos"
//! date="17/08/2000"

#include "Ravl/GUI/Widget.hh"

namespace RavlGUIN {
  //: Bitmap body.
  
  class BitmapBodyC 
    : public RCBodyC
  {
  public:
    BitmapBodyC(int width,int height);
    //: Create a bit map of the given size.
    
    ~BitmapBodyC();
    //: Destructor.
  
    GdkBitmap &Bitmap()
      { return *bmp; }
    //: access bitmap.
    
    void Clear();
    //: Clear the bitmap.
    
  protected:
    int width,height;
    GdkBitmap *bmp;
  };
  
  //: Bitmap.
  // Hold a binary image. often used as a mask.
  
  class BitmapC 
    : public RCHandleC<BitmapBodyC>
  {
  public:
    BitmapC()
      {}
    //: Default constructor.
    // creates an invalid handle.
    
    BitmapC(int width,int height) 
      : RCHandleC<BitmapBodyC>(*new BitmapBodyC(width,height))
      {}
    //: Create a bit map of the given size.
    
    GdkBitmap &Bitmap()
      { return Body().Bitmap(); }
    //: access bitmap.
    
    void Clear()
      { Body().Clear(); }
    //: Clear the bitmap.
    
  };
}

#endif
