/////////////////////////////////////////////////////////
// $Id$

#include "amma/RGBImage.hh"
#include "amma/DP/FileFormatGen.hh"
#include "amma/DP/FuncPort.hh"

void InitCompatIORGB()
{}

//// Bitmap support //////////////////////////////////////////////////

static BooleanT RGBImageBMPLoadFunc(FilenameC &fn, RGBImageC &dat) {
  dat = RGBImageC(fn);
  return dat.IsValid();
}

static BooleanT RGBImageBMPSaveFunc(FilenameC &fn,const RGBImageC &dat) {
  const_cast<RGBImageC &>(dat).SaveAs(fn,BM_24);
  return true;
}

static DPIPortBaseC RGBImageBMPLoadPort(const FilenameC &fn) {
  FilenameC aFn(fn);
  return DPFuncIPortC<RGBImageC,FilenameC>(aFn,&RGBImageBMPLoadFunc);
}

static DPOPortBaseC RGBImageBMPSavePort(const FilenameC &fn) {
  FilenameC aFn(fn);
  return DPFuncOPortC<RGBImageC,FilenameC>(aFn,&RGBImageBMPSaveFunc);
}

FileFormatGenericC RGBImageBMPIO("bmp",
				typeid(RGBImageC),
				RGBImageBMPLoadPort,
				RGBImageBMPSavePort,
				"Microsoft Bitmap format  24-bit",
				"bmp",
				false,
				-5);


//// Ary support //////////////////////////////////////////////////

static BooleanT RGBImageARYLoadFunc(FilenameC &fn, RGBImageC &dat) {
  dat = RGBImageC(fn);
  return dat.IsValid();
}

static BooleanT RGBImageARYSaveFunc(FilenameC &fn,const RGBImageC &dat) {
  const_cast<RGBImageC &>(dat).SaveAs(fn,ARY_RGB_R8);
  return true;
}

static DPIPortBaseC RGBImageARYLoadPort(const FilenameC &fn) {
  FilenameC aFn(fn);
  return DPFuncIPortC<RGBImageC,FilenameC>(aFn,&RGBImageARYLoadFunc);
}

static DPOPortBaseC RGBImageARYSavePort(const FilenameC &fn) {
  FilenameC aFn(fn);
  return DPFuncOPortC<RGBImageC,FilenameC>(aFn,&RGBImageARYSaveFunc);
}

FileFormatGenericC RGBImageARYIO("ary-rgb",
				typeid(RGBImageC),
				RGBImageARYLoadPort,
				RGBImageARYSavePort,
				"RGB Uos ARY format, 8 byte per value",
				"ary",
				false,
				-5,
				StringC(3,"ARY"));

