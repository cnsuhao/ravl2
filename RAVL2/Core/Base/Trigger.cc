// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////
//! rcsid="$Id: Trigger.cc 79 2001-05-10 13:44:47Z craftit $"
//! lib=RavlCore
//! file="Ravl/Core/Base/Trigger.cc"

#include "Ravl/Trigger.hh"
#include "Ravl/Assert.hh"

namespace RavlN
{
  void TriggerBodyC::Invoke() { 
    RavlAssertMsg(0,"Abstract method called : RavlN::TriggerC::Invoke() \n");
  }
}
