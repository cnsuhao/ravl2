// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: RavlInitDMediaIO.cc 3074 2003-06-13 07:23:52Z craftit $"
//! lib=RavlDMedia
//! file="Ravl/Contrib/DMedia/RavlInitDMediaIO.cc"

#include "Ravl/DMedia/DIVOFormat.hh"

namespace RavlImageN
{
  extern void InitFormatDIVO();
  
  void InitDMedaIO() {
    InitFormatDIVO();
  }
  
};

