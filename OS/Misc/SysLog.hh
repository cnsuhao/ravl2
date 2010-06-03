// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SYSLOG_HEADER
#define RAVL_SYSLOG_HEADER 1
//! author="Charles Galambos"
//! example=exSysLog.cc
//! docentry="Ravl.API.OS.SysLog"
//! rcsid="$Id: SysLog.hh 7087 2009-02-04 15:43:59Z craftit $"
//! lib=RavlOS
//! file="Ravl/OS/Misc/SysLog.hh"

#include "Ravl/Stream.hh"

namespace RavlN {
  enum SysLogPriorityT {
    SYSLOG_EMERG = 0,
    SYSLOG_ALERT,
    SYSLOG_CRIT,
    SYSLOG_ERR,
    SYSLOG_WARNING,
    SYSLOG_NOTICE,
    SYSLOG_INFO,
    SYSLOG_DEBUG
  };
  
  bool SysLogOpen(const StringC &name,bool logPid = false,bool sendStdErr = true,bool stdErrOnly = false,int facility = -1);
  //: Open connection to system logger.
  // Facility is set to 'LOG_USER' by default. <br>
  // If logPid is true the processes id will be recorded in the log. <br>
  // If sendStdErr is set the messages will also be send the standard error channel.
  
  bool SysLogClose();
  //: Close connection to system logger.
  // The call of this function is optional.
  
  OStreamC SysLog(SysLogPriorityT priority = SYSLOG_DEBUG);
  //: Send a message to the log file
  // Usage: <br>
  // SysLog(SYSLOG_DEBUG) << "Send message to log";
  
  void SysLog(SysLogPriorityT priority,const char *format ...);
  //: Send a message to the log file
  // Usage: <br>
  // SysLog(SYSLOG_DEBUG,"msg",args...);
  
  bool SysLogLevel(SysLogPriorityT level);
  //: Set the level of messages to send to the system.
  // Only messages with a priority higher or equal to 'level' 
  // we be sent.
  // This can be used to avoid flooding the log system 
  // with debug messages for example.
  
  bool SysLogLevelStdErr(SysLogPriorityT level);
  //: Set the level of messages to send to standard error.
  // This controls the level of messages to send to
  // cerr. <br>
  // Only messages with a priority higher or equal to 'level' we be sent.
  
  const StringC &SysLogApplicationName();
  //: Get the name of the current application.
  
  bool SysLogRedirect(void (*logFunc)(SysLogPriorityT level,const char *message));
  //: Register function to redirect log messages.
  // Calling with a null function pointer restores the default behavour.
}

#endif
