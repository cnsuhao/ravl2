/////////////////////////////////////////////////////////
// $Id$

#include "amma/ByteImag.hh"
#include "amma/IntImage.hh"
#include "amma/DP/FileFormatGen.hh"
#include "amma/DP/FuncPort.hh"

void InitCompatIOY()
{}

//// Bitmap support //////////////////////////////////////////////////

static BooleanT YImageBMPLoadFunc(FilenameC &fn, ByteImageC &dat) {
  dat = ByteImageC(fn);
  return dat.IsValid();
}

static BooleanT YImageBMPSaveFunc(FilenameC &fn,const ByteImageC &dat) {
  const_cast<ByteImageC &>(dat).SaveAs(fn,BM_8);
  return true;
}

static DPIPortBaseC YImageBMPLoadPort(const FilenameC &fn) {
  FilenameC aFn(fn);
  return DPFuncIPortC<ByteImageC,FilenameC>(aFn,&YImageBMPLoadFunc);
}

static DPOPortBaseC YImageBMPSavePort(const FilenameC &fn) {
  FilenameC aFn(fn);
  return DPFuncOPortC<ByteImageC,FilenameC>(aFn,&YImageBMPSaveFunc);
}

FileFormatGenericC YImageBMPIO("bmp-y",
				typeid(ByteImageC),
				YImageBMPLoadPort,
				YImageBMPSavePort,
				"Microsoft Bitmap format, 8-bit",
				"bmp",
				false,
				-5);


//// Ary, byte image //////////////////////////////////////////////////

static BooleanT ByteImageARYLoadFunc(FilenameC &fn, ByteImageC &dat) {
  dat = ByteImageC(fn);
  return dat.IsValid();
}

static BooleanT ByteImageARYSaveFunc(FilenameC &fn,const ByteImageC &dat) {
  const_cast<ByteImageC &>(dat).SaveAs(fn,BARY_IFT);
  return true;
}

static DPIPortBaseC ByteImageARYLoadPort(const FilenameC &fn) {
  FilenameC aFn(fn);
  return DPFuncIPortC<ByteImageC,FilenameC>(aFn,&ByteImageARYLoadFunc);
}

static DPOPortBaseC ByteImageARYSavePort(const FilenameC &fn) {
  FilenameC aFn(fn);
  return DPFuncOPortC<ByteImageC,FilenameC>(aFn,&ByteImageARYSaveFunc);
}

FileFormatGenericC ByteImageARYIO("ary-y",
				typeid(ByteImageC),
				ByteImageARYLoadPort,
				ByteImageARYSavePort,
				"Byte Uos ARY format, 8 byte per value",
				"ary",
				false,
				-5,
				StringC(3,"ARY"));



