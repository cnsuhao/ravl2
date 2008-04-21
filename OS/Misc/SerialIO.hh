// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SERIALIO_HEADER
#define RAVL_SERIALIO_HEADER 1
/////////////////////////////////////////////////////////////
//! userlevel=Normal
//! date="31/12/1999"
//! author="Fangxiang Cheng"
//! docentry="Ravl.API.OS.Hardware"
//! rcsid="$Id$"
//! lib=RavlOS
//! file="Ravl/OS/Misc/SerialIO.hh"

#include "Ravl/Stream.hh"
#if RAVL_OS_WIN32
#include "Ravl/OS/WinStreamIO.hh"
#else
#include "Ravl/OS/UnixStreamIO.hh"
#endif

struct termios ;

namespace RavlN {
  
  //! userlevel=Normal
  //: Class to control unix serial ports.

  class SerialCtrlC :
#if RAVL_OS_WIN32
    public WinStreamIOC
#else
    public UnixStreamIOC
#endif
  {
  public:


    SerialCtrlC();
    //: defualt constructor;
    
    SerialCtrlC(const char *dev, const char * perm = "RDRW",bool nonBlocking = true);
    //: open a device for initialize;
    
    bool Open(const char *dev, const char * perm = "RDRW",bool nonBlocking = true);
    //: Open device.
	
    enum ParityT { 
      SERIAL_PARITY_ODD = 0,
      SERIAL_PARITY_EVEN = 1,
      SERIAL_PARITY_SET = 2,
      SERIAL_PARITY_NONE = 3, 
#if !RAVL_OS_WIN32
      // These are here for compatilibity with older code, they
      // unfortunatly they conflict with define's under windows.
      PARITY_ODD = 0,
      PARITY_EVEN = 1,
      PARITY_SET = 2,
      PARITY_NONE = 3, 
#endif
    };


    bool Setup(IntT i_speed = 9600,
               IntT o_speed = 9600,
               IntT stop_bit = 1,
               ParityT par = SERIAL_PARITY_NONE,
               IntT char_size = 8);
    //: Setup the port.
    // with the given parameters: Input speed, Output speed,
    // stop bit(1,2), parity(exist or not exist), parity type(odd or even) and charactoe size(5,6,7,8)

    bool SetISpeed(const IntT i_speed);
    //: set the input speed of the port;

    bool SetOSpeed(const IntT o_speed);
    //: set the output speed of the port;

    bool SetStopBits(const IntT stop_bit);
    //: set the number of stop bits : 1 or 2;

    bool SetCharSize(const IntT char_size);
    //: set the character size: 5,6,7,8;

    bool SetParity(ParityT par);
    //: parity type: Odd or Even or None or 1
    
    bool IsOpen() const {
#if RAVL_OS_WIN32
      return WinStreamIOC::IsOpen();
#else
      return UnixStreamIOC::IsOpen();
#endif
    }
    //: Is stream open ?
    
  protected:
#if RAVL_HAVE_INTFILEDESCRIPTORS 
    bool SerialInit(IntT fd,
                    IntT i_speed = 9600,
                    IntT o_speed = 9600,
                    IntT stop_bit = 1,
                    ParityT par = SERIAL_PARITY_NONE,
                    IntT char_size = 8);
    //: Initialize the port.
    // with the given parameters: Input speed, Output speed,
    // stop bit(1,2), parity(exist or not exist), parity type(odd or even) and charactoe size(5,6,7,8)
#endif

    static int SpeedSetting(int bitrate);
    //: Get setting to use for a bit rate.
    // returns -1 for illegal values.

    bool SetISpeed(termios &pb,IntT bitrate);
    //: Set input bit rate.

    bool SetOSpeed(termios &pb,IntT bitrate);
    //: Set ouput bit rate.

    bool SetCharSize(termios &pb,IntT bits);
    //: Set bit rate.

    bool SetStopBits(termios &pb,IntT bits);
    //: Set bit rate.

    bool SetParity(termios &pb,ParityT par);
    //: parity type: Odd or Even or None or 1

  };

  //////////////////////////////////////////////////////////////////////////////////////////

  //! userlevel=Normal
  //: Output serial stream.

  class OSerialC
    : public OStreamC,
      public SerialCtrlC
  {
  public:
    OSerialC()
    {}
    //: Default constructor.
    // Creates an invalid handle.

    OSerialC(const char *dev, bool buffered = false);
    //: Open a output serial stream.
    
    bool IsOpen() const
    { return SerialCtrlC::IsOpen(); }
    //: Test if the stream is open.
  };


  //! userlevel=Normal
  //: Input serial stream.

  class ISerialC
    : public IStreamC,
      public SerialCtrlC
  {
  public:
    ISerialC()
    {}
    //:Default constructor.
    // Creates an invalid handle.

    ISerialC (const char *dev, bool buffered = false);
    //: Open an input serial stream.

    bool IsOpen() const
    { return SerialCtrlC::IsOpen(); }
    //: Test if the stream is open.
  };

  //! userlevel=Normal
  //: Input/Output serial stream.

  class IOSerialC
    : public IStreamC,
      public OStreamC,
      public SerialCtrlC
  {
  public:
    IOSerialC()
    {}
    //:Default constructor.
    // Creates an invalid handle.

    IOSerialC (const char *dev, bool buffered = false);
    //: Open an input serial stream.

    bool good()
    { return IStreamC::good() && OStreamC::good(); }
    //: Test if stream is good

    bool operator!()
    { return IStreamC::operator!() || OStreamC::operator!(); }
    //: Test if stream is bad.

    bool Close();
    //: Close the stream.
    
    bool IsOpen() const
    { return SerialCtrlC::IsOpen(); }
    //: Test if the stream is open.
  };
}

#endif
