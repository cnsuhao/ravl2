// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlOS
//! author="Charles Galambos"

#include "Ravl/OS/SysLog.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/Calls.hh"
#include "Ravl/MTLocks.hh"

#if RAVL_OS_POSIX
#include <syslog.h>
#endif

namespace RavlN {
  
  static StringC syslog_ident("NoName");
  static bool syslog_Open = false;
  static bool syslog_StdErrOnly = false;
  static bool syslog_StdErr = false;
  static int localLevel = 8;
  static int syslogLevel = 8;
  
  //: Open connection to system logger.
  // Facility is set to 'LOG_USER' by default. <br>
  // If logPid is true the processes id will be recorded in the log. <br>
  // If sendStdErr is set the messages will also be send the standard error channel.
  
  bool SysLogOpen(const StringC &name,bool logPid,bool sendStdErr,bool stdErrOnly,int facility) {
    syslog_ident = name;
    syslog_Open = true;
    syslog_StdErrOnly = stdErrOnly;
    if(stdErrOnly)
      syslog_StdErr = true;
    syslog_StdErr = sendStdErr;
#if RAVL_OS_POSIX
    if(facility == -1)
      facility = LOG_USER;
    int options = 0;
    if(logPid)
      options |= LOG_PID;
    if(sendStdErr)
      options |= LOG_PERROR;
    openlog(syslog_ident,options,facility);
#endif
    return true;
  }
  
  //: Close connection to system logger.
  // The call of this function is optional.
  
  bool SysLogClose() {
#if RAVL_OS_POSIX
    closelog();
    syslog_Open = false;
#endif
    return true;
  }
  
#if RAVL_OS_POSIX
  // Mapping to syslog levels, though they should be indentical.
  static const int messageTypes[8] = { 
    LOG_EMERG,
    LOG_ALERT,
    LOG_CRIT,
    LOG_ERR,
    LOG_WARNING,
    LOG_NOTICE,
    LOG_INFO,
    LOG_DEBUG
  };
#endif
  
  static bool LogMessage(const char *message,int priority) {
    MTWriteLockC lockWrite(2); // Be carefull in multithreaded programs.
#if RAVL_OS_POSIX
    if(syslog_StdErrOnly) {
      if(priority <= localLevel)
	cerr << syslog_ident << ":" << message << endl;
    } else {
      if(priority < syslogLevel) {
	syslog(priority,"%s",message);
      } else {
	if(syslog_StdErr && priority <= localLevel)
	  cerr << syslog_ident << ":" << message << endl;
      }
    }    
#else
    if(priority < localLevel)
      cerr << syslog_ident << ":" << message << endl;
#endif
    return true;
  }
  
  //: Send a message to the log file
  // Usage: <br>
  // SysLog(SYSLOG_DEBUG) << "Send message to log";
  
  OStreamC SysLog(SysLogPriorityT priority) {
    if(!syslog_Open)
      SysLogOpen("NoName",true,true);
#if RAVL_OS_POSIX
    int pri = LOG_DEBUG;
    if(priority >= 0 && priority < 8)
      pri = messageTypes[(int) priority];
#else
    int pri = (int) priority;
#endif
    return StrOStreamC(Trigger(LogMessage,"",pri)); 
  }

  //: Set the level of messages to send to the system.
  // Only messages with a priority lower than 'level' we be sent.
  // This can be used to avoid flooding the log system
  // with debug messages for example.
  
  bool SysLogLevel(SysLogPriorityT level) 
  { 
    int pri = (int) level;
    if(pri < 0)
      pri = 0;
    else if(pri > 7)
      pri = 7;
#if RAVL_OS_POSIX
    syslogLevel = messageTypes[pri];
#else
    syslogLevel = pri;
#endif
    return true;
  }
  
  //: Set the level of messages to send to standard error.
  // This controls the level of messages to send to
  // cerr. <br>
  // Only messages with a priority lower than 'level' we be sent.
  
  bool SysLogLevelStdErr(SysLogPriorityT level) { 
    int pri = (int) level; 
    if(pri < 0)
      pri = 0;
    else if(pri > 7)
      pri = 7;    
#if RAVL_OS_POSIX
    localLevel = messageTypes[pri];
#else
    syslogLevel = pri
#endif
    return true;
  }
  
  
}
