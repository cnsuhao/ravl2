// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/PowerSpectrum1d.hh"
#include "Ravl/Random.hh"
#include "Ravl/Array1dIter.hh"

using namespace RavlN;

int main()
{
  int size = 16;
  Array1dC<RealT> data(size);
  for(Array1dIterC<RealT> it(data);it;it++)
    it.Data() = Random1();
  cerr << "Calculating power spectrum.:\n";
  PowerSpectrum1dC ps(size);
  Array1dC<RealT> res = ps.Apply(data);
  cerr << "Result:";
  cerr << res << "\n";
}
