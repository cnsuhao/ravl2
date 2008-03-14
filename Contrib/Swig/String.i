// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html



%include "Ravl/Swig/Types.i"

%{
#ifdef SWIGPERL
#undef Copy
#endif

#include "Ravl/String.hh"

#ifdef SWIGPERL
#define Copy(s,d,n,t)   (MEM_WRAP_CHECK_(n,t) (void)memcpy((char*)(d),(const char*)(s), (n) * sizeof(t)))
#endif
%}

namespace RavlN
{

  class StringC
  {
  public:
    StringC();
    StringC(const char *);

    bool IsEmpty() const;

    const char *chars() const;

    SizeT Size() const;

#ifdef SWIGPYTHON

    %extend
    {
      const char *__str__()
      {
        return self->chars();
      }
    }

    %typemap(out) StringC
    {
      $result = PyString_FromStringAndSize($1.chars(), $1.Size());
    }
    
#endif

#ifdef SWIGPERL

    %typemap(out) StringC
    {
      $result = newSVpv($1.chars(), $1.Size());
    }

    %typemap(in) StringC
    {
      $1 = RavlN::StringC(SvPV($input, SvLEN($input)));
    }
    
#endif
  };

}


