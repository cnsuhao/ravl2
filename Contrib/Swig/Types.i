// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html

#include "Ravl/Swig/Size.i"

%{
#ifdef SWIGPERL
#undef Copy
#endif

#include "Ravl/Types.hh"
#include "Ravl/Stream.hh"

#ifdef SWIGPERL
#define Copy(s,d,n,t)   (MEM_WRAP_CHECK_(n,t) (void)memcpy((char*)(d),(const char*)(s), (n) * sizeof(t)))
#endif
%}

namespace RavlN
{
  typedef double RealT;
  typedef float FloatT;
  typedef int IntT;
  typedef unsigned int UIntT;
  typedef short int Int16T;
  typedef unsigned char ByteT;
#ifdef linux64
  typedef signed long int Int64T;
  typedef unsigned long int UInt64T;
#else
  typedef signed long long int Int64T;
  typedef unsigned long long int UInt64T;
#endif
  typedef SizeC SizeT;

}
