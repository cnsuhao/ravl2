////////////////////////////////////////////////////////
//! rcsid="$Id: PixelIO.cc 1744 2002-09-30 09:23:23Z craftit $"

#include "amma/DP/FileFormatStream.hh"
#include "amma/DP/Converter.hh"
#include "amma/DList.hh"
#include "amma/Point2d.hh"
#include "amma/TypeName.hh"
#include "amma/Pixel.hh"

Point2dC  DPConvPixel2Point2d(const PixelC &dat)  
{ return Point2dC(dat); }

DListC<Point2dC> DPConvDListC_Pixel2DListC_Point2d(const DListC<PixelC> &dat)  
{ 
  DListC<Point2dC> ret;
  for(ConstDLIterC<PixelC> it(dat);it.IsElm();it.Next())
    ret.InsLast(it.Data());
  return ret;; 
}

DP_REGISTER_CONVERSION(DPConvPixel2Point2d,1);
DP_REGISTER_CONVERSION(DPConvDListC_Pixel2DListC_Point2d,1);
