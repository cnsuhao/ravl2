// TimeCodeC.cpp: implementation of the TimeCodeC class.
//
//////////////////////////////////////////////////////////////////////

#include "Ravl/TimeCode.hh"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace RavlN {

TimeCodeC::TimeCodeC(ByteT hr, ByteT min, ByteT sec, ByteT fr)
//========================================================
{
	m_liFrame = bcd(hr) * 90000;
	m_liFrame += bcd(min) * 1500;
	m_liFrame += bcd(sec) * 25;
	m_liFrame += bcd(fr);
}

TimeCodeC::TimeCodeC(ByteT *in)
//============================
{
	m_liFrame = bcd(in[3]) * 90000;
	m_liFrame += bcd(in[2]) * 1500;
	m_liFrame += bcd(in[1]) * 25;
	m_liFrame += bcd(in[0]);
}


TimeCodeC::TimeCodeC(int hr, int min, int sec, int fr)
//====================================================
{
	m_liFrame = hr * 90000;
	m_liFrame += min * 1500;
	m_liFrame += sec * 25;
	m_liFrame += fr;
}


TimeCodeC::TimeCodeC(const long int frameNum)
//=====================================
{
	m_liFrame = frameNum;
}

TimeCodeC::TimeCodeC(const TimeCodeC &in)
//=======================================
{
	m_liFrame = in.m_liFrame;
}


TimeCodeC::TimeCodeC(const char * p)
//=====================================
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


TimeCodeC::TimeCodeC()
//====================
{
	m_liFrame = 0;
}


TimeCodeC::~TimeCodeC()
//=====================
{

}

TimeCodeC &
TimeCodeC::operator=(const TimeCodeC & in)
//=======================================
{
	m_liFrame = in.m_liFrame;
	return (*this);
}


bool 
TimeCodeC::operator==(const TimeCodeC &in) const
//===============================================
{

	if(m_liFrame == in.m_liFrame) return true;
	return false;
}

bool 
TimeCodeC::operator==(TimeCodeC &in) 
//==================================
{

	if(m_liFrame == in.m_liFrame) return true;
	return false;
}


bool 
TimeCodeC::operator!=(const TimeCodeC &in) 
//==================================
{
	if(m_liFrame != in.m_liFrame) return true;
	return false;
}

bool 
TimeCodeC::operator<(const TimeCodeC &in) const
//=================================
{
	if(m_liFrame < in.m_liFrame) return true;
	return false;
}


bool 
TimeCodeC::operator>(const TimeCodeC &in) const 
//=================================
{
	if(m_liFrame > in.m_liFrame) return true;
	return false;
}

bool 
TimeCodeC::operator<=(const TimeCodeC &in) const
//=================================
{
	if(m_liFrame <= in.m_liFrame) return true;
	return false;
}

bool 
TimeCodeC::operator>=(const TimeCodeC &in) const 
//=================================
{
	if(m_liFrame >= in.m_liFrame) return true;
	return false;
}

TimeCodeC 
TimeCodeC::operator+(const TimeCodeC & in) const
//===============================================
{
	long int newFrameCount = m_liFrame + in.m_liFrame;
	TimeCodeC res(newFrameCount);
	return res;
}

TimeCodeC 
TimeCodeC::operator-(const TimeCodeC & in) const
//===============================================
{
	long int newFrameCount = m_liFrame - in.m_liFrame;
	TimeCodeC res(newFrameCount);
	return res;
}

TimeCodeC &
TimeCodeC::operator+=(const TimeCodeC & in)
//=========================================
{
	m_liFrame += in.m_liFrame;
	return *this;
}

TimeCodeC &
TimeCodeC::operator+=(long int in)
//=========================================
{
	m_liFrame += in;
	return *this;
}


TimeCodeC &
TimeCodeC::operator-=(const TimeCodeC & in)
//=========================================
{
	m_liFrame -= in.m_liFrame;
	return *this;
}



int 
TimeCodeC::NumberOfFramesTo(const TimeCodeC & tc_In)
//============================================
{
  return (int)sqrt(pow((double)(m_liFrame - tc_In.m_liFrame), 2));
}



bool
TimeCodeC::IsValid()
//==================
{
  
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

char *
TimeCodeC::ToChar() const
//===========================
{
  ldiv_t hr = ldiv(m_liFrame, 90000);
  int hour = (int)hr.quot;
  
  ldiv_t mn = ldiv(hr.rem, 1500);
  int minute = (int)mn.quot;
  
  ldiv_t sc = ldiv(mn.rem, 25);
  int second = (int)sc.quot;
  
  int frame = (int)sc.rem;
  
  char *str = new char[11];
  sprintf(str, "%.2d:%.2d:%.2d:%.2d", hour, minute, second, frame);
  return str;
}

} // end namespaceT RavlN
