// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html

%include "Ravl/Swig/Types.i"
%include "Ravl/Swig/Index.i"

%{
#include "Ravl/Index2d.hh"
%}

namespace RavlN {
  class Index2dC {
  public:	
    Index2dC();
    Index2dC(IntT x,IntT y);
    Index2dC(IndexC x,IndexC y);
    IndexC Row() const;
    IndexC Col() const;
  };
}

