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
#include <stdlib.h>
#include <stdio.h>

namespace RavlN {

  TimeCodeC::TimeCodeC(ByteT hr, ByteT min, ByteT sec, ByteT fr,RealT nFrameRate) 
    : frameRate(nFrameRate)
  { ConvertFrom(bcd(hr),bcd(min),bcd(sec),bcd(fr));  }
  
  TimeCodeC::TimeCodeC(ByteT *in,RealT nFrameRate)     
    : frameRate(nFrameRate)
  { ConvertFrom(bcd(in[3]),bcd(in[2]),bcd(in[1]),bcd(in[0])); }
  
  TimeCodeC::TimeCodeC(int hour, int min, int sec, int frame,RealT nFrameRate) 
    : frameRate(nFrameRate)
  { ConvertFrom(hour,min,sec,frame); }
  
  TimeCodeC::TimeCodeC(const long int frameNum,RealT nFrameRate) 
    : frameRate(nFrameRate)
  { m_liFrame = frameNum; }
  
  TimeCodeC::TimeCodeC(const char * p,RealT nFrameRate) 
    : frameRate(nFrameRate)
  {
    //TODO: put some checks in to verify it is a valid timecode
    long int hour, sec, min, frame;
    
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
  
  bool TimeCodeC::ConvertTo(int &hour, int &minute, int &second, int &frame) const {
    ldiv_t hr = ldiv(m_liFrame,(long int) (frameRate * 3600.0) );
    hour = (int)hr.quot;
    ldiv_t mn = ldiv(hr.rem, (long int) (frameRate * 60.0));
    minute = (int)mn.quot;
    ldiv_t sc = ldiv(mn.rem, (long int) frameRate);
    second = (int)sc.quot;
    frame = (int)sc.rem;
    return true;
  }
  
  //: Convert from hours, minutes, seconds, frame.
  
  bool TimeCodeC::ConvertFrom(int hr,int min,int sec,int fr) {
    m_liFrame = (long int) (hr * (frameRate * 3600.0));
    m_liFrame +=(long int) (min * (frameRate * 60.0));
    m_liFrame +=(long int) (sec * frameRate);
    m_liFrame +=(long int) fr;
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
    long int newFrameCount = m_liFrame + in.m_liFrame;
    return TimeCodeC(newFrameCount);
  }
  
  TimeCodeC TimeCodeC::operator-(const TimeCodeC & in) const {
    long int newFrameCount = m_liFrame - in.m_liFrame;
    return TimeCodeC(newFrameCount);
  }

  TimeCodeC &TimeCodeC::operator+=(const TimeCodeC & in) {
    m_liFrame += in.m_liFrame;
    return *this;
  }

  TimeCodeC &TimeCodeC::operator+=(long int in) {
    m_liFrame += in;
    return *this;
  }


  TimeCodeC &TimeCodeC::operator-=(const TimeCodeC & in) {
    m_liFrame -= in.m_liFrame;
    return *this;
  }

  int TimeCodeC::NumberOfFramesTo(const TimeCodeC & tc_In) {
    return Abs(m_liFrame - tc_In.m_liFrame);
  }
  
  bool TimeCodeC::IsValid() {
    ldiv_t hr = ldiv(m_liFrame, (long int)(frameRate * 3600.0) );
    int hour = (int)hr.quot;
  
    ldiv_t mn = ldiv(hr.rem, (long int) (frameRate * 60.0));
    int minute = (int)mn.quot;
  
    ldiv_t sc = ldiv(mn.rem, (long int) frameRate);
    int second = (int)sc.quot;
    
    int frame = (int)sc.rem;
    
    bool valid = true;
    if((hour<0)||(hour>23)) valid = false;
    else if((minute<0)||(minute>59)) valid = false;
    else if((second<0)||(second>59)) valid = false;
    if((frame<0)||(frame>24)) valid = false;
    return valid;
  }
  
  StringC TimeCodeC::ToText() const {
    int hour,minute,second,frame;
    ConvertTo(hour,minute,second,frame);
    char buff[16];
    sprintf(buff, "%.2d:%.2d:%.2d:%.2d", hour, minute, second, frame);
    return StringC(buff);
  }
  
  ostream &operator<<(ostream &s, const TimeCodeC &out) {
    s << out.ToText();
    return s;
  }

  istream &operator>>(istream &s, TimeCodeC &tc) {
    //cerr << "operator>>(istream &s, TimeCodeC &tc): not implemented" << endl;
    RavlAlwaysAssertMsg(0, "not implemented");
    return s;
  }


} // end namespace RavlN
