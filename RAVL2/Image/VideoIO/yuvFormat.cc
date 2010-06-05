// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////
//! rcsid="$Id: yuvFormat.cc 342 2001-08-28 13:33:14Z craftit $"
//! lib=RavlVideoIO
//! file="Ravl/Image/VideoIO/yuvFormat.cc"

#include "Ravl/Image/yuvFormat.hh"
#include "Ravl/Image/ImgIOyuv.hh"
#include "Ravl/TypeName.hh"
#include <ctype.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {

  void InitYUVFormat() 
  {}
  
  
  // YUV ////////////////////////////////////////////////////////////////
  
  FileFormatYUVBodyC::FileFormatYUVBodyC(const StringC &nvName,const Index2dC &nvSize)
    : FileFormatBodyC(nvName,StringC("Abekas yuv images Size:") + StringC(nvSize.Row().V()) + " " + StringC(nvSize.Col().V())),
      vName(nvName),
      vSize(nvSize)
  {}
  //: Constructor.
  
  //: Is stream in std stream format ?
  // No way to tell !!
  // Just say no ??
  
  const type_info &
  FileFormatYUVBodyC::ProbeLoad(IStreamC &in,const type_info &obj_type) const { 
#if 0
    return typeid(ImageC<ByteYUVValueC>); 
#else
    return typeid(void); 
#endif
  }
  
  const type_info &
  FileFormatYUVBodyC::ProbeLoad(const StringC &nfilename,IStreamC &in,const type_info &obj_type) const {
    StringC suffix = Extension(nfilename);
    ONDEBUG(cerr << "FileFormatYUVBodyC::ProbeLoad() [" << vName << "] Called. Filename:'"<<nfilename <<" Ext:'" << suffix << "'  LoadType:'" << TypeName(obj_type) << "'\n");
    if (suffix != vName)     
      return typeid(void);
    return typeid(ImageC<ByteYUVValueC>);
  }
  
  const type_info &
  FileFormatYUVBodyC::ProbeSave(const StringC &nfilename,const type_info &obj_type,bool forceFormat) const {
    if(!forceFormat) {
      StringC suffix = Extension(nfilename);
      ONDEBUG(cerr << "FileFormatYUVBodyC::ProbeSave() [" << vName << "] Called. Filename:'"<<nfilename <<" Ext:'" << suffix << "'  LoadType:'" << TypeName(obj_type) << "'\n");
      if (suffix != vName)     
	return typeid(void);
    }
    return typeid(ImageC<ByteYUVValueC>);
  }
  
  //: Create a input port for loading.
  // Will create an Invalid port if not supported.
  
  DPIPortBaseC FileFormatYUVBodyC::CreateInput(IStreamC &in,const type_info &obj_type) const {
    ONDEBUG(cerr << "FileFormatYUVBodyC::CreateInput(IStreamC &,const type_info &), Called. \n");
    if(!in.good())
      return DPIPortBaseC();
    if(obj_type == typeid(ImageC<ByteYUVValueC>))
      return DPIImageYUVC(in,vSize);
    return DPIPortBaseC();
  }
  
  //: Create a output port for saving.
  // Will create an Invalid port if not supported.
  
  DPOPortBaseC FileFormatYUVBodyC::CreateOutput(OStreamC &out,const type_info &obj_type) const  {
    if(!out.good())
      return DPOPortBaseC();
    if(obj_type == typeid(ImageC<ByteYUVValueC>))
      return DPOImageYUVC(out,vSize);
    return DPOPortBaseC();
  }
  
  //: Create a input port for loading from file 'filename'.
  // Will create an Invalid port if not supported. <p>
  
  DPIPortBaseC FileFormatYUVBodyC::CreateInput(const StringC &filename,const type_info &obj_type) const {
    ONDEBUG(cerr << "FileFormatYUVBodyC::CreateInput(const StringC &,const type_info &), Called. \n");
    if(obj_type == typeid(ImageC<ByteYUVValueC>)) {
      IStreamC strm(filename);
      if(!strm)
	return DPIPortBaseC();
      return DPIImageYUVC(strm,vSize);
    }
    return DPIPortBaseC();
  }
  
  //: Create a output port for saving to file 'filename'..
  // Will create an Invalid port if not supported. <p>
  
  DPOPortBaseC FileFormatYUVBodyC::CreateOutput(const StringC &filename,const type_info &obj_type) const {
    if(obj_type == typeid(ImageC<ByteYUVValueC>)) {
      OStreamC strm(filename);
      if(!strm)
	return DPOPortBaseC();
      return DPOImageYUVC(strm,vSize);
    }
    return DPOPortBaseC();
  }
  
  //: Get prefered IO type.
  
  const type_info &FileFormatYUVBodyC::DefaultType() const 
  { return typeid(ImageC<ByteYUVValueC>); }
  
  
  // Some common cif formats.
  
  FileFormatYUVC RegisterFileFormatYUV  ("yuv"  ,Index2dC(576,720));
}

