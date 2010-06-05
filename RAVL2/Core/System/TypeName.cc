// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! lib=RavlCore
//! file="Ravl/Core/System/TypeName.cc"

//! rcsid="$Id: TypeName.cc 6532 2008-02-01 10:31:34Z craftit $"

#include "Ravl/TypeName.hh"
#include "Ravl/Hash.hh"
#include "Ravl/String.hh"
#include "Ravl/MTLocks.hh"
#include "Ravl/RCWrap.hh"
#include "Ravl/RealRange2d.hh"
#include "Ravl/IndexRange2d.hh"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

namespace RavlN {
  
  
  typedef const char *(*TypeNameMapT)(const type_info &type);
  extern TypeNameMapT TypeNameMap;
  
  static HashC<const char *,const char *> InitNameMapping();
  
  inline static HashC<const char *,const char *> &HandleNameMapping()  { 
    static HashC<const char *,const char *> handleNameMapping;
    return handleNameMapping;
  }
  
  
  inline static HashC<const char *,const char *> &TypeNameMapping()  { 
    static HashC<const char *,const char *> typeNameMapping = InitNameMapping();
    return typeNameMapping;
  }
  
  inline static HashC<const char *,const type_info *> &RTypeMapping() {
    static HashC<const char *,const type_info *> rTypeNameMapping;
    return rTypeNameMapping;
  }
  
  
  static TypeNameC type0(typeid(void),"void");
  
  static TypeNameC type1(typeid(ByteT),"ByteT");
  static TypeNameC type2(typeid(SByteT),"SByteT");
  static TypeNameC type3(typeid(IntT),"IntT");
  static TypeNameC type4(typeid(UIntT),"UIntT");
  
  static TypeNameC type5(typeid(RealT),"RealT");
  static TypeNameC type6(typeid(FloatT),"FloatT");
  
  //static TypeNameC type7(typeid(LongIntT),"LongIntT");
  //static TypeNameC type8(typeid(ULongIntT),"ULongIntT");
  
  static TypeNameC type9(typeid(Int16T),"Int16T");
  static TypeNameC type10(typeid(UInt16T),"UInt16T");
  
  static TypeNameC type11(typeid(StringC),"StringC");
  static TypeNameC type12(typeid(SubStringC),"SubStringC");
  
  static TypeNameC type13(typeid(IndexC),"IndexC");
  
  static TypeNameC type14(typeid(bool),"bool");
  static TypeNameC type15(typeid(RCBodyVC),"RCBodyVC");
  
  static TypeNameC type16(typeid(RCWrapAbstractC),"RavlN::RCWrapAbstractC");
  
  static TypeNameC type17(typeid(RealRange2dC),"RavlN::RealRange2dC");
  static TypeNameC type18(typeid(IndexRange2dC),"RavlN::IndexRange2dC");
  
  const char *TypeName(const char *name) { 
    MTReadLockC lock;
    const char **res =TypeNameMapping().Lookup(name);
    if(res != 0) {
      const char *ret = *res;
      return ret;
    }
    lock.Unlock();
#ifdef GNU
    // See if its a simple mangled name.
    if(isdigit(name[0])) {
      int len = atoi(name);
      const char *at = name;
      // Skip digits
      at++; // We already know the first character is a digit.
      while(isdigit(*at)) 
	at++;
      if(at[len] == 0) { // Is that all ?
	AddTypeName(name,at); // Add to table.
	return at;
      }
    }
#else
#if defined(__sgi__) || RAVL_COMPILER_VISUALCPP
    // Generate a standard class name.
    StringC newName(name);
    newName.gsub("> >",">>");
    newName.gsub(", ",",");
    newName.gsub(" ","_");
    if(strcmp(newName.chars(),name) != 0) {
      // Copy string so its not deleted.
      int len = newName.length();
      char *tmpName = (char *) malloc(len+1);
      char *at1 = tmpName;
      const char *at2 = newName.chars();
      for(;len > 0;len--)
      *(at1++) = *(at2++);
      *(at1++) = 0;
    AddTypeName(name,tmpName);
    return tmpName;
  }
    // Default is correct, so just use it.
    AddTypeName(name,name);
    return name;
#endif
#endif
#ifndef __sgi__
#ifndef NDEBUG
    cerr << "WARNING: No standard type name for : " << name << endl;
#endif
    AddTypeName(name,name); // Register name, to prevent repeated warnings.
    return name;
#endif
  }
  
  const char *TypeHandleName(const type_info &info) {
    MTReadLockC lock;
    const char **ptr = HandleNameMapping().Lookup(info.name());
    if(ptr == 0) {
      cerr << "WARNING: Handle type name not know for '" << info.name() << "' \n";
      return "Unknown";
    }
    return *ptr;
  }
  
  const char *TypeName(const type_info &info)  { 
    return TypeName(info.name()); 
  }

  static HashC<const char *,const char *> InitNameMapping() {
    TypeNameMap = &TypeName;
    return HashC<const char *,const char *>();
  }
  
  const type_info &RTypeInfo(const char *name) { 
    MTReadLockC lock;
    const type_info **tinf = RTypeMapping().Lookup(name);
    if(tinf != NULL) 
      return **tinf;
    return typeid(void); 
  }
  
  const char *RTypeName(const char *name) { 
    return RTypeInfo(name).name(); 
  }
  
  
  void AddTypeName(const char *sysname,const char *newname) {
    MTWriteLockC lock;
#if RAVL_CHECK
    if(TypeNameMapping().IsElm(sysname)) {
      if(strcmp(TypeNameMapping()[sysname],newname) != 0)
	IssueWarning(__FILE__,__LINE__,"Redefining TypeName '%s' from '%s' to '%s' ",sysname,TypeNameMapping()[sysname],newname);
    }
#endif
    TypeNameMapping()[sysname] = newname;
  }
  
  void AddTypeName(const type_info &info,const char *newname) { 
    AddTypeName(info.name(),newname); 
    MTWriteLockC lock;
    RTypeMapping()[newname] = &info;
  }
  
  //: Add body to handle type mapping.
  
  void AddTypeHandleName(const type_info &info,const char *newname) {
    MTWriteLockC lock;
    HandleNameMapping()[info.name()] = newname;
  }
 
}
