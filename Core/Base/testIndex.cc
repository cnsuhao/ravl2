// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore

#include "Ravl/IndexRange1d.hh"

using namespace RavlN;

int main()
{
  IndexRangeC r1(0,3);
  IndexRangeC r2(1,2);
  IndexRangeC r3(r1);
  r3.Clip(r2);
  if(!r1.Contains(r3)) {
    cerr << "IndexRange test 1 failed " << r1 << " does not contain " << r3 << "\n";
    return 1;
  }
  if(!r2.Contains(r3)) {
    cerr << "IndexRange test 2 failed. " <<r2 << " does not contain " << r3 << "\n";
    return 1;
  }
  cerr << "Test passed ok. \n";
  return 0;
}
