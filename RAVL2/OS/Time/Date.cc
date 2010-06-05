// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////
//! userlevel=Normal
//! author="Charles Galambos"
//! rcsid="$Id: Date.cc 7732 2010-05-19 17:06:04Z craftit $"
//! lib=RavlOS
//! file="Ravl/OS/Time/Date.cc"

#undef _ANSI_SOURCE
#undef _POSIX_C_SOURCE

#include "Ravl/config.h"

#if RAVL_OS_SOLARIS
#define _POSIX_PTHREAD_SEMANTICS 1
#define _REENTRANT 1
//#define __STDC__ 0
#include <time.h>
#endif

#if defined(__linux__) && !defined(_GNU_SOURCE)
#define _GNU_SOURCE 1
#endif

#if RAVL_OS_WIN32
// Turn off deprecated warnings for now, they're not deprecated on other platforms
// may introduce more platform specific fixes later.
#define _CRT_SECURE_NO_DEPRECATE 1
#include <sys/timeb.h>
#endif

#include <time.h>

#ifdef RAVL_OS_MACOSX
extern "C" {
  char *asctime_r(const struct tm *, char *);
  char *ctime_r(const time_t *, char *);
  struct tm *gmtime_r(const time_t *, struct tm *);
  struct tm *localtime_r(const time_t *, struct tm *);
}
#endif

#include "Ravl/Exception.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/String.hh"
#include "Ravl/StrStream.hh"

#include <stdlib.h>

#if RAVL_HAVE_WIN32_THREADS
#include <windows.h>
#endif

#if !RAVL_COMPILER_VISUALCPP
#include <sys/time.h>
#include <sys/timeb.h>
#include <unistd.h>
#else
#include <string.h>

#include <sys/types.h>

char *ctime_r(const time_t *s,char *buff) {
  strcpy(buff,ctime(s));
  return buff;
}

struct tm *localtime_r( const time_t *timer,struct tm *b) {
  memcpy(b,localtime(timer),sizeof(tm));
  return b;
}

extern int sleep(int x); // A hack, I hope it doesn't cause problems later...

#endif

#if defined(__linux__)
#include <sched.h>
#endif

#if RAVL_HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif

namespace RavlN {

  //: Construct from a stream
  
  DateC::DateC(istream &in) { 
    in >> sec >> usec; 
  }
  
  //: Write to a stream.
  
  void DateC::Save(ostream &out) const { 
    out << sec << " " << usec; 
  }
  
  //: Construct from a real in seconds.
  
  DateC::DateC(RealT val) {
    sec = (Int64T) val;
    usec = (long) ((RealT) (val - (RealT) sec) * MaxUSeconds());
  }
  
  //: String constructor
  // Expects data in sec.usec format 
  // as produced by Text() method.
  
  DateC::DateC(const StringC &str) 
    : sec(0), usec(0)
  {
    int sep = str.index('.');
    if(sep < 0) sep = str.index(':');
    if(sep < 0) {
      cerr << "DateC::DateC(), ERROR: String in unrecognised format. '" << str << "'\n";
      return ;
    }
    StringC numS(str);
    sec = atol(StringC(numS.before(sep)));
    for (UIntT i(sep+1); i<str.Size(); ++i)
      usec = (usec *10 + atoi(StringC(str[i])));
  }
  
  //: Is give year a leap year ?
  
  bool DateC::IsLeapYear(int year)  {
    if((year % 4) != 0)
      return false;
    if((year % 100) != 0)
      return true;
    // Is a leap year if century is not divisable by 4.
    return ((year % 400) == 0);
  }
  
  //: Convert year to days since 1970
  DateC::SecondT DateC::YearToDaysSince1970(int year)  {
    SecondT yearx =  year - 1970;
    SecondT yearl = year - 1;
    return (yearx * 365) + (yearl / 4) - (yearl / 100) + (yearl / 400) - 477;
  }
  
