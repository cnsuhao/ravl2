// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include "Ravl/DP/AttributeCtrlInternal.hh"
#include "Ravl/MTLocks.hh"

namespace RavlN {
  
  //: Issue attribute changed signal.
  
  void AttributeCtrlInternalC::IssueChangedSignal(const StringC &attrName) {
    MTWriteLockC lock(3);
    DListC<TriggerC> lst = name2trigList[attrName].Copy();
    lock.Unlock();
    for(DLIterC<TriggerC> it(lst);it;it++)
      (*it).Invoke();
  }
  
  //: Register a changed signal.
  
  IntT AttributeCtrlInternalC::RegisterChangedSignal(const StringC &attrName,const TriggerC &trig) {
    IntT id = trigIdAlloc++;
    DListC<TriggerC> &list = name2trigList[attrName];
    list.InsFirst(trig);
    trigId2trig[id] = list;
    return id;
  }
  
  //: Remove changed signal.
  
  bool AttributeCtrlInternalC::RemoveChangedSignal(IntT id) {
    DLIterC<TriggerC> *trig = trigId2trig.Lookup(id);
    if(trig == 0) 
      return false;
    trig->Del();
    trigId2trig.Del(id);
    return true;
  }
  
}
