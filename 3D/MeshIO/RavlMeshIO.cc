// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=Ravl3DIO

namespace Ravl3DN {

  extern void InitTriSetIO();

  extern void InitTriFormat();
  
  void InitRavlMeshIO() {
    InitTriFormat();
    InitTriSetIO();
  }
}
