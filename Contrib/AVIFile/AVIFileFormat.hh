// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_AVIFILEFORMAT_HEADER
#define RAVLIMAGE_AVIFILEFORMAT_HEADER 1
////////////////////////////////////////////////////////////
//! author="James Smith"
//! docentry="Ravl.API.Images.Video.Video IO"
//! date="19/01/2004"
//! rcsid="$Id: AVIFileFormat.hh 5240 2005-12-06 17:16:50Z plugger $"
//! file="Ravl/Contrib/AVIFile/AVIFileFormat.hh"
//! example=testAVIFile.cc
//! lib=RavlAVIFile

#include "Ravl/DP/FileFormat.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"

namespace RavlImageN {

  //! userlevel=Develop
  //: Avi File format information.
  
  class FileFormatAVIFileBodyC 
    : public FileFormatBodyC 
  {
  public:
    FileFormatAVIFileBodyC();
    //: Constructor.
    
    virtual const type_info &ProbeLoad(IStreamC &in,const type_info &obj_type) const;
    //: Is stream in std stream format ?
    
    virtual const type_info &ProbeLoad(const StringC &filename,IStreamC &in,const type_info &obj_type) const;
    //: Probe for load.
    
    virtual const type_info &ProbeSave(const StringC &filename,const type_info &obj_type,bool forceFormat) const;
    //: Probe for Save.
    
    virtual DPIPortBaseC CreateInput(IStreamC &in,const type_info &obj_type) const;
    //: Create a input port for loading.
    // Will create an Invalid port if not supported.
    
    virtual DPOPortBaseC CreateOutput(OStreamC &out,const type_info &obj_type) const;
    //: Create a output port for saving.
    // Will create an Invalid port if not supported.
    
    virtual DPIPortBaseC CreateInput(const StringC &filename,const type_info &obj_type) const;
    //: Create a input port for loading from file 'filename'.
    // Will create an Invalid port if not supported. <p>
    
    virtual DPOPortBaseC CreateOutput(const StringC &filename,const type_info &obj_type) const;
    //: Create a output port for saving to file 'filename'..
    // Will create an Invalid port if not supported. <p>
    
    virtual const type_info &DefaultType() const; 
    //: Get preferred IO type.
    
    virtual IntT Priority() const { return 2; }
    //: Find the priority of the format. the higher the better.
    // This is better than the default streams IO, and also better than built-in AVI output.
    
    virtual bool IsStream() const { return true; }
    //: Test if format is a fully streamable.
    // check if you can read/write more than object object.
    
  protected:

    const static StringC m_strExtension;
    //: File extension

  };
  
  /////////////////////////////
  //! userlevel=Advanced
  //: Create an instance of a AVIFile Format.
  
  class FileFormatAVIFileC : public FileFormatC<ImageC<ByteRGBValueC> > {
  public:
    FileFormatAVIFileC()
      : FileFormatC<ImageC<ByteRGBValueC> >(*new FileFormatAVIFileBodyC)
      {}
  };
  
}
#endif
  
