// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Container/Queue/testFixedQueue.cc"

#include "Ravl/FixedQueue.hh"
#include "Ravl/Stream.hh"

using namespace RavlN;

int TestQueue();
int TestQueueIter();

int main() 
{
  int ln;
  if((ln = TestQueue()) != 0) {
    cerr << "Queue test failed at:" << ln << "\n";
    return 1;
  }
  if((ln = TestQueueIter()) != 0) {
    cerr << "Queue iter test failed at:" << ln << "\n";
    return 1;
  }
  
  cerr << "Test passed ok.\n";
  return 0;
}

int TestQueue()
{
  cerr << "Starting TestQueue() \n";
  FixedQueueC<int> q(5);
  for(int z = 0;z < 6;z++) {
    if(!q.IsEmpty()) {
      cerr << "IsEmpty test 1 failed. \n";
      return __LINE__;
    }
    if(!q.IsSpace()) {
      cerr << "IsSpace test 1 failed. \n";
      return __LINE__;
    }
    q.InsLast(1);
    if(q.IsEmpty()) {
      cerr << "IsEmpty test 1a failed. \n";
      return __LINE__;
    }
    if(q.Size() != 1) {
      cerr << "Size test 1 failed. \n";
      return __LINE__;
    }
    if(q.GetFirst() != 1) {
      cerr << "Content test 1 failed. \n";
      return __LINE__;
    }
    
    // Fill the queue.
    for(int i = 0;i < 5;i++) {
      if(!q.IsSpace()) {
	cerr << "IsSpace test 3 failed. \n";
	return __LINE__;
      }
      q.InsLast(i);
    }
    if(q.Size() != 5) {
      cerr << "Size test 2 failed. (Size() == " << q.Size() << ")\n";
      return __LINE__;
    }
    
    // Check it out.
    if(q.IsEmpty()) {
      cerr << "IsEmpty test 2 failed. \n";
      return __LINE__;
    }  
    if(q.IsSpace()) {
      cerr << "IsSpace test 2 failed. \n";
      return __LINE__;
    }
    
    for(int j = 0;j < 5;j++) {
      if(q.IsEmpty()) {
	cerr << "IsEmpty test 3 failed. \n";
	return __LINE__;
      }
      if(q.GetFirst() != j) {
	cerr << "Content test 2 failed. \n";
	return __LINE__;
      }
    }
  }
  return 0;
}

int TestQueueIter() {
  cerr << "Starting TestQueueIter() \n";
  FixedQueueC<int> q(5);
  for(int f = 1;f < 6;f++) {
    for(int z = 0;z < 6;z++) {
      // Shit the queue bountry on.
      for(int k = 0;k < 1;k++) {
	q.InsLast(1);
	q.GetFirst();
      }
      for(int i = 0;i < f;i++) 
	q.InsLast(i);
      FixedQueueIterC<int> it(q);
      int cc = 0;
      for(int j = 0;it;j++,it++) {
	if(j >= f) {
	  cerr << "operator bool(), test failed. j=" << j << " q.Size()=" << q.Size()<< "\n";
	  return __LINE__;
	}
	if(*it != j) {
	  cerr << "operator bool(), iter content test failed. \n";
	  return __LINE__;
	}
	cc++;
      }
      if(cc != f) {
	cerr << "Iteration failed :" << cc << " of "  << f << "elements covered. \n";
	return __LINE__;
      }
      // Empty queue again.
      for(int i = 0;i < f;i++) {
	if(q.GetFirst() != i) {
	  cerr << "Content test failed. \n";
	  return __LINE__;
	}
      }
    }
  }
  return 0;
}

template class FixedQueueC<int>;
