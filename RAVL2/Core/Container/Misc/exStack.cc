// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: exStack.cc 5240 2005-12-06 17:16:50Z plugger $"
//! lib=RavlCore
//! file="Ravl/Core/Container/Misc/exStack.cc"
//! author="George (Jiri) Matas"
//! docentry="Ravl.API.Core.Stacks"
//! userlevel=Normal

#include "Ravl/Stack.hh"
#include "Ravl/StackIter.hh"
#include "Ravl/Stream.hh"

using namespace RavlN;

int main()
{
  StackC<int> s;
  
  // Push some numbers onto the stack.
  
  for(int i = 0; i <50 ; i++)
    s.Push(i+5);
  
  // Have a look at a few values.
  
  cout << "Size: " << s.Size() << '\n';
  cout << "Pop:  " << s.Pop()   << '\n';
  cout << "Top:  " << s.Top()   << '\n';
  cout << "First:" << s.First()   << '\n';
  
  // Iterate through the stack contents.
  
  for(StackIterC<int> it(s);it.IsElm();it.Next())
    cout << it.Data() << ' ';
  cout<< '\n';
  
  // Remove all items for the stack.
  
  s.Empty();
  
  cout << "Size: " << s.Size() << '\n';
  
  return 0;
}
