// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlNet

#include "Ravl/OS/NetRequestManager.hh"
#include "Ravl/OS/SysLog.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Constructor.
  
  NetRequestManagerC::NetRequestManagerC(bool nthrowExceptionOnFail)
    : reqIdAlloc(0),
      connectionOk(true),
      throwExceptionOnFail(nthrowExceptionOnFail)
  {}
  
  //: Create new request.
  
  bool NetRequestManagerC::CreateReq(UIntT &id) {
    MutexLockC hold(reqAccess);
    id = reqIdAlloc++;
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetRequestManagerC::CreateReq(), ReqId=" << id);
    id2reqResults[id] = NetRequestDataC(true);
    return true;
  }
  
  //: Deliver data to waiting thread.
  
  bool NetRequestManagerC::DeliverReq(UIntT id,const RCWrapAbstractC &data) {
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetRequestManagerC::::DeliverReq(), ReqId=" << id << " Called. ");
    MutexLockC hold(reqAccess);
    NetRequestDataC reqInfo;
    if(!id2reqResults.Lookup(id,reqInfo)) {
      SysLog(SYSLOG_WARNING) << "NetRequestManagerC::::DeliverReq(), WARNING: Unexpect reply " << id;
      return false;
    }
    reqInfo.Data() = data;
    reqInfo.Event().Post();
    return true;
  }
  
  //: Wait for reply to request to arrive.
  // Returns false on time out.
  
  bool NetRequestManagerC::WaitForReq(UIntT id,RCWrapAbstractC &data) {
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetRequestManagerC::WaitForReq(), ReqId=" << id);
    // Setup request.
    MutexLockC hold(reqAccess);
    if(!connectionOk) {
      SysLog(SYSLOG_CRIT) << "NetRequestManagerC::WaitForReq(), ERROR: Connection not open! ";
      throw ExceptionOperationFailedC("NetRequestManagerC::WaitForReq(), Failed. ");
    }
    NetRequestDataC reqInfo;
    if(!id2reqResults.Lookup(id,reqInfo)) {
      SysLog(SYSLOG_WARNING) << "NetRequestManagerC::WaitForReq(), WARNING: Unknown request. "  << id;
      return false;
    }
    hold.Unlock();
    
    // Wait for reply to request.
    reqInfo.Event().Wait(); // FIXME :- throw an exception on time out ?
    
    hold.Lock();
    
    // Extract data from request reply.
    data = reqInfo.Data();
    if(!data.IsValid()) { // Request fail for some reason ?
      SysLog(SYSLOG_ERR) << "NetRequestManagerC::WaitForReq(), ERROR: Request Failed. ";
      if(throwExceptionOnFail)
	throw ExceptionOperationFailedC("NetRequestManagerC::WaitForReq(), Failed. ");
      return false;
    }
    
    // Remove it from pending table.
    if(!id2reqResults.Del(id))
      SysLog(SYSLOG_WARNING) << "WARNING: Request not present in pending table at end of WaitForReq(). ";
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetRequestManagerC::WaitForReq(), ReqId=" << id << " Done.\n");
    return true;
  }
  
}
