// This file is used in conjunction with RAVL, Recognition And Vision Library
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here

#include "AuxVectorSSE.hh"

#include "Ravl/CPUID.hh"

#include <stdio.h>

namespace RavlN
{

void InitRavlAuxVectorSSE()
{
}

AuxVectorC* GetAuxVectorSSE2()
{
  RavlN::CPUIDC cpuid;
  if(cpuid.sse2())
  {
    //printf("using SSE\n");
    return new AuxVectorSSEC();
  }
  else
  {
    //printf("do not using SSE\n");
    return new AuxVectorC();
  }
}

static int InitFunc()
{
  //printf("InitFunc\n"); 
  GetAuxVector = &GetAuxVectorSSE2;
  return 0;
}

static int a = InitFunc();

} //end of namespace RavlN
