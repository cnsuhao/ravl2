// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLSTACKIT_HEADER
#define RAVLSTACKIT_HEADER
//! date="12/10/95"
//-------------------------------------------------------------------------- 
//  Copyright (c) 1995 by George (Jiri) Matas        g.matas@ee.surrey.ac.uk
//  All rights reserved.
//--------------------------------------------------------------------------
//! docentry="Ravl.Core.Stacks"
//! file="Ravl/Core/Container/Misc/StackIt.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="George (Jiri) Matas"
//! example=exStack.cc
//! rcsid="$Id$"

#include "Ravl/Stack.hh"

namespace RavlN {

  //: Stack iterator.
  // This iterates back through the stack.  Starting at the top element.
  
  template <class T>
  class StackIterC
    : private BaseStackC<T>
  {
    
  public:
    StackIterC(StackC<T> & s)
      : BaseStackC<T>(s),
      stack(s)
      { DecrTop() ;}
    //: Constructor.
    
    StackC<T>& Stack()       
      { return stack; }
    //: Access the stack we're iterating.
    
    StackC<T>& Container()   
      { return stack; }
    //: Access the stack we're iterating.
    
    T& Data() 
      { return topBlk->d[top];}
    //: Access the data.
    
    void First()       
      { BaseStackC<T>::operator=(stack); DecrTop();}
    //: Goto first element in stack.
    
    void Next() 
      { DecrTop(); }  
    //: Goto next element in stack.
    
    bool IsElm() const 
      { return top>=0 ;} 
    //: Is element.
    
    bool IsLast() const 
      { return top==1 && blkSize==incrBlkSize;}
    //: Last item in stack.
    
    long Index() const 
      { return Size() + 1;}
    //: Position in stack.
    
  private:
    StackC<T>&         stack; // Refrence to stack.
    
    inline void        DecrTop() { 
      if(top==0) { 
	blkSize -= incrBlkSize; 
	top      = blkSize;
	if (0 != topBlk) topBlk   = topBlk->link;
      }
      --top;
    }
  };
}

#endif

