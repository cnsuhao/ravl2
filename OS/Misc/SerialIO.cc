// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlOS
//! file="Ravl/OS/Misc/SerialIO.cc"

#include  "Ravl/OS/SerialIO.hh"

#if RAVL_OS_SOLARIS
#include <sys/open.h>
#endif

#if RAVL_HAVE_UNISTD_H
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif

#if RAVL_HAVE_TERMIOS
#include <sys/termios.h>
#endif

#include <ctype.h>
#include <stdio.h>
#include <string.h>

namespace RavlN {
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using namespace RavlN;
#endif
  
  //: Get setting to use for a bit rate.
  // returns -1 for illegal values.
  
  int SerialCtrlC::SpeedSetting(int bitrate) {
    int speedVal = -1;
#if RAVL_HAVE_TERMIOS
    switch(bitrate)
      {
      case 0:  speedVal = B0; break;
      case 50: speedVal = B50; break;
      case 75: speedVal = B75; break;
      case 110: speedVal = B110; break;
      case 134: speedVal = B134; break;
      case 150: speedVal = B150; break;
      case 200: speedVal = B200; break;
      case 300: speedVal = B300; break;
      case 600: speedVal = B600; break;
      case 1200: speedVal = B1200; break;
      case 1800: speedVal = B1800; break;
      case 2400: speedVal = B2400; break;
      case 4800: speedVal = B4800; break;
      case 9600: speedVal = B9600; break;
      case 19200: speedVal = B19200; break;
      case 38400: speedVal = B38400; break;
#ifdef B57600
      case 57600: speedVal = B57600; break;
#endif
#ifdef B115200
      case 115200: speedVal = B115200; break;
#endif
#ifdef B153600
      case 153600: speedVal = B153600; break;
#endif
#ifdef B230400
      case 230400: speedVal = B230400; break;
#endif
#ifdef B307200
      case 307200: speedVal = B307200; break;
#endif
#ifdef B460800
      case 460800: speedVal = B460800; break;
#endif
      }
#endif
    return speedVal;
  }
  
  SerialCtrlC::SerialCtrlC()
    : fid(-1)
  {}
  

  SerialCtrlC::SerialCtrlC(const char *dev, const char * perm) {
#if RAVL_HAVE_TERMIOS
#ifndef O_NDELAY
    int openFlags = O_NONBLOCK | O_NOCTTY;
#else
    int openFlags = O_NONBLOCK | O_NDELAY | O_NOCTTY;    
#endif
    if(strcmp(perm, "RDONLY")==0) 
      openFlags |= O_RDONLY;
    else if ( strcmp(perm, "WRONLY")==0)
      openFlags |=  O_WRONLY;
    else if(strcmp(perm,"RDWR")==0) 
      openFlags |=  O_RDWR;
    else {
      cerr<<"SerialCtrlC::SerialCtrlC(), ERROR: Unknown permission '" << perm << "' should be one of 'RDONLY', 'WRONLY' or 'RDWR'. "<<endl;
      openFlags |=  O_RDWR;
    }
    fid = open(dev,openFlags); 
    
    if (fid<0) { 
      cout << "ERROR: Failed to open serial port '" << dev << "' "<<endl;
    }
#else
    cerr << "WARNING: Control of serial ports is not currently supported on this platform. ";
#endif
  }
  
  //: Set input bit rate.
  
  inline
  bool SerialCtrlC::SetISpeed(termios &pb,IntT bitrate) { 
#if RAVL_HAVE_TERMIOS
    return cfsetispeed(&pb, SpeedSetting(bitrate)) >= 0; 
#else
    return false;
#endif
}
  
  //: Set ouput bit rate.
  
  inline 
  bool SerialCtrlC::SetOSpeed(termios &pb,IntT bitrate) { 
#if RAVL_HAVE_TERMIOS
    return cfsetospeed(&pb, SpeedSetting(bitrate)) >= 0; 
#else
    return false;
#endif
  }
  
  //: Set bit rate.
  
