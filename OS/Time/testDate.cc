// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlOS
//! file="Ravl/OS/Time/testDate.cc"

#include "Ravl/OS/Date.hh"
#include "Ravl/String.hh"
#include "Ravl/Stream.hh"
//#include <stdlib.h>

using namespace RavlN;

int CheckConsistant();
int CheckIO();

// Check dates are consistant.

int main() 
{
  int lineno;
  cerr << "Starting DateC tests... \n";
  if((lineno = CheckConsistant()) != 0) {
    cerr << "CheckConsistant(), Failed :" << lineno << "\n";
    return 1;
  }
  if((lineno = CheckIO()) != 0) {
    cerr << "CheckIO(), Failed :" << lineno << "\n";
    return 1;
  }
  cerr << "Test passed.\n";
  return 0;
}


int CheckConsistant()
{
  int days = 0;
  int i;
  for(i = 1970;i < 2037;i++) {
    if(days != DateC::YearToDaysSince1970(i)) {
      cerr << "Failed year " << i << " Days:" << days << " Calc:" << DateC::YearToDaysSince1970(i) << " Leap:" << DateC::IsLeapYear(i) << endl;
      return __LINE__;
    }
    if(DateC::IsLeapYear(i))
      days += 366;
    else
      days += 365;
    for(int m = 1;m <= 12;m++) {
      DateC tmp(i,m,1); 
      if(tmp.Year() != i) {
	cerr << "Failed at Month=" << m << " Year=" << i << " Date=" << tmp.CTime() << " Month()=" << tmp.Month() << " Year()=" << tmp.Year() << "\n";
	return __LINE__;
      }
      if(tmp.Month() != m) {
	cerr << "Failed at Month=" << m << " Year=" << i << " Month()=" << tmp.Month() << " CTime()=" << tmp.CTime() << "\n";
	return __LINE__;
      }
    }
  }
  return 0;
}

int CheckIO()
{
  // Check string conversions.
  DateC nowish(true);
  StringC str = nowish.Text();
  cerr << "Str:" << str << "\n";
  DateC t(str);
  cerr << "Rec:" << t.Text() << "\n";
  if(t != nowish)
    return __LINE__;
  return 0;
}
