// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/FileFormatRegistry.cc"

#include "Ravl/DP/FileFormatRegistry.hh"

#include "Ravl/TypeName.hh"
#include "Ravl/StringList.hh"
#include "Ravl/HSet.hh"
#include "Ravl/DP/FileFormDesc.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
 
  //: Default constructor.
  
  FileFormatRegistryBodyC::FileFormatRegistryBodyC() 
#if RAVL_USE_IO_AUTO_TYPECONVERTER
    : typeConverter(SystemTypeConverter())
#endif
  {}
  
#if RAVL_USE_IO_AUTO_TYPECONVERTER
  //: Constructor.
  
  FileFormatRegistryBodyC::FileFormatRegistryBodyC(const TypeConverterC &aTypeConveter)
    : typeConverter(aTypeConveter)
  {}
#endif
  
  //: Add a new format to the registry.
  
  bool FileFormatRegistryBodyC::Insert(FileFormatBaseC &ff) {
    if(ff.Name() != "") {
      FormatByName()[ff.Name()].InsLast(ff);
      ONDEBUG(cout << "Registering file format :" << ff.Name() << endl);
    }
    Formats().InsLast(ff);
    return true;
  }
  
  //: Remove an old format from the registry.
  
  bool FileFormatRegistryBodyC::Remove(FileFormatBaseC &ff) {
    RavlAlwaysAssert(0); // Not implemented.
    return false;
  }
  
  /////////////////////////////////////
  //: Find a format.
  
  FileFormatBaseC FileFormatRegistryBodyC::FindFormat(bool forLoad,
						      const StringC &name,
						      const type_info &objtype,
						      bool useIndirect
						      ) {
    if(name == "") { // Request for default format ?
      for(DLIterC<FileFormatBaseC> it(Formats());
	  it.IsElm();
	  it.Next()) {
	if(it.Data().DefaultType() == objtype)
	  return it.Data();
      }
      cerr << "No default file format for: '" << TypeName(objtype) << "'" << endl;
      return FileFormatBaseC(); // No default type found.
    }
    if(!FormatByName().IsElm(name)) {
      cerr << "Unrecognised file format: '" << name << "' "<< endl;
      return FileFormatBaseC(); // Unknown format.
    }
    for(DLIterC<FileFormatBaseC> it(FormatByName()[name]);
	it.IsElm();
	it.Next()) {
      if(forLoad) {
	if(it.Data().ProbeLoad(objtype) != typeid(void))
	  return it.Data();
      } else {
	if(it.Data().ProbeSave(objtype) != typeid(void))
	  return it.Data();
      }
    }
    StringC ls;
    if(forLoad)
      ls = "load";
    else ls = "save";
    cerr << "Don't know how to " << ls << " '" << TypeName(objtype) << "' in format '" << name << "'" << endl;
    return FileFormatBaseC();
  }
  
  /////////////////////////////////////
  //: Find the format of the file.
  
  FileFormatBaseC FileFormatRegistryBodyC::FindFormatFile(bool forLoad,
							  const StringC &filename,
							  const type_info &objtype,
							  StringC formName,
							  bool useIndirect
							  ) {
    if(formName == "") {
      for(DLIterC<FileFormatBaseC> it(Formats());
	  it.IsElm();
	  it.Next()) {
	if(objtype == typeid(void)) {
	  if(forLoad) {
	    if(it.Data().ProbeLoad(filename,it.Data().DefaultType()) == typeid(void))
	      continue;
	  } else {
	    if(it.Data().ProbeSave(filename,it.Data().DefaultType(),false) == typeid(void))
	      continue;
	  }
	} else {
	  if(forLoad) {
	    if(it.Data().ProbeLoad(filename,objtype) == typeid(void))
	      continue;
	  } else {
	    if(it.Data().ProbeSave(filename,objtype,false) == typeid(void))
	      continue;
	  }
	}
	return it.Data();
      }
      if(objtype != typeid(void)) // If a type is specified and we couldn't convert to it.
	cerr << "Unknown file format: '" << filename << "' (Requested type: '" << TypeName(objtype.name()) << ")" << endl;
      return FileFormatBaseC(); // No default type found.
    }
    if(!FormatByName().IsElm(formName)) {
      cerr << "Unrecognised file format: '" << formName << "'" << endl;
      return FileFormatBaseC(); // Unknown format.
    }
    for(DLIterC<FileFormatBaseC> it(FormatByName()[formName]);
	it.IsElm();
	it.Next()) {
      if(objtype == typeid(void)) {
	if(forLoad) {
	  if(it.Data().ProbeLoad(filename,it.Data().DefaultType()) == typeid(void))
	    continue;
	} else {
	  if(it.Data().ProbeSave(filename,it.Data().DefaultType(),true) == typeid(void))
	    continue;
	}
      } else {
	if(forLoad) {
	  if(it.Data().ProbeLoad(filename,objtype) == typeid(void))
	    continue;
	} else {
	  if(it.Data().ProbeSave(filename,objtype,true) == typeid(void))
	    continue;
	}
      }
    return it.Data();
    }
    cerr << "Can't read '" << filename << "' from '" << formName << "' into '" << TypeName(objtype) << "'" << endl;  
    return FileFormatBaseC();
  }
  
  ///////////////////////////////////
  //: Find the format of the file.
  
  FileFormatBaseC FileFormatRegistryBodyC::FindFormat(IStreamC &in,
						      const type_info &objtype,
						      StringC formName,
						      bool useIndirect
						      ) {
    if(formName == "") {
      for(DLIterC<FileFormatBaseC> it(Formats());
	  it.IsElm();
	  it.Next()) {
	ONDEBUG(cout << "FindFormat() " << it.Data().Name() << " : " << TypeName(it.Data().DefaultType()) << endl);
	if(objtype == typeid(void)) {
	  if(it.Data().ProbeLoad(in,it.Data().DefaultType()) == typeid(void))
	    continue;
	} else {
	  if(it.Data().ProbeLoad(in,objtype) == typeid(void))
	    continue;
	}
	return it.Data();
      }
      cerr << "No file format for: 'IStreamC' to " << TypeName(objtype) << endl;
      return FileFormatBaseC(); // No default type found.
    }
    if(!FormatByName().IsElm(formName)) {
      cerr << "Unrecognised file format: " << formName << endl;
      return FileFormatBaseC(); // Unknown format.
    }
    for(DLIterC<FileFormatBaseC> it(FormatByName()[formName]);
	it.IsElm();
	it.Next()) {
      if(objtype == typeid(void)) {
	if(it.Data().ProbeLoad(in,it.Data().DefaultType()) == typeid(void))
	continue;
      } else {
	if(it.Data().ProbeLoad(in,objtype) == typeid(void))
	  continue;
      }
      return it.Data();
    }
    cerr << "Can't read stream in format " << formName << " into " << TypeName(objtype) <<endl;  
    return FileFormatBaseC();
  }
  
  static bool ParseFmts(StringC &fmts,
			HSetC<StringC> &ignoreFmts,
			HSetC<StringC> &acceptFmts) {
    StringListC aLst(fmts,", \n\t\0");
    for(DLIterC<StringC> it(aLst);it.IsElm();it.Next()) {
      if(it.Data()[0] == '!') {
	ignoreFmts += it.Data().after(0);
	ONDEBUG(cerr << "Ignoreing: " << it.Data().after(0) << "\n");
      } else 
	acceptFmts += it.Data();
    } 
    return acceptFmts.IsEmpty();
  }
  
  //: Search for input format.
  
  bool FileFormatRegistryBodyC::FindInputFormat(FileFormatDescC &fmtInfo,
						StringC filename,
						StringC format,
						const type_info &obj_type,
						bool verbose
						) {
    ONDEBUG(cerr << "FindInputFormat(), Fn:'" << filename << "' Format:'" << format << "'  Type : " << TypeName(obj_type) << "  Verb:" << verbose << "\n");

    if(filename.length() == 0) {
      cerr<< "FileFormatRegistryBodyC::FindInputFormat(), Filename too short. \n";
      return false; 
    }
    
    // Open file to start probe..
    IStreamC in(filename,true); // Open in binary mode, particularly for windows.
    if(!in.good() && filename[0] != '@') {
      cerr << "Can't open file '" << filename << "'\n";
      return false;
    }
    FileFormatBaseC form;
    DListC<DPConverterBaseC> conv,new_conv;
    const type_info *intype = 0;
    HSetC<StringC> ignoreFmts,acceptFmts;
    bool acceptAll = ParseFmts(format,ignoreFmts,acceptFmts);
    
    RavlAssert(in.good() || filename[0] == '@');
    
    // Should look for best ??
    for(DLIterC<FileFormatBaseC> it(Formats());
	it.IsElm();
	it.Next()) {
      // Format specified ?
      if(ignoreFmts.IsMember(it.Data().Name()))
	continue;
      if(!acceptAll) {
	if(!acceptFmts.IsMember(it.Data().Name()))
	  continue;
      }
      // Look for all loaders that can load from stream.
      const type_info *ti;
      if(filename != "-")
	ti = &it.Data().ProbeLoad(filename,in,obj_type); // Use file probe.
      else ti = &it.Data().ProbeLoad(in,obj_type); // Use stream probe...
      ONDEBUG(cerr << "IProbe '" << it.Data().Name() << "' '" << TypeName(it.Data().DefaultType()) << "'  = " << TypeName(*ti) << "\n");
#if RAVL_CHECK
      if(!in.good() && filename[0] != '@') {
	cerr << "FindInputFormat(), IProbe left bad stream '" << it.Data().Name() << "' '" << TypeName(it.Data().DefaultType()) << "'  = " << TypeName(*ti) << "\n";
      }
#endif
      RavlAssert(in.good() || filename[0] == '@');
      //ONDEBUG(cerr << "Tell:" << in.Tell() << ") \n");
      if(*ti == typeid(void))
	continue; // Nope.
      if(*ti == obj_type || obj_type == typeid(void)) {
	// Found direct load, use it !
	conv = DListC<DPConverterBaseC>();
	form = it.Data();
	intype = ti;
	break;
      }
      // Can we convert to requested type ?
      if(!conv.IsEmpty())
	continue; // Don't bother if we've found a way already.    
#if RAVL_USE_IO_AUTO_TYPECONVERTER
      new_conv = typeConverter.FindConversion(*ti,obj_type);
      if(!new_conv.IsEmpty()) {
	form = it.Data();
	conv = new_conv;
	intype = ti;
      }
#endif
    }
    if(!form.IsValid()) {
      ONDEBUG(cerr << "FindInputFormat(StringC), Can't identify stream. \n");
      if(verbose)
	cerr << "Can't find format for '" << filename <<"'\n";
      return false;
    }
    if(verbose ONDEBUG(|| 1))
      cerr << "Loading object '" << TypeName(obj_type) << "' in format '" << form.Name() << "' from file '" << filename << "' Steps:" << conv.Size()<< "\n";
    
#if DPDEBUG
    for(DLIterC<DPConverterBaseC> it(conv);it.IsElm();it.Next()) 
      cerr << "Conv:" <<TypeName(it.Data().ArgType(0)) << " -> " << TypeName(it.Data().Output()) << endl;
#endif
    fmtInfo = FileFormatDescC(form,conv,*intype,true);
    return true;
  }
  
  ///////////////////////////////
  //: Create an input pipe.
  
  DPIPortBaseC FileFormatRegistryBodyC::CreateInput(StringC filename,
						StringC format,
						const type_info &obj_type,
						bool verbose
						) {
    FileFormatDescC fmtInfo;
    if(!FindInputFormat(fmtInfo,filename,format,obj_type,verbose)) {
      if(verbose) 
	cerr << "CreateInput(), Can't find format for file '" << filename << "'. \n"; 
      return DPIPortBaseC();
    }
    DPIPortBaseC ret = fmtInfo.CreateInput(filename);
    if(!ret.IsValid())
      cerr << "CreateInput(), Failed to create input stream for '" << filename << "'\n";
    return ret;
  }
  
  //: Search for output format.
  
  bool FileFormatRegistryBodyC::FindOutputFormat(FileFormatDescC &fmtInfo,
						 StringC filename,
						 StringC format,
						 const type_info &obj_type,
						 bool verbose
						 ) {
    ONDEBUG(cerr << "FindOutputFormat(), Fn:'" << filename << "' Format:'" << format << "'  Type : " << TypeName(obj_type) << "  Verb:" << verbose << "\n");
    // Find format thats least effort to convert to.
    RealT minCost = 100000;
    FileFormatBaseC minForm;
    DListC<DPConverterBaseC> bestConv;
    const type_info *bestout = 0;
    IntT bestPri = 0;
    
    HSetC<StringC> ignoreFmts,acceptFmts;
    bool acceptAll = ParseFmts(format,ignoreFmts,acceptFmts);
    const type_info *testType = &obj_type;
      
    for(DLIterC<FileFormatBaseC> it(Formats());
	it.IsElm();
	it.Next()) {
      if(ignoreFmts.IsMember(it.Data().Name()))
	continue;
      if(!acceptAll) {
	if(!acceptFmts.IsMember(it.Data().Name()))
	continue;
      }
      if(obj_type == typeid(void))
	testType = &(it.Data().DefaultType());
      const type_info &ti = it.Data().ProbeSave(filename,*testType,!acceptAll); // it.Data().DefaultType()
      ONDEBUG(cerr << "OProbe '" << it.Data().Name() << "' '" << TypeName(it.Data().DefaultType()) << "'  = " << TypeName(ti) << "\n");
      if(ti == typeid(void))
	continue;
      if(ti == obj_type || obj_type == typeid(void)) {
	if(minCost > 0 || it.Data().Priority() > bestPri) {
	  minForm = it.Data();
	  bestConv = DListC<DPConverterBaseC>();
	  minCost = 0;
	  bestPri = it.Data().Priority();
	  bestout = &ti;
	}
	continue;
      }
#if RAVL_USE_IO_AUTO_TYPECONVERTER
      if(minCost == 0)
	continue; // Found a format needing no conversion !
      RealT acost = -1;
      DListC<DPConverterBaseC> aConv(typeConverter.FindConversion(obj_type,ti,acost));
      if(aConv.Size() == 0)
	continue; // Can't convert !
      if(acost < minCost || (acost == minCost && it.Data().Priority() > bestPri)) {
	bestConv = aConv;
	minForm = it.Data();
	minCost = acost;
	bestout = &ti;
	bestPri = it.Data().Priority();
      }
#endif
    }
    
    if(!minForm.IsValid()) {
      if(verbose)
	cerr << "WARNING: Don't know how to save to file '" << filename << "' in format '" << format << "' from type '" << TypeName(obj_type) << "' \n"; 
      return false;
    }  
    if(verbose ONDEBUG(|| 1))
      cerr << "Saving object '" << TypeName(obj_type) << "' in format '" << minForm.Name() << "' with type '" << TypeName(*bestout) << "' to file '" << filename << "' Steps:" << bestConv.Size() << " Priority:" << bestPri <<  " \n";
    
    fmtInfo = FileFormatDescC(minForm,bestConv,*bestout,false);
    return true;
  }
  
  ///////////////////////////////
  //: Create an output pipe.

  DPOPortBaseC FileFormatRegistryBodyC::CreateOutput(StringC filename,
						 StringC format,
						 const type_info &obj_type,
						 bool verbose
						 ) {
    FileFormatDescC fmtInfo;
    if(!FindOutputFormat(fmtInfo,filename,format,obj_type,verbose))
      return DPOPortBaseC();
    DPOPortBaseC ret = fmtInfo.CreateOutput(filename); 
    if(!ret.IsValid())
      cerr << "CreateInput(), Failed to create output stream for '" << filename << "'\n";
    return ret;
  }
  
  ///////////////////////////////
  //: Create an input pipe.
  
  DPIPortBaseC FileFormatRegistryBodyC::CreateInput(IStreamC &in,
						StringC format,
						const type_info &obj_type,
						bool verbose
						) {
    if(obj_type == typeid(void)) {
      ONDEBUG(cerr << "CreateInput(StreamC), Asked to load void \n");
      return DPIPortBaseC();
    }
    FileFormatBaseC form;
    // Should look for best ??
    DListC<DPConverterBaseC> conv;
    const type_info *bestin = 0;
    
    for(DLIterC<FileFormatBaseC> it(Formats());
	it.IsElm();
	it.Next()) {
      if(!format.IsEmpty()) {
	if(format != it.Data().Name())
	  continue;
      }
      // Look for all loaders that can load from stream.
      const type_info &ti = it.Data().ProbeLoad(in,obj_type);
      if(ti == typeid(void))
	continue; // Can't load give input.
      if(ti == obj_type) {
	conv = DListC<DPConverterBaseC>();
	form = it.Data();
	bestin = &ti;
	break;
      }
      // Can we convert to requested type ?
#if RAVL_USE_IO_AUTO_TYPECONVERTER
      conv = typeConverter.FindConversion(ti,obj_type);
      if(conv.Size() > 0) {
	form = it.Data();
	bestin = &ti;
	break;
      }
#endif
    }
    if(!form.IsValid()) {
      ONDEBUG(cerr << "CreateInput(StreamC), Can't load stream. \n");
      if(verbose) 
	cerr << "CreateInput(StreamC), Can't identify format. \n";
      return DPIPortBaseC();
    }
    if(verbose ONDEBUG(|| 1))
      cerr << "Loading object '" << TypeName(obj_type) << "' in format '" << form.Name() << "' from stream \n";
    
    //: Build conversion stream.
    DPIPortBaseC inp = form.CreateInput(in,*bestin);
    if(!inp.IsValid()) {
      cerr << "Internal error: Failed to open input stream in format '" << form.Name() << "' \n" ;
      RavlAssert(0);
      return DPIPortBaseC();
    }
    for(DLIterC<DPConverterBaseC> it2(conv);it2.IsElm();it2.Next()) {
      inp = it2.Data().CreateIStream(inp);
      RavlAssert(inp.IsValid());
    }
    return inp;  
  }
  
  DPOPortBaseC FileFormatRegistryBodyC::CreateOutput(OStreamC &to,
						 StringC format,
						 const type_info &obj_type,
						 bool verbose
						 ) {
    if(obj_type == typeid(void)) {
      ONDEBUG(cerr << "CreateOutput(OStreamC), Asked to output void. \n");
      return DPOPortBaseC();
    }
  // Find format thats least effort to convert to.
    RealT minCost = 100000;
    FileFormatBaseC minForm;
    DListC<DPConverterBaseC> bestConv;
    IntT bestPri = 0;
    const type_info *bestout = 0;
    bool forceFormat = (format != "");
    for(DLIterC<FileFormatBaseC> it(Formats());
	it.IsElm();
	it.Next()) {
      if(forceFormat) {
	if(format != it.Data().Name())
	  continue;
      }
      const type_info &ti = it.Data().ProbeSave(obj_type);//it.Data().DefaultType());
      if(ti == typeid(void))
	continue;
      if(ti == obj_type) {
	if(minCost > 0 || it.Data().Priority() > bestPri) {
	  minForm = it.Data();
	  bestConv = DListC<DPConverterBaseC>();
	  minCost = 0;
	  bestPri = it.Data().Priority();
	  bestout = &ti;
	}
      }
#if RAVL_USE_IO_AUTO_TYPECONVERTER
      if(minCost == 0)
	continue; // Conversion less format already found.
      RealT acost = -1;
      DListC<DPConverterBaseC> aConv(typeConverter.FindConversion(obj_type,ti,acost));
      if(aConv.Size() == 0)
	continue; // Can't convert !
      if(acost < minCost || (acost == minCost && it.Data().Priority() > bestPri)) {
	bestConv = aConv;
	minForm = it.Data();
	minCost = acost;
	bestPri = it.Data().Priority();
	bestout = &ti;
      }
#endif
    }
    
    if(!minForm.IsValid()) {
      if(verbose)
	cerr << "WARNING: Don't know how to save to stream in format '" << format << "' from type '" << TypeName(obj_type) << "' \n";
      return DPOPortBaseC();
    }  
    if(verbose ONDEBUG(|| 1))
      cerr << "Saving object '" << TypeName(obj_type) << "' in format '" << minForm.Name() << "' to stream \n";
    
    //: Build conversion stream.
    
    DPOPortBaseC outp = minForm.CreateOutput(to,*bestout);
    if(!outp.IsValid()) {
      cerr << "Internal error: Failed to open output stream in format '" << minForm.Name() << "' \n" ;
      RavlAssert(0);
      return DPOPortBaseC();
    }
    for(DLIterC<DPConverterBaseC> it2(bestConv);it2.IsElm();it2.Next()) {
      outp = it2.Data().CreateOStream(outp);
      RavlAssert(outp.IsValid());
    }
    return outp;  
  }


  //: Access the system's format registry.
  
  FileFormatRegistryC &SystemFileFormatRegistry() {
    static FileFormatRegistryC fr(true);
    return fr;
  }



  /////////////////////////////////
  //! userlevel=Advanced
  //: Load to an abstract object handle.
  // NB. an instace of TypeInfoInstC must exists for the contained class if this
  // is to work.
  
  bool FileFormatRegistryBodyC::Load(const StringC &filename,RCWrapAbstractC &obj,StringC fileformat,bool verbose) {
    DPIPortBaseC port = CreateInput(filename,fileformat,typeid(void),verbose);
    if(!port.IsValid()) 
      return false;
    DPTypeInfoC lt = DPTypeInfoBodyC::Types()[port.InputType().name()];
    if(!lt.IsValid()) {
      cerr << "Load(RCWrapAbstractC), No TypeInfoC class for type '" << TypeName(port.InputType()) << "', load failed. \n";
      return false;
    }
    obj = lt.Get(port);
    return true;
  }
  
  /////////////////////////////////
  //! userlevel=Advanced
  //: Save an abstract object handle.
  // NB. an instace of TypeInfoInstC must exists for the contained class if this
  // is to work.
  
  bool FileFormatRegistryBodyC::Save(const StringC &filename,const RCWrapAbstractC &obj,StringC fileformat,bool verbose) {
    if(!obj.IsValid()) {
      if(verbose)
	cerr << "Save(RCWrapAbstractC), Asked to save invalid handle to file '" + filename + "'\n";
      return false;
    }
    DPOPortBaseC port = CreateOutput(filename,fileformat,obj.DataType(),verbose);
    if(!port.IsValid()) 
      return false; // Just plain don't know now to save.
    DPTypeInfoC lt = DPTypeInfoBodyC::Types()[obj.DataType().name()];
    if(!lt.IsValid()) {
      cerr << "Save(RCWrapAbstractC), No TypeInfoC class for type '" << TypeName(obj.DataType()) << "', save failed. \n";
      return false;
    }
    return lt.Put(port,obj);
  }
  
  /////////////////////////////////
  //! userlevel=Advanced
  //: List all file formats that support the given type.
  // If typespec is void then all types are listed.
  
  DListC<FileFormatBaseC> FileFormatRegistryBodyC::ListFormats(bool forLoad,const StringC &fileFormat,const type_info &typespec) {
    DListC<FileFormatBaseC> ret;
    bool forceFormat = (fileFormat != "");
    for(DLIterC<FileFormatBaseC> it(SystemFileFormatRegistry().Formats());
	it.IsElm();
	it.Next()) {
      if(forceFormat) {
	if(it.Data().Name() != fileFormat)
	  continue;
      }
      if(forLoad) {
	IStreamC tmp;
      if(it.Data().ProbeLoad("",tmp,typespec) != typeid(void))
	ret.InsLast(it.Data());
      } else {
	if(it.Data().ProbeSave("",typespec,forceFormat)  != typeid(void))
	  ret.InsLast(it.Data());
      }
    }
    return ret;
  }

  //////////////////////////////////
  //: Identify a file.
  // If file format is unrecognised FileFormatBaseC will be an invalid handle.
  
  FileFormatBaseC FileFormatRegistryBodyC::Identify(const StringC &afile)  {
    FileFormatBaseC ret;
    ret = FindFormatFile(true,afile); // Find a load format.
    if(!ret.IsValid()) // No, then try save.
      ret = FindFormatFile(false,afile);
    return ret;
  }
  
  
  //: Identify a stream.
  // If file format is unrecognised the returned FileFormatBaseC will be an invalid handle.
  
  FileFormatBaseC FileFormatRegistryBodyC::Identify(IStreamC &istrm) 
  { return FindFormat(istrm); }
  
}
