// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////
// $Id$
//! rcsid="$Id$"
//! lib=RavlCore

#include "Ravl/Complex.hh"
#include <iostream.h>

using namespace RavlN;

int main(void)
{
  ostream & myStdO = cout;  // AT&T C++ 3.1 cout = ostream_withassign
                            // GNU C++ 2.4.5 it must be reference

  myStdO << "Complex number\n"
         << "==============\n";
  ComplexC a(3);
  ComplexC b(4,5);
  ComplexC c = a.I() + b.Conj();
  myStdO << "a                   : " << a << '\n'
         << "b                   : " << b << '\n' 
         << "c = a.I() + b.Conj(): " << c << '\n';
         

  myStdO << "End of the example\n" << flush;
  return(0);
}

// IAPS - Image analysis program system.
// End of file exComplx.cc



