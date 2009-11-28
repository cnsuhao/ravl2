// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2009, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FILEFORMATBYTEFILE_HEADER
#define RAVL_FILEFORMATBYTEFILE_HEADER 1
////////////////////////////////////////////////////////
//! docentry = "Ravl.API.Core.IO.Formats"
//! lib = RavlIO
//! file = "Ravl/Core/IO/FileFormatByteFile.hh"
//! userlevel = Default

#include "Ravl/DP/FileFormat.hh"
#include "Ravl/DP/ByteFileIO.hh"
#include "Ravl/TypeName.hh"

namespace RavlN
{

  /////////////////////////////
  //! userlevel = Develop
  //: Raw binary file format.

  class FileFormatByteFileBodyC
  : public FileFormatBodyC
  {
  public:

    FileFormatByteFileBodyC(bool deletable)
    : FileFormatBodyC("bytefile", "Raw binary file.", deletable)
    {}
    //: Ctor.

    FileFormatByteFileBodyC(const StringC& formatId, const StringC& formatDescriptor, bool deletable = true)
    : FileFormatBodyC(formatId, formatDescriptor, deletable)
    {}
    //: Ctor with full format info.

    virtual const type_info& ProbeLoad(IStreamC& inputStream, const type_info& objType) const
    {
      // Byte only
      if (objType != typeid(ByteT))
        return typeid(void);

      // Input stream must be good
      if (!inputStream.good())
        return typeid(void);

      return typeid(ByteT);
    }

    virtual const type_info& ProbeLoad(const StringC& filename, IStreamC& inputStream, const type_info& objType) const
    {
      // Byte only
      if (objType != typeid(ByteT))
        return typeid(void);

      // No filename, so test input stream
      if (filename.IsEmpty())
        return ProbeLoad(inputStream, objType);

      // Need a real filename
      if (filename[0] == '@')
        return typeid(void);

      return typeid(ByteT);
    }

    virtual const type_info& ProbeSave(const StringC& filename, const type_info& objType, bool forceFormat) const
    {
      // Byte only
      if (objType != typeid(ByteT))
        return typeid(void);

      // Need a filename
      if (filename.IsEmpty())
        return typeid(void);

      // Need a real filename
      if (filename[0] == '@')
        return typeid(void);
      
      return typeid(ByteT);
    }

    virtual DPIPortBaseC CreateInput(IStreamC& inputStream, const type_info& objType) const
    {
      // Byte only
      if (objType != typeid(ByteT))
        return DPIPortBaseC();
      
      return DPIByteFileC(inputStream);
    }
    //: Create an input port for loading.
    //!return: An invalid port if not supported.

    virtual DPOPortBaseC CreateOutput(OStreamC& outputStream, const type_info& objType) const
    {
      // Byte only
      if (objType != typeid(ByteT))
        return DPOPortBaseC();
      
      return DPOByteFileC(outputStream);
    }
    //: Create an output port for saving.
    //!return: An invalid port if not supported.

    DPIPortBaseC CreateInput(const StringC& filename, const type_info& objType) const
    {
      // Byte only
      if (objType != typeid(ByteT))
        return DPIPortBaseC();

      return DPIByteFileC(filename);
    }
    //: Create an input port for loading.
    //!return: An invalid port if not supported.

    DPOPortBaseC CreateOutput(const StringC& filename, const type_info& objType) const
    {
      // Byte only
      if (objType != typeid(ByteT))
        return DPOPortBaseC();
      
      return DPOByteFileC(filename);
    }
    //: Create an output port for saving.
    //!return: An invalid port if not supported.

    virtual const type_info& DefaultType() const
    {
      return typeid(ByteT);
    }
    //: Get preferred data type.

    virtual bool IsStream() const
    {
      return true;
    }
    //: Show it is a streamable format.

    virtual IntT Priority() const
    {
      return -1; // Default is 0.
    }
    //: Find the priority of the format. The higher the better.

  };

  /////////////////////////////
  //! userlevel = Normal
  //: Raw binary file format.

  class FileFormatByteFileC
  : public FileFormatC<ByteT>
  {
  public:

    FileFormatByteFileC()
    : FileFormatC<ByteT>(*new FileFormatByteFileBodyC(true))
    {}
    //: Ctor.

    FileFormatByteFileC(const StringC& formatId, const StringC& formatDescriptor)
    : FileFormatC<ByteT>(*new FileFormatByteFileBodyC(formatId, formatDescriptor))
    {}
    //: Ctor with full format info.

  };

}

#endif