  bool SerialCtrlC::SetCharSize(termios &pb,IntT bits) {  
#if RAVL_HAVE_TERMIOS
    pb.c_cflag &= ~(CSIZE);
    switch(bits)
      {
      case 5: pb.c_cflag |= CS5; break;
      case 6: pb.c_cflag |= CS6; break;
      case 7: pb.c_cflag |= CS7; break;
      case 8: pb.c_cflag |= CS8; break;
      default:
	cerr << "SerialCtrlC::SetCharSize(), WARNING: Unsupported char size " << bits << ", Using 8 bit.\n";
	pb.c_cflag |= CS8;
	return false;
      }
    return true;
#else
    return false;
#endif
  }
  
  //: Set number of stop bits.
  
  bool SerialCtrlC::SetStopBits(termios &pb,IntT bits) {
#if RAVL_HAVE_TERMIOS
    switch(bits)
      {
      case 1: pb.c_cflag &= ~(CSTOPB); break;
      case 2: pb.c_cflag |= CSTOPB; break;
      default:
	cerr<<"SerialCtrlC::SetStopBits(), ERROR: Illegal stopbit input " << bits << "\n";
	return false;
      }
    return true;
#else
    return false;
#endif
  }
  
  //: parity type: Odd or Even or None or 1
  
  bool SerialCtrlC::SetParity(termios &pb,ParityT parity_type) {
#if RAVL_HAVE_TERMIOS
    switch(parity_type)
      {
      case PARITY_ODD:
	pb.c_cflag |=(PARODD|PARENB); 
	pb.c_iflag |= INPCK;
	break;
      case PARITY_EVEN:
	pb.c_cflag |=(PARENB); 
	pb.c_cflag &= ~(PARODD); 
	pb.c_iflag |= INPCK;
	break;
      case PARITY_SET:
	pb.c_cflag &=~(PARENB); 
	pb.c_iflag &= ~(INPCK);
	break;
      case PARITY_NONE:
	pb.c_cflag &=~(PARENB); 
	pb.c_iflag &= ~(INPCK);
	break;
      } 
    return true;
#else
    return false;
#endif
  }
  
  //: Setup the port.
  // with the given parameters: Input speed, Output speed, 
  // stop bit(1,2), parity(exist or not exist), parity type(odd or even) and charactoe size(5,6,7,8)
  
  bool SerialCtrlC::Setup(IntT i_speed, 
			  IntT o_speed, 
			  IntT stop_bits,
			  ParityT par,  
			  IntT char_size)
    
  {
#if RAVL_HAVE_TERMIOS
    if (fid < 0) {
      cerr << "SerialCtrlC::Setup(), No file descriptor for port, can't configure. \n";
      return false;
    }
    termios termios_p;
    if (tcgetattr(fid,&termios_p) < 0) { 
      cerr << "SerialCtrlC::Setup(), Failed to read port paramiters. \n";
      return false;
    }
    
    termios_p.c_iflag = IGNBRK;
    termios_p.c_oflag = 0;
    termios_p.c_cflag = CLOCAL | CREAD;
    termios_p.c_lflag = 0;
    termios_p.c_cc[VMIN] = 1;
    termios_p.c_cc[VTIME] = 0;
  
    bool ok = true;
    
    ok &= SetISpeed(termios_p,i_speed);
    ok &= SetOSpeed(termios_p,o_speed);
    ok &= SetCharSize(termios_p,char_size);
    ok &= SetStopBits(termios_p,stop_bits);
    ok &= SetParity(termios_p,par);
    // Bit of a cheat, should give better diagnositics.
    if(!ok) {
      cerr << "SerialCtrlC::Init(), Invalid paramiter. \n";
      return false;
    }
    
    //tcflush(fid, TCSAFLUSH);
    
    if (tcsetattr( fid, TCSANOW, &termios_p ) < 0)  {
      cerr << "SerialCtrlC::Init(), Failed to configure serial port \n";
      return false;
    }
    return true;  
#else
    return false;
#endif
  }
  
