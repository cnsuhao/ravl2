// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FILEFORMATBINSTREAM_HEADER
#define RAVL_FILEFORMATBINSTREAM_HEADER 1
////////////////////////////////////////////////////////
//! docentry="Ravl.API.Core.IO.Formats" 
//! lib=RavlIO
//! file="Ravl/Core/IO/FileFormatBinStream.hh"
//! author="Charles Galambos"
//! date="12/08/1998"
//! rcsid="$Id$"
//! userlevel=Default

#include "Ravl/DP/FileFormat.hh"
#include "Ravl/DP/BinFileIO.hh"
#include "Ravl/TypeName.hh"

namespace RavlN {
  /////////////////////////////
  //: Binary stream file format.
  //! userlevel=Develop
  
  template<class DataT>
  class FileFormatBinStreamBodyC : public FileFormatBodyC {
  public:
    FileFormatBinStreamBodyC(bool deletable)
      : FileFormatBodyC("abs","RAVL binary stream. ",deletable)
    {}
    //: Constructor.
    
    FileFormatBinStreamBodyC(const StringC &formatId,const StringC &formatDescriptor,bool deletable = true)
      : FileFormatBodyC(formatId,formatDescriptor,deletable)
    {}
    //: Constructor with full format info.
    
    virtual const type_info &ProbeLoad(IStreamC &in,const type_info &/*obj_type*/) const  {
      if(!in.good())
	return typeid(void);
      BinIStreamC bin(in);
      streampos mark = bin.Tell();
      UInt16T id;
      // Check magic number.
      bin >> id;
      if(id != RavlN::RAVLBinaryID && id != RavlN::RAVLInvBinaryID) {
	//cerr << "ID Mis-match. " << id << " " << RAVLBinaryID <<" \n";
	bin.Seek(mark);
	return typeid(void);
      }
      // Check class name.
      StringC classname;
      if(id == RavlN::RAVLInvBinaryID)
	bin.UseNativeEndian(!bin.NativeEndian());
      bin >> classname;
      //cout << "Stream Probe: '" << classname << "' Looking for: '" << TypeName(typeid(DataT)) << "'\n";
      bin.Seek(mark);
      if(classname != StringC(TypeName(typeid(DataT)))) 
	return typeid(void); // Don't know how to load this.
      return typeid(DataT);
    }
    //: Is stream in std stream format ?
    
    virtual const type_info &ProbeLoad(const StringC &filename,IStreamC &in,const type_info &obj_type) const {
      //cout << "File Probe '" << filename << "' Looking for:" << TypeName(obj_type) << endl;
      if(filename == "") 
	return typeid(DataT); // Yep, can handle load to DataT.
      return ProbeLoad(in,obj_type); // Check load from stream.
    }
    
    virtual const type_info &ProbeSave(const StringC &filename,const type_info &/*obj_type*/,bool forceFormat) const {
      if(forceFormat)
	return typeid(DataT); // If we're forced just accept it.
      StringC ext = Extension(filename);
      // If there's no extention or the extention is 'abs' we can handle it.
      // abs = RAVL Binary Stream.
      if(filename.IsEmpty())
	return typeid(void); // Nope.
      if(filename[0] == '@')
	return typeid(void); // Nope.
      if(ext == ""  || ext == "abs" || ext == "bin" || ext == formatName) 
	return typeid(DataT); // Yep, can save in format.
      return typeid(void); // Nope.
    }
    
    virtual DPIPortBaseC CreateInput(IStreamC &in,const type_info &obj_type) const {
      if(obj_type != typeid(DataT))
	return DPIPortBaseC();
      BinIStreamC bs(in);
      return DPIBinFileC<DataT>(bs,true);
    }
    //: Create a input port for loading.
    // Will create an Invalid port if not supported.
    
    virtual DPOPortBaseC CreateOutput(OStreamC &out,const type_info &obj_type) const {
      if(obj_type != typeid(DataT))
	return DPOPortBaseC();
      BinOStreamC bs(out);
      return DPOBinFileC<DataT>(bs,true);
    }
    //: Create a output port for saving.
    // Will create an Invalid port if not supported.
    
    
    DPIPortBaseC CreateInput(const StringC &filename,const type_info &obj_type) const  {
      if(obj_type != typeid(DataT))
	return DPIPortBaseC();
      BinIStreamC bs(filename);
      return DPIBinFileC<DataT>(bs,true);
    }
    
    //: Create a input port for loading.
    // Will create an Invalid port if not supported.
    
    DPOPortBaseC CreateOutput(const StringC &filename,const type_info &obj_type) const { 
      if(obj_type != typeid(DataT))
	return DPOPortBaseC();
      BinOStreamC bs(filename);
      return DPOBinFileC<DataT>(bs,true);
    }
    //: Create a output port for saving.
    // Will create an Invalid port if not supported.
    
    virtual const type_info &DefaultType() const 
    { return typeid(DataT); }
    //: Get prefered IO type.

    virtual bool IsStream() const
    { return true; }
    //: Just to make it clear its a streamable format.
  
  };

  
  /////////////////////////////
  //! userlevel=Normal
  //: Binary stream file format.
  
  template<class DataT>
  class FileFormatBinStreamC : public FileFormatC<DataT> {
  public:
    FileFormatBinStreamC()
      : FileFormatC<DataT>(*new FileFormatBinStreamBodyC<DataT>(true))
    {}
    
    FileFormatBinStreamC(const StringC &formatId,const StringC &formatDescriptor)
      : FileFormatC<DataT>(*new FileFormatBinStreamBodyC<DataT>(formatId,formatDescriptor))
    {}
    //: Construct will format id and descriptor
    
  };

}

#endif
