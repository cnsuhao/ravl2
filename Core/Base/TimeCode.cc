// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Base/TimeCode.cc"

#include "Ravl/TimeCode.hh"
#include "Ravl/String.hh"
#include "Ravl/BinStream.hh"
#include <stdlib.h>
#include <stdio.h>

namespace RavlN {

  TimeCodeC::TimeCodeC(ByteT hr, ByteT min, ByteT sec, ByteT fr,RealT nFrameRate) 
    : frameRate(nFrameRate)
  { ConvertFrom(bcd(hr),bcd(min),bcd(sec),bcd(fr));  }
  
  TimeCodeC::TimeCodeC(ByteT *in,RealT nFrameRate)     
    : frameRate(nFrameRate)
  { ConvertFrom(bcd(in[3]),bcd(in[2]),bcd(in[1]),bcd(in[0])); }
  
  TimeCodeC::TimeCodeC(IntT hour, IntT min, IntT sec, IntT frame,RealT nFrameRate) 
    : frameRate(nFrameRate)
  { ConvertFrom(hour,min,sec,frame); }
  
  TimeCodeC::TimeCodeC(const IntT frameNum,RealT nFrameRate) 
    : frameRate(nFrameRate)
  { m_liFrame = frameNum; }
  
  TimeCodeC::TimeCodeC(const char * p,RealT nFrameRate) 
    : frameRate(nFrameRate)
  {
    //TODO: put some checks in to verify it is a valid timecode
    IntT hour, sec, min, frame;
    
    if((p[2]!=':') || (p[5]!=':') || (p[8]!=':')) {
      hour = 0xff;
      min = 0xff;
      sec = 0xff;
      frame = 0xff;
    }
    else {
      hour = atoi(&p[0]);
      min = atoi(&p[3]);
      sec = atoi(&p[6]);
      frame = atoi(&p[9]);
    }
    if((hour>23) || (min>59) || (sec>59) || (frame>24)) {
      hour = 0xff;
      min = 0xff;
      sec = 0xff;
      frame = 0xff;
    }
    
    ConvertFrom(hour,min,sec,frame);
  }
  

  //: Convert to hours, minutes, seconds, frame.
  
  bool TimeCodeC::ConvertTo(IntT &hour, IntT &minute, IntT &second, IntT &frame) const {
    ldiv_t hr = ldiv(m_liFrame,(IntT) (frameRate * 3600.0) );
    //hour = Floor( 

    hour = (IntT) hr.quot;
    ldiv_t mn = ldiv(hr.rem, (IntT) (frameRate * 60.0));
    minute = (IntT)mn.quot;
    ldiv_t sc = ldiv(mn.rem, (IntT) frameRate);
    second = (IntT)sc.quot;
    frame = (IntT)sc.rem;
    return true;
  }
  
  //: Convert from hours, minutes, seconds, frame.
  
  bool TimeCodeC::ConvertFrom(IntT hr,IntT min,IntT sec,IntT fr) {
    m_liFrame = (IntT) (hr * (frameRate * 3600.0));
    m_liFrame +=(IntT) (min * (frameRate * 60.0));
    m_liFrame +=(IntT) (sec * frameRate);
    m_liFrame +=(IntT) fr;
    return true;
  }
  
  bool TimeCodeC::operator==(const TimeCodeC &in) const {
    return (m_liFrame == in.m_liFrame);
  }
  
  bool TimeCodeC::operator!=(const TimeCodeC &in) {
    return (m_liFrame != in.m_liFrame);
  }

  bool TimeCodeC::operator<(const TimeCodeC &in) const {
    return (m_liFrame < in.m_liFrame);
  }
  
  bool TimeCodeC::operator>(const TimeCodeC &in) const {
    if(m_liFrame > in.m_liFrame) return true;
    return false;
  }

  bool TimeCodeC::operator<=(const TimeCodeC &in) const {
    if(m_liFrame <= in.m_liFrame) return true;
    return false;
  }

  bool TimeCodeC::operator>=(const TimeCodeC &in) const {
    if(m_liFrame >= in.m_liFrame) return true;
    return false;
  }

  TimeCodeC TimeCodeC::operator+(const TimeCodeC & in) const {
    IntT newFrameCount = m_liFrame + in.m_liFrame;
    return TimeCodeC(newFrameCount);
  }
  
  TimeCodeC TimeCodeC::operator-(const TimeCodeC & in) const {
    IntT newFrameCount = m_liFrame - in.m_liFrame;
    return TimeCodeC(newFrameCount);
  }

  TimeCodeC &TimeCodeC::operator+=(const TimeCodeC & in) {
    m_liFrame += in.m_liFrame;
    return *this;
  }

  TimeCodeC &TimeCodeC::operator+=(IntT in) {
    m_liFrame += in;
    return *this;
  }


  TimeCodeC &TimeCodeC::operator-=(const TimeCodeC & in) {
    m_liFrame -= in.m_liFrame;
    return *this;
  }

  IntT TimeCodeC::NumberOfFramesTo(const TimeCodeC & tc_In) {
    return Abs(m_liFrame - tc_In.m_liFrame);
  }
  
  bool TimeCodeC::IsValid() {
    ldiv_t hr = ldiv(m_liFrame, (IntT) (frameRate * 3600.0) );
    IntT hour = (IntT)hr.quot;
  
    ldiv_t mn = ldiv(hr.rem, (IntT) (frameRate * 60.0));
    IntT minute = (IntT)mn.quot;
  
    ldiv_t sc = ldiv(mn.rem, (IntT) frameRate);
    IntT second = (IntT)sc.quot;
    
    IntT frame = (IntT)sc.rem;
    
    bool valid = true;
    if((hour<0)||(hour>23)) valid = false;
    else if((minute<0)||(minute>59)) valid = false;
    else if((second<0)||(second>59)) valid = false;
    if((frame<0)||(frame>24)) valid = false;
    return valid;
  }
  
  StringC TimeCodeC::ToText() const {
    IntT hour,minute,second,frame;
    ConvertTo(hour,minute,second,frame);
    char buff[16];
    sprintf(buff, "%.2d:%.2d:%.2d:%.2d", hour, minute, second, frame);
    return StringC(buff);
  }

  // I/O operators 

  ostream &operator<<(ostream & s, const TimeCodeC & tc) {
    s << tc.m_liFrame << " " << tc.frameRate ;
    return s;
  }

  istream &operator>>(istream & s, TimeCodeC & tc) {
    s >> tc.m_liFrame >> tc.frameRate ; 
    return s;
  }

  BinOStreamC & operator << (BinOStreamC & s, const TimeCodeC & tc ) {
    s << tc.m_liFrame << tc.frameRate ; 
    return s ; 
  }

  BinIStreamC & operator >> (BinIStreamC & s, TimeCodeC & tc ) {
    s >> tc.m_liFrame >> tc.frameRate ; 
    return s ; 
  }


} // end namespace RavlN
 
