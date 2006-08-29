// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html

%module Ravl

%{
namespace RavlGUIN
{
  extern void InitDPWindowFormat();
  extern void InitDPDisplayImage();
  void XInitRavlGUIDisplay()
  {
    InitDPWindowFormat();
    InitDPDisplayImage();
  }
}
%}

%include "Ravl/Swig/Types.i"
%include "Ravl/Swig/Point2d.i"
%include "Ravl/Swig/Image.i"
%include "Ravl/Swig/Polygon2d.i"
%include "Ravl/Swig/String.i"
%include "Ravl/Swig/Font.i"
%include "Ravl/Swig/Array2d.i"
%include "Ravl/Swig/SArray1d.i"
%include "Ravl/Swig/Affine2d.i"
%include "Ravl/Swig/DList.i"
%include "Ravl/Swig/Date.i"
%include "Ravl/Swig/PointSet2d.i"
%include "Ravl/Swig/RealRange.i"
%include "Ravl/Swig/RealRange2d.i"
%include "Ravl/Swig/Hash.i"

