//////////////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/Image/TiffFormat.hh"
#include "amma/Image/ImgIOTiffB.hh"
#include "amma/Image/ImgIOTiff.hh"
#include "amma/ByteImag.hh"
#include "amma/TypeName.hh"
#include <ctype.h>

#define USE_TIFFWRITE 1

#define DPDEBUG 0

#if DPDEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

void InitTIFFFormat()
{}


// TIFF ////////////////////////////////////////////////////////////////

//: Constructor.

FileFormatTIFFBodyC::FileFormatTIFFBodyC(const StringC &id,const StringC &desc)
  : FileFormatBodyC(id,desc)
{}

//: Try and choose best format for IO.

const type_info &FileFormatTIFFBodyC::ChooseFormat(const type_info &obj_type) const 
{
  return typeid(ImageC<ByteRGBXValueC>);   
}

//: Is stream in std stream format ?

const type_info &
FileFormatTIFFBodyC::ProbeLoad(IStreamC &in,const type_info &obj_type) const
{
  ONDEBUG(cerr << "FileFormatTIFFBodyC::ProbeLoad(), called. \n");
  if(!in.good())
    return typeid(void);
  UCharT buff[9];
  in.read((char*)buff,4);
  in.Unget((char *)buff,4);
  ONDEBUG(cerr << "FileFormatTIFFBodyC::ProbeLoad(),  " << hex << ((UIntT) buff[0])  << " " << ((UIntT) buff[1]) << " " << ((UIntT) buff[2])  << " " << ((UIntT) buff[3]) << dec << " \n");
  
  if((UIntT) buff[0] == 0x49 && (UIntT) buff[1] == 0x49) {
    if((UIntT) buff[2] == 0x2a && (UIntT) buff[3] == 0)
      return typeid(ImageC<ByteRGBXValueC>);   
  }
  
  if((UIntT) buff[0] == 0x4d && (UIntT) buff[1] == 0x4d) {
    if((UIntT) buff[2] == 0 && (UIntT) buff[3] == 0x2a)
      return typeid(ImageC<ByteRGBXValueC>);   
  }
  ONDEBUG(cerr << "FileFormatTIFFBodyC::ProbeLoad(), Not a tiff. \n");
  return typeid(void); 
}

const type_info &
FileFormatTIFFBodyC::ProbeLoad(const FilenameC &nfilename,IStreamC &in,const type_info &obj_type) const
{
  const type_info &pref = ProbeLoad(in,obj_type);
  ONDEBUG(cerr << "FileFormatTIFFBodyC::ProbeLoad(), Req:" <<obj_type.name() << "  Ret:" << pref.name() << " \n");
  return  pref;
}

const type_info &
FileFormatTIFFBodyC::ProbeSave(const FilenameC &filename,const type_info &obj_type,BooleanT forceFormat ) const
{
#if USE_TIFFWRITE
  if(!forceFormat) {
    if(!filename.HasExtension(".tif") && filename != "-")
      return typeid(void);
  }
  const type_info &pref = ChooseFormat(obj_type);
  ONDEBUG(cerr << "FileFormatTIFFBodyC::ProbeSave(), Req:" << obj_type.name() << "  Ret:" << pref.name() << " \n");
  return pref;
#else
  return typeid(void);   
#endif
}

//: Create a input port for loading from file 'filename'.
// Will create an Invalid port if not supported. <p>
DPIPortBaseC FileFormatTIFFBodyC::CreateInput(const FilenameC &fn,const type_info &obj_type) const {
  return DPIImageTIFFByteRGBAC(fn);
}

//: Create a output port for saving to file 'filename'..
// Will create an Invalid port if not supported. <p>

DPOPortBaseC FileFormatTIFFBodyC::CreateOutput(const FilenameC &fn,const type_info &obj_type) const {
#if USE_TIFFWRITE
  return DPOImageTIFFByteRGBAC(fn);
#else
  return DPOPortBaseC();  
#endif
}

//: Create a input port for loading.
// Will create an Invalid port if not supported.

DPIPortBaseC FileFormatTIFFBodyC::CreateInput(IStreamC &in,const type_info &obj_type) const
{ return DPIImageTIFFByteRGBAC(in); }

//: Create a output port for saving.
// Will create an Invalid port if not supported.

DPOPortBaseC FileFormatTIFFBodyC::CreateOutput(OStreamC &out,const type_info &obj_type) const 
{
#if USE_TIFFWRITE
  return DPOImageTIFFByteRGBAC(out);
#else
  return DPOPortBaseC();  
#endif
}

//: Get prefered IO type.

const type_info &FileFormatTIFFBodyC::DefaultType() const 
{ return typeid(ImageC<ByteRGBXValueC>); }

#if USE_TIFFWRITE
FileFormatTIFFC RegisterFileFormatTIFF("tiff","Tiff file IO. ");
#else
FileFormatTIFFC RegisterFileFormatTIFF("tiff","Tiff file IO. (only reading supported)");
#endif

