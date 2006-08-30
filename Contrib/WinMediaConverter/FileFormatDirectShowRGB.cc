// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include "Ravl/Image/FileFormatDirectShowRGB.hh"


namespace RavlImageN 
{

  const type_info& FileFormatDirectShowRGBBody::ProbeLoad(const StringC & filename,IStreamC& notUsed,const type_info & obj_type) const
  {
    WindowsMediaConverterBodyC tempMediaConverter(filename);
    if(tempMediaConverter.IsInitialised())
    {
      return typeid(ImageC<ByteRGBValueC>);
    }
    else
    {
      return typeid(void);
    }
    return typeid(void);
  };
  
  DPIPortBaseC FileFormatDirectShowRGBBody::CreateInput(const StringC & filename,const type_info & obj_type) const
  {
    if(obj_type == typeid(ImageC<ByteRGBValueC>))
    {
      return WindowsMediaConverterC(filename);
    }
    else
    {
      return DPIPortBaseC();
    }
  }

  DPIPortBaseC FileFormatDirectShowRGBBody::CreateInput(IStreamC &,const type_info &) const
  {
    return DPIPortBaseC(); 
  }

  char* ForceDirectShowLibraryLink()
  {
    char* strMsg = "ForceDirectShowLibraryLink\n";
    return strMsg;
  }

  static FileFormatDirectShowRGB sDirectShowFormat;
}