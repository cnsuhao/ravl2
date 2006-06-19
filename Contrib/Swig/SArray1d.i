// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html


%include "Ravl/Swig/Types.i"
%include "Ravl/Swig/Index.i"

%{
#include "Ravl/SArray1d.hh"
%}

namespace RavlN {
  
  template<typename DataT>
  class SArray1dC<DataT> {
  public:
    SArray1dC<DataT>(SizeT size);
    SArray1dC<DataT>();
    %extend {
      DataT &Access(const IndexC &index)
	{ return self->operator[](index); }
    }
    %extend {
      DataT &Access(const UIntT &index)
	{ return self->operator[](index); }
    }
    
    SizeT Size() const;
    // Get the size of the array
    
  };
}
