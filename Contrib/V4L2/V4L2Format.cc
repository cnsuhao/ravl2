// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////////
//! rcsid = "$Id$"
//! lib=RavlImgIOV4L2
//! author = "Warren Moore"
//! file="Ravl/Contrib/V4L2/V4L2Format.cc"

#include "Ravl/Image/ByteYUVValue.hh"
#include "Ravl/Image/V4L2Format.hh"
#include "Ravl/Image/ImgIOV4L2.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/Image/RealRGBValue.hh"

#define DPDEBUG 0
#if DPDEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN
{
  
  const static StringC g_defaultDevice("/dev/video0");
  //: Default V4L2 device
  
  const static IntT g_defaultChannel(0);
  //: Default V4L2 channel
  
  void InitV4L2Format()
  {}
  
  
  
  FileFormatV4L2BodyC::FileFormatV4L2BodyC() :
    FileFormatBodyC("v4l2", "V4L2 input (@V4L2)")
  {}
  
  
  
  const type_info &FileFormatV4L2BodyC::ProbeLoad(IStreamC &in, const type_info &obj_type) const
  {
    ONDEBUG(cerr << "FileFormatV4L2BodyC::ProbeLoad not a V4L2 input" << endl;)
    return typeid(void); 
  }
  
  
  
  const type_info &FileFormatV4L2BodyC::ProbeLoad(const StringC &filename, IStreamC &in, const type_info &obj_type) const
  {
    ONDEBUG(cerr << "FileFormatV4L2BodyC::ProbeLoad filename(" << filename << ") type(" << obj_type.name() << ")" << endl;)

    // Get the parameters
    StringC device;
    IntT channel;
    if (!FindParams(filename, device, channel))
      return typeid(void);
    ONDEBUG(cerr << "FileFormatV4L2BodyC::ProbeLoad device(" << device << ") channel(" << channel << ")" << endl;)

    // Create the V4L2 object (will not be open after construction if not supported)
    ImgIOV4L2BaseC v4l2(device, channel, obj_type);
    ONDEBUG(cerr << "FileFormatV4L2BodyC::ProbeLoad format supported(" << (v4l2.IsOpen() ? "Y" : "N") << ")" << endl);
    
    if (obj_type == typeid(ImageC<ByteYUVValueC>))
      return typeid(ImageC<ByteRGBValueC>);
    
    return (v4l2.IsOpen() ? obj_type : typeid(void));
  }
  
  
  
  const type_info &FileFormatV4L2BodyC::ProbeSave(const StringC &filename, const type_info &obj_type, bool forceFormat ) const
  {
    ONDEBUG(cerr << "FileFormatV4L2BodyC::ProbeSave unsupported" << endl;)
    return typeid(void);   
  }
  
  
  
  DPIPortBaseC FileFormatV4L2BodyC::CreateInput(IStreamC &in, const type_info &obj_type) const
  { 
    ONDEBUG(cerr << "FileFormatV4L2BodyC::CreateInput(OStreamC) unsupported" << endl;)
    return DPIPortBaseC();
  }
  
  
  
  DPOPortBaseC FileFormatV4L2BodyC::CreateOutput(OStreamC &out, const type_info &obj_type) const
  {
    ONDEBUG(cerr << "FileFormatV4L2BodyC::CreateOutput(OStreamC) unsupported" << endl;)
    return DPOPortBaseC();  
  }
  
  
  
  DPIPortBaseC FileFormatV4L2BodyC::CreateInput(const StringC &filename, const type_info &obj_type) const
  {
    ONDEBUG(cerr << "FileFormatV4L2BodyC::CreateInput filename(" << filename << ") type(" << obj_type.name() << ")" << endl;)

    // Get the parameters
    StringC device;
    IntT channel;
    if (!FindParams(filename, device, channel))
      return DPIPortBaseC();
    ONDEBUG(cerr << "FileFormatV4L2BodyC::CreateInput device(" << device << ") channel(" << channel << ")" << endl;)

    // Create the relevant port
    if (obj_type == typeid(ImageC<ByteRGBValueC>))
      return ImgIOV4L2C<ByteRGBValueC>(device, channel);
    if (obj_type == typeid(ImageC<ByteT>))
      return ImgIOV4L2C<ByteT>(device, channel);

    return DPIPortBaseC();
  }
  
  
  
  DPOPortBaseC FileFormatV4L2BodyC::CreateOutput(const StringC &filename, const type_info &obj_type) const
  {
    ONDEBUG(cerr << "FileFormatV4L2BodyC::CreateOutput(const StringC) unsupported" << endl;)
    return DPOPortBaseC();  
  }
  
  
  
  const type_info &FileFormatV4L2BodyC::DefaultType() const
  { 
    return typeid(ImageC<ByteRGBValueC>); 
  }
  
  
  
  bool FileFormatV4L2BodyC::FindParams(const StringC &filename, StringC &device, IntT &channel) const
  {
    // Look for the device symbol
    if(filename.length() == 0)
      return false;
    if(filename[0] != '@')
      return false;
    
    // Check it's a V4L2 device
    StringC deviceId = ExtractDevice(filename);
    if (deviceId != "V4L2")
      return false;
    
    // Set the defaults
    device = g_defaultDevice;
    channel = g_defaultChannel;

    // Get the device and optional channel
    StringC params = ExtractParams(filename);
    if (params.Size() > 0)
    {
      IntT delim = params.index('#');
      if(delim >= 0)
      {
        device = params.before(delim);
        channel = params.after(delim).IntValue();
      }
      else
        if (params.length() > 0)
          device = params;
    }
    
    return true;
  }
  
  
  
  static FileFormatV4L2C Init;  
}