  //: Constructor.
  
  DateC::DateC(IntT year,IntT month,IntT day,IntT hour,IntT min,IntT asec,IntT nusec,bool useLocalTimeZone)
    : sec(0),
      usec(nusec)
  {
    if(!useLocalTimeZone) {
      //                                    Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov,Dec,x
      static SecondT daysin[14]           = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 0 };
      static SecondT daysintoyear[14]     = { 0,  0, 31, 59, 90,120,151,181,212,243,273,304,334, 365};
      static SecondT daysleapin[14]       = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 0 };
      static SecondT daysintoleapyear[14] = { 0,  0, 31, 60, 91,121,152,182,213,244,274,305,335, 366};
      sec =  YearToDaysSince1970(year) * 24 * 60 * 60;
      if(month < 1 || month > 12) {
	cerr << "DateC::DateC(), Illegal month " << month << "\n";
	return ;
      }
      if(IsLeapYear(year)) {
	sec += daysintoleapyear[month] * 24 * 60 * 60;
	if(day < 1 || day > daysleapin[month]) {
	  cerr << "DateC::DateC(), Illegal day " <<day << " in month " << month << "\n";
	  return ;
	}
      } else {
	sec += daysintoyear[month] * 24 * 60 * 60;
	if(day < 1 || day > daysin[month]) {
	  cerr << "DateC::DateC(), Illegal day " <<day << " in month " << month << "\n";
	  return ;
	}
      }
      sec += (day-1) * (24 * 60 * 60);
      if(hour < 0 || hour > 23) {
	cerr << "DateC::DateC(), Illegal hour " << hour << "\n";
	return ;
      }
      sec += hour * (60 * 60);
      if(min < 0 || min > 59) {
	cerr << "DateC::DateC(), Illegal minite " << min << "\n";
	return ;
      }
      sec += min * 60;
      if(asec < 0 || asec > 59) {
	cerr << "DateC::DateC(), Illegal second " << min << "\n";
	return ;
      }
      sec += asec;
    } else {
      struct tm ttm;
      ttm.tm_year = year - 1900;
      ttm.tm_mon = month-1;
      ttm.tm_mday = day;
      ttm.tm_hour = hour;
      ttm.tm_min = min;
      ttm.tm_sec = asec;
      ttm.tm_wday = -1;
      ttm.tm_yday = -1;
      ttm.tm_isdst = -1;
      sec = mktime(&ttm);
      if(sec == -1)
	cerr << "DateC::DateC(), Illegal date. " << sec << "\n";
    }
  }
  

  //: Get the time in local timezone
  
  DateC DateC::NowLocal() {
#if !RAVL_COMPILER_VISUALCPP    
    // Get time of day
    struct timeval tv;
    gettimeofday(&tv,0);
    DateC ret(tv.tv_sec,tv.tv_usec);
    
    // Go and get the local time offset.
    struct tm b;
    time_t s = (time_t) tv.tv_sec;
    localtime_r(&s,&b);
    
    //cerr << "DateC::NowUTC " << tz.tz_minuteswest << " Raw=" << ret.ODBC() << " \n";
    ret += DateC((time_t)b.tm_gmtoff, 0l);
    return ret;
#else
#if RAVL_OS_WIN32
    struct _timeb ltime;
    _ftime(&ltime);
	return DateC((long)ltime.time, (long)ltime.millitm * 1000);
#else
    throw ExceptionC("DateC::NowLocal(), Not implemented. ");
#endif
#endif
  }
  
  //: Get an invalid time.

  DateC DateC::InvalidTime() {
    DateC ret;
    ret.SetInvalid();
    return ret;
  }

  //: Get the current time in Coordinated Universal Time  (UTC)
  
  DateC DateC::NowUTC() {
#if !RAVL_COMPILER_VISUALCPP
    struct timeval tv;
    gettimeofday(&tv,0);
    return DateC(tv.tv_sec,tv.tv_usec);
#else
#if RAVL_OS_WIN32
    struct _timeb ltime;
    _ftime(&ltime);
    return DateC((long)ltime.time, (long)ltime.millitm * 1000);
#else
    throw ExceptionC("DateC::NowLocal(), Not implemented. ");
#endif
#endif
  }
  
  //: Get the time since the process started.
  
  DateC DateC::NowVirtual() {
#if !RAVL_OS_WIN32
    DateC ret((long)0,(long)clock());
    ret.NormalisePos();
    return ret;
#else
    throw ExceptionC("DateC::NowVirtual(), Not implemented. ");
#endif
  }
  
  
  //: Set value of variable to now!
  
  void DateC::SetToNow(bool useVirt)  {
#if !RAVL_COMPILER_VISUALCPP
    if(useVirt) {
      usec = clock(); // FIXME :- This will fail after about 36 mintes.
      sec = 0;
      NormalisePos();    
      return ;
    }
    struct timeval tv;
    gettimeofday(&tv,0);
    sec =tv.tv_sec;
    usec =tv.tv_usec;
#else
#if RAVL_OS_WIN32
    struct _timeb ltime;
    _ftime(&ltime);
    sec = ltime.time;
    usec = ltime.millitm * 1000;
#else
    throw ExceptionC("DateC::SetToNow(), Not implemented. ");
#endif
#endif
  }
  
  //: Get the local timezone offset.  (Note around daylight saving this may change.)
  
  DateC DateC::TimeZoneOffset() {
#if !RAVL_COMPILER_VISUALCPP    
    struct timeval tv;
    gettimeofday(&tv,0);
    
    // Get time of day
    // Go and get the local time offset.
    struct tm b;
    time_t s = (time_t) tv.tv_sec;
    localtime_r(&s,&b);
    
    return DateC((time_t)-b.tm_gmtoff, 0l);
#else
    throw ExceptionC("DateC::TimeZoneOffset(), Not implemented. ");
#endif    
  }
  
  //: Get the time in string form.
  
  StringC DateC::Text() const  { 
    StringC str;
    str.form("%d.%06d", (unsigned int)sec, (unsigned int)usec);
    return str; 
  }


  //: Return the date and time in ODBC format
  
  StringC DateC::ODBC(bool convertUTCToLocal,bool factionalSeconds) const {
    StringC str;
    if(factionalSeconds) {
      UIntT seconds = Seconds(convertUTCToLocal);
      // Fix formating problem where leading zero is removed from floats.
      if(seconds < 10) {
        str.form("%04d-%02d-%02d %02d:%02d:0%1.10f",
            Year(convertUTCToLocal),
            Month(convertUTCToLocal),
            DayInMonth(convertUTCToLocal),
            Hour(convertUTCToLocal),
            Minute(convertUTCToLocal),
            (double) seconds + (usec / 1000000.0)
        );
      } else {
        str.form("%04d-%02d-%02d %02d:%02d:%02.10f",
            Year(convertUTCToLocal),
            Month(convertUTCToLocal),
            DayInMonth(convertUTCToLocal),
            Hour(convertUTCToLocal),
            Minute(convertUTCToLocal),
            (double) seconds + (usec / 1000000.0)
        );
      }
    } else {
      str.form("%04d-%02d-%02d %02d:%02d:%02d",
               Year(convertUTCToLocal),
               Month(convertUTCToLocal),
               DayInMonth(convertUTCToLocal),
               Hour(convertUTCToLocal),
               Minute(convertUTCToLocal),
               Seconds(convertUTCToLocal)
               );
    }
    return str;
  }

  //: Generate date from odbc string.
  
  DateC DateC::FromODBCString(const StringC &dateStr) {
    DateC ret;
    ret.SetODBC(dateStr);
    return ret;
  }
  
  //: Set date to odbc specified time string.
  // Returns true if conversion succesfull, false
  // if string is not recognised.
  
  bool DateC::SetODBC(const StringC &odbcStr) {
   
    // Empty field ?
    
    if(odbcStr.Size() < 19)
      return false;
    
    IntT seconds, minute, hour, day, month, year;
    StringC tmp = odbcStr.Copy();
    char *str = &tmp[0];
    char *ptr = str;
    
    // Check the stream is formated correctly.
    if(str[4] != '-' || str[7] != '-' || str[10] != ' ' || str[13] != ':' || str[16] != ':')
      return false;
    
    // Get seconds
    ptr = str + 17;
    double intPart;
    double secondsFloat = atof(ptr);
    long usecPart = Round(modf(secondsFloat,&intPart) * 1000000.0);
    seconds = Round(intPart);
    
    // Get minute
    str[16] = 0;
    ptr = str + 14;
    minute = atoi(ptr);
    // Get hour
    str[13] = 0;
    ptr = str + 11;
    hour = atoi(ptr);
    // Get day
    str[10] = 0;
    ptr = str + 8;
    day = atoi(ptr);
    // Get month
    str[7] = 0;
    ptr = str + 5;
    month = atoi(ptr);
    // Get year
    str[4] = 0;
    ptr = str;
    year = atoi(ptr);
    
    // Create date structure
    *this = DateC(year, month, day, hour, minute, seconds,usecPart,false);
    
    return true;
  }


  //: Returns results equivelent to calling ctime().
  
  StringC DateC::CTime(bool useUTCToLocal) const  {
    char buff[50];
    time_t s = (time_t) sec;
    StringC ret;
    if(useUTCToLocal) {
      ret = StringC(ctime_r(&s,buff));
    } else {
      time_t s = (time_t) sec;
#if !RAVL_COMPILER_VISUALCPP
      struct tm b;
      ret = StringC(asctime_r(gmtime_r(&s,&b),buff));
#else
      // VC++ does not support asctime_r or gmtime_r so use the other versions
      // in lieu of anything else
      ret = StringC(asctime(gmtime(&s)));
#endif
    }
    ret.del("\n"); // Get rid of return.
    return ret;
  }
  
  //: Returns a short string containing date/time.
  
  StringC DateC::CTimeShort(bool useUTCToLocal) const {
    StringC buf;
    struct tm b;
    time_t s = (time_t) sec;
    if (useUTCToLocal) {
      localtime_r(&s,&b);
    } else {
#if !RAVL_COMPILER_VISUALCPP
      gmtime_r(&s,&b);
#else
      // VC++ does not support asctime_r or gmtime_r so use the non-thread-safe versions
      // in lieu os anythings else
      b = *gmtime(&s);
#endif
    }
    buf += StringC(b.tm_hour) + ":" + StringC(b.tm_min) + ":" + StringC(b.tm_sec);
    buf += "-";
    buf += StringC(b.tm_mday) + "/" + StringC(b.tm_mon) + "/" + StringC(b.tm_year + 1900);
    return buf;
  }
  
  
  //: Return number of seconds after minuite. 0,61 (61 for leap seconds.)
  
  IntT DateC::Seconds(bool useUTCToLocal) const  {
    struct tm b;
    time_t s = (time_t) sec;
    if (useUTCToLocal) {
      localtime_r(&s,&b);
    } else {
#if !RAVL_COMPILER_VISUALCPP
      gmtime_r(&s,&b);
#else
      // VC++ does not support asctime_r or gmtime_r so use the non-thread-safe versions
      // in lieu os anythings else
      b = *gmtime(&s);
#endif
    }
    return b.tm_sec;
  }
  
  //: Get minute.
  
  IntT DateC::Minute(bool useUTCToLocal) const  {
    struct tm b;
    time_t s = (time_t) sec;
    if (useUTCToLocal) {
      localtime_r(&s,&b);
    } else {
#if !RAVL_COMPILER_VISUALCPP
      gmtime_r(&s,&b);
#else
      // VC++ does not support asctime_r or gmtime_r so use the non-thread-safe versions
      // in lieu os anythings else
      b = *gmtime(&s);
#endif
    }
    return b.tm_min;
  }
  
  
  //: Hours since midnight. 0-23
  
  IntT DateC::Hour(bool useUTCToLocal) const  {
    struct tm b;
    time_t s = (time_t) sec;
    if (useUTCToLocal) {
      localtime_r(&s,&b);
    } else {
#if !RAVL_COMPILER_VISUALCPP
      gmtime_r(&s,&b);
#else
      // VC++ does not support asctime_r or gmtime_r so use the non-thread-safe versions
      // in lieu os anythings else
      b = *gmtime(&s);
#endif
    }
    return b.tm_hour;  
  }
  
  //: Get month 1-31
  
  IntT DateC::Month(bool useUTCToLocal) const  {
    struct tm b;
    time_t s = (time_t) sec;
    if (useUTCToLocal) {
      localtime_r(&s,&b);
    } else {
#if !RAVL_COMPILER_VISUALCPP
      gmtime_r(&s,&b);
#else
      // VC++ does not support asctime_r or gmtime_r so use the non-thread-safe versions
      // in lieu os anythings else
      b = *gmtime(&s);
#endif
    }
    return b.tm_mon + 1;
  }
  
  
  //: Get year.
  
  IntT DateC::Year(bool useUTCToLocal) const  {
    struct tm b;
    time_t s = (time_t) sec;
    if (useUTCToLocal) {
      localtime_r(&s,&b);
    } else {
#if !RAVL_COMPILER_VISUALCPP
      gmtime_r(&s,&b);
#else
      // VC++ does not support asctime_r or gmtime_r so use the non-thread-safe versions
      // in lieu os anythings else
      b = *gmtime(&s);
#endif
    }
    return b.tm_year + 1900;  
  }
  
  //: Get day in month.  1,31
  
  IntT DateC::DayInMonth(bool useUTCToLocal) const  {
    struct tm b;
    time_t s = (time_t) sec;
    if (useUTCToLocal) {
      localtime_r(&s,&b);
    } else {
#if !RAVL_COMPILER_VISUALCPP
      gmtime_r(&s,&b);
#else
      // VC++ does not support asctime_r or gmtime_r so use the non-thread-safe versions
      // in lieu os anythings else
      b = *gmtime(&s);
#endif
    }
    return b.tm_mday;    
  }
  
  //: Get day of year. 0-365
  
  IntT DateC::DayInYear(bool useUTCToLocal) const  {
    struct tm b;
    time_t s = (time_t) sec;
    if (useUTCToLocal) {
      localtime_r(&s,&b);
    } else {
#if !RAVL_COMPILER_VISUALCPP
      gmtime_r(&s,&b);
#else
      // VC++ does not support asctime_r or gmtime_r so use the non-thread-safe versions
      // in lieu os anythings else
      b = *gmtime(&s);
#endif
    }
    return b.tm_yday;
  }
  
  
  //: Get day of week. Since sunday, 0-6

  IntT DateC::DayInWeek(bool useUTCToLocal) const  {
    struct tm b;
    time_t s = (time_t) sec;
    if (useUTCToLocal) {
      localtime_r(&s,&b);
    } else {
#if !RAVL_COMPILER_VISUALCPP
      gmtime_r(&s,&b);
#else
      // VC++ does not support asctime_r or gmtime_r so use the non-thread-safe versions
      // in lieu os anythings else
	  b = *gmtime(&s);
#endif
    }
    return b.tm_wday;  
  }

  //: Get day of week in text form.
  
  const StringC &DateC::TextDayInWeek(bool useUTCToLocal) const {
    static StringC days[7] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    return days[DayInWeek(useUTCToLocal)];
  }
  
  //: Are we daylight saveing ?
  // True = yes
  
  bool DateC::DaylightSaving() const  {
    struct tm b;
    time_t s = (time_t) sec;

#if !RAVL_COMPILER_VISUALCPP
    gmtime_r(&s,&b);
#else
    // VC++ does not support asctime_r or gmtime_r so use the non-thread-safe versions
    // in lieu os anythings else
    b = *gmtime(&s);
#endif
    return b.tm_isdst > 0;
  }
  
  ostream &operator <<(ostream &out,const DateC &date) {
    date.Save(out);
    return out;
  }
  
  //: Stream operator.
  
  istream &operator >>(istream &in,DateC &date) {
    date = DateC(in);
    return in; 
  }

