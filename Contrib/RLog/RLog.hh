// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_RLOG_HEADER
#define RAVL_RLOG_HEADER

#include <rlog/rlog.h>

namespace RavlN {
  
  //: Initalise rlog to standard out
  bool RLogInit(bool verbose = false);
  
  //! Subscribe to a model.
  bool RLogSubscribe(const char *moduleName,const char *path = "",rlog::LogLevel level = rlog::Log_Undef);
  
}

#endif
