/////////////////////////////////////////////////////////
// $Id$

#include "amma/YUVImage.hh"
#include "amma/DP/FileFormatGen.hh"
#include "amma/DP/FuncPort.hh"

void InitCompatIOYUV()
{}

//// Ary support //////////////////////////////////////////////////

static BooleanT YUVImageARYLoadFunc(FilenameC &fn, YUVImageC &dat) {
  ImageIStreamC iis(fn);
  dat = YUVImageC(iis);
  return dat.IsValid();
}

static BooleanT YUVImageARYSaveFunc(FilenameC &fn,const YUVImageC &dat) {
  const_cast<YUVImageC &>(dat).SaveAs(fn,ARY_YUV_R8);
  return true;
}

static DPIPortBaseC YUVImageARYLoadPort(const FilenameC &fn) {
  FilenameC aFn(fn);
  return DPFuncIPortC<YUVImageC,FilenameC>(aFn,&YUVImageARYLoadFunc);
}

static DPOPortBaseC YUVImageARYSavePort(const FilenameC &fn) {
  FilenameC aFn(fn);
  return DPFuncOPortC<YUVImageC,FilenameC>(aFn,&YUVImageARYSaveFunc);
}

FileFormatGenericC YUVImageARYIO("ary-yuv",
				typeid(YUVImageC),
				YUVImageARYLoadPort,
				YUVImageARYSavePort,
				"YUV Uos ARY format, 8 byte per value",
				"ary",
				false,
				-5,
				StringC(3,"ARY"));

