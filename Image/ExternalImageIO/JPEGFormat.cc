//////////////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/YUVImage.hh"
#include "amma/RGBImage.hh"
#include "amma/ByteImag.hh"

#include "amma/Image/JPEGFormat.hh"
#include "amma/Image/ImgIOJPeg.hh"
#include "amma/TypeName.hh"
#include <ctype.h>

#define DPDEBUG 0

#if DPDEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

void InitJPEGFormat()
{}

// JPEG ////////////////////////////////////////////////////////////////

//: Constructor.

FileFormatJPEGBodyC::FileFormatJPEGBodyC()
  : FileFormatBodyC("jpeg","JPEG rgb colour images.")
{}

//: Constructor.

FileFormatJPEGBodyC::FileFormatJPEGBodyC(int comp,int npri,const StringC &name,const StringC &desc)
  : FileFormatBodyC(name,desc),
    compression(comp),
    pri(npri)
{}

class DoubleImageC;

#ifdef __sgi__
static ImageC<SByteGreyValueT> stupsgibugfix1;
static ImageC<Int16T> stupsgibugfix2;
#endif

//: Try and choose best format for IO.

const type_info &FileFormatJPEGBodyC::ChooseFormat(const type_info &obj_type) const {
  if(obj_type == typeid(ImageC<ByteRGBValueC>))
    return obj_type; // We know how do this as well.
  if(obj_type == typeid(ImageC<ByteYUVValueC>))
    return obj_type; // We know how do this as well.
  if(obj_type == typeid(ImageC<ByteGreyValueT>))
    return obj_type; // We know how do this as well.
  
  // Use some hints...
  
  if(obj_type == typeid(RGBImageC))                // Use this as a hint.
    return typeid(ImageC<ByteRGBValueC>);
  if(obj_type == typeid(YUVImageC))                // Use this as a hint.
    return typeid(ImageC<ByteYUVValueC>);
  if(obj_type == typeid(ByteImageC))                // Use this as a hint.
    return typeid(ImageC<ByteGreyValueT>);
  // Look for a single component hint...
  if(obj_type == typeid(ImageC<IntT>) || obj_type == typeid(ImageC<UIntT>) ||
     obj_type == typeid(ImageC<UInt16T>) || obj_type == typeid(ImageC<Int16T>) ||
     obj_type == typeid(ImageC<SByteGreyValueT>) || obj_type == typeid(ImageC<DoubleImageValueT>) 
     )
    return typeid(ImageC<ByteGreyValueT>);
  
  // We could have a peak in the file and try and decide what's best here.
  // but just return an RGB image will work, just might be a little slower
  // in some cases.
  
  // Sooo do the default.
  
  return typeid(ImageC<ByteRGBValueC>);   
}

//: Is stream in std stream format ?

const type_info &
FileFormatJPEGBodyC::ProbeLoad(IStreamC &in,const type_info &obj_type) const
{
  ONDEBUG(cerr << "FileFormatJPEGBodyC::ProbeLoad(), called. \n");
  if(!in.good())
    return typeid(void);
  UCharT buff[3];
  in.read((char*)buff,2);
  in.Unget((char *)buff,2);
  ONDEBUG(cerr << "FileFormatJPEGBodyC::ProbeLoad(), called. " << hex << ((UIntT) buff[0])  << " " << ((UIntT) buff[1])  << dec << " \n");
  if((UIntT) buff[0] != ((UIntT) 0xff))
    return typeid(void);
  if((UIntT) buff[1] != ((UIntT) 0xd8))
    return typeid(void);
  return ChooseFormat(obj_type);
}

const type_info &
FileFormatJPEGBodyC::ProbeLoad(const FilenameC &nfilename,IStreamC &in,const type_info &obj_type) const
{
  //FilenameC filename(nfilename);
  //  if(obj_type != typeid(ImageC<ByteRGBValueC>))
  //    return FALSE; // Can only deal with rgb at the moment.
  // For Load, use stream probe its more reliable than extentions.
  return ProbeLoad(in,obj_type);
}

const type_info &
FileFormatJPEGBodyC::ProbeSave(const FilenameC &filename,const type_info &obj_type,BooleanT forceFormat ) const
{
  if(forceFormat)
    return ChooseFormat(obj_type);
  if(!filename.HasExtension(".jpg") && filename != "-")
    return typeid(void);
  const type_info &ret_type = ChooseFormat(obj_type);
  ONDEBUG(cerr << "FileFormatJPEGBodyC::ProbeSave(), Using:'" << ret_type.name() << " Requested:'" << obj_type.name() << "'\n");
  return ret_type;
}

//: Create a input port for loading from file 'filename'.
// Will create an Invalid port if not supported. <p>
DPIPortBaseC FileFormatJPEGBodyC::CreateInput(const FilenameC &filename,const type_info &obj_type) const {  
  if(obj_type == typeid(ImageC<ByteRGBValueC>))
    return DPIImageJPegByteRGBC(filename);
  if(obj_type == typeid(ImageC<ByteYUVValueC>))
    return DPIImageJPegByteYUVC(filename);
  if(obj_type == typeid(ImageC<ByteGreyValueT>))
    return DPIImageJPegByteGreyC(filename);
  return DPIPortBaseC();  
}

//: Create a output port for saving to file 'filename'..
// Will create an Invalid port if not supported. <p>
DPOPortBaseC FileFormatJPEGBodyC::CreateOutput(const FilenameC &filename,const type_info &obj_type) const {
  if(obj_type == typeid(ImageC<ByteRGBValueC>))
    return  DPOImageJPegByteRGBC(filename,compression);
  if(obj_type == typeid(ImageC<ByteYUVValueC>))
    return  DPOImageJPegByteYUVC(filename,compression);
  if(obj_type == typeid(ImageC<ByteGreyValueT>))
    return  DPOImageJPegByteGreyC(filename,compression);
  return DPOPortBaseC();
}

//: Create a input port for loading.
// Will create an Invalid port if not supported.

DPIPortBaseC FileFormatJPEGBodyC::CreateInput(IStreamC &in,const type_info &obj_type) const
{
  if(obj_type == typeid(ImageC<ByteRGBValueC>))
    return DPIImageJPegByteRGBC(in);
  if(obj_type == typeid(ImageC<ByteYUVValueC>))
    return DPIImageJPegByteYUVC(in);
  if(obj_type == typeid(ImageC<ByteGreyValueT>))
    return DPIImageJPegByteGreyC(in);
  return DPIPortBaseC();
}

//: Create a output port for saving.
// Will create an Invalid port if not supported.

DPOPortBaseC FileFormatJPEGBodyC::CreateOutput(OStreamC &out,const type_info &obj_type) const 
{
  if(obj_type == typeid(ImageC<ByteRGBValueC>))
    return  DPOImageJPegByteRGBC(out,compression);
  if(obj_type == typeid(ImageC<ByteYUVValueC>))
    return  DPOImageJPegByteYUVC(out,compression);
  if(obj_type == typeid(ImageC<ByteGreyValueT>))
    return  DPOImageJPegByteGreyC(out,compression);
  return DPOPortBaseC();
}

//: Get prefered IO type.

const type_info &FileFormatJPEGBodyC::DefaultType() const 
{ return typeid(ImageC<ByteRGBValueC>); }


FileFormatJPEGC RegisterFileFormatJPEG(100,0,"jpeg","JPEG image file format.  Default lossless compression.");
FileFormatJPEGC RegisterFileFormatJPEGL(75,-25,"jpegl","JPEG image file format.  Default 75% lossy compression.");

