// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, James Smith
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////
//! rcsid="$Id: URLIO.cc 1965 2002-10-31 11:34:01Z vap-james $"
//! lib=RavlURLIO
//! file="Ravl/Contrib/HTTP/URLIO.cc"

namespace RavlN {
  
  extern void InitURLStreamIO();
  
  void InitURL() {
     InitURLStreamIO();
  }

}
