// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_MPEGFORMAT_HEADER
#define RAVLIMAGE_MPEGFORMAT_HEADER 1
////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/ExternalImageIO/TiffFormat.hh"
//! lib=RavlMPEG
//! author="Charles Galambos"
//! docentry="Ravl.Images.Video.Video IO.MPEG2"
//! date="29/10/2001"

#include "Ravl/DP/FileFormat.hh"
#include "Ravl/Image/Image.hh"

namespace RavlImageN {

  //! userlevel=Develop
  //: MPEG File format information.
  
  class FileFormatMPEGBodyC 
    : public FileFormatBodyC
  {
  public:
    
    FileFormatMPEGBodyC(const StringC &id,const StringC &desc);
    //: Constructor.
    
    const type_info &ChooseFormat(const type_info &obj_type) const;
    //: Try and choose best format for IO.
    
    virtual const type_info &ProbeLoad(IStreamC &in,const type_info &obj_type) const;
    //: Is stream in std stream format ?
    
    virtual const type_info &ProbeLoad(const StringC &filename,IStreamC &in,const type_info &obj_type) const;
    //: Probe for load.
    
    virtual const type_info &ProbeSave(const StringC &filename,const type_info &obj_type,bool forceFormat) const;
    //: Probe for Save.
    
    virtual DPIPortBaseC CreateInput(const StringC &filename,const type_info &obj_type) const;
    //: Create a input port for loading from file 'filename'.
    // Will create an Invalid port if not supported. <p>
    
    virtual DPOPortBaseC CreateOutput(const StringC &filename,const type_info &obj_type) const;
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
    
    virtual IntT Priority() const { return 0; }
    //: Find the priority of the format. the higher the better.
    // Default is zero, this is better than the default (streams.)
    
    virtual bool IsStream() const { return true ; }
    //: Test if format is a fully streamable.
    // i.e. check if you can read/write more than object object.
    // png supports sequences.. but not with this software for now...
    
  protected:
  };
  
  /////////////////////////////
  //! userlevel=Advanced
  //: Create an instance of a MPEG File Format.
  
  class FileFormatMPEGC : public FileFormatC<ImageC<ByteT> > {
  public:
    FileFormatMPEGC(const StringC &id,const StringC &desc)
      : FileFormatC<ImageC<ByteT> >(*new FileFormatMPEGBodyC(id,desc))
      {}
  };
}

#endif