  bool SerialCtrlC::SerialInit(IntT fd,IntT i_speed,IntT o_speed,IntT stop_bits,ParityT par,IntT char_size) {
    fid = fd;
    return Setup(i_speed,o_speed,stop_bits,par,char_size);
  }
  
  bool SerialCtrlC::SetISpeed(const IntT i_speed) {
#if RAVL_HAVE_TERMIOS
    termios pb;
    if (tcgetattr(fid,&pb) < 0) { 
      cerr << "SerialCtrlC::SetISpeed(), Failed to read port paramiters. \n";
      return false;
    }
    if(!SetISpeed(pb,i_speed))
      return false;
    return tcsetattr( fid, TCSANOW, &pb ) >= 0;
#else
    return false;
#endif
  }
  
  bool SerialCtrlC::SetOSpeed(const IntT o_speed) {
#if RAVL_HAVE_TERMIOS
    termios pb;
    if (tcgetattr(fid,&pb) < 0) { 
      cerr << "SerialCtrlC::SetOSpeed(), Failed to read port paramiters. \n";
      return false;
    }
    if(!SetOSpeed(pb,o_speed))
      return false;
    return tcsetattr( fid, TCSANOW, &pb ) >= 0;
#else
    return false;
#endif
  }

  
  bool SerialCtrlC::SetStopBits(const IntT stop_bit) {  
#if RAVL_HAVE_TERMIOS
    termios pb;
    if (tcgetattr(fid,&pb) < 0) { 
      cerr << "SerialCtrlC::SetStopBits(), Failed to read port paramiters. \n";
      return false;
    }
    if(!SetStopBits(pb,stop_bit))
      return false;
    return tcsetattr( fid, TCSANOW, &pb ) >= 0;
#else
    return false;
#endif
  }
  
  
  bool SerialCtrlC::SetCharSize(const IntT char_size) {
#if RAVL_HAVE_TERMIOS
    termios pb;
    if (tcgetattr(fid,&pb) < 0) { 
      cerr << "SerialCtrlC::SetCharSize(), Failed to read port paramiters. \n";
      return false;
    }
    if(!SetCharSize(pb,char_size))
      return false;
    return tcsetattr( fid, TCSANOW, &pb ) >= 0;
#else
    return false;
#endif
  }
  
  
  bool SerialCtrlC::SetParity(ParityT parity_type){
#if RAVL_HAVE_TERMIOS
    termios pb;
    if (tcgetattr(fid,&pb) < 0) { 
      cerr << "SerialCtrlC::SetParity(), Failed to read port paramiters. \n";
      return false;
    }
    if(!SetParity(pb,parity_type))
      return false;
    return tcsetattr( fid, TCSANOW, &pb ) >= 0;
#else
    return false;
#endif
  }
  
  IntT SerialCtrlC::Getfd()
  { return fid; }
  
  //////// OSerialC ///////////////////////////////////////////////////////////////

  //: Open a output serial stream.
  
  OSerialC::OSerialC(const char *dev, bool buffered)  {
#if RAVL_HAVE_TERMIOS
    IntT fd = open(dev,O_WRONLY);
    SerialInit(fd);
    ((OStreamC &)(*this)) = OStreamC(fid,true,buffered);
#endif
  }
  
  //////// ISerialC ///////////////////////////////////////////////////////////////
  
  
  //: Open an input serial stream.
  
  ISerialC::ISerialC (const char *dev, bool buffered) {
#if RAVL_HAVE_TERMIOS
    IntT fd = open(dev,O_RDONLY);
    SerialInit(fd);
    ((IStreamC &)(*this)) = IStreamC(fid,true,buffered);  
#endif
  }
  
  //////////////////////////////////////////////////////////
  
  //: Open an input serial stream.
  
  IOSerialC::IOSerialC (const char *dev, bool buffered) {
#if RAVL_HAVE_TERMIOS
    IntT fd = open(dev,O_RDWR);
    SerialInit(fd);
    ((IStreamC &)(*this)) = IStreamC(fid,true,buffered);  
    ((OStreamC &)(*this)) = OStreamC(fid,true,buffered);  
#endif
  }
  
}

