// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/CPDDesignerFactory.hh"
#include "Ravl/Prob/VariableDiscrete.hh"
#include "Ravl/Prob/VariableContinuous.hh"
#include "Ravl/Prob/CPDDesignerContinuousDiscrete1.hh"
#include "Ravl/OS/SysLog.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlProbN {
  using namespace RavlN;
  
  CPDDesignerFactoryBodyC::CPDDesignerFactoryBodyC() {
  }

  CPDDesignerFactoryBodyC::~CPDDesignerFactoryBodyC() {
  }

  CPDDesignerC CPDDesignerFactoryBodyC::GetCPDDesigner(const VariableC& variable, const VariableSetC& parentVariableSet) const {
    if (((VariableContinuousC)variable).IsValid()) {
      // the variable is continuous
      ONDEBUG(SysLog(SYSLOG_DEBUG) << "CPDDesignerFactoryBodyC::GetCPDDesigner(), variable is continuous");
      if (parentVariableSet.Size() == 1) {
        // single parent variable
        ONDEBUG(SysLog(SYSLOG_DEBUG) << "CPDDesignerFactoryBodyC::GetCPDDesigner(), single parent variable");
        VariableC parentVariable = parentVariableSet.Variable(0);
        if (((VariableDiscreteC)parentVariable).IsValid()) {
          ONDEBUG(SysLog(SYSLOG_DEBUG) << "CPDDesignerFactoryBodyC::GetCPDDesigner(), single parent variable is discrete");
          return CPDDesignerContinuousDiscrete1C::GetInstance();
        }
      }
      else  {
      }
    }
    else {
      // the variable is discrete
    }
    throw ExceptionC("CPDDesignerFactoryBodyC::GetCPDDesigner(), no suitable designer found!");
    return CPDDesignerC(); // no valid designer!
  }

  CPDDesignerFactoryC CPDDesignerFactoryC::m_instance;

  CPDDesignerFactoryC CPDDesignerFactoryC::GetInstance() {
    if (!m_instance.IsValid())
      m_instance = CPDDesignerFactoryC(true);
    return m_instance;
  }

}
