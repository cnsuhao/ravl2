// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/RefCounter.hh"
#include "Ravl/RCAbstract.hh"
#include "Ravl/String.hh"
#include "Ravl/OS/DeadLineTimer.hh"
#include "Ravl/OS/ChildOSProcess.hh"
#include "Ravl/StringList.hh"
#include "Ravl/DLIter.hh"
#include "Ravl/Exception.hh"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <iostream.h>
#include <assert.h>
#include <signal.h>

#define DODEBUG 1

#if DODEBUG 
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

using namespace RavlN;

int SelfCheck();
int Validate(char *dir);

StringC procname;

int main(int nargs,char *args[])
{
  procname = args[0];
  bool hang = false;
  bool fault = false;
  bool selfTestOnly = false;
  char *testDir = 0;
  for(int i = 1;i < nargs;i++) {
    if(strcmp(args[i],"-hang") == 0) { // Hang.
      hang = true;
      break;
    }
    if(strcmp(args[i],"-s") == 0) { // Seg fault.
      fault = true;
      break;
    }
    if(strcmp(args[i],"-t") == 0) { // Return true
      exit(0);
      break;
    }
    if(strcmp(args[i],"-f") == 0) { // Return false.
      exit(1);
      break;
    }
    if(strcmp(args[i],"-st") == 0) { // Do only self test.
      selfTestOnly = true;
      continue;
    }
    if(strcmp(args[i],"-h") == 0 || strcmp(args[i],"-help") == 0) { // Help...
      cerr << " -hang    Go into an inifite loop. \n";
      cerr << " -s       Seg fault \n";
      cerr << " -t       Return true\n";
      cerr << " -f       Return false\n";
      cerr << " -st      Self test only\n";
      cerr << " -h or -help  print help.\n";
      exit(0);
      break;
    }
    if(args[i][0] != '-') {
      if(testDir != 0) {
	cerr << "You can only specify one test directory '" << args[i] << "'.\n";
	exit(-1);
      }
      testDir = args[i];
      continue;
    }
  }
  // Do some nasty stuff ?
  while(hang) ;
  if(fault) {
    char *ptr = ((char *)0);
    *ptr = 0;
  }
  try {
    // Do self check.
    if(!SelfCheck()) {
      cerr << "Validate: Self check failed. \n";
      cout << "TEST FAILED. \n" << flush;
      exit(-1);
    }
  
    // Only doing self test ?
    if(selfTestOnly)
      exit(0);
    
    // Do validation.
    if(testDir == 0) {
      cerr << "Validate: No working directory specified. \n";
      cout << "TEST FAILED. \n" << flush;
      exit(-1);
    }
    if(Validate(testDir) == 0) {
      cout << "TEST PASSED. \n" << flush;
      exit(0);
    }
  } catch(exception &ex) {
    cerr << "Std C++ Exception caught : " << ex.what() << endl;
    exit(-1);
  } catch(ExceptionC &ex) {
    cerr << "RAVL Exception caught : " << ex.what() << endl;
    exit(-1);
  } catch(...) {
    cerr << "Unknown exception caught. \n";
    exit(-1);
  }
  cout << "TEST FAILED. \n" << flush;
  exit(1);
}

int Validate(char *dir)
{
  FilenameC testDir(dir);
  FilenameC testDB(testDir + "/TestExes");
  if(!testDir.IsDirectory()) {
    cerr << "VALIDATE: Test directory not found. \n";
    return 2;
  }
  if(!testDir.Exists())
    return 2;
  if(!testDB.Exists()) {
    cerr << "VALIDATE: Test database not found. \n";
    return 2;
  }
  IStreamC in(testDB);
  const int buffsize = 4096;
  char linebuff[buffsize];
  bool passed = true;
  while(in.good()) {
    in.getline(linebuff,buffsize);
    if(in.gcount() == (unsigned int) buffsize) {
      cerr << "ERROR: Line buffer overflow. \n";
      return 2;
    }
    if(in.gcount() == 0)
      continue;
    if(linebuff[0] == '#')
      continue;  // Ignore comments.
    cout << linebuff << " ";
    int space = 15 - strlen(linebuff);
    for(;space > 0;space--)
      cout << ' ';
    cout << "= " << flush;
    FilenameC exeFile(testDir + "/bin/" + linebuff);
    if(!exeFile.Exists()) {
      cout << "FAILED -> Program not found \n";
      passed = false;
      continue;
    }
    FilenameC logfile(testDir + "/log/" + linebuff);
    if(logfile.Exists())
      logfile.Remove();
    ChildOSProcessC testit(exeFile,logfile,true);
    if(!testit.IsRunning()) {
      cout << "FAILED -> Can't run program. \n"<< flush;
      passed = false;
      continue;
    }
    if(!testit.Wait(60 * 2)) { // Wait up to 2 minites
      cout << "FAILED -> Timeout,  Terminated.  \n"<< flush;
      testit.Terminate();
      passed = false;
      continue;
    }
    if(!testit.ExitedOk()) {
      cout << "FAILED -> Abnormal exit,  ";
      int ec = testit.ExitCode();
      switch(ec)
	{
	case SIGSEGV:
	  cout << "Segmentation fault.";
	  break;
	case SIGKILL:
	  cout << "Killed.";
	  break;
	case SIGBUS:
	  cout << "Bus error.";
	  break;
	case SIGFPE:
	  cout << "Floating point exception.";
	  break;
	case SIGILL:
	  cout << "Illegal instruction.";
	  break;	  
	case SIGPIPE:
	  cout << "Broken pipe.";
	  break;	  
	case SIGABRT:
	  cout << "Aborted. (Possible assertion failure.)";
	  break;
	default:
	  cout << "Code:" << ec;
	}
      cout <<" \n"<< flush;
      passed = false;
      continue;
    }
    if(testit.ExitCode() != 0) {
      cout << "FAILED -> Exited with error. Code:" << testit.ExitCode() << " \n"<< flush;
      passed = false;
      continue;
    }
    //logfile.Remove(); // No need for log.
    cout << "PASSED \n" << flush;
  }
  if(passed)
    return 0;
  return 2;
}

