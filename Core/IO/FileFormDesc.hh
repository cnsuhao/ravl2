// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLFILEFORMATDESC_HEADER
#define RAVLFILEFORMATDESC_HEADER 1
//////////////////////////////////////////////////
//! docentry="Ravl.Core.IO.Formats" 
//! lib=RavlIO
//! author="Charles Galambos"
//! date="13/08/98"
//! rcsid="$Id$"
//! file="Ravl/Core/IO/FileFormDesc.hh"
//! userlevel=Default

#include "Ravl/DList.hh"
#include "Ravl/DP/FileFormat.hh"
#include "Ravl/DP/DataConv.hh"
#include "Ravl/DP/Converter.hh"

namespace RavlN {
  ///////////////////////////////////
  //! userlevel=Advanced
  //: File Format descriptor.
  // Small object.
  
  class FileFormatDescC {
public:
    FileFormatDescC()
      : stype(&typeid(void))
    {}
    //: Default constructor.
    
    FileFormatDescC(FileFormatBaseC nform,DListC<DPConverterBaseC> nconv,const type_info &ntype,bool nisInput)
      : form(nform),
      conv(nconv),
      stype(&ntype),
      isInput(nisInput)
      {}
    //: Constructor.
    
    const FileFormatBaseC &Format() const { return form; }
    //: File format.
    
    const DListC<DPConverterBaseC> &Conversion() const { return conv; }
    //: Required type conversion.
    
    const type_info &SourceType() const { return *stype; }
    //: Type to request in load.
    
    bool IsInput() const { return isInput; }
    //: Is an input descriptor ?
  
    DPIPortBaseC CreateInput(StringC filename) const;
    //: Create an input from the descriptor.
    
    DPOPortBaseC CreateOutput(StringC filename) const;
    //: Create an input from the descriptor.
    
    DPIPortBaseC BuildInputConv(const DPIPortBaseC &ip) const;
    //: Build input conversion.
    
    DPOPortBaseC BuildOutputConv(const DPOPortBaseC &op) const;
    //: Build output conversion.
    
    void DumpConv(ostream &out) const;
    //: Dump conversion to out.
    
  protected:
    FileFormatBaseC form;
    DListC<DPConverterBaseC> conv;
    const type_info *stype;
    bool isInput;
  };
  
}
#endif
