// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlAVIFile
//! file="Ravl/Contrib/AVIFile/AVIFileFormat.cc"

#include "Ravl/Image/AVIFileFormat.hh"
#include "Ravl/Image/AVIFileIO.hh"
#include "Ravl/TypeName.hh"
#include <ctype.h>

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {

  void InitAVIFileFormat()
  {} //help for the Linker
    
  // AVIFile ////////////////////////////////////////////////////////////////
  
  const StringC FileFormatAVIFileBodyC::m_strExtension("avi");

  FileFormatAVIFileBodyC::FileFormatAVIFileBodyC()
    : FileFormatBodyC(m_strExtension,StringC("AVI video sequences."))
  {}
  //: Constructor.
  

  const type_info &
  FileFormatAVIFileBodyC::ProbeLoad(IStreamC &in,const type_info &obj_type) const
  { return typeid(void); }

  const type_info &
  FileFormatAVIFileBodyC::ProbeLoad(const StringC &nfilename,IStreamC &in,const type_info &obj_type) const {
    return typeid(void);
  }
  
  const type_info &
  FileFormatAVIFileBodyC::ProbeSave(const StringC &nfilename,const type_info &obj_type,bool forceFormat) const 
  {
    StringC suffix = Extension(nfilename);
    ONDEBUG(cerr << "FileFormatAVIFileBodyC::ProbeSave() [" << m_strExtension << "] Called. Filename:'"<<nfilename <<" Ext:'" << suffix << "'  SaveType:'" << TypeName(obj_type) << "'\n");    
    if ((suffix.CaseCmp(m_strExtension) != 0) && (!forceFormat)) return typeid(void);
    //other checks to be placed here.      
    return typeid(ImageC<ByteRGBValueC>);
  }
  
  //: Create a input port for loading.
  // Will create an Invalid port if not supported.
  
  DPIPortBaseC FileFormatAVIFileBodyC::CreateInput(IStreamC &in,const type_info &obj_type) const 
  {
    ONDEBUG(cerr << "FileFormatAVIFileBodyC::CreateInput(IStreamC &,const type_info &), Called. \n");
    return DPIPortBaseC(); //returns the base port if the stream is not good
  }
  
  //: Create a output port for saving.
  // Will create an Invalid port if not supported.
  
  DPOPortBaseC FileFormatAVIFileBodyC::CreateOutput(OStreamC &out,const type_info &obj_type) const  
  {
    ONDEBUG(cerr << "FileFormatAVIFileBodyC::CreateOutput(OStreamC &,const type_info &), Called. \n");
    return DPOPortBaseC();
  }
  
  //: Create a input port for loading from file 'filename'.
  // Will create an Invalid port if not supported. <p>
  
  DPIPortBaseC FileFormatAVIFileBodyC::CreateInput(const StringC &filename,const type_info &obj_type) const 
  {
    ONDEBUG(cerr << "FileFormatAVIFileBodyC::CreateInput(const StringC &,const type_info &), Called. \n");
    //if (obj_type == typeid(ImageC<ByteRGBValueC>)) return DPIAVIFileC(filename);
    return DPIPortBaseC();
  }
  
  //: Create a output port for saving to file 'filename'..
  // Will create an Invalid port if not supported. <p>
  
  DPOPortBaseC FileFormatAVIFileBodyC::CreateOutput(const StringC &filename,const type_info &obj_type) const 
  {
    ONDEBUG(cerr << "FileFormatAVIFileBodyC::CreateOutput(const StringC &,const type_info &), Called \n");
    if (obj_type == typeid(ImageC<ByteRGBValueC>)) return DPOAVIFileC(filename);
    return DPOPortBaseC();
  }
  
  //: Get prefered IO type.
  
  const type_info &FileFormatAVIFileBodyC::DefaultType() const { 
    return typeid(ImageC<ByteRGBValueC>); 
  }
  
  // Some common avi formats.
  FileFormatAVIFileC RegisterFileFormatAVIFile;
  
}

