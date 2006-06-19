// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html

%include "Ravl/Swig/Types.i"

%{
#include "Ravl/Index.hh"
%}

namespace RavlN {
  class IndexC {
  public:	
    IndexC();
    IndexC(IntT);
    IntT V() const;
    %rename(Add) IndexC::operator+(IndexC v1);
    %rename(Sub) IndexC::operator-(IndexC v1);
  };

}

