// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef FILEFORMATIO_HEADER
#define FILEFORMATIO_HEADER 1
/////////////////////////////////////////
//! lib=RavlIO
//! rcsid="$Id$"
//! file="Ravl/Core/IO/FileFormatIO.hh"
//! author="Charles Galambos"
//! date="13/08/98"
//! docentry="Ravl.Core.IO" 

// These functions provide an interface to the system file format registry,
// with out having to include 100's of big nasty header files.

#include "Ravl/String.hh"
#include "Ravl/DP/Port.hh"

//! userlevel=Normal
//: Namespace for standard IO functions.

namespace RavlN {  

  class FileFormatBaseC;
  class RCWrapAbstractC;
  class IStreamC;
  class OStreamC;
  template <class DataC> class DListC;
  
  template<class DataT>
  bool Load(const StringC &filename,DataT &obj,StringC fileformat = "",bool verbose = false) {
    DPIPortC<DataT> in(BaseLoad(filename,fileformat,typeid(DataT),verbose));
    if(!in.IsValid()) {
#if RAVL_CHECK
      if(verbose) 
#endif
	cerr << "RavlN::Load(), Failed to load object from file '" << filename << "'\n";
      return false;
    }
    return in.Get(obj);
  }
  //: Load a single object.
  //!param: filename - name of file containing object
  //!param: obj - name of C++ object
  //!param: fileformat - format of object file. If fileformat string is empty, the file format is detected automatically.  To get a list of file formats, type <code>conv -lf</code>
  //!param: verbose -  if true, a message is printed to stdout describing the filename, the format used, the object type being loaded and any status information. 
  // More information <a href="../Tree/Basic_Types.IO.html#LoadSave">here</a>
  
  template<class DataT>
    bool Save(const StringC &filename,const DataT &obj,StringC fileformat = "",bool verbose = false) {
    DPOPortC<DataT> out(BaseSave(filename,fileformat,typeid(DataT),verbose));
    if(!out.IsValid()) {
#if RAVL_CHECK
      if(verbose) 
#endif
	cerr << "RavlN::Save(), Failed to save object to file '" << filename << "'\n";
      return false; // Failed to find format.
    }
    if(!out.Put(obj)) {
      cerr << "RavlN::Save(), Put failed! \n";
      assert(0);
      return false;
    }
    return true;
  }
  //: Save a single object.
  //!param: filename - name of file containing object
  //!param: obj - name of C++ object
  //!param: fileformat - format of object file. If fileformat string is empty, the file format is detected automatically.  To get a list of file formats, type <code>conv -lf</code>
  //!param: verbose -  if true, a message is printed to stdout describing the filename, the format used, the object type being loaded and any status information. 
  // More information <a href="../Tree/Basic_Types.IO.html#LoadSave">here</a>

  template<class DataT>
  bool Load(IStreamC &is,DataT &obj,StringC fileformat = "",bool verbose = false) {
    DPIPortC<DataT> in(BaseLoad(is,fileformat,typeid(DataT),verbose));
    if(!in.IsValid()) {
      if(verbose) 
	cerr << "RavlN::Load(), Failed to load object from stream.\n";
      return false;
    }
    return in.Get(obj);
  }
  //: Load a single object from a stream
  //!param: os - stream from which to load object.
  //!param: obj - name of C++ object
  //!param: fileformat - format of object file. If fileformat string is empty, the file format is detected automatically.  To get a list of file formats, type <code>conv -lf</code>
  //!param: verbose -  if true, a message is printed to stdout describing the filename, the format used, the object type being loaded and any status information. 
  // More information <a href="../Tree/Basic_Types.IO.html#LoadSave">here</a>
  
  template<class DataT>
    bool Save(OStreamC &os,const DataT &obj,StringC fileformat = "",bool verbose = false) {
    DPOPortC<DataT> out(BaseSave(os,fileformat,typeid(DataT),verbose));
    if(!out.IsValid()) {
      if(verbose) 
	cerr << "RavlN::Save(), Failed to save object to stream\n";
      return false; // Failed to find format.
    }
    if(!out.Put(obj)) {
      cerr << "RavlN::Save(), Put failed! \n";
      assert(0);
      return false;
    }
    return true;
  }
  //: Save a single object to a stream
  //!param: os - Where to save the stream to.
  //!param: obj - name of C++ object
  //!param: fileformat - format of object file. If fileformat string is empty, the file format is detected automatically.  To get a list of file formats, type <code>conv -lf</code>
  //!param: verbose -  if true, a message is printed to stdout describing the filename, the format used, the object type being loaded and any status information. 
  // More information <a href="../Tree/Basic_Types.IO.html#LoadSave">here</a>
  
  bool Load(const StringC &filename,RCWrapAbstractC &obj,StringC fileformat,bool verbose);
  //: Load to an abstract object handle.
  // NB. an instace of TypeInfoInstC must exists for the contained class if this
  // is to work.
  
  bool Save(const StringC &filename,const RCWrapAbstractC &obj,StringC fileformat,bool verbose);
  //: Save an abstract object handle.
  // NB. an instace of TypeInfoInstC must exists for the contained class if this
  // is to work.
  
  DListC<FileFormatBaseC> ListFormats(bool forLoad,const StringC &fileFormat = StringC(""),const type_info &typespec = typeid(void));
  //: List all file formats that support the given type.
  // forLoad == true, then for load. forLoad == false, then for save. <p>  
  // If fileFormat string is empty then all file formats are listed. <p>
  // If typespec is void then all types are listed.
  
  FileFormatBaseC Identify(const StringC &afile);
  //: Identify a file.
  // If file format is unrecognised the returned FileFormatBaseC will be an invalid handle.
  
  FileFormatBaseC Identify(IStreamC &is);
  //: Identify a stream.
  // If file format is unrecognised the returned FileFormatBaseC will be an invalid handle.
  
  //! userlevel=Develop
  
  DPIPortBaseC BaseLoad(const StringC &filename,StringC fformat,const type_info &obj_type,bool verbose = false);
  //: Base load function.
  // If fileformat string is empty, the file format is detected automaticly.
  // When verbose flag is true, a message is printed to stdout describing the filename, the format
  // used and the object type being loaded. 
  
  DPOPortBaseC BaseSave(const StringC &filename,StringC fformat,const type_info &obj_type,bool verbose = false);
  //: Base save function.
  // If fileformat string is empty, the default file format for the type is used.
  // When verbose flag is true, a message is printed to stdout describing the filename, the format
  // used and the object type being saved. 
  
  DPIPortBaseC BaseLoad(IStreamC &is,StringC fformat,const type_info &obj_type,bool verbose = false);
  //: Base load function for streams.
  // If fileformat string is empty, the file format is detected automaticly.
  // When verbose flag is true, a message is printed to stdout describing the filename, the format
  // used and the object type being loaded. 
  
  DPOPortBaseC BaseSave(OStreamC &os,StringC fformat,const type_info &obj_type,bool verbose = false);
  //: Base save function for streams
  // If fileformat string is empty, the default file format for the type is used.
  // When verbose flag is true, a message is printed to stdout describing the filename, the format
  // used and the object type being saved. 
  
};


#endif
