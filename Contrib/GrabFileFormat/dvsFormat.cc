// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////
//! rcsid="$Id: dvsFormat.cc 342 2001-08-28 13:33:14Z simone $"
//! lib=RavlDVSFileFormat
//! file="Ravl/DVSFileFormat/dvsFormat.cc"

#include "Ravl/Image/dvsFormat.hh"
#include "Ravl/Image/ImgIOdvsyuv.hh"
#include "Ravl/Image/ImgIOdvsrgb.hh"
#include "Ravl/TypeName.hh"
#include <ctype.h>
#include "Ravl/Image/NewGrabfileReader.hh"
#include "Ravl/Image/NewGrabfileWriter.hh"
#include "Ravl/Stream.hh"
#include "Ravl/StrStream.hh"


using namespace RavlImageN;
using namespace RavlN;

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {

  void InitDVSYUV422Format() 
  {
  }
  
  // DVSYUV422 ////////////////////////////////////////////////////////////////
  
  FileFormatDVSYUV422BodyC::FileFormatDVSYUV422BodyC(const StringC &nvName,const Index2dC &nvSize)
    : FileFormatBodyC(nvName,StringC("YUV422 images Size:") + StringC(nvSize.Row().V()) + " " + StringC(nvSize.Col().V())),
      vName(nvName),
      vSize(nvSize)
  {
  file_writer_pointer = 0;
  file_reader_pointer = 0;
  }
  //: Constructor.
  
  //: Is stream in std stream format ?
  // No way to tell !!
  // Just say no ??
  
  const type_info &
  FileFormatDVSYUV422BodyC::ProbeLoad(IStreamC &in,const type_info &obj_type) const { 
    file_reader_pointer = NewGrabfileReader(in.Name(), false);
    if(file_reader_pointer->Open(in.Name().chars())) { //, mode)) {
       switch(IdToColourMode(file_reader_pointer->ColourMode())) {
          case YUV422: {
             return typeid(ImageC<ByteYUV422ValueC>);
          }
          case RGB_RGB: {
             return typeid(ImageC<ByteRGBValueC>);
          }
          default: {
             RavlIssueError("Unknown Colour Mode in FileFormatYCrCbBodyC::ProbeLoad.") ;
          }
        }
    }
    else {
       RavlIssueError("Could not open grab file.") ;
       return typeid(void);
    }
  }
  
  const type_info &
  FileFormatDVSYUV422BodyC::ProbeLoad(const StringC &nfilename,IStreamC &in,const type_info &obj_type) const {
    StringC suffix = Extension(nfilename);
    ONDEBUG(cerr << "FileFormatDVSYUV422BodyC::ProbeLoad() [" << vName << "] Called. Filename:'"<<nfilename <<" Ext:'" << suffix << "'  LoadType:'" << TypeName(obj_type) << "'\n");
    if (suffix != vName) {     
       return typeid(void);
    }
    else {
       return ProbeLoad(in,obj_type);
    }
  }
  
  const type_info &
  FileFormatDVSYUV422BodyC::ProbeSave(const StringC &nfilename,const type_info &obj_type,bool forceFormat) const {
    if(!forceFormat) {
      StringC suffix = Extension(nfilename);
      ONDEBUG(cerr << "FileFormatDVSYUV422BodyC::ProbeSave() [" << vName << "] Called. Filename:'"<<nfilename <<" Ext:'" << suffix << "'  LoadType:'" << TypeName(obj_type) << "'\n");
      if (suffix != vName) {     
	return typeid(void);
      }
    }
       if(obj_type == typeid(ImageC<ByteYUV422ValueC>)) {
          cmode = YUV422;
	  bformat = BITS_10_DVS;
	  vmode = SMPTE274_25I;
       }
       if(obj_type == typeid(ImageC<ByteRGBValueC>)) {
          cmode = RGB_RGB;
	  bformat = BITS_8;
	  vmode = PAL;
       }
       //: Setup the card
   
	file_writer_pointer = NewGrabfileWriter(1);
    if(file_writer_pointer->Openva(nfilename,IdToVideoMode(vmode),IdToByteFormat(bformat),IdToColourMode(cmode),1245184,0)) {
       //Check for YUV422 or RGB in header then return appropriate typeid.
          if(obj_type == typeid(ImageC<ByteYUV422ValueC>)) {
             return typeid(ImageC<ByteYUV422ValueC>);
          }
	  else if(obj_type == typeid(ImageC<ByteRGBValueC>)) {
             return typeid(ImageC<ByteRGBValueC>);
          }
	  else {
             RavlIssueError("Unknown Colour Mode in FileFormatYCrCbBodyC::ProbeLoad.") ;
	     return typeid(void);
          }
        }
    }
  
  //: Create a input port for loading.
  // Will create an Invalid port if not supported.
  
  DPIPortBaseC FileFormatDVSYUV422BodyC::CreateInput(IStreamC &in,const type_info &obj_type) const {
    ONDEBUG(cerr << "FileFormatDVSYUV422BodyC::CreateInput(IStreamC &,const type_info &), Called. \n");
    if(!in.good()) {
      return DPIPortBaseC();
    }
    if(obj_type == typeid(ImageC<ByteYUV422ValueC>)) {
      return DPIImageDVSYUV422C(*file_reader_pointer,in,vSize);
    }
    if(obj_type == typeid(ImageC<ByteRGBValueC>)) {
      return DPIImageDVSRGBC(*file_reader_pointer,in,Index2dC(576,720));
    }
    return DPIPortBaseC();
  }
  
  //: Create a output port for saving.
  // Will create an Invalid port if not supported.
  
  DPOPortBaseC FileFormatDVSYUV422BodyC::CreateOutput(OStreamC &out,const type_info &obj_type) const  {
    /*if(!out.good()) {
      return DPOPortBaseC();
    }*/
    if(obj_type == typeid(ImageC<ByteYUV422ValueC>)) {
      return DPOImageDVSYUV422C(*file_writer_pointer,out,vSize);
    }
    if(obj_type == typeid(ImageC<ByteRGBValueC>)) {
      return DPOImageDVSRGBC(*file_writer_pointer,out,vSize);
    }
    return DPOPortBaseC();
  }
  
  //: Create a input port for loading from file 'filename'.
  // Will create an Invalid port if not supported. <p>
  
  DPIPortBaseC FileFormatDVSYUV422BodyC::CreateInput(const StringC &filename,const type_info &obj_type) const {
    ONDEBUG(cerr << "FileFormatDVSYUV422BodyC::CreateInput(const StringC &,const type_info &), Called. \n");
    if(obj_type == typeid(ImageC<ByteYUV422ValueC>)) {
      IStreamC strm(filename);
      if(!strm) {
	return DPIPortBaseC();
      }
      return DPIImageDVSYUV422C(*file_reader_pointer,strm,vSize);
    }
    if(obj_type == typeid(ImageC<ByteRGBValueC>)) {
      IStreamC strm(filename);
      if(!strm) {
	return DPIPortBaseC();
      }
      return DPIImageDVSRGBC(*file_reader_pointer,strm,vSize);
    }
    return DPIPortBaseC();
  }
  
  //: Create a output port for saving to file 'filename'..
  // Will create an Invalid port if not supported. <p>
  
  DPOPortBaseC FileFormatDVSYUV422BodyC::CreateOutput(const StringC &filename,const type_info &obj_type) const {
    if(obj_type == typeid(ImageC<ByteYUV422ValueC>)) {
      OStreamC strm(filename);
      return DPOImageDVSYUV422C(*file_writer_pointer,strm,vSize);
    }
    if(obj_type == typeid(ImageC<ByteRGBValueC>)) {
      OStreamC strm(filename);
      return DPOImageDVSRGBC(*file_writer_pointer,strm,vSize);
    }
    return DPOPortBaseC();
  }
  

  //Destructor.
  FileFormatDVSYUV422BodyC::~FileFormatDVSYUV422BodyC() {
     if(file_writer_pointer != NULL) {
        file_writer_pointer->Close();
     }
     if(file_reader_pointer != NULL) {
        file_reader_pointer->Close();
     }
  }

  //: Get prefered IO type.
  
  const type_info &FileFormatDVSYUV422BodyC::DefaultType() const 
  { return typeid(ImageC<ByteYUV422ValueC>); }
  
  
  // Some common dvs file formats.
  //FileFormatDVSRGBC RegisterFileFormatDVSRGB ("grab",Index2dC(576,720));
  FileFormatDVSYUV422C RegisterFileFormatDVSYUV422  ("grab"  ,Index2dC(1080,1920));
}
