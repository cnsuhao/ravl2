// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDATE_HEADER
#define RAVLDATE_HEADER 1
//////////////////////////////////////////////////////////////
//! userlevel=Normal
//! author="Charles Galambos"
//! lib=RavlOS
//! docentry="Ravl.OS.Time"
//! rcsid="$Id$"
//! file="Ravl/OS/Time/Date.hh"
//! date="07/05/1998"

#include "Ravl/Types.hh"

namespace RavlN {
  class StringC;
  class BinIStreamC;
  class BinOStreamC;
  
  //: Date & Time information.
  // SMALL OBJECT.
  // NB. The virtual timer uses the clock() system call. This
  // means virtual timing will only make sense for the first
  // 36 minutes. After that the timer will wrap.
  
  class DateC {
  public:
    inline DateC()
      : sec(0),
	usec(0)
    {}
    //: Default constructor.
    // Sets time to 0.
    
    inline DateC(bool setval,bool useVirt = false);
    //: Constructor.
    // If 'setval' is false an invalid date is created.
    // otherwise the date is set to now.
    // if useVirt is true a virtual time is used.
    
    DateC(RealT val);
    //: Construct from a real in seconds.
    
    DateC(IntT year,IntT month,IntT day,IntT hour = 0,IntT min = 0,IntT sec = 0,IntT usec = 0);
    //: Constructer.
    
    DateC(istream &in);
    //: Construct from a stream
    
    inline DateC(long xsec,long xusec)
      : sec(xsec),
	usec(xusec)
    {}
    //: Construct from two longs..
    
    inline DateC(const DateC &val)
      : sec(val.sec),
	usec(val.usec)
    {}
    //: Copy constructor
    
    DateC(const StringC &);
    //: String constructor
    // Expects data in sec:usec format 
    // as produced by Text() method.
    
    static bool IsLeapYear(int year);
    //: Is give year a leap year ?
    
    static int YearToDaysSince1970(int year);
    //: Convert year to days since 1970
    
    inline bool IsValid() const
    { return usec >= 0; }
    //: Is a valid date ?
    
    inline bool IsZero() const
    { return sec == 0 && usec == 0;}
    //: Is time zero ?
    
    inline void SetInvalid()
    { usec = -1; }
    //: Make this date invalid.
    
    void SetToNow(bool useVirt = false);
    //: Set value of variable to now!
    
    inline long MaxUSeconds() const { return 1000000; }
    //: Maximum mircro seconds.
    
    inline long Resolution() const
    { return 10000; }
    //: Get resolution of timer in microseconds.
    // NB. This assumes 100Hz by default.
    
    inline void NormalisePos();
    //: Normalise time representation after addition
    
    inline void NormaliseNeg();
    //: Normalise time representation after subtraction
    
    inline bool operator==(const DateC &oth) const;
    //: Compre times.
    
    inline bool operator!=(const DateC &oth) const
    { return !operator==(oth); }
    //: Compare times.
    
    inline bool operator>(const DateC &oth) const;
    //: Compare times.
    
    inline bool operator<(const DateC &oth) const;
    //: Compare times.
    
    inline bool operator>=(const DateC &oth) const;
    //: Compare times.
    
    inline bool operator<=(const DateC &oth) const;
    //: Compare times.
  
    inline DateC operator+(const DateC &oth) const;
    //: Add times.
    
    inline DateC operator-(const DateC &oth) const;
    //: Subtract times.
    
    inline const DateC &operator-=(const DateC &val);
    //: Inplace subtraction.
    
    inline const DateC &operator-=(double val);
    //: Inplace subtraction.
    
    inline const DateC &operator+=(const DateC &val);
    //: Inplace addition.
    
    inline const DateC &operator+=(double val);
    //: Inplace addition.
    
    StringC Text() const;
    //: Get the time in string form.
    // This currently prints the time in the form
    // sec:usec.
    
    StringC CTime() const;
    //: Returns results equivelent to calling ctime().
    
    StringC CTimeShort() const;
    //: Returns a short string containing date/time.
    
    inline long USeconds() const
    { return usec; }
    //: Get micro seconds.
    
    inline long TotalSeconds() const
    { return sec; }
    //: Get total seconds.
    
    inline double Double() const
    { return (double) sec + (((double)usec) / ((double) MaxUSeconds())); }
    //: Get time in double form.
    
