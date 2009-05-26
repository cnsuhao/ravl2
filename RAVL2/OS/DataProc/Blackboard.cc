// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlDPMT
#include "Ravl/config.h"
#include "Ravl/DP/Blackboard.hh"
#include "Ravl/DP/TypeConverter.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/BufStream.hh"
#include "Ravl/IO.hh"
#include "Ravl/VirtualConstructor.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
//! file="Ravl/OS/DataProc/Blackboard.cc"

#if RAVL_COMPILER_MIPSPRO 
#pragma instantiate RavlN::DPIPortBodyC<RavlN::RCWrapAbstractC>
#endif 

namespace RavlN {
  
  //: Default constructor.
  
  BlackboardBodyC::BlackboardBodyC()
  {}
  
  //: Stream constructor.
  
  BlackboardBodyC::BlackboardBodyC(istream &strm) 
    : RCBodyVC(strm)
  {
    int version;
    strm >> version;
    if(version > 0) {
      cerr << "BlackboardBodyC::BlackboardBodyC(), Illegal stream version = " << version << "\n";
      throw ExceptionOutOfRangeC("BlackboardBodyC::BlackboardBodyC(istream &), Unexpected version number. ");
    }
    UIntT size;
    strm >> size;
    for(;size > 0;size--) {
      StringC key;
      strm >> key;
      StringC formatClue;
      strm >> formatClue;
      SArray1dC<char> buf;
      strm >> buf;
      BufIStreamC ss(buf);
      RCWrapAbstractC obj;
      if(!RavlN::Load(ss,obj,formatClue,false)) 
	unknown[key] = Tuple2C<StringC,SArray1dC<char> >(formatClue,buf); // Failed to load object.
      else 
	entries[key] = obj;
    }
  }
  
  //: Stream constructor.
  
  BlackboardBodyC::BlackboardBodyC(BinIStreamC &strm)
    : RCBodyVC(strm)
  {
    int version;
    strm >> version;
    if(version > 0) {
      cerr << "BlackboardBodyC::BlackboardBodyC(), Illegal stream version = " << version << "\n";
      throw ExceptionOutOfRangeC("BlackboardBodyC::BlackboardBodyC(istream &), Unexpected version number. ");
    }
    UIntT size;
    strm >> size;
    for(;size > 0;size--) {
      StringC key;
      strm >> key;
      SArray1dC<char> buf;
      StringC formatClue;
      strm >> formatClue;
      strm >> buf;
      BufIStreamC ss(buf);
      RCWrapAbstractC obj;
      if(!RavlN::LoadAbstract(ss,obj,formatClue,false)) 
	unknown[key] = Tuple2C<StringC,SArray1dC<char> > (formatClue,buf); // Failed to load object.
      else 
	entries[key] = obj;
    }
  }
    
  //: Writes object to stream, can be loaded using constructor
  
  bool BlackboardBodyC::Save (ostream &strm) const {
    if(!RCBodyVC::Save(strm))
      return false;
    int version = 0;
    strm << version << ' ';
    strm << ((UIntT) entries.Size())  << ' ';
    for(HashIterC<StringC,RCWrapAbstractC> it(entries);it;it++) {
      strm << it.Key() << ' ';
      BufOStreamC ss;
      StringC formatClue = "stream";
      if(!RavlN::SaveAbstract(ss,it.Data(),formatClue,true)) {
	// Maybe try another format and then turn to ascii ?
	cerr << "Failed to save key '" << it.Key() << "'\n";
	return false;
      }
      strm << formatClue  << ' ';
      strm << ss.Data() << ' ';
    }
    for(HashIterC<StringC,Tuple2C<StringC,SArray1dC<char> > > it(unknown);it;it++) {
      if(entries.IsElm(it.Key()))
	continue;
      strm << it.Key();
      strm << it.Data().Data1();
      strm << it.Data().Data2();
    }
    return true;
  }
    
  //: Writes object to stream, can be loaded using constructor
  
  bool BlackboardBodyC::Save (BinOStreamC &strm) const {
    if(!RCBodyVC::Save(strm))
      return false;
    int version = 0;
    strm << version; 
    strm << ((UIntT) entries.Size());
    bool verbose = true;
    for(HashIterC<StringC,RCWrapAbstractC> it(entries);it;it++) {
      strm << it.Key();
      BufOStreamC ss;
      StringC formatClue = "abs";
      if(!RavlN::SaveAbstract(ss,it.Data(),formatClue,verbose)) { // abs is prefered...
	formatClue = "stream";
	if(!RavlN::SaveAbstract(ss,it.Data(),formatClue,verbose)) { // Then strm.
	  formatClue = "";
	  if(!RavlN::SaveAbstract(ss,it.Data(),formatClue,verbose)) { // Then anyhow!
	    cerr << "Failed to save key '" << it.Key() << "'\n";
	    return false;
	  }
	}
      }
      strm << formatClue;
      strm << ss.Data();
    }
    return true;    
  }

  //: Attempt conversion to requested type.
  
  RCWrapAbstractC BlackboardBodyC::Convert(RCWrapAbstractC &handle,const type_info &to) {
    const type_info &from = handle.DataType();
    if(from == to) return handle;
    return RCWrapAbstractC(SystemTypeConverter().DoConversion(handle.Abstract(),from,to));
  }
  
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(BlackboardBodyC,BlackboardC,RCHandleVC<BlackboardBodyC>);
  
  //--------------------------------------------------------------------------------------------
  
  FileFormatStreamC<BlackboardC> FileFormatStream_Blackboard;
  FileFormatBinStreamC<BlackboardC> FileFormatBinStream_Blackboard;

  static TypeNameC type0(typeid(BlackboardC),"BlackboardC");
}
