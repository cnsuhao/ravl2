// This file is part of OmniSoft, Pattern recognition software
// Copyright (C) 2003, Omniperception Ltd.
// file-header-ends-here
#ifndef RAVLN_CPUID_HEADER
#define RAVLN_CPUID_HEADER 1
//! rcsid="$Id$"
//! lib=
//! docentry="Ravl"
//! file="Ravl/Core"
//! author="Kieron J Messer"
 
#include "Ravl/config.h"

#define CHECK_FOR_3DNOW 0

namespace RavlN {
  
  class CPUIDC {
    
  public:
    CPUIDC();
    //: Construct

    bool mmx()
      { return m_mmx; }
    //: do we have mmx

    bool sse()
      { return m_sse; }
    //: do we have sse

    bool sse2()
      { return m_sse2; }
    //: do we have sse2

    bool htt()
      { return m_htt; }
    //: do we have hyperthreading processor 

#if CHECK_FOR_3DNOW
    bool ThreeDNow()
      { return m_3dnow; }
    //: do we have 3d now

    bool ThreeDNowExt()
      { return m_3dnow_p; }
    //: do we have 3d now with extensions
#endif

    void Info() const;
    //: Print info about processor out


  protected:
    bool m_mmx;
    //: do we have mmx

    bool m_sse;
    //: do we have sse

    bool m_sse2;
    //: do we have sse2

    bool m_htt;
    //: do we have hyper threading

#if CHECK_FOR_3DNOW
    bool m_3dnow;
    //: do we have 3d now

    bool m_3dnow_p;
    //: do we have 3d now extensions
#endif
  };
}


#endif