    IntT Seconds() const;
    //: Return number of seconds after minuite. 0,61 (61 for leap seconds.)
    
    IntT Minute() const;
    //: Get minute.
    
    IntT Hour() const;
    //: Hours since midnight. 0-23
    
    IntT Month() const;
    //: Get month 1-31
    
    IntT Year() const;
    //: Get year.
    
    IntT DayInMonth() const;
    //: Get day in month.  1,31
    
    IntT DayInYear() const;
    //: Get day of year. 0-365
    
    IntT DayInWeek() const;
    //: Get day of week. Since sunday, 0-6
    
    const StringC &TextDayInWeek() const;
    //: Get day of week in text form.
    
    bool DaylightSaving() const;
    //: Are we daylight saveing ?
    // True = yes
    
    bool Wait() const;
    //: Wait until this time.
    // this is implemented with the DeadLineTimer.
    
    void Save(ostream &out) const;
    //: Write to a stream.
    
  private:
    long sec;  // Seconds since 12:00 January 1, 1970.
    long usec; // microseconds.
  };
  
  
  bool Sleep(RealT delay);
  //: Pause execution for 'delay' seconds.
  
  ostream &operator <<(ostream &out,const DateC &date);
  //: Stream operator.
  
  istream &operator >>(istream &in,DateC &date);
  //: Stream operator.
  
  BinOStreamC &operator <<(BinOStreamC &out,const DateC &date);
  //: Stream operator.
  
  BinIStreamC &operator >>(BinIStreamC &in,DateC &date);
  //: Stream operator.
  
  //////////////////////////////////////////////////////////
  
  inline 
  DateC::DateC(bool setval,bool useVirt)  {
    if(setval)
      SetToNow(useVirt);
    else {
      sec = 0;
      usec = -1;
    }
  }
  
  inline 
  bool DateC::operator==(const DateC &oth) const {
    if(sec != oth.sec)
      return false;
    return (usec == oth.usec);
  }
  
  inline 
  bool DateC::operator>(const DateC &oth) const  {
    if(sec > oth.sec)
      return true;
    if(sec < oth.sec)
      return false;
    return (usec > oth.usec);
  }
  
  inline 
  bool DateC::operator<(const DateC &oth) const  {
    if(sec < oth.sec)
      return true;
    if(sec > oth.sec)
      return false;
    return (usec < oth.usec);
  }
  
  inline 
  bool DateC::operator>=(const DateC &oth) const  {
    if(sec > oth.sec)
      return true;
    if(sec < oth.sec)
      return false;
    return (usec >= oth.usec);
  }
  
  inline 
  bool DateC::operator<=(const DateC &oth) const  {
    if(sec < oth.sec)
      return true;
    if(sec > oth.sec)
      return false;
    return (usec <= oth.usec);
  }
  
  inline 
  void DateC::NormalisePos()  {
    while(usec >= MaxUSeconds()) {
      usec -= MaxUSeconds();
      sec++;
    }
  }
  
  inline 
  void DateC::NormaliseNeg()  {
    while(usec < 0) {
      usec += MaxUSeconds();
      sec--;
    }
  }
  
  inline 
  DateC DateC::operator+(const DateC &oth) const  {
    DateC ret;
    ret.sec = sec + oth.sec;
    ret.usec = usec + oth.usec;
    ret.NormalisePos();
    return ret;
  }
  
  inline 
  DateC DateC::operator-(const DateC &oth) const  {
    DateC ret;
    ret.sec = sec - oth.sec;
    ret.usec = usec - oth.usec;
    ret.NormaliseNeg();
    return ret;
  }
  
  inline
  const DateC &DateC::operator-=(const DateC &val) {
    sec -= val.sec;
    usec -= val.usec;
    NormaliseNeg();
    return *this;
  }

  inline
  const DateC &DateC::operator+=(const DateC &val)  {
    sec += val.sec;
    usec += val.usec;
    NormalisePos();
    return *this;
  }
  
  inline 
  const DateC &DateC::operator+=(double val) {
    sec += (long) val;
    usec += ((long) ((RealT) val * 1000000) % 1000000);
    NormalisePos();  
    return *this;
  }
  
  inline 
  const DateC &DateC::operator-=(double val) {
    sec -= (long) val;
    usec -= ((long) ((RealT) val * 1000000) % 1000000);
    NormaliseNeg();
    return *this;
  }
  
}

#endif
