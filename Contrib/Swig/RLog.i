// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2010, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html

%include "Ravl/Swig/Types.i"
%include "Ravl/Swig/String.i"

%{
#include "Ravl/RLog.hh"
%}

namespace RavlN
{

  bool RLogInit(bool verbose = false);

  bool RLogInit(const StringC& filename, const StringC& verbose, const StringC& logLevel);

  bool RLogSubscribe(const char* moduleName, const char* path = "", rlog::LogLevel level = rlog::Log_Undef);

}
