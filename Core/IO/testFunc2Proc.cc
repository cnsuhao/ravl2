// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/testFunc2Proc.cc"

#include "Ravl/DP/Func2Proc.hh"
#include "Ravl/DP/FuncP2Proc.hh"

using namespace RavlN;

int conv(const int &val) {
  return val;
}

int main()
{
  DPFunc2ProcC<int,int,conv> func;
}

template class DPFunc2ProcC<int,int,conv>;
