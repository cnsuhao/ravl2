// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2010, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////////////
//! lib = RavlImgIOQT
//! author = "Charles Galambos"

#include "Ravl/MacOSX/QTFormat.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/Image/ByteYUVValue.hh"
#include "Ravl/Image/ByteYUV422Value.hh"
#include "Ravl/Image/RealRGBValue.hh"
#include "Ravl/MacOSX/QTImageIPort.hh"
#include "Ravl/EntryPnt.hh"

#define DPDEBUG 0
#if DPDEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN
{
  
  FileFormatQTBodyC::FileFormatQTBodyC() :
    FileFormatBodyC("QT", "QT input (@QT)")
  {
    ONDEBUG(std::cerr << "FileFormatQTBodyC Regiester format." << endl;)
  }
  
  const type_info &FileFormatQTBodyC::ProbeLoad(IStreamC &in, const type_info &obj_type) const
  {
    ONDEBUG(std::cerr << "FileFormatQTBodyC::ProbeLoad not a QT input" << endl;)
    return typeid(void); 
  }
  
  
  const type_info &FileFormatQTBodyC::ProbeLoad(const StringC &filename, IStreamC &in, const type_info &obj_type) const
  {
    ONDEBUG(std::cerr << "FileFormatQTBodyC::ProbeLoad filename(" << filename << ") type(" << obj_type.name() << ")" << endl;)

    // Get the parameters
    StringC device;
    IntT buffSize;
    if (!FindParams(filename, device, buffSize))
      return typeid(void);

    if(!RavlN::UsingRavlMain()) {
      std::cerr << "In order to use @QT program must be started with RAVL_ENTRY_POINT, See Ravl/EntryPnt.hh \n";
      return typeid(void);
    }
    ONDEBUG(std::cerr << "FileFormatQTBodyC::ProbeLoad device(" << device << ") buffSize(" << buffSize << ")" << endl);

#if 1
    if (obj_type == typeid(ImageC<ByteYUVValueC>)) {
      //return typeid(ImageC<ByteYUVValueC>); // Doesn't seem to be supported on webcam.
      return typeid(ImageC<ByteYUV422ValueC>);
    }

    if(obj_type == typeid(ImageC<FloatT>) || obj_type == typeid(ImageC<RealT>) || obj_type==typeid(UInt16T) || obj_type == typeid(ImageC<ByteT>)) {
      //return typeid(ImageC<UInt16T>); // This doesn't seem to be supported when using a webcam.
      return typeid(ImageC<ByteYUV422ValueC>);
    }

    if( obj_type == typeid(ImageC<ByteYUV422ValueC>)  )
      return typeid(ImageC<ByteYUV422ValueC>);
#endif

    return typeid(ImageC<ByteRGBValueC>);
  }
  
  const type_info &FileFormatQTBodyC::ProbeSave(const StringC &filename, const type_info &obj_type, bool forceFormat ) const
  {
    ONDEBUG(std::cerr << "FileFormatQTBodyC::ProbeSave unsupported" << endl;)
    return typeid(void);   
  }
  
  DPIPortBaseC FileFormatQTBodyC::CreateInput(IStreamC &in, const type_info &obj_type) const
  { 
    ONDEBUG(std::cerr << "FileFormatQTBodyC::CreateInput(OStreamC) unsupported" << endl;)
    return DPIPortBaseC();
  }
  
  DPOPortBaseC FileFormatQTBodyC::CreateOutput(OStreamC &out, const type_info &obj_type) const
  {
    ONDEBUG(std::cerr << "FileFormatQTBodyC::CreateOutput(OStreamC) unsupported" << endl;)
    return DPOPortBaseC();  
  }
  
  DPIPortBaseC FileFormatQTBodyC::CreateInput(const StringC &filename, const type_info &obj_type) const
  {
    ONDEBUG(std::cerr << "FileFormatQTBodyC::CreateInput filename(" << filename << ") type(" << obj_type.name() << ")" << endl;)

    // Get the parameters
    StringC device;
    IntT bufferSize;
    if (!FindParams(filename, device, bufferSize))
      return DPIPortBaseC();
    ONDEBUG(std::cerr << "FileFormatQTBodyC::CreateInput device(" << device << ") bufferSize(" << bufferSize << ")" << endl);

    if (obj_type == typeid(ImageC<ByteRGBValueC>))
      return DPIPortQTImageC<ByteRGBValueC>(device,bufferSize);

    if (obj_type == typeid(ImageC<UInt16T>))
      return DPIPortQTImageC<UInt16T>(device,bufferSize);
    
    if (obj_type == typeid(ImageC<ByteYUV422ValueC>))
      return DPIPortQTImageC<ByteYUV422ValueC>(device,bufferSize);

    if (obj_type == typeid(ImageC<ByteYUVValueC>))
      return DPIPortQTImageC<ByteYUVValueC>(device,bufferSize);

    return DPIPortBaseC();
  }
  
  
  
  DPOPortBaseC FileFormatQTBodyC::CreateOutput(const StringC &filename, const type_info &obj_type) const
  {
    ONDEBUG(std::cerr << "FileFormatQTBodyC::CreateOutput(const StringC) unsupported" << endl;)
    return DPOPortBaseC();  
  }
  
  
  
  const type_info &FileFormatQTBodyC::DefaultType() const
  { 
    return typeid(ImageC<ByteRGBValueC>); 
  }
  
  
  
  bool FileFormatQTBodyC::FindParams(const StringC &filename, StringC &device, IntT &buffSize) const
  {
    // Look for the device symbol
    if(filename.length() == 0)
      return false;
    if(filename[0] != '@')
      return false;
    
    // Check it's a QT device
    StringC deviceId = ExtractDevice(filename);
    if (deviceId != "QT")
      return false;
    
    // Set the defaults
    device = "";
    buffSize = 2;

    // Get the device and optional buffSize
    StringC params = ExtractParams(filename);
    if (params.Size() > 0)
    {
      IntT delim = params.index('#');
      if(delim >= 0)
      {
        device = params.before(delim);
        buffSize = params.after(delim).IntValue();
      }
      else
        if (params.length() > 0)
          device = params;
    }
    
    return true;
  }
  
  void LinkQTCaptureFormat() {

  }
  
  static FileFormatQTC Init;
}
