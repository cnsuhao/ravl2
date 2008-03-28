// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2006, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// Python is used under the terms of the Python License
// Copyright (C) 2001, 2002, 2003, 2004 Python Software Foundation; All Rights Reserved
// file-header-ends-here
////////////////////////////////////////////////
//! file = "Ravl/Contrib/Python/PythonLock.cc"
//! lib = RavlPython

#include "Ravl/PythonLock.hh"
#include "Ravl/Assert.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN
{
  
	PythonLockC::PythonLockC(PyThreadState *threadState)
	{
    RavlAssert(threadState != NULL);
    PyEval_AcquireLock();
    PyThreadState_Swap(threadState);
	}

  PythonLockC::~PythonLockC()
  {
    PyThreadState_Swap(NULL);
    PyEval_ReleaseLock();
  }
  
}
