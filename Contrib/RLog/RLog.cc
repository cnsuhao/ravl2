// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include "Ravl/Stream.hh"

#include "Ravl/RLog.hh"
#include "Ravl/Hash.hh"

#include <rlog/RLogChannel.h>
#include <rlog/StdioNode.h>
#include <rlog/rlog.h>
#include <fcntl.h>

#ifdef WIN32
#include <io.h>
#include <sys\stat.h>
#endif

namespace RavlN {
  
  bool g_RLogInitDone = false;
  static rlog::StdioNode *g_rlogNode = 0;
  
  //! Initialise rlog to filename (filename can be stderr)
  bool RLogInit(const StringC &filename, const StringC &verbose, const StringC &logLevel)
  {
    return RLogInit(0, NULL, filename.chars(), verbose == "true") &&
           RLogSubscribeL(logLevel.chars());    
  }      
  
  bool RLogInit(int argc, char **argv, const char *filename, bool verbose) 
  {
    //std::cerr << "InitRLog(), Called. \n";
    if(g_RLogInitDone)
      return true;
    g_RLogInitDone = true;
    
    int fd = 0;
    if(strcmp(filename, "stderr") == 0) 
    {
      fd = 2;
    }
    else 
    {
      //FIXME need mecanism of closing the log file
#ifdef WIN32	
	  fd = _open(filename, _O_WRONLY | _O_CREAT | _O_APPEND, _S_IREAD | _S_IWRITE);
#else
      mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
      fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, mode);
#endif
      if(fd == -1) 
      {
        fprintf(stderr, "[Error] Failed to open log-file %s\n", filename);
	return false;
      }
    }
    int args = argc;
    rlog::RLogInit(args, argv);
															  
    g_rlogNode = new rlog::StdioNode(fd,
                                     rlog::StdioNode::OutputColor | 
                                     (verbose ? rlog::StdioNode::OutputContext : 0) | 
                                     rlog::StdioNode::OutputChannel);
    
    if(verbose)
      rInfo("RLog initalised. ");
    return true;
  }
  
  bool RLogInit(bool verbose) {
    //std::cerr << "InitRLog(), Called. \n";
    if(g_RLogInitDone)
      return true;
    g_RLogInitDone = true;
    
    g_rlogNode = new rlog::StdioNode(2,
                                     rlog::StdioNode::OutputColor | 
                                     (verbose ? rlog::StdioNode::OutputContext : 0) | 
                                     rlog::StdioNode::OutputChannel
                                     );
    
    
    //rlogStdio->subscribeTo(RLOG_CHANNEL(""));
    //rlogStdio->subscribeTo(RLOG_CHANNEL_IMPL(Ravl,"",rlog::Log_Undef));    
    //g_rlogNode->subscribeTo(rlog::GetComponentChannel("Ravl","",rlog::Log_Undef));
    g_rlogNode->subscribeTo(rlog::GetGlobalChannel(""));
    if(verbose)
		rInfo("RLog initalised. ");
    return true;
  }
  
  bool RLogSubscribe(rlog::RLogChannel *Channel)
  {
    if(g_rlogNode == 0)
      RLogInit();
    RavlAssert(g_rlogNode != 0);
    g_rlogNode->subscribeTo(Channel);  
    return true;
  }
  
  //! Subscribe to a model.
  bool RLogSubscribe(const char *moduleName,const char *path,rlog::LogLevel level) {
    if(g_rlogNode == 0)
      RLogInit();
    RavlAssert(g_rlogNode != 0);
    g_rlogNode->subscribeTo(rlog::GetComponentChannel(moduleName,path,rlog::Log_Undef));
    return true;
  }

  //! Subscribe according to log level
  bool RLogSubscribeL(const char *LogLevel)
  {
    static int a = 0;
    if(a != 0)
    {
      rDebug("Trying to subscribe to rlog for second time with logLevel:%s\n", LogLevel);
      return true;
    }    
    
    if(strcmp(LogLevel, "debug") == 0)
    {
      RLogSubscribe(rlog::_RLDebugChannel);
      RLogSubscribe(rlog::_RLInfoChannel);
      RLogSubscribe(rlog::_RLWarningChannel);
      RLogSubscribe(rlog::_RLErrorChannel);
    }
    else if(strcmp(LogLevel, "info") == 0)
    {
      RLogSubscribe(rlog::_RLInfoChannel);
      RLogSubscribe(rlog::_RLWarningChannel);
      RLogSubscribe(rlog::_RLErrorChannel);
    }
    else if(strcmp(LogLevel, "warning") == 0)
    {
      RLogSubscribe(rlog::_RLWarningChannel);
      RLogSubscribe(rlog::_RLErrorChannel);
    }
    else 
    {
      RLogSubscribe(rlog::_RLErrorChannel);
    }
											       
    return true;											       
  }
  
}//end of namespace

