// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlVideoIO
//! file="Ravl/Image/VideoIO/AviFormat.cc"

#include "Ravl/Image/AviFormat.hh"

#include "Ravl/Image/RGBFrmIOAvi.hh"
#include "Ravl/Image/DVFrmIOAvi.hh"

#include "Ravl/TypeName.hh"
#include <ctype.h>

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {

  void InitAviFormat()
  {} //help for the Linker
    
  // Avi ////////////////////////////////////////////////////////////////
  
  FileFormatAviBodyC::FileFormatAviBodyC(const StringC &nvName)
    : FileFormatBodyC(nvName,StringC("Avi frame sequences.")),
      vName(nvName)
  {}
  //: Constructor.
  

  //: Is stream in std stream format ?
  // Assume it is...  if it doesn't work, the user will have to sort it out...
  
  const type_info &
  FileFormatAviBodyC::ProbeLoad(IStreamC &in,const type_info &obj_type) const
  { return typeid(ImageC<ByteRGBValueC>); }

  const type_info &
  FileFormatAviBodyC::ProbeLoad(const StringC &nfilename,IStreamC &in,const type_info &obj_type) const {
    StringC suffix = Extension(nfilename); //  the file can be checked by extension
    ONDEBUG(cerr << "FileFormatAviBodyC::ProbeLoad() [" << vName << "] Called. Filename:'"<< nfilename <<" Ext:'" << suffix << "'  LoadType:'" << TypeName(obj_type) << "'\n");
    
    //LIST OF CHECKS to be placed here.   
    //checks the file extension  

    if (suffix != vName) 
      {
	ONDEBUG(cerr << "ERROR: not an AVI file\n");
	return typeid(void);
      }

    //checks whether the video stream exists
    
    in.Seek((streampos)108);
    char token[4];
    in.read(token,4);
    bool isVids = (token[0] == 'v') && (token[1] == 'i') && (token[2] == 'd') && (token[3] == 's');
    bool isIavs = (token[0] == 'i') && (token[1] == 'a') && (token[2] == 'v') && (token[3] == 's');

    if(!isVids && !isIavs ) 
      {
	ONDEBUG(cerr << "ERROR: file: " << nfilename << " doesn't contain a video stream!\n");
	return typeid(void);
      }
    else
      {
	in.read(token,4);
	if( (token[0] == (char)0) && (token[1] == (char)0) && (token[2] == (char)0) && (token[3] == (char)0) )
	  return typeid(ImageC<ByteRGBValueC>);
	if( (token[0] == 'd') && (token[1] == 'v') && (token[2] == 's') && (token[3] == 'd') )
	  return typeid(DVFrameC);
	else
	  {
	    ONDEBUG(cerr << "ERROR: video stream in file: " << nfilename << " is not a known video format\n";)
	    return typeid(void);
	  }
      }
  }
  
  const type_info &
  FileFormatAviBodyC::ProbeSave(const StringC &nfilename,const type_info &obj_type,bool forceFormat) const 
  {
    StringC suffix = Extension(nfilename);
    ONDEBUG(cerr << "FileFormatAviBodyC::ProbeSave() [" << vName << "] Called. Filename:'"<<nfilename <<" Ext:'" << suffix << "'  LoadType:'" << TypeName(obj_type) << "'\n");
    if ((suffix != vName) && (!forceFormat)) return typeid(void); //this only effects if the extension check is explicitely required
    if(obj_type == typeid(DVFrameC))
      return typeid(DVFrameC);
    //other checks to be placed here.      
    return typeid(ImageC<ByteRGBValueC>); //save into a raw RGB image avi file by default
  }
  
  //: Create a input port for loading.
  // Will create an Invalid port if not supported.
  
  DPIPortBaseC FileFormatAviBodyC::CreateInput(IStreamC &in,const type_info &obj_type) const 
  {
    ONDEBUG(cerr << "FileFormatAviBodyC::CreateInput(IStreamC &,const type_info &), Called. \n");
    if(in)
      {   
	if(obj_type == typeid(ImageC<ByteRGBValueC>)) return DPISRGBAviFrameC(in);//if RGB creates a RGB input port
	if(obj_type == typeid(DVFrameC)) return DPISDVAviFrameC(in);//if DV creates a DV input port
      }
    return DPIPortBaseC(); //returns the base port if the stream is not good
  }
  
  //: Create a output port for saving.
  // Will create an Invalid port if not supported.
  
  DPOPortBaseC FileFormatAviBodyC::CreateOutput(OStreamC &out,const type_info &obj_type) const  
  {
    if(out)
      {
	if(obj_type == typeid(ImageC<ByteRGBValueC>)) return DPOSRGBAviFrameC(out);
	if(obj_type == typeid(DVFrameC)) return DPOSDVAviFrameC(out);//if DV creates a DV input port
      }
    return DPOPortBaseC();
  }
  
  //: Create a input port for loading from file 'filename'.
  // Will create an Invalid port if not supported. <p>
  
  DPIPortBaseC FileFormatAviBodyC::CreateInput(const StringC &filename,const type_info &obj_type) const 
  {
    ONDEBUG(cerr << "FileFormatAviBodyC::CreateInput(const StringC &,const type_info &), Called. \n");
    
    IStreamC strm(filename);
    if(strm)
      {
	if(obj_type == typeid(ImageC<ByteRGBValueC>)) return DPISRGBAviFrameC(strm);
	if(obj_type == typeid(DVFrameC)) return DPISDVAviFrameC(strm);
      }
    return DPIPortBaseC();
  }
  
  //: Create a output port for saving to file 'filename'..
  // Will create an Invalid port if not supported. <p>
  
  DPOPortBaseC FileFormatAviBodyC::CreateOutput(const StringC &filename,const type_info &obj_type) const 
  {
    OStreamC strm(filename);
    if(strm)
      {
	if(obj_type == typeid(ImageC<ByteRGBValueC>)) return DPOSRGBAviFrameC(strm);
	if(obj_type == typeid(DVFrameC)) return DPOSDVAviFrameC(strm);//if DV creates a DV input port
      }
    return DPOPortBaseC();
  }
  
  //: Get prefered IO type.
  
  const type_info &FileFormatAviBodyC::DefaultType() const { 
    return typeid(ImageC<ByteRGBValueC>); 
  }
  
  // Some common avi formats.
  FileFormatAviC RegisterFileFormatAvi("avi");
  
}

