// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_RESOURCE_HEADER
#define RAVL_RESOURCE_HEADER 1
//! rcsid="$Id$"
//! lib=RavlCore
//! docentry="Ravl.API.Core.Resource"
//! userlevel=Normal
//! file="Ravl/Core/Base/Resource.hh"

#include "Ravl/String.hh"

namespace RavlN {
  
  //!userlevel=Normal
  
  bool SetResourceRoot(const StringC &name);
  //: Access root of resource directory.
  
  const StringC &ResourceRoot();
  //: Access root of resource directory.
  
  StringC Resource(const char *module,const char *name);
  //: Get location of resource.
  
  //!userlevel=Advanced
  
  typedef StringC (*ResourceLookupFuncT)(const char *module,const char *name);
  
  bool SetResourceLookupFunc(ResourceLookupFuncT resourceLookup);
  //: Replace method for doing resource lookups.
  
}



#endif
