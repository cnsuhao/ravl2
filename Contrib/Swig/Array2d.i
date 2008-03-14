// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html


%include "Ravl/Swig/Types.i"
%include "Ravl/Swig/IndexRange2d.i"

%{
#ifdef SWIGPERL
#undef Copy
#endif

#include "Ravl/Array2d.hh"

#ifdef SWIGPERL
#define Copy(s,d,n,t)   (MEM_WRAP_CHECK_(n,t) (void)memcpy((char*)(d),(const char*)(s), (n) * sizeof(t)))
#endif
%}

namespace RavlN {

  template<typename DataT>
  class Array2dC {
  public:
    Array2dC();
    Array2dC(SizeT rows,SizeT cols);
    Array2dC(const IndexRange2dC &range);
    IndexRange2dC Frame();
    void Fill(const DataT &value);
    IntT Stride() const;
    %extend {
      DataT &Access(const Index2dC &index)
	{ return self->operator[](index); }
    }
    %extend {
      DataT &Access(IntT r,IntT c)
	{ return self->operator[](r)[c]; }
    }
    %extend {
      DataT &Access(IndexC r,IndexC c)
	{ return self->operator[](r)[c]; }
    }
  };
  %template(Array2dByteC) Array2dC<ByteT>;
  %template(Array2dRealC) Array2dC<RealT>;
}

