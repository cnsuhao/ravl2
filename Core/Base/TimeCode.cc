// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore

#include "Ravl/TimeCode.hh"
#include "Ravl/String.hh"
#include <stdlib.h>
#include <stdio.h>

namespace RavlN {

  TimeCodeC::TimeCodeC(ByteT hr, ByteT min, ByteT sec, ByteT fr) {
    m_liFrame = bcd(hr) * 90000;
    m_liFrame += bcd(min) * 1500;
    m_liFrame += bcd(sec) * 25;
    m_liFrame += bcd(fr);
  }
  
  TimeCodeC::TimeCodeC(ByteT *in) {
    m_liFrame = bcd(in[3]) * 90000;
    m_liFrame += bcd(in[2]) * 1500;
    m_liFrame += bcd(in[1]) * 25;
    m_liFrame += bcd(in[0]);
  }


  TimeCodeC::TimeCodeC(int hr, int min, int sec, int fr) {
    m_liFrame = hr * 90000;
    m_liFrame += min * 1500;
    m_liFrame += sec * 25;
    m_liFrame += fr;
  }


  TimeCodeC::TimeCodeC(const long int frameNum) {
    m_liFrame = frameNum;
  }
  

  TimeCodeC::TimeCodeC(const char * p) {
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
  
    if((hour>3) || (min>59) || (sec>59) || (frame>24)) {
      hour = 0xff;
      min = 0xff;
      sec = 0xff;
      frame = 0xff;
    }
  
    m_liFrame = hour*90000;
    m_liFrame += min * 1500;
    m_liFrame += sec * 25;
    m_liFrame += frame;
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
    TimeCodeC res(newFrameCount);
    return res;
  }
  
  TimeCodeC TimeCodeC::operator-(const TimeCodeC & in) const {
    long int newFrameCount = m_liFrame - in.m_liFrame;
    TimeCodeC res(newFrameCount);
    return res;
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
    ldiv_t hr = ldiv(m_liFrame, 90000);
    int hour = (int)hr.quot;
  
    ldiv_t mn = ldiv(hr.rem, 1500);
    int minute = (int)mn.quot;
  
    ldiv_t sc = ldiv(mn.rem, 25);
    int second = (int)sc.quot;
  
    int frame = (int)sc.rem;
    
    bool valid = true;
    if((hour<0)||(hour>3)) valid = false;
    else if((minute<0)||(minute>59)) valid = false;
    else if((second<0)||(second>59)) valid = false;
    if((frame<0)||(frame>24)) valid = false;
    return valid;
  }
  
  StringC TimeCodeC::ToText() const {
    ldiv_t hr = ldiv(m_liFrame, 90000);
    int hour = (int)hr.quot;
  
    ldiv_t mn = ldiv(hr.rem, 1500);
    int minute = (int)mn.quot;
  
    ldiv_t sc = ldiv(mn.rem, 25);
    int second = (int)sc.quot;
  
    int frame = (int)sc.rem;
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
    IssueError(__FILE__, __LINE__, "not implemented");
    return s;
  }


} // end namespace RavlN