#if 1
  //: Wait until this time.
  
  bool DateC::Wait() const {
#if !RAVL_COMPILER_VISUALCPP
    struct timeval timeout;
    int reterr;
#if RAVL_OS_LINUX || RAVL_OS_LINUX64
    // Linux select modifies 'timeout' to time not slept, so we only have to setup once.
    DateC now = DateC::NowUTC();
    if(now >= *this)
      return true;
    DateC toGo = *this - now;
    //cerr << "Delay=" << toGo << "\n";
    timeout.tv_sec = toGo.TotalSeconds();
    timeout.tv_usec = toGo.USeconds();
    while(timeout.tv_sec > 0 || timeout.tv_usec > 0) {
      reterr = select(0,0,0,0,&timeout);
      // A signal may throw us out of select early so check we're finished.
    };
    
#else
    do {
      DateC now = DateC::NowUTC();
      if(now >= *this)
	return true;
      DateC toGo = *this - now;
      timeout.tv_sec = toGo.TotalSeconds();
      timeout.tv_usec = toGo.USeconds();
      reterr = select(0,0,0,0,&timeout);
      // A signal may throw us out of select early.
    } while(1);
#endif
#else
#if RAVL_HAVE_WIN32_THREADS
    do {
      DateC now = DateC::NowUTC();
      if(now >= *this)
	return true;
      DateC toGo = *this - now;
      ::Sleep(Round(toGo.Double() * 1000));
      // A signal may throw us out of select early.
    } while(1);
#else
    throw ExceptionC("DateC::Wait(), Not implemented. ");
#endif
#endif
    return true;
  }

  //: Pause execution for 'delay' seconds.
  
  bool Sleep(RealT delay) {
#if RAVL_HAVE_WIN32_THREADS
    ::Sleep(Round(delay * 1000));
    return true;
#else
#if RAVL_OS_LINUX || RAVL_OS_LINUX64
    //cerr << "Delay=" << toGo << "\n";
    if(delay <= 0)
      return true;
    struct timeval timeout;
    double dummy;
    timeout.tv_sec = Floor(delay);
    timeout.tv_usec = Round(modf(delay,&dummy) * 1000000.0);
    while(timeout.tv_sec > 0 || timeout.tv_usec > 0) {
      //std::cerr << " Sec=" << timeout.tv_sec << " usec=" << timeout.tv_usec << "\n";
      select(0,0,0,0,&timeout);
      // A signal may throw us out of select early so check we're finished.
    };
    return true;
#else
    DateC now(true);
    now += delay;
    return now.Wait();
#endif
#endif
  }
#endif

  const DateC &DateC::operator+=(double val) {

#if 0
    sec += (SecondT) val;
    usec += ((long) ((RealT) val * 1000000) % 1000000);
#else
    double frac;
    usec += Round(modf(val,&frac) * 1000000);
    sec += (SecondT) frac;
#endif
    NormalisePos();
    return *this;
  }

  const DateC &DateC::operator-=(double val) {
#if 0
    sec -= (SecondT) val;
    usec -= ((long) ((RealT) val * 1000000) % 1000000);
#else
    double frac;
    usec -= Round(modf(val,&frac) * 1000000);
    sec -= (SecondT) frac;
#endif
    NormaliseNeg();
    return *this;
  }

    
}
