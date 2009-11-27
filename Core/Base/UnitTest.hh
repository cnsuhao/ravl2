// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2009, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_UNITTEST_HEADER
#define RAVL_UNITTEST_HEADER 1
/////////////////////////////////////////////////////////////////////////
//! docentry="Ravl.API.Core"
//! file="Ravl/Core/Base/UnitTest.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Charles Galambos"

#include "Ravl/BinStream.hh"
#include "Ravl/StrStream.hh"

// Helper functions for unit testing RAVL code.
namespace RavlN {

  //! Test binary IO.
  // Its up to the implementer to check the reloaded
  // value is equal to the original input.
  // Returns true if stream is synchronised on output.

  template<typename DataT>
  bool TestBinStreamIO(const DataT &input,DataT &reloaded) {
    // Write data out.
    StringC strmData;
    UIntT checkValue = 0x12345678;
    {
      StrOStreamC ostrm;
      BinOStreamC bos(ostrm);
      bos << input << checkValue;
      strmData = ostrm.String();
    }

    // Read data in.
    {
      StrIStreamC strm(strmData);
      BinIStreamC bis(strm);
      UIntT loadedCheckValue = 0;
      bis >> reloaded >> loadedCheckValue;

      // Check the stream length matches.
      if(loadedCheckValue != checkValue) return false;
    }

    return true;
  }
}

#endif
