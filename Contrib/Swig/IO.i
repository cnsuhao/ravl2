// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html


%include "Ravl/Swig/String.i"

%{
#include "Ravl/IO.hh"
#include "Ravl/DP/PrintIOInfo.hh"
#include "Ravl/Stream.hh"

%}

namespace std {
  class ostream;
}

namespace RavlN {
  using namespace std;
  
  void PrintIOFormats(ostream &os = std::cout);
  //: Print in human readable format, information about available formats to 'os'.
  
  void PrintIOConversions(ostream &os = std::cout);
  //: Print in human readable format, information about available type conversions to 'os'.
  
  void PrintIOClassTypes(ostream &os = std::cout);
  //: Print in human readable format, information about available class types to 'os'.
  
}
