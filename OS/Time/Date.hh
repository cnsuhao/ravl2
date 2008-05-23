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
//! docentry="Ravl.API.OS.Time"
//! rcsid="$Id$"
//! file="Ravl/OS/Time/Date.hh"
//! date="07/05/1998"

#include "Ravl/Types.hh"

namespace RavlN {
  class StringC;
  class BinIStreamC;
  class BinOStreamC;
  
  //: Date & Time information.
  // SMALL OBJECT.<br>
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
    
    static DateC NowUTC();
    //: Get the current time in Coordinated Universal Time  (UTC)
    
    static DateC NowLocal();
    //: Get the time in local timezone
    
    static DateC NowVirtual();
    //: Get the time since the process started.
    // Note on some systems this counter wraps after about 36 minutes.
    
    static DateC TimeZoneOffset();
    //: Get the local timezone offset.  (Note around daylight saving this may change.)
    
    inline DateC(bool setval,bool useVirt = false);
    //: Constructor.
    // This constructor is obsolete. Use one of NowUTC,NowLocal or NowVirtual.
    //!param: setval - if false an invalid date is created, otherwise a time is set.
    //!param: useVirt - If true use virtual process time.
    
    DateC(RealT val);
    //: Construct from a real in seconds.
    
    DateC(IntT year,IntT month,IntT day,IntT hour = 0,IntT min = 0,IntT sec = 0,IntT usec = 0,bool useLocalTimeZone = false);
    //: Constructor.
    //!param: year - Year (Must be from 1901 to 2038 inclusive)
    //!param: month - Month in year 1-12
    //!param: day - Day in the month 1 to 31
    //!param: hour - 0 to 23
    //!param: min - 0 to 59
    //!param: sec - 0 to 59
    //!param: usec - 1000000's of a second.
    //!param: useLocalTimeZone - When true assume parameters are in the local time zone and convert to UTC
    
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
    
    DateC(const StringC &str);
    //: String constructor
    // Expects data in sec.usec format 
    // as produced by Text() method.

    DateC Copy() const
    { return *this; }
    //: Make a copy of this object.
    
    DateC DeepCopy(UIntT levels) const
    { return *this; }
    //: Make a copy.
    
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
    //!param: useVirt - If true use process time, otherwise use UTC (Universal Coordinate Time)
    // Note. The static methods NowUTC(), NowLocal() and NowVirtual()
    // are the preferred method of getting the current time.
    
    inline long MaxUSeconds() const { return 1000000; }
    //: Maximum value for micro seconds, to avoid problems with mistyped number of zeros
    
    inline long Resolution() const
    { return 10000; }
    //: Get an estimate of the resolution of timer in microseconds.
    // NB. This assumes 100Hz by default.
    
    inline void NormalisePos();
    //: Normalise time representation after addition
    
    inline void NormaliseNeg();
    //: Normalise time representation after subtraction
    
    inline bool operator==(const DateC &oth) const;
    //: Compare times.
    
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
    //: In-place subtraction.
    
    inline const DateC &operator-=(double val);
    //: In-place subtraction (seconds).
    
    inline const DateC &operator+=(const DateC &val);
    //: In-place addition.
    
    inline const DateC &operator+=(double val);
    //: In-place addition (seconds).
    
    StringC Text() const;
    //: Get the time in string form.
    // This prints the time in decimal form: <code>sec.usec</code>.
    // There are always 6 digits after the decimal point.
    
    StringC ODBC(bool convertUTCToLocal = false,bool factionalSeconds = false) const;
    //: Return the date and time in ODBC format
    
    bool SetODBC(const StringC &odbcStr);
    //: Set date to ODBC specified time string.
    // Returns true if conversion successful, false
    // if string is not recognised.
    
    StringC CTime(bool convertUTCToLocal = false) const;
    //: Returns results equivalent to calling ctime().
    
    StringC CTimeShort(bool convertUTCToLocal = false) const;
    //: Returns a short string containing date/time.
    
    inline long USeconds() const
    { return usec; }
    //: Get fractional part of the current second in micro seconds.
    
    inline long TotalSeconds() const
    { return sec; }
    //: Get total whole seconds that have passed.
    
    inline double Double() const
    { return (double) sec + (((double)usec) / ((double) MaxUSeconds())); }
    //: Get time in seconds from the epoch in double form.
    
    IntT Seconds(bool convertUTCToLocal = false) const;
    //: Return number of seconds after minute. 0,61 (61 for leap seconds.)
    
    IntT Minute(bool convertUTCToLocal = false) const;
    //: Get minute.
    
    IntT Hour(bool convertUTCToLocal = false) const;
    //: Hours since midnight. 0 to 23
    
    IntT Month(bool convertUTCToLocal = false) const;
    //: Get month 1 to 12
    
    IntT Year(bool convertUTCToLocal = false) const;
    //: Get year.
    
    IntT DayInMonth(bool convertUTCToLocal = false) const;
    //: Get day in month.  1 to 31
    
    IntT DayInYear(bool convertUTCToLocal = false) const;
    //: Get day of year. 0 to 365
    
    IntT DayInWeek(bool convertUTCToLocal = false) const;
    //: Get day of week. Since Sunday, 0 to 6
    
    const StringC &TextDayInWeek(bool convertUTCToLocal = false) const;
    //: Get day of week in text form.
    
    bool DaylightSaving() const;
    //: Are we daylight saving ?
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
