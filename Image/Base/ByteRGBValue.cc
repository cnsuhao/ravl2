// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
// $Id$
//! rcsid="$Id$"
//! lib=RavlImage

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/TypeName.hh"

namespace RavlN {
  static TypeNameC type1(typeid(ImageC<ByteT>),"ImageC<ByteT>");  
  static TypeNameC type2(typeid(ByteRGBValueC),"ByteRGBValueC");
  static TypeNameC type3(typeid(ImageC<ByteRGBValueC>),"ImageC<ByteRGBValueC>");

}
