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

namespace RavlN {
  
  bool g_RLogInitDone = false;
  static rlog::StdioNode *g_rlogNode = 0;
  
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
  
  //! Subscribe to a model.
  
  bool RLogSubscribe(const char *moduleName,const char *path,rlog::LogLevel level) {
    if(g_rlogNode == 0)
      RLogInit();
    RavlAssert(g_rlogNode != 0);
    g_rlogNode->subscribeTo(rlog::GetComponentChannel(moduleName,path,rlog::Log_Undef));
    return true;
  }
  
}

