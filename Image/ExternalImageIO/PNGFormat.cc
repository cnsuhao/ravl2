//////////////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/Image/PNGFormat.hh"
#include "amma/Image/ImgIOPNGB.hh"
#include "amma/ByteImag.hh"
#include "amma/TypeName.hh"
#include <ctype.h>

#define DPDEBUG 0

#if DPDEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

void InitPNGFormat()
{}


// PNG ////////////////////////////////////////////////////////////////

//: Constructor.

FileFormatPNGBodyC::FileFormatPNGBodyC(BooleanT nonly16Bit,const StringC &id,const StringC &desc)
  : FileFormatBodyC(id,desc),
    only16Bit(nonly16Bit)
{}

//: Try and choose best format for IO.

const type_info &FileFormatPNGBodyC::ChooseFormat(const type_info &obj_type) const 
{
  if(!only16Bit) {
    if(obj_type == typeid(ImageC<ByteRGBValueC>))
      return obj_type; // We know how do this as well.
    if(obj_type == typeid(ImageC<ByteGreyValueT>))
      return obj_type; // We know how do this as well.
    if(obj_type == typeid(ImageC<ByteRGBXValueC>)) 
      return obj_type; // We know how do this as well.  
    if(obj_type == typeid(ImageC<ByteGreyValueT>)) 
      return obj_type; // We know how do this as well.    
  } else {
    
    if(obj_type == typeid(ImageC<ByteRGBValueC>))
      return typeid(ImageC<RGBValueU16C>);
    if(obj_type == typeid(ImageC<ByteRGBXValueC>))
      return typeid(ImageC<RGBValueU16C>); // Need a 16 bit RGBX ??
    if(obj_type == typeid(ImageC<ByteGreyValueT>))
      return typeid(ImageC<GreyValueU16T>); 
    if(obj_type == typeid(ImageC<ByteGreyValueT>)) 
      return typeid(ImageC<GreyValueU16T>); 
  }
  if(obj_type == typeid(ImageC<GreyValueU16T>))
    return obj_type; // We know how do this as well.      
  if(obj_type == typeid(ImageC<RGBValueU16C>)) 
    return obj_type; // We know how do this as well.      
  
  
  // Use some hints...
  
  if(obj_type == typeid(RGBImageC)) { 
    if(only16Bit) 
      return typeid(ImageC<RGBValueU16C>);
    return typeid(ImageC<ByteRGBValueC>);
  }
  
  if(obj_type == typeid(ByteImageC) || obj_type == typeid(ImageC<SByteGreyValueT>)) {
    if(only16Bit) 
      return typeid(ImageC<GreyValueU16T>);
    return typeid(ImageC<ByteGreyValueT>);
  }
  
  // Look for a single component hints...
  
  if(obj_type == typeid(ImageC<IntT>) || obj_type == typeid(ImageC<UIntT>) ||
     obj_type == typeid(ImageC<UInt16T>) || obj_type == typeid(ImageC<Int16T>) ||
     obj_type == typeid(ImageC<DoubleImageValueT>) 
     )
    return typeid(ImageC<GreyValueU16T>);
  
  // We could have a peak in the file and try and decide what's best here.
  // but just return an RGB image will work, just might be a little slower
  // in some cases.
  
  // Sooo do the default.
  
  if(only16Bit) 
    return typeid(ImageC<RGBValueU16C>);
  return typeid(ImageC<ByteRGBValueC>);   
}

//: Is stream in std stream format ?

const type_info &
FileFormatPNGBodyC::ProbeLoad(IStreamC &in,const type_info &obj_type) const
{
  ONDEBUG(cerr << "FileFormatPNGBodyC::ProbeLoad(), called. \n");
  if(!in.good())
    return typeid(void);
  UCharT buff[9];
  in.read((char*)buff,4);
  in.Unget((char *)buff,4);
  ONDEBUG(cerr << "FileFormatPNGBodyC::ProbeLoad(), called. " << hex << ((UIntT) buff[0])  << " " << ((UIntT) buff[1]) << " " << ((UIntT) buff[2])  << " " << ((UIntT) buff[3]) << dec << " \n");
  
  if((UIntT) buff[0] != 0x89 || (UIntT) buff[1] != 0x50 || (UIntT) buff[2] != 0x4e || (UIntT) buff[3] != 0x47)
    return typeid(void);
  
  return ChooseFormat(obj_type);
}

const type_info &
FileFormatPNGBodyC::ProbeLoad(const FilenameC &nfilename,IStreamC &in,const type_info &obj_type) const
{
  const type_info &pref = ProbeLoad(in,obj_type);
  ONDEBUG(cerr << "FileFormatPNGBodyC::ProbeLoad(), Req:" <<obj_type.name() << "  Ret:" << pref.name() << " \n");
  return  pref;
}

const type_info &
FileFormatPNGBodyC::ProbeSave(const FilenameC &filename,const type_info &obj_type,BooleanT forceFormat ) const
{
  if(!forceFormat) {
    if(!filename.HasExtension(".png") && filename != "-")
      return typeid(void);
  }
  const type_info &pref = ChooseFormat(obj_type);
  ONDEBUG(cerr << "FileFormatPNGBodyC::ProbeSave(), Req:" << obj_type.name() << "  Ret:" << pref.name() << " \n");
  return pref;
}

