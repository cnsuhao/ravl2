// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html

#include "Ravl/Swig/Image.i"

%{
#ifdef SWIGPERL
#undef Copy
#endif

#include "Ravl/Image/Image.hh"
#include "Ravl/DP/Port.hh"
#include "Ravl/DP/SequenceIO.hh"

#ifdef SWIGPERL
#define Copy(s,d,n,t)   (MEM_WRAP_CHECK_(n,t) (void)memcpy((char*)(d),(const char*)(s), (n) * sizeof(t)))
#endif
%}

namespace RavlN {

  template<typename DataT>
  class DPIPortC 
  {
  public:
    DPIPortC();
    bool Get(DataT &buff);
    bool SetAttr(const StringC & attrName, const StringC & attrValue);
    bool GetAttr(const StringC & attrName, StringC & attrValue);
  };

  %template(DPIPortImageByteC) DPIPortC<RavlImageN::ImageC<ByteT> >;

  bool OpenISequence(DPIPortC<RavlImageN::ImageC<ByteT> >&, const StringC &);

}

