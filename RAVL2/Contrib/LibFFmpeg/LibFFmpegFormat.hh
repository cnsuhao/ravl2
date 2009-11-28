// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, Omniperception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_LIBFFMPEGFORMAT_HEADER
#define RAVL_LIBFFMPEGFORMAT_HEADER 1
//////////////////////////////////////////////////////////////////
//! author = "Warren Moore"
//! docentry = "Ravl.API.Images.Video.Video IO.LibFFmpeg"
//! date = "31/03/2005"
//! rcsid = "$Id: LibFFmpegFormat.hh 7393 2009-11-26 11:38:25Z simondennis $"
//! lib=RavlLibFFmpeg
//! file = "Ravl/Contrib/LibFFmpeg/LibFFmpegFormat.hh"

#include "Ravl/DP/FileFormat.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"

namespace RavlImageN
{

  
  
  /////////////////////////////
  //! userlevel = Develop
  //: File format information.
  
  class FileFormatLibFFmpegBodyC :
    public FileFormatBodyC 
  {
  public:
    FileFormatLibFFmpegBodyC();
    //: Constructor

    FileFormatLibFFmpegBodyC(const StringC &vName,const StringC &vDesc);
    //: Constructor
    
    virtual const type_info &ProbeLoad(IStreamC &in, const type_info &obj_type) const;
    //: Probe for load
    
    virtual const type_info &ProbeLoad(const StringC &filename, IStreamC &in, const type_info &obj_type) const;
    //: Probe for load
    
    virtual const type_info &ProbeSave(const StringC &filename, const type_info &obj_type, bool forceFormat) const;
    //: Probe for Save
    
    virtual DPIPortBaseC CreateInput(IStreamC &in, const type_info &obj_type) const;
    //: Create a input port for loading
    // Will create an Invalid port if not supported
    
    virtual DPOPortBaseC CreateOutput(OStreamC &out, const type_info &obj_type) const;
    //: Create a output port for saving
    // Will create an Invalid port if not supported
    
    virtual DPIPortBaseC CreateInput(const StringC &filename, const type_info &obj_type) const;
    //: Create a input port for loading from file 'filename'
    // Will create an Invalid port if not supported
   
    virtual DPOPortBaseC CreateOutput(const StringC &filename, const type_info &obj_type) const;
    //: Create a output port for saving to file 'filename'
    // Will create an Invalid port if not supported
    
    virtual const type_info &DefaultType() const; 
    //: Get prefered IO type
    
    virtual IntT Priority() const { return 1; }
    //: Find the priority of the format: the higher the better (default = 0).
    
    virtual bool IsStream() const { return true; }
    //: Test if format is a fully streamable
    
  private:
    bool IsSupported(const char *filename) const;
    //: Is this file supported by FFmpeg?

    bool IsOutPutSupported(const char *filename) const;
    //: Is this output format supported by FFmpeg?
  };
  
  
  
  /////////////////////////////
  //! userlevel = Advanced
  //: Create an instance of the file format
  // BIG OBJECT
  
  class FileFormatLibFFmpegC :
    public FileFormatC< ImageC<ByteRGBValueC> > 
  {
  public:
    FileFormatLibFFmpegC() :
      FileFormatC< ImageC<ByteRGBValueC> >(*new FileFormatLibFFmpegBodyC())
    {}
    
    FileFormatLibFFmpegC(const StringC &vName,const StringC &vDesc)
      : FileFormatC<ImageC<ByteRGBValueC> >(*new FileFormatLibFFmpegBodyC(vName,vDesc))
      {}

    const type_info & ProbeLoad(IStreamC & in,const type_info & obj_type) const
    { return Body().ProbeLoad(in,obj_type); }
    //: Probe for load 
    //!cwiz:author
    
    const type_info & ProbeLoad(const StringC & filename,IStreamC & in,const type_info & obj_type) const
    { return Body().ProbeLoad(filename,in,obj_type); }
    //: Probe for load 
    //!cwiz:author
    
    const type_info & ProbeSave(const StringC & filename,const type_info & obj_type,bool forceFormat) const
    { return Body().ProbeSave(filename,obj_type,forceFormat); }
    //: Probe for Save 
    //!cwiz:author
    
    DPIPortBaseC CreateInput(IStreamC & in,const type_info & obj_type) const
    { return Body().CreateInput(in,obj_type); }
    //: Create a input port for loading 
    // Will create an Invalid port if not supported
    //!cwiz:author
    
    DPOPortBaseC CreateOutput(OStreamC & out,const type_info & obj_type) const
    { return Body().CreateOutput(out,obj_type); }
    //: Create a output port for saving 
    // Will create an Invalid port if not supported
    //!cwiz:author
    
    DPIPortBaseC CreateInput(const StringC & filename,const type_info & obj_type) const
    { return Body().CreateInput(filename,obj_type); }
    //: Create a input port for loading from file 'filename' 
    // Will create an Invalid port if not supported
    //!cwiz:author
    
    DPOPortBaseC CreateOutput(const StringC & filename,const type_info & obj_type) const
    { return Body().CreateOutput(filename,obj_type); }
    //: Create a output port for saving to file 'filename' 
    // Will create an Invalid port if not supported
    //!cwiz:author
    
    const type_info & DefaultType() const
    { return Body().DefaultType(); }
    //: Get prefered IO type 
    //!cwiz:author
    
    IntT Priority() const
    { return Body().Priority(); }
    //: Find the priority of the format: the higher the better (default = 0). 
    //!cwiz:author
    
    bool IsStream() const
    { return Body().IsStream(); }
    //: Test if format is a fully streamable 
    //!cwiz:author
  };
  
  
  
}

#endif