//: Create a input port for loading from file 'filename'.
// Will create an Invalid port if not supported. <p>
DPIPortBaseC FileFormatPNGBodyC::CreateInput(const FilenameC &fn,const type_info &obj_type) const {
  if(obj_type == typeid(ImageC<ByteRGBValueC>))
    return DPIImagePNGC<ByteRGBValueC>(fn);
  if(obj_type == typeid(ImageC<ByteGreyValueT>))
    return DPIImagePNGC<ByteGreyValueT>(fn);
  if(obj_type == typeid(ImageC<ByteGreyValueT>)) 
    return DPIImagePNGC<ByteGreyValueT>(fn);
  if(obj_type == typeid(ImageC<GreyValueU16T>)) 
    return DPIImagePNGC<GreyValueU16T>(fn);
  if(obj_type == typeid(ImageC<ByteRGBXValueC>)) 
    return DPIImagePNGC<ByteRGBXValueC>(fn);
  if(obj_type == typeid(ImageC<RGBValueU16C>)) 
    return DPIImagePNGC<RGBValueU16C>(fn);
  return DPIPortBaseC();  
}

//: Create a output port for saving to file 'filename'..
// Will create an Invalid port if not supported. <p>

DPOPortBaseC FileFormatPNGBodyC::CreateOutput(const FilenameC &fn,const type_info &obj_type) const {
  if(obj_type == typeid(ImageC<ByteRGBValueC>))
    return DPOImagePNGC<ByteRGBValueC>(fn);
  if(obj_type == typeid(ImageC<ByteGreyValueT>))
    return DPOImagePNGC<ByteGreyValueT>(fn);
  if(obj_type == typeid(ImageC<ByteGreyValueT>)) 
    return DPOImagePNGC<ByteGreyValueT>(fn);
  if(obj_type == typeid(ImageC<GreyValueU16T>)) 
    return DPOImagePNGC<GreyValueU16T>(fn);
  if(obj_type == typeid(ImageC<ByteRGBXValueC>)) 
    return DPOImagePNGC<ByteRGBXValueC>(fn);
  if(obj_type == typeid(ImageC<RGBValueU16C>)) 
    return DPOImagePNGC<RGBValueU16C>(fn);
  return DPOPortBaseC();
}

//: Create a input port for loading.
// Will create an Invalid port if not supported.

DPIPortBaseC FileFormatPNGBodyC::CreateInput(IStreamC &in,const type_info &obj_type) const
{
  if(obj_type == typeid(ImageC<ByteRGBValueC>))
    return DPIImagePNGC<ByteRGBValueC>(in);
  if(obj_type == typeid(ImageC<ByteGreyValueT>))
    return DPIImagePNGC<ByteGreyValueT>(in);
  if(obj_type == typeid(ImageC<ByteGreyValueT>)) 
    return DPIImagePNGC<ByteGreyValueT>(in);
  if(obj_type == typeid(ImageC<GreyValueU16T>)) 
    return DPIImagePNGC<GreyValueU16T>(in);
  if(obj_type == typeid(ImageC<ByteRGBXValueC>)) 
    return DPIImagePNGC<ByteRGBXValueC>(in);
  if(obj_type == typeid(ImageC<RGBValueU16C>)) 
    return DPIImagePNGC<RGBValueU16C>(in);
  return DPIPortBaseC();
}

//: Create a output port for saving.
// Will create an Invalid port if not supported.

DPOPortBaseC FileFormatPNGBodyC::CreateOutput(OStreamC &out,const type_info &obj_type) const 
{
  if(obj_type == typeid(ImageC<ByteRGBValueC>))
    return DPOImagePNGC<ByteRGBValueC>(out);
  if(obj_type == typeid(ImageC<ByteGreyValueT>))
    return DPOImagePNGC<ByteGreyValueT>(out);
  if(obj_type == typeid(ImageC<ByteGreyValueT>)) 
    return DPOImagePNGC<ByteGreyValueT>(out);
  if(obj_type == typeid(ImageC<GreyValueU16T>)) 
    return DPOImagePNGC<GreyValueU16T>(out);
  if(obj_type == typeid(ImageC<ByteRGBXValueC>)) 
    return DPOImagePNGC<ByteRGBXValueC>(out);
  if(obj_type == typeid(ImageC<RGBValueU16C>)) 
    return DPOImagePNGC<RGBValueU16C>(out);
  return DPOPortBaseC();
}

//: Get prefered IO type.

const type_info &FileFormatPNGBodyC::DefaultType() const 
{ 
  if(only16Bit)
    return typeid(ImageC<RGBValueU16C>);
  return typeid(ImageC<ByteRGBValueC>); 
}


FileFormatPNGC RegisterFileFormatPNG(false,"png","General png file IO. ");
FileFormatPNGC RegisterFileFormatPNG16(true,"png16","16 bit only png file IO. ");

