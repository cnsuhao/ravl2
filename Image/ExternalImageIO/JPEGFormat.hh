#ifndef JPEGFORMAT_HEADER
#define JPEGFORMAT_HEADER 1
////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="amma/Image/ExtImgIO/JPEGFormat.hh"
//! lib=ExtImgIO
//! author="Charles Galambos"
//! docentry="Image.Image IO"
//! date="29/10/98"

#include "amma/DP/FileFormat.hh"
#include "amma/Image.hh"
#include "amma/RGBValue.hh"

//! userlevel=Develop
//: JPEG File format information.

class FileFormatJPEGBodyC 
  : public FileFormatBodyC 
{
public:
  FileFormatJPEGBodyC();
  //: Default constructor.

  FileFormatJPEGBodyC(int comp,int pri,const StringC &name,const StringC &desc);
  //: Constructor.
  
  const type_info &ChooseFormat(const type_info &obj_type) const;
  //: Try and choose best format for IO.
  
  virtual const type_info &ProbeLoad(IStreamC &in,const type_info &obj_type) const;
  //: Is stream in std stream format ?
  
  virtual const type_info &ProbeLoad(const FilenameC &filename,IStreamC &in,const type_info &obj_type) const;
  //: Probe for load.

  virtual const type_info &ProbeSave(const FilenameC &filename,const type_info &obj_type,BooleanT forceFormat) const;
  //: Probe for Save.
  
  virtual DPIPortBaseC CreateInput(const FilenameC &filename,const type_info &obj_type) const;
  //: Create a input port for loading from file 'filename'.
  // Will create an Invalid port if not supported. <p>
  
  virtual DPOPortBaseC CreateOutput(const FilenameC &filename,const type_info &obj_type) const;
  //: Create a output port for saving to file 'filename'..
  // Will create an Invalid port if not supported. <p>
  
  virtual DPIPortBaseC CreateInput(IStreamC &in,const type_info &obj_type) const;
  //: Create a input port for loading.
  // Will create an Invalid port if not supported.
  
  virtual DPOPortBaseC CreateOutput(OStreamC &out,const type_info &obj_type) const;
  //: Create a output port for saving.
  // Will create an Invalid port if not supported.
  
  virtual const type_info &DefaultType() const; 
  //: Get prefered IO type.
  
  virtual IntT Priority() const { return pri; }
  //: Find the priority of the format. the higher the better.
  // Default is zero, this is better than the default (streams.)
  
  virtual BooleanT IsStream() const { return TRUE; }
  //: Test if format is a fully streamable.
  // i.e. check if you can read/write more than object object.
  // jpeg supports sequences.. but not with this software for now...

protected:
  int compression;
  int pri;
};

/////////////////////////////
//! userlevel=Advanced
//: Create an instance of a JPEG File Format.

class FileFormatJPEGC : public FileFormatC<ImageC<ByteGreyValueT> > {
public:
  FileFormatJPEGC(int comp,int pri,const StringC &name,const StringC &desc)
    : FileFormatC<ImageC<ByteGreyValueT> >(*new FileFormatJPEGBodyC(comp,pri,name,desc))
  {}
};

#endif
