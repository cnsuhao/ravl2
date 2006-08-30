// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here


#ifndef FILEFORMATDIRECTSHOW_H
#define FILEFORMATDIRECTSHOW_H

#include "Ravl/DP/FileFormat.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/WindowsMediaConverter.hh"

namespace RavlImageN 
{
  class FileFormatDirectShowRGBBody : public FileFormatBodyC
  {
  public:
    FileFormatDirectShowRGBBody(void) {}; //Default constructor
    ~FileFormatDirectShowRGBBody(void) {};  //Destructor

  private:
    FileFormatDirectShowRGBBody(const FileFormatDirectShowRGBBody& rhs) {}; //Private copy constructor
  public:

    //Probe load, the input parameter obj_type is not used
    virtual const type_info & ProbeLoad(const StringC & filename,IStreamC& notUsed, const type_info & obj_type) const;

    //Create input, The input parameter obj_type is not used
    virtual DPIPortBaseC CreateInput(const StringC & filename,const type_info & obj_type) const;
    //Create input
    virtual DPIPortBaseC CreateInput(IStreamC &,const type_info &) const;
  };



  class FileFormatDirectShowRGB : public FileFormatC<ImageC<ByteRGBValueC> >
  {
  public:
    FileFormatDirectShowRGB(void)
      : FileFormatC<ImageC<ByteRGBValueC> >(*new FileFormatDirectShowRGBBody()) {}; //Default constructor
    ~FileFormatDirectShowRGB(void) {};  //Destructor
  private:
    FileFormatDirectShowRGB(const FileFormatDirectShowRGB& rhs) {}; //Private copy constructor
    
  };
}

#endif //FILEFORMATDIRECTSHOW_H