// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html


%include "Ravl/Swig/Point2d.i"

%{
#include "Ravl/Polygon2d.hh"
%}

namespace RavlN {

  class Polygon2dC {
  public:
    Polygon2dC();
    void InsLast(Point2dC &point);
    // Add point to polygon
    
    SizeT Size() const;
    // Number of points in the polygon
  };
}

