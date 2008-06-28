// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_RLOG_HEADER
#define RAVL_RLOG_HEADER

#ifndef RLOG_COMPONENT
#define RLOG_COMPONENT Ravl
#endif

#include <rlog/rlog.h>

namespace RavlN {
  
  //! Initialise rlog to filename (filename can be stderr)
  bool RLogInit(int argc, char **argv, const char *filename, bool verbose);
  
  //! Initalise rlog to standard out
  bool RLogInit(bool verbose = false);
  
  //! Subscribe to a model.
  bool RLogSubscribe(const char *moduleName,const char *path = "",rlog::LogLevel level = rlog::Log_Undef);
  
  //! Subscribe to a channel (_RLDebugChannel, _RLInfoChannel, _RLWarningChannel, _RLErrorChannel)
  bool RLogSubscribe(rlog::RLogChannel *Channel);
  
  //! Subscribe according to log level
  bool RLogSubscribeL(const char *LogLevel);
}

#endif
