// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCameraCal

#include "Ravl/3D/PinholeCamera0.hh"

namespace Ravl3DN
{
  using namespace RavlN;

  istream& operator>>(istream& s, PinholeCamera0C& camera)
  {
    s >> camera.fx() >> camera.fy() >> camera.cx() >> camera.cy();
    s >> camera.R();
    s >> camera.t();
    return s;
  }

  ostream& operator<<(ostream& s, const PinholeCamera0C& camera)
  {
    s << camera.fx() 
      << " " << camera.fy() 
      << " " << camera.cx() 
      << " " << camera.cy() 
      << endl;
    s << camera.R();
    s << camera.t();
    return s;
  }
};
