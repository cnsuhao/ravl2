// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
// $Id$
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Container/Misc/testQueue.cc"

#include "Ravl/BlkQueue.hh"
#include <iostream.h>
#include <stdlib.h>

using namespace RavlN;

int main() {
  BlkQueueC<int> q;
  int count = 0;
  int lget = -1;
  for(int i = 0;i < 5000;i++) {
    switch(rand() % 2)
      {
      case 0:
	q.InsLast(count++);
	break;
      case 1:
	if(q.IsEmpty())
	  continue;
	{
	  int lval = q.GetFirst();
	  if(lval != (lget+1)) {
	    cerr << "Queue test failed. \n";
	    return 1; 
	  }
	  lget = lval;
	}
      }
  }
  cerr << "Queue test passed ok. \n";
  return 0;
}

template class BlkQueueC<int>;
