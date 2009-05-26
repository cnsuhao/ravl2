// This file is part of QMake, Quick Make System 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
/**********************************************************************************
//! rcsid="$Id$"
//! file="Ravl/QMake/untouch.cc"
 * untouch, check that a file is at least a second old. (if it exists).
 */
/*! rcsid="$Id$" */
/*! author="Charles Galambos" */
/*! docentry="Ravl.QMake.html" */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <utime.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

int verbose = 0;

int untouch(char *filename,int seconds) {
  struct stat buf;
  struct utimbuf utbuf;
  time_t now,target;
  
  // Find out what the time is currently set to.
  if(stat(filename,&buf)) {
    if(verbose)
      perror("can't stat file ");
    return 0;
  }
  ONDEBUG(printf("Time : %d \n",buf.st_mtime));

  // What time is it now ?
  now = time(0);
  target = now - seconds;

  // Is the file at least 'seconds' old already ?
  if(buf.st_mtime < target)
    return 0; // No need to change anything.
  
  // Change the modification time.
  utbuf.modtime = target;
  utbuf.actime = target;
  if(utime(filename,&utbuf)) {
    perror("failed to change modification time. ");
    return 1;
  }
  return  0;
}

int main(int nargs,char **argv) {
  int seconds =1;
  ONDEBUG(printf("untouch '%s' \n",argv[1]));
  if(nargs < 2) {
    printf("Usage: untouch [files] \n");
    exit(1);
  }
  for(int i = 1;i < nargs;i++) {
    // Check for options.
    if(argv[i][0] == '-') {
      if(argv[i][1] == 'v') {
	if(argv[i][2] == 0) {
	  verbose = 1;
	  continue;
	}
      }
      printf("ERROR: Unrecognised option %s. ",argv[i]);
      return 1;
    }
    // otherwise it must be a file.
    untouch(argv[i],seconds);
  }
  return 0;
}
