// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_STACKIT_HEADER
#define RAVL_STACKIT_HEADER
//! date="12/10/1995"
//! docentry="Ravl.Core.Stacks"
//! file="Ravl/Core/Container/Misc/StackIt.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="George (Jiri) Matas"
//! example=exStack.cc
//! rcsid="$Id$"

#include "Ravl/Stack.hh"

namespace RavlN {
  
  //: StackC iterator.
  // This iterates back through the stack.  Starting at the top element.
  
  template <class T>
  class StackIterC
    : private BaseStackC<T>
  {
    
  public:
    StackIterC(StackC<T> & s)
      : BaseStackC<T>(s),
	stack(&s)
    { DecrTop() ;}
    //: Constructor.
    
    StackIterC()
      : stack(0)
    {}
    //: Default constructor.
    
    StackC<T>& Stack() { 
      RavlAssert(stack != 0);
      return *stack; 
    }
    //: Access the stack we're iterating.
    
    StackC<T>& Container()   
    { return stack; }
    //: Access the stack we're iterating.
    
    T& Data() 
    { return topBlk->d[top];}
    //: Access the data.

    const T& Data() const
    { return topBlk->d[top];}
    //: Access the data.
    
    T& operator *()
    { return Data(); }
    //: Access data.

    const T& operator *() const
    { return Data(); }
    //: Access data.

    T* operator ->()
    { return &Data(); }
    //: Access data.
    
    const T* operator ->() const
    { return &Data(); }
    //: Access data.
    
    void First()       
    { BaseStackC<T>::operator=(stack); DecrTop();}
    //: Goto first element in stack.
    
    void Next() 
    { DecrTop(); }  
    //: Goto next element in stack.

    void operator++(int)
    { Next(); }
    //: Goto next element in stack.
    
    bool IsElm() const 
    { return top>=0 ;} 
    //: Is this a valid element ?
    
    operator bool() const
    { return IsElm(); }
    //: Is this a valid element ?
    
    bool IsLast() const 
    { return top==1 && blkSize==incrBlkSize;}
    //: Last item in stack.
    
    long Index() const 
    { return Size() + 1;}
    //: Position in stack.
    
  private:
    StackC<T>*         stack; // Stack we're iterating.
    
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

