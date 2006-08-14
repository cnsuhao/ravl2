// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html

%include "Ravl/Swig/Types.i"
%include "Ravl/Swig/DList.i"

%{
#include "Ravl/Point2d.hh"
%}

namespace RavlN {
  class Point2dC {
  public:	
    Point2dC();
    Point2dC(RealT x,RealT y);
    RealT Row() const;
    RealT Col() const;
  };
}

DLIST_TOLIST_OBJECT(Point2d, RavlN::Point2dC)
