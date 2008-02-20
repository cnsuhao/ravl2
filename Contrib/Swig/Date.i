// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html

%include "Ravl/Swig/Types.i"
%include "Ravl/Swig/String.i"

%{
#undef Copy
#include "Ravl/OS/Date.hh"
#define Copy(s,d,n,t)   (MEM_WRAP_CHECK_(n,t) (void)memcpy((char*)(d),(const char*)(s), (n) * sizeof(t)))
%}

namespace RavlN
{

  class DateC {
  public:
    DateC();
    //: Default constructor.
    // Sets time to 0.

    static DateC NowUTC();
    //: Get the current time in Coordinated Universal Time  (UTC)

    static DateC NowLocal();
    //: Get the time in local timezone

    static DateC NowVirtual();
    //: Get the time since the process started.

    static DateC TimeZoneOffset();
    //: Get the local timezone offset.  (Note around daylight saving this may change.)

    inline DateC(bool setval,bool useVirt = false);
    //: Constructor.
    // This constructor is obsolete. Use one of NowUTC,NowLocal or NowVirtual.
    //!param: setval - is false an invalid date is created, otherwise a time is set.
    //!param: useVirt - If true use virtual process time.

    DateC(RealT val);
    //: Construct from a real in seconds.

    DateC(IntT year,IntT month,IntT day,IntT hour = 0,IntT min = 0,IntT sec = 0,IntT usec = 0,bool useLocalTimeZone = false);
    //: Constructer.
    //!param: year - Year (Must be from 1901 to 2038 inclusive)
    //!param: month - Month in year 1-12
    //!param: day - Day in the month 1 to 31
    //!param: hour - 0 to 23
    //!param: min - 0 to 59
    //!param: sec - 0 to 59
    //!param: usec - 1000000's of a second.
    //!param: useLocalTimeZone - When true assume parameters are in the local time zone and convert to UTC

    DateC(long xsec,long xusec);
    //: Construct from two longs..

    DateC(const DateC &val);
    //: Copy constructor

    DateC(const StringC &str);
    //: String constructor
    // Expects data in sec:usec format
    // as produced by Text() method.

    static bool IsLeapYear(int year);
    //: Is give year a leap year ?

    static int YearToDaysSince1970(int year);
    //: Convert year to days since 1970

    bool IsValid() const;
    //: Is a valid date ?

    bool IsZero() const;
    //: Is time zero ?

    void SetInvalid();
    //: Make this date invalid.

    void SetToNow(bool useVirt = false);
    //: Set value of variable to now!
    //!param: useVirt - If true use process time.

    long MaxUSeconds() const;
    //: Maximum mircro seconds.

    long Resolution() const;
    //: Get resolution of timer in microseconds.
    // NB. This assumes 100Hz by default.

    void NormalisePos();
    //: Normalise time representation after addition

    void NormaliseNeg();
    //: Normalise time representation after subtraction

    bool operator==(const DateC &oth) const;
    //: Compre times.

    bool operator!=(const DateC &oth) const
    { return !operator==(oth); }
    //: Compare times.

    bool operator>(const DateC &oth) const;
    //: Compare times.

    bool operator<(const DateC &oth) const;
    //: Compare times.

    bool operator>=(const DateC &oth) const;
    //: Compare times.

    bool operator<=(const DateC &oth) const;
    //: Compare times.

    DateC operator+(const DateC &oth) const;
    //: Add times.

    DateC operator-(const DateC &oth) const;
    //: Subtract times.

    const DateC &operator-=(const DateC &val);
    //: Inplace subtraction.

    const DateC &operator-=(double val);
    //: Inplace subtraction (seconds).

    const DateC &operator+=(const DateC &val);
    //: Inplace addition.

    const DateC &operator+=(double val);
    //: Inplace addition (seconds).

    StringC Text() const;
    //: Get the time in string form.
    // This currently prints the time in the form
    // sec:usec.

    StringC ODBC(bool convertUTCToLocal = false) const;
    //: Return the date and time in ODBC format

    bool SetODBC(const StringC &odbcStr);
    //: Set date to odbc specified time string.
    // Returns true if conversion succesfull, false
    // if string is not recognised.

    StringC CTime(bool convertUTCToLocal = false) const;
    //: Returns results equivelent to calling ctime().

    StringC CTimeShort(bool convertUTCToLocal = false) const;
    //: Returns a short string containing date/time.

    long USeconds() const;
    //: Get micro seconds.

    long TotalSeconds() const;
    //: Get total seconds.

    double Double() const;
    //: Get time in double form.

    IntT Seconds(bool convertUTCToLocal = false) const;
    //: Return number of seconds after minuite. 0,61 (61 for leap seconds.)

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
    //: Get day of week. Since sunday, 0 to 6

    const StringC TextDayInWeek(bool convertUTCToLocal = false) const;
    //: Get day of week in text form.

    bool DaylightSaving() const;
    //: Are we daylight saveing ?
    // True = yes

    bool Wait() const;
    //: Wait until this time.
    // this is implemented with the DeadLineTimer.

  };

}

